import FWCore.ParameterSet.Config as cms

# Calo geometry service model
#
# removed by tommaso
#
#ECAL conditions
#  include "CalibCalorimetry/EcalTrivialCondModules/data/EcalTrivialCondRetriever.cfi"
#
#TPG condition needed by ecalRecHit producer if TT recovery is ON
from RecoLocalCalo.EcalRecProducers.ecalRecHitTPGConditions_cff import *
#ECAL reconstruction
from RecoLocalCalo.EcalRecProducers.ecalGlobalUncalibRecHit_cfi import *
#from RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi import *
from RecoLocalCalo.EcalRecProducers.ecalRecHit_cfi import *
from RecoLocalCalo.EcalRecProducers.ecalPreshowerRecHit_cfi import *
from RecoLocalCalo.EcalRecProducers.ecalDetIdToBeRecovered_cfi import *
from RecoLocalCalo.EcalRecProducers.ecalCompactTrigPrim_cfi import *
from RecoLocalCalo.EcalRecProducers.ecalTPSkim_cfi import *
from RecoLocalCalo.EcalRecProducers.ecalDetailedTimeRecHit_cfi import *

from Timing.TimingAnalyzer.jwk_ku_ecalMultiFitUncalRecHit_cff import *

ku_ecalUncalibRecHitSequence = cms.Sequence(ecalMultiFitUncalibRecHit*
					kuEcalMultiFitUncalibRecHit*
        	                        ecalDetIdToBeRecovered)

ku_multi_ecalUncalibRecHitSequence = cms.Sequence(ecalMultiFitUncalibRecHit*
                                        kuEcalMultiFitUncalibRecHit*
                                        kuNotEcalMultiFitUncalibRecHit*
                                        ecalDetIdToBeRecovered)

ku_only_ecalUncalibRecHitSequence = cms.Sequence(kuEcalMultiFitUncalibRecHit*
						ecalDetIdToBeRecovered)

kuEcalRecHit = ecalRecHit.clone(
	EErechitCollection = cms.string('kuEcalRecHitsEE'),
	EEuncalibRecHitCollection = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEE"),
	EBuncalibRecHitCollection = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEB"),
	EBrechitCollection = cms.string('kuEcalRecHitsEB'),
	)

kuStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuStcEcalRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuStcEcalRecHitsEB'),
	skipTimeCalib = cms.bool(True),
        )

kuNotEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuNotEcalRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuNotEcalRecHitsEB'),
        )

kuNotStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuNotStcEcalRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuNotStcEcalRecHitsEB'),
        skipTimeCalib = cms.bool(True),
        )

ku_ecalRecHitSequence        = cms.Sequence(ecalRecHit*
					 kuEcalRecHit*
                                         ecalCompactTrigPrim*
                                         ecalTPSkim+
                                         ecalPreshowerRecHit)

ku_min_ecalRecHitSequence        = cms.Sequence(ecalRecHit*kuEcalRecHit)

ku_only_ecalRecHitSequence        = cms.Sequence(kuEcalRecHit)

ku_multi_ecalRecHitSequence        = cms.Sequence(kuEcalRecHit*
						kuStcEcalRecHit*
						kuNotEcalRecHit*
						kuNotStcEcalRecHit)

# full sequences
ku_ecalLocalRecoSequence     	= cms.Sequence(ku_ecalUncalibRecHitSequence*ku_ecalRecHitSequence)

ku_min_ecalLocalRecoSequence    = cms.Sequence(ku_ecalUncalibRecHitSequence*ku_only_ecalRecHitSequence)

ku_only_ecalLocalRecoSequence  	= cms.Sequence(ku_only_ecalUncalibRecHitSequence*ku_only_ecalRecHitSequence)

ku_multi_ecalLocalRecoSequence   = cms.Sequence(ku_multi_ecalUncalibRecHitSequence*ku_multi_ecalRecHitSequence)

from RecoLocalCalo.EcalRecProducers.ecalDetailedTimeRecHit_cfi import *
_phase2_timing_ecalRecHitSequence = cms.Sequence( ku_ecalRecHitSequence.copy() + ecalDetailedTimeRecHit )
from Configuration.Eras.Modifier_phase2_timing_cff import phase2_timing
phase2_timing.toReplaceWith( ku_ecalRecHitSequence, _phase2_timing_ecalRecHitSequence )
#
#_fastSim_ecalRecHitSequence = ecalRecHitSequence.copyAndExclude([ecalCompactTrigPrim,ecalTPSkim])
#_fastSim_ecalUncalibRecHitSequence = ecalUncalibRecHitSequence.copyAndExclude([ecalDetIdToBeRecovered])
#from Configuration.Eras.Modifier_fastSim_cff import fastSim
#fastSim.toReplaceWith(ecalRecHitSequence, _fastSim_ecalRecHitSequence)
#fastSim.toReplaceWith(ecalUncalibRecHitSequence, _fastSim_ecalUncalibRecHitSequence)


