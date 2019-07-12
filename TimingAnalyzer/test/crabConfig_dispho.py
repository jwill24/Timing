from CRABClient.UserUtilities import config
config = config()

# External files needed by CRAB
inputDir     = '/afs/cern.ch/user/k/kmcdermo/public/input/'
inputPaths   = 'HLTpathsWExtras.txt'
inputFilters = 'HLTfilters.txt'
inputFlags   = 'METflags.txt'

config.General.workArea      = 'workArea'
config.General.requestName   = 'disphoTest'

config.JobType.pluginName    = 'Analysis'
config.JobType.psetName      = 'dispho.py'
config.JobType.numCores      = 8
config.JobType.maxMemoryMB   = 4000
config.JobType.inputFiles    = [ inputDir+inputPaths , inputDir+inputFilters , inputDir+inputFlags ]
config.JobType.pyCfgParams   = ['globalTag=101X_dataRun2_Prompt_v11','storeRecHits=True','onlyGED=True','lhcInfoValid=True',\
'nThreads='+str(config.JobType.numCores),'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags]

config.Data.inputDBS         = 'global'
config.Data.inputDataset     = '/EGamma/Run2018D-PromptReco-v2/MINIAOD'
config.Data.useParent        = True #Parent is /EGamma/Run2018D-v1/RAW
config.Data.splitting        = 'EventAwareLumiBased'
config.Data.unitsPerJob      = 10
config.Data.totalUnits       = 10

config.Data.outputDatasetTag = 'ecalTiming'
config.Data.publication      = False
config.Site.storageSite      = 'T2_CH_CERN'
config.Data.outLFNDirBase    = '/store/group/phys_exotica/PPS-Diphoton/juwillia/'

config.Data.lumiMask         = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
