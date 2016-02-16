#include "combinator.h"

#include "uisetter.h"
#include "recotools.h"
#include "kinefitter.h"

#include "particle/PID.h"
#include "particle/utility.h"
#include "particle/combination.h"
#include "particle/ParticleUserInfo.h"
#include "mdst/findKs.h"
#include "nisKsFinder/nisKsFinder.h"
#include "mdst/mdst.h"
#include "ip/IpProfile.h"

#include MDST_H
#include HEPEVT_H
//#include BELLETDF_H
//#include EVTCLS_H

using namespace std;
#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

bool   Combinator::m_ntuple_flag = false;
bool   Combinator::m_mc_flag     = false;
double Combinator::d0mmin        = 1.865 - 0.065;
double Combinator::d0mmax        = 1.865 + 0.065;
double Combinator::d0mmin_narrow = 1.865 - 0.065;
double Combinator::d0mmax_narrow = 1.865 + 0.065;
double Combinator::mds_min       = 1.967 - 0.065;
double Combinator::mds_max       = 1.967 + 0.065;
double Combinator::mphi_min      = 0.99;
double Combinator::mphi_max      = 1.05;
double Combinator::m_omega_min   = 0.78265-0.030;
double Combinator::m_omega_max   = 0.78265+0.030;
double Combinator::m_eta_min_gg  = 0.547862-0.035;
double Combinator::m_eta_max_gg  = 0.547862+0.035;
double Combinator::m_eta_min_ppp = 0.547862-0.020;
double Combinator::m_eta_max_ppp = 0.547862+0.020;

int Combinator::make_kpi(vector<Particle> &pipl,vector<Particle> &piml,vector<Particle> &kpl,vector<Particle> &kml){
  pipl.clear(); piml.clear(); kpl.clear(); kml.clear();
  const Gen_hepevt &null = Gen_hepevt_Manager::get_manager().get_NULL();

  Mdst_charged_Manager &chg_mgr = Mdst_charged_Manager::get_manager();
  for(vector<Mdst_charged>::const_iterator i = chg_mgr.begin(); i != chg_mgr.end(); i++){
    const Mdst_charged& track = *i;
    Particle pi(track,Ptype(track.charge()>0 ? "PI+" : "PI-"));
    Particle K(track,Ptype(track.charge()>0  ? "K+"  : "K-" ));

    if(m_ntuple_flag){
      pi.userInfo(TrkUserInfo());
      K.userInfo(TrkUserInfo());
      UISetter::SetTrkInfo(pi);
      UISetter::SetTrkInfo(K);

      const int flag = UISetter::CheckTrk(K,true);
      if(flag>0 && flag!=6) continue;
      const double rip = fabs(((const TrkUserInfo&)K.userInfo()).r());
      if(!(rip<2)){
        cout << "r = " << rip << ", flag = " << flag << endl;
      }
      const Gen_hepevt &h = m_mc_flag ? get_hepevt(track) : null;
      if(h){
        pi.relation().genHepevt(h);
        K.relation().genHepevt(h);
      }
      if(track.charge() > 0){
        pipl.push_back(pi);
        if(flag != 6) kpl.push_back(K);
      } else{
        piml.push_back(pi);
        if(flag != 6) kml.push_back(K);
      }
    } else{
      const int flag = UISetter::CheckTrk(K,false);
      if(flag>0 && flag!=6) continue;
      if(track.charge() > 0){
        pipl.push_back(pi);
        if(flag != 6) kpl.push_back(K);
      } else{
        piml.push_back(pi);
        if(flag != 6) kml.push_back(K);
      }
    }
  }
  return pipl.size()+piml.size();
}

int Combinator::make_ks(vector<Particle> &ksl){
  ksl.clear();
  const Gen_hepevt &null = Gen_hepevt_Manager::get_manager().get_NULL();
  nisKsFinder ksnb;

  Mdst_vee2_Manager &vee2_mgr = Mdst_vee2_Manager::get_manager();
  const HepPoint3D IP = IpProfile::usable() ? IpProfile::e_position() : HepPoint3D(0);
  for(vector<Mdst_vee2>::iterator i = vee2_mgr.begin(); i != vee2_mgr.end(); i++){
    Mdst_vee2 &vee2 = *i;
    int kind = vee2.kind();
    if(kind != 1) continue;
    ksnb.candidates(vee2,IP);
    if(!ksnb.standard()) continue;
    Particle p(vee2);
    if(p.p().m()>0.52 || p.p().m()<0.48) continue;
    const Gen_hepevt &h = m_mc_flag ? get_hepevt(vee2) : null;
    if(h) p.relation().genHepevt(h);
    if(m_ntuple_flag){
      p.userInfo(KsUserInfo());
      dynamic_cast<KsUserInfo&>(p.userInfo()).dr(ksnb.drp()>ksnb.drn() ? ksnb.drp() : ksnb.drn());
      dynamic_cast<KsUserInfo&>(p.userInfo()).dz(ksnb.zdist());
      dynamic_cast<KsUserInfo&>(p.userInfo()).dphi(ksnb.dphi());
      dynamic_cast<KsUserInfo&>(p.userInfo()).fl(ksnb.fl());
    }
    ksl.push_back(p);
  }
  return ksl.size();
}

int Combinator::make_d0tok0shh(std::vector<Particle> &d0l,std::vector<Particle> &ksl,std::vector<Particle> &hpl,std::vector<Particle> &hml){
  d0l.clear(); combination(d0l,Ptype("D0"),ksl,hpl,hml);
  withMassCut(d0l,d0mmin,d0mmax);
  if(m_ntuple_flag) UISetter::SetD0lInfo(d0l);
  return d0l.size();
}

int Combinator::make_d0tohh(std::vector<Particle> &d0l,std::vector<Particle> &h1l,std::vector<Particle> &h2l,const bool narrow){
  d0l.clear();
  combination(d0l,Ptype("D0"),h1l,h2l);
  if(narrow) withMassCut(d0l,d0mmin_narrow,d0mmax_narrow);
  else       withMassCut(d0l,d0mmin,d0mmax);
  if(m_ntuple_flag) UISetter::SetD0lInfo(d0l);
  return d0l.size();
}

int Combinator::make_d0tokpi(std::vector<Particle> &d0l,std::vector<Particle> &kpl,std::vector<Particle> &piml,std::vector<Particle> &kml,std::vector<Particle> &pipl){
  d0l.clear();
  combination(d0l,Ptype("D0"),kml,pipl);
  withMassCut(d0l,d0mmin,d0mmax);
  vector<Particle> d0bl;
  combination(d0bl,Ptype("D0B"),kpl,piml);
  withMassCut(d0bl,d0mmin,d0mmax);
  d0l.insert(d0l.end(),d0bl.begin(),d0bl.end());
  if(m_ntuple_flag) UISetter::SetD0lInfo(d0l);
  return d0l.size();
}

int Combinator::make_d0tokpipi0(std::vector<Particle> &d0l,std::vector<Particle> &kpl,std::vector<Particle> &piml,std::vector<Particle> &kml,std::vector<Particle> &pipl,std::vector<Particle> &pi0l){
  d0l.clear();
  combination(d0l,Ptype("D0"),kml,pipl,pi0l);
  withMassCut(d0l,d0mmin_narrow,d0mmax_narrow);
  vector<Particle> d0bl;
  combination(d0bl,Ptype("D0B"),kpl,piml,pi0l);
  withMassCut(d0bl,d0mmin_narrow,d0mmax_narrow);
  d0l.insert(d0l.end(),d0bl.begin(),d0bl.end());
  if(m_ntuple_flag) UISetter::SetD0lInfo(d0l);
  return d0l.size();
}

int Combinator::make_d0tokpipipi(std::vector<Particle> &d0l,std::vector<Particle> &kpl,std::vector<Particle> &piml,std::vector<Particle> &kml,std::vector<Particle> &pipl){
  d0l.clear();
  combination(d0l,Ptype("D0"),pipl,piml,pipl,kml);
  withMassCut(d0l,d0mmin_narrow,d0mmax_narrow);
  vector<Particle> d0bl;
  combination(d0bl,Ptype("D0B"),piml,pipl,piml,kpl);
  withMassCut(d0bl,d0mmin_narrow,d0mmax_narrow);
  d0l.insert(d0l.end(),d0bl.begin(),d0bl.end());
  if(m_ntuple_flag) UISetter::SetD0lInfo(d0l);
  return d0l.size();
}

int Combinator::make_pi0(vector<Particle> &pi0l){
  pi0l.clear();
  const Gen_hepevt &null = Gen_hepevt_Manager::get_manager().get_NULL();
// pi0 > gamma gamma
  Mdst_pi0_Manager &pi0_mgr = Mdst_pi0_Manager::get_manager();
  for(vector<Mdst_pi0>::const_iterator i = pi0_mgr.begin(); i != pi0_mgr.end(); i++){
    const Mdst_pi0& pi0 = *i;
    Particle p(pi0);
    if(p.child(0).p().t() < 0.04 || p.child(1).p().t() < 0.04) continue;
    if(m_ntuple_flag){
      const Gen_hepevt &h = m_mc_flag ? get_hepevt(pi0) : null;
      if(h) p.relation().genHepevt(h);
      const Gen_hepevt &hg1 = m_mc_flag ? get_hepevt(p.child(0).mdstGamma()) : null;
      if(hg1) p.child(0).relation().genHepevt(hg1);
      const Gen_hepevt &hg2 = m_mc_flag ? get_hepevt(p.child(1).mdstGamma()) : null;
      if(hg2) p.child(1).relation().genHepevt(hg2);
      p.userInfo(Pi0UserInfo());
      dynamic_cast<Pi0UserInfo&>(p.userInfo()).Mass(pi0.mass());
      dynamic_cast<Pi0UserInfo&>(p.userInfo()).Chi2(pi0.chisq());
      setGammasError(p,HepPoint3D(0),1.*HepSymMatrix(3,1));// Necessary for kinematic fitting
    }
    pi0l.push_back(p);
  }
  return pi0l.size();
}

void Combinator::setH0toGGErrors(vector<Particle>& etal){
//  const HepPoint3D origin;
//  HepSymMatrix dx = HepSymMatrix(3,1)*1.0;
//  setGammaError(eta.child(0),origin,dx);
//  setGammaError(eta.child(1),origin,dx);
  for(int i=0; i<etal.size(); i++) setGammasError(etal[i],HepPoint3D(0),1.*HepSymMatrix(3,1));
}

int Combinator::make_etato2g(vector<Particle>& etal, vector<Particle>& gammas){
  etal.clear();
// eta -> gamma gamma
  gammas.clear();
  makeGamma(gammas); withPCut(gammas,0.08);
  combination(etal,Ptype(221),gammas,gammas);
  withMassCut(etal,m_eta_min_gg,m_eta_max_gg);
  if(m_ntuple_flag){
    UISetter::Seth0lInfo(etal);
    Combinator::setH0toGGErrors(etal);
  }
  return etal.size();
}

int Combinator::make_etato3pi(vector<Particle>& etal,vector<Particle>& pipl,vector<Particle>& piml,vector<Particle>& pi0l){
  etal.clear();
  combination(etal,Ptype(221),pipl,piml,pi0l);
  withMassCut(etal,m_eta_min_ppp,m_eta_max_ppp);
  if(m_ntuple_flag) UISetter::Seth0lInfo(etal);
  return etal.size();
}

int Combinator::make_omega(vector<Particle>& omegal,vector<Particle>& pipl,vector<Particle>& piml,vector<Particle>& pi0l){
  omegal.clear();
// omega -> pi+ pi- pi0
  combination(omegal,Ptype(223),pipl,piml,pi0l);
  withMassCut(omegal,m_omega_min,m_omega_max);
  if(m_ntuple_flag) UISetter::Seth0lInfo(omegal);
  return omegal.size();
}

int Combinator::make_phitokk(vector<Particle> &phil,vector<Particle> &kpl,vector<Particle> &kml){
  phil.clear();
  combination(phil,Ptype("PHI"),kpl,kml);
  withMassCut(phil,mphi_min,mphi_max);
  if(m_ntuple_flag) UISetter::SetPhilInfo(phil);
  return phil.size();
}

int Combinator::make_dstophipi(vector<Particle> &dsl,vector<Particle> &phil,vector<Particle> &pipl,vector<Particle> &piml){
  dsl.clear();
  combination(dsl,Ptype("DS+"),phil,pipl);
  withMassCut(dsl,mds_min,mds_max);

  vector<Particle> dsml;
  combination(dsml,Ptype("DS-"),phil,piml);
  withMassCut(dsml,mds_min,mds_max);
  dsl.insert(dsl.end(),dsml.begin(),dsml.end());

  if(m_ntuple_flag) UISetter::SetDslInfo(dsl);
  return dsl.size();
}

int Combinator::make_b0tod0pipi(std::vector<Particle>& b0l,std::vector<Particle> &d0l,std::vector<Particle> &pipl, std::vector<Particle> &piml){
  b0l.clear();
  combination(b0l,Ptype("B0"),d0l,pipl,piml);
  double mbc,de;
  for(int i=0; i<b0l.size(); i++){
    Particle& B0 = b0l[i];
    RTools::Mbc_deltaE(B0,mbc,de);
    if(!m_ntuple_flag){
      if(fabs(de)<0.35 && mbc>5.18 && mbc<5.31){
        if(!RTools::IsDuplicated(B0)) return 1;
      }
    } else{
      B0.userInfo(B0UserInfo());
      UISetter::SetB0toDhhRawInfo(B0);
      if(de>0.3 || de<-0.3 || mbc<5.25 || mbc>5.30){ b0l.erase(b0l.begin()+i); i--; continue; }
      if(RTools::IsDuplicated(B0)){                  b0l.erase(b0l.begin()+i); i--; continue; }
      if(make_vtx_for_b0tod0pipi(B0)){
        UISetter::SetBadVtx(B0);             // b0l.erase(b0l.begin()+i); i--; continue; }
        UISetter::SetMbc_deltaE(B0,mbc,de);
        continue;
      }
      if(make_mass_for_b0tod0pipi(B0)){
        UISetter::SetBadMass(B0);             // b0l.erase(b0l.begin()+i); i--; continue; }
      }      
      UISetter::SetMbc_deltaE(B0,mbc,de);
    }
  }
  return b0l.size();
}

int Combinator::make_vtx_for_b0tod0pipi(Particle& b0){
  const int d0index = RTools::ChldIndex(b0,421,true);
  if(d0index<0) return -4;// There is no D0 among children
  Particle& D0 = b0.child(d0index);
  // * Vertex fitting * //
  const bool d0_vtx_fit_done = ((const D0UserInfo&)D0.userInfo()).IsVtxFitDone();
  if(!d0_vtx_fit_done){
    double d0_vtx_chisq = -1;
    const int d0_vtx_fit_flag = KineFitter::vtx_fit_r(D0,d0_vtx_chisq);
    dynamic_cast<D0UserInfo&>(D0.userInfo()).VtxChi2(d0_vtx_chisq);
    dynamic_cast<D0UserInfo&>(D0.userInfo()).VtxFitDone();
    dynamic_cast<D0UserInfo&>(D0.userInfo()).VtxFitGood(!d0_vtx_fit_flag);
  }
  const bool d0_vtx_fit_good = ((const D0UserInfo&)D0.userInfo()).IsVtxFitGood();
  if(!d0_vtx_fit_good){
    cout << "Bad D0 vtx fit for mode " << ((const D0UserInfo&)D0.userInfo()).Mode() << endl;
    return -1;
  }
  int fit_flag = 0; 
  kvertexfitter kvf = KineFitter::vtx_fit(b0,true,fit_flag);
  if(fit_flag) return -2;
  UISetter::SetSigVtxFitInfo(b0,kvf);
  if(RTools::TagVertex(b0)) return -3;
  return 0;
}

int Combinator::make_mass_for_b0tod0pipi(Particle& b0){
  const int d0index = RTools::ChldIndex(b0,421,true);
  if(d0index<0) return -4;// There is no D0 among children
  Particle& D0 = b0.child(d0index);
  const bool d0_mass_fit_done = ((const D0UserInfo&)D0.userInfo()).IsMassFitDone();
  if(!d0_mass_fit_done){
    double d0_mass_chisq = -1;
    const int d0_mass_fit_flag = KineFitter::mass_fit_r(D0,d0_mass_chisq);
    dynamic_cast<D0UserInfo&>(D0.userInfo()).MassChi2(d0_mass_chisq);
    dynamic_cast<D0UserInfo&>(D0.userInfo()).MassFitDone();
    dynamic_cast<D0UserInfo&>(D0.userInfo()).MassFitGood(!d0_mass_fit_flag);
  }
  const bool d0_mass_fit_good = ((const D0UserInfo&)D0.userInfo()).IsMassFitGood();
  if(!d0_mass_fit_good){
    cout << "Bad D0 mass fit for mode " << ((const D0UserInfo&)D0.userInfo()).Mode() << endl;
    return -1;
  }
  kmassfitter kmf = KineFitter::mass_fit(b0,true);
  UISetter::SetB0toDhhMassFitInfo(b0,kmf);
  return 0;
}

int Combinator::make_b0tod0pi0pi0(std::vector<Particle>& b0l,std::vector<Particle> &d0l,std::vector<Particle> &pi0l){
  b0l.clear();
  combination(b0l,Ptype("B0"),d0l,pi0l,pi0l);
  double mbc,de;
  for(int i=0; i<b0l.size(); i++){
    Particle& B0 = b0l[i];
    RTools::Mbc_deltaE(B0,mbc,de);
    if(!m_ntuple_flag){
      if(fabs(de)<0.32 && mbc>5.18 && mbc<5.31){
        if(!RTools::IsDuplicated(B0)) return 1;
      }
    } else{
      B0.userInfo(B0UserInfo());
      if(de>0.3 || de<-0.3 || mbc<5.2 || mbc>5.3){
        b0l.erase(b0l.begin()+i); i--;
        continue;
      }
      if(RTools::IsDuplicated(B0)){
        b0l.erase(b0l.begin()+i); i--;
        continue;
      }
      int d0index = 0;
           if(abs(B0.child(0).lund()) == 421) d0index = 0;
      else if(abs(B0.child(1).lund()) == 421) d0index = 1;
      else if(abs(B0.child(2).lund()) == 421) d0index = 2;
      else continue;
      Particle& D0 = B0.child(d0index);
      const bool d0_vtx_fit_done = ((const D0UserInfo&)D0.userInfo()).IsVtxFitDone();
      if(!d0_vtx_fit_done){
        double d0_vtx_chisq = -1;
        const int d0_vtx_fit_flag = KineFitter::vtx_fit_r(D0,d0_vtx_chisq);
        dynamic_cast<D0UserInfo&>(D0.userInfo()).VtxChi2(d0_vtx_chisq);
        dynamic_cast<D0UserInfo&>(D0.userInfo()).VtxFitDone();
        dynamic_cast<D0UserInfo&>(D0.userInfo()).VtxFitGood(!d0_vtx_fit_flag);
      }
      const bool d0_vtx_fit_good = ((const D0UserInfo&)D0.userInfo()).IsVtxFitGood();
      if(!d0_vtx_fit_good){
        b0l.erase(b0l.begin()+i); i--;
        continue;
      }
      if(KineFitter::b0tod0pipi_d0vtx_fit(B0)){
        b0l.erase(b0l.begin()+i); i--;
        continue;
      }
      if(RTools::TagVertex(B0)){
        b0l.erase(b0l.begin()+i); i--;
        continue;
      }
      UISetter::SetMbc_deltaE(B0,mbc,de);
    }
  }
  return b0l.size();
}

#if defined(BELLE_NAMESPACE)
}
#endif

