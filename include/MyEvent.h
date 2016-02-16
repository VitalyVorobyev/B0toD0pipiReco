#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__

#include "TObject.h"
#include "TTree.h"
#include "particle/Particle.h"


#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

class TrackInfo : public TObject{
public:
  TrackInfo(void);
  void Clear();

private:
  Double_t px, py, pz;   // Momentum
  Double_t r, z;         // Impact parameters
  Int_t rz_svd, rphi_svd;// SVD hits
  Double_t atckpi;       // Identification
};


#if defined(BELLE_NAMESPACE)
}
#endif
