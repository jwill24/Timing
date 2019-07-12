#include "alcap0_ana.h"
#include "L1Trigger/L1TCalorimeter/src/CaloTools.cc"
#include "L1Trigger/L1TCalorimeter/src/CaloStage2Nav.cc"

alcap0_ana::alcap0_ana(const edm::ParameterSet& ps) :
	stage2CaloLayer2EGammaToken_(consumes<l1t::EGammaBxCollection>(ps.getParameter<edm::InputTag>("stage2CaloLayer2EGammaProducer")))
{}

alcap0_ana::~alcap0_ana(){}

void alcap0_ana::analyze(const edm::Event& e, const edm::EventSetup& c) 
{

  // EGamma Collection
  edm::Handle<l1t::EGammaBxCollection> EGammaBxCollection;
  e.getByToken(stage2CaloLayer2EGammaToken_, EGammaBxCollection);

  // Filling eta-phi map for egamma for BX=-2,-1,0,+1,+2
//  for (int itBX = EGammaBxCollection->getFirstBX(); itBX <= EGammaBxCollection->getLastBX(); ++itBX) {
    int itBX = 0;
     for (l1t::EGammaBxCollection::const_iterator egamma = EGammaBxCollection->begin(itBX); egamma != EGammaBxCollection->end(itBX); ++egamma) {

//std::cout << "EGamma Object: Event " << e.id().event() << " BX " << itBX << " "<< " Eta: " << egamma->eta() << " Phi: " << egamma->phi() << std::endl;
        towerIEta = egamma->towerIEta();
        towerIPhi = egamma->towerIPhi();
        rawEt = egamma->rawEt();
        isoEt = egamma->isoEt();
        footprintEt = egamma->footprintEt();
        nTT = egamma->nTT();
        shape = egamma->shape();

        towerHoE = egamma->towerHoE();
        hwPt = egamma->hwPt();
        hwEta = egamma->hwEta();
        hwPhi = egamma->hwPhi();
        hwQual = egamma->hwQual();
        hwIso = egamma->hwIso();

	eta = egamma->eta();
	phi = egamma->phi();

	towerEta = l1t::CaloTools::towerEta(hwEta);
	towerPhi = l1t::CaloTools::towerPhi(hwEta,hwPhi);

        hwEtaHist->Fill(hwEta);
        etaHist->Fill(eta);
        hwPhiHist->Fill(hwPhi);
        phiHist->Fill(phi);
	hwEtaPhiHist->Fill(hwEta, hwPhi);
        etaPhiHist->Fill(eta, phi);


	alcap0_anaTree->Fill();

//      if (egamma->pt() >= egammaPtCut_) {
//        denominator_egamma->Fill(egamma->eta(), egamma->phi());
//        int index = itBX - std::min(0, 1 - (int)bxrange_%2 - (int)std::floor(bxrange_/2.)); // the correlation from itBX to respective index of the vector
//        egamma_eta_phi.at(index)->Fill(egamma->eta(), egamma->phi());
//      }

    } // egamma loop
//  } // bx loop
}

void alcap0_ana::beginJob() {

        edm::Service<TFileService> fs;
        alcap0_anaTree = fs->make<TTree>("alcap0_anaTree",""); //"alcap0_anaTree");
	hwEtaHist = fs->make<TH1F>("hwEtaHist","",171,-85.5,85.5);
        etaHist = fs->make<TH1F>("etaHist","",64,-3.2,3.2);
	hwPhiHist = fs->make<TH1F>("hwPhiHist","",181,-0.5,180.5);
        phiHist = fs->make<TH1F>("phiHist","",128,-6.4,6.4);
	hwEtaPhiHist = fs->make<TH2F>("hwEtaPhiHst","",171,-85.5,85.5,181,-0.5,180.5);
	etaPhiHist = fs->make<TH2F>("etaPhiHist","",1024,-3.2,3.2,1024,-3.2,3.2);


        alcap0_anaTree->Branch("towerIEta", &towerIEta, "towerIEta/I");
        alcap0_anaTree->Branch("towerIPhi", &towerIPhi, "towerIPhi/I");
        alcap0_anaTree->Branch("rawEt", &rawEt, "rawEt/I");
        alcap0_anaTree->Branch("isoEt", &isoEt, "isoEt/I");
        alcap0_anaTree->Branch("footprintEt", &footprintEt, "footprintEt/I");
        alcap0_anaTree->Branch("nTT", &nTT, "nTT/I");
        alcap0_anaTree->Branch("shape", &shape, "shape/I");

        alcap0_anaTree->Branch("hwPt", &hwPt, "hwPt/I");
        alcap0_anaTree->Branch("hwEta", &hwEta, "hwEta/I");
        alcap0_anaTree->Branch("hwPhi", &hwPhi, "hwPhi/I");
        alcap0_anaTree->Branch("hwQual", &hwQual, "hwQual/I");
        alcap0_anaTree->Branch("hwIso", &hwIso, "hwIso/I");

        alcap0_anaTree->Branch("towerEta", &towerEta, "towerEta/F");
        alcap0_anaTree->Branch("towerPhi", &towerPhi, "towerPhi/F");

        alcap0_anaTree->Branch("eta", &eta, "eta/D");
        alcap0_anaTree->Branch("phi", &phi, "phi/D");

}

void alcap0_ana::endJob() {}


void alcap0_ana::beginRun(edm::Run const& iRuI, edm::EventSetup const& iSetup) {}

void alcap0_ana::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup) {}

DEFINE_FWK_MODULE(alcap0_ana);
