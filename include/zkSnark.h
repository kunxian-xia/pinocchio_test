#include "Keys.h"
#include "Proof.h"
#include "Encoding.h"
#include "qsp/QSP.h"


class zkSnark {
public:
  virtual void genKeyPair(QspProvingKey &prov, QspVerificationKey &verf) = 0;

  virtual QspProof *prove(const QspProvingKey &prov) = 0;

  virtual bool verify(const QspVerificationKey &verf) = 0;

  QSP *qsp;
};

class GGPR : zkSnark {
public:
    GGPR();
    ~GGPR();
};
