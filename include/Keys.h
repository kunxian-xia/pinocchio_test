#include "Encoding.h"

class QspProvingKey {
public:
    QspProvingKey();
    ~QspProvingKey();

    LEncodedElt* sPowers;
    LEncodedElt* alphaSPowers;

    LEncodedElt* V;
    REncodedElt* W;

    LEncodedElt* alphaV;
    REncodedElt* alphaW;

    LEncodedElt* betavV;
    LEncodedElt* betawW;

};

class QspVerificationKey {
public: 
    LEncodedElt alphaL;
    REncodedElt alphaR;

    LEncodedElt gamma;
    LEncodedElt betavGamma;
    LEncodedElt betawGamma;
};
