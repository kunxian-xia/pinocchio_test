#pragma once

#include "Encoding.h"

class QspProof {
public:
    LEncodedElt Vmid;
    LEncodedElt alphaVmid;

    REncodedElt W;
    REncodedElt alphaW;

    LEncodedElt H;
    LEncodedElt alphaH;

    LEncodedElt betaVW;    
};


