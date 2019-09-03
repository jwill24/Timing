#!/bin/bash

##################
## Source First ##
##################
source scripts/common_variables.sh

############
## Config ##
############

echo "Reading Config"

#half_2018RunD_ntp.root
## command line inputs
#outdirbase=${1:-"madv2_v1/timing/Zee"}
outdirbase=${1:-"dispho_plots"}
#usetof=${2:-"false"}
usetof=${2:-"true"}
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
useshift=${3:-"false"}
usesmear=${4:-"false"}
#triggertower=${5:-"Inclusive"}
#triggertower=${5:-"Same"}
#triggertower=${5:-"Different"}

echo "outdirbase=${outdirbase}"
echo "usetof=${usetof}"
echo "useshift=${useshift}"
echo "usesmear=${usesmear}"
#echo "triggertower=${triggertower}"

tower_i="Inclusive"
tower_s="Same"
tower_d="Different"

## other info
#diphodir="test"

#run="2016sp"
#run="2017sp"
#run="2016deg_tof_ntt"
#run="2017deg_tof"
#run="2018eg_tof_ntt"
#run="2016G_deg_tof_raw_part"
#run="2017B_deg_tof_raw_part"
#run="2018eg_tof"
#run="2018A_eg_tof_raw_315322"
#run="2018A_eg_tof_mini_315322"
#run="2018D_part_twotier_ku"
run="2018D_part_twotier_ratio"

loc="Local"
glo="Global"

#typelist="${loc}"
#typelist="${glo}"
typelist="${loc} ${glo}"

inc="Inclusive"
sam="Same"
dif="Different"

towerlistg="${inc}"
#towerlistl="${inc}"
towerlistl="${inc} ${sam} ${dif}"

ntcutname0="None"
ntcutname1="nvtxCut1"
ntcutname2="nvtxCut2"
ntcutname3="nvtxCut3"
ntcutname4="nvtxCut4"
ntcutname5="nvtxCut5"
ntcutname6="nvtxCut6"

ntcutname7="trianCut1"
ntcutname8="trianCut2"
ntcutname9="trianCut3"
ntcutname10="trianCut14"
ntcutname11="trianCut15"
ntcutname12="trianCut16"
ntcutname13="trianCut17"
ntcutname14="trianCut18"

fragdir="plot_config/fragments"

#Zeel="Local dispho_DiXtal_v2_2016 dispho_Zee_v2_2017B always_true"
#Zeeg="Global dispho_Zee_v2_2016 dispho_Zee_v2_2017B always_true"

#Zeeg="Global dispho_Zee_v2_2017 dispho_Zee_v2_2017B always_true"
#Zeel="Local dispho_DiXtal_v2_2017 dispho_Zee_v2_2017B always_true"

#Zeel="Local dispho_DiXtal_v2_2018D dispho_Zee_v2_2017B always_true"
#Zeeg="Global dispho_Zee_v2_2018D dispho_DiXtal_2017B always_true"

#Zeel="Local dispho_DiXtal_v2_2018ABC dispho_Zee_v2_2017B always_true"
#Zeeg="Global dispho_Zee_v2_2018ABC dispho_DiXtal_2017B always_true"

#Zeel="Local dispho_DiXtal_v2_2018RAW dispho_Zee_v2_2017B always_true"
#Zeeg="Global dispho_Zee_v2_2018RAW dispho_Zee_v2_2017B always_true"

#dispho_Zee_v2_2018Dp_RAW.root
#Zeel="Local dispho_DiXtal_v2_2018Dp_RAW dispho_Zee_v2_2017B always_true"
#Zeeg="Global dispho_Zee_v2_2018Dp_RAW dispho_Zee_v2_2017B always_true"

#Zeel="Local dispho_DiXtal_v2_2018 dispho_Zee_v2_2017B always_true"
#Zeeg="Global dispho_Zee_v2_2018 dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v3_eg2018 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v3_eg2018 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v3_deg2017 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v3_deg2017 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v3_deg2016 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v3_deg2016 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v3_sp2017 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v3_sp2017 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v3_sp2016 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v3_sp2016 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v3_eg2018A_raw_315322 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v3_eg2018A_raw_315322 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v3_eg2018A_mini_315322 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v3_eg2018A_mini_315322 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v3_deg2017B_raw94_part skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v3_deg2017B_raw94_part skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v4_deg2017B_raw94_part skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v4_deg2017B_raw94_part skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v4_deg2016G_raw94_part skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v4_deg2016G_raw94_part skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_deg2016 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_ntt_deg2016 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_deg2017 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_ntt_deg2017 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_eg2018 skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_ntt_eg2018 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/ku_2tier_test_run18D_dispho skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/ku_2tier_test_run18D_dispho skimmed/dispho_Zee_v2_2017B always_true"

Zeel="Local dixtal_skims/ku_rhcomp_twotier_run18D_dispho skimmed/dispho_Zee_v2_2017B always_true"
Zeeg="Global zee_skims/ku_rhcomp_twotier_run18D_dispho skimmed/dispho_Zee_v2_2017B always_true"

ZEEL="${Zeel} empty"
#declare -a inputsl=(ZEEL)
#export inputsl

export ZEEG="${Zeeg} empty"
#declare -a inputsg=(ZEEG)
#export inputsg

A0="((phoseedE_0/phoseedadcToGeV_0)/phoseedpedrms12_0)"
A1="((phoseedE_1/phoseedadcToGeV_1)/phoseedpedrms12_1)"
fA="((${A0}*${A1})/sqrt(pow(${A0},2)+pow(${A1},2)))"
#pho_cut="(${fA}<700&&${fA}>350)"
#pho_cut="abs(${A0}-${A1})<750"
#pho_cut="(abs(phoseedtime_0)<3.0)&&(abs(phoseedtime_1)<5.0)"
pho_cut="1"

#phoseedtime_0
nvxt_cut0="1"
nvxt_cut1="nvtx<=20"
nvxt_cut2="nvtx>20&&nvtx<=40"
nvxt_cut3="nvtx>20&&nvtx<=30"
nvxt_cut4="nvtx>30&&nvtx<=40"
nvxt_cut5="nvtx>40&&nvtx<=60"
nvxt_cut6="nvtx>40"

nvxt_cut7="subtrain_position>0&&subtrain_position<=4"
nvxt_cut8="subtrain_position>4&&subtrain_position<=8"
nvxt_cut9="subtrain_position>8&&subtrain_position<=12"
nvxt_cut10="subtrain_position>0&&subtrain_position<=8"
nvxt_cut11="subtrain_position>8&&subtrain_position<=16"
nvxt_cut12="subtrain_position>16&&subtrain_position<=30"
nvxt_cut13="subtrain_position>30&&subtrain_position<=38"
nvxt_cut14="subtrain_position>38"

gdr_cut0="1"
#gdr_cut1="gdR<2.5"
gdr_cut1="max(phoseedootMax_0*(phoseedadcToGeV_0/phoseedE_0),phoseedootMax_1*(phoseedadcToGeV_1/phoseedE_1))<0.003"
#gdr_cut2="gdR>=2.5"
gdr_cut2="max(phoseedootMax_0*(phoseedadcToGeV_0/phoseedE_0),phoseedootMax_1*(phoseedadcToGeV_1/phoseedE_1))>=0.003"


emax="120"
eminlist="0 1 2 5 10 20"
#eminlist="1"
E0_120="(phoseedE_0>=0)&&(phoseedE_0<=120)&&(phoseedE_1>=0)&&(phoseedE_1<=120)"
E10_120="(phoseedE_0>=10)&&(phoseedE_0<=120)&&(phoseedE_1>=10)&&(phoseedE_1<=120)"
E0_1="(phoseedE_0>0)&&(phoseedE_0<=1)&&(phoseedE_1>0)&&(phoseedE_1<=1)"
E1_2="(phoseedE_0>1)&&(phoseedE_0<=2)&&(phoseedE_1>1)&&(phoseedE_1<=2)"
E2_5="(phoseedE_0>2)&&(phoseedE_0<=5)&&(phoseedE_1>2)&&(phoseedE_1<=5)"
E5_10="(phoseedE_0>5)&&(phoseedE_0<=10)&&(phoseedE_1>5)&&(phoseedE_1<=10)"
E10_20="(phoseedE_0>10)&&(phoseedE_0<=20)&&(phoseedE_1>10)&&(phoseedE_1<=20)"
E20_40="(phoseedE_0>20)&&(phoseedE_0<=40)&&(phoseedE_1>20)&&(phoseedE_1<=40)"
E40_80="(phoseedE_0>40)&&(phoseedE_0<=80)&&(phoseedE_1>40)&&(phoseedE_1<=80)"
E80_120="(phoseedE_0>80)&&(phoseedE_0<=120)&&(phoseedE_1>80)&&(phoseedE_1<=120)"

ecutnamef="FullE"
ecutnamef10="Emin10"
ecutname0="Ecut0"
ecutname1="Ecut1"
ecutname2="Ecut2"
ecutname5="Ecut5"
ecutname10="Ecut10"
ecutname20="Ecut20"
ecutname40="Ecut40"
ecutname80="Ecut80"

#gdrcutname0="FulldR"
#gdrcutname1="dRlt25"
#gdrcutname2="dRgt25"
gdrcutname0="nodr"
#gdrcutname0="FullMaxRoot"
#gdrcutname0="MaxRootGt"
#gdrcutname0="MaxRootLt"

#E_cutList="${E0_120}"
E_cutList="${E10_120}"
#E_cutList="${E0_120} ${E0_1} ${E1_2} ${E2_5} ${E5_10} ${E10_20} ${E20_40} ${E40_80} ${E80_120}"

nvxt_cuts="${nvxt_cut0}"
#nvxt_cuts="${nvxt_cut1} ${nvxt_cut2} ${nvxt_cut3} ${nvxt_cut4} ${nvxt_cut5} ${nvxt_cut6}" 
#nvxt_cuts="${nvxt_cut0} ${nvxt_cut1} ${nvxt_cut2} ${nvxt_cut3} ${nvxt_cut4} ${nvxt_cut5} ${nvxt_cut6} ${nvxt_cut7} ${nvxt_cut8} ${nvxt_cut9} ${nvxt_cut10} ${nvxt_cut11} ${nvxt_cut12} ${nvxt_cut13}  ${nvxt_cut14}"
#nvxt_cuts="${nvxt_cut7} ${nvxt_cut8}  ${nvxt_cut9} ${nvxt_cut10} ${nvxt_cut11} ${nvxt_cut12} ${nvxt_cut13}  ${nvxt_cut14}"
#nvxt_cuts="${nvxt_cut10} ${nvxt_cut11} ${nvxt_cut12} ${nvxt_cut13} ${nvxt_cut14}"
#echo ${nvxt_cuts}

gdr_cuts="${gdr_cut0}"
#gdr_cuts="${gdr_cut1}"
#gdr_cuts="${gdr_cut1} ${gdr_cut2}"
#gdr_cuts="${gdr_cut0} ${gdr_cut1} ${gdr_cut2}"


for plottype in ${typelist}
do

if [[ "${plottype}" == ${loc} ]]
then
	towerlist=${towerlistl}
else
        towerlist=${towerlistg}
fi


for tower in ${towerlist}
do

diphodir="${plottype}_${tower}_Run${run}"
triggertower=${tower}

echo "triggertower=${tower}"
echo "diphodir=${plottype}_${tower}_Run${run}"

if [[ "${plottype}" == ${loc} ]]
then
	declare -a inputs=(ZEEL)
	export inputs
	#inputs=${ZEEL}
else
	declare -a inputs=(ZEEG)
	export inputs
	#inputs=${ZEEG}
fi

for gdr_cut in ${gdr_cuts}
do

for E_cut in ${E_cutList}
do

for nvxt_cut in ${nvxt_cuts}
do
	
        if [[ "${nvxt_cut}" == ${nvxt_cut0} ]] 
	then 
		ntcutname=${ntcutname0}
	elif [[ "${nvxt_cut}" == ${nvxt_cut1} ]] 
	then 
		ntcutname=${ntcutname1}
        elif [[ "${nvxt_cut}" == ${nvxt_cut2} ]] 
	then 
		ntcutname=${ntcutname2}
        elif [[ "${nvxt_cut}" == ${nvxt_cut3} ]] 
	then 
		ntcutname=${ntcutname3}
        elif [[ "${nvxt_cut}" == ${nvxt_cut4} ]] 
	then 
		ntcutname=${ntcutname4}
        elif [[ "${nvxt_cut}" == ${nvxt_cut5} ]] 
	then 
		ntcutname=${ntcutname5}
        elif [[ "${nvxt_cut}" == ${nvxt_cut6} ]] 
	then 
		ntcutname=${ntcutname6}
        elif [[ "${nvxt_cut}" == ${nvxt_cut7} ]] 
	then 
		ntcutname=${ntcutname7}
        elif [[ "${nvxt_cut}" == ${nvxt_cut8} ]] 
	then 
		ntcutname=${ntcutname8}
        elif [[ "${nvxt_cut}" == ${nvxt_cut9} ]] 
	then 
		ntcutname=${ntcutname9}
        elif [[ "${nvxt_cut}" == ${nvxt_cut10} ]] 
	then 
		ntcutname=${ntcutname10}
        elif [[ "${nvxt_cut}" == ${nvxt_cut11} ]] 
	then 
		ntcutname=${ntcutname11}
        elif [[ "${nvxt_cut}" == ${nvxt_cut12} ]] 
	then 
		ntcutname=${ntcutname12}
        elif [[ "${nvxt_cut}" == ${nvxt_cut13} ]]
        then
                ntcutname=${ntcutname13}
        elif [[ "${nvxt_cut}" == ${nvxt_cut14} ]]
        then
                ntcutname=${ntcutname14}
	else
		echo " BAD NTVX ADDRESS"
	fi

        if [[ "${E_cut}" == ${E0_120} ]]
        then
                ecutname=${ecutnamef}
        elif [[ "${E_cut}" == ${E0_1} ]]
        then
                ecutname=${ecutname0}
        elif [[ "${E_cut}" == ${E1_2} ]]
        then
                ecutname=${ecutname1}
        elif [[ "${E_cut}" == ${E2_5} ]]
        then
                ecutname=${ecutname2}
        elif [[ "${E_cut}" == ${E5_10} ]]
        then
                ecutname=${ecutname5}
        elif [[ "${E_cut}" == ${E10_20} ]]
        then
                ecutname=${ecutname10}
        elif [[ "${E_cut}" == ${E20_40} ]]
        then
                ecutname=${ecutname20}
        elif [[ "${E_cut}" == ${E40_80} ]]
        then
                ecutname=${ecutname40}
        elif [[ "${E_cut}" == ${E80_120} ]]
        then
                ecutname=${ecutname80}
        elif [[ "${E_cut}" == ${E10_120} ]]
        then
                ecutname=${ecutnamef10}
        else
                echo "BAD E ADDRESS"
        fi

        #if [[ "${gdr_cut}" == ${gdr_cut0} ]]
        #then
        #        gdrcutname=${gdrcutname0}
        #elif [[ "${gdr_cut}" == ${gdr_cut1} ]]
        #then
        #        gdrcutname=${gdrcutname1}
        #elif [[ "${gdr_cut}" == ${gdr_cut2} ]]
        #then
        #        gdrcutname=${gdrcutname2}
	#fi

	#echo "Working with ${nvxt_cut} ${cut_t} ${gdr_cut} in ${diphodir}"
      
        gdrcutname=${gdrcutname0}
	jwk_cut="${nvxt_cut}&&${E_cut}&&${pho_cut}&&${gdr_cut}"
	echo "Working with : ${jwk_cut}"
	
	## eta regions
	declare -a dietas=("EBEB" "Full")
	
	## vars
	declare -a vars_map=("A_eff A") # "seedE_eff seedE"
	
	## logx vars
	declare -a logx_vars=("pt_0" "pt_1" "pt_eff" "E_0" "E_1" "E_eff" "seedE_eff" "A_eff")
	
	## do full era vars for mu hists
	declare -a mualleras_vars=()
	
	## sigma fit vars
	pt_0="p_{T} GeV 0 10 100 0 1 10"
	pt_1="p_{T} GeV 0 10 100 0 1 10"
	pt_eff="p_{T}^{Eff} GeV 0 10 100 0 1 10"
	E_0="E GeV 0 10 100 0 1 10"
	E_1="E GeV 0 10 100 0 1 10"
	E_eff="E_{eff} GeV 0 10 100 0 1 10"
	seedE_eff="E_{eff}^{seed} GeV 0 1 10 0 1 10"
	A_eff="A_{eff}/#sigma_{n} NONE 0 50 100 0 .5 1"
	declare -a sigmafit_vars=(pt_0 pt_1 pt_eff E_0 E_1 E_eff seedE_eff A_eff)
	
	###############
	## Run code! ##
	###############
	
	## loop over vars, dietas, eras, inputs
	## write tmp configs as needed
	## run 1D plots, 2D plots, and time fitter
	
	echo "Run code!"
	for var_pair in "${vars_map[@]}"
	do 
	    echo ${var_pair} | while read -r var fragment
	    do
	        ##########################
	        ## Set plot config (1D) ##
	        ##########################
		echo "Set plot config (1D)"
		while IFS='' read -r line || [[ -n "${line}" ]]
		do
		    if   [[ "${line}" == "var="* ]]
		    then
			x_var=$( ReadConfig "${line}" )
		    elif [[ "${line}" == "title="* ]]
		    then
			title=$( ReadConfig "${line}" )
		    elif [[ "${line}" == "bins="* ]]
		    then
			x_bins=$( ReadConfig "${line}" )
		    elif [[ "${line}" == "unit="* ]]
		    then
			unit=$( ReadConfig "${line}" )
		    elif [[ "${line}" == "ytitle="* ]]
		    then
			ytitle=$( ReadConfig "${line}" )
		    fi
		done < "${fragdir}/${fragment}.${inTextExt}"
	    
	        ## add in photon indices
		if   [[ "${var}" == *"_0" ]] 
		then
		    title="Leading ${title}"
		    x_var="${x_var}_0"
		elif [[ "${var}" == *"_1" ]]
		then
		    title="Subleading ${title}"
		    x_var="${x_var}_1"
		elif [[ "${var}" == *"_eff" ]]
		then
		    if [[ "${var}" == "A_eff" ]]
		    then
			title="${title}_{eff}/#sigma_{n}"
			xvar0="(phoseedE_0/phoseedadcToGeV_0)/phoseedpedrms12_0"
			xvar1="(phoseedE_1/phoseedadcToGeV_1)/phoseedpedrms12_1"
			x_var="((${xvar0}*${xvar1})/sqrt(pow(${xvar0},2)+pow(${xvar1},2)))"
		    else
			title="Effective ${title}"
			x_var="((${x_var}_0*${x_var}_1)/sqrt(pow(${x_var}_0,2)+pow(${x_var}_1,2)))"
		    fi
		elif [[ "${var}" == *"_delta" ]]
		then
		    title="#Delta(${title})"
		    x_var="${x_var}_0-${x_var}_1"
		fi
	
	        ## add units to title
		if [[ "${unit}" != "" ]]
		then
		    title+=" ${unit}"
		fi
	    
	        ##########################
	        ## Set plot config (2D) ##
	        ##########################
		echo "Set plot config (2D)"
		while IFS='' read -r line || [[ -n "${line}" ]]
		do
		    if   [[ "${line}" == "var="* ]]
		    then
			time_var=$( ReadConfig "${line}" )
		    elif [[ "${line}" == "title="* ]]
		    then
			time_title=$( ReadConfig "${line}" )
		    elif [[ "${line}" == "unit="* ]]
		    then
			time_unit=$( ReadConfig "${line}" )
		    elif [[ "${line}" == "bins="* ]]
		    then
			time_bins=$( ReadConfig "${line}" )
		    fi
		done < "${fragdir}/${base_time_var}.${inTextExt}"
		
	        ## add in photon indices
		time_var="${time_var}_0-${time_var}_1"
	
	        ## add delta and units to title
		time_title="#Delta(${time_title}) ${time_unit}"
	    
	        #####################
	        ## set corrections ##
	        #####################
		echo "set corrections"
		## deltaT first, single T after
		time_data_corr=""
		time_mc_corr=""
		data_corr=""
		mc_corr=""
	
		## tof
		if [[ "${usetof}" == "true" ]]
		then
		    time_tof_corr_delta="+(${tof_corr}_0-${tof_corr}_1)"
	
		    time_data_corr+="${time_tof_corr_delta}"
		    time_mc_corr+="${time_tof_corr_delta}"
	
		    if [[ "${var}" == "time_0" ]]
		    then
			tof_corr_0="+${tof_corr}_0"
	
			data_corr+="${tof_corr_0}"
			mc_corr+="${tof_corr_0}"
		    elif [[ "${var}" == "time_1" ]]
		    then
			tof_corr_1="+${tof_corr}_1"
	
			data_corr+="${tof_corr_1}"
			mc_corr+="${tof_corr_1}"
		    elif [[ "${var}" == "time_delta" ]]
		    then
			data_corr+="${time_tof_corr_delta}"
			mc_corr+="+${time_tof_corr_delta}"
		    fi
		fi
	
		## shift
		if [[ "${useshift}" == "true" ]]
		then
		    time_shift_corr_delta="+${shift_corr}_0-${shift_corr}_1"
	
		    time_data_corr+="${time_shift_corr_delta}"
		    time_mc_corr+="${time_shift_corr_delta}"
	
		    if [[ "${var}" == "time_0" ]]
		    then
			shift_corr_0="+${shift_corr}_0"
	
			data_corr+="${shift_corr_0}"
			mc_corr+="${shift_corr_0}"
		    elif [[ "${var}" == "time_1" ]]
		    then
			shift_corr_1="+${shift_corr}_1"
	
			data_corr+="${shift_corr_1}"
			mc_corr+="${shift_corr_1}"
		    elif [[ "${var}" == "time_delta" ]]
		    then
			data_corr+="${time_shift_corr_delta}"
			mc_corr+="+${time_shift_corr_delta}"
		    fi
		fi
	
		## smear
		if [[ "${usesmear}" == "true" ]]
		then
		    time_smear_corr_delta="+${smear_corr}_0-${smear_corr}_1"
	
		    time_mc_corr+="${time_smear_corr_delta}"
	
		    if [[ "${var}" == "time_0" ]]
		    then
			smear_corr_0="+${smear_corr}_0"
	
			mc_corr+="${smear_corr_0}"
		    elif [[ "${var}" == "time_1" ]]
		    then
			smear_corr_1="+${smear_corr}_1"
	
			mc_corr+="${smear_corr_1}"
		    elif [[ "${var}" == "time_delta" ]]
		    then
			mc_corr+="+${time_smear_corr_delta}"
		    fi
		fi
	    
	        ## loop over dieta regions
		echo "loop over dieta regions"
		for eta in "${dietas[@]}"
		do
		    ## only do Full detector for time plot only
		    if [[ "${eta}" == "Full" ]] && [[ "${var}" != "time_delta" ]]
		    then
			continue
		    fi
		    
		    #####################
		    ## make cut config ##
		    #####################
		    echo "make cut config"
		    cut="tmp_cut_config.txt"
		    > "${cut}"
	
		    ## eta cuts
	            eta_cut_base="phoisEB"
	            if [[ "${eta}" == "Full" ]]
	            then
			eta_cut="(1)"
	            elif [[ "${eta}" == "EBEB" ]]
	            then
			eta_cut="(${eta_cut_base}_0&&${eta_cut_base}_1)"
	            elif [[ "${eta}" == "EBEE" ]]
	            then
			eta_cut="((${eta_cut_base}_0&&!${eta_cut_base}_1)||(!${eta_cut_base}_0&&${eta_cut_base}_1))"
	            elif [[ "${eta}" == "EEEE" ]]
	            then
			eta_cut="(!${eta_cut_base}_0&&!${eta_cut_base}_1)"
		    else
			echo "How did this happen?? Did not choose a correct option for dieta: ${eta} ... Exiting..."
			exit
		    fi
		    
		    ## trigger tower cuts
		    if [[ "${triggertower}" == "Inclusive" ]]
		    then
			TT_cut="(1)"
		    elif [[ "${triggertower}" == "Same" ]]
		    then
			TT_cut="(phoseedTT_0==phoseedTT_1)"
		    elif [[ "${triggertower}" == "Different" ]]
		    then
			TT_cut="(phoseedTT_0!=phoseedTT_1)"
		    else
			echo "Yikes, triggertower cannot be: ${triggertower} ... Exiting..."
			exit
		    fi
	
		    ## write the remainder of cuts
		    echo "common_cut=${eta_cut}&&${TT_cut}" >> "${cut}"
		    echo "data_cut=${jwk_cut}" >> "${cut}"
		    echo "bkgd_cut=" >> "${cut}"
		    echo "sign_cut=" >> "${cut}"
		    
		    ###########################
	            ## make plot config (1D) ##
		    ###########################
		    echo "make plot config (1D)"
		    plot="tmp_${var}_${eta}.${inTextExt}"
		    > "${plot}"
		    
		    echo "plot_title=${title} (${eta})" >> "${plot}"
		    echo "x_title=${title} (${eta})" >> "${plot}"
		    echo "x_var=${x_var}" >> "${plot}"
		    echo "x_bins=${x_bins}" >> "${plot}"
		    echo "y_title=${ytitle}" >> "${plot}"
	
		    ###########################
	            ## make plot config (2D) ##
		    ###########################
		    echo "make plot config (2D)"
		    plot2D="tmp_deltaT_vs_${var}_${eta}.${inTextExt}"
		    > "${plot2D}"
	
		    echo "plot_title=${time_title} vs. ${title} (${eta})" >> "${plot2D}"
		    echo "x_title=${title} (${eta})" >> "${plot2D}"
		    echo "x_var=${x_var}" >> "${plot2D}"
		    echo "x_bins=${x_bins}" >> "${plot2D}"
		    echo "y_title=${time_title} (${eta})" >> "${plot2D}"
		    echo "y_var=${time_var}" >> "${plot2D}"
		    echo "y_bins=${time_bins}" >> "${plot2D}"       
		    
		    echo "y_var_data=${time_data_corr}" >> "${plot2D}"
		    echo "y_var_bkgd=${time_mc_corr}" >> "${plot2D}"
		    echo "y_var_sign=${time_mc_corr}" >> "${plot2D}"
		    
		    ## add corrections if plotting time --> currently disabled time_delta vs time_delta plot
		    if [[ "${var}" == "time"* ]]
		    then
			echo "x_var_data=${data_corr}" >> "${plot}"
			echo "x_var_bkgd=${mc_corr}" >> "${plot}"
			echo "x_var_sign=${mc_corr}" >> "${plot}"
			
			echo "x_var_data=${data_corr}" >> "${plot2D}"
			echo "x_var_bkgd=${mc_corr}" >> "${plot2D}"
			echo "x_var_sign=${mc_corr}" >> "${plot2D}"
		    fi
	
		    ######################################
		    ## determine which misc file to use ##
		    ######################################
	
		    misc=$( GetMisc ${input} ${plot} )
		    
		    #########################
		    ## make timefit config ##
		    #########################
		    echo "make timefit config"
		    timefit_config="tmp_timefit_config.${inTextExt}"
		    > "${timefit_config}"
		    
		    echo "time_text=t_{1}-t_{2}" >> "${timefit_config}"
		    echo ${fitinfo} | while read -r fittype rangelow rangeup
		    do
			echo "fit_type=${fittype}" >> "${timefit_config}"
			echo "range_low=${rangelow}" >> "${timefit_config}"
			echo "range_up=${rangeup}" >> "${timefit_config}"
		    done
		    
		    check_sigmafit=$( CheckVar ${var} "${sigmafit_vars[@]}" )
		    if [[ "${check_sigmafit}" == "true" ]]
		    then
			echo "do_sigma_fit=1" >> "${timefit_config}"
			echo "use_sqrt2=1" >> "${timefit_config}"
			    
			echo ${!var} | while read -r var_text var_unit N_low N_val N_up C_low C_val C_up
			do
			    echo "sigma_var_text=${var_text}" >> "${timefit_config}"
			    echo "sigma_var_unit=${var_unit}" >> "${timefit_config}"
			    echo "sigma_init_N_params=${N_low} ${N_val} ${N_up}" >> "${timefit_config}"
			    echo "sigma_init_C_params=${C_low} ${C_val} ${C_up}" >> "${timefit_config}"
			done
		    else
			echo "do_sigma_fit=0" >> "${timefit_config}"
		    fi
		    
		    ##############################
		    ## make misc timefit config ##
		    ##############################
	            echo "make misc timefit config"
		    misc_fit="tmp_misc_fit.${inTextExt}"
		    > "${misc_fit}"
	
		    check_logx=$( CheckVar ${var} "${logx_vars[@]}" )
		    if [[ "${check_logx}" == "true" ]]
		    then
			echo "do_logx=1" >> "${misc_fit}"
		    else
			echo "do_logx=0" >> "${misc_fit}"
		    fi
	
		    ####################
		    ## loop over eras ##
		    ####################
		    echo "loop over eras"
		    for era in "${eras[@]}"
		    do
			## skip if not needed to do all eras
			check_mualleras=$( CheckVar ${var} "${mualleras_vars[@]}" )
			if [[ "${check_mualleras}" != "true" ]] && [[ "${era}" != "Full" ]]
			then
			    echo "Mualleras check FAILED"
			    continue
			fi
			echo "Mualleras check Passed"		
			################################
			## loop over inputs: Zee only ##
			################################
			echo "loop over inputs: "
			for input in "${inputs[@]}"
			do echo ${!input} | while read -r label infile insigfile sel varwgtmap
			    do
	                 	## outfile names
				#outdir="${outdirbase}/${label}/${diphodir}/${eta}/${var}"
				outdir="${outdirbase}/${diphodir}_${ntcutname}_${ecutname}_${gdrcutname}/"
				outfile="${label}_${eta}_${era}"
                                kuoutfile="ku_${label}_${eta}_${era}"
				echo "OutFile: ${outdir} in ${outfile}"			
	
				## run 1D plotter
				jwk_plot="jwk_plot_configs/plot_difA_EBEB.txt"
                                jwk_ku_plot="jwk_plot_configs/plot_ku_difA_EBEB.txt"
				#echo "run 1D plotter"
				./scripts/runTreePlotter.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${outfile}" "${outdir}"
                                ./scripts/runTreePlotter.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_ku_plot}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "ku_${outfile}" "${outdir}"

				## run 2D plotter, passing 2D plots to make fits for all vars except vs time
				echo " run 2D plotter, passing 2D plots to make fits for all vars except vs time"
				if [[ "${var}" != "time_delta" ]]
				then
	                 	    ## extra outfile name
				    outfile2D="deltaT_vs_${outfile}"
                                    outfile_ku_2D="ku_deltaT_vs_${kuoutfile}"
				    timefile="timefit"
				    plot_ku_2D="tmp_ku_deltaT_vs_A_eff_EBEB.txt"
				    ## run 2D plotter
				    echo "run 2D plotter"
				#  makes base 2d plot for time fit
				echo "${skimdir}/${infile}.root"
				echo "${skimdir}/${insigfile}.root"
				echo "${cut}"
				echo "${varwgtconfigdir}/${varwgtmap}.${inTextExt}"
                                echo "${miscconfigdir}/${misc}.${inTextExt}"
                                echo "${era}"
                                echo "${outdir}"
                                echo "${misc_fit}"
                                echo "${timefit_config}"

				    ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${plot2D}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${outfile2D}" "${outdir}"
                                    ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${plot_ku_2D}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${outfile_ku_2D}" "${outdir}"

                                    jwk_plotkudifT="jwk_plot_configs/plot_difT_vs_kudifT_EBEB.txt"
                                    jwk_outfilekudifT="jwk_difT_v_kudifT_${outfile}"
                                    ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plotkudifT}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfilekudifT}" "${outdir}"
                                    rm ${jwk_outfilekudifT}.root

                                    jwk_plotkuTOF="jwk_plot_configs/plot_seedTOF_seedkuTOF.txt"
                                    jwk_outfilekuTOF="jwk_seedTOF_seedkuTOF_${outfile}"
                                    ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plotkuTOF}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfilekuTOF}" "${outdir}"
                                    rm ${jwk_outfilekuTOF}.root

                                    jwk_plotkuAeff="jwk_plot_configs/plot_difA_kudifA.txt"
                                    jwk_outfilekuAeff="jwk_difA_kudifA_${outfile}"
                                    ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plotkuAeff}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfilekuAeff}" "${outdir}"
                                    rm ${jwk_outfilekuAeff}.root

				    ## run fitter, getting 2D plots from before
				    echo "run fitter, getting 2D plots from before"
				    ./scripts/runTimeFitter.sh "${outfile2D}.root" "${plot2D}" "${misc_fit}" "${timefit_config}" "${era}" "${outfile}_${timefile}" "${outdir}"
                                    ./scripts/runTimeFitter.sh "${outfile_ku_2D}.root" "${plot_ku_2D}" "${misc_fit}" "${timefit_config}" "${era}" "${kuoutfile}_${timefile}" "${outdir}"
				fi ## end check over vars to fit
			        echo "end check over vars to fit"
			    done ## read input
			    echo "End read input"
			done ## loop over inputs:"
			echo "end input loop"
		    done ## loop over eras
		    echo "end eras loop"
		    ## remove tmp files
	#	    rm "${cut}" "${plot}" "${plot2D}" "${timefit_config}" "${misc_fit}"
		done ## loop over dieta
		echo "end dieta loop"
	    done ## read var_pair
	    echo "end var_pair loop"
	done ## loop over vars_map
	echo "end var_map loop"
done ## min E loop
echo "end min E loop"
done ## dR loop
echo "end dR loop"
done ## my cut loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
echo "end cut loop"
done ## my global local loop
echo "end global/local  loop"
done ## my tower loop
echo "end tower loop"
echo "end of script"
echo "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"

