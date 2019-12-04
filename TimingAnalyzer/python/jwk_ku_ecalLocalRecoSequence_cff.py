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
                                        kuWtEcalMultiFitUncalibRecHit*
					kuWootEcalMultiFitUncalibRecHit*
                                        kuMfootEcalMultiFitUncalibRecHit*
                                        kuMfootCCEcalMultiFitUncalibRecHit*
                                        ecalDetIdToBeRecovered)

ku_only_ecalUncalibRecHitSequence = cms.Sequence(kuEcalMultiFitUncalibRecHit*
						ecalDetIdToBeRecovered)

kuEcalRecHit = ecalRecHit.clone(
	EErechitCollection = cms.string('kuRecHitsEE'),
	EEuncalibRecHitCollection = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEE"),
	EBuncalibRecHitCollection = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEB"),
	EBrechitCollection = cms.string('kuRecHitsEB'),
	)

kuStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuStcRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuStcRecHitsEB'),
	skipTimeCalib = cms.bool(True),
        )

kuNotEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuNotRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuNotRecHitsEB'),
        )

kuNotStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuNotStcRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuNotStcRecHitsEB'),
        skipTimeCalib = cms.bool(True),
        )

kuWtEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuWtRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuWtEcalMultiFitUncalibRecHit","kuWtEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuWtEcalMultiFitUncalibRecHit","kuWtEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuWtRecHitsEB'),
        )

kuWtStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuWtStcRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuWtEcalMultiFitUncalibRecHit","kuWtEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuWtEcalMultiFitUncalibRecHit","kuWtEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuWtStcRecHitsEB'),
        skipTimeCalib = cms.bool(True),
        )

kuWootEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuWootRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuWootEcalMultiFitUncalibRecHit","kuWootEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuWootEcalMultiFitUncalibRecHit","kuWootEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuWootRecHitsEB'),
        )

kuWootStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuWootStcRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuWootEcalMultiFitUncalibRecHit","kuWootEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuWootEcalMultiFitUncalibRecHit","kuWootEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuWootStcRecHitsEB'),
        skipTimeCalib = cms.bool(True),
        )

kuMfootEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuMfootRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuMfootEcalMultiFitUncalibRecHit","kuMfootEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuMfootEcalMultiFitUncalibRecHit","kuMfootEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuMfootRecHitsEB'),
        )

kuMfootStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuMfootStcRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuMfootEcalMultiFitUncalibRecHit","kuMfootEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuMfootEcalMultiFitUncalibRecHit","kuMfootEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuMfootStcRecHitsEB'),
        skipTimeCalib = cms.bool(True),
        )

kuMfootCCStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuMfootCCStcRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuMfootCCEcalMultiFitUncalibRecHit","kuMfootCCEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuMfootCCEcalMultiFitUncalibRecHit","kuMfootCCEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuMfootCCStcRecHitsEB'),
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
						#kuNotEcalRecHit*
						kuNotStcEcalRecHit*
                                                kuWtStcEcalRecHit*
                                                kuWootStcEcalRecHit*
						kuMfootStcEcalRecHit*
                                                kuMfootCCStcEcalRecHit
						)

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


