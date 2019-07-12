# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: 
# 	jwk_reco_data -s RAW2DIGI,L1Reco,RECO,PAT --datatier RECO,MINIAOD --conditions 101X_dataRun2_Prompt_v11 --eventcontent RECO,MINIAOD --era Run2_2018 
#		--data --runUnscheduled -n 100 --no_exec

import os, re
import FWCore.ParameterSet.Config as cms

### CMSSW command line parameter parser
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('python')
print('Loading Options')
## LHC Info
options.register('lhcInfoValid',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get lhc info');
options.register('rlelist','events2018.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'Events to Process');
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
options.register('inputPaths','input/HLTpathsWExtras.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input signal paths');
options.register('inputFilters','input/HLTfilters.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input signal filters');

## met filter input
options.register('inputFlags','input/METflags.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input MET filter flags');

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
#options.register('globalTag','102X_dataRun2_Prompt_v11',VarParsing.multiplicity.singleton,VarParsing.varType.string,'gloabl tag to be used');
options.register('globalTag','102X_dataRun2_Sep2018Rereco_v1',VarParsing.multiplicity.singleton,VarParsing.varType.string,'gloabl tag to be used');
#options.register('globalTag','101X_dataRun2_Prompt_v11',VarParsing.multiplicity.singleton,VarParsing.varType.string,'gloabl tag to be used');

## do a demo run over only 1k events
#options.register('demoMode',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to run over only 1k events');
options.register('demoMode',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to run over only 1k events');

## processName
options.register('processName','TREE',VarParsing.multiplicity.singleton,VarParsing.varType.string,'process name to be considered');

## outputFile Name
options.register('outputFileName','very_short_kutest_run18D_dispho.root',VarParsing.multiplicity.singleton,VarParsing.varType.string,'output file name created by cmsRun');

## etra bits
#options.register('nThreads',8,VarParsing.multiplicity.singleton,VarParsing.varType.int,'number of threads per job');
options.register('deleteEarly',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'delete temp products early if not needed');
options.register('runUnscheduled',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'run unscheduled for products');

print('Parsing command line arguments')
## parsing command line arguments
options.parseArguments()

if options.isGMSB or options.isHVDS or options.isBkgd or options.isToy or options.isADD: options.isMC = True

print "     ##### Settings ######"
print "       -- Blinding --"
print "blindSF        : ",options.blindSF
print "applyBlindSF   : ",options.applyBlindSF
print "blindMET       : ",options.blindMET
print "applyBlindMET  : ",options.applyBlindMET
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
print "splitPho       : ",options.splitPho
print "onlyGED        : ",options.onlyGED
print "onlyOOT        : ",options.onlyOOT
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
print "        -- MC Info --"
print "isMC           : ",options.isMC
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
print "demoMode       : ",options.demoMode
print "processName    : ",options.processName	
print "outputFileName : ",options.outputFileName	
print "        -- Extra bits --"
#print "nThreads       : ",options.nThreads
print "runUnscheduled : ",options.runUnscheduled
print "deleteEarly    : ",options.deleteEarly
print " "
print "LHC Info       : ",options.lhcInfoValid

print "     #####################"

print("Defining Process")
## Define the CMSSW process
from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Run2_2018)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
#process.load('PhysicsTools.PatAlgos.slimming.metFilterPaths_cff')
#process.load('Configuration.StandardSequences.PAT_cff')
process.load('Timing.TimingAnalyzer.jwk_PAT_cff')
process.load('Timing.TimingAnalyzer.jwk_ku_ecalLocalRecoSequence_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load("Geometry.CaloEventSetup.CaloTowerConstituents_cfi")

process.maxEvents = cms.untracked.PSet(
#    input = cms.untracked.int32(5)
    input = cms.untracked.int32(20)
#    input = cms.untracked.int32(-1)
)

# Input source
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring('file:jwk_reco_data_DIGI2RAW.root'),
#    secondaryFileNames = cms.untracked.vstring()
#)

#eventList = open(options.rlelist,'r')
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(#'file:jwk_reco_data_DIGI2RAW.root'),
        #'/store/data/Run2018D/ZeroBias/RAW/v1/000/325/240/00000/FFA4CC2A-A63C-8440-ADC4-D7E2FF53BB4F.root'
	#'file:2E81C787-2D53-E811-BAFC-FA163E2CD5B1.root'
	'file:30F3675D-F89D-E811-8D66-FA163E884269.root'#run2018D
        #'/store/data/Run2018A/AlCaPhiSym/RAW/v1/000/315/318/00000/FEC219CA-264A-E811-BDD5-FA163E19DD9A.root'
	#'/store/data/Run2018A/EGamma/RAW/v1/000/315/973/00000/2E81C787-2D53-E811-BAFC-FA163E2CD5B1.root'
        ),
    secondaryFileNames = cms.untracked.vstring(),
#    eventsToProcess = cms.untracked.VEventRange(eventList)
)

process.options = cms.untracked.PSet(

)

# LHC Info
print('LHC Info reader')
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

# Message Logger settings
print('Message Logger settings')
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('jwk_reco_data nevts:all'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition
#print('Create RECO output file')
#process.RECOoutput = cms.OutputModule("PoolOutputModule",
#    dataset = cms.untracked.PSet(
#        dataTier = cms.untracked.string('RECO'),
#        filterName = cms.untracked.string('')
#    ),
#    fileName = cms.untracked.string('jwk_root_reco_data_RAW2DIGI_L1Reco_RECO_PAT.root'),
#    outputCommands = process.RECOEventContent.outputCommands,
#    splitLevel = cms.untracked.int32(0)
#)
#
#process.MINIAODoutput = cms.OutputModule("PoolOutputModule",
#    compressionAlgorithm = cms.untracked.string('LZMA'),
#    compressionLevel = cms.untracked.int32(4),
#    dataset = cms.untracked.PSet(
#        dataTier = cms.untracked.string('MINIAOD'),
#        filterName = cms.untracked.string('')
#    ),
#    dropMetaData = cms.untracked.string('ALL'),
#    eventAutoFlushCompressedSize = cms.untracked.int32(-900),
#    fastCloning = cms.untracked.bool(False),
#    fileName = cms.untracked.string('jwk_root_reco_data_RAW2DIGI_L1Reco_RECO_PAT_inMINIAOD.root'),
#    outputCommands = process.MINIAODEventContent.outputCommands,
#    overrideBranchesSplitLevel = cms.untracked.VPSet(
#        cms.untracked.PSet(
#            branch = cms.untracked.string('patPackedCandidates_packedPFCandidates__*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('recoGenParticles_prunedGenParticles__*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('patTriggerObjectStandAlones_slimmedPatTrigger__*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('patPackedGenParticles_packedGenParticles__*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('patJets_slimmedJets__*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('recoVertexs_offlineSlimmedPrimaryVertices__*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('recoCaloClusters_reducedEgamma_reducedESClusters_*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('EcalRecHitsSorted_reducedEgamma_reducedEBRecHits_*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('EcalRecHitsSorted_reducedEgamma_reducedEERecHits_*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('recoGenJets_slimmedGenJets__*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('patJets_slimmedJetsPuppi__*'),
#            splitLevel = cms.untracked.int32(99)
#        ), 
#        cms.untracked.PSet(
#            branch = cms.untracked.string('EcalRecHitsSorted_reducedEgamma_reducedESRecHits_*'),
#            splitLevel = cms.untracked.int32(99)
#        )
#    ),
#    overrideInputFileSplitLevels = cms.untracked.bool(True),
#    splitLevel = cms.untracked.int32(0)
#)

# Additional output definition

print('Create TTree output file')
## Create output file
## Setup the service to make a ROOT TTree
process.TFileService = cms.Service("TFileService", 
		                   fileName = cms.string(options.outputFileName))

print('Decide which label to use for MET Flags')
## Decide which label to use for MET Flags
if   options.isMC : triggerFlagsProcess = "PAT"
else              : triggerFlagsProcess = "RECO"

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '101X_dataRun2_Prompt_v11', '')

## generate track collection at miniAOD
from PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi import unpackedTracksAndVertices
process.unpackedTracksAndVertices = unpackedTracksAndVertices.clone()

#print('Apply IDs in pat::Photon')
## Apply IDs in pat::Photon
#from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
#setupEgammaPostRecoSeq(process,
#                       isMiniAOD=True,
#                       runVID=True,
#                       runEnergyCorrections=False, #as energy corrections are not yet availible for 2018
#                       era='2018-Prompt')


## Rerun one MET filter: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#How_to_run_ecal_BadCalibReducedM
baddetEcallist = cms.vuint32(
    [872439604,872422825,872420274,872423218,
     872423215,872416066,872435036,872439336,
     872420273,872436907,872420147,872439731,
     872436657,872420397,872439732,872439339,
     872439603,872422436,872439861,872437051,
     872437052,872420649,872422436,872421950,
     872437185,872422564,872421566,872421695,
     872421955,872421567,872437184,872421951,
     872421694,872437056,872437057,872437313])

process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter("EcalBadCalibFilter",
    EcalRecHitSource = cms.InputTag("reducedEgamma:reducedEERecHits"),
    ecalMinEt        = cms.double(50.),
    baddetEcal       = baddetEcallist,
    taggingMode      = cms.bool(True),
    debug            = cms.bool(False)
)


print('Setting up DisPho')
# Make the tree 
process.dispho = cms.EDAnalyzer("DisPho",
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
   ## pr-selection
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
   kuRecHitsEB = cms.InputTag("kuEcalRecHit", "kuEcalRecHitsEB"),
   kuRecHitsEE = cms.InputTag("kuEcalRecHit", "kuEcalRecHitsEE"),
   ## ecal uncalib recHits
   #uncalibratedRecHitsEB = cms.InputTag("ecalUncalibHitRatio","EcalUncalibRecHitsEB"),
   #uncalibratedRecHitsEE = cms.InputTag("ecalUncalibHitRatio","EcalUncalibRecHitsEE"),
   #uncalibratedRecHitsEB = cms.InputTag("ecalWeightUncalibRecHit","EcalUncalibRecHitsEB"),
   #uncalibratedRecHitsEE = cms.InputTag("ecalWeightUncalibRecHit","EcalUncalibRecHitsEE"),
   uncalibratedRecHitsEB = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEB"),
   uncalibratedRecHitsEE = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEE"),
   ## digis
   EBdigiCollection = cms.InputTag("ecalDigis","ebDigis"),
   EEdigiCollection = cms.InputTag("ecalDigis","eeDigis"),
   #ecalDigisEB = cms.InputTag("selectDigi","selectedEcalEBDigiCollection"),
   #ecalDigisEE = cms.InputTag("selectDigi","selectedEcalEEDigiCollection"),

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

#process.seq = cms.Sequence(
#   process.egammaPostRecoSeq
#)

print('Set up Path and EndPath Definitions')
# DisPho Path and EndPath definitions

process.ecalBadCalibReducedMINIAODFilter_step = cms.Path(process.ecalBadCalibReducedMINIAODFilter)

process.tree_step = cms.EndPath(
	#process.seq +
	##process.patJetCorrFactorsUpdatedJEC +
	##process.updatedPatJetsUpdatedJEC +
	##process.fullPatMetSequenceModifiedMET +
	#process.ecalBadCalibReducedMINIAODFilter +
	process.unpackedTracksAndVertices +
        process.dispho
)

process.jwk_calolocalreco = cms.Sequence(
				process.ku_ecalLocalRecoSequence+
				process.hcalLocalRecoSequence
				)

process.jwk_localreco = cms.Sequence(
				process.bunchSpacingProducer+
				process.trackerlocalreco+
				process.muonlocalreco+
				process.jwk_calolocalreco+
				process.castorreco
				)

process.jwk_highlevelreco = cms.Sequence(
			      process.egammaHighLevelRecoPrePF*
                              process.particleFlowReco*
                              process.egammaHighLevelRecoPostPF*
                              process.muoncosmichighlevelreco*
                              process.muonshighlevelreco *
                              process.particleFlowLinks*
                              process.jetHighLevelReco*
                              process.metrecoPlusHCALNoise*
                              process.btagging*
                              process.recoPFMET*
                              process.PFTau*
                              process.reducedRecHits #*
                              #process.cosmicDCTracksSeq
                             )

process.jwk_reconstruction = cms.Sequence(
#				process.localreco*
                                process.jwk_localreco*
				process.globalreco*
				process.jwk_highlevelreco*
				process.logErrorHarvester
)

process.ku_reconstruction = cms.Sequence(
                                process.localreco*
    				process.ku_supEcalLocalRecoSequence*
                                process.globalreco*
                                process.jwk_highlevelreco*
                                process.logErrorHarvester
)

process.content = cms.EDAnalyzer("EventContentAnalyzer")
process.content_step = cms.Path(process.content)

# RAW Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
#process.reconstruction_step = cms.Path(process.ku_reconstruction)
process.reconstruction_step = cms.Path(process.jwk_reconstruction)
#process.Flag_trackingFailureFilter = cms.Path(process.goodVertices+process.trackingFailureFilter)
#process.Flag_goodVertices = cms.Path(process.primaryVertexFilter)
#process.Flag_CSCTightHaloFilter = cms.Path(process.CSCTightHaloFilter)
#process.Flag_trkPOGFilters = cms.Path(process.trkPOGFilters)
#process.Flag_HcalStripHaloFilter = cms.Path(process.HcalStripHaloFilter)
#process.Flag_trkPOG_logErrorTooManyClusters = cms.Path(~process.logErrorTooManyClusters)
#process.Flag_EcalDeadCellTriggerPrimitiveFilter = cms.Path(process.EcalDeadCellTriggerPrimitiveFilter)
#process.Flag_ecalLaserCorrFilter = cms.Path(process.ecalLaserCorrFilter)
#process.Flag_globalSuperTightHalo2016Filter = cms.Path(process.globalSuperTightHalo2016Filter)
#process.Flag_eeBadScFilter = cms.Path(process.eeBadScFilter)
#process.Flag_METFilters = cms.Path(process.metFilters)
#process.Flag_chargedHadronTrackResolutionFilter = cms.Path(process.chargedHadronTrackResolutionFilter)
#process.Flag_globalTightHalo2016Filter = cms.Path(process.globalTightHalo2016Filter)
#process.Flag_CSCTightHaloTrkMuUnvetoFilter = cms.Path(process.CSCTightHaloTrkMuUnvetoFilter)
#process.Flag_HBHENoiseIsoFilter = cms.Path(process.HBHENoiseFilterResultProducer+process.HBHENoiseIsoFilter)
#process.Flag_BadChargedCandidateSummer16Filter = cms.Path(process.BadChargedCandidateSummer16Filter)
#process.Flag_hcalLaserEventFilter = cms.Path(process.hcalLaserEventFilter)
#process.Flag_BadPFMuonFilter = cms.Path(process.BadPFMuonFilter)
#process.Flag_ecalBadCalibFilter = cms.Path(process.ecalBadCalibFilter)
#process.Flag_HBHENoiseFilter = cms.Path(process.HBHENoiseFilterResultProducer+process.HBHENoiseFilter)
#process.Flag_trkPOG_toomanystripclus53X = cms.Path(~process.toomanystripclus53X)
#process.Flag_EcalDeadCellBoundaryEnergyFilter = cms.Path(process.EcalDeadCellBoundaryEnergyFilter)
#process.Flag_BadChargedCandidateFilter = cms.Path(process.BadChargedCandidateFilter)
#process.Flag_trkPOG_manystripclus53X = cms.Path(~process.manystripclus53X)
#process.Flag_BadPFMuonSummer16Filter = cms.Path(process.BadPFMuonSummer16Filter)
#process.Flag_muonBadTrackFilter = cms.Path(process.muonBadTrackFilter)
#process.Flag_CSCTightHalo2015Filter = cms.Path(process.CSCTightHalo2015Filter)
process.endjob_step = cms.EndPath(process.endOfProcess)
#process.RECOoutput_step = cms.EndPath(process.RECOoutput)
#process.MINIAODoutput_step = cms.EndPath(process.MINIAODoutput)

# Schedule definition
process.schedule = cms.Schedule(
		#process.content_step,
		process.raw2digi_step,
		process.L1Reco_step,
		process.reconstruction_step,
		#process.ecalBadCalibReducedMINIAODFilter_step,
		process.endjob_step,
		process.tree_step,
		#process.RECOoutput_step
)

#process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.Flag_HBHENoiseFilter,process.Flag_HBHENoiseIsoFilter,process.Flag_CSCTightHaloFilter,process.Flag_CSCTightHaloTrkMuUnvetoFilter,process.Flag_CSCTightHalo2015Filter,process.Flag_globalTightHalo2016Filter,process.Flag_globalSuperTightHalo2016Filter,process.Flag_HcalStripHaloFilter,process.Flag_hcalLaserEventFilter,process.Flag_EcalDeadCellTriggerPrimitiveFilter,process.Flag_EcalDeadCellBoundaryEnergyFilter,process.Flag_ecalBadCalibFilter,process.Flag_goodVertices,process.Flag_eeBadScFilter,process.Flag_ecalLaserCorrFilter,process.Flag_trkPOGFilters,process.Flag_chargedHadronTrackResolutionFilter,process.Flag_muonBadTrackFilter,process.Flag_BadChargedCandidateFilter,process.Flag_BadPFMuonFilter,process.Flag_BadChargedCandidateSummer16Filter,process.Flag_BadPFMuonSummer16Filter,process.Flag_trkPOG_manystripclus53X,process.Flag_trkPOG_toomanystripclus53X,process.Flag_trkPOG_logErrorTooManyClusters,process.Flag_METFilters,process.pretree_step,process.endjob_step,process.RECOoutput_step,process.tree_step)

process.schedule.associate(process.patTask)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)

# customisation of the process.

# Automatic addition of the customisation function from PhysicsTools.PatAlgos.slimming.miniAOD_tools
#from PhysicsTools.PatAlgos.slimming.miniAOD_tools import miniAOD_customizeAllData
from Timing.TimingAnalyzer.jwk_miniAOD_tools import miniAOD_customizeAllData 

#call to customisation function miniAOD_customizeAllData imported from PhysicsTools.PatAlgos.slimming.miniAOD_tools
process = miniAOD_customizeAllData(process)

# End of customisation functions

# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion

### Extra bits from other configs
#process.options = cms.untracked.PSet(
#        numberOfThreads=cms.untracked.uint32(options.nThreads),
#        numberOfStreams=cms.untracked.uint32(options.nThreads/2)
#)


