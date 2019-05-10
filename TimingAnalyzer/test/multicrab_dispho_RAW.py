#! /usr/bin/env python

import os
from optparse import OptionParser

from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException
from in_r18D_list import file_list 

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


def subcrab( runs ):

    options = getOptions()

    # The submit command needs special treatment.
    if options.crabCmd == 'submit':

        # External files needed by CRAB
        inputDir     = '/home/t3-ku/jaking/ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
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
        #config.General.requestName = None

        config.JobType.pluginName  = 'Analysis'
        config.JobType.psetName    = 'test_raw_dispho.py'
        config.JobType.numCores    = 8
        config.JobType.maxMemoryMB = 4000
        #config.JobType.maxJobRuntimeMin = 1600
        config.JobType.pyCfgParams = None
        config.JobType.inputFiles  = [ inputDir+inputPaths , inputDir+inputFilters , inputDir+inputFlags ]

        config.Data.inputDataset = None
        config.Data.lumiMask     = inputJSON
        #config.Data.splitting    = 'LumiBased'
        config.Data.splitting    = 'EventAwareLumiBased'
        #config.Data.splitting    = 'Automatic'
        config.Data.unitsPerJob  =  1000    
	# unitsPerJob = 1000 for 321122-321128 and maxMemoryMB = 4000  on EventAwareLumiBased
	config.Data.runRange	= runs #'321122-321128'

        #config.Data.outputDatasetTag = 'reducedRAW_EGamma_ntuple'
        config.Data.publication      = False
        config.Site.storageSite      = 'T2_US_Nebraska'
        config.Data.outLFNDirBase    = '/store/user/jaking/ecalTiming/'
        #--------------------------------------------------------

        # Will submit one task for each of these input datasets.
        inputDataAndOpts = [

            #['/EGamma/Run2018D-v1/RAW'],
            ['/EGamma/Run2018C-v1/RAW'],
            #['/EGamma/Run2018B-v1/RAW'],
            #['/EGamma/Run2018A-v1/RAW'],

	    ]
#'/store/data/Run2018D/EGamma/RAW/v1/000/321/218/00000/5A0A07C1-FE9E-E811-BEDA-FA163E108FC3.root'
 
        for inDO in inputDataAndOpts:
            # inDO[0] is of the form /A/B/C. Since A+B is unique for each inDS, use this in the CRAB request name.
	    #print( inDO[0] )
            primaryDataset = inDO[0].split('/')[1]
            runEra         = inDO[0].split('/')[2]
	    dataset	   = inDO[0].split('/')[3]
	    #infilename	   = inDO[0].split('/')[11]

            config.General.requestName   = primaryDataset+"_"+runEra+"_"+dataset+"_"+runs+"_red"
            config.Data.outputDatasetTag = "red_"+primaryDataset+"_"+runEra+"_"+dataset+"_"+runs

#            config.General.requestName   = primaryDataset+"_"+runEra+"_"+dataset+"_"+infilename[:-5]
#            config.Data.outputDatasetTag = primaryDataset+"_"+runEra+"_"+dataset+"_"+infilename[:-5]

            # for 2018D EGamma RAW
            #config.JobType.pyCfgParams   = ['globalTag=101X_dataRun2_Prompt_v11','nThreads='+str(config.JobType.numCores),
            #                                'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags,
            #                                'onlyGED=True', 'outputFileName=output.root', 'lhcInfoValid=True']

	    # for 2018ABC EGamma RAW
            config.JobType.pyCfgParams   = ['globalTag=101X_dataRun2_Prompt_v11','nThreads='+str(config.JobType.numCores), 
                                            'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags, 
                                            'onlyGED=True', 'outputFileName=output.root', 'lhcInfoValid=False']
	    # for 2018D prompt
            #config.JobType.pyCfgParams   = ['globalTag=102X_dataRun2_Prompt_v1','nThreads='+str(config.JobType.numCores),
            #                                'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags,
            #                                'onlyGED=True', 'outputFileName=output.root', 'lhcInfoValid=True']

	    # for 2018E prompt
            #config.JobType.pyCfgParams   = ['globalTag=','nThreads='+str(config.JobType.numCores),
            #                                'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags,
            #                                'onlyGED=True', 'outputFileName=output.root', 'lhcInfoValid=True']

	    # for 2018 ABC rereco
            #config.JobType.pyCfgParams   = ['globalTag=102X_dataRun2_Sep2018Rereco_v1','nThreads='+str(config.JobType.numCores),
            #                                'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags,
            #                                'onlyGED=True', 'outputFileName=output.root', 'lhcInfoValid=False']

            config.Data.inputDataset     = inDO[0]
            #config.Data.outputDatasetTag = '%s_%s' % (config.General.workArea, config.General.requestName)
            # Submit.
            try:
                print "Submitting for input dataset %s for runs %s" % (inDO[0], runs)
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


#subcrab( "320916-321121" )

def submit_run2018A():
	subcrab( "316876-316995" )
	subcrab( "316723-316766" )
	subcrab( "316701-316722" )
	subcrab( "316590-316700" )
	subcrab( "316217-316240" )
	subcrab( "316199-316216" )
	subcrab( "316111-316187" )
	subcrab( "315974-316110" )
	subcrab( "315800-315973" )
	subcrab( "315721-315790" )
	subcrab( "315690-315713" )
	subcrab( "315640-315689" )
	#subcrab( "315489-315557" )
	#subcrab( "315420-315488" )
	subcrab( "315339-315366" )
	subcrab( "315257-315322" )

def submit_run2018B():
	subcrab( "318828-319077" )
	subcrab( "317661-317696" )
	subcrab( "317641-317650" )
	subcrab( "317591-317640" )
	subcrab( "317438-317527" )
	subcrab( "317382-317435" )
	subcrab( "317319-317340" )
	subcrab( "317212-317297" )
	subcrab( "317080-317182" )

def submit_run2018C():
	subcrab( "320039-320065" )
	subcrab( "320002-320038" )
	subcrab( "319912-319993" )
	subcrab( "319840-319910" )
	subcrab( "319687-319756" )
	subcrab( "319625-319678" )
	subcrab( "319503-319579" )
	subcrab( "319347-319486" )
	subcrab( "319337-319337" )

def submit_run2018D():
	subcrab( "325057-325170" )
	subcrab( "324997-325022" )
	subcrab( "324897-324980" )
	subcrab( "324840-324878" )
	subcrab( "324769-324835" )
	subcrab( "324420-324765" )
	subcrab( "324293-324318" )
	subcrab( "324202-324245" )
	subcrab( "324021-324201" )
	subcrab( "323940-323997" )
	subcrab( "323775-323857" )
	subcrab( "323696-323755" )
	subcrab( "323492-323693" )
	subcrab( "323414-323488" )
	subcrab( "322510-322633" )
	subcrab( "322407-322492" )
	subcrab( "322348-322381" )
	subcrab( "322317-322332" )
	subcrab( "322201-322252" )
	subcrab( "322079-322179" )
	subcrab( "322013-322068" )
	subcrab( "321975-321990" )
	subcrab( "321917-321973" )
	subcrab( "321887-321909" )
	subcrab( "321820-321880" )
	subcrab( "321773-321818" )
	subcrab( "321732-321760" )
	subcrab( "321461-321730" )
	subcrab( "321432-321457" )
	subcrab( "321397-321431" )
	subcrab( "321311-321396" )
	subcrab( "321221-321305" )
	subcrab( "321165-321219" )
	subcrab( "321126-321149" )
	subcrab( "321067-321124" )
	subcrab( "321009-321055" )
	subcrab( "320934-321007" )
	subcrab( "320859-320933" )
	subcrab( "320838-320858" )
	subcrab( "320807-320824" )
	subcrab( "320674-320804" )
	subcrab( "320673-320673" )

#submit_run2018A()
submit_run2018B()
#submit_run2018C()
#submit_run2018D()

