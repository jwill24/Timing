import os
import sys

#infile = (sys.argv[1:])[0]
#infile='ku_multitest_twotier_run18D_323414_dispho.root'
#infile='dispho_raw_eg2018A_315322.root'
#infile='ku_twotier_run18D_320712_dispho.root'
#infile='output_235.root'
infile='dispho_2t_eg2018B.root'
#infile='ku_rhcomp_twotier_run18D_dispho.root'
#infile='dispho_mini_eg2018A_315322.root'

eta='EBEB'
era='Full'
#res='Local'
res='Local_Same'

outfile=res+'_'+eta+'_'+era
kuoutfile='ku_'+outfile              
kuStcoutfile='kuStc_'+outfile
kuNotoutfile='kuNot_'+outfile
kuNotStcoutfile='kuNotStc_'+outfile

outfile2D='deltaT_vs_'+outfile
outfile_ku_2D='ku_deltaT_vs_'+kuoutfile
outfile_kuStc_2D='kuStc_deltaT_vs_'+kuoutfile
outfile_kuNot_2D='kuNot_deltaT_vs_'+kuoutfile
outfile_kuNotStc_2D='kuNotStc_deltaT_vs_'+kuoutfile
timefile='_timefit'

plot_2D='ku_config/tmp_ratio_deltaT_vs_A_eff_EBEB.txt'
plot_ku_2D='ku_config/tmp_ku_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_2D='ku_config/tmp_kuStc_deltaT_vs_A_eff_EBEB.txt'
plot_kuNot_2D='ku_config/tmp_kuNot_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_2D='ku_config/tmp_kuNotStc_deltaT_vs_A_eff_EBEB.txt'

#cut_cf='ku_config/tmp_cut_config.txt'
cut_cf='ku_config/tmp_same_cut_config.txt'
#cut_cf='ku_config/tmp_diff_cut_config.txt'
misc_cf='misc_config/misc.txt'
varwgt_cf='varwgt_config/empty.txt'
timefit_cf='ku_config/tmp_timefit_config.txt'
skim_cf='skim_config/DiXtal_kurecs_Skim.txt'
#skim_cf='skim_config/DiXtal_nokurecs_Skim.txt'
#skim_cf='skim_config/DiXtal_Skim.txt'
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
skim='root -b -q -l runKUSkimmer_v2.C\(\\"'
#skim='root -b -q -l runSkimmer.C\("'
end_skim='\\"\)'

# run skimmer for Local
cmdskim=skim+indir+qc+skimoutdir+qc+infile+qc+skim_cf+end_skim
print(cmdskim)
#os.system(cmdskim)

#  makes base 2d plot for time fit
cmd2da=plotter2d+sq+skimoutdir+infile+qq+skimoutdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_2D+qq+misc_cf+qq+era+qq+outfile2D+qq+outdir+eq
os.system(cmd2da)
cmd2db=plotter2d+sq+skimoutdir+infile+qq+skimoutdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_ku_2D+qq+misc_cf+qq+era+qq+outfile_ku_2D+qq+outdir+eq
os.system(cmd2db)
cmd2dc=plotter2d+sq+skimoutdir+infile+qq+skimoutdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_kuStc_2D+qq+misc_cf+qq+era+qq+outfile_kuStc_2D+qq+outdir+eq
os.system(cmd2dc)
cmd2dd=plotter2d+sq+skimoutdir+infile+qq+skimoutdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_kuNot_2D+qq+misc_cf+qq+era+qq+outfile_kuNot_2D+qq+outdir+eq
os.system(cmd2dd)
cmd2de=plotter2d+sq+skimoutdir+infile+qq+skimoutdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_kuNotStc_2D+qq+misc_cf+qq+era+qq+outfile_kuNotStc_2D+qq+outdir+eq
os.system(cmd2de)

## run fitter, getting 2D plots from before
cmdta=timefit+sq+filedir+outfile2D+'.root'+qq+plot_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+outfile+timefile+qq+outdir+eq
os.system(cmdta)
cmdtb=timefit+sq+filedir+outfile_ku_2D+'.root'+qq+plot_ku_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+kuoutfile+timefile+qq+outdir+eq
os.system(cmdtb)
cmdtc=timefit+sq+filedir+outfile_kuStc_2D+'.root'+qq+plot_kuStc_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+kuStcoutfile+timefile+qq+outdir+eq
os.system(cmdtc)
cmdtd=timefit+sq+filedir+outfile_kuNot_2D+'.root'+qq+plot_kuNot_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+kuNotoutfile+timefile+qq+outdir+eq
os.system(cmdtd)
cmdte=timefit+sq+filedir+outfile_kuNotStc_2D+'.root'+qq+plot_kuNotStc_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+kuNotStcoutfile+timefile+qq+outdir+eq
os.system(cmdte)

