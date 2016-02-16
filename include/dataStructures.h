#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__

#include "TTree.h"
#include "particle/Particle.h"

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

typedef struct TrackInfo{
  double px, py, pz;   // Momentum
  double r, z;         // Impact parameters
  int rz_svd, rphi_svd;// SVD hits
  double atckpi;       // Identification
  double atckp;
  double eid;
  double muid;
} TrkInfo;

typedef struct Ks0Info{
  double m, m_raw;
  double px, py, pz;
  double dr,dz,dphi,fl;
} KsInfo;

typedef struct Pi0Info{
  double m, m_raw;
  double px, py, pz;
  double eg1,eg2;
  double chisq;
//  double width;
//  double e9oe25;
//  int nhits;
} pi0Info;

typedef struct VertexInfo{
  double z,sz;
  int ntrk,ndf;
  double chisq,cl;
} VtxInfo;

typedef struct SFWMInfo{
  double kmm2;
  double ket;
  double khso00;
  double khso01;
  double khso02;
  double khso03;
  double khso04;
  double khso10;
  double khso12;
  double khso14;
  double khso20;
  double khso22;
  double khso24;
  double khoo0;
  double khoo1;
  double khoo2;
  double khoo3;
  double khoo4;
} sfwmInfo;

typedef struct BEvent{
////////////////////////
//   Main variables   //
////////////////////////
  int exp,run,evtn; //

  double de,mbc; //
  double mp,mm; //
  double mp_raw,mm_raw; //

  double costhBcms;

  VtxInfo recvtx, ascvtx;

  double md0, md0_raw; //
  double chi2_mass_d0;
  double chi2_vtx_d0;
  double chi2_mass_b0;

  TrkInfo pip_ks, pim_ks; // Ks0->    pi+ pi-
  TrkInfo pip_b0, pim_b0; // B0 -> D0 pi+ pi-
  pi0Info pi01_b0,pi02_b0;// B0 -> D0 pi0 pi0

  double px_h0,py_h0,pz_h0;
  TrkInfo hp_d0, hm_d0, hp2_d0, hm2_d0; // D0 -> K+K-, pi+pi-, Kpi, Ks0pi+pi-, Ks0K+K-
  TrkInfo hp_h0, hm_h0; // eta->pi+pi-pi0, omega->pi+pi-pi0, phi->K+K-
  int flv_d0, mode_d0, mode_h0, mode;

  KsInfo ks;
  pi0Info pi0;

  double mdpip,mdpim,mpipi;
  double cos_hel_dpip,cos_hel_dpim,cos_hel_pipi;

  double mdpip_raw,mdpim_raw,mpipi_raw;
  double cos_hel_dpip_raw,cos_hel_dpim_raw,cos_hel_pipi_raw;

  double chi2_vtx_h0; // light pseudoscalar meson
  double chi2_mass_h0;
  double cos_hel_h0;
  double mh0,mh0_raw;

  double ipx,ipy,ipz; //
  double boostx,boosty,boostz; //
//////////////
//  TagFlv  //
//////////////
//  double tag_NN,tag_NN_err; //
  double tag_LH,tag_LH_err; //
  int tagl, taglid;
  int flv;

/////////////////////////////
//  Continuum Suppression  //
/////////////////////////////
  double cos_thr;
  double thr_sig;
  double thr_oth;

  sfwmInfo k0, k1;
}bEvnt;

typedef struct MCSigEvent{
  double mp_mc,mm_mc;
  double z_sig_mc,z_asc_mc;
  double z_upsilon;
  int flv_mc,flv_d0_mc;
//  int nptag;
  double mdpip_mc;
  double mdpim_mc;
  double mpipi_mc;
  double cos_hel_dpip_mc;
  double cos_hel_dpim_mc;
  double cos_hel_pipi_mc;
}MCSigEvnt;

typedef struct MCGenEvent{
  int d0_chain[9];
  int pip_chain[9];
  int pim_chain[9];
  int b0id,b0f;
  int d0id,d0f;
  int type;
  int signal;

  int ngen;
  int idhep[1000];
  int daF[1000];
  int daL[1000];
  int mo[1000];
}MCGenEvnt;

TTree* SetupTreeD0pipi(const int mode);
int FillBEvent(Particle& b0,const bool mc);

#if defined(BELLE_NAMESPACE)
}
#endif

#endif

