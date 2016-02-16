#include "recotools.h"
#include "uisetter.h"

#include "benergy/BeamEnergy.h"
#include <CLHEP/Vector/LorentzVector.h>
#include "particle/utility.h"
#include "particle/combination.h"
#include "hamlet/Hamlet.h"
#include "hamlet/Fbtag_MultDimLikelihood0.h"
#include "hamlet/Fbtag_NN1.h"
#include "tagv/TagV.h"

#include "toolbox/FuncPtr.h"
#include "toolbox/FoxWolfr.h"
#include "toolbox/Thrust.h"

using namespace std;
#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

double RTools::ResonanceHelicity(const Particle& b0,const int nch1,const int nch2,double& invmsq){
  return ResonanceHelicity(b0.p(),b0.child(nch1).p(),b0.child(nch2).p(),invmsq);
}

double RTools::ResonanceHelicity(const HepLorentzVector& mov, const HepLorentzVector& ch1v, const HepLorentzVector& ch2v, double& invmsq){
  HepLorentzVector ch1vc = ch1v;
  HepLorentzVector momvc = mov;
  const HepLorentzVector sum_lv = ch1v+ch2v;
  const Hep3Vector h0p3 = -sum_lv.boostVector();
  invmsq = sum_lv.m2();
  ch1vc.boost(h0p3);
  momvc.boost(h0p3);

  const Hep3Vector ch1_p3 = ch1vc.vect().unit();
  const Hep3Vector mom_p3 = momvc.vect().unit();
  return ch1_p3.dot(mom_p3);
}

int RTools::Mbc_deltaE(const Particle& b0,double& mbc,double& de){
  HepLorentzVector lv = b0.p();
  lv.boost(-BeamEnergy::CMBoost());
  const double benergy = BeamEnergy::E_beam_corr();
  de = lv.t() - benergy;
  lv.setT(benergy);
  mbc = lv.mag();
  return 0;
}

double RTools::cosThetaCMS(const Particle& b0){
  HepLorentzVector p = b0.p();
  p.boost(-BeamEnergy::CMBoost());
  return p.cosTheta();
}

double RTools::MissingMass(const Particle& b0){
  HepLorentzVector p(0,0,0,b0.pType().mass());
  p.boost(BeamEnergy::CMBoost());
  p -= b0.child(0).p();
  return p.m();
}

//double RTools::BDecayTime(const Particle& b0){
//  const double mb0 = b0.pType().mass();
//  Hep3Vector dr = b0.x()-IpProfile::position(1);
//  return dr*b0.p3()*mb0/b0.p3().mag2();
//}

//bool RTools::CheckSVD(const Particle& pi){ 
//  Mdst_trk_fit &trk_fit = pi.mdstCharged().trk().mhyp(2);//2 -> pi 
//  if(trk_fit.nhits(3)<1 || trk_fit.nhits(4)<2) return false;// 3 -> rphi, 4 -> z 
//  return true; 
//}

bool RTools::IsTheSame(const Particle& p1, const Particle& p2){
  if(fabs(p1.charge()) != fabs(p2.charge())) return false;
  const Hep3Vector dp = p1.p().vect() - p2.p().vect();
  return dp.mag() < 0.0001 ? true : false;
}

//bool RTools::IsDuplicated(const Particle& b0){
//  const Particle& pi1    = b0.child(1);// pi+
//  const Particle& pi2    = b0.child(2);// pi-
//  const Particle& d0     = b0.child(0);
//  const Particle& d0_pip = d0.child(1);
//  const Particle& d0_pim = d0.child(2);
//  const Particle& ks     = d0.child(0);
//  const Particle& ks_pip = ks.child(0).lund() > 0 ? ks.child(0) : ks.child(1);
//  const Particle& ks_pim = ks.child(0).lund() > 0 ? ks.child(1) : ks.child(0);
//  if(IsTheSame(d0_pip,ks_pip)) return true;
//  if(IsTheSame(d0_pim,ks_pim)) return true;
//  if(IsTheSame(pi1,ks_pip))    return true;
//  if(IsTheSame(pi2,ks_pim))    return true;
//  if(IsTheSame(pi1,d0_pip))    return true;
//  if(IsTheSame(pi2,d0_pim))    return true;
//  return false;
//}

bool RTools::IsDuplicated(const Particle& p){
  vector<Particle*> fspl = p.relation().finalStateParticles();
  for(int i=0; i<fspl.size(); i++){
    for(int j=i+1; j<fspl.size(); j++){
      if(checkSame(*fspl[i],*fspl[j])) return true;
//      if(RTools::MyCheckSame(*fspl[i],*fspl[j])) return true;
//      if(RTools::IsTheSame(*fspl[i],*fspl[j])) return true;
    }
  }
  return false;
}

double RTools::CosThr(const Particle& b0,double& thr_sig,double& thr_oth){
  vector<Hep3Vector> sigtrk,otherb;
  RTools::BoostedList(b0,sigtrk,otherb);

  Hep3Vector thrSig = thrust(sigtrk.begin(),sigtrk.end(),SelfFunc(Hep3Vector()));
  Hep3Vector thrOth = thrust(otherb.begin(),otherb.end(),SelfFunc(Hep3Vector()));
  thr_sig = thrSig.mag();
  thr_oth = thrOth.mag();

  return thrSig.unit().dot(thrOth.unit());
}

int RTools::BoostedList(const Particle& b0,vector<Hep3Vector>&sigtrk,vector<Hep3Vector>&otherb){
  // make lists of track/gamma in signal_b (all charged tracks as pi)
  vector<Particle> pi,pi_m,kpl,kml,allgams;
  makeKPi(kpl,kml,pi,pi_m,false);
//  vector<Particle> pi,pi_m,allgams;
//  make_pi_list(pi,pi_m,false);
  makeGamma(allgams);

  vector<Particle*> final = b0.relation().finalStateParticles();
  pi.insert(pi.end(),pi_m.begin(),pi_m.end());
  pi.insert(pi.end(),allgams.begin(),allgams.end());

  for(int i=0; i<b0.relation().nFinalStateParticles(); i++){
    removeParticle(pi,b0.relation().finalStateParticle(i));
  }

  const Hep3Vector boostv = -BeamEnergy::CMBoost();
  sigtrk.clear(); otherb.clear();

  for(int i=0; i<final.size(); i++){
    HepLorentzVector p = final[i]->p();
    p.boost(boostv);
    sigtrk.push_back(p.vect());
  }

  for(int i=0; i<pi.size(); i++){
    HepLorentzVector p = pi[i].p();
    p.boost(boostv);
    otherb.push_back(p.vect());
  }
  return 0;
}

int RTools::TagVertex(Particle& b0){
  TagVK tagv;
  tagv.setdefault(b0,b0.x());

  vector<Particle> pipl,piml,kpl,kml;
  makeKPi(kpl,kml,pipl,piml);
  pipl.insert(pipl.end(),piml.begin(),piml.end());
  for(int i=0; i<b0.relation().nFinalStateParticles(); i++) removeParticle(pipl,b0.relation().finalStateParticle(i));
  for(int i=0; i<pipl.size(); i++) tagv.push_back(&pipl[i]);
  if(tagv.fit()) return -1;
  if(tagv.chisq_tracks()<0) return -2;
  UISetter::SetTagVtxFitInfo(b0,tagv);
  return 0;
}

int RTools::make_MDLH_b0_tag(Particle &b0){
  Hamlet hamlet;
  hamlet.setBcp(b0);
  hamlet.setTagMethod(Hamlet::MULT_DIM_LH);
  const Fbtag_MultDimLikelihood0 &mdlh_evtgen = hamlet.fbtg_mult_dim_likelihood();
  dynamic_cast<B0UserInfo&>(b0.userInfo()).fqLH(mdlh_evtgen.fq());
  dynamic_cast<B0UserInfo&>(b0.userInfo()).fqErrLH(mdlh_evtgen.fq_err());
  dynamic_cast<B0UserInfo&>(b0.userInfo()).qLH(hamlet.q());
  return 0;
}

int RTools::make_NN_b0_tag(Particle &b0){
  Hamlet hamlet;
  hamlet.setBcp(b0);
  hamlet.setTagMethod(Hamlet::NN1);
  const Fbtag_NN1 &nn_evtgen = hamlet.fbtg_NN1();
//  dynamic_cast<B0UserInfo&>(b0.userInfo()).fqNN(nn_evtgen.fq());
//  dynamic_cast<B0UserInfo&>(b0.userInfo()).fqErrNN(nn_evtgen.fq_err());
//  dynamic_cast<B0UserInfo&>(b0.userInfo()).qNN(hamlet.q());
  return 0;
}

//===
// Select gamma exceeding proper threshold.
//===
int RTools::gamma_tight(Hep3Vector gamma_3v){
  // Energy threshold of gamma shower in GeV.
  const double eth_barrel = 0.05;
  const double eth_fwdec  = 0.10;
  const double eth_bwdec  = 0.10;
  // Gaps between barrel and endcaps in cos(theta).
  const double cos_fwd_gap =  0.8501;
  const double cos_bwd_gap = -0.6643;
  int ireturn = -1; // return value, -1:bad, 0:good.

  if(gamma_3v.cosTheta()>cos_fwd_gap){// In Fwd. Endcap.
    if(gamma_3v.mag()>eth_fwdec){
      ireturn = 0;
    }
  } else if(gamma_3v.cosTheta()<cos_fwd_gap && gamma_3v.cosTheta()>cos_bwd_gap){// In Barrel.
    if(gamma_3v.mag()>eth_barrel){
      ireturn = 0;
    }
  } else{ // In Bwd. Endcap.
    if(gamma_3v.mag()>eth_bwdec){
      ireturn = 0;
    }
  }
  return ireturn;
}

void RTools::KspipiDalitzVars(const Particle& d0,double& mpsq,double& mmsq){
  const HepLorentzVector momp = d0.child(0).p() + d0.child(1).p();
  const HepLorentzVector momm = d0.child(0).p() + d0.child(2).p();
  mpsq = momp.m2();
  mmsq = momm.m2();
  return;
}

bool RTools::MyCheckSame(const Particle &p1,const Particle &p2){
  // same     --> return true;
  // not same --> return false;
  if(p1.nChildren() == 0 && p2.nChildren() == 0){
    /* p1 and p2 have no children */
    return p1.relation().isIdenticalWith(p2.relation());
  } else if(p1.nChildren() > 0 && p2.nChildren() == 0){
    /* p1 have children and no p2 children */
    for(unsigned i1=0; i1<p1.nChildren(); ++i1)
      if(RTools::MyCheckSame(p1.child(i1),p2)) return true;
    return false;
  } else if(p1.nChildren() == 0 && p2.nChildren() > 0){
    /* p2 have children and no p1 children */
    for(unsigned i2=0; i2<p2.nChildren(); ++i2)
      if(RTools::MyCheckSame(p1,p2.child(i2))) return true;
    return false;
  } else{
    /* p1 and p2 both have children */
    for(unsigned i1=0; i1<p1.nChildren(); ++i1)
      for(unsigned i2=0; i2<p2.nChildren(); ++i2)
        if(RTools::MyCheckSame(p1.child(i1),p2.child(i2))) return true;
    return false;
  }
}

void RTools::MyCombination(vector<Particle> &new_p,const Ptype &ptype,vector<Particle> &p1,vector<Particle> &p2){
  for(int i=0; i<p1.size(); i++){
    for(int j=0; j<p2.size(); j++){
      RTools::MyCombinationNoCut(new_p,ptype,p1[i],p2[j]);
    }
  }
}

void RTools::MyCombination(vector<Particle> &new_p,const Ptype &ptype,vector<Particle> &p1,vector<Particle> &p2,const double &massL,const double &massR){
  for(int i=0; i<p1.size(); i++){
    for(int j=0; j<p2.size(); j++){
      RTools::MyCombinationCut(new_p,ptype,p1[i],p2[j],massL,massR);
    }
  }
}

void RTools::MyCombinationNoCut(vector<Particle> &new_p,const Ptype &ptype,Particle &p1,Particle &p2){
  if(RTools::MyCheckSame(p1,p2)) return;
  Particle cand(p1.p() + p2.p(),ptype);
  cand.relation().append(p1);
  cand.relation().append(p2);
  new_p.push_back(cand);
}

void RTools::MyCombinationCut(vector<Particle> &new_p,const Ptype &ptype,Particle &p1,Particle &p2,const double &massL,const double &massR){
  if(RTools::MyCheckSame(p1,p2)) return;
  //...checks mass
  double mass = (p1.p() + p2.p()).m();
  if((massL < mass) && (mass < massR)){
    Particle cand(p1.p() + p2.p(),ptype);
    cand.relation().append(p1);
    cand.relation().append(p2);
    new_p.push_back(cand);
  }
}

int RTools::ChldIndex(const Particle& p,const int ch,const bool absflag){
  const int nch = p.nChildren();
  int i=0;
  for(i=0; i<nch; i++){
    const int lund = absflag ? abs(p.child(i).lund()) : p.child(i).lund();
    if(ch == lund) break;
  }
  return i == nch ? -1 : i;
}

int RTools::GetTrueVertices(const Gen_hepevt& sigb, const vector<Gen_hepevt>& mcl, double& sigv, double& tagv, double& upsv){
  if(!sigb) return -1;
  const Gen_hepevt& tagb = OtherB(sigb,mcl);
  if(tagb == sigb) return -2;

  const Gen_hepevt& tagbch = mcl[tagb.da(0)-1];
  if(!tagbch) return -3;

  const Gen_hepevt& sigbch = mcl[sigb.da(0)-1];
  if(!sigbch) return -4;

  upsv = sigb.V(3);
  sigv = sigbch.V(3) - upsv;
  tagv = tagbch.V(3) - upsv;

  return 0;
}

const Gen_hepevt& RTools::OtherB(const Gen_hepevt& sigb, const vector<Gen_hepevt>& mcl){
  const int sigid = sigb.idhep();
  for(unsigned i=0; i<mcl.size(); i++){
    if(mcl[i].idhep() == -sigid) return mcl[i];
  }
  return sigb;
}

HepLorentzVector RTools::mc_lvtx(const Gen_hepevt& b0){
  return HepLorentzVector(b0.V(0),b0.V(1),b0.V(2),b0.V(3)); 
}

HepLorentzVector RTools::mc_lmom(const Gen_hepevt& b0){
  return HepLorentzVector(b0.P(0),b0.P(1),b0.P(2),b0.P(3)); 
}

const Gen_hepevt& RTools::mc_child(const Gen_hepevt& mo, const vector<Gen_hepevt>& mcl, const int ch, const bool absflag){
  if(!mo) return mo;
  for(int i=mo.daFirst(); i<=mo.daLast(); i++) {
    if(absflag){
      if(abs(mcl[i-1].idhep()) == ch) return mcl[i-1];
    } else{
      if(mcl[i-1].idhep() == ch) return mcl[i-1];
    }
  }
  return mo;
}

#if defined(BELLE_NAMESPACE)
}
#endif

