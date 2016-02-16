#ifndef DINFO_H
#define DINFO_H

#include "particle/ParticleUserInfo.h"

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif 

class DUserInfo : public ParticleUserInfo{
public:
  DUserInfo();
  DUserInfo(const DUserInfo &);
  virtual ~DUserInfo();
  DUserInfo * clone(void) const;
  DUserInfo & operator = (const DUserInfo &);
public:
  void pcm(const double& v) {m_pcm = v;}
  double pcm(void) const {return m_pcm;}

  void m_raw(const double& v) {m_m_raw = v;}
  double m_raw(void) const {return m_m_raw;}

  void FitDone(void) {m_fit_done = true;}
  bool IsFitDone(void) const {return m_fit_done;}

  void FitGood(const bool v) {m_fit_good = v;}
  bool IsFitGood(void) const {return m_fit_good;}

  void MassChi2(const double& v) {m_mass_chi2 = v;}
  double MassChi2(void) const {return m_mass_chi2;}

  void mcflag(const int v) {m_mcflag = v;}
  int mcflag(void) const {return m_mcflag;}

private:
  double m_pcm;
  double m_m_raw;
  double m_mass_chi2;
  bool m_fit_done;
  bool m_fit_good;
  int m_mcflag;
};

#if defined(BELLE_NAMESPACE)
}
#endif 

#endif
