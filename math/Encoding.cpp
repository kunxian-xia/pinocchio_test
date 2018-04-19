#include "include/Encoding.h"

#ifdef USE_BN128
#include <libff/algebra/curves/bn128/bn128_pp.hpp>
bool EncodedProduct::operator==(const EncodedProduct &b) {
    return *(this->elem) == *(b.elem);
}
Encoding::Encoding(Field* field) {
    init_bn128_params();
}
void Encoding::encodeL(const FieldElt& a, LEncodedElt& r) {
    bn128_G1 one = bn128_G1::one();
    *(r.point) = operator*<LIMBS>(a, one);
}

void Encoding::encodeR(const FieldElt& a, REncodedElt& r) {
    bn128_G2 one = bn128_G2::one();
    *(r.point) = operator*<LIMBS>(a, one);
}

void Encoding::mul(const LEncodedElt& a, const REncodedElt& b, EncodedProduct& r) {
    *(r.elem) = bn128_pp::pairing(*(a.point), *(b.point));
}

void Encoding::add(const LEncodedElt &a, const LEncodedElt &b, LEncodedElt &r) {
    *(r.point) = *(a.point) + *(b.point);
}
void Encoding::add(const REncodedElt &a, const REncodedElt &b, REncodedElt &r) {
    *(r.point) = *(a.point) + *(b.point);
}
void Encoding::mul(const EncodedProduct &a, const EncodedProduct &b, EncodedProduct &r) {
    *(r.elem) = *(a.elem) * *(b.elem);
}

#elif USE_ALT_BN128



#endif