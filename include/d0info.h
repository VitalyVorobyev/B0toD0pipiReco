#ifndef D0INFO_H
#define D0INFO_H

#include "particle/ParticleUserInfo.h"

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif 

class D0UserInfo : public ParticleUserInfo{
public:
  D0UserInfo();
  D0UserInfo(const D0UserInfo &);
  virtual ~D0UserInfo();
  D0UserInfo * clone(void) const;
  D0UserInfo & operator = (const D0UserInfo &);
public:
  void SetDalitzVars(const double& m2p, const double& m2m) {m_m2p = m2p; m_m2m = m2m;}
  double m2p(void) const {return m_m2p;}
  double m2m(void) const {return m_m2m;}

  void SetRawDalitzVars(const double& m2p, const double& m2m) {m_m2p_raw = m2p; m_m2m_raw = m2m;}
  double m2p_raw(void) const {return m_m2p_raw;}
  double m2m_raw(void) const {return m_m2m_raw;}

  void Mass(const double& v) {m_md0_raw = v;}
  double Mass(void) const {return m_md0_raw;}

  void md0_fit(const double& v) {m_md0_fit = v;}
  double md0_fit(void) const {return m_md0_fit;}

  void VtxFitDone(void) {m_vtx_fit_done = true;}
  bool IsVtxFitDone(void) const {return m_vtx_fit_done;}

  void VtxFitGood(const bool v) {m_vtx_fit_good = v;}
  bool IsVtxFitGood(void) const {return m_vtx_fit_good;}

  void VtxChi2(const double& v) {m_vtx_chi2 = v;}
  double VtxChi2(void) const {return m_vtx_chi2;}

  void MassFitDone(void) {m_mass_fit_done = true;}
  bool IsMassFitDone(void) const {return m_mass_fit_done;}

  void MassFitGood(const bool v) {m_mass_fit_good = v;}
  bool IsMassFitGood(void) const {return m_mass_fit_good;}

  void MassChi2(const double& v) {m_mass_chi2 = v;}
  double MassChi2(void) const {return m_mass_chi2;}

//////////
//  MC  //
//////////
  void FlvMC(const int v) {m_flv_mc = v;}
  int FlvMC(void) const {return m_flv_mc;}

  void Mode(const int mode) {m_mode = mode; return;}
  int Mode(void) const {return m_mode;}
private:
  double m_m2p,m_m2m;
  double m_m2p_raw,m_m2m_raw;

  double m_md0_raw;
  double m_md0_fit;

  int m_flv_mc;

  bool m_vtx_fit_done;
  bool m_vtx_fit_good;
  double m_vtx_chi2;

  bool m_mass_fit_done;
  bool m_mass_fit_good;
  double m_mass_chi2;

  int m_mode;
};

#if defined(BELLE_NAMESPACE)
}
#endif 

#endif
