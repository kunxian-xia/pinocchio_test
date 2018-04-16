#include "include/Field.h"
#include <libff/algebra/fields/fp.hpp>
using namespace libff;

bigint<LIMBS> FIELDMODULUS;

Field::Field(field_desc_tc* field)
{
    msfield = field;
    FIELDMODULUS = msfield->modulus;
    Fp_model<LIMBS, FIELDMODULUS>::inv = msfield->inv;
    Fp_model<LIMBS, FIELDMODULUS>::euler = msfield->euler;
    Fp_model<LIMBS, FIELDMODULUS>::num_bits = msfield->num_bits;
    Fp_model<LIMBS, FIELDMODULUS>::Rsquared = msfield->Rsquared;
    Fp_model<LIMBS, FIELDMODULUS>::s = msfield->s;
    Fp_model<LIMBS, FIELDMODULUS>::t = msfield->t;
    Fp_model<LIMBS, FIELDMODULUS>::t_minus_1_over_2 = msfield->t_minus_1_over_2;
    Fp_model<LIMBS, FIELDMODULUS>::Rcubed = msfield->Rcubed;

    memcpy(ctr.data, msfield->one.data, sizeof(FieldElt));
}

void Field::assignRandomElt(FieldElt* elt)
{
    bigint<LIMBS> r;
    do
    {
        r.randomize();

        /* clear all bits higher than MSB of modulus */
        size_t bitno = GMP_NUMB_BITS * LIMBS - 1;
        while (msfield->modulus.test_bit(bitno) == false)
        {
            const std::size_t part = bitno/GMP_NUMB_BITS;
            const std::size_t bit = bitno - (GMP_NUMB_BITS*part);

            r.data[part] &= ~(1ul<<bit);

            bitno--;
        }
    }
   /* if r.data is still >= modulus -- repeat (rejection sampling) */
    while (mpn_cmp(r.data, msfield->modulus.data, LIMBS) >= 0);
    memcpy(elt->data, r.data, sizeof(FieldElt));
}

FieldElt* Field::newRandomElt()
{
    FieldElt* elt = new FieldElt;
    assignRandomElt(elt);
    return elt;
}

FieldElt* Field::newOne()
{
    FieldElt* elt = new FieldElt;
    memcpy(elt->data, msfield->one.data, sizeof(FieldElt));
}

unsigned int Field::bit(int index, FieldElt& in)
{
    assert(index >= 0 && index < LIMBS*sizeof(mp_limb_t)*8);
    int word, offset;
    unsigned int bit;
    word = index/(8*sizeof(mp_limb_t));
    offset = index - word*8*sizeof(mp_limb_t);

    bit = (in.data[word] >> offset) & 1;
    return bit;
}

void Field::set(FieldElt& a, int i)
{

}

void Field::mul(const FieldElt& a, const FieldElt& b, FieldElt& c)
{
    Fp_model<LIMBS, FIELDMODULUS> tmpA;
    Fp_model<LIMBS, FIELDMODULUS> tmpB;

    tmpA.mont_repr = a;
    tmpB.mont_repr = b;
    tmpA *= tmpB;
    memcpy(c.data, tmpA.mont_repr.data, sizeof(FieldElt));
}

void Field::div(const FieldElt& a, const FieldElt& b, FieldElt& c)
{
    Fp_model<LIMBS, FIELDMODULUS> tmpA;
    Fp_model<LIMBS, FIELDMODULUS> tmpB;
    Fp_model<LIMBS, FIELDMODULUS> tmpBinv;

    tmpA.mont_repr = a;
    tmpB.mont_repr = b;
    tmpBinv = tmpB.invert();
    tmpA *= tmpBinv;
    memcpy(c.data, tmpA.mont_repr.data, sizeof(FieldElt));
}
void Field::add(const FieldElt& a, const FieldElt& b, FieldElt& c)
{
    Fp_model<LIMBS, FIELDMODULUS> tmpA;
    Fp_model<LIMBS, FIELDMODULUS> tmpB;

    tmpA.mont_repr = a;
    tmpB.mont_repr = b;
    tmpA += tmpB;
    memcpy(c.data, tmpA.mont_repr.data, sizeof(FieldElt));
}

void Field::sub(const FieldElt& a, const FieldElt& b, FieldElt& c)
{
    Fp_model<LIMBS, FIELDMODULUS> tmpA;
    Fp_model<LIMBS, FIELDMODULUS> tmpB;

    tmpA.mont_repr = a;
    tmpB.mont_repr = b;
    tmpA += tmpB;
    memcpy(c.data, tmpA.mont_repr.data, sizeof(FieldElt));
}

void Field::print(const FieldElt& e)
{
    FieldElt* ebar = mont_to_std(e);
    ebar->print();
    //e.print();
}

void Field::print_hex(const FieldElt& e) {
    FieldElt* ebar = mont_to_std(e);
    ebar->print_hex();
}

//void Field::print_hex()
void Field::assignFreshElt(FieldElt* elt)
{
    memcpy(elt->data, ctr.data, sizeof(FieldElt));
    add(ctr, ctr, ctr);
}

bool Field::isZero(FieldElt& a)
{
    FieldElt tmp;
    zero(tmp);

    return memcmp(a.data, tmp.data, sizeof(FieldElt)) == 0;
}

FieldElt* Field::mont_to_std(const FieldElt& a) {
    FieldElt* abar = new FieldElt;
    Fp_model<LIMBS, FIELDMODULUS> tmp;
    tmp.mont_repr.data[0] = 1;
    tmp.mul_reduce(a);

    copy(tmp.mont_repr, *abar);
    return abar;
}