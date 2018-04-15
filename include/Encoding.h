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

class LEncodedElt;
class REncodedElt;
class EncodedProduct;

typedef FieldElt LEncodedElt[3];
typedef FieldElt REncodedElt[6];
typedef FieldElt EncodedProduct[12];

//template <typename A>
class Encoding {
  public:
    Encoding(Field *f);

    virtual void encode(FieldElt &a, LEncodedElt &r);
    virtual void encode(FieldElt &a, REncodedElt &r);

    virtual void pair(const LEncodedElt &a, const REncodedElt &b, EncodedProduct &r);
    virtual void mul(const LEncodedElt &a, const REncodedElt &b, EncodedProduct &r);

  private:
    Field *field;
};