#include "dinfo.h"

using namespace std;

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif 

////////////////
// D0 and Ds+ //
////////////////
DUserInfo::DUserInfo() :
  m_pcm(0),
  m_mass_chi2(-1.),
  m_m_raw(0.),
  m_fit_done(false),
  m_fit_good(false),
  m_mcflag(0)
{
}

DUserInfo::~DUserInfo()
{
}

DUserInfo::DUserInfo(const DUserInfo &x)
  : m_m_raw(x.m_m_raw),
    m_pcm(x.m_pcm),
    m_fit_done(x.m_fit_done),
    m_fit_good(m_fit_good),
    m_mass_chi2(x.m_mass_chi2),
    m_mcflag(x.m_mcflag)
{
}

DUserInfo* DUserInfo::clone(void) const
{
  DUserInfo *x = new DUserInfo( *this );
  return x;
}

DUserInfo& DUserInfo::operator=(const DUserInfo &x){
  m_fit_done = x.m_fit_done;
  m_fit_good = x.m_fit_good;
  m_m_raw = x.m_m_raw;
  m_pcm = x.m_pcm;
  m_mass_chi2 = x.m_mass_chi2;
  m_mcflag = x.m_mcflag;

  return *this;
}

#if defined(BELLE_NAMESPACE)
}
#endif 
