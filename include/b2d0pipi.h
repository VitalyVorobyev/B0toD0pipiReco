#include "particle/Particle.h"
#include "particle/utility.h"
#include "event/BelleEvent.h"
#include "basf/module.h"
#include "basf/module_descr.h"
#include "ip/IpProfile.h"

#include "uisetter.h"
#include "geninfo.h"
#include "dataStructures.h"
#include "recotools.h"
#include "kinefitter.h"
#include "combinator.h"

#include "benergy/BeamEnergy.h"

#include "hamlet/Hamlet.h"

#include <vector>
#include "belle.h"

#include "TTree.h"
#include "TFile.h"

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

class b2d0pipi : public Module{
public:
  b2d0pipi(void):
  clock(0),ntuple_flag(1),n_good_b(0) {}
  ~b2d0pipi(void) {}
  void init(int *);
  void term(void);
  void disp_stat(const char*){}
  void hist_def(void) {}
  void begin_run(BelleEvent*, int*);
  void event(BelleEvent*, int*);
  void end_run(BelleEvent*, int*){}

  int m_mode;//0 -> Data
             //1 -> Signal MC
             //2 -> Genegic M
  int ntuple_flag;
  char ofile[1024];

private:
  bool IsMC(void);
  bool mc_flag;
  TTree* TEvent;
  TFile* tfile;
  int clock;
  int n_good_b;
};

#if defined(BELLE_NAMESPACE)
}
#endif

