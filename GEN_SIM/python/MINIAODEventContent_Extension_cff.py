import FWCore.ParameterSet.Config as cms

### EventContent_cff actually goes to slimming.slimming_cff --> bypass this and go straight to the source ###
# from PhysicsTools.PatAlgos.slimming.MicroEventContent_cff import MicroEventContent,MicroEventContentMC 

# MicroEventContent = cms.PSet(
#     outputCommands = cms.untracked.vstring(
#         'keep *_slimmedPhotons_*_*',
#         'keep *_slimmedElectrons_*_*',
#         'keep *_slimmedMuons_*_*',
#         'keep *_slimmedTaus_*_*',
#         'keep *_slimmedTausBoosted_*_*',
#         'keep *_slimmedJets_*_*',
#         'keep *_slimmedJetsAK8_*_*',
#         'keep *_slimmedJetsPuppi_*_*',
#         'keep *_slimmedMETs_*_*',
#         'keep *_slimmedMETsNoHF_*_*',
#         'keep *_slimmedMETsPuppi_*_*',
#         'keep *_slimmedSecondaryVertices_*_*',
#         'keep *_slimmedJetsAK8PFCHSSoftDropPacked_SubJets_*',
#         'keep *_slimmedJetsAK8PFPuppiSoftDropPacked_SubJets_*',
        
#         'keep recoPhotonCores_reducedEgamma_*_*',
#         'keep recoGsfElectronCores_reducedEgamma_*_*',
#         'keep recoConversions_reducedEgamma_*_*',
#         'keep recoSuperClusters_reducedEgamma_*_*',
#         'keep recoCaloClusters_reducedEgamma_*_*',
#         'keep EcalRecHitsSorted_reducedEgamma_*_*',

#         'drop *_*_caloTowers_*',
#         'drop *_*_pfCandidates_*',
#         'drop *_*_genJets_*',

#         'keep *_offlineBeamSpot_*_*',
#         'keep *_offlineSlimmedPrimaryVertices_*_*',
#         'keep patPackedCandidates_packedPFCandidates_*_*',

#         'keep *_bunchSpacingProducer_*_*',

#         'keep double_fixedGridRhoAll__*',
#         'keep double_fixedGridRhoFastjetAll__*',
#         'keep double_fixedGridRhoFastjetAllCalo__*',
#         'keep double_fixedGridRhoFastjetCentral_*_*',
#         'keep double_fixedGridRhoFastjetCentralCalo__*',
#         'keep double_fixedGridRhoFastjetCentralChargedPileUp__*',
#         'keep double_fixedGridRhoFastjetCentralNeutral__*',

#         'keep *_selectedPatTrigger_*_*',
#         'keep patPackedTriggerPrescales_patTrigger__*',
#         'keep patPackedTriggerPrescales_patTrigger_l1max_*',
#         'keep patPackedTriggerPrescales_patTrigger_l1min_*',
#         # old L1 trigger
#         'keep *_l1extraParticles_*_*',
#         'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
#         # stage 2 L1 trigger
#         'keep *_gtStage2Digis__*', 
#         'keep *_gmtStage2Digis_Muon_*',
#         'keep *_caloStage2Digis_Jet_*',
#         'keep *_caloStage2Digis_Tau_*',
#         'keep *_caloStage2Digis_EGamma_*',
#         'keep *_caloStage2Digis_EtSum_*',
#         # HLT
#         'keep *_TriggerResults_*_HLT',
#         'keep *_TriggerResults_*_*', # for MET filters (a catch all for the moment, but ideally it should be only the current process)
#         'keep patPackedCandidates_lostTracks_*_*',
#         'keep HcalNoiseSummary_hcalnoise__*',
#         'keep recoCSCHaloData_CSCHaloData_*_*',
#         'keep recoBeamHaloSummary_BeamHaloSummary_*_*',
#         # Lumi
#         'keep LumiScalerss_scalersRawToDigi_*_*',
#     )
# )

### Finally, declare anew MINIAODEventContent ###

from Configuration.EventContent.EventContent_cff import MINIAODEventContent

MINIAODEventContent= cms.PSet(    
    outputCommands = cms.untracked.vstring(
        'keep *_slimmedPhotons_*_*',
        'keep *_slimmedElectrons_*_*',
        'keep *_slimmedMuons_*_*',
        'keep *_slimmedTaus_*_*',
        'keep *_slimmedTausBoosted_*_*',
        'keep *_slimmedJets_*_*',
        'keep *_slimmedJetsAK8_*_*',
        'keep *_slimmedJetsPuppi_*_*',
        'keep *_slimmedMETs_*_*',
        'keep *_slimmedMETsNoHF_*_*',
        'keep *_slimmedMETsPuppi_*_*',
        'keep *_slimmedSecondaryVertices_*_*',
        'keep *_slimmedJetsAK8PFCHSSoftDropPacked_SubJets_*',
        'keep *_slimmedJetsAK8PFPuppiSoftDropPacked_SubJets_*',
        
        'keep recoPhotonCores_reducedEgamma_*_*',
        'keep recoGsfElectronCores_reducedEgamma_*_*',
        'keep recoConversions_reducedEgamma_*_*',
        'keep recoSuperClusters_reducedEgamma_*_*',
        'keep recoCaloClusters_reducedEgamma_*_*',
        'keep EcalRecHitsSorted_reducedEgamma_*_*',

        'drop *_*_caloTowers_*',
        'drop *_*_pfCandidates_*',
        'drop *_*_genJets_*',

        'keep *_offlineBeamSpot_*_*',
        'keep *_offlineSlimmedPrimaryVertices_*_*',
        'keep patPackedCandidates_packedPFCandidates_*_*',

        'keep *_bunchSpacingProducer_*_*',

        'keep double_fixedGridRhoAll__*',
        'keep double_fixedGridRhoFastjetAll__*',
        'keep double_fixedGridRhoFastjetAllCalo__*',
        'keep double_fixedGridRhoFastjetCentral_*_*',
        'keep double_fixedGridRhoFastjetCentralCalo__*',
        'keep double_fixedGridRhoFastjetCentralChargedPileUp__*',
        'keep double_fixedGridRhoFastjetCentralNeutral__*',

        'keep *_selectedPatTrigger_*_*',
        'keep patPackedTriggerPrescales_patTrigger__*',
        'keep patPackedTriggerPrescales_patTrigger_l1max_*',
        'keep patPackedTriggerPrescales_patTrigger_l1min_*',
        # old L1 trigger
        'keep *_l1extraParticles_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
        # stage 2 L1 trigger
        'keep *_gtStage2Digis__*', 
        'keep *_gmtStage2Digis_Muon_*',
        'keep *_caloStage2Digis_Jet_*',
        'keep *_caloStage2Digis_Tau_*',
        'keep *_caloStage2Digis_EGamma_*',
        'keep *_caloStage2Digis_EtSum_*',
        # HLT
        'keep *_TriggerResults_*_HLT',
        'keep *_TriggerResults_*_*', # for MET filters (a catch all for the moment, but ideally it should be only the current process)
        'keep patPackedCandidates_lostTracks_*_*',
        'keep HcalNoiseSummary_hcalnoise__*',
        'keep recoCSCHaloData_CSCHaloData_*_*',
        'keep recoBeamHaloSummary_BeamHaloSummary_*_*',
        # Lumi
        'keep LumiScalerss_scalersRawToDigi_*_*',
        ),
    eventAutoFlushCompressedSize=cms.untracked.int32(15*1024*1024),
    compressionAlgorithm=cms.untracked.string("LZMA"),
    compressionLevel=cms.untracked.int32(4)
)

