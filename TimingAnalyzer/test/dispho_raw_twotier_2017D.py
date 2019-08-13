import os, re
import FWCore.ParameterSet.Config as cms
  
### CMSSW command line parameter parser
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('python')

## LHC Info
options.register('lhcInfoValid',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get lhc info');
options.register('rawCollectionsValid',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get digi/uncalRechit');
options.register('kuRechitValid',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get kuRechit');

#options.register('rlelist','events2018.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'Events to Process');
## blinding
options.register('blindSF',1000,VarParsing.multiplicity.singleton,VarParsing.varType.int,'pick every nth SF event');
options.register('applyBlindSF',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to apply event SF blinding');
options.register('blindMET',100.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'blind events greater than MET cut');
options.register('applyBlindMET',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to apply event MET blinding');

## object prep cuts
options.register('jetpTmin',15.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'jet pT minimum cut');
options.register('jetEtamax',3.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'jet eta maximum cut');
options.register('jetIDmin',1,VarParsing.multiplicity.singleton,VarParsing.varType.int,'jet ID minimum cut');
options.register('rhEmin',1.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'recHit energy minimum cut');
options.register('phpTmin',20.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'photon pT minimum cut');
options.register('phIDmin','none',VarParsing.multiplicity.singleton,VarParsing.varType.string,'photon ID minimum cut');

## object extra pruning cuts
options.register('seedTimemin',-25.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'photon seed time minimum cut');
options.register('nPhosmax',2,VarParsing.multiplicity.singleton,VarParsing.varType.int,'number of photons to clean jets');

## photon storing options
options.register('splitPho',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'store leading top two photons, OOT and GED');
options.register('onlyGED',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'store only leading GED photons, at most four');
options.register('onlyOOT',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'store only leading OOT photons, at most four');

## lepton prep cuts
options.register('ellowpTmin',20.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'electron low pT minimum cut');
options.register('elhighpTmin',50.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'electron high pT minimum cut');
options.register('mulowpTmin',20.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'muon low pT minimum cut');
options.register('muhighpTmin',50.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'muon high pT minimum cut');

## rechit storing options
options.register('storeRecHits',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'store all rechits above rhEmin');

## pre-selection cuts
options.register('applyTrigger',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to apply trigger pre-selection');
options.register('minHT',400.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'jet HT minimum cut');
options.register('applyHT',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to apply HT pre-selection');
options.register('phgoodpTmin',70.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'good photon pT minimum cut');
options.register('phgoodIDmin','loose',VarParsing.multiplicity.singleton,VarParsing.varType.string,'good photon ID minimum cut');
options.register('applyPhGood',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to require at least one good photon in pre-selection');

## matching cuts
options.register('dRmin',0.3,VarParsing.multiplicity.singleton,VarParsing.varType.float,'dR minimum cut');
options.register('pTres',100.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'pT resolution cut');
options.register('gendRmin',0.1,VarParsing.multiplicity.singleton,VarParsing.varType.float,'gen dR minimum cut');
options.register('genpTres',0.5,VarParsing.multiplicity.singleton,VarParsing.varType.float,'gen pT resolution cut');
options.register('trackdRmin',0.2,VarParsing.multiplicity.singleton,VarParsing.varType.float,'track dR minimum cut');
options.register('trackpTmin',5.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'track pT minimum cut');
options.register('genjetdRmin',0.2,VarParsing.multiplicity.singleton,VarParsing.varType.float,'genjet dR minimum cut for smearing');
options.register('genjetpTfactor',3.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'genjet pT resolution factor for smearing');
options.register('leptondRmin',0.3,VarParsing.multiplicity.singleton,VarParsing.varType.float,'lepton dR minimum cut for veto');

## Extra JER info
options.register('smearjetEmin',0.01,VarParsing.multiplicity.singleton,VarParsing.varType.float,'min jet E for smearing');

## trigger input
options.register('inputPaths','/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/HLTpathsWExtras.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input signal paths');
options.register('inputFilters','/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/HLTfilters.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input signal filters');

## met filter input
options.register('inputFlags','/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/METflags.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input MET filter flags');

## data or MC options
options.register('isMC',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate data or MC');
options.register('isGMSB',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate GMSB');
options.register('isHVDS',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate HVDS');
options.register('isBkgd',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate Background MC');
options.register('isToy',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate Toy MC');
options.register('isADD',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate ADD Monophoton');
options.register('xsec',1.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'cross section in pb');
options.register('filterEff',1.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'filter efficiency of MC');
options.register('BR',1.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'branching ratio of MC');

## GT to be used
options.register('globalTag','101X_dataRun2_Prompt_v11',VarParsing.multiplicity.singleton,VarParsing.varType.string,'gloabl tag to be used');

## do a demo run over only 1k events
options.register('demoMode',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to run over only 1k events');

## processName
options.register('processName','TREE',VarParsing.multiplicity.singleton,VarParsing.varType.string,'process name to be considered');

## outputFile Name
options.register('outputFileName','ku_multitest_twotier_run18D_323414_dispho.root',VarParsing.multiplicity.singleton,VarParsing.varType.string,'output file name created by cmsRun');

## etra bits
options.register('nThreads',8,VarParsing.multiplicity.singleton,VarParsing.varType.int,'number of threads per job');
options.register('deleteEarly',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'delete temp products early if not needed');
options.register('runUnscheduled',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'run unscheduled for products');

## parsing command line arguments
options.parseArguments()

if options.isGMSB or options.isHVDS or options.isBkgd or options.isToy or options.isADD: options.isMC = True

print "     ##### Settings ######"
#print "       -- Blinding --"
#print "blindSF        : ",options.blindSF
#print "applyBlindSF   : ",options.applyBlindSF
#print "blindMET       : ",options.blindMET
#print "applyBlindMET  : ",options.applyBlindMET
print "      -- Object Prep --"
print "jetpTmin       : ",options.jetpTmin
print "jetEtamax      : ",options.jetEtamax
print "jetIDmin       : ",options.jetIDmin
print "rhEmin         : ",options.rhEmin
print "phpTmin        : ",options.phpTmin
print "phIDmin        : ",options.phIDmin
print "     -- Extra Pruning --"
print "seedTimemin    : ",options.seedTimemin
print "nPhosmax       : ",options.nPhosmax
print "     -- Photon Storing --"
#print "splitPho       : ",options.splitPho
print "onlyGED        : ",options.onlyGED
#print "onlyOOT        : ",options.onlyOOT
print "      -- Lepton Prep --"
print "ellowpTmin     : ",options.ellowpTmin
print "elhighpTmin    : ",options.elhighpTmin
print "mulowpTmin     : ",options.mulowpTmin
print "muhighpTmin    : ",options.muhighpTmin
print "     -- RecHit Storing --"
print "storeRecHits   : ",options.storeRecHits
print "   -- Event Pre-Selection --"
print "applyTrigger   : ",options.applyTrigger
print "minHT          : ",options.minHT
print "applyHT        : ",options.applyHT
print "phgoodpTmin    : ",options.phgoodpTmin	
print "phgoodIDmin    : ",options.phgoodIDmin
print "applyPhGood    : ",options.applyPhGood	
print "        -- Matching --"
print "dRmin          : ",options.dRmin
print "pTres          : ",options.pTres
print "gendRmin       : ",options.gendRmin
print "genpTres       : ",options.genpTres
print "trackdRmin     : ",options.trackdRmin
print "trackpTmin     : ",options.trackpTmin
print "genjetdRmin    : ",options.genjetdRmin
print "genjetpTfactor : ",options.genjetpTfactor
print "leptondRmin    : ",options.leptondRmin
print "       -- Extra JER --"
print "smearjetEmin   : ",options.smearjetEmin
print "        -- Trigger --"
print "inputPaths     : ",options.inputPaths
print "inputFilters   : ",options.inputFilters
print "       -- MET Filters --"
print "inputFlags     : ",options.inputFlags
#print "        -- MC Info --"
#print "isMC           : ",options.isMC
if options.isMC:
	print "isGMSB         : ",options.isGMSB
	print "isHVDS         : ",options.isHVDS
	print "isBkgd         : ",options.isBkgd
	print "isToy          : ",options.isToy
	print "isADD          : ",options.isADD
	print "xsec           : ",options.xsec
	print "filterEff      : ",options.filterEff
	print "BR             : ",options.BR
print "           -- GT --"
print "globalTag      : ",options.globalTag	
print "         -- Output --"
#print "demoMode       : ",options.demoMode
print "processName    : ",options.processName	
print "outputFileName : ",options.outputFileName	
#print "        -- Extra bits --"
#print "nThreads       : ",options.nThreads
#print "runUnscheduled : ",options.runUnscheduled
#print "deleteEarly    : ",options.deleteEarly
print " "
print "LHC Info       : ",options.lhcInfoValid
print "rawCollections : ",options.rawCollectionsValid
print "kuRechit       : ",options.kuRechitValid
print "     #####################"

## Define the CMSSW process
from Configuration.StandardSequences.Eras import eras
process = cms.Process(options.processName,eras.Run2_2018)

## Load the standard set of configuration modules
process.load('Configuration.StandardSequences.Services_cff')
#process.load("Configuration.Geometry.GeometryRecoDB_cff")
#process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')

process.load("Geometry.CaloEventSetup.CaloTowerConstituents_cfi")
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Timing.TimingAnalyzer.jwk_ku_ecalLocalRecoSequence_cff')

#process.load('PhysicsTools.PatAlgos.slimming.metFilterPaths_cff')
#process.load('Configuration.StandardSequences.PAT_cff')
#process.load('Timing.TimingAnalyzer.jwk_PAT_cff')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('Configuration.StandardSequences.EndOfProcess_cff')

## Message Logger settings
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# LHC Info
process.LHCInfoReader = cms.ESSource("PoolDBESSource",
				     DBParameters = cms.PSet(
		messageLevel = cms.untracked.int32(0),
		authenticationPath = cms.untracked.string('')),
				     toGet = cms.VPSet( 
		cms.PSet(
			record = cms.string("LHCInfoRcd"),
			tag = cms.string("LHCInfoStartFillTest_v2")
			)
		),
				     connect = cms.string('frontier://FrontierPrep/CMS_CONDITIONS')
				     )

process.lhcinfo_prefer = cms.ESPrefer("PoolDBESSource","LHCInfoReader")


## Define the input source
#eventList = open(options.rlelist,'r')
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(#'file:jwk_reco_data_DIGI2RAW.root'),
	'/store/data/Run2017D/DoubleEG/MINIAOD/31Mar2018-v1/00000/A20F8F1B-4137-E811-A406-B083FED12B5C.root'
	#'file:rootSourceFiles/run2017D/miniaod/A20F8F1B-4137-E811-A406-B083FED12B5C.root'
        ),
    secondaryFileNames = cms.untracked.vstring(
	#323414

#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/DAC2DFF0-D997-E711-A34C-02163E0143AD.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/AA23A5AC-D297-E711-A984-02163E019C2D.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/9CFEC4E0-D497-E711-ABAC-02163E0142DA.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/8E7447D5-D297-E711-9FD3-02163E01A6FE.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/8C3CCEB5-D297-E711-9176-02163E01A4AB.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/625E43CB-D297-E711-B0E3-02163E01A516.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/58779778-DB97-E711-9BDD-02163E01A521.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/4CB2AEC2-D297-E711-9E14-02163E01A371.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/36BE6CCD-D297-E711-8D54-02163E019E1B.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/361700E4-D497-E711-B8B9-02163E019C43.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/1A117DB3-D297-E711-BF5F-02163E01A571.root',
        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/E6D783BA-D297-E711-9E48-02163E019DB9.root', # first 100 events
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/00BDA6C5-D297-E711-8A62-02163E01A50A.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/596/00000/F0667189-D896-E711-832E-02163E01A550.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/596/00000/C4293084-D896-E711-B007-02163E01A5C5.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/596/00000/88F70D92-D896-E711-82C9-02163E019D76.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/BE242B8A-D797-E711-A2D3-02163E011B46.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/5EC367A5-D797-E711-BDC4-02163E019C4F.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/424DBDAF-D797-E711-8D9E-02163E0140F1.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/0C4970B9-D797-E711-99B9-02163E01A637.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/484/00000/F491E3F9-6E94-E711-BAF5-02163E0141EE.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/484/00000/4E8B066B-6E94-E711-9D75-02163E0135A6.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/484/00000/32F2B665-6E94-E711-853D-02163E013728.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/5249E1A5-DE97-E711-9E87-02163E014209.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/1E2183B2-D797-E711-8442-02163E01470E.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/128E33A6-D797-E711-BFF5-02163E019D18.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/34CCF3B7-D297-E711-988D-02163E012BC7.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/0CBAC5A2-D297-E711-8D81-02163E012B20.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/F04E8394-D797-E711-BBFE-02163E01A76B.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/AE7C9CBC-D797-E711-AC72-02163E019BA4.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/9ADD3F8B-D797-E711-9693-02163E0138EE.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/E0A843DD-D497-E711-AAB3-02163E0141A8.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/6E9B2AC8-D297-E711-AF22-02163E019E52.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/634/00000/4A426FB5-D297-E711-8D2A-02163E014280.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/646/00000/00F6BE97-DC97-E711-9DFD-02163E01414C.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/98FB558B-D797-E711-A174-02163E019E74.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/5E65A4DF-D797-E711-A140-02163E01A26A.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/5A30D696-D797-E711-98FB-02163E012558.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/635/00000/00952BAF-D797-E711-A646-02163E019BB0.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/479/00000/DA3EC5B1-4C94-E711-8DDB-02163E019B44.root',
#        '/store/data/Run2017D/DoubleEG/RAW/v1/000/302/479/00000/AAA374AA-4C94-E711-952D-02163E0127F2.root'
#
#        'file:rootSourceFiles/run2017D/raw/00952BAF-D797-E711-A646-02163E019BB0.root',
#        'file:rootSourceFiles/run2017D/raw/00BDA6C5-D297-E711-8A62-02163E01A50A.root',
#        'file:rootSourceFiles/run2017D/raw/00F6BE97-DC97-E711-9DFD-02163E01414C.root',
#        'file:rootSourceFiles/run2017D/raw/0C4970B9-D797-E711-99B9-02163E01A637.root',
#        'file:rootSourceFiles/run2017D/raw/0CBAC5A2-D297-E711-8D81-02163E012B20.root',
#        'file:rootSourceFiles/run2017D/raw/128E33A6-D797-E711-BFF5-02163E019D18.root',
#        'file:rootSourceFiles/run2017D/raw/1A117DB3-D297-E711-BF5F-02163E01A571.root',
#        'file:rootSourceFiles/run2017D/raw/1E2183B2-D797-E711-8442-02163E01470E.root',
#        'file:rootSourceFiles/run2017D/raw/32F2B665-6E94-E711-853D-02163E013728.root',
#        'file:rootSourceFiles/run2017D/raw/34CCF3B7-D297-E711-988D-02163E012BC7.root',
#        'file:rootSourceFiles/run2017D/raw/361700E4-D497-E711-B8B9-02163E019C43.root',
#        'file:rootSourceFiles/run2017D/raw/36BE6CCD-D297-E711-8D54-02163E019E1B.root',
#        'file:rootSourceFiles/run2017D/raw/424DBDAF-D797-E711-8D9E-02163E0140F1.root',
#        'file:rootSourceFiles/run2017D/raw/4A426FB5-D297-E711-8D2A-02163E014280.root',
#        'file:rootSourceFiles/run2017D/raw/4CB2AEC2-D297-E711-9E14-02163E01A371.root',
#        'file:rootSourceFiles/run2017D/raw/4E8B066B-6E94-E711-9D75-02163E0135A6.root',
#        'file:rootSourceFiles/run2017D/raw/5249E1A5-DE97-E711-9E87-02163E014209.root',
#        'file:rootSourceFiles/run2017D/raw/58779778-DB97-E711-9BDD-02163E01A521.root',
#        'file:rootSourceFiles/run2017D/raw/5A30D696-D797-E711-98FB-02163E012558.root',
#        'file:rootSourceFiles/run2017D/raw/5E65A4DF-D797-E711-A140-02163E01A26A.root',
#        'file:rootSourceFiles/run2017D/raw/5EC367A5-D797-E711-BDC4-02163E019C4F.root',
#        'file:rootSourceFiles/run2017D/raw/625E43CB-D297-E711-B0E3-02163E01A516.root',
#        'file:rootSourceFiles/run2017D/raw/6E9B2AC8-D297-E711-AF22-02163E019E52.root',
#        'file:rootSourceFiles/run2017D/raw/88F70D92-D896-E711-82C9-02163E019D76.root',
#        'file:rootSourceFiles/run2017D/raw/8C3CCEB5-D297-E711-9176-02163E01A4AB.root',
#        'file:rootSourceFiles/run2017D/raw/8E7447D5-D297-E711-9FD3-02163E01A6FE.root',
#        'file:rootSourceFiles/run2017D/raw/98FB558B-D797-E711-A174-02163E019E74.root',
#        'file:rootSourceFiles/run2017D/raw/9ADD3F8B-D797-E711-9693-02163E0138EE.root',
#        'file:rootSourceFiles/run2017D/raw/9CFEC4E0-D497-E711-ABAC-02163E0142DA.root',
#        'file:rootSourceFiles/run2017D/raw/AA23A5AC-D297-E711-A984-02163E019C2D.root',
#        'file:rootSourceFiles/run2017D/raw/AAA374AA-4C94-E711-952D-02163E0127F2.root',
#        'file:rootSourceFiles/run2017D/raw/AE7C9CBC-D797-E711-AC72-02163E019BA4.root',
#        'file:rootSourceFiles/run2017D/raw/BE242B8A-D797-E711-A2D3-02163E011B46.root',
#        'file:rootSourceFiles/run2017D/raw/C4293084-D896-E711-B007-02163E01A5C5.root',
#        'file:rootSourceFiles/run2017D/raw/DA3EC5B1-4C94-E711-8DDB-02163E019B44.root',
#        'file:rootSourceFiles/run2017D/raw/DAC2DFF0-D997-E711-A34C-02163E0143AD.root',
#        'file:rootSourceFiles/run2017D/raw/E0A843DD-D497-E711-AAB3-02163E0141A8.root',
#        'file:rootSourceFiles/run2017D/raw/E6D783BA-D297-E711-9E48-02163E019DB9.root', # first 100 events
#        'file:rootSourceFiles/run2017D/raw/F04E8394-D797-E711-BBFE-02163E01A76B.root',
#        'file:rootSourceFiles/run2017D/raw/F0667189-D896-E711-832E-02163E01A550.root',
#        'file:rootSourceFiles/run2017D/raw/F491E3F9-6E94-E711-BAF5-02163E0141EE.root'
	),
    #eventsToProcess = cms.untracked.VEventRange(eventList)
)


## How many events to process
#if   options.demoMode : process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
#else                  : process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.maxEvents))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Set the global tag depending on the sample type
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag.globaltag = options.globalTag  

## Create output file
## Setup the service to make a ROOT TTree
process.TFileService = cms.Service("TFileService", 
		                   fileName = cms.string(options.outputFileName))
				   
## Decide which label to use for MET Flags
#if   options.isMC : triggerFlagsProcess = "PAT"
#else              : triggerFlagsProcess = "RECO"
triggerFlagsProcess = "RECO"

## generate track collection at miniAOD
from PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi import unpackedTracksAndVertices
process.unpackedTracksAndVertices = unpackedTracksAndVertices.clone()

# Make the tree 
process.tree = cms.EDAnalyzer("DisPho",
   ## additional collections
   kuRechitValid = cms.bool(options.kuRechitValid),
   rawCollectionsValid = cms.bool(options.rawCollectionsValid),
   ## LHC Info
   lhcInfoValid = cms.bool(options.lhcInfoValid),
   ## blinding 
   blindSF = cms.int32(options.blindSF),
   applyBlindSF = cms.bool(options.applyBlindSF),
   blindMET = cms.double(options.blindMET),
   applyBlindMET = cms.bool(options.applyBlindMET),
   ## object prep cuts
   jetpTmin  = cms.double(options.jetpTmin),
   jetEtamax = cms.double(options.jetEtamax),
   jetIDmin  = cms.int32(options.jetIDmin),
   rhEmin    = cms.double(options.rhEmin),
   phpTmin   = cms.double(options.phpTmin),
   phIDmin   = cms.string(options.phIDmin),
   ## extra object pruning
   seedTimemin = cms.double(options.seedTimemin),
   nPhosmax    = cms.int32(options.nPhosmax),
   ## photon storing options
   splitPho = cms.bool(options.splitPho),
   onlyGED  = cms.bool(options.onlyGED),
   onlyOOT  = cms.bool(options.onlyOOT),
   ## lepton prep cuts 
   ellowpTmin  = cms.double(options.ellowpTmin),
   elhighpTmin = cms.double(options.elhighpTmin),
   mulowpTmin  = cms.double(options.mulowpTmin),
   muhighpTmin = cms.double(options.muhighpTmin),
   ## recHit storing options
   storeRecHits = cms.bool(options.storeRecHits),
   ## pre-selection
   applyTrigger = cms.bool(options.applyTrigger),
   minHT        = cms.double(options.minHT),
   applyHT      = cms.bool(options.applyHT),
   phgoodpTmin  = cms.double(options.phgoodpTmin),
   phgoodIDmin  = cms.string(options.phgoodIDmin),
   applyPhGood  = cms.bool(options.applyPhGood),
   ## matched criteria
   dRmin = cms.double(options.dRmin),
   pTres = cms.double(options.pTres),
   gendRmin = cms.double(options.gendRmin),
   genpTres = cms.double(options.genpTres),
   trackdRmin = cms.double(options.trackdRmin),
   trackpTmin = cms.double(options.trackpTmin),
   genjetdRmin = cms.double(options.genjetdRmin),
   genjetpTfactor = cms.double(options.genjetpTfactor),
   leptondRmin = cms.double(options.leptondRmin),
   ## extra JER info
   smearjetEmin = cms.double(options.smearjetEmin),
   ## triggers
   inputPaths     = cms.string(options.inputPaths),
   inputFilters   = cms.string(options.inputFilters),
   triggerResults = cms.InputTag("TriggerResults", "", "HLT"),
   triggerObjects = cms.InputTag("slimmedPatTrigger"),
   ## met filters
   inputFlags       = cms.string(options.inputFlags),
   triggerFlags     = cms.InputTag("TriggerResults", "", triggerFlagsProcess),
   ecalBadCalibFlag = cms.InputTag("ecalBadCalibReducedMINIAODFilter"),			      
   ## tracks
   tracks = cms.InputTag("unpackedTracksAndVertices"),
   ## vertices
   vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
   ## rho
   rho = cms.InputTag("fixedGridRhoFastjetAll"), #fixedGridRhoAll
   ## METs
   #mets = cms.InputTag("slimmedMETsModifiedMET"),
   mets = cms.InputTag("slimmedMETs"),
   ## jets
   #jets = cms.InputTag("updatedPatJetsUpdatedJEC"),
   jets = cms.InputTag("slimmedJets"),
   ## electrons
   electrons = cms.InputTag("slimmedElectrons"),
   ## muons
   muons = cms.InputTag("slimmedMuons"),
   ## photons
   gedPhotons = cms.InputTag("slimmedPhotons"),
   ootPhotons = cms.InputTag("slimmedOOTPhotons"),

   ## ecal recHits
   recHitsEB = cms.InputTag("reducedEgamma", "reducedEBRecHits"),
   recHitsEE = cms.InputTag("reducedEgamma", "reducedEERecHits"),

   ## ecal kuRecHits
   kuRecHitsEB = cms.InputTag("kuEcalRecHit", "kuEcalRecHitsEB"),
   kuRecHitsEE = cms.InputTag("kuEcalRecHit", "kuEcalRecHitsEE"),

   kuStcRecHitsEB = cms.InputTag("kuStcEcalRecHit", "kuStcEcalRecHitsEB"),
   kuStcRecHitsEE = cms.InputTag("kuStcEcalRecHit", "kuStcEcalRecHitsEE"),

   kuNotRecHitsEB = cms.InputTag("kuNotEcalRecHit", "kuNotEcalRecHitsEB"),
   kuNotRecHitsEE = cms.InputTag("kuNotEcalRecHit", "kuNotEcalRecHitsEE"),

   kuNotStcRecHitsEB = cms.InputTag("kuNotStcEcalRecHit", "kuNotStcEcalRecHitsEB"),
   kuNotStcRecHitsEE = cms.InputTag("kuNotStcEcalRecHit", "kuNotStcEcalRecHitsEE"),

   ## ecal uncalib recHits
   uncalibratedRecHitsEB = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEB"),
   uncalibratedRecHitsEE = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEE"),

   ku_uncalibratedRecHitsEB = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEB"),
   ku_uncalibratedRecHitsEE = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEE"),

   kuNot_uncalibratedRecHitsEB = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEB"),
   kuNot_uncalibratedRecHitsEE = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEE"),

   ## digis
   EBdigiCollection = cms.InputTag("ecalDigis","ebDigis"),
   EEdigiCollection = cms.InputTag("ecalDigis","eeDigis"),

   ## gen info
   isGMSB       = cms.bool(options.isGMSB),
   isHVDS       = cms.bool(options.isHVDS),
   isBkgd       = cms.bool(options.isBkgd),
   isToy        = cms.bool(options.isToy),
   isADD        = cms.bool(options.isADD),
   xsec         = cms.double(options.xsec),
   filterEff    = cms.double(options.filterEff),
   BR           = cms.double(options.BR),
   genEvt       = cms.InputTag("generator"),
   gent0        = cms.InputTag("genParticles", "t0"),
   genxyz0      = cms.InputTag("genParticles", "xyz0"),
   pileups      = cms.InputTag("slimmedAddPileupInfo"),
   genParticles = cms.InputTag("prunedGenParticles"),
   genJets      = cms.InputTag("slimmedGenJets"),
)


# Set up the path
#process.treePath = cms.Path(
process.tree_step = cms.EndPath(
	process.unpackedTracksAndVertices +
	process.tree
)

process.jwk_digisunpacker = cms.Sequence(
				process.L1TRawToDigi+
				#siPixelDigis+
				#siStripDigis+
        			process.ecalDigis+
        			process.ecalPreshowerDigis#+
	                        #hcalDigis+
	                        #muonCSCDigis+
	                        #muonDTDigis+
	                        #muonRPCDigis+
	                      	#castorDigis+
	                      	#scalersRawToDigi+
	                      	#tcdsDigis+
	                      	#onlineMetaDataDigis
        			)

process.jwk_calolocalreco = cms.Sequence(
				#process.ku_min_ecalLocalRecoSequence
                                process.ku_multi_ecalLocalRecoSequence
                                #process.ku_ecalLocalRecoSequence
                                #process.ecalLocalRecoSequence
				#process.hcalLocalRecoSequence
				)

process.jwk_localreco = cms.Sequence(
				process.bunchSpacingProducer+
				#process.trackerlocalreco+
				#process.muonlocalreco+
				process.jwk_calolocalreco
				#process.castorreco
				)

process.jwk_highlevelreco = cms.Sequence(
			      #process.egammaHighLevelRecoPrePF*
                              #process.particleFlowReco*
                              #process.egammaHighLevelRecoPostPF*
                              #process.muoncosmichighlevelreco*
                              #process.muonshighlevelreco *
                              #process.particleFlowLinks*
                              #process.jetHighLevelReco*
                              #process.metrecoPlusHCALNoise*
                              #process.btagging*
                              #process.recoPFMET*
                              #process.PFTau*
                              #process.reducedRecHits #*
                              #process.cosmicDCTracksSeq
                             )

process.jwk_reconstruction = cms.Sequence(
				#process.localreco*
                                process.jwk_localreco*
				#process.globalreco*
				#process.jwk_highlevelreco*
				process.logErrorHarvester
)

process.content = cms.EDAnalyzer("EventContentAnalyzer")
process.content_step = cms.Path(process.content)

#process.raw2digi_step = cms.Path(process.RawToDigi)
process.ecalraw2digi_step = cms.Path(process.jwk_digisunpacker)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.jwk_reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)

process.schedule = cms.Schedule(
		#process.raw2digi_step,
		process.ecalraw2digi_step,
                process.L1Reco_step,
		process.reconstruction_step,
		#process.content_step,
		process.endjob_step,
		process.tree_step
)

### Extra bits from other configs
#process.options = cms.untracked.PSet(
#	numberOfThreads=cms.untracked.uint32(options.nThreads),
#	numberOfStreams=cms.untracked.uint32(options.nThreads/2)
#)
process.options = cms.untracked.PSet()

#process.schedule.associate(process.patTask)
#from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
#associatePatAlgosToolsTask(process)

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)

# customisation of the process.

# Automatic addition of the customisation function from PhysicsTools.PatAlgos.slimming.miniAOD_tools
#from Timing.TimingAnalyzer.jwk_miniAOD_tools import miniAOD_customizeAllData
#from PhysicsTools.PatAlgos.slimming.miniAOD_tools import miniAOD_customizeAllData

#call to customisation function miniAOD_customizeAllData imported from PhysicsTools.PatAlgos.slimming.miniAOD_tools
#process = miniAOD_customizeAllData(process)

# End of customisation functions

from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
if options.deleteEarly :
	process = customiseEarlyDelete(process)
