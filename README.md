# Displaced Photon Analysis Framework. 

Update to README: this code has been modified to work with CMSSW_10_2_X and LHCInfo  

```
cmsrel CMSSW_10_2_5  
cd CMSSW_10_2_5/src  
cmsenv  
git cms-init  

git cms-merge-topic jwill24:Egamma_OOT_postRecoSeq   

git clone git@github.com:jwill24/Timing.git  
cd Timing  
git checkout 10_2_X  

scram b -j 10  
```

----------------

Use lhcInfoValid=True during cmsRun for eras containing LHCInfo




