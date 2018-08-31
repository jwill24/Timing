#!/bin/bash

## config
indir=${1}
outdir=${2}
filename=${3}
sumwgts=${4}
puwgtfilename=${5:-""}
skimtype=${6:-"Standard"}
redophoid=${7:-0}

## run macro
root -b -q -l runSkimmer.C\(\"${indir}\",\"${outdir}\",\"${filename}\",${sumwgts},\"${puwgtfilename}\",\"${skimtype}\",${redophoid}\)

## Final message
echo "Finished Skimming for file:" ${filename}
