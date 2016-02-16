#include "d0info.h"

using namespace std;

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif 

////////////////
//     D0     //
////////////////
D0UserInfo::D0UserInfo() :
  m_m2p(0),
  m_m2m(0),
  m_m2p_raw(0),
  m_m2m_raw(0),
  m_md0_raw(0.),
  m_md0_fit(0.),
  m_vtx_fit_done(false),
  m_vtx_fit_good(false),
  m_vtx_chi2(-1.),
  m_mass_fit_done(false),
  m_mass_fit_good(false),
  m_mass_chi2(-1.),
  m_flv_mc(0),
  m_mode(-1)
{
}

D0UserInfo::~D0UserInfo()
{
}

D0UserInfo::D0UserInfo(const D0UserInfo &x)
{
  *this = x;
}

D0UserInfo* D0UserInfo::clone(void) const
{
  D0UserInfo *x = new D0UserInfo( *this );
  return x;
}

D0UserInfo & D0UserInfo::operator = (const D0UserInfo &x)
{
  m_vtx_fit_done = x.m_vtx_fit_done;
  m_vtx_fit_good = x.m_vtx_fit_good;
  m_mass_fit_done = x.m_mass_fit_done;
  m_mass_fit_good = x.m_mass_fit_good;
  m_m2p = x.m_m2p;
  m_m2m = x.m_m2m;
  m_m2p_raw = x.m_m2p_raw;
  m_m2m_raw = x.m_m2m_raw;
  m_md0_raw = x.m_md0_raw;
  m_md0_fit = x.m_md0_fit;
  m_vtx_chi2 = x.m_vtx_chi2;
  m_mass_chi2 = x.m_mass_chi2;
  m_flv_mc = x.m_flv_mc;
  m_mode  = x.m_mode;
  return *this;
}

#if defined(BELLE_NAMESPACE)
}
#endif 
