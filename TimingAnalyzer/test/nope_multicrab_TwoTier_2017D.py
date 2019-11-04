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
        inputJSON    = 'golden2017.json'
        #inputJSON    = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
        inputRuns  =   '302033-302163'
	#secInputPaths = '/DoubleEG/Run2017D-v1/RAW'

        #--------------------------------------------------------
        # This is the base config:
        #--------------------------------------------------------
        from CRABClient.UserUtilities import config
        config = config()

        config.General.workArea    = options.workArea
        config.General.requestName = None

        config.JobType.pluginName  = 'Analysis'
        #config.JobType.psetName    = 'dispho_twotier.py'
        #config.JobType.psetName    = 'dispho_raw_twotier.py'
        config.JobType.psetName    = 'dispho_raw_twotier_2017D.py'
        #config.JobType.numCores    = 8
        config.JobType.pyCfgParams = None
        config.JobType.inputFiles  = [ inputDir+inputPaths , inputDir+inputFilters , inputDir+inputFlags ]

        config.Data.inputDataset   = None
        config.Data.useParent      = True
        #config.Data.secondaryInputDataset	= secInputPaths
        config.Data.lumiMask       = inputJSON
        config.Data.splitting      = 'EventAwareLumiBased'
        config.Data.unitsPerJob    = 25000
        #config.Data.splitting     = 'Automatic'
        #config.Data.unitsPerJob   = 200000
        config.Data.runRange       = inputRuns

        config.Data.publication    = False
        config.Site.storageSite    = 'T2_US_Nebraska'
        config.Data.outLFNDirBase  = '/store/user/jaking/ecalTiming/'
        #--------------------------------------------------------

        # Will submit one task for each of these input datasets.
        inputDataAndOpts = [
            #['/SinglePhoton/Run2017B-09May2018-v1/MINIAOD'],
            #['/SinglePhoton/Run2017C-09May2018-v1/MINIAOD'],
            #['/SinglePhoton/Run2017D-09May2018-v1/MINIAOD'],
            #['/SinglePhoton/Run2017E-09May2018-v1/MINIAOD'],
            #['/SinglePhoton/Run2017F-09May2018-v1/MINIAOD'],

            #['/DoubleEG/Run2017B-09May2018-v1/MINIAOD'],
            #['/DoubleEG/Run2017C-09May2018-v1/MINIAOD'],
            #['/DoubleEG/Run2017D-09May2018-v1/MINIAOD'],
            #['/DoubleEG/Run2017E-09May2018-v1/MINIAOD'],
            #['/DoubleEG/Run2017F-09May2018-v1/MINIAOD'],

            #['/DoubleEG/Run2017D-09Aug2019_UL2017-v1/MINIAOD'],

            #['/DoubleEG/Run2017B-17Nov2017-v1/MINIAOD'],
            #['/DoubleEG/Run2017C-17Nov2017-v1/MINIAOD'],
            ['/DoubleEG/Run2017D-17Nov2017-v1/MINIAOD'],
            #['/DoubleEG/Run2017E-17Nov2017-v1/MINIAOD'],
            #['/DoubleEG/Run2017F -17Nov2017-v1/MINIAOD'],

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
            #trial          = "valtest16_twotier"  # raw reco w/kurechits: useParent=True; rawCollectionsValid=True
            #trial          = "valtest17_twotier"  # raw reco w/kurechits: useParent=True; rawCollectionsValid=True, justin partial unpack
            #trial          = "valtest18_twotier"  # raw reco w/kurechits: useParent=True; rawCollectionsValid=True, jwk partial unpack
            #trial          = "valtest19_twotier"  # raw reco w/kurechits: useParent=True; rawCollectionsValid=True, jwk partial unpack v2
            #trial          = "valtest20_twotier"  # same as 19, test fix for kurechit fill issue, unitsPerJob=200000 
            #trial          = "valtest21_twotier"  # same as 20, 321732-321760 added L1Reco and bunchspace producer( jwkpupv3 ), unitsPerJob=50000
            #trial          = "valtest22_twotier"  # same as 21 with runrange: 323414-323488
            #trial          = "valtest23_twotier"  # same as 22, with LHCInfoValid=False
            #trial          = "valtest24_twotier"  # mini+raw for kurechits/uncal: true,true,false, jwkpupv3, unitsPerJob=25000, 320673-321730 2018D
            #trial          = "valtest26v2_2t_2017"  # mini+raw for kurechits/uncal: true,true,false, jwkpupv3, unitsPerJob=25000, 302033-302163 2017D
            #trial          = "valtest27_2t_2017"  # aod+raw for kurechits/uncal: true,true,false, jwkpupv3, unitsPerJob=25000, 302033-302163 2017D
            #trial          = "valtest28_2t_2017"  # miniaod+raw for kurechits/uncal: true,true,false, jwkpupv3, unitsPerJob=25000, 302033-302163 2017D
            #trial          = "valtest33_2t_2017" # as 28 with /DoubleEG/Run2017D-09Aug2019_UL2017-v1/MINIAOD
            #trial          = "valtest34_2t_2017" # as 28 with /DoubleEG/Run2017D-17Nov2017-v1/MINIAOD
            trial          = "valtest35_2t_2017" # as 28 with /DoubleEG/Run2017D-17Nov2017-v1/MINIAOD w/ 10_4 gt
            runs           = inputRuns
	    #runs	   = "Full"

            #config.General.requestName   = primaryDataset+"_"+runEra+"_v7"
            config.General.requestName   = trial+"_"+primaryDataset+"_"+runEra+"_"+runs+"_"+dataset+"_dispho"
            config.Data.outputDatasetTag = trial+"_"+primaryDataset+"_"+dataset+"_"+runEra+"_"+runs+"_dispho"

            #config.Data.secondaryInputDataset = secInputPaths

            #config.JobType.pyCfgParams   = ['globalTag=106X_dataRun2_v20',#'nThreads='+str(config.JobType.numCores),
            #                                'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags, 'onlyGED=True', 
	    #				    'outputFileName=output.root', 'kuRechitValid=True','lhcInfoValid=False', 'rawCollectionsValid=True']

            config.JobType.pyCfgParams   = ['globalTag=101X_dataRun2_Prompt_v11',#'nThreads='+str(config.JobType.numCores), 
                                            'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags,
                                            'onlyGED=True', 'outputFileName=output.root', #'rlelist='+events,
                                            'kuRechitValid=True','lhcInfoValid=False', 'rawCollectionsValid=True' ]

            #config.JobType.pyCfgParams   = ['globalTag=94X_dataRun2_ReReco_EOY17_v2',#'nThreads='+str(config.JobType.numCores),
            #                                'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags, 'onlyGED=True',
            #                                'outputFileName=output.root', 'kuRechitValid=True','lhcInfoValid=False', 'rawCollectionsValid=True']


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

