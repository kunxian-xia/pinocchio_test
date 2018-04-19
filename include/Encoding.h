/*
 * base curve G1: E(Fp) 
 *  each point is (x, y, z) 
 * 
 * twisted curve G2: defined over Fp2
 *  each point is (xbar, ybar, zbar)
 * 
 * target group Gt: { h \in Fp12: h^r = 1 for some r }
 * 
 * fields: Fp, Fp2, Fp12
 * 
 */ 
#include "Types.h"
#include "Field.h"

#ifdef USE_BN128
#include <libff/algebra/curves/bn128/bn128_g1.hpp>
#include <libff/algebra/curves/bn128/bn128_g2.hpp>
#include <libff/algebra/curves/bn128/bn128_gt.hpp>
#include <libff/algebra/curves/bn128/bn128_init.hpp>
using namespace libff;

class LEncodedElt {
public:
    LEncodedElt() { point = new bn128_G1; }
    ~LEncodedElt() { delete point; }

    bn128_G1* point;
};

class REncodedElt {
public:
    REncodedElt() { point = new bn128_G2; }
    ~REncodedElt() { delete point; }

    bn128_G2* point;
};

class EncodedProduct {
public:
    EncodedProduct() { elem = new bn128_GT; }
    ~EncodedProduct() { delete elem; }

    bool operator==(const EncodedProduct &b);
    bn128_GT* elem;
};

#elif defined(USE_ALT_BN128)

#include <libff/algebra/curves/alt_bn128/alt_bn128_g1.hpp>
#include <libff/algebra/curves/alt_bn128/alt_bn128_init.hpp>
using libff;

class LEncodedElt {
public:
    LEncodedElt() { point = new alt_bn128_G1; }
    ~LEncodedElt() { delete point; }

    alt_bn128_G1* point;
};

class REncodedElt {
public:
    REncodedElt() {};
    ~REncodedElt() {};

    alt_bn128_G1* point;
};

//#else 

#endif

//template <typename A>
class Encoding {
  public:
    Encoding(Field *f);

    void encodeL(const FieldElt &a, LEncodedElt &r);
    void encodeR(const FieldElt &a, REncodedElt &r);

    void pair(const LEncodedElt &a, const REncodedElt &b, EncodedProduct &r);
    void mul(const LEncodedElt &a, const REncodedElt &b, EncodedProduct &r);

    void add(const LEncodedElt &a, const LEncodedElt &b, LEncodedElt &r);
    void add(const REncodedElt &a, const REncodedElt &b, REncodedElt &r);
    void mul(const EncodedProduct &a, const EncodedProduct &b, EncodedProduct &r);
  private:
    Field *field;
};