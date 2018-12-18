#include "Timing/TimingAnalyzer/plugins/Counter.hh"

// N == None
// L == Loose
// T == Tight

Counter::Counter(const edm::ParameterSet& iConfig): 
  // matching criteria
  dRmin(iConfig.existsAs<double>("dRmin") ? iConfig.getParameter<double>("dRmin") : 0.3),
  pTmin(iConfig.existsAs<double>("pTmin") ? iConfig.getParameter<double>("pTmin") : 20.0),
  pTres(iConfig.existsAs<double>("pTres") ? iConfig.getParameter<double>("pTres") : 1.0),

  // cands
  candsTag(iConfig.getParameter<edm::InputTag>("cands")),

  // mets
  metsTag(iConfig.getParameter<edm::InputTag>("mets")),  

  // photons
  gedPhotonsTag(iConfig.getParameter<edm::InputTag>("gedPhotons")),
  ootPhotonsTag(iConfig.getParameter<edm::InputTag>("ootPhotons")),

  // MC objects
  genevtInfoTag(iConfig.getParameter<edm::InputTag>("genevt")),
  pileupInfosTag(iConfig.getParameter<edm::InputTag>("pileup")),
  genpartsTag(iConfig.getParameter<edm::InputTag>("genparts")),

  // MC config
  isMC(iConfig.existsAs<bool>("isMC") ? iConfig.getParameter<bool>("isMC") : false),
  xsec(iConfig.existsAs<double>("xsec") ? iConfig.getParameter<double>("xsec") : 1.0),
  BR(iConfig.existsAs<double>("BR") ? iConfig.getParameter<double>("BR") : 1.0)
{
  usesResource();
  usesResource("TFileService");

  // cands 
  candsToken = consumes<std::vector<pat::PackedCandidate> > (candsTag);

  // mets
  metsToken = consumes<std::vector<pat::MET> > (metsTag);

  // photons
  gedPhotonsToken = consumes<std::vector<pat::Photon> > (gedPhotonsTag);
  ootPhotonsToken = consumes<std::vector<pat::Photon> > (ootPhotonsTag);

  // MC
  if (isMC)
  {
    genevtInfoToken  = consumes<GenEventInfoProduct>             (genevtInfoTag);
    pileupInfosToken = consumes<std::vector<PileupSummaryInfo> > (pileupInfosTag);
    genpartsToken    = consumes<std::vector<reco::GenParticle> > (genpartsTag);
  }
}

Counter::~Counter() {}

void Counter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  // PF CANDIDATES
  iEvent.getByToken(candsToken, candsH);
  cands = *candsH;

  // MET
  iEvent.getByToken(metsToken, metsH);
  mets = *metsH;

  // GEDPHOTONS + IDS
  iEvent.getByToken(gedPhotonsToken, gedPhotonsH);
  gedPhotons = *gedPhotonsH;

  // OOTPHOTONS + IDS
  iEvent.getByToken(ootPhotonsToken, ootPhotonsH);
  ootPhotons = *ootPhotonsH;

  // GEN INFO
  if (isMC)
  {
    // gen evt record
    iEvent.getByToken(genevtInfoToken, genevtInfoH);
    genevtInfo = *genevtInfoH;

    // pileup info
    iEvent.getByToken(pileupInfosToken, pileupInfosH);
    pileupInfos = *pileupInfosH;

    // gen particles
    iEvent.getByToken(genpartsToken, genparticlesH);
    genparticles = *genparticlesH;

    Counter::SetMCInfo();
  }

  // reset counters
  Counter::ResetCounters();

  // set basic counters
  Counter::SetBasicCounters();

  // reset photon indices
  Counter::ResetPhotonIndices();

  // set photon indices
  Counter::SetPhotonIndices();

  // set photon counters
  Counter::SetPhotonCounters();

  // MET
  Counter::SetMETInfo();

  // fill tree
  tree->Fill();
}

void Counter::SetMCInfo()
{
  genwgt = genevtInfo.weight();
  for (const auto & pileupInfo : pileupInfos)
  {
    if (pileupInfo.getBunchCrossing() == 0) 
    {
      genputrue = pileupInfo.getTrueNumInteractions();
      break;
    } // end check over correct BX
  } // end loop over PU
}

void Counter::SetBasicCounters()
{
  // nGED
  nGED_N = gedPhotons.size();
  for (const auto & gedPhoton : gedPhotons)
  {
    if (gedPhoton.photonID(Config::GEDPhotonLooseVID)) nGED_L++;
    if (gedPhoton.photonID(Config::GEDPhotonTightVID)) nGED_T++;
  }

  // nOOT
  nOOT_N = ootPhotons.size();
  for (const auto & ootPhoton : ootPhotons)
  {
    if (ootPhoton.photonID(Config::OOTPhotonLooseVID)) nOOT_L++;
    if (ootPhoton.photonID(Config::OOTPhotonTightVID)) nOOT_T++;
  }
}

void Counter::SetPhotonIndices()
{
  Counter::SetPhotonIndices("NONE","NONE",matchedGTGED_N,matchedLTGED_N,unmatchedGED_N,matchedCands_N);
  Counter::SetPhotonIndices(Config::GEDPhotonLooseVID,Config::OOTPhotonLooseVID,matchedGTGED_L,matchedLTGED_L,unmatchedGED_L,matchedCands_L);
  Counter::SetPhotonIndices(Config::GEDPhotonTightVID,Config::OOTPhotonTightVID,matchedGTGED_T,matchedLTGED_T,unmatchedGED_T,matchedCands_T);
}

void Counter::SetPhotonIndices(const std::string & gedVID, const std::string & ootVID,
			       std::vector<int> & matchedGTGED, std::vector<int> & matchedLTGED,
			       std::vector<int> & unmatchedGED, std::vector<int> & matchedCands)
{
  // save on dereference
  const auto & cands = *candsH;
  const auto & gedPhotons = *gedPhotonsH;
  const auto & ootPhotons = *ootPhotonsH;

  // save on check size
  const auto nCands = cands.size();

  // loop over OOT photons, setting indices
  for (auto ioot = 0; ioot < nOOT_N; ioot++)
  {
    const auto & ootPhoton = ootPhotons[ioot];

    if (ootVID != "NONE") 
      if (!ootPhoton.photonID(ootVID)) continue;

    auto isMatched = true;

    for (auto iged = 0; iged < nGED_N; iged++)
    {
      const auto & gedPhoton = gedPhotons[iged];

      if (gedVID != "NONE") 
	if (!gedPhoton.photonID(gedVID)) continue;
      
      if (reco::deltaR(ootPhoton,gedPhoton) < dRmin)
      {
	if   (Counter::isOOT_GT_GED(gedPhoton,ootPhoton)) matchedGTGED[ioot] = iged;
	else                                              matchedLTGED[ioot] = iged;

	isMatched = true;
	break;
      } // end check over deltaR match
    } // end loop over ged photons

    if (!isMatched)
    {
      unmatchedGED[ioot] = 1;

      for (auto icand = 0U; icand < nCands; icand++)
      {
	const auto & cand = cands[icand];
	
	if (cand.pt() < pTmin) continue;
	for (auto iged = 0; iged < nGED_N; iged++)
	{
	  const auto & gedPhoton = gedPhotons[iged];

	  if (gedVID != "NONE") 
	    if (!gedPhoton.photonID(gedVID)) continue;
	  if (reco::deltaR(gedPhoton,cand) < dRmin) continue;
	  if (reco::deltaR(ootPhoton,cand) < dRmin)
	  {
	    matchedCands[ioot] = icand;
	    break;
	  } // end deltaR match to pfcand
	} // end loop over ged photons
      } // end loop over pf cands
    } // end block over unmatched OOT phos
  } // end loop over ootPhotons
}

void Counter::SetPhotonCounters()
{
  Counter::SetPhotonCounter(matchedGTGED_N,nOOT_matchedGTGED_N);
  Counter::SetPhotonCounter(matchedLTGED_N,nOOT_matchedLTGED_N);
  Counter::SetPhotonCounter(unmatchedGED_N,nOOT_unmatchedGED_N);
  Counter::SetPhotonCounter(matchedCands_N,nOOT_matchedCands_N);

  Counter::SetPhotonCounter(matchedGTGED_L,nOOT_matchedGTGED_L);
  Counter::SetPhotonCounter(matchedLTGED_L,nOOT_matchedLTGED_L);
  Counter::SetPhotonCounter(unmatchedGED_L,nOOT_unmatchedGED_L);
  Counter::SetPhotonCounter(matchedCands_L,nOOT_matchedCands_L);

  Counter::SetPhotonCounter(matchedGTGED_T,nOOT_matchedGTGED_T);
  Counter::SetPhotonCounter(matchedLTGED_T,nOOT_matchedLTGED_T);
  Counter::SetPhotonCounter(unmatchedGED_T,nOOT_unmatchedGED_T);
  Counter::SetPhotonCounter(matchedCands_T,nOOT_matchedCands_T);
}

void Counter::SetPhotonCounter(const std::vector<int> & indices, int & counter)
{
  for (const auto index : indices)
  {
    if (index > 0) counter++;
  }
}

void Counter::SetMETInfo()
{
  const auto & t1pfMET = mets.front();
  const auto & genMET = *(t1pfMET.genMET());
  t1pfMETpt = t1pfMET.pt();
  t1pfMETphi = t1pfMET.phi();
  genMETpt = genMET.pt();
  genMETphi = genMET.phi();
  
  Counter::SetCorrectedMET(matchedGTGED_N,matchedLTGED_N,unmatchedGED_N,ootMETpt_N,ootMETphi_N);
  Counter::SetCorrectedMET(matchedGTGED_L,matchedLTGED_L,unmatchedGED_L,ootMETpt_L,ootMETphi_L);
  Counter::SetCorrectedMET(matchedGTGED_T,matchedLTGED_T,unmatchedGED_T,ootMETpt_T,ootMETphi_T);
}

void Counter::SetCorrectedMET(const std::vector<int> & matchedGTGED, const std::vector<int> & matchedLTGED,
			      const std::vector<int> & unmatchedGED, float & ootMETpt, float & ootMETphi)
{
  // initialize
  ootMETpt  = t1pfMETpt;
  ootMETphi = t1pfMETphi;

  // change the MET
  for (auto ioot = 0; ioot < nOOT_N; ioot++)
  {
    // skip if matched, but lower in pT
    if (matchedLTGED[ioot] < 0) continue;

    // get ootPhoton info --> will use it regardless!
    const auto & ootPhoton = ootPhotons[ioot];
    const auto ootpt  = (ootPhoton.userFloat("ecalEnergyPostCorr")/ootPhoton.energy())*ootPhoton.pt();
    const auto ootphi = ootPhoton.phi();
    
    // first change MET with non-overlapping OOT photons
    if (unmatchedGED[ioot] > 0)
    {
      // get compnonents
      const auto x = ootMETpt*std::cos(ootMETphi) - ootpt*std::cos(ootphi);
      const auto y = ootMETpt*std::sin(ootMETphi) - ootpt*std::sin(ootphi);
      
      // make new met
      ootMETpt  = Config::hypo(x,y);
      ootMETphi = Config::phi (x,y);
    } // end check over non-overlapping OOT photons

    // then, change MET with overlapping OOT photons
    if (matchedGTGED[ioot] >= 0)
    {
      // get gedPhoton info
      const auto & gedPhoton = gedPhotons[matchedGTGED[ioot]];
      const auto gedpt  = (gedPhoton.userFloat("ecalEnergyPostCorr")/gedPhoton.energy())*gedPhoton.pt();
      const auto gedphi = gedPhoton.phi();

      // get compnonents
      const auto x = ootMETpt*std::cos(ootMETphi) - ootpt*std::cos(ootphi) + gedpt*std::cos(gedphi);
      const auto y = ootMETpt*std::sin(ootMETphi) - ootpt*std::sin(ootphi) + gedpt*std::sin(gedphi);
  
      // make new met
      ootMETpt  = Config::hypo(x,y);
      ootMETphi = Config::phi (x,y);
    } // end check over overlapping OOT photons
  } // end loop over OOT photons
}

//////////////////////
// Helper Functions //
//////////////////////

bool Counter::isOOT_GT_GED(const pat::Photon & gedPhoton, const pat::Photon & ootPhoton)
{
  const auto gedpt = (gedPhoton.userFloat("ecalEnergyPostCorr")/gedPhoton.energy())*gedPhoton.pt();
  const auto ootpt = (ootPhoton.userFloat("ecalEnergyPostCorr")/ootPhoton.energy())*ootPhoton.pt();
  return (ootpt > gedpt);
}

void Counter::ResetCounters()
{
  nGED_N = 0;
  nOOT_N = 0;
  nOOT_matchedGTGED_N = 0;
  nOOT_matchedLTGED_N = 0;
  nOOT_unmatchedGED_N = 0;
  nOOT_matchedCands_N = 0;

  nGED_L = 0;
  nOOT_L = 0;
  nOOT_matchedGTGED_L = 0;
  nOOT_matchedLTGED_L = 0;
  nOOT_unmatchedGED_L = 0;
  nOOT_matchedCands_L = 0;
 
  nGED_T = 0;
  nOOT_T = 0;
  nOOT_matchedGTGED_T = 0;
  nOOT_matchedLTGED_T = 0;
  nOOT_unmatchedGED_T = 0;
  nOOT_matchedCands_T = 0;
}

void Counter::ResetPhotonIndices()
{
  Counter::ResetPhotonIndices(matchedGTGED_N);
  Counter::ResetPhotonIndices(matchedLTGED_N);
  Counter::ResetPhotonIndices(unmatchedGED_N);
  Counter::ResetPhotonIndices(matchedCands_N);

  Counter::ResetPhotonIndices(matchedGTGED_L);
  Counter::ResetPhotonIndices(matchedLTGED_L);
  Counter::ResetPhotonIndices(unmatchedGED_L);
  Counter::ResetPhotonIndices(matchedCands_L);

  Counter::ResetPhotonIndices(matchedGTGED_T);
  Counter::ResetPhotonIndices(matchedLTGED_T);
  Counter::ResetPhotonIndices(unmatchedGED_T);
  Counter::ResetPhotonIndices(matchedCands_T);
}

void Counter::ResetPhotonIndices(std::vector<int> & indices)
{
  indices.resize(nOOT_N); // loop over all oot photons in the event
  for (auto & index : indices) index = -1;
}

////////////////////////
// Internal Functions //
////////////////////////
			   
void Counter::beginJob()
{
  edm::Service<TFileService> fs;
  
  // Event tree
  tree = fs->make<TTree>("tree","tree");

  // MC info
  if (isMC)
  {
    tree->Branch("genwgt", &genwgt, "genwgt/F");
    tree->Branch("xsec", &xsec, "xsec/F");
    tree->Branch("BR", &BR, "BR/F");
    tree->Branch("genputrue", &genputrue, "genputrue/I");
  }

  // counter info
  tree->Branch("nGED_N", &nGED_N, "nGED_N/I");
  tree->Branch("nOOT_N", &nOOT_N, "nOOT_N/I");
  tree->Branch("nOOT_matchedGTGED_N", &nOOT_matchedGTGED_N, "nOOT_matchedGTGED_N/I");
  tree->Branch("nOOT_matchedLTGED_N", &nOOT_matchedLTGED_N, "nOOT_matchedLTGED_N/I");
  tree->Branch("nOOT_unmatchedGED_N", &nOOT_unmatchedGED_N, "nOOT_unmatchedGED_N/I");
  tree->Branch("nOOT_matchedCands_N", &nOOT_matchedCands_N, "nOOT_matchedCands_N/I");

  tree->Branch("nGED_L", &nGED_L, "nGED_L/I");
  tree->Branch("nOOT_L", &nOOT_L, "nOOT_L/I");
  tree->Branch("nOOT_matchedGTGED_L", &nOOT_matchedGTGED_L, "nOOT_matchedGTGED_L/I");
  tree->Branch("nOOT_matchedLTGED_L", &nOOT_matchedLTGED_L, "nOOT_matchedLTGED_L/I");
  tree->Branch("nOOT_unmatchedGED_L", &nOOT_unmatchedGED_L, "nOOT_unmatchedGED_L/I");
  tree->Branch("nOOT_matchedCands_L", &nOOT_matchedCands_L, "nOOT_matchedCands_L/I");
 
  tree->Branch("nGED_T", &nGED_T, "nGED_T/I");
  tree->Branch("nOOT_T", &nOOT_T, "nOOT_T/I");
  tree->Branch("nOOT_matchedGTGED_T", &nOOT_matchedGTGED_T, "nOOT_matchedGTGED_T/I");
  tree->Branch("nOOT_matchedLTGED_T", &nOOT_matchedLTGED_T, "nOOT_matchedLTGED_T/I");
  tree->Branch("nOOT_unmatchedGED_T", &nOOT_unmatchedGED_T, "nOOT_unmatchedGED_T/I");
  tree->Branch("nOOT_matchedCands_T", &nOOT_matchedCands_T, "nOOT_matchedCands_T/I");

  // MET info
  tree->Branch("t1pfMETpt", &t1pfMETpt, "t1pfMETpt/F");
  tree->Branch("t1pfMETphi", &t1pfMETphi, "t1pfMETphi/F");
  tree->Branch("genMETpt", &genMETpt, "genMETpt/F");
  tree->Branch("genMETphi", &genMETphi, "genMETphi/F");

  tree->Branch("ootMETpt_N", &ootMETpt_N, "ootMETpt_N/F");
  tree->Branch("ootMETphi_N", &ootMETphi_N, "ootMETphi_N/F");

  tree->Branch("ootMETpt_L", &ootMETpt_L, "ootMETpt_L/F");
  tree->Branch("ootMETphi_L", &ootMETphi_L, "ootMETphi_L/F");

  tree->Branch("ootMETpt_T", &ootMETpt_T, "ootMETpt_T/F");
  tree->Branch("ootMETphi_T", &ootMETphi_T, "ootMETphi_T/F");
}

void Counter::endJob() {}

void Counter::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup) {}

void Counter::endRun(edm::Run const&, edm::EventSetup const&) {}

void Counter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) 
{
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(Counter);
