#ifndef __COMBINATOR_H__
#define __COMBINATOR_H__

//#include HEPEVT_H
#include "particle/Particle.h"
#include <vector>

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

class Combinator{
public:
  Combinator() {}
  ~Combinator() {}

  static void SetNT(const bool ntuple_flag) {m_ntuple_flag = ntuple_flag;}
  static void SetMC(const bool mc_flag)     {m_mc_flag = mc_flag;}

// * B0 makers * //
  static int make_b0tod0pipi(std::vector<Particle>& b0l,std::vector<Particle> &d0l,std::vector<Particle> &pipl, std::vector<Particle> &piml);
  static int make_vtx_for_b0tod0pipi(Particle& b0);
  static int make_mass_for_b0tod0pipi(Particle& b0);
  static int make_b0tod0pi0pi0(std::vector<Particle>& b0l,std::vector<Particle> &d0l,std::vector<Particle> &pi0l);

  static int make_kpi(std::vector<Particle> &pipl, std::vector<Particle> &piml, std::vector<Particle> &kpl, std::vector<Particle> &kml);
  static int make_ks(std::vector<Particle> &ksl);
  static int make_pi0(std::vector<Particle> &pi0l);

  static int make_phitokk(std::vector<Particle> &phil,std::vector<Particle> &kpl,std::vector<Particle> &kml);

// * h0 makers * //
  // eta -> gg
  static int make_etato2g(std::vector<Particle>& etal, std::vector<Particle>& gammas);
  // eta ->pi+ pi- pi0
  static int make_etato3pi(std::vector<Particle>& etal,std::vector<Particle>& pipl,std::vector<Particle>& piml,std::vector<Particle>& pi0l);
  // omega -> pi+ pi- pi0
  static int make_omega(std::vector<Particle>& omegal,std::vector<Particle>& pipl,std::vector<Particle>& piml,std::vector<Particle>& pi0l);
// * * //

// * D0 makers * //
  // D0 -> Ks0 h+ h-
  static int make_d0tok0shh(std::vector<Particle> &d0l,std::vector<Particle> &ksl,std::vector<Particle> &hpl,std::vector<Particle> &hml);
  // D0 -> K+K-, pi+pi-, Ks0 pi0,  Ks0 eta, Ks0 omega, Ks0 phi
  static int make_d0tohh(std::vector<Particle> &d0l,std::vector<Particle> &h1l,std::vector<Particle> &h2l,const bool narrow = false); 
  // D0 -> K+ pi-
  static int make_d0tokpi(std::vector<Particle> &d0l,std::vector<Particle> &kpl,std::vector<Particle> &piml,std::vector<Particle> &kml,std::vector<Particle> &pipl);
  // D0 -> K+ pi- pi0
  static int make_d0tokpipi0(std::vector<Particle> &d0l,std::vector<Particle> &kpl,std::vector<Particle> &piml,std::vector<Particle> &kml,std::vector<Particle> &pipl,std::vector<Particle> &pi0l);
  // D0 -> K+ pi- pi+ pi-
  static int make_d0tokpipipi(std::vector<Particle> &d0l,std::vector<Particle> &kpl,std::vector<Particle> &piml,std::vector<Particle> &kml,std::vector<Particle> &pipl);
// * * //

// * Ds makers * //
  // Ds+ -> phi pi+
  static int make_dstophipi(std::vector<Particle> &dsl,std::vector<Particle> &phil,std::vector<Particle> &pipl,std::vector<Particle> &piml);
// * * //

// //
private:
  static void setH0toGGErrors(std::vector<Particle>& etal);

  static bool m_ntuple_flag;
  static bool m_mc_flag;
  static double d0mmin;
  static double d0mmax;
  static double d0mmin_narrow;
  static double d0mmax_narrow;
  static double mphi_min;
  static double mphi_max;
  static double mds_min;
  static double mds_max;
  static double m_omega_min;
  static double m_omega_max;
  static double m_eta_min_ppp;
  static double m_eta_max_ppp;
  static double m_eta_min_gg;
  static double m_eta_max_gg;
};

#if defined(BELLE_NAMESPACE)
}
#endif

#endif

