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
usetof=${2:-"false"}
#usetof=${2:-"false"}
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
#run="2016deg"
#run="2017deg"
#run="2016G_deg_raw_part"
#run="2017B_deg_raw_part"
#run="2018eg"
run="2018A_eg_raw_315322"

loc="Local"
glo="Global"

#typelist="${loc}"
typelist="${glo}"
#typelist="${loc} ${glo}"

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
Zeeg="Global zee_skims/dispho_Zee_v4_eg2018A_raw_315322 skimmed/dispho_Zee_v2_2017B always_true"

#Zeel="Local dixtal_skims/dispho_DiXtal_v3_deg2017B_raw_part skimmed/dispho_Zee_v2_2017B always_true"
#Zeeg="Global zee_skims/dispho_Zee_v3_deg2017B_raw_part skimmed/dispho_Zee_v2_2017B always_true"

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
pho_cut="${fA}>250"
#pho_cut="1"

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
gdr_cut1="gdR<2.5"
gdr_cut2="gdR>=2.5"



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

gdrcutname0="FulldR"
gdrcutname1="dRlt25"
gdrcutname2="dRgt25"

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

        if [[ "${gdr_cut}" == ${gdr_cut0} ]]
        then
                gdrcutname=${gdrcutname0}
        elif [[ "${gdr_cut}" == ${gdr_cut1} ]]
        then
                gdrcutname=${gdrcutname1}
        elif [[ "${gdr_cut}" == ${gdr_cut2} ]]
        then
                gdrcutname=${gdrcutname2}
	fi

	echo "Working with ${nvxt_cut} ${cut_t} ${gdr_cut} in ${diphodir}"

	jwk_cut="${nvxt_cut}&&${E_cut}&&${pho_cut}&&${gdr_cut}"
	echo "Working with : ${jwk_cut}"
	
	## eta regions
#	declare -a dietas=("EBEB" "EBEE" "EEEE")
       declare -a dietas=("EBEB")
	
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
		    echo "data_cut=${jwk_cut}&&${pho_cut}" >> "${cut}"
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
				outdir="${outdirbase}/MyProfilePlots_${diphodir}_${ntcutname}_${ecutname}_${gdrcutname}/"
				outfile="${label}_${eta}_${era}"
				
				## run 1D plotter
				jwk_plot="jwk_plot_configs/plot_difA_EBEB.txt"
				#echo "run 1D plotter"

				## run 2D plotter, passing 2D plots to make fits for all vars except vs time
				echo " run 2D plotter, passing 2D plots to make fits for all vars except vs time"
				if [[ "${var}" != "time_delta" ]]
				then
	                 	    ## extra outfile name
				    outfile2D="deltaT_vs_${outfile}"
				    timefile="timefit"
				    ## run 2D plotter
				    echo "run 2D plotter"

                                    jwk_plot_52="jwk_plot_configs/plot_profile_ootamaf_dpst.txt"
                                    jwk_outfile52="jwk_ootamaf_dpst_${outfile}"
                                 #   ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_52}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile52}" "${outdir}"
                                    rm ${jwk_outfile52}.root			
                                    jwk_plot_53="jwk_plot_configs/plot_profile_ootamaf_dpst_signed.txt"
                                    jwk_outfile53="jwk_ootamaf_dpst_signed_${outfile}"
                                    ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_53}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile53}" "${outdir}"
                                    rm ${jwk_outfile53}.root
                                    jwk_plot_54="jwk_plot_configs/plot_profile_ootamaf_ootamaf.txt"
                                    jwk_outfile54="jwk_ootamaf_ootamaf_${outfile}"
                                  #  ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_54}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile54}" "${outdir}"
                                    rm ${jwk_outfile54}.root
                                    jwk_plot_55="jwk_plot_configs/plot_profile_ootamax_dpst.txt"
                                    jwk_outfile55="jwk_ootamax_dpst_${outfile}"
                                   # ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_55}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile55}" "${outdir}"
                                    rm ${jwk_outfile55}.root
                                    jwk_plot_56="jwk_plot_configs/plot_profile_ootamax_dpst_signed.txt"
                                    jwk_outfile56="jwk_ootamax_dpst_signed_${outfile}"
                                    ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_56}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile56}" "${outdir}"
                                    rm ${jwk_outfile56}.root
                                    jwk_plot_57="jwk_plot_configs/plot_profile_ootamax_ootamax.txt"
                                    jwk_outfile57="jwk_ootamax_ootamax_${outfile}"
                                    ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_57}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile57}" "${outdir}"
                                    rm ${jwk_outfile57}.root
                                    jwk_plot_58="jwk_plot_configs/plot_profile_ootambe_dpst.txt"
                                    jwk_outfile58="jwk_ootambe_dpst_${outfile}"
                                   # ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_58}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile58}" "${outdir}"
                                    rm ${jwk_outfile58}.root
                                    jwk_plot_59="jwk_plot_configs/plot_profile_ootambe_dpst_signed.txt"
                                    jwk_outfile59="jwk_ootambe_dpst_signed_${outfile}"
                                    ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_59}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile59}" "${outdir}"
                                    rm ${jwk_outfile59}.root
                                    jwk_plot_60="jwk_plot_configs/plot_profile_ootambe_ootambe.txt"
                                    jwk_outfile60="jwk_ootambe_ootambe_${outfile}"
                                   # ./scripts/runTreePlotter2D.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_60}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile60}" "${outdir}"
                                    jwk_plot_72="jwk_plot_configs/plot_ootMax.txt"
                                    jwk_outfile72="jwk_ootMax_${outfile}"
                                    ./scripts/runTreePlotter.sh "${skimdir}/${infile}.root" "${skimdir}/${insigfile}.root" "${cut}" "${varwgtconfigdir}/${varwgtmap}.${inTextExt}" "${jwk_plot_72}" "${miscconfigdir}/${misc}.${inTextExt}" "${era}" "${jwk_outfile72}" "${outdir}"
                                    rm ${jwk_outfile72}.root
				    ## run fitter, getting 2D plots from before
				    echo "run fitter, getting 2D plots from before"
	#			    ./scripts/runTimeFitter.sh "${outfile2D}.root" "${plot2D}" "${misc_fit}" "${timefit_config}" "${era}" "${outfile}_${timefile}" "${outdir}"

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

