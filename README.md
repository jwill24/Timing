# Displaced Photon Analysis Framework

Update to README: this code has been modified to work with CMSSW_10_2_X
Code belongs to kmcdermo/Timing

cmsrel CMSSW_10_2_5
cd CMSSW_10_2_5/src
cmsenv
git cms-init

git cms-merge-topic cms-egamma:EgammaID_1023
git cms-merge-topic cms-egamma:EgammaPostRecoTools

Two lines need to be edited in RecoEgamma/EgammaTools/python/EgammaPostRecoTools.py
Comment out lines 240 and 242
Add the following lines:
phoSrc = cms.InputTag('slimmedOOTPhotons',processName=cms.InputTag.skipCurrentProcess())
phoCalibSrc = cms.InputTag('slimmedOOTPhotons',processName=cms.InputTag.skipCurrentProcess())

git clone git@github.com:jwill24/Timing.git
cd Timing
git checkout 10_2_X

scram b -j 10




