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


#def subcrab( runs ):
def subcrab( runs, events, reqmem ):

    options = getOptions()

    # The submit command needs special treatment.
    if options.crabCmd == 'submit':

        # External files needed by CRAB
        #inputDir     = '/home/t3-ku/jaking/ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
        inputDir     = '/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
        inputPaths   = 'HLTpathsWExtras.txt'
        inputFilters = 'HLTfilters.txt'
        inputFlags   = 'METflags.txt'
        #inputJSON    = 'golden2016.json'
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
        #config.JobType.psetName    = 'jwk_raw_dispho.py'
        config.JobType.psetName    = 'dispho_rawlist_twotier.py'
        #config.JobType.numCores    = 8
        #config.JobType.maxMemoryMB = reqmem
        #config.JobType.maxJobRuntimeMin = 1600
        config.JobType.pyCfgParams = None
        config.JobType.inputFiles  = [ inputDir+inputPaths , inputDir+inputFilters , inputDir+inputFlags ]

        config.Data.inputDataset = None
        config.Data.useParent      = True
        #config.Data.useParent      = False
        config.Data.lumiMask     = inputJSON
        #config.Data.splitting    = 'LumiBased'
        config.Data.splitting    = 'EventAwareLumiBased'
        #config.Data.splitting    = 'Automatic'
        config.Data.unitsPerJob  =  25000    
	# unitsPerJob = 1000 for 321122-321128 and maxMemoryMB = 4000  on EventAwareLumiBased
	config.Data.runRange	= runs #'321122-321128'

        #config.Data.outputDatasetTag = 'reducedRAW_EGamma_ntuple'
        config.Data.publication      = False
        config.Site.storageSite      = 'T2_US_Nebraska'
        config.Data.outLFNDirBase    = '/store/user/jaking/ecalTiming/'
        #--------------------------------------------------------

        # Will submit one task for each of these input datasets.
        inputDataAndOpts = [

            #['/EGamma/Run2018A-17Sep2018-v2/MINIAOD'],
            #['/EGamma/Run2018B-26Sep2018-v1/MINIAOD'],
            #['/EGamma/Run2018C-17Sep2018-v1/MINIAOD'],
            ['/EGamma/Run2018D-PromptReco-v2/MINIAOD'],
            #['/EGamma/Run2018E-PromptReco-v1/MINIAOD'],

	    ]
 
        for inDO in inputDataAndOpts:
            # inDO[0] is of the form /A/B/C. Since A+B is unique for each inDS, use this in the CRAB request name.
	    #print( inDO[0] )
            primaryDataset = inDO[0].split('/')[1]
            runEra         = inDO[0].split('/')[2]
	    dataset	   = inDO[0].split('/')[3]
	    #infilename	   = inDO[0].split('/')[11]
	    #trial	   = "valtest5"
            #trial          = "valtest24_twotier"  # mini+raw for kurechits/uncal: true,true,false, jwkpupv3, unitsPerJob=25000, 320673-321730 2018D
            trial          = "valtest25_twotierlist"  # mini+raw for kurechits/uncal: true,true,false, jwkpupv3, unitsPerJob=25000, lists run

            config.General.requestName   = trial+"_"+primaryDataset+"_"+runEra+"_"+runs+"_"+dataset+"_dispho"
            config.Data.outputDatasetTag = trial+"_"+primaryDataset+"_"+dataset+"_"+runEra+"_"+runs+"_dispho"


	    # for 2018 EGamma 2tier
            config.JobType.pyCfgParams   = ['globalTag=101X_dataRun2_Prompt_v11',#'nThreads='+str(config.JobType.numCores), 
                                            'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags, 
                                            'onlyGED=True', 'outputFileName=output.root', 'rlelist='+events,
					    'kuRechitValid=True','lhcInfoValid=False', 'rawCollectionsValid=True' ]

            config.Data.inputDataset     = inDO[0]
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

event_list_path = "/home/t3-ku/jaking/trees/ecal/run_lumi_event_lists/sel_eg2018/"

def submit_run2018A():
        subcrab( "315257-315322", event_list_path + "sel_315257v315322_EG2018A.txt", 3000 )
        subcrab( "315339-315366", event_list_path + "sel_315339v315366_EG2018A.txt", 3000 )
        subcrab( "315420-315488", event_list_path + "sel_315420v315488_EG2018A.txt", 3000 )
        subcrab( "315489-315557", event_list_path + "sel_315489v315557_EG2018A.txt", 3000 )
        subcrab( "315640-315689", event_list_path + "sel_315640v315689_EG2018A.txt", 3250 )
        subcrab( "315690-315713", event_list_path + "sel_315690v315713_EG2018A.txt", 3250 )
        subcrab( "315721-315790", event_list_path + "sel_315721v315790_EG2018A.txt", 3000 )
        subcrab( "315800-315973", event_list_path + "sel_315800v315973_EG2018A.txt", 3500 )
        subcrab( "315974-316110", event_list_path + "sel_315974v316110_EG2018A.txt", 3000 )
        subcrab( "316111-316187", event_list_path + "sel_316111v316187_EG2018A.txt", 3000 )
        subcrab( "316199-316216", event_list_path + "sel_316199v316216_EG2018A.txt", 3000 )
        subcrab( "316217-316240", event_list_path + "sel_316217v316240_EG2018A.txt", 3000 )
        subcrab( "316241-316457", event_list_path + "sel_316241v316457_EG2018A.txt", 3000 )
        subcrab( "316469-316569", event_list_path + "sel_316469v316569_EG2018A.txt", 3000 )
        subcrab( "316590-316700", event_list_path + "sel_316590v316700_EG2018A.txt", 3000 )
        subcrab( "316701-316722", event_list_path + "sel_316701v316722_EG2018A.txt", 3000 )
        subcrab( "316723-316766", event_list_path + "sel_316723v316766_EG2018A.txt", 3250 )
        subcrab( "316876-316995", event_list_path + "sel_316876v316995_EG2018A.txt", 3250 )

def submit_run2018B():
        subcrab( "317080-317182", event_list_path + "sel_317080v317182_EG2018B.txt", 3000 )
        subcrab( "317212-317297", event_list_path + "sel_317212v317297_EG2018B.txt", 3000 )
        subcrab( "317319-317340", event_list_path + "sel_317319v317340_EG2018B.txt", 3000 )
        subcrab( "317382-317435", event_list_path + "sel_317382v317435_EG2018B.txt", 3000 )
        subcrab( "317438-317527", event_list_path + "sel_317438v317527_EG2018B.txt", 3000 )
        subcrab( "317591-317640", event_list_path + "sel_317591v317640_EG2018B.txt", 3000 )
        subcrab( "317641-317650", event_list_path + "sel_317641v317650_EG2018B.txt", 3000 )
        subcrab( "317661-317696", event_list_path + "sel_317661v317696_EG2018B.txt", 3000 )
        subcrab( "318828-319077", event_list_path + "sel_318828v319077_EG2018B.txt", 3000 )

def submit_run2018C():
        subcrab( "319337-319337", event_list_path + "sel_319337v319337_EG2018C.txt", 3000 )
        subcrab( "319347-319486", event_list_path + "sel_319347v319486_EG2018C.txt", 3000 )
        subcrab( "319503-319579", event_list_path + "sel_319503v319579_EG2018C.txt", 3000 )
        subcrab( "319625-319678", event_list_path + "sel_319625v319678_EG2018C.txt", 3000 )
        subcrab( "319687-319756", event_list_path + "sel_319687v319756_EG2018C.txt", 3000 )
        subcrab( "319840-319910", event_list_path + "sel_319840v319910_EG2018C.txt", 3000 )
        subcrab( "319912-319993", event_list_path + "sel_319912v319993_EG2018C.txt", 3000 )
        subcrab( "320002-320038", event_list_path + "sel_320002v320038_EG2018C.txt", 3000 )
        subcrab( "320039-320065", event_list_path + "sel_320039v320065_EG2018C.txt", 3000 )

def submit_run2018D():
        #subcrab( "320673-320673", event_list_path + "sel_320673v320673_EG2018D.txt", 3000 )
        #subcrab( "320674-320804", event_list_path + "sel_320674v320804_EG2018D.txt", 3000 )
        #subcrab( "320807-320824", event_list_path + "sel_320807v320824_EG2018D.txt", 3000 )
        #subcrab( "320838-320858", event_list_path + "sel_320838v320858_EG2018D.txt", 3000 )
        #subcrab( "320859-320933", event_list_path + "sel_320859v320933_EG2018D.txt", 3000 )
        #subcrab( "320934-321007", event_list_path + "sel_320934v321007_EG2018D.txt", 3000 )

        subcrab( "321009-321055", event_list_path + "sel_321009v321055_EG2018D.txt", 3000 )

        #subcrab( "321067-321124", event_list_path + "sel_321067v321124_EG2018D.txt", 3000 )
        #subcrab( "321126-321149", event_list_path + "sel_321126v321149_EG2018D.txt", 3000 )
        #subcrab( "321165-321219", event_list_path + "sel_321165v321219_EG2018D.txt", 3000 )
        #subcrab( "321221-321305", event_list_path + "sel_321221v321305_EG2018D.txt", 3000 )
        #subcrab( "321311-321396", event_list_path + "sel_321311v321396_EG2018D.txt", 3000 )
        #subcrab( "321397-321431", event_list_path + "sel_321397v321431_EG2018D.txt", 3000 )
        #subcrab( "321432-321457", event_list_path + "sel_321432v321457_EG2018D.txt", 3000 )
        #subcrab( "321461-321730", event_list_path + "sel_321461v321730_EG2018D.txt", 3000 )
        #subcrab( "321732-321760", event_list_path + "sel_321732v321760_EG2018D.txt", 3000 )
        #subcrab( "321773-321818", event_list_path + "sel_321773v321818_EG2018D.txt", 3000 )
        #subcrab( "321820-321880", event_list_path + "sel_321820v321880_EG2018D.txt", 3000 )
        #subcrab( "321887-321909", event_list_path + "sel_321887v321909_EG2018D.txt", 3000 )
        #subcrab( "321917-321973", event_list_path + "sel_321917v321973_EG2018D.txt", 3000 )
        #subcrab( "321975-321990", event_list_path + "sel_321975v321990_EG2018D.txt", 3000 )
        #subcrab( "322013-322068", event_list_path + "sel_322013v322068_EG2018D.txt", 3000 )
        #subcrab( "322079-322179", event_list_path + "sel_322079v322179_EG2018D.txt", 3000 )
        #subcrab( "322201-322252", event_list_path + "sel_322201v322252_EG2018D.txt", 3000 )
        #subcrab( "322317-322332", event_list_path + "sel_322317v322332_EG2018D.txt", 3000 )
        #subcrab( "322348-322381", event_list_path + "sel_322348v322381_EG2018D.txt", 3000 )
        #subcrab( "322407-322492", event_list_path + "sel_322407v322492_EG2018D.txt", 3000 )
        #subcrab( "322510-322633", event_list_path + "sel_322510v322633_EG2018D.txt", 3000 )
        #subcrab( "323414-323488", event_list_path + "sel_323414v323488_EG2018D.txt", 3000 )
        #subcrab( "323492-323693", event_list_path + "sel_323492v323693_EG2018D.txt", 3000 )
        #subcrab( "323696-323755", event_list_path + "sel_323696v323755_EG2018D.txt", 3000 )
        #subcrab( "323775-323857", event_list_path + "sel_323775v323857_EG2018D.txt", 3000 )
        #subcrab( "323940-323997", event_list_path + "sel_323940v323997_EG2018D.txt", 3000 )
        #subcrab( "324021-324201", event_list_path + "sel_324021v324201_EG2018D.txt", 3000 )
        #subcrab( "324202-324245", event_list_path + "sel_324202v324245_EG2018D.txt", 3000 )
        #subcrab( "324293-324318", event_list_path + "sel_324293v324318_EG2018D.txt", 3000 )
        #subcrab( "324420-324765", event_list_path + "sel_324420v324765_EG2018D.txt", 3000 )
        #subcrab( "324769-324835", event_list_path + "sel_324769v324835_EG2018D.txt", 3000 )
        #subcrab( "324840-324878", event_list_path + "sel_324840v324878_EG2018D.txt", 3000 )
        #subcrab( "324897-324980", event_list_path + "sel_324897v324980_EG2018D.txt", 3000 )
        #subcrab( "324997-325022", event_list_path + "sel_324997v325022_EG2018D.txt", 3000 )
        #subcrab( "325057-325170", event_list_path + "sel_325057v325170_EG2018D.txt", 3000 )


#submit_run2018A()
#submit_run2018B()
#submit_run2018C()
submit_run2018D()

