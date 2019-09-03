# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: -s RAW2DIGI,L1Reco,RECO --data --scenario pp --conditions 101X_dataRun2_Express_v7 --era Run2_2018 --eventcontent RECO --datatier RECO --filein /store/express/Run2018A/ExpressPhysics/FEVT/Express-v1/000/315/689/00000/0006526E-0A4F-E811-9FEC-FA163E735BE1.root --python_filename=Data_101X_cfg.py --runUnscheduled -n 10 --no_exec

orbit_begin_array = [0]
orbit_end_array = [1434229500]
index = 0

import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
process = cms.Process('NTUPLE',eras.Run2_2018)

#--------------------------------------------------------------------------------------------------
import FWCore.ParameterSet.VarParsing as opts
opt = opts.VarParsing ('analysis')
opt.register('dataTier',           'RAW',
	     opts.VarParsing.multiplicity.singleton, opts.VarParsing.varType.string,
	     'Input data tier: RAW, RECO, FEVT or AOD')

opt.register('inputFile',          '',
	     opts.VarParsing.multiplicity.singleton, opts.VarParsing.varType.string,
	     'input file name')

opt.register('secondaryInputFile', '',
	     opts.VarParsing.multiplicity.singleton, opts.VarParsing.varType.string,
	     'input file name')

opt.register('Efficiency',         True,
	     opts.VarParsing.multiplicity.singleton, opts.VarParsing.varType.bool,
	     'Specify if you want to create Efficiency (TimingStudy) ntuples')

opt.register('LATrees',            True,
	     opts.VarParsing.multiplicity.singleton, opts.VarParsing.varType.bool,
	     'Specify if you want to create Lorentz Angle (SiPixelLorentzAngle) ntuples')

opt.register('BPixResolution',     True,
	     opts.VarParsing.multiplicity.singleton, opts.VarParsing.varType.bool,
	     'Specify if you want to create BPix Resolution (Pxl) ntuples')

opt.register('FPixResolution',     True,
	     opts.VarParsing.multiplicity.singleton, opts.VarParsing.varType.bool,
	     'Specify if you want to create FPix Resolution (Pixel) ntuples')


### Events to process: 'maxEvents' is already registered by the framework
#opt.setDefault('maxEvents', 10)
opt.parseArguments()

# input tracks
# Refitter
process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
trackInput = 'generalTracks'
if opt.dataTier == 'RECO' or opt.dataTier == 'FEVT' or opt.dataTier == 'RAW':
    trackInput = 'TrackRefitter'
    process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
    process.TrackRefitter_step = cms.Path(process.MeasurementTrackerEvent*process.TrackRefitter)

#------------------------------------------
#  Define your Analyzer(s) here
#------------------------------------------

# Efficiency

process.PhaseINtuplizerPlugin = cms.EDAnalyzer("PhaseIPixelNtuplizer",
     trajectoryInput = cms.InputTag('TrackRefitter'),
      outputFileName = cms.untracked.string('Efficiency.root'),
      # Do not save everything and downscale clusters
      clusterSaveDownscaleFactor     = cms.untracked.int32(10000),
      #eventSaveDownscaleFactor       = cms.untracked.int32(opt.prescale),
      eventSaveDownscaleFactor       = cms.untracked.int32(100),
      saveDigiTree                   = cms.untracked.bool(False),
      aveTrackTree                  = cms.untracked.bool(False),
      saveNonPropagatedExtraTrajTree = cms.untracked.bool(False),  
)

# Lorentz Angle
process.SiPixelLorentzAngle = cms.EDAnalyzer("SiPixelLorentzAngle",
        src = cms.InputTag(trackInput),
        fileName = cms.string('LA.root'),
        fileNameFit     = cms.string(""),
        binsDepth       = cms.int32(50),
        binsDrift =     cms.int32(200),
        ptMin = cms.double(3),
        ptMinFPix = cms.double(0.1),
        #in case of MC set this to true to save the simhits (does not work currently, Mixing Module needs to be included correctly)
        simData = cms.bool(False),
        normChi2Max = cms.double(2),
        clustSizeYMin = cms.int32(2),
        residualMax = cms.double(0.01),
        clustChargeMax = cms.double(120000)
)

# BPix Resolution
process.BPixResolution_Template = cms.EDAnalyzer('Pixel',
        triggerSource = cms.InputTag('TriggerResults::HLT'),
        ttrhBuilder = cms.string('WithAngleAndTemplate'),
        orbit_beginning = cms.int32(orbit_begin_array[index]),
        orbit_end = cms.int32(orbit_end_array[index]),
        )

process.BPixResolution_Generic = process.BPixResolution_Template.clone(
    ttrhBuilder = cms.string('WithTrackAngle'),
    orbit_beginning = cms.int32(orbit_begin_array[index]),
    orbit_end = cms.int32(orbit_end_array[index]),
)

# FPix Resolution
process.FPixResolution_Template = cms.EDAnalyzer('Pixel_phase1',
    triggerSource = cms.InputTag('TriggerResults::HLT'),
    ttrhBuilder = cms.string('WithAngleAndTemplate'),
    doBPix = cms.bool(False),
    doFPix = cms.bool(True),
    orbit_beginning = cms.int32(orbit_begin_array[index]),
    orbit_end = cms.int32(orbit_end_array[index]),
)
process.FPixResolution_Generic = process.FPixResolution_Template.clone(
    ttrhBuilder = cms.string('WithTrackAngle'),
    orbit_beginning = cms.int32(orbit_begin_array[index]),
    orbit_end = cms.int32(orbit_end_array[index]),
)

# TFileService used for both BPix/FPix resolution
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('Resolution.root'),
)


# Paths
process.PhaseIPixelNtuplizer_step = cms.Path(process.PhaseINtuplizerPlugin)
process.Efficiency_step = cms.Path(process.PhaseINtuplizerPlugin)

#process.Efficiency_step     = cms.Path(process.TimingStudy)
#process.LATrees_step        = cms.Path(process.SiPixelLorentzAngle)
#process.BPixResolution_step = cms.Path(process.BPixResolution_Template*process.BPixResolution_Generic)
#process.FPixResolution_step = cms.Path(process.FPixResolution_Template*process.FPixResolution_Generic)

#------------------------------------------
#  Configurations from cmsDriver.py
#------------------------------------------

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
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# number of events to run on
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)        
)

# MessageLogger
process.MessageLogger.cerr.FwkReport.reportEvery = 10 if opt.dataTier == 'RAW' else 100

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       # '/store/express/Run2018A/ExpressPhysics/FEVT/Express-v1/000/315/689/00000/0006526E-0A4F-E811-9FEC-FA163E735BE1.root'
        #'/store/express/Run2018B/ExpressPhysics/FEVT/Express-v1/000/318/816/00000/685DE116-517A-E811-9338-A4BF0114D040.root'
        #'/store/data/Run2018D/ZeroBias/RAW/v1/000/321/149/00000/40ADBB3F-B79D-E811-B5A6-FA163EF9728B.root' 
         '/store/data/Run2018B/ZeroBias/RAW/v1/000/318/816/00000/D411217A-517A-E811-96D4-FA163E2FE8B3.root'   
        ),
                            )

if opt.secondaryInputFile != '':
    process.source.secondaryFileNames = cms.untracked.vstring(opt.secondaryInputFile)
    
process.options = cms.untracked.PSet(

)

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_v5_preUL', '')

#------------------ LOCAL CONDITIONS

process.GlobalTag.toGet = cms.VPSet(
#    cms.PSet(record = cms.string('SiPixelTemplateDBObjectRcd'),
#             tag = cms.string('SiPixelTemplateDBObject_phase1_38T_2018_v8'),
#             connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
#             ),
#    cms.PSet(record = cms.string('SiPixelGenErrorDBObjectRcd'),
#             tag = cms.string('SiPixelGenErrorDBObject_phase1_38T_2018_v8'),
#             connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
#             ),
#    cms.PSet(record = cms.string('SiPixelLorentzAngleRcd'),
#             tag = cms.string('SiPixelLorentzAngle_phase1_2018_v8'),
#             connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
#             ),
#    cms.PSet(record = cms.string('TrackerAlignmentRcd'),
#             tag = cms.string('TrackerAlignment_PostMD2_v3'),
#             connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
#             ),    
    cms.PSet(record = cms.string('SiPixelQualityFromDbRcd'),
             tag = cms.string('SiPixelQuality_byPCL_prompt_v2'),
             connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
             ),  
    )

#------------------------------------------------------------------------------
# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)

# Schedule definition
if opt.dataTier == 'RECO' or opt.dataTier == 'FEVT':
    process.schedule = cms.Schedule()
else:
    process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step)

# Add TrackRef tter if needed
trackInput == 'TrackRefitter'
if trackInput == 'TrackRefitter': process.schedule.append(process.TrackRefitter_step)
# Add ntuplizers
if opt.Efficiency:     process.schedule.append(process.Efficiency_step)
#if opt.LATrees:        process.schedule.append(process.LATrees_step)
#if opt.BPixResolution: process.schedule.append(process.BPixResolution_step)
#if opt.FPixResolution: process.schedule.append(process.FPixResolution_step)


# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('-s nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    #fileName = cms.untracked.string('-s_RAW2DIGI_L1Reco_RECO.root'),
    fileName = cms.untracked.string('RECO.root'),
    outputCommands = process.RECOEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)
process.schedule.append(process.endjob_step)
#process.schedule.append(process.RECOoutput_step)


# Additional output definition

# Other statements
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '101X_dataRun2_Express_v7', '')

# Path and EndPath definitions
#process.raw2digi_step = cms.Path(process.RawToDigi)
##process.L1Reco_step = cms.Path(process.L1Reco)
#process.reconstruction_step = cms.Path(process.reconstruction)

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,p#rocess.endjob_step,process.RECOoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)


# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
