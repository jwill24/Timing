from CRABClient.UserUtilities import config
config = config()

# External files needed by CRAB
inputDir     = '/afs/cern.ch/work/j/juwillia/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
inputPaths   = 'HLTpathsWExtras.txt'
inputFilters = 'HLTfilters.txt'
inputFlags   = 'METflags.txt'

config.General.workArea      = 'workArea'
config.General.requestName   = 'disphoTest19'

config.JobType.pluginName    = 'Analysis'
config.JobType.psetName      = 'disphoNew.py'
config.JobType.numCores      = 8
config.JobType.maxMemoryMB   = 4000
config.JobType.inputFiles    = [ inputDir+inputPaths , inputDir+inputFilters , inputDir+inputFlags ]
config.JobType.pyCfgParams   = ['globalTag=101X_dataRun2_Prompt_v10','storeRecHits=True','onlyGED=True','lhcInfoValid=False','nThreads='+str(config.JobType.numCores)]

config.Data.inputDBS         = 'global'
config.Data.inputDataset     = '/EGamma/Run2018B-PromptReco-v1/MINIAOD'
config.Data.secondaryInputDataset = '/EGamma/Run2018B-v1/RAW'
config.Data.splitting        = 'EventAwareLumiBased'
config.Data.unitsPerJob      = 10
config.Data.totalUnits       = 10

config.Data.outputDatasetTag = 'ecalTiming'
config.Data.publication      = False
config.Site.storageSite      = 'T2_CH_CERN'
config.Data.outLFNDirBase    = '/store/group/phys_exotica/PPS-Diphoton/juwillia/'

config.Data.lumiMask         = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
