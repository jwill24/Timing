#!/bin/bash

infilename=${1:-"test.root"}
cutconfig=${2:-"cut_config/always_true.txt"}
plotconfig=${3:-"plot_config/phopt_0.txt"}
miscconfig=${4:-"plot_config/misc_blind.txt"}
outfiletext=${5:-"plots"}
dir=${6:-"plots/test"}

## first make plot
root -l -b -q runTreePlotter.C\(\"${infilename}\",\"${cutconfig}\",\"${plotconfig}\",\"${miscconfig}\",\"${outfiletext}\"\)

## make out dirs
topdir=/afs/cern.ch/user/k/kmcdermo/www
fulldir=${topdir}/dispho/${dir}

## make them readable
mkdir -p ${fulldir}
pushd ${topdir}
./makereadable.sh ${fulldir}
popd

## copy everything
cp ${outfiletext}_log.png ${outfiletext}_lin.png ${outfiletext}.root ${outfiletext}_integrals.txt ${fulldir}

## Final message
echo "Finished TreePlotting for plot:" ${plotconfig}
