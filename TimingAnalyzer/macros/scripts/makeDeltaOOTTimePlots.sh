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

#MyProfilePlots_Global_Inclusive_Run2018A_eg_raw_315322_None_Emin10_FulldR
inrootdir="~/ecaltiming/dispho_plots/dispho_plots/MyProfilePlots_Global_Inclusive_Run2018A_eg_raw_315322_None_Emin10_FulldR/"
misc_fit="tmp_configs/tmp_misc_fit.txt"
timefit_config="tmp_configs/tmp_timefit_config.txt"

## run fitter, getting 2D plots from befo
echo "run fitter, getting 2D plots from before"

inrootfile="${inrootdir}jwk_ootamax_dpst_Global_EBEB_Full"
plot2D="jwk_plot_configs/plot_profile_ootamax_dpst.txt"
#./scripts/runTimeFitter.sh "${inrootfile}.root" "${plot2D}" "${misc_fit}" "${timefit_config}" "EBEB" "ootAmax_timefit" "dispho_plots/ootProfiles"
inrootfile="${inrootdir}jwk_ootamaf_dpst_Global_EBEB_Full"
plot2D="jwk_plot_configs/plot_profile_ootamaf_dpst.txt"
#./scripts/runTimeFitter.sh "${inrootfile}.root" "${plot2D}" "${misc_fit}" "${timefit_config}" "EBEB" "ootAmaf_timefit" "dispho_plots/ootProfiles"
inrootfile="${inrootdir}jwk_ootambe_dpst_Global_EBEB_Full"
plot2D="jwk_plot_configs/plot_profile_ootambe_dpst.txt"
#./scripts/runTimeFitter.sh "${inrootfile}.root" "${plot2D}" "${misc_fit}" "${timefit_config}" "EBEB" "ootAmbe_timefit" "dispho_plots/ootProfiles"
inrootfile="${inrootdir}jwk_ootamax_dpst_signed_Global_EBEB_Full"
plot2D="jwk_plot_configs/plot_profile_ootamax_dpst_signed.txt"
./scripts/runTimeFitter.sh "${inrootfile}.root" "${plot2D}" "${misc_fit}" "${timefit_config}" "EBEB" "ootAmax_signed_timefit" "dispho_plots/ootProfiles"
inrootfile="${inrootdir}jwk_ootamaf_dpst_signed_Global_EBEB_Full"
plot2D="jwk_plot_configs/plot_profile_ootamaf_dpst_signed.txt"
./scripts/runTimeFitter.sh "${inrootfile}.root" "${plot2D}" "${misc_fit}" "${timefit_config}" "EBEB" "ootAmaf_signed_timefit" "dispho_plots/ootProfiles"
inrootfile="${inrootdir}jwk_ootambe_dpst_signed_Global_EBEB_Full"
plot2D="jwk_plot_configs/plot_profile_ootambe_dpst_signed.txt"
./scripts/runTimeFitter.sh "${inrootfile}.root" "${plot2D}" "${misc_fit}" "${timefit_config}" "EBEB" "ootAmbe_signed_timefit" "dispho_plots/ootProfiles"

echo "end of script"

