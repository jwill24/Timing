#! /usr/bin/env python

import os
from optparse import OptionParser

from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

def getOptions():
    """
    Parse and return the arguments provided by the user.
    """
    usage = ("Usage: %prog --crabCmd CMD [--workArea WAD --crabCmdOpts OPTS]"
             "\nThe multicrab command executes 'crab CMD OPTS' for each project directory contained in WAD"
             "\nUse multicrab -h for help")

    parser = OptionParser(usage=usage)

    parser.add_option('-c', '--crabCmd',
                      dest = 'crabCmd',
                      default = 'submit',
                      help = "crab command",
                      metavar = 'CMD')

    parser.add_option('-w', '--workArea',
                      dest = 'workArea',
                      default = 'myworkingArea',
                      help = "work area directory (only if CMD != 'submit')",
                      metavar = 'WAD')

    parser.add_option('-o', '--crabCmdOpts',
                      dest = 'crabCmdOpts',
                      default = '',
                      help = "options for crab command CMD",
                      metavar = 'OPTS')

    (options, arguments) = parser.parse_args()

    if arguments:
        parser.error("Found positional argument(s): %s." % (arguments))
    if not options.crabCmd:
        parser.error("(-c CMD, --crabCmd=CMD) option not provided.")
    if options.crabCmd != 'submit':
        if not options.workArea:
            parser.error("(-w WAR, --workArea=WAR) option not provided.")
        if not os.path.isdir(options.workArea):
            parser.error("'%s' is not a valid directory." % (options.workArea))

    return options


def docrab():

    options = getOptions()

    # The submit command needs special treatment.
    if options.crabCmd == 'submit':

        # External files needed by CRAB
        inputDir     = '/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
        inputPaths   = 'HLTpathsWExtras.txt'
        inputFilters = 'HLTfilters.txt'
        inputFlags   = 'METflags.txt'
        #inputJSON    = 'golden2017.json'
        inputJSON    = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'

        #--------------------------------------------------------
        # This is the base config:
        #--------------------------------------------------------
        from CRABClient.UserUtilities import config
        config = config()

        config.General.workArea    = options.workArea
        config.General.requestName = None

        config.JobType.pluginName  = 'Analysis'
        #config.JobType.psetName    = 'dispho_twotier.py'
        config.JobType.psetName    = 'dispho_raw_twotier.py'
        #config.JobType.numCores    = 8
        config.JobType.pyCfgParams = None
        config.JobType.inputFiles  = [ inputDir+inputPaths , inputDir+inputFilters , inputDir+inputFlags ]

        config.Data.inputDataset   = None
        config.Data.useParent      = True
        #config.Data.useParent      = False
        config.Data.lumiMask       = inputJSON
        config.Data.splitting      = 'EventAwareLumiBased'
        config.Data.unitsPerJob    = 250000
        #config.Data.splitting     = 'Automatic'
        #config.Data.unitsPerJob   = 200000
        config.Data.runRange       = '321732-321760'

        config.Data.publication    = False
        config.Site.storageSite    = 'T2_US_Nebraska'
        config.Data.outLFNDirBase  = '/store/user/jaking/ecalTiming/'
        #--------------------------------------------------------

        # Will submit one task for each of these input datasets.
        inputDataAndOpts = [
            #['/SinglePhoton/Run2017B-31Mar2018-v1/MINIAOD'],
            #['/SinglePhoton/Run2017C-31Mar2018-v1/MINIAOD'],
            #['/SinglePhoton/Run2017D-31Mar2018-v1/MINIAOD'],
            #['/SinglePhoton/Run2017E-31Mar2018-v1/MINIAOD'],
            #['/SinglePhoton/Run2017F-31Mar2018-v1/MINIAOD'],

            #['/DoubleEG/Run2017B-31Mar2018-v1/MINIAOD'],
            #['/DoubleEG/Run2017C-31Mar2018-v1/MINIAOD'],
            #['/DoubleEG/Run2017D-31Mar2018-v1/MINIAOD'],
            #['/DoubleEG/Run2017E-31Mar2018-v1/MINIAOD'],
            #['/DoubleEG/Run2017F-31Mar2018-v1/MINIAOD'],

            #['/EGamma/Run2018A-17Sep2018-v2/MINIAOD'],
            #['/EGamma/Run2018B-26Sep2018-v1/MINIAOD'],
            #['/EGamma/Run2018C-17Sep2018-v1/MINIAOD'],
            ['/EGamma/Run2018D-PromptReco-v2/MINIAOD'],
            #['/EGamma/Run2018E-PromptReco-v1/MINIAOD'],
            ]
 
        for inDO in inputDataAndOpts:
            # inDO[0] is of the form /A/B/C. Since A+B is unique for each inDS, use this in the CRAB request name.
            primaryDataset = inDO[0].split('/')[1]
            runEra         = inDO[0].split('/')[2]
            dataset        = inDO[0].split('/')[3]
            #trial          = "valtest12_twotier" # useParent=True; rawCollectionsValid=True 
            #trial          = "valtest13_twotier"  # useParent=True; rawCollectionsValid=False
            #trial          = "valtest14_twotier"  # useParent=False; rawCollectionsValid=False
            #trial          = "valtest15_twotier"  # raw reco: useParent=True; rawCollectionsValid=True
            trial          = "valtest16_twotier"  # raw reco w/kurechits: useParent=True; rawCollectionsValid=True
	    runs	   = "321732-321760"
	    #runs	   = "Full"

            #config.General.requestName   = primaryDataset+"_"+runEra+"_v7"
            config.General.requestName   = trial+"_"+primaryDataset+"_"+runEra+"_"+runs+"_"+dataset+"_dispho"
            config.Data.outputDatasetTag = trial+"_"+primaryDataset+"_"+dataset+"_"+runEra+"_"+runs+"_dispho"

	    # for 2018 prompt v1
            #config.JobType.pyCfgParams   = ['globalTag=102X_dataRun2_Prompt_v1','nThreads='+str(config.JobType.numCores),
            #                                'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags,
            #                                'onlyGED=True', 'outputFileName=output.root', 'lhcInfoValid=True']

	    # for 2018  prompt v11
            config.JobType.pyCfgParams   = ['globalTag=102X_dataRun2_Prompt_v11',#'nThreads='+str(config.JobType.numCores),
                                            'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags,
                                            'onlyGED=True', 'outputFileName=output.root', 'lhcInfoValid=True', 'rawCollectionsValid=True']

	    # for 2018 ABC rereco
            #config.JobType.pyCfgParams   = ['globalTag=102X_dataRun2_Sep2018Rereco_v1','nThreads='+str(config.JobType.numCores),
            #                                'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags,
            #                                'onlyGED=True', 'outputFileName=output.root', 'lhcInfoValid=False']

            config.Data.inputDataset     = inDO[0]
            #config.Data.outputDatasetTag = '%s_%s' % (config.General.workArea, config.General.requestName)
            # Submit.
            try:
                print "Submitting for input dataset %s" % (inDO[0])
                crabCommand(options.crabCmd, config = config, *options.crabCmdOpts.split())
                os.system("rm -rf %s/crab_%s/inputs" % (config.General.workArea, config.General.requestName))
            except HTTPException as hte:
                print "Submission for input dataset %s failed: %s" % (inDO[0], hte.headers)
            except ClientException as cle:
                print "Submission for input dataset %s failed: %s" % (inDO[0], cle)

    # All other commands can be simply executed.
    elif options.workArea:

        for dir in os.listdir(options.workArea):
            projDir = os.path.join(options.workArea, dir)
            if not os.path.isdir(projDir):
                continue
            # Execute the crab command.
            msg = "Executing (the equivalent of): crab %s --dir %s %s" % (options.crabCmd, projDir, options.crabCmdOpts)
            print "-"*len(msg)
            print msg
            print "-"*len(msg)
            try:
                crabCommand(options.crabCmd, dir = projDir, *options.crabCmdOpts.split())
            except HTTPException as hte:
                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, hte.headers)
            except ClientException as cle:
                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, cle)


docrab();

