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
					kuKsEcalMultiFitUncalibRecHit*
        	                        ecalDetIdToBeRecovered)

ku_multi_ecalUncalibRecHitSequence = cms.Sequence(ecalMultiFitUncalibRecHit*
                                        kuKsEcalMultiFitUncalibRecHit*
                                        kuWeiEcalMultiFitUncalibRecHit*
                                        kuWeiNotEcalMultiFitUncalibRecHit*
                                        ecalDetIdToBeRecovered)

ku_only_ecalUncalibRecHitSequence = cms.Sequence(kuKsEcalMultiFitUncalibRecHit*
						ecalDetIdToBeRecovered)

kuKsEcalRecHit = ecalRecHit.clone(
	EErechitCollection = cms.string('kuKsEcalRecHitsEE'),
	EEuncalibRecHitCollection = cms.InputTag("kuKsEcalMultiFitUncalibRecHit","kuKsEcalUncalibRecHitsEE"),
	EBuncalibRecHitCollection = cms.InputTag("kuKsEcalMultiFitUncalibRecHit","kuKsEcalUncalibRecHitsEB"),
	EBrechitCollection = cms.string('kuKsEcalRecHitsEB'),
	)

kuKsStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuKsStcEcalRecHitsEE'),
        EEuncalibRecHitCollectioe = cms.InputTag("kuKsEcalMultiFitUncalibRecHit","kuKsEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuKsEcalMultiFitUncalibRecHit","kuKsEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuKsStcEcalRecHitsEB'),
	skipTimeCalib = cms.bool(True),
        )

kuWeiEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuWeiEcalRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuWeiEcalMultiFitUncalibRecHit","kuWeiEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuWeiEcalMultiFitUncalibRecHit","kuWeiEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuWeiEcalRecHitsEB'),
        )

kuWeiStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuWeiStcEcalRecHitsEE'),
        EEuncalibRecHitCollectioe = cms.InputTag("kuWeiEcalMultiFitUncalibRecHit","kuWeiEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuWeiEcalMultiFitUncalibRecHit","kuWeiEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuWeiStcEcalRecHitsEB'),
        skipTimeCalib = cms.bool(True),
        )

kuWeiNotEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuWeiNotEcalRecHitsEE'),
        EEuncalibRecHitCollection = cms.InputTag("kuWeiNotEcalMultiFitUncalibRecHit","kuWeiNotEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuWeiNotEcalMultiFitUncalibRecHit","kuWeiNotEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuWeiNotEcalRecHitsEB'),
        )

kuWeiNotStcEcalRecHit = ecalRecHit.clone(
        EErechitCollection = cms.string('kuWeiNotStcEcalRecHitsEE'),
        EEuncalibRecHitCollectioe = cms.InputTag("kuWeiNotEcalMultiFitUncalibRecHit","kuWeiNotEcalUncalibRecHitsEE"),
        EBuncalibRecHitCollection = cms.InputTag("kuWeiNotEcalMultiFitUncalibRecHit","kuWeiNotEcalUncalibRecHitsEB"),
        EBrechitCollection = cms.string('kuWeiNotStcEcalRecHitsEB'),
        skipTimeCalib = cms.bool(True),
        )

ku_ecalRecHitSequence        = cms.Sequence(ecalRecHit*
					 kuKsEcalRecHit*
                                         ecalCompactTrigPrim*
                                         ecalTPSkim+
                                         ecalPreshowerRecHit)

ku_min_ecalRecHitSequence        = cms.Sequence(ecalRecHit*kuKsEcalRecHit)

ku_only_ecalRecHitSequence        = cms.Sequence(kuKsEcalRecHit)

ku_multi_ecalRecHitSequence        = cms.Sequence(kuKsEcalRecHit*
						kuKsStcEcalRecHit*
						kuWeiEcalRecHit*
						kuWeiStcEcalRecHit*
						kuWeiNotEcalRecHit*
						kuWeiNotStcEcalRecHit)

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


