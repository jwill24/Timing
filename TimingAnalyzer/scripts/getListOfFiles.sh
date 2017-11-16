#!/bin/bash

label=${1}
outdir=${2:-"files"}

mkdir -p ${outdir}

## Data first
dataset="SinglePhoton"
for subera in "B v1" "B v2" "C v1" "C v2" "C v3" "D v1" "E v1" "F v1"
do echo ${subera} | while read -r era version
    do
	./scripts/getListOfFilesData.sh ${label} ${outdir} ${dataset} ${era} ${version}
    done
done

## QCD second
qcdtune="EMEnriched_TuneCUETP8M1_13TeV_pythia8"
for bin in "15to20" "20to30" "30to50" "50to80" "80to120" "120to170" "170to300"
do
    dataset="QCD_Pt-"${bin}
    ./scripts/getListOfFilesMC.sh ${label}_Bkgd ${outdir} ${dataset} ${qcdtune}
done

## GJets
dataset="GJet"
gjettune="DoubleEMEnriched_13TeV_pythia8"
./scripts/getListOfFilesMC.sh ${label}_Bkgd ${outdir} ${dataset} ${gjettune}

## GMSB
dataset="GMSB"
gmsbtune="L200TeV_CTau400cm_930"
./scripts/getListOfFilesMC.sh ${label}_Signal ${outdir} ${dataset} ${gmsbtune}