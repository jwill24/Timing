import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff import *
#from PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff import *
from Timing.TimingAnalyzer.jwk_selectedPatCandidates_cff import *
#from PhysicsTools.PatAlgos.slimming.slimming_cff import *
from Timing.TimingAnalyzer.jwk_slimming_cff import *
#from RecbunchSpacingProducer_cfi import *

#print( ">>>>>>>>>>>> jwk PAT accessed" )

patTask = cms.Task(
    patCandidatesTask,
    selectedPatCandidatesTask,
    slimmingTask,
    #bunchSpacingProducer
)

miniAOD=cms.Sequence()
