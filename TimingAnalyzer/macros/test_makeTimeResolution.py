import os
import sys

#skiminfile = (sys.argv[1:])[0]

inlist_dataset_egamma = [
'twotier_rm_w_ks_kscc_v4_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho_0000.root',
'twotier_rm_w_ks_kscc_v4_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho_0001.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0000.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0001.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0002.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0003.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0004.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0005.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0006.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0000.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0001.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0002.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0003.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0004.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0005.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0006.root'
]

inlist_dataset_double = [
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017F-31Mar2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017F-31Mar2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016H-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0003.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016H-17Jul2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0004.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016H-17Jul2018-v1_All_dispho_0003.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0002.root'
]

inlist_tree_94 = [
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016G-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016D-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017F-31Mar2018-v1_All_dispho_0002.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016D-17Jul2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017C-31Mar2018-v1_All_dispho_0002.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016F-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016G-17Jul2018-v1_All_dispho_0002.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016G-17Jul2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017B-31Mar2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016E-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016C-17Jul2018-v1_All_dispho_0000.root'
]

inlist_tree_10 = [
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0000.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0004.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0005.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0001.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0003.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0002.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0006.root',
]

inlist_dataset_egamma_woot = [
'twotier_rm_w_woot_ks_kscc_nolhc_v7_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho_0000.root',
'twotier_rm_w_woot_ks_kscc_nolhc_v7_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho_0001.root'
]

#skiminfile='ku_multitest_twotier_run18D_323414_dispho.root'
#skiminfile='ku_test_ks_1000_twotier_run18D_323414_dispho.root'
#skiminfile='dispho_raw_eg2018A_315322.root'
#skiminfile='ku_twotier_run18D_320712_dispho.root'
#skiminfile='output_235.root'
#skiminfile='ku_rhcomp_twotier_run18D_dispho.root'
#skiminfile='dispho_mini_eg2018A_315322.root'
#skiminfile='dispho_2t_eg2018B.root'
#skiminfile='dispho_tt_2018A.root'
#skiminfile='dispho_tt_2018B.root'
#skiminfile='dispho_tt_2018C.root'
#skiminfile='dispho_tt_2018D.root'
#skiminfile='dispho_tt_2018D_320673-320824.root'
#skiminlist='dispho_tt_2018D_320673-320824.txt'
#skiminfile='dispho_tt_2018A_315257-315488.root'
#skiminlist='dispho_tt_2018A_315257-315488.txt'
#skiminfile='dispho_2t_eg2018B_global.root'
#skiminfile='dispho_2t_eg2018B_local_icv2.root'
#skiminfile='dispho_2t_eg2018B_local.root'
#skiminfile='dispho_2t_eg2018B_notof.root'
#skiminfile='dispho_tt_2018D_320673-320824_mf.root'
#skiminfile='dispho_tt_2018pABCD_mf.root'
skiminfile='blank.root'
#preplotoutfile=skiminfile
#preplotoutfile='ku_multitest_twotier_run18D_323414_dispho_preplot.root'
#preplotoutfile='dispho_tt_2018B_preplot.root'
#preplotoutfile='dispho_tt_2018C_preplot.root'
#preplotoutfile='dispho_tt_2018D_preplot.root'
#preplotoutfile='dispho_2t_eg2018B_local_icv2_i25_e5e5_preplot.root'
#preplotoutfile='dispho_2t_eg2018D_global_icv2_i25_e5e3_preplot.root'
preplotoutfile='dispho_2t_eg2018D_local_globalic_i25_e5e3_preplot.root'
#preplotoutfile='dispho_2t_eg2018B_global_preplot.root'
#preplotoutfile='dispho_tt_eg2018B_global_ic_preplot.root'
#preplotoutfile='dispho_2t_eg2018B_local_preplot.root'
#preplotoutfile='dispho_tt_eg2018B_local_ic_preplot.root'
#preplotoutfile='dispho_2t_eg2018B_notof_preplot.root'
#preplotoutfile='dispho_2t_eg2018B_tof_preplot.root'
#preplotoutfile='dispho_2t_eg2018B_inter_preplot.root'

#caliinfile='dispho_2t_eg2018B_local_icv2_i25_e5e5.root'
#caliinfile='dispho_2t_eg2018D_global_e5_i25_e5e3.root'
#caliinfile='dispho_2t_eg2018D_global_i25_e5e3.root'
caliinfile='dispho_2t_2018pABCD_global_i25_e5e3.root'

cali1infile='dispho_2t_eg2018D_global_e5_i25_e5e3.root'
cali2infile='dispho_2t_eg2018D_global_i25_e5e3.root'
calioutfile='caliplots_2t_eg2018D_global_i25_e5e3.root'

infile=preplotoutfile
#infile=skiminfile

eta='EBEB'
era='Full'
res='Local'
#res='Global'

# Final output file
outfile=res+'_'+eta+'_'+era
kuoutfile='ku_'+outfile              
kuStcoutfile='kuStc_'+outfile
kuNotoutfile='kuNot_'+outfile
kuNotStcoutfile='kuNotStc_'+outfile

kuNotStc_e0_outfile='kuNotStc_e0_'+outfile
kuNotStc_e1_outfile='kuNotStc_e1_'+outfile
kuNotStc_2e1_outfile='kuNotStc_2e1_'+outfile
kuNotStc_4e1_outfile='kuNotStc_4e1_'+outfile
kuNotStc_e2_outfile='kuNotStc_e2_'+outfile
kuNotStc_e5_outfile='kuNotStc_e5_'+outfile
kuNotStc_2e5_outfile='kuNotStc_2e5_'+outfile
kuNotStc_4e5_outfile='kuNotStc_4e5_'+outfile
kuNotStc_e10_outfile='kuNotStc_e10_'+outfile
kuNotStc_cl_outfile='kuNotStc_cl_'+outfile
kuNotStc_ic_outfile='kuNotStc_ic_'+outfile

#kuStc_e0_outfile='kuStc_e0_'+outfile
#kuStc_e1_outfile='kuStc_e1_'+outfile
#kuStc_2e1_outfile='kuStc_2e1_'+outfile
#kuStc_4e1_outfile='kuStc_4e1_'+outfile
#kuStc_e2_outfile='kuStc_e2_'+outfile
kuStc_e5_outfile='kuStc_e5_'+outfile
#kuStc_2e5_outfile='kuStc_2e5_'+outfile
#kuStc_4e5_outfile='kuStc_4e5_'+outfile
#kuStc_e10_outfile='kuStc_e10_'+outfile
#kuStc_cl_outfile='kuStc_cl_'+outfile
#kuStc_ic_outfile='kuStc_ic_'+outfile

kuWootStc_e5_outfile='kuWootStc_e5_'+outfile

# 2D plotter output file
outfile_2D='deltaT_vs_'+outfile
outfile_ku_2D='ku_deltaT_vs_'+kuoutfile
outfile_kuStc_2D='kuStc_deltaT_vs_'+kuoutfile
outfile_kuNot_2D='kuNot_deltaT_vs_'+kuoutfile
outfile_kuNotStc_2D='kuNotStc_deltaT_vs_'+kuoutfile

outfile_kuNotStc_e0_2D='kuNotStc_e0_deltaT_vs_'+kuoutfile
outfile_kuNotStc_e1_2D='kuNotStc_e1_deltaT_vs_'+kuoutfile
outfile_kuNotStc_2e1_2D='kuNotStc_e1_deltaT_vs_'+kuoutfile
outfile_kuNotStc_4e1_2D='kuNotStc_e1_deltaT_vs_'+kuoutfile
outfile_kuNotStc_e2_2D='kuNotStc_e2_deltaT_vs_'+kuoutfile
outfile_kuNotStc_e5_2D='kuNotStc_e5_deltaT_vs_'+kuoutfile
outfile_kuNotStc_2e5_2D='kuNotStc_e5_deltaT_vs_'+kuoutfile
outfile_kuNotStc_4e5_2D='kuNotStc_e5_deltaT_vs_'+kuoutfile
outfile_kuNotStc_e10_2D='kuNotStc_e10_deltaT_vs_'+kuoutfile
outfile_kuNotStc_cl_2D='kuNotStc_cl_deltaT_vs_'+kuoutfile
outfile_kuNotStc_ic_2D='kuNotStc_ic_deltaT_vs_'+kuoutfile

#outfile_kuStc_e0_2D='kuStc_e0_deltaT_vs_'+kuoutfile
#outfile_kuStc_e1_2D='kuStc_e1_deltaT_vs_'+kuoutfile
#outfile_kuStc_2e1_2D='kuStc_2e1_deltaT_vs_'+kuoutfile
#outfile_kuStc_4e1_2D='kuStc_4e1_deltaT_vs_'+kuoutfile
#outfile_kuStc_e2_2D='kuStc_e2_deltaT_vs_'+kuoutfile
outfile_kuStc_e5_2D='kuStc_e5_deltaT_vs_'+kuoutfile
#outfile_kuStc_2e5_2D='kuStc_2e5_deltaT_vs_'+kuoutfile
#outfile_kuStc_4e5_2D='kuStc_4e5_deltaT_vs_'+kuoutfile
#outfile_kuStc_e10_2D='kuStc_e10_deltaT_vs_'+kuoutfile
#outfile_kuStc_cl_2D='kuStc_cl_deltaT_vs_'+kuoutfile
#outfile_kuStc_ic_2D='kuStc_ic_deltaT_vs_'+kuoutfile

outfile_kuWtStc_e5_2D='kuWtStc_e5_deltaT_vs_'+kuoutfile
outfile_kuWootStc_e5_2D='kuWootStc_e5_deltaT_vs_'+kuoutfile

timefile='_timefit'

#Plot Configs standard
plot_2D='ku_config/tmp_ratio_deltaT_vs_A_eff_EBEB.txt'
plot_ku_2D='ku_config/tmp_ku_deltaT_vs_A_eff_EBEB.txt'

#Plot Configs with KU preplotbration
plot_kuStc_2D='ku_config/tmp_kuStc_deltaT_vs_A_eff_EBEB.txt'
#plot_kuNot_2D='ku_config/tmp_kuNot_cali_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_2D='ku_config/tmp_kuNotStc_cali_deltaT_vs_A_eff_EBEB.txt'

plot_kuNotStc_e0_2D='ku_config/tmp_kuNotStc_cali_e0_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_e1_2D='ku_config/tmp_kuNotStc_cali_e1_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_2e1_2D='ku_config/tmp_kuNotStc_cali_2e1_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_4e1_2D='ku_config/tmp_kuNotStc_cali_4e1_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_e2_2D='ku_config/tmp_kuNotStc_cali_e2_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_e5_2D='ku_config/tmp_kuNotStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_2e5_2D='ku_config/tmp_kuNotStc_cali_2e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_4e5_2D='ku_config/tmp_kuNotStc_cali_4e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_e10_2D='ku_config/tmp_kuNotStc_cali_e10_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_cl_2D='ku_config/tmp_kuNotStc_cali_cl_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_ic_2D='ku_config/tmp_kuNotStc_cali_ic_deltaT_vs_A_eff_EBEB.txt'

#plot_kuStc_e0_2D='ku_config/tmp_kuStc_cali_e0_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_e1_2D='ku_config/tmp_kuStc_cali_e1_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_2e1_2D='ku_config/tmp_kuStc_cali_2e1_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_4e1_2D='ku_config/tmp_kuStc_cali_4e1_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_e2_2D='ku_config/tmp_kuStc_cali_e2_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_e5_2D='ku_config/tmp_kuStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_2e5_2D='ku_config/tmp_kuStc_cali_2e5_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_4e5_2D='ku_config/tmp_kuStc_cali_4e5_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_e10_2D='ku_config/tmp_kuStc_cali_e10_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_cl_2D='ku_config/tmp_kuStc_cali_cl_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_ic_2D='ku_config/tmp_kuStc_cali_ic_deltaT_vs_A_eff_EBEB.txt'

plot_kuWtStc_e5_2D='ku_config/tmp_kuWtStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuWootStc_e5_2D='ku_config/tmp_kuWootStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'

base = [ plot_2D, outfile_2D, outfile ]
ku = [ plot_ku_2D, outfile_ku_2D, kuoutfile ]
kuStc = [ plot_kuStc_2D, outfile_kuStc_2D, kuStcoutfile ]
#kuNot = [ plot_kuNot_2D, outfile_kuNot_2D, kuNotoutfile ]
kuNotStc = [ plot_kuNotStc_2D, outfile_kuNotStc_2D, kuNotStcoutfile ]
kuNotStcE0 = [ plot_kuNotStc_e0_2D, outfile_kuNotStc_e0_2D, kuNotStc_e0_outfile ]
kuNotStcE1 = [ plot_kuNotStc_e1_2D, outfile_kuNotStc_e1_2D, kuNotStc_e1_outfile ]
kuNotStc2E1 = [ plot_kuNotStc_2e1_2D, outfile_kuNotStc_2e1_2D, kuNotStc_2e1_outfile ]
kuNotStc4E1 = [ plot_kuNotStc_4e1_2D, outfile_kuNotStc_4e1_2D, kuNotStc_4e1_outfile ]
kuNotStcE2 = [ plot_kuNotStc_e2_2D, outfile_kuNotStc_e2_2D, kuNotStc_e2_outfile ]
kuNotStcE5 = [ plot_kuNotStc_e5_2D, outfile_kuNotStc_e5_2D, kuNotStc_e5_outfile ]
kuNotStc2E5 = [ plot_kuNotStc_2e5_2D, outfile_kuNotStc_2e5_2D, kuNotStc_2e5_outfile ]
kuNotStc4E5 = [ plot_kuNotStc_4e5_2D, outfile_kuNotStc_4e5_2D, kuNotStc_4e5_outfile ]
kuNotStcE10 = [ plot_kuNotStc_e10_2D, outfile_kuNotStc_e10_2D, kuNotStc_e10_outfile ]
kuNotStcCl = [ plot_kuNotStc_cl_2D, outfile_kuNotStc_cl_2D, kuNotStc_cl_outfile ]
kuNotStcIc= [ plot_kuNotStc_ic_2D, outfile_kuNotStc_ic_2D, kuNotStc_ic_outfile ]
#kuStcE0 = [ plot_kuStc_e0_2D, outfile_kuStc_e0_2D, kuStc_e0_outfile ]
#kuStcE1 = [ plot_kuStc_e1_2D, outfile_kuStc_e1_2D, kuStc_e1_outfile ]
#kuStc2E1 = [ plot_kuStc_2e1_2D, outfile_kuStc_2e1_2D, kuStc_2e1_outfile ]
#kuStc4E1 = [ plot_kuStc_4e1_2D, outfile_kuStc_4e1_2D, kuStc_4e1_outfile ]
#kuStcE2 = [ plot_kuStc_e2_2D, outfile_kuStc_e2_2D, kuStc_e2_outfile ]
kuStcE5 = [ plot_kuStc_e5_2D, outfile_kuStc_e5_2D, kuStc_e5_outfile ]
#kuStc2E5 = [ plot_kuStc_2e5_2D, outfile_kuStc_2e5_2D, kuStc_2e5_outfile ]
#kuStc4E5 = [ plot_kuStc_4e5_2D, outfile_kuStc_4e5_2D, kuStc_4e5_outfile ]
#kuStcE10 = [ plot_kuStc_e10_2D, outfile_kuStc_e10_2D, kuStc_e10_outfile ]
#kuStcCl = [ plot_kuStc_cl_2D, outfile_kuStc_cl_2D, kuStc_cl_outfile ]
#kuStcIc= [ plot_kuStc_ic_2D, outfile_kuStc_ic_2D, kuStc_ic_outfile ]
#kuWtStcE5 = [ plot_kuWtStc_e5_2D, outfile_kuWtStc_e5_2D, kuWtStc_e5_outfile ]
kuWootStcE5 = [ plot_kuWootStc_e5_2D, outfile_kuWootStc_e5_2D, kuWootStc_e5_outfile ]

#plot_list = [ base, ku, kuStc, kuNot, kuNotStc ]
plot_list = [kuNotStcE0, kuNotStcE1, kuNotStcE2, kuNotStcE5, kuNotStcE10, kuNotStcCl, kuNotStcIc ]
#plot_list = [kuStcE0, kuStcE1, kuStcE2, kuStcE5, kuStcE10 ] #, kuStcCl, kuStcIc ]
#plot_list = [kuStcE1, kuStc2E1, kuStc4E1, kuStcE5, kuStc2E5, kuStc4E5 ] #, kuStcCl, kuStcIc ]
#plot_list = [ ku, kuStcCl, kuStcIc ]
#plot_list = [ kuWootStcE5 ]
#plot_list = [ kuNotStcE0, kuNotStcE1, kuNotStcE2, kuNotStcE5, kuNotStcE10, kuNotStcCl, kuNotStcIc, kuWootStcE5, 
#		kuStcE5, kuNotStc2E1, kuNotStc4E1, kuNotStc2E5, kuNotStc4E5, ku, base ]

#cut_cf='ku_config/tmp_cut_config.txt'
cut_cf='ku_config/tmp_same_cut_config.txt'
#cut_cf='ku_config/tmp_diff_cut_config.txt'
misc_cf='misc_config/misc.txt'
varwgt_cf='varwgt_config/empty.txt'
timefit_cf='ku_config/tmp_timefit_config.txt'
skim_cf='skim_config/DiXtal_kurecs_Skim.txt'  #  LOCAL
#skim_cf='skim_config/DiXtal_nokurecs_Skim.txt'
#skim_cf='skim_config/DiXtal_Skim.txt'
#skim_cf='skim_config/Zee_kurecs_Skim.txt'  #  GLOBAL
misc_fit_cf='ku_config/tmp_misc_fit.txt'

#indir="/home/t3-ku/jaking/trees/ecal"
indir="/home/t3-ku/jaking/datasets/ecalTiming/EGamma"
#indir="/home/t3-ku/jaking/datasets/ecalTiming/DoubleEG"
#indir="../test/"
#skimoutdir="skimmed/local_ta/"
#skimoutdir="skimmed/local_tb/"
#skimoutdir="skimmed/global_ta/"
#skimoutdir="skimmed/global_tb/"
skimoutdir="skimmed/"
caliindir="skimmed/global_ta/"
#caliindir=skimoutdir
outdir=infile[:-5]+"/"
filedir="trplots/"+outdir

qc='\\",\\"'
qq='" "'
sq=' "'
eq='"'
plotter2d='./scripts/runTreePlotter2D.sh '
timefit='./scripts/runTimeFitter.sh '
skim2a='root -b -q -l wc_runKUSkimmer_v2a.C\(\\"'
skim2wt='root -b -q -l wc_runKUSkimmer_v2wt.C\(\\"'
skim_chain_2a='root -b -q -l wc_runKUSkimmer_chain_v2a.C\(\\"'
skim2b='root -b -q -l wc_runKUSkimmer_v2b.C\(\\"'
#skim2='root -b -q -l wc_runKUSkimmer.C\(\\"'
#dopreplot='root -b -q -l wc_ku_Preplot.C\(\\"'
#dopreplot='root -b -q -l wc_ku_Preplot_nowt.C\(\\"'
dopreplot='root -b -q -l wc_ku_Preplot_ic.C\(\\"'
dointercali='root -b -q -l wc_ku_InterCali_global_v1.C\(\\"'
#dointercali='root -b -q -l wc_ku_InterCali_v1.C\(\\"'
#dointercali='root -b -q -l wc_ku_InterCali_v2.C\(\\"'
#dointercali='root -b -q -l wc_runKUIntercalV2.C\(\\"'
docaliplot='root -b -q -l wc_ku_CaliPlots.C\(\\"'
#wc_ku_CaliPlots.C
end_skim='\\"\)'

#######################################################################################
## make all plots in plot list
def do_plots( plot_list ):

    for entry in plot_list :
        #2d_plot = entry[0]  #2d_outfile = entry[1]  #tf_outile = entry[2]
	##  makes base 2d plot for time fit
        cmd2d=plotter2d+sq+skimoutdir+infile+qq+skimoutdir+infile+qq+cut_cf+qq+varwgt_cf+qq+entry[0]+qq+misc_cf+qq+era+qq+entry[1]+qq+outdir+eq
        os.system(cmd2d)
	## run fitter, getting 2D plots from before
        cmdtf=timefit+sq+filedir+entry[1]+'.root'+qq+entry[0]+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+entry[2]+timefile+qq+outdir+eq
        os.system(cmdtf)

## run skimmer 
def do_skimmer():

 	cmdskim=skim2a+indir+qc+skimoutdir+qc+skiminfile+qc+skim_cf+end_skim
#        cmdskim=skim2b+indir+qc+skimoutdir+qc+skiminfile+qc+skim_cf+end_skim
#        cmdskim=skim2+indir+qc+skimoutdir+qc+skiminfile+qc+skim_cf+end_skim
	print(cmdskim)
	os.system(cmdskim)

def do_skimmer_list(infilelist):
 
	for skimfile in infilelist :
        	cmdskim=skim2a+indir+qc+skimoutdir+qc+skimfile+qc+skim_cf+end_skim
        	print(cmdskim)
        	os.system(cmdskim)

def do_skimmer_list_wt(infilelist):

        for skimfile in infilelist :
                cmdskim=skim2wt+indir+qc+skimoutdir+qc+skimfile+qc+skim_cf+end_skim
                print(cmdskim)
                os.system(cmdskim)

def do_skimmer_chain():

        cmdskim=skim_chain_2a+indir+qc+skimoutdir+qc+skiminlist+qc+skim_cf+end_skim
        print(cmdskim)
        os.system(cmdskim)

##  run preplot skimmer
def do_preplotskim():

	cmdpreplot=dopreplot+caliindir+caliinfile+qc+skimoutdir+skiminfile+qc+skimoutdir+preplotoutfile+end_skim
	print(cmdpreplot)
	os.system(cmdpreplot)

def do_intercali():

	cmdintercali=dointercali+skimoutdir+skiminfile+qc+skimoutdir+caliinfile+end_skim
        print(cmdintercali)
        os.system(cmdintercali)

#wc_ku_CaliPlots.C
def do_caliplots():

	cmdcaliplot=docaliplot+skimoutdir+cali1infile+qc+skimoutdir+cali2infile+qc+skimoutdir+calioutfile+end_skim
        print(cmdcaliplot)
        os.system(cmdcaliplot)

######################################################################################

#do_skimmer()
#do_skimmer_list(inlist_dataset_double)
#do_skimmer_list(inlist_tree_94)
do_skimmer_list_wt(inlist_dataset_egamma_woot)
#do_skimmer_chain()
#do_intercali()
#do_preplotskim()
#do_plots( plot_list )
#do_caliplots()






