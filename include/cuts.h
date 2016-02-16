
const bool fullfit = false;
const bool const_back_flag = false;
const bool flag41 = false;

const double de_fit_min = -0.15;
const double de_fit_max = 0.3;

const double de_min = -0.08;
const double de_max = 0.07;

const double de_min_etappp = -0.05;
const double de_max_etappp =  0.04;

const double de_min_omega = -0.06;
const double de_max_omega =  0.05;

const double mbc_min = 5.272;
const double mbc_max = 5.286;
const double mbc_side = 5.25;

const double DMass = 1.865;
const double md_cut = 0.013;

const double KMass = 0.4975;
const double mk_cut = 0.009;

const double Pi0Mass = 0.135;
const double mpi0_cut = 0.012;

const double EtaMass = 0.547862;
const double meta_cut = 0.02;

const double OmegaMass = 0.78265;
const double momega_cut = 0.02;

const double atckpi_cut = 1.;

double bdt_cut = 0.32;
double bdtgs_cut = 0.916515;//0.98;
double bdtgfr_cut = 0.2168;
double bdtgsl_cut = 0.821645;
double bdtgmbcs_cut = 0.759934;
double bdtgdes_cut = 0.6;
double lh_cut = 0.814616;
double lh1_cut = 0.742361;

// Signal shape
const bool cSig = true;
const bool cSIG = true;
// mbc
const double m_mbc0 = 5.28291e+00;
const double m_mbc00 = 5.27979e+00;
const double m_sl = 6.28487e-03;
const double m_sll = 2.96898e-03;
const double m_sr = 1.92172e-03;
const double m_srr = 2.17430e-03;
const double m_fmbc = 2.80705e-01;

// de
const double m_alphal = 3.85675e-01;
const double m_alphar = -1.56269e+00;
const double m_de0 = 1.51293e-02;
const double m_deCBl = -2.58588e-02;
const double m_deCBr = -1.22991e-02;
const double m_fCBl = 4.62725e-01;
const double m_fCBr = 2.11382e-01;
const double m_nl = 1.71068e+01;
const double m_nr = 3.79904e+00;
const double m_s1 = 2.24893e-02;
const double m_sCBl = 2.71645e-02;
const double m_sCBr = 3.97215e-02;

// Rho shape
const bool keysflag = false;
const bool cRho = true;
const bool cRHO = false;
// mbc
const int mbc_rho_param = 0;
const double mr_mbc0_0 = 5.28177e+00;
const double mr_sl_0 = 1.88012e-02;
const double mr_sr_0 = 3.21321e-03;
const double mr_cond_0 = 8.97366e-02;
const double mr_condr_0 = 8.40921e-03;

const double mr_mbc0_1 = 5.28064e+00;
const double mr_sl_1 = 2.76386e-02;
const double mr_sr_1 = 1.04874e-06;
const double mr_cond_1 = 0.006;
const double mr_mbc00_1 = 5.27999e+00;
const double mr_sll_1 = 6.24356e-03;
const double mr_srr_1 = 4.45965e-03;
const double mr_fmbc_1 = 5.04927e-02;

const double mr_mbc0_2 = 5.27878e+00;
const double mr_sr_2 = 3.80005e-03;
const double mr_mbc1_2 = 5.26645e+00;
const double mr_fcb_2 = 6.11183e-02;
const double mr_alpha_2 = -3.74609e+00;
const double mr_ss_2 = 1.15691e-02;
const double mr_n_2 = 0.48;

const double mr_argpar_3 = -9.53674e-05;
const double mr_argedge_3 = 5.28616e+00;
const double mr_mbc0_3 = 5.28440e+00;
const double mr_cond_3 = 3.97230e-02;
const double mr_condr_3 = 3.53054e-02;
const double mr_sl_3 = 1.21988e-02;
const double mr_sr_3 = 3.16735e-03;
//de
const int de_rho_param = 1;

const double mr_exppar = -3.37184e+01;

const double mr_de0r = -1.11131e-01;
const double mr_slopel = -7.03669e+02;
const double mr_sloper = -1.52863e+00;
const double mr_steep = 9.52444e+00;
const double mr_p5 = 9.39841e-01;

const double mr_x0 = -1.27853e-01;
const double mr_p1 = -2.80709e+02;
const double mr_p2 = 5.31945e+00;

const double mr_x0_1d = -1.21409e-01;
const double mr_p1_1d = -4.26629e+02;
const double mr_p2_1d = 7.27530e+00;

const double mr_x0_2 = -5.48334e-02;
const double mr_slopel_2 = 1.29144e+01;
const double mr_steep_2 = 2.47426e+03;
const double mr_exppar_2 = 4.38643e+01;

// Comb shape
const bool cComb = true;
// mbc
//const double mc_argpar = -2.37807e+01;
//const double mc_argedge = 5.28941e+00;
const double mc_argpar = -2.04306e+01;
const double mc_argedge = 5.28941e+00;

// de
//const double mc_c1 = -4.57562e-01;
//const double mc_c2 = 6.94555e-02;
const double mc_c1 = -4.55023e-01;
const double mc_c2 = 6.71316e-02;

const double mc_c1_1d = -5.39318e-01;
const double mc_c2_1d = 9.53054e-02;

// RooKSFW pre cuts
const double k0mm2_min = -20.5;
const double k0mm2_max = 22.;

const double k0et_min = 2.8;
const double k0et_max = 12.;

const double k0hso00_min = 0.;
const double k0hso00_max = 1.3;

const double k0hso02_min = -0.5;
const double k0hso02_max = 0.75;

const double k0hso4_min = -0.35;
const double k0hso4_max = 0.6;

const double k0hso10_min = 0;
const double k0hso10_max = 1.;

const double k0hso12_min = -0.35;
const double k0hso12_max = 0.6;

const double k0hso14_min = -0.3;
const double k0hso14_max = 0.45;

const double k0hso20_min = 0.;
const double k0hso20_max = 0.75;

const double k0hso22_min = -0.3;
const double k0hso22_max = 0.6;

const double k0hso24_min = -0.3;
const double k0hso24_max = 0.5;

const double k0hoo0_min = 0.;
const double k0hoo0_max = 0.5;

const double k0hoo1_min = -0.05;
const double k0hoo1_max = 0.07;

const double k0hoo2_min = -0.03;
const double k0hoo2_max = 0.02;

const double k0hoo3_min = -0.04;
const double k0hoo3_max = 0.05;

const double k0hoo4_min = -0.035;
const double k0hoo4_max = 0.150;

const double k1mm2_min = -20.5;
const double k1mm2_max = 22.;

const double k1et_min = 3.7;
const double k1et_max = 13.;

const double k1hso00_min = 0.;
const double k1hso00_max = 3.8;

const double k1hso01_min = -0.8;
const double k1hso01_max = 0.8;

const double k1hso02_min = -1.;
const double k1hso02_max = 1.6;

const double k0hso4_min = -0.75;
const double k0hso4_max = 1.;

const double k1hso10_min = 0;
const double k1hso10_max = 3.;

const double k1hso12_min = -0.75;
const double k1hso12_max = 1.;

const double k1hso14_min = -0.5;
const double k1hso14_max = 0.7;

const double k1hso20_min = 0.;
const double k1hso20_max = 2.3;

const double k1hso22_min = -0.7;
const double k1hso22_max = 1.2;

const double k1hso24_min = -0.6;
const double k1hso24_max = 0.9;

const double k1hoo0_min = 0.;
const double k1hoo0_max = 0.5;

const double k1hoo1_min = -0.05;
const double k1hoo1_max = 0.07;

const double k1hoo2_min = -0.03;
const double k1hoo2_max = 0.02;

const double k1hoo3_min = -0.04;
const double k1hoo3_max = 0.05;

const double k1hoo4_min = -0.035;
const double k1hoo4_max = 0.150;


