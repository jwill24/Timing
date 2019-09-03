#!/bin/bash

## config
indir=${1}
outdir=${2}
filename=${3}
skimconfig=${4}

## run macro

##DiXtal

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2017B.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2017C.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2017D.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2017E.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2017F.root\",\"skim_config/DiXtal_Skim.txt\"\)
#
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017B.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017C.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017D.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017E.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017F.root\",\"skim_config/DiXtal_Skim.txt\"\)
#
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_eg2018D_0000.root\",\"skim_config/DiXtal_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_eg2018D_0001.root\",\"skim_config/DiXtal_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_eg2018D_0002.root\",\"skim_config/DiXtal_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_eg2018D_0003.root\",\"skim_config/DiXtal_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_eg2018A_0000.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_eg2018A_0001.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_eg2018B.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_eg2018C.root\",\"skim_config/DiXtal_Skim.txt\"\)
#
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2016C.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2016D.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2016E.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2016F.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2016G.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_sp2016H.root\",\"skim_config/DiXtal_Skim.txt\"\)
#
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016C.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016D.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016E.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016F.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016G.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016H.root\",\"skim_config/DiXtal_Skim.txt\"\)


##ZEE 

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2017B.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2017C.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2017D.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2017E.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2017F.root\",\"skim_config/Zee_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017B.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017C.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017D.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017E.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017F.root\",\"skim_config/Zee_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_eg2018D_0000.root\",\"skim_config/Zee_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_eg2018D_0001.root\",\"skim_config/Zee_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_eg2018D_0002.root\",\"skim_config/Zee_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_eg2018D_0003.root\",\"skim_config/Zee_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_eg2018A_0000.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_eg2018A_0001.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_eg2018B.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_eg2018C.root\",\"skim_config/Zee_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2016C.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2016D.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2016E.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2016F.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2016G.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_sp2016H.root\",\"skim_config/Zee_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016C.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016D.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016E.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016F.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016G.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016H.root\",\"skim_config/Zee_Skim.txt\"\)

##RAW tests
##2016
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_raw94_deg2016G_279760.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_raw94_deg2016G_280191.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_raw94_deg2016G_280251.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_raw94_deg2016G_280364.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_raw94_deg2016G_279760.root\",\"skim_config/Zee_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_raw94_deg2016G_280191.root\",\"skim_config/Zee_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_raw94_deg2016G_280251.root\",\"skim_config/Zee_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_raw94_deg2016G_280364.root\",\"skim_config/Zee_urec_Skim.txt\"\)

##2017

##dispho_raw_deg2017B_297101.root
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_raw94_deg2017B_297411.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_raw94_deg2017B_297486.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_raw94_deg2017B_299061.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_raw94_deg2017B_297101.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_raw94_deg2017B_297411.root\",\"skim_config/Zee_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_raw94_deg2017B_297486.root\",\"skim_config/Zee_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_raw94_deg2017B_299061.root\",\"skim_config/Zee_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_raw94_deg2017B_297101.root\",\"skim_config/Zee_urec_Skim.txt\"\)


##2018
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_raw_eg2018A_315322.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_raw_eg2018A_315322.root\",\"skim_config/Zee_urec_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_mini_eg2018A_315322.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_mini_eg2018A_315322.root\",\"skim_config/Zee_Skim.txt\"\)

##ku_rechit test
#very_short_kutest_run18D_dispho.root
#root -b -q -l runKUSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"ku_2tier_test_run18D_dispho.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)
#root -b -q -l runKUSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"ku_2tier_test_run18D_dispho.root\",\"skim_config/Zee_urec_Skim.txt\"\)

root -b -q -l runKUSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"ku_rhcomp_twotier_run18D_dispho.root\",\"skim_config/DiXtal_urec_Skim.txt\"\)
#root -b -q -l runKUSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"ku_rhcomp_twotier_run18D_dispho.root\",\"skim_config/Zee_urec_Skim.txt\"\)


## Final message
echo "Finished Skimming for file:" #${filename}
