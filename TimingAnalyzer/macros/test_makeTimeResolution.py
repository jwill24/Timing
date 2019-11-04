import os
import sys

#skiminfile = (sys.argv[1:])[0]
#skiminfile='ku_multitest_twotier_run18D_323414_dispho.root'
#skiminfile='dispho_raw_eg2018A_315322.root'
#skiminfile='ku_twotier_run18D_320712_dispho.root'
#skiminfile='output_235.root'
#skiminfile='ku_rhcomp_twotier_run18D_dispho.root'
#skiminfile='dispho_mini_eg2018A_315322.root'
#skiminfile='dispho_2t_eg2018B.root'
#skiminfile='dispho_2t_eg2018B_global.root'
skiminfile='dispho_2t_eg2018B_local.root'
#skiminfile='dispho_2t_eg2018B_notof.root'
#calioutfile=skiminfile
#calioutfile='dispho_2t_eg2018B_cali.root'
#calioutfile='dispho_2t_eg2018B_global_cali.root'
calioutfile='dispho_2t_eg2018B_local_cali.root'
#calioutfile='dispho_2t_eg2018B_notof_cali.root'
#calioutfile='dispho_2t_eg2018B_tof_cali.root'
#calioutfile='dispho_2t_eg2018B_inter_cali.root'

infile=calioutfile
#infile=skiminfile

eta='EBEB'
era='Full'
#res='Local'
res='Local_Same'

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
kuStcoutfile='kuStc_'+outfile
kuStc_e0_outfile='kuStc_e0_'+outfile
kuStc_e1_outfile='kuStc_e1_'+outfile
kuStc_2e1_outfile='kuStc_2e1_'+outfile
kuStc_4e1_outfile='kuStc_4e1_'+outfile
kuStc_e2_outfile='kuStc_e2_'+outfile
kuStc_e5_outfile='kuStc_e5_'+outfile
kuStc_2e5_outfile='kuStc_2e5_'+outfile
kuStc_4e5_outfile='kuStc_4e5_'+outfile
kuStc_e10_outfile='kuStc_e10_'+outfile
kuStc_cl_outfile='kuStc_cl_'+outfile
kuStc_ic_outfile='kuStc_ic_'+outfile

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
outfile_kuStc_e0_2D='kuStc_e0_deltaT_vs_'+kuoutfile
outfile_kuStc_e1_2D='kuStc_e1_deltaT_vs_'+kuoutfile
outfile_kuStc_2e1_2D='kuStc_2e1_deltaT_vs_'+kuoutfile
outfile_kuStc_4e1_2D='kuStc_4e1_deltaT_vs_'+kuoutfile
outfile_kuStc_e2_2D='kuStc_e2_deltaT_vs_'+kuoutfile
outfile_kuStc_e5_2D='kuStc_e5_deltaT_vs_'+kuoutfile
outfile_kuStc_2e5_2D='kuStc_2e5_deltaT_vs_'+kuoutfile
outfile_kuStc_4e5_2D='kuStc_4e5_deltaT_vs_'+kuoutfile
outfile_kuStc_e10_2D='kuStc_e10_deltaT_vs_'+kuoutfile
outfile_kuStc_cl_2D='kuStc_cl_deltaT_vs_'+kuoutfile
outfile_kuStc_ic_2D='kuStc_ic_deltaT_vs_'+kuoutfile

timefile='_timefit'

#Plot Configs standard
plot_2D='ku_config/tmp_ratio_deltaT_vs_A_eff_EBEB.txt'
plot_ku_2D='ku_config/tmp_ku_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_2D='ku_config/tmp_kuStc_deltaT_vs_A_eff_EBEB.txt'
#plot_kuNot_2D='ku_config/tmp_kuNot_deltaT_vs_A_eff_EBEB.txt'
#plot_kuNotStc_2D='ku_config/tmp_kuNotStc_deltaT_vs_A_eff_EBEB.txt'

#Plot Configs with KU calibration
#plot_ku_2D='ku_config/tmp_ku_calideltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_2D='ku_config/tmp_kuStc_calideltaT_vs_A_eff_EBEB.txt'
plot_kuNot_2D='ku_config/tmp_kuNot_calideltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_2D='ku_config/tmp_kuNotStc_calideltaT_vs_A_eff_EBEB.txt'

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
plot_kuStc_e0_2D='ku_config/tmp_kuStc_cali_e0_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_e1_2D='ku_config/tmp_kuStc_cali_e1_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_2e1_2D='ku_config/tmp_kuStc_cali_2e1_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_4e1_2D='ku_config/tmp_kuStc_cali_4e1_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_e2_2D='ku_config/tmp_kuStc_cali_e2_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_e5_2D='ku_config/tmp_kuStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_2e5_2D='ku_config/tmp_kuStc_cali_2e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_4e5_2D='ku_config/tmp_kuStc_cali_4e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_e10_2D='ku_config/tmp_kuStc_cali_e10_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_cl_2D='ku_config/tmp_kuStc_cali_cl_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_ic_2D='ku_config/tmp_kuStc_cali_ic_deltaT_vs_A_eff_EBEB.txt'

base = [ plot_2D, outfile_2D, outfile ]
ku = [ plot_ku_2D, outfile_ku_2D, kuoutfile ]
kuStc = [ plot_kuStc_2D, outfile_kuStc_2D, kuStcoutfile ]
kuNot = [ plot_kuNot_2D, outfile_kuNot_2D, kuNotoutfile ]
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
kuStcE0 = [ plot_kuStc_e0_2D, outfile_kuStc_e0_2D, kuStc_e0_outfile ]
kuStcE1 = [ plot_kuStc_e1_2D, outfile_kuStc_e1_2D, kuStc_e1_outfile ]
kuStc2E1 = [ plot_kuStc_2e1_2D, outfile_kuStc_2e1_2D, kuStc_2e1_outfile ]
kuStc4E1 = [ plot_kuStc_4e1_2D, outfile_kuStc_4e1_2D, kuStc_4e1_outfile ]
kuStcE2 = [ plot_kuStc_e2_2D, outfile_kuStc_e2_2D, kuStc_e2_outfile ]
kuStcE5 = [ plot_kuStc_e5_2D, outfile_kuStc_e5_2D, kuStc_e5_outfile ]
kuStc2E5 = [ plot_kuStc_2e5_2D, outfile_kuStc_2e5_2D, kuStc_2e5_outfile ]
kuStc4E5 = [ plot_kuStc_4e5_2D, outfile_kuStc_4e5_2D, kuStc_4e5_outfile ]
kuStcE10 = [ plot_kuStc_e10_2D, outfile_kuStc_e10_2D, kuStc_e10_outfile ]
kuStcCl = [ plot_kuStc_cl_2D, outfile_kuStc_cl_2D, kuStc_cl_outfile ]
kuStcIc= [ plot_kuStc_ic_2D, outfile_kuStc_ic_2D, kuStc_ic_outfile ]

#plot_list = [ base, ku, kuStc, kuNot, kuNotStc ]
#plot_list = [kuNotStcE0, kuNotStcE1, kuNotStcE2, kuNotStcE5, kuNotStcE10, kuNotStcCl, kuNotStcIc ]
#plot_list = [kuStcE0, kuStcE1, kuStcE2, kuStcE5, kuStcE10 ] #, kuStcCl, kuStcIc ]
#plot_list = [kuStcE1, kuStc2E1, kuStc4E1, kuStcE5, kuStc2E5, kuStc4E5 ] #, kuStcCl, kuStcIc ]
plot_list = [ ku, kuStcCl, kuStcIc ]

#cut_cf='ku_config/tmp_cut_config.txt'
cut_cf='ku_config/tmp_same_cut_config.txt'
#cut_cf='ku_config/tmp_diff_cut_config.txt'
misc_cf='misc_config/misc.txt'
varwgt_cf='varwgt_config/empty.txt'
timefit_cf='ku_config/tmp_timefit_config.txt'
skim_cf='skim_config/DiXtal_kurecs_Skim.txt'
#skim_cf='skim_config/DiXtal_nokurecs_Skim.txt'
#skim_cf='skim_config/DiXtal_Skim.txt'
#skim_cf='skim_config/Zee_kurecs_Skim.txt'
misc_fit_cf='ku_config/tmp_misc_fit.txt'

indir="/home/t3-ku/jaking/trees/ecal"
#indir="/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test"
#indir="/home/t3-ku/jaking/datasets/ecalTiming/EGamma/valtest32_twotier_EGamma_MINIAOD_Run2018D-PromptReco-v2_320673-320933_dispho/191002_161827/0000/"
#indir="../test/"
#indir=""
skimoutdir="skimmed/"
outdir=infile[:-5]+"/"
filedir="trplots/"+outdir

qc='\\",\\"'
qq='" "'
sq=' "'
eq='"'
plotter2d='./scripts/runTreePlotter2D.sh '
timefit='./scripts/runTimeFitter.sh '
skim='root -b -q -l wc_runKUSkimmer.C\(\\"'
#skim='root -b -q -l runSkimmer.C\("'
docali='root -b -q -l wc_ku_Cali.C\(\\"'
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

## run skimmer for Local
def do_skimmer():

	cmdskim=skim+indir+qc+skimoutdir+qc+skiminfile+qc+skim_cf+end_skim
	print(cmdskim)
	os.system(cmdskim)

##  run cali skimmer
def do_caliskim():

	cmdcali=docali+skimoutdir+skiminfile+qc+skimoutdir+calioutfile+end_skim
	print(cmdcali)
	os.system(cmdcali)

######################################################################################

#do_skimmer()
#do_caliskim()
do_plots( plot_list )




