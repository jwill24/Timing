import os, re
import FWCore.ParameterSet.Config as cms
  
print("### CMSSW command line parameter parser")
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('python')
options.register('globalTag','101X_dataRun2_Prompt_v11',VarParsing.multiplicity.singleton,VarParsing.varType.string,'gloabl tag to be used');
options.register('processName','EgammaDump',VarParsing.multiplicity.singleton,VarParsing.varType.string,'process name to be considered');
options.register('outputFileName','alcap0_dump.root',VarParsing.multiplicity.singleton,VarParsing.varType.string,'output file name created by cmsRun');
#options.register('deleteEarly',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'delete temp products early if not needed');
#options.register('runUnscheduled',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'run unscheduled for products');

## parsing command line arguments
options.parseArguments()

print("## Define the CMSSW process")
process = cms.Process(options.processName)

## Load the standard set of configuration modules
#process.load("Configuration.Geometry.GeometryRecoDB_cff")
#process.load('Configuration.StandardSequences.Services_cff')
#process.load('Configuration.StandardSequences.GeometryDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#process.load("Geometry.CaloEventSetup.CaloTowerConstituents_cfi")

print("## Message Logger settings")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 100000

print("## Define the input source")
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:0A8A8823-854B-E811-BA99-FA163EC4A708.root' # alcareco phi0 2018
        ),
    secondaryFileNames = cms.untracked.vstring(),
)


print("## How many events to process")
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

print("# Set the global tag depending on the sample type")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag.globaltag = options.globalTag  

## Create output file
## Setup the service to make a ROOT TTree
process.TFileService = cms.Service("TFileService", 
		                   fileName = cms.string(options.outputFileName))
				   
print("# Make the tree") 
process.egammaana = cms.EDAnalyzer("alcap0_ana",
	stage2CaloLayer2EGammaProducer = cms.InputTag("hltGtStage2Digis","EGamma")
)


print("# Set up the path")
process.treePath = cms.Path(
	process.egammaana
)


#from FWCore.ParameterSet.Utilities import convertToUnscheduled
#if options.runUnscheduled : 
#	process = convertToUnscheduled(process)

#from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
#if options.deleteEarly:
#	process = customiseEarlyDelete(process)
