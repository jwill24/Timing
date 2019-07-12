
// System include files
#include <memory>
#include <vector>
#include <array>
#include <algorithm>
#include <string>

// ROOT
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "Math/PositionVector3D.h"

#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/EtSum.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"

#include "L1Trigger/L1TCalorimeter/interface/CaloTools.h"
#include "L1Trigger/L1TCalorimeter/interface/CaloStage2Nav.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h" 

class alcap0_ana : public edm::one::EDAnalyzer<> {

 public:

  alcap0_ana(const edm::ParameterSet& ps);
  ~alcap0_ana();

 protected:

  virtual void beginJob();
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);

 private:  

  TTree * alcap0_anaTree;
  TH1F * hwEtaHist;
  TH1F * hwPhiHist;
  TH2F * hwEtaPhiHist;
  TH1F * etaHist;
  TH1F * phiHist;
  TH2F * etaPhiHist;
  
  const edm::InputTag stage2CaloLayer2EGammaTag;
  edm::EDGetTokenT<l1t::EGammaBxCollection> stage2CaloLayer2EGammaToken_;

  short int towerIEta;
  short int towerIPhi;
  short int rawEt;
  short int isoEt;
  short int footprintEt;
  short int nTT;
  short int shape;
  short int towerHoE;

  // integer "hardware" values
  int hwPt;
  int hwEta;
  int hwPhi;
  int hwQual;
  int hwIso;

  float towerEta;
  float towerPhi;

  double eta;
  double phi;

};

