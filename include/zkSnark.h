#pragma once 

#include "Keys.h"
#include "Proof.h"
#include "Encoding.h"
#include "qsp/QSP.h"

/*
class ProvingKey;
class VerificationKey;

*/

class GGPR {
public:
    GGPR(QSP* qsp, Encoding* encoding);
    ~GGPR();
    virtual void genKeyPair(QspProvingKey& prov, QspVerificationKey& verf);

    virtual QspProof *prove(const QspProvingKey &prov);

    virtual bool verify(const QspVerificationKey &verf);

    QSP* qsp;
    Encoding* encoding;
};
