#include "dataStructures.h"
#include "uisetter.h"
#include "geninfo.h"
#include "recotools.h"
#include "belle.h"
#include "ksfwmoments.h"
#include HEPEVT_H
#include "event/BelleEvent.h"
#include "benergy/BeamEnergy.h"
#include "ip/IpProfile.h"

using namespace std;

#if defined(BELLE_NAMESPACE)
namespace Belle {
#endif

bEvnt bEvt;
MCSigEvnt MCSigEvt;
MCGenEvnt MCGenEvt;

TTree* SetupTreeD0pipi(const int mode){
  TTree* TEvent = new TTree("TEvent","TEvent");
  TEvent->Branch("exp",&bEvt.exp,"exp/I");
  TEvent->Branch("run",&bEvt.run,"run/I");
  TEvent->Branch("evtn",&bEvt.evtn,"evtn/I");

  TEvent->Branch("de",&bEvt.de,"de/D");
  TEvent->Branch("mbc",&bEvt.mbc,"mbc/D");
  TEvent->Branch("mp",&bEvt.mp,"mp/D");
  TEvent->Branch("mm",&bEvt.mm,"mm/D");
//  TEvent->Branch("mp_raw",&bEvt.mp_raw,"mp_raw/D");
//  TEvent->Branch("mm_raw",&bEvt.mm_raw,"mm_raw/D");

  TEvent->Branch("costhBcms",&bEvt.costhBcms,"costhBcms/D");

  TEvent->Branch("z_rec",&bEvt.recvtx.z,"z_rec/D");
  TEvent->Branch("sz_rec",&bEvt.recvtx.sz,"sz_rec/D");
  TEvent->Branch("ndf_rec",&bEvt.recvtx.ndf,"ndf_rec/I");
  TEvent->Branch("ntrk_rec",&bEvt.recvtx.ntrk,"ntrk_rec/I");
  TEvent->Branch("chisq_rec",&bEvt.recvtx.chisq,"chisq_rec/D");

  TEvent->Branch("z_asc",&bEvt.ascvtx.z,"z_asc/D");
  TEvent->Branch("sz_asc",&bEvt.ascvtx.sz,"sz_asc/D");
  TEvent->Branch("ndf_asc",&bEvt.ascvtx.ndf,"ndf_asc/I");
  TEvent->Branch("ntrk_asc",&bEvt.ascvtx.ntrk,"ntrk_asc/I");
  TEvent->Branch("chisq_asc",&bEvt.ascvtx.chisq,"chisq_asc/D");

  TEvent->Branch("md0",&bEvt.md0,"md0/D");
  TEvent->Branch("md0_raw",&bEvt.md0_raw,"md0_raw/D");
  TEvent->Branch("chi2_vtx_d0",&bEvt.chi2_vtx_d0,"chi2_vtx_d0/D");
  TEvent->Branch("chi2_mass_d0",&bEvt.chi2_mass_d0,"chi2_mass_d0/D");
  TEvent->Branch("chi2_mass_b0",&bEvt.chi2_mass_b0,"chi2_mass_b0/D");

  TEvent->Branch("mh0",&bEvt.mh0,"mh0/D");
  TEvent->Branch("mh0_raw",&bEvt.mh0_raw,"mh0_raw/D");
  TEvent->Branch("chi2_vtx_h0",&bEvt.chi2_vtx_h0,"chi2_vtx_h0/D");
  TEvent->Branch("chi2_mass_h0",&bEvt.chi2_mass_h0,"chi2_mass_h0/D");
  TEvent->Branch("cos_hel_h0",&bEvt.cos_hel_h0,"cos_hel_h0/D");

  TEvent->Branch("px_hp_d0",&bEvt.hp_d0.px,"px_hp_d0/D");
  TEvent->Branch("py_hp_d0",&bEvt.hp_d0.py,"py_hp_d0/D");
  TEvent->Branch("pz_hp_d0",&bEvt.hp_d0.pz,"pz_hp_d0/D");
  TEvent->Branch("r_hp_d0",&bEvt.hp_d0.r,"r_hp_d0/D");
  TEvent->Branch("z_hp_d0",&bEvt.hp_d0.z,"z_hp_d0/D");
  TEvent->Branch("rz_svd_hp_d0",&bEvt.hp_d0.rz_svd,"rz_svd_hp_d0/I");
  TEvent->Branch("rphi_svd_hp_d0",&bEvt.hp_d0.rphi_svd,"rphi_svd_hp_d0/I");
  TEvent->Branch("atckpi_hp_d0",&bEvt.hp_d0.atckpi,"atckpi_hp_d0/D");
  TEvent->Branch("atckp_hp_d0",&bEvt.hp_d0.atckp,"atckp_hp_d0/D");
  TEvent->Branch("eid_hp_d0",&bEvt.hp_d0.eid,"eid_hp_d0/D");
  TEvent->Branch("muid_hp_d0",&bEvt.hp_d0.muid,"muid_hp_d0/D");

  TEvent->Branch("px_hm_d0",&bEvt.hm_d0.px,"px_hm_d0/D");
  TEvent->Branch("py_hm_d0",&bEvt.hm_d0.py,"py_hm_d0/D");
  TEvent->Branch("pz_hm_d0",&bEvt.hm_d0.pz,"pz_hm_d0/D");
  TEvent->Branch("r_hm_d0",&bEvt.hm_d0.r,"r_hm_d0/D");
  TEvent->Branch("z_hm_d0",&bEvt.hm_d0.z,"z_hm_d0/D");
  TEvent->Branch("rz_svd_hm_d0",&bEvt.hm_d0.rz_svd,"rz_svd_hm_d0/I");
  TEvent->Branch("rphi_svd_hm_d0",&bEvt.hm_d0.rphi_svd,"rphi_svd_hm_d0/I");
  TEvent->Branch("atckpi_hm_d0",&bEvt.hm_d0.atckpi,"atckpi_hm_d0/D");
  TEvent->Branch("atckp_hm_d0",&bEvt.hm_d0.atckp,"atckp_hm_d0/D");
  TEvent->Branch("eid_hm_d0",&bEvt.hm_d0.eid,"eid_hm_d0/D");
  TEvent->Branch("muid_hm_d0",&bEvt.hm_d0.muid,"muid_hm_d0/D");

//  TEvent->Branch("px_hp2_d0",&bEvt.hp2_d0.px,"px_hp2_d0/D");
//  TEvent->Branch("py_hp2_d0",&bEvt.hp2_d0.py,"py_hp2_d0/D");
//  TEvent->Branch("pz_hp2_d0",&bEvt.hp2_d0.pz,"pz_hp2_d0/D");
//  TEvent->Branch("r_hp2_d0",&bEvt.hp2_d0.r,"r_hp2_d0/D");
//  TEvent->Branch("z_hp2_d0",&bEvt.hp2_d0.z,"z_hp2_d0/D");
//  TEvent->Branch("rz_svd_hp2_d0",&bEvt.hp2_d0.rz_svd,"rz_svd_hp2_d0/I");
//  TEvent->Branch("rphi_svd_hp2_d0",&bEvt.hp2_d0.rphi_svd,"rphi_svd_hp_2d0/I");
//  TEvent->Branch("atckpi_hp2_d0",&bEvt.hp2_d0.atckpi,"atckpi_hp2_d0/D");

//  TEvent->Branch("px_hm2_d0",&bEvt.hm2_d0.px,"px_hm2_d0/D");
//  TEvent->Branch("py_hm2_d0",&bEvt.hm2_d0.py,"py_hm2_d0/D");
//  TEvent->Branch("pz_hm2_d0",&bEvt.hm2_d0.pz,"pz_hm2_d0/D");
//  TEvent->Branch("r_hm2_d0",&bEvt.hm2_d0.r,"r_hm2_d0/D");
//  TEvent->Branch("z_hm2_d0",&bEvt.hm2_d0.z,"z_hm2_d0/D");
//  TEvent->Branch("rz_svd_hm2_d0",&bEvt.hm2_d0.rz_svd,"rz_svd_hm2_d0/I");
//  TEvent->Branch("rphi_svd_hm2_d0",&bEvt.hm2_d0.rphi_svd,"rphi_svd_hm2_d0/I");
//  TEvent->Branch("atckpi_hm2_d0",&bEvt.hm2_d0.atckpi,"atckpi_hm2_d0/D");

  TEvent->Branch("px_pip_b0",&bEvt.pip_b0.px,"px_pip_b0/D");
  TEvent->Branch("py_pip_b0",&bEvt.pip_b0.py,"py_pip_b0/D");
  TEvent->Branch("pz_pip_b0",&bEvt.pip_b0.pz,"pz_pip_b0/D");
  TEvent->Branch("r_pip_b0",&bEvt.pip_b0.r,"r_pip_b0/D");
  TEvent->Branch("z_pip_b0",&bEvt.pip_b0.z,"z_pip_b0/D");
  TEvent->Branch("rz_svd_pip_b0",&bEvt.pip_b0.rz_svd,"rz_svd_pip_b0/I");
  TEvent->Branch("rphi_svd_pip_b0",&bEvt.pip_b0.rphi_svd,"rphi_svd_pip_b0/I");
  TEvent->Branch("atckpi_pip_b0",&bEvt.pip_b0.atckpi,"atckpi_pip_b0/D");
  TEvent->Branch("atckp_pip_b0",&bEvt.pip_b0.atckp,"atckp_pip_b0/D");
  TEvent->Branch("eid_pip_b0",&bEvt.pip_b0.eid,"eid_pip_b0/D");
  TEvent->Branch("muid_pip_b0",&bEvt.pip_b0.muid,"muid_pip_b0/D");

  TEvent->Branch("px_pim_b0",&bEvt.pim_b0.px,"px_pim_b0/D");
  TEvent->Branch("py_pim_b0",&bEvt.pim_b0.py,"py_pim_b0/D");
  TEvent->Branch("pz_pim_b0",&bEvt.pim_b0.pz,"pz_pim_b0/D");
  TEvent->Branch("r_pim_b0",&bEvt.pim_b0.r,"r_pim_b0/D");
  TEvent->Branch("z_pim_b0",&bEvt.pim_b0.z,"z_pim_b0/D");
  TEvent->Branch("rz_svd_pim_b0",&bEvt.pim_b0.rz_svd,"rz_svd_pim_b0/I");
  TEvent->Branch("rphi_svd_pim_b0",&bEvt.pim_b0.rphi_svd,"rphi_svd_pim_b0/I");
  TEvent->Branch("atckpi_pim_b0",&bEvt.pim_b0.atckpi,"atckpi_pim_b0/D");
  TEvent->Branch("atckp_pim_b0",&bEvt.pim_b0.atckp,"atckp_pim_b0/D");
  TEvent->Branch("eid_pim_b0",&bEvt.pim_b0.eid,"eid_pim_b0/D");
  TEvent->Branch("muid_pim_b0",&bEvt.pim_b0.muid,"muid_pim_b0/D");

  TEvent->Branch("px_hp_h0",&bEvt.hp_h0.px,"px_hp_h0/D");
  TEvent->Branch("py_hp_h0",&bEvt.hp_h0.py,"py_hp_h0/D");
  TEvent->Branch("pz_hp_h0",&bEvt.hp_h0.pz,"pz_hp_h0/D");
  TEvent->Branch("r_hp_h0",&bEvt.hp_h0.r,"r_hp_h0/D");
  TEvent->Branch("z_hp_h0",&bEvt.hp_h0.z,"z_hp_h0/D");
  TEvent->Branch("rz_svd_hp_h0",&bEvt.hp_h0.rz_svd,"rz_svd_hp_h0/I");
  TEvent->Branch("rphi_svd_hp_h0",&bEvt.hp_h0.rphi_svd,"rphi_svd_hp_h0/I");
  TEvent->Branch("atckpi_hp_h0",&bEvt.hp_h0.atckpi,"atckpi_hp_h0/D");
  TEvent->Branch("atckp_hp_h0",&bEvt.hp_h0.atckp,"atckp_hp_h0/D");
  TEvent->Branch("eid_hp_h0",&bEvt.hp_h0.eid,"eid_hp_h0/D");
  TEvent->Branch("muid_hp_h0",&bEvt.hp_h0.muid,"muid_hp_h0/D");

  TEvent->Branch("px_hm_h0",&bEvt.hm_h0.px,"px_hm_d0/D");
  TEvent->Branch("py_hm_h0",&bEvt.hm_h0.py,"py_hm_d0/D");
  TEvent->Branch("pz_hm_h0",&bEvt.hm_h0.pz,"pz_hm_d0/D");
  TEvent->Branch("r_hm_h0",&bEvt.hm_h0.r,"r_hm_d0/D");
  TEvent->Branch("z_hm_h0",&bEvt.hm_h0.z,"z_hm_d0/D");
  TEvent->Branch("rz_svd_hm_h0",&bEvt.hm_h0.rz_svd,"rz_svd_hm_h0/I");
  TEvent->Branch("rphi_svd_hm_h0",&bEvt.hm_h0.rphi_svd,"rphi_svd_hm_h0/I");
  TEvent->Branch("atckpi_hm_h0",&bEvt.hm_h0.atckpi,"atckpi_hm_h0/D");
  TEvent->Branch("atckp_hm_h0",&bEvt.hm_h0.atckp,"atckp_hm_h0/D");
  TEvent->Branch("eid_hm_h0",&bEvt.hm_h0.eid,"eid_hm_h0/D");
  TEvent->Branch("muid_hm_h0",&bEvt.hm_h0.muid,"muid_hm_h0/D");

  TEvent->Branch("flv_d0",&bEvt.flv_d0,"flv_d0/I");
  TEvent->Branch("mode_d0",&bEvt.mode_d0,"mode_d0/I");
  TEvent->Branch("mode_h0",&bEvt.mode_h0,"mode_h0/I");
  TEvent->Branch("mode",&bEvt.mode,"mode/I");

  TEvent->Branch("ks_dr",&bEvt.ks.dr,"ks_dr/D");
  TEvent->Branch("ks_dz",&bEvt.ks.dz,"ks_dz/D");
  TEvent->Branch("ks_dphi",&bEvt.ks.dphi,"ks_dphi/D");
  TEvent->Branch("ks_fl",&bEvt.ks.fl,"ks_fl/D");
  TEvent->Branch("mks",&bEvt.ks.m,"mks/D");
  TEvent->Branch("mks_raw",&bEvt.ks.m_raw,"mks_raw/D");
  TEvent->Branch("px_ks",&bEvt.ks.px,"px_ks/D");
  TEvent->Branch("py_ks",&bEvt.ks.py,"py_ks/D");
  TEvent->Branch("pz_ks",&bEvt.ks.pz,"pz_ks/D");

  TEvent->Branch("mpi0",&bEvt.pi0.m,"mpi0/D");
  TEvent->Branch("mpi0_raw",&bEvt.pi0.m_raw,"mpi0_raw/D");
  TEvent->Branch("px_pi0",&bEvt.pi0.px,"px_pi0/D");
  TEvent->Branch("py_pi0",&bEvt.pi0.py,"py_pi0/D");
  TEvent->Branch("pz_pi0",&bEvt.pi0.pz,"pz_pi0/D");
  TEvent->Branch("eg1_pi0",&bEvt.pi0.eg1,"eg1_pi0/D");
  TEvent->Branch("eg2_pi0",&bEvt.pi0.eg2,"eg2_pi0/D");
  TEvent->Branch("chi2_pi0",&bEvt.pi0.chisq,"chi2_pi0/D");

//  TEvent->Branch("mpi01_b0",    &bEvt.pi01_b0.m,    "mpip01_d0/D");
//  TEvent->Branch("mpi01_b0_raw",&bEvt.pi01_b0.m_raw,"mpi01_b0_raw/D");
//  TEvent->Branch("px_pi01_b0",  &bEvt.pi01_b0.px,   "px_pi01_b0/D");
//  TEvent->Branch("py_pi01_b0",  &bEvt.pi01_b0.py,   "py_pi01_b0/D");
//  TEvent->Branch("pz_pi01_b0",  &bEvt.pi01_b0.pz,   "pz_pi01_b0/D");
//  TEvent->Branch("eg1_pi01_b0", &bEvt.pi01_b0.eg1,  "eg1_pi01_b0/D");
//  TEvent->Branch("eg2_pi01_b0", &bEvt.pi01_b0.eg2,  "eg2_pi01_b0/D");
//  TEvent->Branch("chi2_pi01_b0",&bEvt.pi01_b0.chisq,"chi2_pi01_b0/D");

//  TEvent->Branch("mpi02_b0",    &bEvt.pi02_b0.m,    "mpip02_d0/D");
//  TEvent->Branch("mpi02_b0_raw",&bEvt.pi02_b0.m_raw,"mpi02_b0_raw/D");
//  TEvent->Branch("px_pi02_b0",  &bEvt.pi02_b0.px,   "px_pi02_b0/D");
//  TEvent->Branch("py_pi02_b0",  &bEvt.pi02_b0.py,   "py_pi02_b0/D");
//  TEvent->Branch("pz_pi02_b0",  &bEvt.pi02_b0.pz,   "pz_pi02_b0/D");
//  TEvent->Branch("eg1_pi02_b0", &bEvt.pi02_b0.eg1,  "eg1_pi02_b0/D");
//  TEvent->Branch("eg2_pi02_b0", &bEvt.pi02_b0.eg2,  "eg2_pi02_b0/D");
//  TEvent->Branch("chi2_pi02_b0",&bEvt.pi02_b0.chisq,"chi2_pi02_b0/D");

  TEvent->Branch("mdpip",&bEvt.mdpip,"mdpip/D");
  TEvent->Branch("mdpim",&bEvt.mdpim,"mdpim/D");
  TEvent->Branch("mpipi",&bEvt.mpipi,"mpipi/D");

  TEvent->Branch("mdpip_raw",&bEvt.mdpip_raw,"mdpip_raw/D");
  TEvent->Branch("mdpim_raw",&bEvt.mdpim_raw,"mdpim_raw/D");
  TEvent->Branch("mpipi_raw",&bEvt.mpipi_raw,"mpipi_raw/D");

  TEvent->Branch("cos_hel_dpip",&bEvt.cos_hel_dpip,"cos_hel_dpip/D");
  TEvent->Branch("cos_hel_dpim",&bEvt.cos_hel_dpim,"cos_hel_dpim/D");
  TEvent->Branch("cos_hel_pipi",&bEvt.cos_hel_pipi,"cos_hel_pipi/D");

  TEvent->Branch("cos_hel_dpip_raw",&bEvt.cos_hel_dpip_raw,"cos_hel_dpip_raw/D");
  TEvent->Branch("cos_hel_dpim_raw",&bEvt.cos_hel_dpim_raw,"cos_hel_dpim_raw/D");
  TEvent->Branch("cos_hel_pipi_raw",&bEvt.cos_hel_pipi_raw,"cos_hel_pipi_raw/D");

  TEvent->Branch("ipx",&bEvt.ipx,"ipx/D");
  TEvent->Branch("ipy",&bEvt.ipy,"ipy/D");
  TEvent->Branch("ipz",&bEvt.ipz,"ipz/D");

  TEvent->Branch("boostx",&bEvt.boostx,"boostx/D");
  TEvent->Branch("boosty",&bEvt.boosty,"boosty/D");
  TEvent->Branch("boostz",&bEvt.boostz,"boostz/D");

  TEvent->Branch("tag_LH",&bEvt.tag_LH,"tag_LH/D");
  TEvent->Branch("tag_LH_err",&bEvt.tag_LH_err,"tag_LH_err/D");
  TEvent->Branch("tagl",&bEvt.tagl,"tagl/I");
  TEvent->Branch("taglid",&bEvt.taglid,"taglid/I");

  TEvent->Branch("cos_thr",&bEvt.cos_thr,"cos_thr/D");
  TEvent->Branch("thr_sig",&bEvt.thr_sig,"thr_sig/D");
  TEvent->Branch("thr_oth",&bEvt.thr_oth,"thr_oth/D");

  TEvent->Branch("k0mm2",&bEvt.k0.kmm2,"k0mm2/D");
  TEvent->Branch("k0et",&bEvt.k0.ket,"k0et/D");
  TEvent->Branch("k0hso00",&bEvt.k0.khso00,"k0hso00/D");
  TEvent->Branch("k0hso01",&bEvt.k0.khso01,"k0hso01/D");
  TEvent->Branch("k0hso02",&bEvt.k0.khso02,"k0hso02/D");
  TEvent->Branch("k0hso03",&bEvt.k0.khso03,"k0hso03/D");
  TEvent->Branch("k0hso04",&bEvt.k0.khso04,"k0hso04/D");
  TEvent->Branch("k0hso10",&bEvt.k0.khso10,"k0hso10/D");
  TEvent->Branch("k0hso12",&bEvt.k0.khso12,"k0hso12/D");
  TEvent->Branch("k0hso14",&bEvt.k0.khso14,"k0hso14/D");
  TEvent->Branch("k0hso20",&bEvt.k0.khso20,"k0hso20/D");
  TEvent->Branch("k0hso22",&bEvt.k0.khso22,"k0hso22/D");
  TEvent->Branch("k0hso24",&bEvt.k0.khso24,"k0hso24/D");
  TEvent->Branch("k0hoo0",&bEvt.k0.khoo0,"k0hoo0/D");
  TEvent->Branch("k0hoo1",&bEvt.k0.khoo1,"k0hoo1/D");
  TEvent->Branch("k0hoo2",&bEvt.k0.khoo2,"k0hoo2/D");
  TEvent->Branch("k0hoo3",&bEvt.k0.khoo3,"k0hoo3/D");
  TEvent->Branch("k0hoo4",&bEvt.k0.khoo4,"k0hoo4/D");

  TEvent->Branch("k1mm2",&bEvt.k1.kmm2,"k1mm2/D");
  TEvent->Branch("k1et",&bEvt.k1.ket,"k1et/D");
  TEvent->Branch("k1hso00",&bEvt.k1.khso00,"k1hso00/D");
  TEvent->Branch("k1hso01",&bEvt.k1.khso01,"k1hso01/D");
  TEvent->Branch("k1hso02",&bEvt.k1.khso02,"k1hso02/D");
  TEvent->Branch("k1hso03",&bEvt.k1.khso03,"k1hso03/D");
  TEvent->Branch("k1hso04",&bEvt.k1.khso04,"k1hso04/D");
  TEvent->Branch("k1hso10",&bEvt.k1.khso10,"k1hso10/D");
  TEvent->Branch("k1hso12",&bEvt.k1.khso12,"k1hso12/D");
  TEvent->Branch("k1hso14",&bEvt.k1.khso14,"k1hso14/D");
  TEvent->Branch("k1hso20",&bEvt.k1.khso20,"k1hso20/D");
  TEvent->Branch("k1hso22",&bEvt.k1.khso22,"k1hso22/D");
  TEvent->Branch("k1hso24",&bEvt.k1.khso24,"k1hso24/D");
  TEvent->Branch("k1hoo0",&bEvt.k1.khoo0,"k1hoo0/D");
  TEvent->Branch("k1hoo1",&bEvt.k1.khoo1,"k1hoo1/D");
  TEvent->Branch("k1hoo2",&bEvt.k1.khoo2,"k1hoo2/D");
  TEvent->Branch("k1hoo3",&bEvt.k1.khoo3,"k1hoo3/D");
  TEvent->Branch("k1hoo4",&bEvt.k1.khoo4,"k1hoo4/D");

  if(mode == 1){// Signal MC
    TEvent->Branch("mp_mc",&MCSigEvt.mp_mc,"mp_mc/D");
    TEvent->Branch("mm_mc",&MCSigEvt.mm_mc,"mm_mc/D");
    TEvent->Branch("z_sig_mc",&MCSigEvt.z_sig_mc,"z_sig_mc/D");
    TEvent->Branch("z_asc_mc",&MCSigEvt.z_asc_mc,"z_asc_mc/D");
    TEvent->Branch("z_upsilon",&MCSigEvt.z_upsilon,"z_upsilon/D");

    TEvent->Branch("flv_mc",&MCSigEvt.flv_mc,"flv_mc/I");
    TEvent->Branch("flv_d0_mc",&MCSigEvt.flv_d0_mc,"flv_d0_mc/I");

    TEvent->Branch("mdpip_mc",&MCSigEvt.mdpip_mc,"mdpip_mc/D");
    TEvent->Branch("mdpim_mc",&MCSigEvt.mdpim_mc,"mdpim_mc/D");
    TEvent->Branch("mpipi_mc",&MCSigEvt.mpipi_mc,"mpipi_mc/D");

    TEvent->Branch("cos_hel_dpip_mc",&MCSigEvt.cos_hel_dpip_mc,"cos_hel_dpip_mc/D");
    TEvent->Branch("cos_hel_dpim_mc",&MCSigEvt.cos_hel_dpim_mc,"cos_hel_dpim_mc/D");
    TEvent->Branch("cos_hel_pipi_mc",&MCSigEvt.cos_hel_pipi_mc,"cos_hel_pipi_mc/D");
  }
  if(mode == 2 || mode == 1){
//    TEvent->Branch("hp_d0_chain",MCGenEvt.hp_d0_chain[9],"hp_d0_chain/I");
//    TEvent->Branch("hm_d0_chain",MCGenEvt.hm_d0_chain[9],"hm_d0_chain/I");
//    TEvent->Branch("pi0_chain",MCGenEvt.pi0_chain[9],"pi0_chain/I");
//    TEvent->Branch("k0s_chain",MCGenEvt.k0s_chain[9],"k0s_chain/I");
//    TEvent->Branch("hp_h0_chain",MCGenEvt.hp_h0_chain[9],"hp_h0_chain/I");
//    TEvent->Branch("hm_h0_chain",MCGenEvt.hm_h0_chain[9],"hm_h0_chain/I");
    TEvent->Branch("pip_chain",MCGenEvt.pip_chain,"pip_chain[9]/I");
    TEvent->Branch("pim_chain",MCGenEvt.pim_chain,"pim_chain[9]/I");
    TEvent->Branch("d0_chain",MCGenEvt.d0_chain,"d0_chain[9]/I");

    TEvent->Branch("b0id",&MCGenEvt.b0id,"b0id/I");
    TEvent->Branch("b0f",&MCGenEvt.b0f,"b0f/I");
    TEvent->Branch("d0id",&MCGenEvt.d0id,"d0id/I");
    TEvent->Branch("d0f",&MCGenEvt.d0f,"d0f/I");
//    TEvent->Branch("ksid",&MCGenEvt.ksid,"ksid/I");
//    TEvent->Branch("ksf",&MCGenEvt.ksf,"ksf/I");
//    TEvent->Branch("h0id",&MCGenEvt.h0id,"h0id/I");
//    TEvent->Branch("h0f",&MCGenEvt.h0f,"h0f/I");
//    TEvent->Branch("pi0id",&MCGenEvt.pi0id,"pi0id/I");
//    TEvent->Branch("pi0f",&MCGenEvt.pi0f,"pi0f/I");

//    TEvent->Branch("nptag",&MCSigEvt.nptag,"nptag/I");

    TEvent->Branch("ngen",&MCGenEvt.ngen,"ngen/I");
    TEvent->Branch("gen_idhep",MCGenEvt.idhep,"gen_idhep[ngen]/I");
    TEvent->Branch("gen_daF",MCGenEvt.daF,"gen_daF[ngen]/I");
    TEvent->Branch("gen_daL",MCGenEvt.daL,"gen_daL[ngen]/I");
    TEvent->Branch("gen_mo",MCGenEvt.mo,"gen_mo[ngen]/I");
  }
  return TEvent;
}

void ClearSigMC(void){
  MCSigEvt.mp_mc = -99.;
  MCSigEvt.mm_mc = -99.;
  MCSigEvt.z_sig_mc  = -99.;
  MCSigEvt.z_asc_mc  = -99.;
  MCSigEvt.z_upsilon = -99.;
  MCSigEvt.flv_mc    = -2;
  MCSigEvt.flv_d0_mc = -2;
  MCSigEvt.mdpip_mc  = -99.;
  MCSigEvt.mdpim_mc  = -99.;
  MCSigEvt.mpipi_mc  = -99.;
  MCSigEvt.cos_hel_dpip_mc = -2.;
  MCSigEvt.cos_hel_dpim_mc = -2.;
  MCSigEvt.cos_hel_pipi_mc = -2.;
}

void ClearTrk(TrkInfo& trk){
  trk.px = -99, trk.py = -99, trk.pz = -99;   // Momentum
  trk.r  = -99, trk.z = -99;         // Impact parameters
  trk.rz_svd = -1, trk.rphi_svd = -1;// SVD hits
  trk.atckpi = -2;       // Identification
  trk.atckp  = -2;
  trk.eid    = -2;
  trk.muid   = -2;
}

void ClearKs0(Ks0Info& ks0){
  ks0.m = 0, ks0.m_raw = 0;
  ks0.px = -99, ks0.py = -99, ks0.pz = -99;
  ks0.dr = -99, ks0.dz = -99, ks0.dphi = -99, ks0.fl = -99;
}

void ClearPi0(pi0Info& pi0){
  pi0.m = 0, pi0.m_raw = 0;
  pi0.px = -99, pi0.py = -99, pi0.pz = -99;
  pi0.eg1 = -99, pi0.eg2 = -99;
  pi0.chisq = -1;
}

void ClearBEvt(bEvnt& bev){
  bev.mp = 0, bev.mm = 0; //
  bev.mp_raw = 0, bev.mm_raw = 0; //

  bev.md0 = 0, bev.md0_raw = 0; //
  bev.chi2_mass_d0 = -1;
  bev.chi2_vtx_d0 = -1;
  bev.chi2_mass_b0 = -1;

//  ClearTrk(bev.pip_ks);
//  ClearTrk(bev.pim_ks);
  ClearTrk(bev.pip_b0);
  ClearTrk(bev.pim_b0);

  bev.px_h0, bev.py_h0, bev.pz_h0;
  ClearTrk(bev.hp_d0);
  ClearTrk(bev.hm_d0);
//  ClearTrk(bev.hp2_d0);
//  ClearTrk(bev.hm2_d0);
  ClearTrk(bev.hp_h0);
  ClearTrk(bev.hm_h0);

  bev.flv_d0 = 0, bev.mode_d0 = -99, bev.mode_h0 = -99, bev.mode = -99;

  ClearKs0(bev.ks);
  ClearPi0(bev.pi0);
//  ClearPi0(bev.pi01_b0);
//  ClearPi0(bev.pi02_b0);

  bev.mdpip = 0, bev.mdpim = 0, bev.mpipi = 0;
  bev.cos_hel_dpip = -2, bev.cos_hel_dpim = -2, bev.cos_hel_pipi = -2;

  bev.mdpip_raw = 0, bev.mdpim_raw = 0, bev.mpipi_raw = 0;
  bev.cos_hel_dpip_raw = -2, bev.cos_hel_dpim_raw = -2, bev.cos_hel_pipi_raw = -2;

  bev.chi2_vtx_h0 = 0; // light pseudoscalar meson
  bev.chi2_mass_h0 = 0;
  bev.cos_hel_h0 = 0;
  bev.mh0 = 0, bev.mh0_raw = 0;

  ClearSigMC();
}

int mc_list(vector<Gen_hepevt>& mcl){
  mcl.clear();
  Gen_hepevt_Manager &mGHep = Gen_hepevt_Manager::get_manager();
  for(std::vector<Gen_hepevt>::iterator i = mGHep.begin();i != mGHep.end();i++){
    Gen_hepevt tmp = *i;
    mcl.push_back(tmp);
  }
  return mcl.size();
}
//////////////////////////////////////////////////////////////////////
//                      Fill Signal MC Event                        //
//////////////////////////////////////////////////////////////////////

int FillMCSigEvt(const Particle& _b0, const vector<Gen_hepevt>& mcl){
  const Gen_hepevt& b0 = const_cast<Gen_hepevt&>(_b0.relation().genHepevt());
  if(!b0) return -1;
  const Gen_hepevt& d0 = RTools::mc_child(b0,mcl,421,true);
  if(d0 == b0) return -2;
  const Gen_hepevt& pp = RTools::mc_child(b0,mcl,211,false);
  if(pp == b0) return -3;
  const Gen_hepevt& pm = RTools::mc_child(b0,mcl,-211,false);
  if(pm == b0) return -3;

  const HepLorentzVector b0lv = RTools::mc_lmom(b0);
  const HepLorentzVector d0lv = RTools::mc_lmom(d0);
  const HepLorentzVector pplv = RTools::mc_lmom(pp);
  const HepLorentzVector pmlv = RTools::mc_lmom(pm);

  MCSigEvt.cos_hel_dpip_mc = RTools::ResonanceHelicity(b0lv,d0lv,pplv,MCSigEvt.mdpip_mc);
  MCSigEvt.cos_hel_dpim_mc = RTools::ResonanceHelicity(b0lv,d0lv,pmlv,MCSigEvt.mdpim_mc);
  MCSigEvt.cos_hel_pipi_mc = RTools::ResonanceHelicity(b0lv,pplv,pmlv,MCSigEvt.mpipi_mc);
  MCSigEvt.flv_mc = b0.idhep() == -511 ? -1 : 1;

  RTools::GetTrueVertices(b0,mcl,MCSigEvt.z_sig_mc,MCSigEvt.z_asc_mc,MCSigEvt.z_upsilon);
  return 0;
}

// Fill D0 -> Ks0 pi+pi- generator information
int FillMCSigEvtMode0(const Particle& _d0, const vector<Gen_hepevt>& mcl){
  const Gen_hepevt& d0 = const_cast<Gen_hepevt&>(_d0.relation().genHepevt());
  if(!d0) return -1;
  const Gen_hepevt& ks = RTools::mc_child(d0,mcl,310,true);
  if(ks == d0) return -2;
  const Gen_hepevt& pp = RTools::mc_child(d0,mcl,211,false);
  if(pp == d0) return -3;
  const Gen_hepevt& pm = RTools::mc_child(d0,mcl,-211,false);
  if(pm == d0) return -3;

  const HepLorentzVector d0lv = RTools::mc_lmom(d0);
  const HepLorentzVector kslv = RTools::mc_lmom(ks);
  const HepLorentzVector pplv = RTools::mc_lmom(pp);
  const HepLorentzVector pmlv = RTools::mc_lmom(pm);

  RTools::ResonanceHelicity(d0lv,kslv,pplv,MCSigEvt.mp_mc);
  RTools::ResonanceHelicity(d0lv,kslv,pmlv,MCSigEvt.mm_mc);
  MCSigEvt.flv_d0_mc = d0.idhep() == -421 ? -1 : 1;

  return 0;
//  BDecayTime_MC(b0,MCSigEvt.t_sig_mc,MCSigEvt.t_asc_mc,MCSigEvt.z_sig_mc,MCSigEvt.z_asc_mc,MCSigEvt.z_upsilon,zups);

//  MCSigEvt.nptag     = NPTag(_b0);
  return 0;
}

/////////////////////////////////////////////////////////////////////
//                     Fill Generic MC Event                       //
/////////////////////////////////////////////////////////////////////
int FillMCGenEvt(Particle& b0){
  setMCtruth(b0);

  Particle& pip = const_cast<Particle&>(b0.child(1));
  Particle& pim = const_cast<Particle&>(b0.child(2));
  Particle& d0  = const_cast<Particle&>(b0.child(0));
//  Particle& pip = const_cast<Particle&>(d0.child(1));
//  Particle& pim = const_cast<Particle&>(d0.child(2));
//  Particle& k0s = const_cast<Particle&>(d0.child(0));

  genDecayChain(pip,MCGenEvt.pip_chain);
  genDecayChain(pim,MCGenEvt.pim_chain);
  genDecayChain(d0,MCGenEvt.d0_chain);
//  genDecayChain(pip,MCGenEvt.pip_chain);
//  genDecayChain(pim,MCGenEvt.pim_chain);
//  genDecayChain(k0s,MCGenEvt.k0s_chain);

//  MCGenEvt.ksid = IDhep(k0s);
//  MCGenEvt.ksf  = getMCtruthFlag(k0s);
  MCGenEvt.d0id = IDhep(d0);
  MCGenEvt.d0f  = getMCtruthFlag(d0);
  MCGenEvt.b0id = IDhep(b0);
  MCGenEvt.b0f  = getMCtruthFlag(b0);

  vector<Gen_hepevt> mcl;
  mc_list(mcl);
  MCGenEvt.ngen = mcl.size();
  for(int i=0; i<MCGenEvt.ngen; i++){
    MCGenEvt.idhep[i] = mcl[i].idhep();
    MCGenEvt.daF[i]   = mcl[i].daFirst();
    MCGenEvt.daL[i]   = mcl[i].daLast();
    MCGenEvt.mo[i]    = mcl[i].mother();
  }

  if(MCGenEvt.b0f == 1 || MCGenEvt.b0f == 5 || MCGenEvt.b0f == 10) FillMCSigEvt(b0,mcl);
  const D0UserInfo& dinfo = (D0UserInfo&)d0.userInfo();
  if(dinfo.Mode() == 0 && (MCGenEvt.d0f == 1 || MCGenEvt.d0f == 5 || MCGenEvt.d0f == 10)) FillMCSigEvtMode0(d0,mcl);

  return 0;
}

//////////////////////////////////////////////////////////////////////
//                          Fill B Event                            //
//////////////////////////////////////////////////////////////////////
void FillTrk(const Particle& trk,TrkInfo& info){
  info.px = trk.p().x();
  info.py = trk.p().y();
  info.pz = trk.p().z();
  const TrkUserInfo& trkinfo = (TrkUserInfo&)trk.userInfo();
  info.z        = trkinfo.z();
  info.r        = trkinfo.r();
  info.rz_svd   = trkinfo.rz_svd_hits();
  info.rphi_svd = trkinfo.rphi_svd_hits();
  info.atckpi   = trkinfo.atckpi();
  info.atckp    = trkinfo.atckp();
  info.eid      = trkinfo.eid();
  info.muid     = trkinfo.muid();
}

void FillBVtx(const B0UserInfo& binfo,VtxInfo& recvtx,VtxInfo& ascvtx,const HepPoint3D& IP){
  recvtx.z     = binfo.ZSig()-IP.z();
  ascvtx.z     = binfo.ZAsc()-IP.z();
  recvtx.sz    = binfo.SzSig();
  ascvtx.sz    = binfo.SzAsc();
  recvtx.ntrk  = binfo.NtrkSig();
  ascvtx.ntrk  = binfo.NtrkAsc();
  recvtx.ndf   = binfo.NdfSig();
  ascvtx.ndf   = binfo.NdfAsc();
  recvtx.chisq = binfo.ChisqSig();
  ascvtx.chisq = binfo.ChisqAsc();
}

void FillKSFW(ksfwmoments& km,sfwmInfo& info,const int usefs){
  km.usefinal(usefs);
  info.kmm2   = km.mm2();
  info.ket    = km.et();
  info.khso00 = km.Hso(0,0);
  info.khso01 = km.Hso(0,1);
  info.khso02 = km.Hso(0,2);
  info.khso03 = km.Hso(0,3);
  info.khso04 = km.Hso(0,4);
  info.khso10 = km.Hso(1,0);
  info.khso12 = km.Hso(1,2);
  info.khso14 = km.Hso(1,4);
  info.khso20 = km.Hso(2,0);
  info.khso22 = km.Hso(2,2);
  info.khso24 = km.Hso(2,4);
  info.khoo0  = km.Hoo(0);
  info.khoo1  = km.Hoo(1);
  info.khoo2  = km.Hoo(2);
  info.khoo3  = km.Hoo(3);
  info.khoo4  = km.Hoo(4);
}

void FillKs0(const Particle& ks,Ks0Info& info){
  info.m     = ks.p().m();
  info.px    = ks.p().x();
  info.py    = ks.p().y();
  info.pz    = ks.p().z();
  const KsUserInfo& ksinfo = (KsUserInfo&)ks.userInfo();
  info.dr    = ksinfo.dr();
  info.dz    = ksinfo.dz();
  info.dphi  = ksinfo.dphi();
  info.fl    = ksinfo.fl();
  info.m_raw = ksinfo.Mass();
}

void FillPi0(const Particle& pi0, Pi0Info& info){
  info.m     = pi0.p().m();
  info.px    = pi0.p().x();
  info.py    = pi0.p().y();
  info.pz    = pi0.p().z();
  info.eg1   = pi0.child(0).p().t();
  info.eg2   = pi0.child(1).p().t();
  const Pi0UserInfo& pi0info = (Pi0UserInfo&)pi0.userInfo();
  info.m_raw = pi0info.Mass();
  info.chisq = pi0info.Chi2();
}

int FillBEvent(Particle& b0,const bool mc){
  ClearBEvt(bEvt);
  Belle_event_Manager& evtmgr = Belle_event_Manager::get_manager();
  Belle_event& evthead = *evtmgr.begin();
  bEvt.exp = evthead.ExpNo();
  bEvt.run = evthead.RunNo();
  bEvt.evtn = (evthead.EvtNo() & 0xfffffff);

  B0UserInfo& binfo = (B0UserInfo&)b0.userInfo();
  bEvt.mbc  = binfo.Mbc();
  bEvt.de   = binfo.deltaE();
  bEvt.mode = binfo.Mode();
  switch(binfo.Mode()){
  case 1:// B0 -> D0 pi+ pi-
    FillTrk(b0.child(1),bEvt.pip_b0);
    FillTrk(b0.child(2),bEvt.pim_b0);
    break;
  case 2:// B0 -> D0 pi0 pi0
    FillPi0(b0.child(1),bEvt.pi01_b0);
    FillPi0(b0.child(2),bEvt.pi02_b0);
    break;
  }

  bEvt.costhBcms = RTools::cosThetaCMS(b0);
  const HepPoint3D IP = IpProfile::usable() ? IpProfile::e_position() : HepPoint3D(0);
  FillBVtx(binfo,bEvt.recvtx,bEvt.ascvtx,IP);

  bEvt.cos_hel_dpip = binfo.CosHel12();
  bEvt.cos_hel_dpim = binfo.CosHel13();
  bEvt.cos_hel_pipi = binfo.CosHel23();

  bEvt.mdpip = binfo.Mass12();
  bEvt.mdpim = binfo.Mass13();
  bEvt.mpipi = binfo.Mass23();

  bEvt.cos_hel_dpip_raw = binfo.RawCosHel12();
  bEvt.cos_hel_dpim_raw = binfo.RawCosHel13();
  bEvt.cos_hel_pipi_raw = binfo.RawCosHel23();

  bEvt.mdpip_raw = binfo.RawMass12();
  bEvt.mdpim_raw = binfo.RawMass13();
  bEvt.mpipi_raw = binfo.RawMass23();

  bEvt.chi2_mass_b0 = binfo.MassChi2();

  bEvt.ipx = IP.x(); bEvt.ipy = IP.y(); bEvt.ipz = IP.z();
  bEvt.boostx = -BeamEnergy::CMBoost().x();
  bEvt.boosty = -BeamEnergy::CMBoost().y();
  bEvt.boostz = -BeamEnergy::CMBoost().z();

  RTools::make_MDLH_b0_tag(b0);
  bEvt.tag_LH     = binfo.fqLH();
  bEvt.tag_LH_err = binfo.fqErrLH();
  bEvt.tagl       = binfo.tagl();
  bEvt.taglid     = binfo.taglid();
 
  bEvt.cos_thr = RTools::CosThr(b0,bEvt.thr_sig,bEvt.thr_oth);

  ksfwmoments km(b0,BeamEnergy::E_beam_corr(),-BeamEnergy::CMBoost());//BeamEnergy::Ecm()/2.
  FillKSFW(km,bEvt.k0,0);
  FillKSFW(km,bEvt.k1,1);

  int d0index = 0;
  if(abs(b0.child(0).lund()) == 421) d0index = 0;
  else if(abs(b0.child(1).lund()) == 421) d0index = 1;
  else if(abs(b0.child(2).lund()) == 421) d0index = 2;
  else return -1;
  const Particle& d0 = b0.child(d0index);
  bEvt.md0 = d0.p().m();
  const D0UserInfo& dinfo = (D0UserInfo&)d0.userInfo();
  bEvt.mode_d0      = dinfo.Mode();
  bEvt.md0_raw      = dinfo.Mass();
  bEvt.chi2_vtx_d0  = dinfo.VtxChi2();
  bEvt.chi2_mass_d0 = dinfo.MassChi2();

  switch(dinfo.Mode()){
  case 0:// Ks0 pi+ pi-
    RTools::KspipiDalitzVars(d0,bEvt.mp,bEvt.mm);
    FillKs0(d0.child(0),bEvt.ks);
    FillTrk(d0.child(1),bEvt.hp_d0);
    FillTrk(d0.child(2),bEvt.hm_d0);
    bEvt.flv_d0 = 0;
    break;
  case 10:// K- pi+
    if(d0.child(0).pType().charge()>0){
      FillTrk(d0.child(0),bEvt.hp_d0);
      FillTrk(d0.child(1),bEvt.hm_d0);
      bEvt.flv_d0 = -1;
    } else{
      FillTrk(d0.child(0),bEvt.hm_d0);
      FillTrk(d0.child(1),bEvt.hp_d0);
      bEvt.flv_d0 = 1;
    }
    break;
  case 11:// K- pi+ pi0
    if(d0.child(0).pType().charge()>0){
      FillTrk(d0.child(0),bEvt.hp_d0);
      FillTrk(d0.child(1),bEvt.hm_d0);
      bEvt.flv_d0 = -1;
    } else{
      FillTrk(d0.child(0),bEvt.hm_d0);
      FillTrk(d0.child(1),bEvt.hp_d0);
      bEvt.flv_d0 = 1;
    }
    FillPi0(d0.child(2),bEvt.pi0);
    break;
  case 12:// K- pi+ pi- pi+
    if(d0.child(0).pType().charge()>0){
      FillTrk(d0.child(0),bEvt.hp_d0);
      FillTrk(d0.child(1),bEvt.hm_d0);
      FillTrk(d0.child(2),bEvt.hp2_d0);
      FillTrk(d0.child(3),bEvt.hm2_d0);
      bEvt.flv_d0 = -1;
    } else{
      FillTrk(d0.child(0),bEvt.hm_d0);
      FillTrk(d0.child(1),bEvt.hp_d0);
      FillTrk(d0.child(2),bEvt.hm2_d0);
      FillTrk(d0.child(3),bEvt.hp2_d0);
      bEvt.flv_d0 = 1;
    }
    break;
  case 20:// K+ K-
    bEvt.flv_d0 = 0;
    FillTrk(d0.child(0),bEvt.hp_d0);
    FillTrk(d0.child(1),bEvt.hm_d0);
    break;
  case 21:// pi+ pi-
    bEvt.flv_d0 = 0;
    FillTrk(d0.child(0),bEvt.hp_d0);
    FillTrk(d0.child(1),bEvt.hm_d0);
    break;
  case 22:// Ks0 pi0
    bEvt.flv_d0 = 0;
    FillKs0(d0.child(0),bEvt.ks);
    FillPi0(d0.child(1),bEvt.pi0);
    break;
  case 23:// Ks0 eta
    bEvt.mh0_raw = ((const EtaUserInfo&)d0.child(1).userInfo()).Mass();
    bEvt.flv_d0 = 0;
    FillKs0(d0.child(0),bEvt.ks);
    bEvt.mh0 = d0.child(1).p().m();
    bEvt.px_h0 = d0.child(1).p().x();
    bEvt.py_h0 = d0.child(1).p().y();
    bEvt.pz_h0 = d0.child(1).p().z();
    if(d0.child(1).nChildren() == 2){
      bEvt.mode_h0 = 10;
    } else{
      bEvt.mode_h0 = 20;
      FillTrk(d0.child(1).child(0),bEvt.hp_h0);
      FillTrk(d0.child(1).child(1),bEvt.hm_h0);
      FillPi0(d0.child(1).child(2),bEvt.pi0);
    }
    break;
  case 24:// Ks0 omega
    bEvt.mh0_raw = ((const EtaUserInfo&)d0.child(1).userInfo()).Mass();
    bEvt.flv_d0 = 0;
    FillKs0(d0.child(0),bEvt.ks);
    bEvt.mh0 = d0.child(1).p().m();
    bEvt.px_h0 = d0.child(1).p().x();
    bEvt.py_h0 = d0.child(1).p().y();
    bEvt.pz_h0 = d0.child(1).p().z();
    FillTrk(d0.child(1).child(0),bEvt.hp_h0);
    FillTrk(d0.child(1).child(1),bEvt.hm_h0);
    FillPi0(d0.child(1).child(2),bEvt.pi0);
    break;
  case 25:// Ks0 phi
    bEvt.mh0_raw = ((const EtaUserInfo&)d0.child(1).userInfo()).Mass();
    bEvt.flv_d0 = 0;
    FillKs0(d0.child(0),bEvt.ks);
    bEvt.mh0 = d0.child(1).p().m();
    bEvt.px_h0 = d0.child(1).p().x();
    bEvt.py_h0 = d0.child(1).p().y();
    bEvt.pz_h0 = d0.child(1).p().z();
    FillTrk(d0.child(1).child(0),bEvt.hp_h0);
    FillTrk(d0.child(1).child(1),bEvt.hm_h0);
    break;
  }

  if(mc) FillMCGenEvt(b0);
  return 0;
}

#if defined(BELLE_NAMESPACE)
}
#endif

