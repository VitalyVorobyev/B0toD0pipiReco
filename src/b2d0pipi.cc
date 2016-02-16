#include "b2d0pipi.h"

using namespace std;

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

const bool dump = false;
extern "C" Module_descr *mdcl_b2d0pipi()
{
  b2d0pipi *module = new b2d0pipi;
  Module_descr *dscr = new Module_descr("b2d0pipi",module);
  BeamEnergy::define_global(dscr);
  dscr->define_param("mode","mode",&module->m_mode);
  dscr->define_param("ofile","ofile",1024,module->ofile);
  dscr->define_param("ntuple_flag","ntuple_flag",&module->ntuple_flag);
  return dscr;
}

void b2d0pipi::init(int *){
  std::cout << "init" << endl;
  Ptype dummy("VPHO");
  if(ntuple_flag) Hamlet::init();
  return;
}

bool b2d0pipi::IsMC(void){
  Belle_runhead_Manager &rhd_mgr = Belle_runhead_Manager::get_manager();
  std::vector<Belle_runhead>::const_iterator rhd = rhd_mgr.begin();
  if(rhd == rhd_mgr.end()){
    fprintf(stderr,"Constructor: Cannot access to Belle_runhead\n");
    return false;
  } else{
    if(rhd->ExpMC() == 1) return false;//real data
    else                  return true;
  }
  return false;
}

void b2d0pipi::begin_run(BelleEvent* evptr, int *status){
  IpProfile::begin_run();
  BeamEnergy::begin_run();
  eid::init_data();
  if(ntuple_flag){
    Hamlet::begin_run(Hamlet::MULT_DIM_LH);
  } else{
//    UISetter::m_rphi_svd = 0;// no SVD hits requirement at skim level
//    UISetter::m_rz_svd   = 0;
  }
  mc_flag = IsMC();
  if(ntuple_flag && !clock){
    clock = 1;
    tfile = new TFile(ofile,"RECREATE");
    cout << ofile << endl;
    TEvent = SetupTreeD0pipi(m_mode);
  }
  Combinator::SetNT(ntuple_flag);
  Combinator::SetMC(mc_flag);
  UISetter::SetMC(mc_flag);

  return;
}

void b2d0pipi::term(void){
  cout << "Term " << ofile << endl;
  if(ntuple_flag){
    cout << "Term TEvent: " << TEvent->GetEntries() << endl;
    TEvent->Write();
    tfile->Close();
  }
  cout << "# of Good B0: " << n_good_b << endl;
}

void b2d0pipi::event(BelleEvent* evptr, int *status){
  *status = 0;
  Belle_event_Manager& evtmgr = Belle_event_Manager::get_manager();
  Belle_event& evthead = *evtmgr.begin();
  const int evtn = evthead.EvtNo() & 0xfffffff;
  if(!(evtn%100)) cout << "run: " << evthead.RunNo() << ", evtn: " << evtn << endl;
  if(!IpProfile::usable()){ std::cout<<"IP profile is not available!!!\n"; return; }

  const bool no_pi0  = false;
  const bool no_hppp = false || no_pi0;

  const bool mode_0  = true;// Ks0 pi+ pi-

  const bool modes_flv = true;
  const bool mode_10 = modes_flv && true;// K- pi+
  const bool mode_11 = modes_flv && false && !no_pi0;// K- pi+ pi0
  const bool mode_12 = modes_flv && false;// K- pi+ pi- pi+

  const bool modes_cp = true;
  const bool mode_20 = modes_cp && true;// K- K+
  const bool mode_21 = modes_cp && false;// pi+ pi-
  const bool mode_22 = modes_cp && true && !no_pi0;// Ks0 pi0
  const bool mode_23 = modes_cp && false;// Ks0 eta
  const bool mode_24 = modes_cp && false && !no_hppp;// Ks0 omega
  const bool mode_25 = modes_cp && true;// Ks0 phi

  const bool mode_d0pipi   = true;
  const bool mode_d0pi0pi0 = false;
  const bool pi0modes = mode_d0pi0pi0 || mode_24 || mode_23 || mode_22 || mode_11;

  vector<Particle> pipl,piml,kpl,kml;
  Combinator::make_kpi(pipl,piml,kpl,kml);

  vector<Particle> ksl;
  Combinator::make_ks(ksl);

  vector<Particle> pi0l;
  if(!(no_pi0 || !pi0modes)) Combinator::make_pi0(pi0l);
  vector<Particle> gammal;
  vector<Particle> etal;
  vector<Particle> etaggl,etapppl,omegal,phil;
  if(mode_23){
    Combinator::make_etato2g(etaggl,gammal);
    if(ntuple_flag) UISetter::SetModeEta(etaggl,10);
    etal.insert(etal.end(),etaggl.begin(),etaggl.end());
  }
  if(!no_hppp && mode_23){
    Combinator::make_etato3pi(etapppl,pipl,piml,pi0l);
    if(ntuple_flag) UISetter::SetModeEta(etapppl,20);
    etal.insert(etal.end(),etapppl.begin(),etapppl.end());
  }
  if(mode_24) Combinator::make_omega(omegal,pipl,piml,pi0l);
  if(mode_25) Combinator::make_phitokk(phil,kpl,kml);

// ** D0 lists ** //
  vector<Particle> d0l;
  // * D0 -> Ks0 pi+ pi- * //
  vector<Particle> d0ksppl;
  if(mode_0){
    Combinator::make_d0tok0shh(d0ksppl,ksl,pipl,piml);
    if(ntuple_flag) UISetter::SetModeD0(d0ksppl,0);
    d0l.insert(d0l.end(),d0ksppl.begin(),d0ksppl.end());
  }
  // * D0 -> Flavor states * //
  vector<Particle> d0kpil, d0kpipi0l, d0kpipipil;
  if(mode_10){
    Combinator::make_d0tokpi(d0kpil,kpl,piml,kml,pipl);
    if(ntuple_flag) UISetter::SetModeD0(d0kpil,10);
    d0l.insert(d0l.end(),d0kpil.begin(),d0kpil.end());
  }
  if(mode_11){
    Combinator::make_d0tokpipi0(d0kpipi0l,kpl,piml,kml,pipl,pi0l);
    if(ntuple_flag) UISetter::SetModeD0(d0kpipi0l,11);
    d0l.insert(d0l.end(),d0kpipi0l.begin(),d0kpipi0l.end());
  }
  if(mode_12){
    Combinator::make_d0tokpipipi(d0kpipipil,kpl,piml,kml,pipl);
    if(ntuple_flag) UISetter::SetModeD0(d0kpipipil,12);
    d0l.insert(d0l.end(),d0kpipipil.begin(),d0kpipipil.end());
  }
  // * D0 -> CP states * //
  vector<Particle> d0kkl,d0pipil,d0ks0pi0l,d0ks0etal,d0ks0omegal,d0ks0phil;
  if(mode_20){
    Combinator::make_d0tohh(d0kkl,kpl,kml);
    if(ntuple_flag) UISetter::SetModeD0(d0kkl,20);
    d0l.insert(d0l.end(),d0kkl.begin(),d0kkl.end());
  }
  if(mode_21){
    Combinator::make_d0tohh(d0pipil,pipl,piml);
    if(ntuple_flag) UISetter::SetModeD0(d0pipil,21);
    d0l.insert(d0l.end(),d0pipil.begin(),d0pipil.end());
  }
  if(mode_22){
    Combinator::make_d0tohh(d0ks0pi0l,ksl,pi0l);
    if(ntuple_flag) UISetter::SetModeD0(d0ks0pi0l,22);
    d0l.insert(d0l.end(),d0ks0pi0l.begin(),d0ks0pi0l.end());
  }
  if(mode_23){
    Combinator::make_d0tohh(d0ks0etal,ksl,etal,true);
    if(ntuple_flag) UISetter::SetModeD0(d0ks0etal,23);
    d0l.insert(d0l.end(),d0ks0etal.begin(),d0ks0etal.end());
  }
  if(mode_24){
    Combinator::make_d0tohh(d0ks0omegal,ksl,omegal,true);
    if(ntuple_flag) UISetter::SetModeD0(d0ks0omegal,24);
    d0l.insert(d0l.end(),d0ks0omegal.begin(),d0ks0omegal.end());
  }
  if(mode_25){
    Combinator::make_d0tohh(d0ks0phil,ksl,phil);
    if(ntuple_flag) UISetter::SetModeD0(d0ks0phil,25);
    d0l.insert(d0l.end(),d0ks0phil.begin(),d0ks0phil.end());
  }
// ** ** //
  vector<Particle> b0l,b0tod0pi0pi0l;
  if(mode_d0pipi){
   n_good_b += Combinator::make_b0tod0pipi(b0l,d0l,pipl,piml);
    if(ntuple_flag) UISetter::SetModeB0(b0l,1);
  }
  if(mode_d0pi0pi0){
    n_good_b += Combinator::make_b0tod0pi0pi0(b0tod0pi0pi0l,d0l,pi0l);
    if(ntuple_flag) UISetter::SetModeB0(b0tod0pi0pi0l,2);
    b0l.insert(b0l.end(),b0tod0pi0pi0l.begin(),b0tod0pi0pi0l.end());
  }
  if(!b0l.size()) return;
  if(ntuple_flag){
    for(int i=0; i<b0l.size(); i++){
      FillBEvent(b0l[i],mc_flag);
      TEvent->Fill();
    }
  } else{
    *status = 1;
  }
  pipl.clear(), piml.clear(), kpl.clear(), kml.clear();
  ksl.clear(); pi0l.clear();
  gammal.clear();
  etal.clear();
  etaggl.clear(), etapppl.clear(), omegal.clear(), phil.clear();
  d0l.clear();
  d0ksppl.clear();
  d0kpil.clear(), d0kpipi0l.clear(), d0kpipipil.clear();
  d0kkl.clear(), d0pipil.clear(), d0ks0pi0l.clear(), d0ks0etal.clear(), d0ks0omegal.clear(), d0ks0phil.clear();
  b0l.clear(); b0tod0pi0pi0l.clear();
  return;
}

#if defined(BELLE_NAMESPACE)
}
#endif

