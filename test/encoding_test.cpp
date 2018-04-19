#include "include/Encoding.h"
#include <libff/algebra/fields/bigint.hpp>
using namespace libff;

void runPairTest() {
    field_desc_tc* field_desc = new field_desc_tc;
    Field f(field_desc);
     /* parameters for scalar field Fr */
    field_desc->modulus = bigint<LIMBS>("21888242871839275222246405745257275088548364400416034343698204186575808495617");
    if (sizeof(mp_limb_t) == 8)
    {
        field_desc->Rsquared = bigint<LIMBS>("944936681149208446651664254269745548490766851729442924617792859073125903783");
        field_desc->Rcubed = bigint<LIMBS>("5866548545943845227489894872040244720403868105578784105281690076696998248512");
        field_desc->inv = 0xc2e1f593efffffff;
    }
    if (sizeof(mp_limb_t) == 4)
    {
        field_desc->Rsquared = bigint<LIMBS>("944936681149208446651664254269745548490766851729442924617792859073125903783");
        field_desc->Rcubed = bigint<LIMBS>("5866548545943845227489894872040244720403868105578784105281690076696998248512");
        field_desc->inv = 0xefffffff;
    }
    field_desc->num_bits = 254;
    field_desc->euler = bigint<LIMBS>("10944121435919637611123202872628637544274182200208017171849102093287904247808");
    field_desc->s = 28;
    field_desc->t = bigint<LIMBS>("81540058820840996586704275553141814055101440848469862132140264610111");
    field_desc->t_minus_1_over_2 = bigint<LIMBS>("40770029410420498293352137776570907027550720424234931066070132305055");
    
    Encoding* encoding = new Encoding(&f);
    FieldElt one = bigint<LIMBS>("1");
    FieldElt a = bigint<LIMBS>("10"); FieldElt aprime = bigint<LIMBS>("11");  
    FieldElt b = bigint<LIMBS>("11");
    LEncodedElt ea, eaprime, eone, er;
    REncodedElt eb;
    EncodedProduct eab, eaprimeb, eoneb, eer;
    encoding->encodeL(a, ea); 
    encoding->encodeL(one, eone);
    encoding->encodeL(aprime, eaprime);
    encoding->encodeR(b, eb);

    encoding->add(ea, eone, er);
    if (*(er.point) == *(eaprime.point)) {
        std::cout << "addition holds in G1" << std::endl;
    }
    encoding->mul(ea, eb, eab);
    encoding->mul(eone, eb, eoneb);
    encoding->mul(eaprime, eb, eaprimeb);

    encoding->mul(eab, eoneb, eer);
    eer.elem->print();
    eaprimeb.elem->print();
    if (eer == eaprimeb) {
        std::cout << "bilinear property holds in Gt" << std::endl;
    } else {
        std::cout << "does not satisfy bilinear property" << std::endl;
    }
}

int main()
{
    runPairTest();
}