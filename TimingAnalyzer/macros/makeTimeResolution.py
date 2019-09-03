import os
import sys

#infile = (sys.argv[1:])[0]
infile='ku_multitest_twotier_run18D_323414_dispho.root'
#infile='ku_rhcomp_twotier_run18D_dispho.root'
#infile='dispho_mini_eg2018A_315322.root'

outfile='Local_EBEB_Full'
kuoutfile='ku_Local_EBEB_Full'              
kuStcoutfile='kuStc_Local_EBEB_Full'
kuNotoutfile='kuNot_Local_EBEB_Full'
kuNotStcoutfile='kuNotStc_Local_EBEB_Full'

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

era='Full'
cut_cf='ku_config/tmp_cut_config.txt'
misc_cf='misc_config/misc.txt'
varwgt_cf='varwgt_config/empty.txt'
timefit_cf='ku_config/tmp_timefit_config.txt'
skim_cf='skim_config/DiXtal_kurecs_Skim.txt'
#skim_cf='skim_config/DiXtal_Skim.txt'
misc_fit_cf='ku_config/tmp_misc_fit.txt'

#indir="/home/t3-ku/jaking/trees/ecal"
indir="/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test"
outdir="skimmed/"
thisdir=""

qc='\\",\\"'
qq='" "'
sq=' "'
eq='"'
plotter2d='./scripts/runTreePlotter2D.sh '
timefit='./scripts/runTimeFitter.sh '
skim='root -b -q -l runKUSkimmer.C\(\\"'
#skim='root -b -q -l runSkimmer.C\("'
end_skim='\\"\)'

# run skimmer for Local
cmdskim=skim+indir+qc+outdir+qc+infile+qc+skim_cf+end_skim
print(cmdskim)
os.system(cmdskim)

#  makes base 2d plot for time fit
cmd2da=plotter2d+sq+outdir+infile+qq+outdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_2D+qq+misc_cf+qq+era+qq+outfile2D+qq+thisdir+eq
os.system(cmd2da)
cmd2db=plotter2d+sq+outdir+infile+qq+outdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_ku_2D+qq+misc_cf+qq+era+qq+outfile_ku_2D+qq+thisdir+eq
os.system(cmd2db)
cmd2dc=plotter2d+sq+outdir+infile+qq+outdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_kuStc_2D+qq+misc_cf+qq+era+qq+outfile_kuStc_2D+qq+thisdir+eq
os.system(cmd2dc)
cmd2dd=plotter2d+sq+outdir+infile+qq+outdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_kuNot_2D+qq+misc_cf+qq+era+qq+outfile_kuNot_2D+qq+thisdir+eq
os.system(cmd2dd)
cmd2de=plotter2d+sq+outdir+infile+qq+outdir+infile+qq+cut_cf+qq+varwgt_cf+qq+plot_kuNotStc_2D+qq+misc_cf+qq+era+qq+outfile_kuNotStc_2D+qq+thisdir+eq
os.system(cmd2de)

## run fitter, getting 2D plots from before
cmdta=timefit+sq+outfile2D+'.root'+qq+plot_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+outfile+timefile+qq+thisdir+eq
os.system(cmdta)
cmdtb=timefit+sq+outfile_ku_2D+'.root'+qq+plot_ku_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+kuoutfile+timefile+qq+thisdir+eq
os.system(cmdtb)
cmdtc=timefit+sq+outfile_kuStc_2D+'.root'+qq+plot_kuStc_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+kuStcoutfile+timefile+qq+thisdir+eq
os.system(cmdtc)
cmdtd=timefit+sq+outfile_kuNot_2D+'.root'+qq+plot_kuNot_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+kuNotoutfile+timefile+qq+thisdir+eq
os.system(cmdtd)
cmdte=timefit+sq+outfile_kuNotStc_2D+'.root'+qq+plot_kuNotStc_2D+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+kuNotStcoutfile+timefile+qq+thisdir+eq
os.system(cmdte)


