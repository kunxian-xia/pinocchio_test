#include "zkSnark.h"

//GGPR

GGPR::GGPR(QSP* qsp, Encoding *encoding) {
    this->qsp = qsp;
    this->encoding = encoding;
}

void GGPR::genKeyPair(QspProvingKey& prov, QspVerificationKey& verf) {
    
}