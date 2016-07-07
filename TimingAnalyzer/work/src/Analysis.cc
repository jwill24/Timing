#include "../interface/Analysis.hh"
#include "TROOT.h"

#include "TH1D.h"

inline Float_t rad2 (Float_t x, Float_t y){return x*x + y*y;}
inline Float_t theta(Float_t r, Float_t z){return std::atan2(r,z);}
inline Float_t eta  (Float_t x, Float_t y, Float_t z)
{
  return -1.0f*std::log(std::tan(theta(std::sqrt(rad2(x,y)),z)/2.f));
}
inline Float_t TOF  (Float_t x, Float_t y, Float_t z, Float_t vx, Float_t vy, Float_t vz, Float_t time)
{
  return time + (std::sqrt(z*z+rad2(x,y))-std::sqrt((z-vz)*(z-vz)+rad2((x-vx),(y-vy))))/Config::sol;
}
inline Float_t effA (Float_t e1, Float_t e2){return e1*e2/std::sqrt(rad2(e1,e2));}

Analysis::Analysis(TString sample, Bool_t isMC) : fSample(sample), fIsMC(isMC) 
{
  // because root is dumb?
  gROOT->ProcessLine("#include <vector>");

  // Set input
  TString filename = Form("input/%s/%s/%s", (fIsMC?"MC":"DATA"), fSample.Data(), (Config::useFull?"tree.root":"skimmedtree.root"));
  fInFile  = TFile::Open(filename.Data());
  CheckValidFile(fInFile,filename);

  TString treename = "tree/tree";
  fInTree = (TTree*)fInFile->Get(treename.Data());
  CheckValidTree(fInTree,treename,filename);
  InitTree();
  
  // Set Output Stuff
  fOutDir = Form("%s/%s/%s",Config::outdir.Data(), (fIsMC?"MC":"DATA"), fSample.Data());
  MakeOutDir(fOutDir);
  fOutFile = new TFile(Form("%s/plots.root",fOutDir.Data()),"UPDATE");
  fColor = (fIsMC?Config::colorMap[fSample]:kBlack);
  
  // extra setup for data and MC
  if (fIsMC) { 
    // Get pile-up weights
    TString purwfname = "input/PU/pileupWeights.root";
    TFile * purwfile  = TFile::Open(purwfname.Data());
    CheckValidFile(purwfile,purwfname);

    TH1D * gen_pu    = (TH1D*) purwfile->Get("generated_pu");
    CheckValidTH1D(gen_pu,"generated_pu",purwfname);
    TH1D * puweights = (TH1D*) purwfile->Get("weights");
    CheckValidTH1D(puweights,"weights",purwfname);

    TH1D* weightedPU= (TH1D*)gen_pu->Clone("weightedPU");
    weightedPU->Multiply(puweights);
    TH1D* weights = (TH1D*)puweights->Clone("rescaledWeights");
    weights->Scale( gen_pu->Integral(1,Config::nbinsvtx) / weightedPU->Integral(1,Config::nbinsvtx) );

    for (Int_t i = 1; i <= Config::nbinsvtx; i++){
      fPUweights.push_back(weights->GetBinContent(i));
    }

    delete gen_pu;
    delete puweights;
    delete weightedPU;
    delete weights;
    delete purwfile;
    // end getting pile-up weights

    // set sample xsec + wgtsum
    fXsec   = Config::SampleXsecMap[fSample];
    fWgtsum = Config::SampleWgtsumMap[fSample];
  }  
  else{
    fTH1Dump.open(Form("%s/%s",Config::outdir.Data(),Config::plotdumpname.Data()),std::ios_base::trunc); // do this once, and just do it for data
  }
}

Analysis::~Analysis()
{
  delete fInTree;
  delete fInFile;
  delete fOutFile;
  if (!fIsMC) fTH1Dump.close();
}

void Analysis::EventLoop()
{
  // Set up hists first --> first in map is histo name, by design!
  if (Config::doStandard) Analysis::SetupStandardPlots();
  if (Config::doZvars)    Analysis::SetupZPlots();
  if (Config::doEffE)     Analysis::SetupEffEPlots();
  if (Config::doNvtx)     Analysis::SetupNvtxPlots();
  if (Config::doEta)      Analysis::SetupEtaPlots();
  if (Config::doVtxZ)     Analysis::SetupVtxZPlots();
  if (Config::doSingleE)  Analysis::SetupSingleEPlots();
  if (Config::doRuns)     Analysis::SetupRunPlots();
  if (Config::doTrigEff)  Analysis::SetupTrigEffPlots();

  // do loop over events, filling histos
  for (UInt_t entry = 0; entry < (!Config::doDemo?fInTree->GetEntries():Config::demoNum); entry++){
    fInTree->GetEntry(entry);
    if ((zmass>Config::zlow && zmass<Config::zhigh) && hltdoubleel && (el1pid == -el2pid)) { // extra selection over skimmed samples

      // determine event weight
      Float_t weight = -1.;
      if   (fIsMC) {weight = (fXsec * Config::lumi * wgt / fWgtsum) * fPUweights[putrue];}
      else         {weight = 1.0;}

      // determine ecal partitions
      const Float_t el1seedeta = eta(el1seedX,el1seedY,el1seedZ);
      Bool_t el1eb = false; Bool_t el1ee = false;
      if      (std::abs(el1seedeta) < Config::etaEB)                                                { el1eb = true; }
      else if (std::abs(el1seedeta) > Config::etaEElow && std::abs(el1seedeta) < Config::etaEEhigh) { el1ee = true; }
      Bool_t el1ep = false; Bool_t el1em = false;
      if (el1ee) {
	if      (el1seedZ>0) {el1ep = true;}
	else if (el1seedZ<0) {el1em = true;}
      }

      const Float_t el2seedeta = eta(el2seedX,el2seedY,el2seedZ);
      Bool_t el2eb = false; Bool_t el2ee = false;
      if      (std::abs(el2seedeta) < Config::etaEB)                                                { el2eb = true; }
      else if (std::abs(el2seedeta) > Config::etaEElow && std::abs(el2seedeta) < Config::etaEEhigh) { el2ee = true; }
      Bool_t el2ep = false; Bool_t el2em = false;
      if (el2ee) {
	if      (el2seedZ>0) {el2ep = true;}
	else if (el2seedZ<0) {el2em = true;}
      }
      
      // correct for sigma_n
      if (Config::useSigma_n) {
	el1pt    /= Config::sigma_n; el2pt    /= Config::sigma_n;
	el1p     /= Config::sigma_n; el2p     /= Config::sigma_n;
	el1scE   /= Config::sigma_n; el2scE   /= Config::sigma_n;
	el1E     /= Config::sigma_n; el2E     /= Config::sigma_n;
	el1seedE /= Config::sigma_n; el2seedE /= Config::sigma_n;
      }

      // get the proper times
      Float_t el1time = -99.0;
      if   (Config::applyTOF && !Config::wgtedtime) {el1time = TOF(el1seedX,el1seedY,el1seedZ,vtxX,vtxY,vtxZ,el1seedtime);}
      else                                          {el1time = el1seedtime;}

      Float_t el2time = -99.0;
      if   (Config::applyTOF && !Config::wgtedtime) {el2time = TOF(el2seedX,el2seedY,el2seedZ,vtxX,vtxY,vtxZ,el2seedtime);}
      else                                          {el2time = el2seedtime;}

      // calculate constants
      const Float_t timediff = el1time-el2time;
      const Float_t effpt    = effA(el1pt,el2pt);
      const Float_t effE     = effA(el1E,el2E);
      const Float_t effseedE = effA(el1seedE,el2seedE);

      // fill the plots
      if (Config::doStandard) Analysis::FillStandardPlots(weight,timediff,effpt,effE,effseedE,el1time,el1seedeta,el1eb,el1ee,el1ep,el1em,el2time,el2seedeta,el2eb,el2ee,el2ep,el2em);
      if (Config::doZvars)    Analysis::FillZPlots(weight,timediff);
      if (Config::doEffE)     Analysis::FillEffEPlots(weight,timediff,effpt,effE,effseedE,el1eb,el1ee,el1ep,el1em,el2eb,el2ee,el2ep,el2em);
      if (Config::doNvtx)     Analysis::FillNvtxPlots(weight,timediff,el1time,el2time,el1eb,el1ee,el1ep,el1em,el2eb,el2ee,el2ep,el2em);
      if (Config::doEta)      Analysis::FillEtaPlots(weight,timediff,el1time,el2time,el1seedeta,el2seedeta);
      if (Config::doVtxZ)     Analysis::FillVtxZPlots(weight,timediff,el1time,el2time);
      if (Config::doSingleE)  Analysis::FillSingleEPlots(weight,el1time,el2time,el1eb,el1ee,el1ep,el1em,el2eb,el2ee,el2ep,el2em);
      if (Config::doRuns)     Analysis::FillRunPlots(weight,timediff,el1eb,el1ee,el2eb,el2ee);
      if (Config::doTrigEff)  Analysis::FillTrigEffPlots(weight);
    } // end check over selection
  } // end loop over events
  
  // output hists
  if (Config::doStandard) Analysis::OutputStandardPlots();
  if (Config::doZvars)    Analysis::OutputZPlots();
  if (Config::doEffE)     Analysis::OutputEffEPlots();
  if (Config::doNvtx)     Analysis::OutputNvtxPlots();
  if (Config::doEta)      Analysis::OutputEtaPlots();
  if (Config::doVtxZ)     Analysis::OutputVtxZPlots();
  if (Config::doSingleE)  Analysis::OutputSingleEPlots();
  if (Config::doRuns)     Analysis::OutputRunPlots();
  if (Config::doTrigEff)  Analysis::OutputTrigEffPlots();
}

void Analysis::SetupStandardPlots()
{
  // event based variables
  standardTH1Map["nvtx"]    = Analysis::MakeTH1Plot("nvtx","",Config::nbinsvtx,0.,Double_t(Config::nbinsvtx),"nVertices","Events",standardTH1SubMap,"standard");
  standardTH1Map["vtxZ"]    = Analysis::MakeTH1Plot("vtxZ","",100,-15.0,15.0,"PV z position [cm]","Events",standardTH1SubMap,"standard");

  // z variables
  standardTH1Map["zpt"]     = Analysis::MakeTH1Plot("zpt","",100,0.,750.,"Dielectron p_{T} [GeV/c^{2}]","Events",standardTH1SubMap,"standard");
  standardTH1Map["zeta"]    = Analysis::MakeTH1Plot("zeta","",100,-10.0,10.0,"Dielectron #eta","Events",standardTH1SubMap,"standard");
  standardTH1Map["abszeta"] = Analysis::MakeTH1Plot("abszeta","",100,0.0,10.0,"Dielectron |#eta|","Events",standardTH1SubMap,"standard");
  standardTH1Map["zphi"]    = Analysis::MakeTH1Plot("zphi","",100,-Config::PI,Config::PI,"Dielectron #phi","Events",standardTH1SubMap,"standard");

  // zmass 
  standardTH1Map["zmass"]      = Analysis::MakeTH1Plot("zmass","",100,Config::zlow,Config::zhigh,"Dielectron invariant mass [GeV/c^{2}]","Events",standardTH1SubMap,"standard");
  standardTH1Map["zmass_EBEB"] = Analysis::MakeTH1Plot("zmass_EBEB","",100,Config::zlow,Config::zhigh,"Dielectron invariant mass [GeV/c^{2}] (EBEB)","Events",standardTH1SubMap,"standard");
  standardTH1Map["zmass_EEEE"] = Analysis::MakeTH1Plot("zmass_EEEE","",100,Config::zlow,Config::zhigh,"Dielectron invariant mass [GeV/c^{2}] (EEEE)","Events",standardTH1SubMap,"standard");
  standardTH1Map["zmass_EMEM"] = Analysis::MakeTH1Plot("zmass_EMEM","",100,Config::zlow,Config::zhigh,"Dielectron invariant mass [GeV/c^{2}] (EE-EE-)","Events",standardTH1SubMap,"standard");
  standardTH1Map["zmass_EPEP"] = Analysis::MakeTH1Plot("zmass_EPEP","",100,Config::zlow,Config::zhigh,"Dielectron invariant mass [GeV/c^{2}] (EE+EE+)","Events",standardTH1SubMap,"standard");
  standardTH1Map["zmass_EBEE"] = Analysis::MakeTH1Plot("zmass_EBEE","",100,Config::zlow,Config::zhigh,"Dielectron invariant mass [GeV/c^{2}] (EBEE)","Events",standardTH1SubMap,"standard");

  // effective energies
  standardTH1Map["eff_dielpt"]  = Analysis::MakeTH1Plot("eff_dielpt","",100,0.,Config::XHighMap["effpt"],Form("Effective Dielectron %s",Config::XTitleMap["pt"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["eff_dielE"]   = Analysis::MakeTH1Plot("eff_dielE","",100,0.,Config::XHighMap["effE"],Form("Effective Dielectron %s",Config::XTitleMap["E"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["eff_diseedE"] = Analysis::MakeTH1Plot("eff_diseedE","",100,0.,Config::XHighMap["effseedE"],Form("Effective Dielectron Seed %s",Config::XTitleMap["E"].Data()),"Events",standardTH1SubMap,"standard");

  // el1 and el2 variables
  standardTH1Map["el1phi"]     = Analysis::MakeTH1Plot("el1phi","",100,-Config::PI,Config::PI,"Leading Electron #phi","Events",standardTH1SubMap,"standard");
  standardTH1Map["el1eta"]     = Analysis::MakeTH1Plot("el1eta","",100,-3.0,3.0,"Leading Electron #eta","Events",standardTH1SubMap,"standard");
  standardTH1Map["el1seedeta"] = Analysis::MakeTH1Plot("el1seedeta","",100,-3.0,3.0,"Leading Electron Seed #eta","Events",standardTH1SubMap,"standard");

  standardTH1Map["el2phi"]     = Analysis::MakeTH1Plot("el2phi","",100,-Config::PI,Config::PI,"Subleading Electron #phi","Events",standardTH1SubMap,"standard");
  standardTH1Map["el2eta"]     = Analysis::MakeTH1Plot("el2eta","",100,-3.0,3.0,"Subleading Electron #eta","Events",standardTH1SubMap,"standard");
  standardTH1Map["el2seedeta"] = Analysis::MakeTH1Plot("el2seedeta","",100,-3.0,3.0,"Subleading Electron Seed #eta","Events",standardTH1SubMap,"standard");

  // e1 and el2 energies
  standardTH1Map["el1pt"]    = Analysis::MakeTH1Plot("el1pt","",100,0.,Config::XHighMap["el1pt"],Form("Leading Electron %s",Config::XTitleMap["pt"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["el1p"]     = Analysis::MakeTH1Plot("el1p","",100,0.,Config::XHighMap["el1E"],Form("Leading Electron %s",Config::XTitleMap["p"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["el1E"]     = Analysis::MakeTH1Plot("el1E","",100,0.,Config::XHighMap["el1E"],Form("Leading Electron %s",Config::XTitleMap["E"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["el1scE"]   = Analysis::MakeTH1Plot("el1scE","",100,0.,Config::XHighMap["el1E"],Form("Leading Electron SuperCluster %s",Config::XTitleMap["E"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["el1seedE"] = Analysis::MakeTH1Plot("el1seedE","",100,0.,Config::XHighMap["el1seedE"],Form("Leading Electron Seed %s",Config::XTitleMap["E"].Data()),"Events",standardTH1SubMap,"standard");

  standardTH1Map["el2pt"]    = Analysis::MakeTH1Plot("el2pt","",100,0.,Config::XHighMap["el2pt"],Form("Subleading Electron %s",Config::XTitleMap["pt"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["el2p"]     = Analysis::MakeTH1Plot("el2p","",100,0.,Config::XHighMap["el2E"],Form("Subleading Electron %s",Config::XTitleMap["p"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["el2E"]     = Analysis::MakeTH1Plot("el2E","",100,0.,Config::XHighMap["el2E"],Form("Subleading Electron %s",Config::XTitleMap["E"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["el2scE"]   = Analysis::MakeTH1Plot("el2scE","",100,0.,Config::XHighMap["el2E"],Form("Subleading Electron SuperCluster %s",Config::XTitleMap["E"].Data()),"Events",standardTH1SubMap,"standard");
  standardTH1Map["el2seedE"] = Analysis::MakeTH1Plot("el2seedE","",100,0.,Config::XHighMap["el2seedE"],Form("Subleading Electron Seed %s",Config::XTitleMap["E"].Data()),"Events",standardTH1SubMap,"standard");

  // inclusive timing plots (subdivided by ecal partitions)
  timingMap["timediff"] = Analysis::MakeTH1Plot("timediff","",Config::ntimebins,-Config::timerange,Config::timerange,"Dielectron Seed Time Difference [ns] (Inclusive)","Events",timingSubMap,"timing/inclusive");
  timingMap["td_EBEB"]  = Analysis::MakeTH1Plot("td_EBEB","",Config::ntimebins,-Config::timerange,Config::timerange,"Dielectron Seed Time Difference [ns] (EBEB Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["td_EBEE"]  = Analysis::MakeTH1Plot("td_EBEE","",Config::ntimebins,-Config::timerange,Config::timerange,"Dielectron Seed Time Difference [ns] (EBEE Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["td_EEEE"]  = Analysis::MakeTH1Plot("td_EEEE","",Config::ntimebins,-Config::timerange,Config::timerange,"Dielectron Seed Time Difference [ns] (EEEE Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["td_EPEP"]  = Analysis::MakeTH1Plot("td_EPEP","",Config::ntimebins,-Config::timerange,Config::timerange,"Dielectron Seed Time Difference [ns] (EE+EE+ Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["td_EMEM"]  = Analysis::MakeTH1Plot("td_EMEM","",Config::ntimebins,-Config::timerange,Config::timerange,"Dielectron Seed Time Difference [ns] (EE-EE- Inclusive)","Events",timingSubMap,"timing/inclusive");  

  timingMap["el1time"]    = Analysis::MakeTH1Plot("el1time","",Config::ntimebins,-Config::timerange,Config::timerange,"Leading Electron Seed Time [ns] (Inclusive)","Events",timingSubMap,"timing/inclusive");
  timingMap["el1time_EB"] = Analysis::MakeTH1Plot("el1time_EB","",Config::ntimebins,-Config::timerange,Config::timerange,"Leading Electron Time [ns] (EB Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["el1time_EE"] = Analysis::MakeTH1Plot("el1time_EE","",Config::ntimebins,-Config::timerange,Config::timerange,"Leading Electron Time [ns] (EE Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["el1time_EP"] = Analysis::MakeTH1Plot("el1time_EP","",Config::ntimebins,-Config::timerange,Config::timerange,"Leading Electron Time [ns] (EE+ Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["el1time_EM"] = Analysis::MakeTH1Plot("el1time_EM","",Config::ntimebins,-Config::timerange,Config::timerange,"Leading Electron Time [ns] (EE- Inclusive)","Events",timingSubMap,"timing/inclusive");  

  timingMap["el2time"]    = Analysis::MakeTH1Plot("el2time","",Config::ntimebins,-Config::timerange,Config::timerange,"Subleading Electron Seed Time [ns] (Inclusive)","Events",timingSubMap,"timing/inclusive");
  timingMap["el2time_EB"] = Analysis::MakeTH1Plot("el2time_EB","",Config::ntimebins,-Config::timerange,Config::timerange,"Subleading Electron Time [ns] (EB Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["el2time_EE"] = Analysis::MakeTH1Plot("el2time_EE","",Config::ntimebins,-Config::timerange,Config::timerange,"Subleading Electron Time [ns] (EE Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["el2time_EP"] = Analysis::MakeTH1Plot("el2time_EP","",Config::ntimebins,-Config::timerange,Config::timerange,"Subleading Electron Time [ns] (EE+ Inclusive)","Events",timingSubMap,"timing/inclusive");  
  timingMap["el2time_EM"] = Analysis::MakeTH1Plot("el2time_EM","",Config::ntimebins,-Config::timerange,Config::timerange,"Subleading Electron Time [ns] (EE- Inclusive)","Events",timingSubMap,"timing/inclusive");  
}

void Analysis::SetupZPlots()
{
  zbins["td_zpt"]  = {0,5,10,15,20,25,30,40,50,60,70,100,150,200,250,300,750};
  z2DMap["td_zpt"] = Analysis::MakeTH2Plot("td_zpt","",zbins["td_zpt"],Config::ntimebins,-Config::timerange,Config::timerange,"Z p_{T} [GeV/c]","Dielectron Seed Time Difference [ns]",z2DSubMap,"timing/z/pt");  

  for (Int_t i = 0; i < 21; i++){zbins["td_zeta"].push_back(i/2. - 5.0);}
  z2DMap["td_zeta"] = Analysis::MakeTH2Plot("td_zeta","",zbins["td_zeta"],Config::ntimebins,-Config::timerange,Config::timerange,"Z #eta","Dielectron Seed Time Difference [ns]",z2DSubMap,"timing/z/eta");  

  for (Int_t i = 0; i < 21; i++){zbins["td_abszeta"].push_back(i/4.);}
  z2DMap["td_abszeta"] = Analysis::MakeTH2Plot("td_abszeta","",zbins["td_abszeta"],Config::ntimebins,-Config::timerange,Config::timerange,"Z |#eta|","Dielectron Seed Time Difference [ns]",z2DSubMap,"timing/z/abseta");  

  for (Int_t i = 0; i < 21; i++){zbins["td_zphi"].push_back(i*0.32 - 3.2);}
  z2DMap["td_zphi"] = Analysis::MakeTH2Plot("td_zphi","",zbins["td_zphi"],Config::ntimebins,-Config::timerange,Config::timerange,"Z #phi","Dielectron Seed Time Difference [ns]",z2DSubMap,"timing/z/phi");  
}

void Analysis::SetupEffEPlots()
{
  /////////////////////////////////////////////////////////////////////////////////////////
  // make 2D plots for effective electron pt, E, and seedE, for EBEB, EBEE, EEEE (++,--) //
  /////////////////////////////////////////////////////////////////////////////////////////
  effptbins = Config::XBinsMap["effpt"]; //effective el pt bins
  effpt2DMap["td_effpt_inclusive"] = Analysis::MakeTH2Plot("td_effpt_inclusive","",effptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (inclusive)",Config::XTitleMap["pt"].Data()),"Dielectron Seed Time Difference [ns]",effpt2DSubMap,"timing/effective/pt/inclusive");  
  effpt2DMap["td_effpt_EBEB"] = Analysis::MakeTH2Plot("td_effpt_EBEB","",effptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EBEB)",Config::XTitleMap["pt"].Data()),"Dielectron Seed Time Difference [ns]",effpt2DSubMap,"timing/effective/pt/EBEB");
  effpt2DMap["td_effpt_EBEE"] = Analysis::MakeTH2Plot("td_effpt_EBEE","",effptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EBEE)",Config::XTitleMap["pt"].Data()),"Dielectron Seed Time Difference [ns]",effpt2DSubMap,"timing/effective/pt/EBEE");
  effpt2DMap["td_effpt_EEEE"] = Analysis::MakeTH2Plot("td_effpt_EEEE","",effptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EEEE)",Config::XTitleMap["pt"].Data()),"Dielectron Seed Time Difference [ns]",effpt2DSubMap,"timing/effective/pt/EEEE");
  effpt2DMap["td_effpt_EPEP"] = Analysis::MakeTH2Plot("td_effpt_EPEP","",effptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EE+EE+)",Config::XTitleMap["pt"].Data()),"Dielectron Seed Time Difference [ns]",effpt2DSubMap,"timing/effective/pt/EPEP");
  effpt2DMap["td_effpt_EMEM"] = Analysis::MakeTH2Plot("td_effpt_EMEM","",effptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EE-EE-)",Config::XTitleMap["pt"].Data()),"Dielectron Seed Time Difference [ns]",effpt2DSubMap,"timing/effective/pt/EMEM");

  effEbins = Config::XBinsMap["effE"]; //effective el E bins
  effE2DMap["td_effE_inclusive"] = Analysis::MakeTH2Plot("td_effE_inclusive","",effEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (inclusive)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effE2DSubMap,"timing/effective/E/inclusive");  
  effE2DMap["td_effE_EBEB"] = Analysis::MakeTH2Plot("td_effE_EBEB","",effEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EBEB)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effE2DSubMap,"timing/effective/E/EBEB");
  effE2DMap["td_effE_EBEE"] = Analysis::MakeTH2Plot("td_effE_EBEE","",effEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EBEE)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effE2DSubMap,"timing/effective/E/EBEE");
  effE2DMap["td_effE_EEEE"] = Analysis::MakeTH2Plot("td_effE_EEEE","",effEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EEEE)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effE2DSubMap,"timing/effective/E/EEEE");
  effE2DMap["td_effE_EPEP"] = Analysis::MakeTH2Plot("td_effE_EPEP","",effEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EE+EE+)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effE2DSubMap,"timing/effective/E/EPEP");
  effE2DMap["td_effE_EMEM"] = Analysis::MakeTH2Plot("td_effE_EMEM","",effEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective %s (EE-EE-)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effE2DSubMap,"timing/effective/E/EMEM");

  effseedEbins = Config::XBinsMap["effseedE"]; //effective el seedE bins
  effseedE2DMap["td_effseedE_inclusive"] = Analysis::MakeTH2Plot("td_effseedE_inclusive","",effseedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective Seed %s (inclusive)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effseedE2DSubMap,"timing/effective/seedE/inclusive");  
  effseedE2DMap["td_effseedE_EBEB"] = Analysis::MakeTH2Plot("td_effseedE_EBEB","",effseedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective Seed %s (EBEB)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effseedE2DSubMap,"timing/effective/seedE/EBEB");
  effseedE2DMap["td_effseedE_EBEE"] = Analysis::MakeTH2Plot("td_effseedE_EBEE","",effseedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective Seed %s (EBEE)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effseedE2DSubMap,"timing/effective/seedE/EBEE");
  effseedE2DMap["td_effseedE_EEEE"] = Analysis::MakeTH2Plot("td_effseedE_EEEE","",effseedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective Seed %s (EEEE)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effseedE2DSubMap,"timing/effective/seedE/EEEE");
  effseedE2DMap["td_effseedE_EPEP"] = Analysis::MakeTH2Plot("td_effseedE_EPEP","",effseedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective Seed %s (EE+EE+)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effseedE2DSubMap,"timing/effective/seedE/EPEP");
  effseedE2DMap["td_effseedE_EMEM"] = Analysis::MakeTH2Plot("td_effseedE_EMEM","",effseedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Effective Seed %s (EE-EE-)",Config::XTitleMap["E"].Data()),"Dielectron Seed Time Difference [ns]",effseedE2DSubMap,"timing/effective/seedE/EMEM");
}

void Analysis::SetupNvtxPlots()
{
  ////////////////////////////////////////////////////////////////
  // make 2D plots for td vs nvtx, for EBEB, EBEE, EEEE (++,--) //
  ////////////////////////////////////////////////////////////////
  for (int iv = 0; iv <= Config::nbinsvtx; iv++) {nvtxbins.push_back(Double_t(iv));}
  nvtx2DMap["td_nvtx_inclusive"] = Analysis::MakeTH2Plot("td_nvtx_inclusive","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (inclusive)","Dielectron Seed Time Difference [ns]",nvtx2DSubMap,"timing/nvtx/inclusive");  
  nvtx2DMap["td_nvtx_EBEB"] = Analysis::MakeTH2Plot("td_nvtx_EBEB","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EBEB)","Dielectron Seed Time Difference [ns]",nvtx2DSubMap,"timing/nvtx/EBEB");  
  nvtx2DMap["td_nvtx_EBEE"] = Analysis::MakeTH2Plot("td_nvtx_EBEE","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EBEE)","Dielectron Seed Time Difference [ns]",nvtx2DSubMap,"timing/nvtx/EBEE");  
  nvtx2DMap["td_nvtx_EEEE"] = Analysis::MakeTH2Plot("td_nvtx_EEEE","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EEEE)","Dielectron Seed Time Difference [ns]",nvtx2DSubMap,"timing/nvtx/EEEE");  
  nvtx2DMap["td_nvtx_EPEP"] = Analysis::MakeTH2Plot("td_nvtx_EPEP","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EE+EE+)","Dielectron Seed Time Difference [ns]",nvtx2DSubMap,"timing/nvtx/EPEP");  
  nvtx2DMap["td_nvtx_EMEM"] = Analysis::MakeTH2Plot("td_nvtx_EMEM","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EE-EE-)","Dielectron Seed Time Difference [ns]",nvtx2DSubMap,"timing/nvtx/EMEM");  

  //////////////////////////////
  // Single El timing vs nvtx //
  //////////////////////////////
  // resuse nvtx bins from above
  nvtx2DMap["el1_nvtx_inclusive"] = Analysis::MakeTH2Plot("el1_nvtx_inclusive","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (inclusive)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el1/nvtx/inclusive");  
  nvtx2DMap["el1_nvtx_EB"] = Analysis::MakeTH2Plot("el1_nvtx_EB","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EB)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el1/nvtx/EB");  
  nvtx2DMap["el1_nvtx_EE"] = Analysis::MakeTH2Plot("el1_nvtx_EE","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EE)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el1/nvtx/EE");  
  nvtx2DMap["el1_nvtx_EP"] = Analysis::MakeTH2Plot("el1_nvtx_EP","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EE+)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el1/nvtx/EP");  
  nvtx2DMap["el1_nvtx_EM"] = Analysis::MakeTH2Plot("el1_nvtx_EM","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EE-)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el1/nvtx/EM");  

  nvtx2DMap["el2_nvtx_inclusive"] = Analysis::MakeTH2Plot("el2_nvtx_inclusive","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (inclusive)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el2/nvtx/inclusive");  
  nvtx2DMap["el2_nvtx_EB"] = Analysis::MakeTH2Plot("el2_nvtx_EB","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EB)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el2/nvtx/EB");  
  nvtx2DMap["el2_nvtx_EE"] = Analysis::MakeTH2Plot("el2_nvtx_EE","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EE)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el2/nvtx/EE");  
  nvtx2DMap["el2_nvtx_EP"] = Analysis::MakeTH2Plot("el2_nvtx_EP","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EE+)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el2/nvtx/EP");  
  nvtx2DMap["el2_nvtx_EM"] = Analysis::MakeTH2Plot("el2_nvtx_EM","",nvtxbins,Config::ntimebins,-Config::timerange,Config::timerange,"nPV (EE-)","Leading Electron Seed Time [ns]",nvtx2DSubMap,"timing/el2/nvtx/EM");  
}

void Analysis::SetupEtaPlots()
{
  ///////////////////////////////////////
  // 2D plots for td vs single el etas //
  ///////////////////////////////////////
  for (Int_t i = 0; i < 21; i++){eletabins.push_back(i/4. - 2.5);}
  eleta2DMap["td_el1eta"]     = Analysis::MakeTH2Plot("td_el1eta","",eletabins,Config::ntimebins,-Config::timerange,Config::timerange,"Leading Electron #eta","Dielectron Seed Time Difference [ns]",eleta2DSubMap,"timing/singleeta/el1eta");  
  eleta2DMap["td_el1seedeta"] = Analysis::MakeTH2Plot("td_el1seedeta","",eletabins,Config::ntimebins,-Config::timerange,Config::timerange,"Leading Electron Seed #eta","Dielectron Seed Time Difference [ns]",eleta2DSubMap,"timing/singleeta/el1seedeta");  

  eleta2DMap["td_el2eta"]     = Analysis::MakeTH2Plot("td_el2eta","",eletabins,Config::ntimebins,-Config::timerange,Config::timerange,"Subleading Electron #eta","Dielectron Seed Time Difference [ns]",eleta2DSubMap,"timing/singleeta/el2eta");  
  eleta2DMap["td_el2seedeta"] = Analysis::MakeTH2Plot("td_el2seedeta","",eletabins,Config::ntimebins,-Config::timerange,Config::timerange,"Subleading Electron Seed #eta","Dielectron Seed Time Difference [ns]",eleta2DSubMap,"timing/singleeta/el2seedeta");  

  //////////////////////////////
  // Single El timing vs etas //
  //////////////////////////////
  eleta2DMap["el1_el1eta"]     = Analysis::MakeTH2Plot("el1_el1eta","",eletabins,Config::ntimebins,-Config::timerange,Config::timerange,"Leading Electron #eta","Leading Electron Seed Time [ns]",eleta2DSubMap,"timing/el1/eta");  
  eleta2DMap["el1_el1seedeta"] = Analysis::MakeTH2Plot("el1_el1seedeta","",eletabins,Config::ntimebins,-Config::timerange,Config::timerange,"Leading Electron Seed #eta","Leading Electron Seed Time [ns]",eleta2DSubMap,"timing/el1/seedeta");  

  eleta2DMap["el2_el2eta"]     = Analysis::MakeTH2Plot("el2_el2eta","",eletabins,Config::ntimebins,-Config::timerange,Config::timerange,"Subleading Electron #eta","Subleading Electron Seed Time [ns]",eleta2DSubMap,"timing/el2/eta");  
  eleta2DMap["el2_el2seedeta"] = Analysis::MakeTH2Plot("el2_el2seedeta","",eletabins,Config::ntimebins,-Config::timerange,Config::timerange,"Subleading Electron Seed #eta","Subleading Electron Seed Time [ns]",eleta2DSubMap,"timing/el2/seedeta");  
}

void Analysis::SetupVtxZPlots()
{
  vtxZbins = {-15.0,-12.0,-11.0,-10.0,-9.0,-8.0,-7.0,-6.0,-5.0,-4.5,-4.0,-3.5,-3.0,-2.5,-2.0,-1.5,-1.25,-1.0,-0.75,-0.5,-0.25,0.0};
  for (int i = vtxZbins.size()-2; i >= 0; i--){vtxZbins.push_back(-1.0*vtxZbins[i]);}
  
  // time difference
  vtxZ2DMap["td_vtxZ"]  = Analysis::MakeTH2Plot("td_vtxZ","",vtxZbins,Config::ntimebins,-Config::timerange,Config::timerange,"PV z position [cm]","Dielectron Seed Time Difference [ns]",vtxZ2DSubMap,"timing/vtxZ");  

  // single electron
  vtxZ2DMap["el1_vtxZ"] = Analysis::MakeTH2Plot("el1_vtxZ","",vtxZbins,Config::ntimebins,-Config::timerange,Config::timerange,"PV z position [cm]","Leading Electron Seed Time [ns]",vtxZ2DSubMap,"timing/el1/vtxZ");  
  vtxZ2DMap["el2_vtxZ"] = Analysis::MakeTH2Plot("el2_vtxZ","",vtxZbins,Config::ntimebins,-Config::timerange,Config::timerange,"PV z position [cm]","Subleading Electron Seed Time [ns]",vtxZ2DSubMap,"timing/el2/vtxZ");  
}

void Analysis::SetupSingleEPlots()
{
  ////////////////////////////////////////////////////////////////////
  // make 2D plots for single electron timing vs pt, energies (el1) // 
  ////////////////////////////////////////////////////////////////////
  el1ptbins = Config::XBinsMap["el1pt"]; // el1 pt bins
  el1pt2DMap["el1pt_inclusive"] = Analysis::MakeTH2Plot("el1pt_inclusive","",el1ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (inclusive)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el1pt2DSubMap,"timing/el1/pt/inclusive");  
  el1pt2DMap["el1pt_EB"] = Analysis::MakeTH2Plot("el1pt_EB","",el1ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EB)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el1pt2DSubMap,"timing/el1/pt/EB");  
  el1pt2DMap["el1pt_EE"] = Analysis::MakeTH2Plot("el1pt_EE","",el1ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el1pt2DSubMap,"timing/el1/pt/EE");  
  el1pt2DMap["el1pt_EP"] = Analysis::MakeTH2Plot("el1pt_EP","",el1ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE+)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el1pt2DSubMap,"timing/el1/pt/EP");  
  el1pt2DMap["el1pt_EM"] = Analysis::MakeTH2Plot("el1pt_EM","",el1ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE-)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el1pt2DSubMap,"timing/el1/pt/EM");  

  el1Ebins = Config::XBinsMap["el1E"]; // el1 E bins
  el1E2DMap["el1E_inclusive"] = Analysis::MakeTH2Plot("el1E_inclusive","",el1Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (inclusive)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1E2DSubMap,"timing/el1/E/inclusive");  
  el1E2DMap["el1E_EB"] = Analysis::MakeTH2Plot("el1E_EB","",el1Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EB)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1E2DSubMap,"timing/el1/E/EB");  
  el1E2DMap["el1E_EE"] = Analysis::MakeTH2Plot("el1E_EE","",el1Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1E2DSubMap,"timing/el1/E/EE");  
  el1E2DMap["el1E_EP"] = Analysis::MakeTH2Plot("el1E_EP","",el1Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE+)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1E2DSubMap,"timing/el1/E/EP");  
  el1E2DMap["el1E_EM"] = Analysis::MakeTH2Plot("el1E_EM","",el1Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE-)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1E2DSubMap,"timing/el1/E/EM");  

  el1seedEbins = Config::XBinsMap["el1seedE"]; // el1 seedE bins
  el1seedE2DMap["el1seedE_inclusive"] = Analysis::MakeTH2Plot("el1seedE_inclusive","",el1seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (inclusive)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1seedE2DSubMap,"timing/el1/seedE/inclusive");  
  el1seedE2DMap["el1seedE_EB"] = Analysis::MakeTH2Plot("el1seedE_EB","",el1seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EB)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1seedE2DSubMap,"timing/el1/seedE/EB");  
  el1seedE2DMap["el1seedE_EE"] = Analysis::MakeTH2Plot("el1seedE_EE","",el1seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1seedE2DSubMap,"timing/el1/seedE/EE");  
  el1seedE2DMap["el1seedE_EP"] = Analysis::MakeTH2Plot("el1seedE_EP","",el1seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE+)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1seedE2DSubMap,"timing/el1/seedE/EP");  
  el1seedE2DMap["el1seedE_EM"] = Analysis::MakeTH2Plot("el1seedE_EM","",el1seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE-)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el1seedE2DSubMap,"timing/el1/seedE/EM");  

  ////////////////////////////////////////////////////////////////////
  // make 2D plots for single electron timing vs pt, energies (el2) // 
  ////////////////////////////////////////////////////////////////////
  el2ptbins = Config::XBinsMap["el2pt"]; // el2 pt bins
  el2pt2DMap["el2pt_inclusive"] = Analysis::MakeTH2Plot("el2pt_inclusive","",el2ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (inclusive)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el2pt2DSubMap,"timing/el2/pt/inclusive");  
  el2pt2DMap["el2pt_EB"] = Analysis::MakeTH2Plot("el2pt_EB","",el2ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EB)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el2pt2DSubMap,"timing/el2/pt/EB");  
  el2pt2DMap["el2pt_EE"] = Analysis::MakeTH2Plot("el2pt_EE","",el2ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el2pt2DSubMap,"timing/el2/pt/EE");  
  el2pt2DMap["el2pt_EP"] = Analysis::MakeTH2Plot("el2pt_EP","",el2ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE+)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el2pt2DSubMap,"timing/el2/pt/EP");  
  el2pt2DMap["el2pt_EM"] = Analysis::MakeTH2Plot("el2pt_EM","",el2ptbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE-)",Config::XTitleMap["pt"].Data()),"Leading Electron Seed Time [ns]",el2pt2DSubMap,"timing/el2/pt/EM");  

  el2Ebins = Config::XBinsMap["el2E"]; // el2 E bins
  el2E2DMap["el2E_inclusive"] = Analysis::MakeTH2Plot("el2E_inclusive","",el2Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (inclusive)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2E2DSubMap,"timing/el2/E/inclusive");  
  el2E2DMap["el2E_EB"] = Analysis::MakeTH2Plot("el2E_EB","",el2Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EB)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2E2DSubMap,"timing/el2/E/EB");  
  el2E2DMap["el2E_EE"] = Analysis::MakeTH2Plot("el2E_EE","",el2Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2E2DSubMap,"timing/el2/E/EE");  
  el2E2DMap["el2E_EP"] = Analysis::MakeTH2Plot("el2E_EP","",el2Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE+)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2E2DSubMap,"timing/el2/E/EP");  
  el2E2DMap["el2E_EM"] = Analysis::MakeTH2Plot("el2E_EM","",el2Ebins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE-)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2E2DSubMap,"timing/el2/E/EM");  

  el2seedEbins = Config::XBinsMap["el2seedE"]; // el2 seedE bins
  el2seedE2DMap["el2seedE_inclusive"] = Analysis::MakeTH2Plot("el2seedE_inclusive","",el2seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (inclusive)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2seedE2DSubMap,"timing/el2/seedE/inclusive");  
  el2seedE2DMap["el2seedE_EB"] = Analysis::MakeTH2Plot("el2seedE_EB","",el2seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EB)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2seedE2DSubMap,"timing/el2/seedE/EB");  
  el2seedE2DMap["el2seedE_EE"] = Analysis::MakeTH2Plot("el2seedE_EE","",el2seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2seedE2DSubMap,"timing/el2/seedE/EE");  
  el2seedE2DMap["el2seedE_EP"] = Analysis::MakeTH2Plot("el2seedE_EP","",el2seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE+)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2seedE2DSubMap,"timing/el2/seedE/EP");  
  el2seedE2DMap["el2seedE_EM"] = Analysis::MakeTH2Plot("el2seedE_EM","",el2seedEbins,Config::ntimebins,-Config::timerange,Config::timerange,Form("Leading Electron %s (EE-)",Config::XTitleMap["E"].Data()),"Leading Electron Seed Time [ns]",el2seedE2DSubMap,"timing/el2/seedE/EM");  
}

void Analysis::SetupRunPlots()
{
  // read in run numbers
  std::ifstream inputruns;
  inputruns.open(Config::runs.Data(),std::ios::in);
  Int_t runno = -1;
  IntVec runNos;
  while(inputruns >> runno){
    runNos.push_back(runno);
  }
  inputruns.close();
  
  // need this to do the wonky binning to get means/sigmas to line up exactly with run number
  Int_t totalRuns = runNos.back()-runNos.front();
  Int_t startrun  = runNos.front();
  for (Int_t i = 0; i < totalRuns + 2; i++) { // +1 for subtraction, +1 for half offset
    dRunNos.push_back(startrun + i - 0.5);
  }
  
  // declare hists
  runs2DMap["td_runs_inclusive"] = Analysis::MakeTH2Plot("td_runs_inclusive","",dRunNos,Config::ntimebins,-Config::timerange,Config::timerange,"Run Number (inclusive)","Dielectron Seed Time Difference [ns]",runs2DSubMap,"timing/runs/inclusive");  
  runs2DMap["td_runs_EBEB"] = Analysis::MakeTH2Plot("td_runs_EBEB","",dRunNos,Config::ntimebins,-Config::timerange,Config::timerange,"Run Number (EBEB)","Dielectron Seed Time Difference [ns]",runs2DSubMap,"timing/runs/EBEB");  
  runs2DMap["td_runs_EBEE"] = Analysis::MakeTH2Plot("td_runs_EBEE","",dRunNos,Config::ntimebins,-Config::timerange,Config::timerange,"Run Number (EBEE)","Dielectron Seed Time Difference [ns]",runs2DSubMap,"timing/runs/EBEE");  
  runs2DMap["td_runs_EEEE"] = Analysis::MakeTH2Plot("td_runs_EEEE","",dRunNos,Config::ntimebins,-Config::timerange,Config::timerange,"Run Number (EEEE)","Dielectron Seed Time Difference [ns]",runs2DSubMap,"timing/runs/EEEE");  
}

void Analysis::SetupTrigEffPlots()
{
  Int_t nBinsDEEpt = 100; Float_t xLowDEEpt = 20.; Float_t xHighDEEpt = 120.;
  n_hltdoubleel_el1pt = new TH1F("numer_hltdoubleel_el1pt","",nBinsDEEpt,xLowDEEpt,xHighDEEpt);
  d_hltdoubleel_el1pt = new TH1F("denom_hltdoubleel_el1pt","",nBinsDEEpt,xLowDEEpt,xHighDEEpt);

  n_hltdoubleel_el2pt = new TH1F("numer_hltdoubleel_el2pt","",nBinsDEEpt,xLowDEEpt,xHighDEEpt);
  d_hltdoubleel_el2pt = new TH1F("denom_hltdoubleel_el2pt","",nBinsDEEpt,xLowDEEpt,xHighDEEpt);

  trTH1Map["hltdoubleel_el1pt"] = Analysis::MakeTH1Plot("hltdoubleel_el1pt","Double Electron Trigger Efficiency vs. p_{T}",nBinsDEEpt,xLowDEEpt,xHighDEEpt,"Leading Electron p_{T} [GeV/c]","Efficiency",trTH1SubMap,"trigger_zoomest");
  trTH1Map["hltdoubleel_el2pt"] = Analysis::MakeTH1Plot("hltdoubleel_el2pt","Double Electron Trigger Efficiency vs. p_{T}",nBinsDEEpt,xLowDEEpt,xHighDEEpt,"Subleading Electron p_{T} [GeV/c]","Efficiency",trTH1SubMap,"trigger_zoomest");
}

void Analysis::FillStandardPlots(const Float_t weight, const Float_t timediff, const Float_t effpt, const Float_t effE, const Float_t effseedE, 
				 const Float_t el1time, const Float_t el1seedeta, Bool_t el1eb, Bool_t el1ee, Bool_t el1ep, Bool_t el1em,
				 const Float_t el2time, const Float_t el2seedeta, Bool_t el2eb, Bool_t el2ee, Bool_t el2ep, Bool_t el2em)
{
  // standard "validation" and Z mass plots
  standardTH1Map["nvtx"]->Fill(nvtx,weight);
  standardTH1Map["vtxZ"]->Fill(vtxZ,weight);

  standardTH1Map["zmass"]->Fill(zmass,weight);
  standardTH1Map["zpt"]->Fill(zpt,weight);
  standardTH1Map["zeta"]->Fill(zeta,weight);
  standardTH1Map["abszeta"]->Fill(std::abs(zeta),weight);
  standardTH1Map["zphi"]->Fill(zphi,weight);
  standardTH1Map["effpt"]->Fill(effpt,weight);
  standardTH1Map["effE"]->Fill(effE,weight);
  standardTH1Map["effseedE"]->Fill(effseedE,weight);

  standardTH1Map["el1phi"]->Fill(el1phi,weight);
  standardTH1Map["el1eta"]->Fill(el1eta,weight);
  standardTH1Map["el1seedeta"]->Fill(el1seedeta,weight);

  standardTH1Map["el2phi"]->Fill(el2phi,weight); 
  standardTH1Map["el2eta"]->Fill(el2eta,weight);
  standardTH1Map["el2seedeta"]->Fill(el2seedeta,weight);

  standardTH1Map["el1pt"]->Fill(el1pt,weight);
  standardTH1Map["el1p"]->Fill(el1p,weight);
  standardTH1Map["el1E"]->Fill(el1E,weight);
  standardTH1Map["el1scE"]->Fill(el1scE,weight);
  standardTH1Map["el1seedE"]->Fill(el1seedE,weight);

  standardTH1Map["el2pt"]->Fill(el2pt,weight);
  standardTH1Map["el2p"]->Fill(el2p,weight);
  standardTH1Map["el2E"]->Fill(el2E,weight);
  standardTH1Map["el2scE"]->Fill(el2scE,weight);
  standardTH1Map["el2seedE"]->Fill(el2seedE,weight);

  timingMap["timediff"]->Fill(timediff,weight);

  // inclusive single electron timing
  timingMap["el1time"]->Fill(el1time,weight);
  if        (el1eb) {timingMap["el1time_EB"]->Fill(el1time,weight);}
  else if   (el1ee) {timingMap["el1time_EE"]->Fill(el1time,weight);
    if      (el1ep) {timingMap["el1time_EP"]->Fill(el1time,weight);}
    else if (el1em) {timingMap["el1time_EM"]->Fill(el1time,weight);}
  }
  
  timingMap["el2time"]->Fill(el2time,weight);
  if        (el2eb) {timingMap["el2time_EB"]->Fill(el2time,weight);}
  else if   (el2ee) {timingMap["el2time_EE"]->Fill(el2time,weight);
    if      (el2ep) {timingMap["el2time_EP"]->Fill(el2time,weight);}
    else if (el2em) {timingMap["el2time_EM"]->Fill(el2time,weight);}
  }

  // plots subdivided into 2partition events
  if        (el1eb && el2eb) { //EBEB
    standardTH1Map["zmass_EBEB"]->Fill(zmass,weight); 
    timingMap["td_EBEB"]->Fill(timediff,weight); 
  }
  else if   (el1ee && el2ee) { //EEEE
    standardTH1Map["zmass_EEEE"]->Fill(zmass,weight); 
    timingMap["td_EEEE"]->Fill(timediff,weight); 
    if      (el1ep && el2ep) { //EE+EE+
      standardTH1Map["zmass_EPEP"]->Fill(zmass,weight); 
      timingMap["td_EPEP"]->Fill(timediff,weight); 
    }
    else if (el1em && el2em) { //EE-EE-
      standardTH1Map["zmass_EMEM"]->Fill(zmass,weight); 
      timingMap["td_EMEM"]->Fill(timediff,weight); 
    }
  }
  else if ((el1eb && el2ee) || (el1ee && el2eb)) { //EBEE
    standardTH1Map["zmass_EBEE"]->Fill(zmass,weight); 
    timingMap["td_EBEE"]->Fill(timediff,weight); 
  }
}

void Analysis::FillZPlots(const Float_t weight, const Float_t timediff)
{
  z2DMap["td_zpt"]->Fill(zpt,timediff,weight);
  z2DMap["td_zeta"]->Fill(zeta,timediff,weight);
  z2DMap["td_abszeta"]->Fill(std::abs(zeta),timediff,weight);
  z2DMap["td_zphi"]->Fill(zphi,timediff,weight);
}

void Analysis::FillEffEPlots(const Float_t weight, const Float_t timediff, const Float_t effpt, const Float_t effE, const Float_t effseedE, 
			     Bool_t el1eb, Bool_t el1ee, Bool_t el1ep, Bool_t el1em, Bool_t el2eb, Bool_t el2ee, Bool_t el2ep, Bool_t el2em)
{
  effpt2DMap["td_effpt_inclusive"]->Fill(effpt,timediff,weight);
  effE2DMap["td_effE_inclusive"]->Fill(effE,timediff,weight);
  effseedE2DMap["td_effseedE_inclusive"]->Fill(effseedE,timediff,weight);
  
  if (el1eb && el2eb) { //EBEB
    effpt2DMap["td_effpt_EBEB"]->Fill(effpt,timediff,weight);
    effE2DMap["td_effE_EBEB"]->Fill(effE,timediff,weight);
    effseedE2DMap["td_effseedE_EBEB"]->Fill(effseedE,timediff,weight);
  }
  else if (el1ee && el2ee) { //EEEE
    effpt2DMap["td_effpt_EEEE"]->Fill(effpt,timediff,weight);
    effE2DMap["td_effE_EEEE"]->Fill(effE,timediff,weight);
    effseedE2DMap["td_effseedE_EEEE"]->Fill(effseedE,timediff,weight);
    if      (el1ep && el2ep) { // EE+EE+
      effpt2DMap["td_effpt_EPEP"]->Fill(effpt,timediff,weight);
      effE2DMap["td_effE_EPEP"]->Fill(effE,timediff,weight);
      effseedE2DMap["td_effseedE_EPEP"]->Fill(effseedE,timediff,weight);
    }
    else if (el1em && el2em) { // EE-EE-
      effpt2DMap["td_effpt_EMEM"]->Fill(effpt,timediff,weight);
      effE2DMap["td_effE_EMEM"]->Fill(effE,timediff,weight);
      effseedE2DMap["td_effseedE_EMEM"]->Fill(effseedE,timediff,weight);

    }
  }
  else if ((el1eb && el2ee) || (el1ee && el2eb)) { //EBEE 
    effpt2DMap["td_effpt_EBEE"]->Fill(effpt,timediff,weight);
    effE2DMap["td_effE_EBEE"]->Fill(effE,timediff,weight);
    effseedE2DMap["td_effseedE_EBEE"]->Fill(effseedE,timediff,weight);
  }
}

void Analysis::FillNvtxPlots(const Float_t weight, const Float_t timediff, const Float_t el1time, const Float_t el2time,
			     Bool_t el1eb, Bool_t el1ee, Bool_t el1ep, Bool_t el1em, Bool_t el2eb, Bool_t el2ee, Bool_t el2ep, Bool_t el2em)
{
  nvtx2DMap["td_nvtx_inclusive"]->Fill(nvtx,timediff,weight);
  if        (el1eb && el2eb) {nvtx2DMap["td_nvtx_EBEB"]->Fill(nvtx,timediff,weight);}
  else if   (el1ee && el2ee) {nvtx2DMap["td_nvtx_EEEE"]->Fill(nvtx,timediff,weight);
    if      (el1ep && el2ep) {nvtx2DMap["td_nvtx_EPEP"]->Fill(nvtx,timediff,weight);}
    else if (el1em && el2em) {nvtx2DMap["td_nvtx_EMEM"]->Fill(nvtx,timediff,weight);}
  }
  else if ((el1eb && el2ee) || (el1ee && el2eb)) {nvtx2DMap["td_nvtx_EBEE"]->Fill(nvtx,timediff,weight);}

  nvtx2DMap["el1_nvtx_inclusive"]->Fill(nvtx,el1time,weight);
  if        (el1eb) {nvtx2DMap["el1_nvtx_EB"]->Fill(nvtx,el1time,weight);}
  else if   (el1ee) {nvtx2DMap["el1_nvtx_EE"]->Fill(nvtx,el1time,weight);
    if      (el1ep) {nvtx2DMap["el1_nvtx_EP"]->Fill(nvtx,el1time,weight);}
    else if (el1em) {nvtx2DMap["el1_nvtx_EM"]->Fill(nvtx,el1time,weight);}
  }

  nvtx2DMap["el2_nvtx_inclusive"]->Fill(nvtx,el2time,weight);
  if        (el2eb) {nvtx2DMap["el2_nvtx_EB"]->Fill(nvtx,el2time,weight);}
  else if   (el2ee) {nvtx2DMap["el2_nvtx_EE"]->Fill(nvtx,el2time,weight);
    if      (el2ep) {nvtx2DMap["el2_nvtx_EP"]->Fill(nvtx,el2time,weight);}
    else if (el2em) {nvtx2DMap["el2_nvtx_EM"]->Fill(nvtx,el2time,weight);}
  }
}
   
void Analysis::FillEtaPlots(const Float_t weight, const Float_t timediff, const Float_t el1time, const Float_t el2time, const Float_t el1seedeta, const Float_t el2seedeta)
{
  eleta2DMap["td_el1eta"]->Fill(el1eta,timediff,weight);
  eleta2DMap["td_el1seedeta"]->Fill(el1seedeta,timediff,weight);
  eleta2DMap["td_el2eta"]->Fill(el2eta,timediff,weight);
  eleta2DMap["td_el2seedeta"]->Fill(el2seedeta,timediff,weight);

  eleta2DMap["el1_el1eta"]->Fill(el1eta,el1time,weight);
  eleta2DMap["el1_el1seedeta"]->Fill(el1seedeta,el1time,weight);
  eleta2DMap["el2_el2eta"]->Fill(el2eta,el2time,weight);
  eleta2DMap["el2_el2seedeta"]->Fill(el2seedeta,el2time,weight);
}

void Analysis::FillVtxZPlots(const Float_t weight, const Float_t timediff, const Float_t el1time, const Float_t el2time)
{
  vtxZ2DMap["td_vtxZ"] ->Fill(vtxZ,timediff,weight);
  vtxZ2DMap["el1_vtxZ"]->Fill(vtxZ,el1time,weight);
  vtxZ2DMap["el2_vtxZ"]->Fill(vtxZ,el2time,weight);
}

void Analysis::FillSingleEPlots(const Float_t weight, const Float_t el1time, const Float_t el2time,
			        Bool_t el1eb, Bool_t el1ee, Bool_t el1ep, Bool_t el1em, Bool_t el2eb, Bool_t el2ee, Bool_t el2ep, Bool_t el2em)
{
  el1pt2DMap   ["el1pt_inclusive"]   ->Fill(el1pt,   el1time,weight);
  el1E2DMap    ["el1E_inclusive"]    ->Fill(el1E,    el1time,weight);
  el1seedE2DMap["el1seedE_inclusive"]->Fill(el1seedE,el1time,weight);
  if        (el1eb) {
    el1pt2DMap   ["el1pt_EB"]   ->Fill(el1pt,   el1time,weight);
    el1E2DMap    ["el1E_EB"]    ->Fill(el1E,    el1time,weight);
    el1seedE2DMap["el1seedE_EB"]->Fill(el1seedE,el1time,weight);
  }
  else if   (el1ee) {
    el1pt2DMap   ["el1pt_EE"]   ->Fill(el1pt,   el1time,weight);
    el1E2DMap    ["el1E_EE"]    ->Fill(el1E,    el1time,weight);
    el1seedE2DMap["el1seedE_EE"]->Fill(el1seedE,el1time,weight);
    if      (el1ep) {
      el1pt2DMap   ["el1pt_EP"]   ->Fill(el1pt,   el1time,weight);
      el1E2DMap    ["el1E_EP"]    ->Fill(el1E,    el1time,weight);
      el1seedE2DMap["el1seedE_EP"]->Fill(el1seedE,el1time,weight);
    }
    else if (el1em) {
      el1pt2DMap   ["el1pt_EM"]   ->Fill(el1pt,   el1time,weight);
      el1E2DMap    ["el1E_EM"]    ->Fill(el1E,    el1time,weight);
      el1seedE2DMap["el1seedE_EM"]->Fill(el1seedE,el1time,weight);
    }
  }

  el2pt2DMap   ["el2pt_inclusive"]   ->Fill(el2pt,   el2time,weight);
  el2E2DMap    ["el2E_inclusive"]    ->Fill(el2E,    el2time,weight);
  el2seedE2DMap["el2seedE_inclusive"]->Fill(el2seedE,el2time,weight);
  if        (el2eb) {
    el2pt2DMap   ["el2pt_EB"]   ->Fill(el2pt,   el2time,weight);
    el2E2DMap    ["el2E_EB"]    ->Fill(el2E,    el2time,weight);
    el2seedE2DMap["el2seedE_EB"]->Fill(el2seedE,el2time,weight);
  }
  else if   (el2ee) {
    el2pt2DMap   ["el2pt_EE"]   ->Fill(el2pt,   el2time,weight);
    el2E2DMap    ["el2E_EE"]    ->Fill(el2E,    el2time,weight);
    el2seedE2DMap["el2seedE_EE"]->Fill(el2seedE,el2time,weight);
    if      (el2ep) {
      el2pt2DMap   ["el2pt_EP"]   ->Fill(el2pt,   el2time,weight);
      el2E2DMap    ["el2E_EP"]    ->Fill(el2E,    el2time,weight);
      el2seedE2DMap["el2seedE_EP"]->Fill(el2seedE,el2time,weight);
    }
    else if (el2em) {
      el2pt2DMap   ["el2pt_EM"]   ->Fill(el2pt,   el2time,weight);
      el2E2DMap    ["el2E_EM"]    ->Fill(el2E,    el2time,weight);
      el2seedE2DMap["el2seedE_EM"]->Fill(el2seedE,el2time,weight);
    }
  }
}

void Analysis::FillRunPlots(const Float_t weight, const Float_t timediff, Bool_t el1eb, Bool_t el1ee, Bool_t el2eb, Bool_t el2ee)
{
  runs2DMap["td_runs_inclusive"]->Fill(run,timediff,weight);
  if      (el1eb && el2eb)                       { runs2DMap["td_runs_EBEB"]->Fill(run,timediff,weight); }
  else if (el1ee && el2ee)                       { runs2DMap["td_runs_EEEE"]->Fill(run,timediff,weight); }
  else if ((el1eb && el2ee) || (el1ee && el2eb)) { runs2DMap["td_runs_EBEE"]->Fill(run,timediff,weight); }
}

void Analysis::FillTrigEffPlots(const Float_t weight)
{
  if ( hltdoubleel ) { // fill number if passed
    n_hltdoubleel_el1pt->Fill(el1pt,weight);
    n_hltdoubleel_el2pt->Fill(el2pt,weight);
  }
  // always fill denom
  d_hltdoubleel_el1pt->Fill(el1pt,weight);
  d_hltdoubleel_el2pt->Fill(el2pt,weight);
}

void Analysis::OutputStandardPlots() 
{
  MakeSubDirs(standardTH1SubMap,fOutDir);
  Analysis::SaveTH1s(standardTH1Map,standardTH1SubMap);
  if (!fIsMC) Analysis::DumpTH1Names(standardTH1Map,standardTH1SubMap);
  Analysis::DeleteTH1s(standardTH1Map);

  MakeSubDirs(timingSubMap,fOutDir);
  Analysis::SaveTH1s(timingMap,timingSubMap);
  if (!fIsMC) Analysis::DumpTH1Names(timingMap,timingSubMap);
  Analysis::DeleteTH1s(timingMap);
}

void Analysis::OutputZPlots() 
{
  MakeSubDirs(z2DSubMap,fOutDir);
  Analysis::SaveTH2s(z2DMap,z2DSubMap);
  for (TH2MapIter mapiter = z2DMap.begin(); mapiter != z2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,z2DSubMap[name],zbins[name],name);
  }
  Analysis::DeleteTH2s(z2DMap);  
}

void Analysis::OutputEffEPlots()
{
  // pt
  MakeSubDirs(effpt2DSubMap,fOutDir);
  Analysis::SaveTH2s(effpt2DMap,effpt2DSubMap);
  for (TH2MapIter mapiter = effpt2DMap.begin(); mapiter != effpt2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,effpt2DSubMap[name],effptbins,name);
  }
  Analysis::DeleteTH2s(effpt2DMap);  

  // E
  MakeSubDirs(effE2DSubMap,fOutDir);
  Analysis::SaveTH2s(effE2DMap,effE2DSubMap);
  for (TH2MapIter mapiter = effE2DMap.begin(); mapiter != effE2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,effE2DSubMap[name],effEbins,name);
  }
  Analysis::DeleteTH2s(effE2DMap);  

  // seedE
  MakeSubDirs(effseedE2DSubMap,fOutDir);
  Analysis::SaveTH2s(effseedE2DMap,effseedE2DSubMap);
  for (TH2MapIter mapiter = effseedE2DMap.begin(); mapiter != effseedE2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,effseedE2DSubMap[name],effseedEbins,name);
  }
  Analysis::DeleteTH2s(effseedE2DMap);  
}

void Analysis::OutputNvtxPlots()
{
  MakeSubDirs(nvtx2DSubMap,fOutDir);
  Analysis::SaveTH2s(nvtx2DMap,nvtx2DSubMap);
  for (TH2MapIter mapiter = nvtx2DMap.begin(); mapiter != nvtx2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,nvtx2DSubMap[name],nvtxbins,name);
  }
  Analysis::DeleteTH2s(nvtx2DMap);  
}

void Analysis::OutputEtaPlots()
{
  MakeSubDirs(eleta2DSubMap,fOutDir);
  Analysis::SaveTH2s(eleta2DMap,eleta2DSubMap);
  for (TH2MapIter mapiter = eleta2DMap.begin(); mapiter != eleta2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,eleta2DSubMap[name],eletabins,name);
  }
  Analysis::DeleteTH2s(eleta2DMap);  
}

void Analysis::OutputVtxZPlots()
{
  MakeSubDirs(vtxZ2DSubMap,fOutDir);
  Analysis::SaveTH2s(vtxZ2DMap,vtxZ2DSubMap);
  for (TH2MapIter mapiter = vtxZ2DMap.begin(); mapiter != vtxZ2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,vtxZ2DSubMap[name],vtxZbins,name);
  }
  Analysis::DeleteTH2s(vtxZ2DMap);  
}

void Analysis::OutputSingleEPlots()
{ 
  // el1pt
  MakeSubDirs(el1pt2DSubMap,fOutDir);
  Analysis::SaveTH2s(el1pt2DMap,el1pt2DSubMap);
  for (TH2MapIter mapiter = el1pt2DMap.begin(); mapiter != el1pt2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,el1pt2DSubMap[name],el1ptbins,name);
  }
  Analysis::DeleteTH2s(el1pt2DMap);  

  // el1E
  MakeSubDirs(el1E2DSubMap,fOutDir);
  Analysis::SaveTH2s(el1E2DMap,el1E2DSubMap);
  for (TH2MapIter mapiter = el1E2DMap.begin(); mapiter != el1E2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,el1E2DSubMap[name],el1Ebins,name);
  }
  Analysis::DeleteTH2s(el1E2DMap);  

  // el1seedE
  MakeSubDirs(el1seedE2DSubMap,fOutDir);
  Analysis::SaveTH2s(el1seedE2DMap,el1seedE2DSubMap);
  for (TH2MapIter mapiter = el1seedE2DMap.begin(); mapiter != el1seedE2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,el1seedE2DSubMap[name],el1seedEbins,name);
  }
  Analysis::DeleteTH2s(el1seedE2DMap);  

  // el2pt
  MakeSubDirs(el2pt2DSubMap,fOutDir);
  Analysis::SaveTH2s(el2pt2DMap,el2pt2DSubMap);
  for (TH2MapIter mapiter = el2pt2DMap.begin(); mapiter != el2pt2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,el2pt2DSubMap[name],el2ptbins,name);
  }
  Analysis::DeleteTH2s(el2pt2DMap);  

  // el2E
  MakeSubDirs(el2E2DSubMap,fOutDir);
  Analysis::SaveTH2s(el2E2DMap,el2E2DSubMap);
  for (TH2MapIter mapiter = el2E2DMap.begin(); mapiter != el2E2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,el2E2DSubMap[name],el2Ebins,name);
  }
  Analysis::DeleteTH2s(el2E2DMap);  

  // el2seedE
  MakeSubDirs(el2seedE2DSubMap,fOutDir);
  Analysis::SaveTH2s(el2seedE2DMap,el2seedE2DSubMap);
  for (TH2MapIter mapiter = el2seedE2DMap.begin(); mapiter != el2seedE2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,el2seedE2DSubMap[name],el2seedEbins,name);
  }
  Analysis::DeleteTH2s(el2seedE2DMap);  
}

void Analysis::OutputRunPlots()
{      
  MakeSubDirs(runs2DSubMap,fOutDir);
  Analysis::SaveTH2s(runs2DMap,runs2DSubMap);
  for (TH2MapIter mapiter = runs2DMap.begin(); mapiter != runs2DMap.end(); ++mapiter){
    TString name = (*mapiter).first;
    Analysis::Make1DTimingPlots((*mapiter).second,runs2DSubMap[name],dRunNos,name);
  }
  Analysis::DeleteTH2s(runs2DMap);  
}

void Analysis::OutputTrigEffPlots()
{
  MakeSubDirs(trTH1SubMap,fOutDir);
  ComputeRatioPlot(n_hltdoubleel_el1pt,d_hltdoubleel_el1pt,trTH1Map["hltdoubleel_el1pt"]);
  ComputeRatioPlot(n_hltdoubleel_el2pt,d_hltdoubleel_el2pt,trTH1Map["hltdoubleel_el2pt"]);
  Analysis::SaveTH1s(trTH1Map,trTH1SubMap);
  if (!fIsMC) Analysis::DumpTH1Names(trTH1Map,trTH1SubMap);
  Analysis::DeleteTH1s(trTH1Map);

  // delete by hand throw away plots
  delete n_hltdoubleel_el1pt;
  delete d_hltdoubleel_el1pt;
  delete n_hltdoubleel_el2pt;
  delete d_hltdoubleel_el2pt;
}

void Analysis::Make1DTimingPlots(TH2F *& hist2D, const TString subdir2D, const DblVec& bins2D, TString name)
{
   TH1Map th1Dmap; TStrMap th1Dsubmap; TStrIntMap th1Dbinmap;
   Analysis::Project2Dto1D(hist2D,subdir2D,th1Dmap,th1Dsubmap,th1Dbinmap);
   Analysis::ProduceMeanSigma(th1Dmap,th1Dbinmap,name,hist2D->GetXaxis()->GetTitle(),bins2D,subdir2D);
   Analysis::DeleteTH1s(th1Dmap);
}

void Analysis::Project2Dto1D(TH2F *& hist2d, TString subdir2d, TH1Map & th1map, TStrMap & subdir1dmap, TStrIntMap & th1binmap) 
{
  // y bins same width, x bins are variable

  TString  basename = hist2d->GetName();
  Int_t    nybins   = hist2d->GetNbinsY();
  Double_t ylow     = hist2d->GetYaxis()->GetXmin();
  Double_t yhigh    = hist2d->GetYaxis()->GetXmax();
  TString  xtitle   = hist2d->GetXaxis()->GetTitle();
  TString  ytitle   = hist2d->GetYaxis()->GetTitle();

  // loop over all x bins to project out
  for (Int_t i = 1; i <= hist2d->GetNbinsX(); i++){  
    // if no bins are filled, then continue to next plot
    Bool_t isFilled = false;
    for (Int_t j = 1; j <= hist2d->GetNbinsY(); j++) {
      if (hist2d->GetBinContent(i,j) > 0) {isFilled = true; break;}
    }
    if (!isFilled) continue;

    Double_t xlow  = hist2d->GetXaxis()->GetBinLowEdge(i); 
    Double_t xhigh = hist2d->GetXaxis()->GetBinUpEdge(i);

    TString histname = "";
    // First create each histogram
    if     (basename.Contains("td_zeta",TString::kExact)) { //ugh
      histname = Form("%s_%3.1f_%3.1f",basename.Data(),xlow,xhigh);
      th1map[histname.Data()] = Analysis::MakeTH1Plot(histname.Data(),"",nybins,ylow,yhigh,Form("%s in %s bin: %3.1f to %3.1f",ytitle.Data(),xtitle.Data(),xlow,xhigh),
						      "Events",subdir1dmap,subdir2d);
    }
    else if ((basename.Contains("zphi",TString::kExact))       || (basename.Contains("abszeta",TString::kExact))     ||
	     (basename.Contains("el1eta",TString::kExact))     || (basename.Contains("el2eta",TString::kExact))      || 
	     (basename.Contains("el1seedeta",TString::kExact)) || (basename.Contains("el2seedeta",TString::kExact))) { //triple ugh
      histname = Form("%s_%4.2f_%4.2f",basename.Data(),xlow,xhigh);
      th1map[histname.Data()] = Analysis::MakeTH1Plot(histname.Data(),"",nybins,ylow,yhigh,Form("%s in %s bin: %4.2f to %4.2f",ytitle.Data(),xtitle.Data(),xlow,xhigh),
						      "Events",subdir1dmap,subdir2d);
    }
    else if (basename.Contains("vtxZ",TString::kExact)) { //quintuple ugh
      histname = Form("%s_%5.2f_%5.2f",basename.Data(),xlow,xhigh);
      th1map[histname.Data()] = Analysis::MakeTH1Plot(histname.Data(),"",nybins,ylow,yhigh,Form("%s in %s bin: %5.2f to %5.2f",ytitle.Data(),xtitle.Data(),xlow,xhigh),
						      "Events",subdir1dmap,subdir2d);
    }
    else if (basename.Contains("runs",TString::kExact)) { //double ugh
      Int_t runno = (xlow+xhigh)/2;
      histname = Form("%s_%i",basename.Data(),runno);
      th1map[histname.Data()] = Analysis::MakeTH1Plot(histname.Data(),"",nybins,ylow,yhigh,Form("%s in Run: %i",ytitle.Data(),runno),
						      "Events",subdir1dmap,subdir2d);
    }
    else if (basename.Contains("nvtx",TString::kExact)) { //quadruple ugh
      Int_t ivtx = (xlow+xhigh)/2;
      histname = Form("%s_%i",basename.Data(),ivtx);
      th1map[histname.Data()] = Analysis::MakeTH1Plot(histname.Data(),"",nybins,ylow,yhigh,Form("%s in nPV: %i",ytitle.Data(),ivtx),
						      "Events",subdir1dmap,subdir2d);
    }
    else { // "normal" filling
      Int_t ixlow  = Int_t(xlow); 
      Int_t ixhigh = Int_t(xhigh); 
      histname = Form("%s_%i_%i",basename.Data(),ixlow,ixhigh);
      th1map[histname.Data()] = Analysis::MakeTH1Plot(histname.Data(),"",nybins,ylow,yhigh,Form("%s in %s bin: %i to %i",ytitle.Data(),xtitle.Data(),ixlow,ixhigh),
						      "Events",subdir1dmap,subdir2d);
    }
    th1binmap[histname.Data()] = i; // universal pairing

    // then fill corresponding bins from y
    for (Int_t j = 0; j <= hist2d->GetNbinsY() + 1; j++) {
      // check to make sure not zero though...
      if ( !(hist2d->GetBinContent(i,j) < 0) ) {
	th1map[histname.Data()]->SetBinContent(j,hist2d->GetBinContent(i,j));
	th1map[histname.Data()]->SetBinError(j,hist2d->GetBinError(i,j)); 
      }
      else{
	th1map[histname.Data()]->SetBinContent(i,0);
	th1map[histname.Data()]->SetBinError(i,0);
      }
    }
  }
}

void Analysis::ProduceMeanSigma(TH1Map & th1map, TStrIntMap & th1binmap, TString name, TString xtitle, const DblVec vxbins, TString subdir)
{
  // need to convert bins into array
  const Double_t * axbins = &vxbins[0]; // https://stackoverflow.com/questions/2923272/how-to-convert-vector-to-array-c

  // initialize new mean/sigma histograms
  TH1F * outhist_mean  = new TH1F(Form("%s_mean_%s",name.Data(),Config::formname.Data()),"",vxbins.size()-1,axbins);
  outhist_mean->GetXaxis()->SetTitle(xtitle.Data());
  if (name.Contains("td_",TString::kExact)) {
    outhist_mean->GetYaxis()->SetTitle("Dielectron Seed Time Difference #mu [ns]");
  }
  else if (name.Contains("el1",TString::kExact)) {
    outhist_mean->GetYaxis()->SetTitle("Leading Electron Seed Time #mu [ns]");
  }
  else if (name.Contains("el2",TString::kExact)) {
    outhist_mean->GetYaxis()->SetTitle("Subleading Electron Seed Time #mu [ns]");
  }
  outhist_mean->SetLineColor(fColor);
  outhist_mean->SetMarkerColor(fColor);
  outhist_mean->GetYaxis()->SetTitleOffset(outhist_mean->GetYaxis()->GetTitleOffset() * Config::TitleFF);
  outhist_mean->Sumw2();

  TH1F * outhist_sigma  = new TH1F(Form("%s_sigma_%s",name.Data(),Config::formname.Data()),"",vxbins.size()-1,axbins);
  outhist_sigma->GetXaxis()->SetTitle(xtitle.Data());
  if (name.Contains("td_",TString::kExact)) {
    outhist_sigma->GetYaxis()->SetTitle("Dielectron Seed Time Difference #sigma [ns]");
  }
  else if (name.Contains("el1",TString::kExact)) {
    outhist_sigma->GetYaxis()->SetTitle("Leading Electron Seed Time #sigma [ns]");
  }
  else if (name.Contains("el2",TString::kExact)) {
    outhist_sigma->GetYaxis()->SetTitle("Subleading Electron Seed Time #sigma [ns]");
  }
  outhist_sigma->SetLineColor(fColor);
  outhist_sigma->SetMarkerColor(fColor);
  outhist_sigma->GetYaxis()->SetTitleOffset(outhist_sigma->GetYaxis()->GetTitleOffset() * Config::TitleFF);
  outhist_sigma->Sumw2();

  // use this to store runs that by themselves produce bad fits
  TH1Map tempmap; // a bit hacky I admit...
  Int_t  sumevents = 0; // also a bit hacky...

  for (TH1MapIter mapiter = th1map.begin(); mapiter != th1map.end(); ++mapiter) { 
    Int_t bin = th1binmap[(*mapiter).first]; // returns which bin each th1 corresponds to one the new plot
    
    // only do this for run number plots --> check each plot has enough entries to do fit
    if ( name.Contains("runs",TString::kExact) ) {
      if ( ((*mapiter).second->Integral() + sumevents) < Config::nEventsCut ) { 
	
	// store the plot to be added later
	tempmap[(*mapiter).first] = (TH1F*)(*mapiter).second->Clone(Form("%s_tmp",(*mapiter).first.Data()));

	// record the number of events to exceed cut
	sumevents += tempmap[(*mapiter).first]->Integral();
	continue; // don't do anything more, just go to next run
      } 
      
      if ( tempmap.size() > 0 ) { // since we passed the last check, see if we had any bad runs -- if so, add to this one

	// set bin to weighted average of events
	Int_t numer = 0;
	numer += bin * (*mapiter).second->Integral();
	Int_t denom = sumevents + (*mapiter).second->Integral();

	// add the bad histos to the good one
	for (TH1MapIter tempmapiter = tempmap.begin(); tempmapiter != tempmap.end(); ++tempmapiter) {
	  (*mapiter).second->Add((*tempmapiter).second);
	  numer += th1binmap[(*tempmapiter).first] * (*tempmapiter).second->Integral();
	}
	
	// set "effective" bin number
	bin = numer / denom; 

	// now delete everything in temp map to avoid leaking
	for (TH1MapIter tempmapiter = tempmap.begin(); tempmapiter != tempmap.end(); ++tempmapiter) {
	  delete ((*tempmapiter).second);
	}
	tempmap.clear();
	sumevents = 0; // reset sum events, too
      }
    } // end check over "runs"

    // declare fit, prep it, then use it for binned plots
    TF1 * fit; 
    Analysis::PrepFit(fit,(*mapiter).second);
    (*mapiter).second->Fit(fit->GetName(),"RBQ0");

    // need to capture the mean and sigma
    Float_t mean,  emean;
    Float_t sigma, esigma;
    Analysis::GetMeanSigma(fit,mean,emean,sigma,esigma);

    outhist_mean->SetBinContent(bin,mean);
    outhist_mean->SetBinError(bin,emean);

    outhist_sigma->SetBinContent(bin,sigma);
    outhist_sigma->SetBinError(bin,esigma);

    // save a copy of the fitted histogram with the fit
    Analysis::SaveTH1andFit((*mapiter).second,subdir,fit);
  } // end loop over th1s

  TString xruntitle = outhist_mean->GetXaxis()->GetTitle();
  if (name.Contains("runs",TString::kExact) && xruntitle.Contains("EBEB",TString::kExact)) {
    outhist_mean->SetMaximum(  0.04 );
    outhist_mean->SetMinimum( -0.04 );

    outhist_sigma->SetMaximum( 0.50 );
    outhist_sigma->SetMinimum( 0.25 );
  }

  // write output mean/sigma hists to file
  fOutFile->cd();
  outhist_mean->Write();
  outhist_sigma->Write();

  // and want to dump them too (for stacking)!
  if (!fIsMC && !name.Contains("runs",TString::kExact)) {fTH1Dump << outhist_mean->GetName()  << " " << subdir.Data() << std::endl;}
  if (!fIsMC && !name.Contains("runs",TString::kExact)) {fTH1Dump << outhist_sigma->GetName() << " " << subdir.Data() << std::endl;}

  // save log/lin of each plot
  TCanvas * canv = new TCanvas("canv","canv");
  canv->cd();

  outhist_mean->Draw("PE");
  CMSLumi(canv);
  canv->SaveAs(Form("%s/%s/%s.%s",fOutDir.Data(),subdir.Data(),outhist_mean->GetName(),Config::outtype.Data()));

  Float_t min = 1e9;
  for (Int_t i = 1; i <= outhist_sigma->GetNbinsX(); i++){
    Float_t tmpmin = outhist_sigma->GetBinContent(i);
    if (tmpmin < min && tmpmin != 0){ min = tmpmin; }
  }
  outhist_sigma->SetMinimum( min / 1.1 );
  outhist_sigma->Draw("PE");
  CMSLumi(canv);
  canv->SaveAs(Form("%s/%s/%s.%s",fOutDir.Data(),subdir.Data(),outhist_sigma->GetName(),Config::outtype.Data()));
  
  delete canv;
  delete outhist_sigma;
  delete outhist_mean;
}

void Analysis::PrepFit(TF1 *& fit, TH1F *& hist) 
{
  TF1 * tempfit = new TF1("temp","gaus(0)",-Config::fitrange,Config::fitrange);
  tempfit->SetParLimits(2,0,10);
  hist->Fit("temp","RQ0B");
  const Float_t tempp0 = tempfit->GetParameter(0); // constant
  const Float_t tempp1 = tempfit->GetParameter(1); // mean
  const Float_t tempp2 = tempfit->GetParameter(2); // sigma

  if (Config::formname.EqualTo("gaus1",TString::kExact)) {
    TFormula form(Config::formname.Data(),"[0]*exp(-0.5*((x-[1])/[2])**2)");
    fit  = new TF1(Form("%s_fit",Config::formname.Data()),Config::formname.Data(),-Config::fitrange,Config::fitrange);
    fit->SetParameters(tempp0,tempp1,tempp2);
    fit->SetParLimits(2,0,10);
  }
  else if (Config::formname.EqualTo("gaus2",TString::kExact)) {
    TFormula form(Config::formname.Data(),"[0]*exp(-0.5*((x-[1])/[2])**2)+[3]*exp(-0.5*((x-[4])/[5])**2)");
    fit  = new TF1(Form("%s_fit",Config::formname.Data()),Config::formname.Data(),-Config::fitrange,Config::fitrange);
    fit->SetParameters(tempp0,tempp1,tempp2,tempp0/10,0,tempp2*4);
    fit->SetParLimits(2,0,10);
    fit->SetParLimits(5,0,10);
  }
  else if (Config::formname.EqualTo("gaus2fm",TString::kExact)) {
    TFormula form(Config::formname.Data(),"[0]*exp(-0.5*((x-[1])/[2])**2)+[3]*exp(-0.5*((x-[1])/[4])**2)");
    fit  = new TF1(Form("%s_fit",Config::formname.Data()),Config::formname.Data(),-Config::fitrange,Config::fitrange);
    fit->SetParameters(tempp0,tempp1,tempp2,tempp0/10,tempp2*4);
    fit->SetParLimits(2,0,10);
    fit->SetParLimits(4,0,10);
  }
  else {
    std::cerr << "Yikes, you picked a function that we made that does not even exist ...exiting... " << std::endl;
    exit(1);
  }

  fit->SetLineColor(kMagenta-3); //kViolet-6
  delete tempfit;
}

void Analysis::GetMeanSigma(TF1 *& fit, Float_t & mean, Float_t & emean, Float_t & sigma, Float_t & esigma) 
{
  if (Config::formname.EqualTo("gaus1",TString::kExact)) {
    mean   = fit->GetParameter(1);
    emean  = fit->GetParError (1);
    sigma  = fit->GetParameter(2);
    esigma = fit->GetParError (2);
  }
  else if (Config::formname.EqualTo("gaus2",TString::kExact)) {
    const Float_t const1 = fit->GetParameter(0); 
    const Float_t const2 = fit->GetParameter(3);
    const Float_t denom =  const1 + const2;

    mean   = (const1*fit->GetParameter(1) + const2*fit->GetParameter(4))/denom;
    sigma  = (const1*fit->GetParameter(2) + const2*fit->GetParameter(5))/denom;

    emean  = rad2(const1*fit->GetParError(1),const2*fit->GetParError(4));
    esigma = rad2(const1*fit->GetParError(2),const2*fit->GetParError(5));

    emean  = std::sqrt(emean) /denom;
    esigma = std::sqrt(esigma)/denom;
  }
  else if (Config::formname.EqualTo("gaus2fm",TString::kExact)) {
    const Float_t const1 = fit->GetParameter(0); 
    const Float_t const2 = fit->GetParameter(3);
    const Float_t denom =  const1 + const2;

    mean   = fit->GetParameter(1);
    sigma  = (const1*fit->GetParameter(2) + const2*fit->GetParameter(4))/denom;

    emean  = fit->GetParError(1);
    esigma = rad2(const1*fit->GetParError(2),const2*fit->GetParError(4));

    esigma = std::sqrt(esigma)/denom;
  }
}

void Analysis::DrawSubComp(TF1 *& fit, TCanvas *& canv, TF1 *& sub1, TF1 *& sub2) 
{
  if (Config::formname.EqualTo("gaus2",TString::kExact)) {
    sub1 = new TF1("sub1","gaus(0)",-Config::fitrange,Config::fitrange);
    sub1->SetParameters(fit->GetParameter(0),fit->GetParameter(1),fit->GetParameter(2));
  
    sub2 = new TF1("sub2","gaus(0)",-Config::fitrange,Config::fitrange);
    sub2->SetParameters(fit->GetParameter(3),fit->GetParameter(4),fit->GetParameter(5));
  } 
  else if (Config::formname.EqualTo("gaus2fm",TString::kExact)) {
    sub1 = new TF1("sub1","gaus(0)",-Config::fitrange,Config::fitrange);
    sub1->SetParameters(fit->GetParameter(0),fit->GetParameter(1),fit->GetParameter(2));
  
    sub2 = new TF1("sub2","gaus(0)",-Config::fitrange,Config::fitrange);
    sub2->SetParameters(fit->GetParameter(3),fit->GetParameter(1),fit->GetParameter(4));
  } 
  else { // do not do anything in this function
    return;
  }

  canv->cd();

  sub1->SetLineColor(kRed) ;  // kgreen-3
  sub1->SetLineWidth(2);
  sub1->SetLineStyle(7);
  sub1->Draw("same");

  sub2->SetLineColor(kBlue); // kViolet-3
  sub2->SetLineWidth(2);
  sub2->SetLineStyle(7);
  sub2->Draw("same");
}

TH1F * Analysis::MakeTH1Plot(TString hname, TString htitle, Int_t nbins, Double_t xlow, Double_t xhigh,
			     TString xtitle, TString ytitle, TStrMap& subdirmap, TString subdir) 
{
  TH1F * hist = new TH1F(hname.Data(),htitle.Data(),nbins,xlow,xhigh);
  hist->SetLineColor(kBlack);
  if (fIsMC) {
    hist->SetFillColor(fColor);
    hist->SetMarkerColor(fColor);
  }
  hist->GetXaxis()->SetTitle(xtitle.Data());
  hist->GetYaxis()->SetTitle(ytitle.Data());
  hist->GetYaxis()->SetTitleOffset(hist->GetYaxis()->GetTitleOffset() * Config::TitleFF);
  hist->Sumw2();

  // cheat a bit and set subdir map here
  subdirmap[hname] = subdir;
  
  return hist;
}

TH2F * Analysis::MakeTH2Plot(TString hname, TString htitle, const DblVec& vxbins, Int_t nbinsy, Double_t ylow, 
			     Double_t yhigh, TString xtitle, TString ytitle, TStrMap& subdirmap, TString subdir) 
{
  // need to convert vectors into arrays per ROOT
  const Double_t * axbins = &vxbins[0]; // https://stackoverflow.com/questions/2923272/how-to-convert-vector-to-array-c

  TH2F * hist = new TH2F(hname.Data(),htitle.Data(),vxbins.size()-1,axbins,nbinsy,ylow,yhigh);
  hist->GetXaxis()->SetTitle(xtitle.Data());
  hist->GetYaxis()->SetTitle(ytitle.Data());
  hist->Sumw2();

  // cheat a bit and set subdir map here
  subdirmap[hname] = subdir;
  
  return hist;
}

void Analysis::SaveTH1s(TH1Map & th1map, TStrMap & subdirmap) 
{
  fOutFile->cd();

  for (TH1MapIter mapiter = th1map.begin(); mapiter != th1map.end(); ++mapiter) { 
    // save to output file
    (*mapiter).second->Write(); // map is map["hist name",TH1D*]

    // now draw onto canvas to save as png
    TCanvas * canv = new TCanvas("canv","canv");
    canv->cd();
    (*mapiter).second->Draw( fIsMC ? "HIST" : "PE" );
    
    // first save as linear, then log
    canv->SetLogy(0);
    CMSLumi(canv);
    canv->SaveAs(Form("%s/%s/lin/%s.%s",fOutDir.Data(),subdirmap[(*mapiter).first].Data(),(*mapiter).first.Data(),Config::outtype.Data()));

    canv->SetLogy(1);
    CMSLumi(canv);
    canv->SaveAs(Form("%s/%s/log/%s.%s",fOutDir.Data(),subdirmap[(*mapiter).first].Data(),(*mapiter).first.Data(),Config::outtype.Data()));

    delete canv;

    // Draw and save normalized clone; then take original and fit it with some copy/past code
    TString xtitle = (*mapiter).second->GetXaxis()->GetTitle();
    if (xtitle.Contains("Time",TString::kExact)) {
      // first clone th1, then normalize it, then draw + save it
      TH1F * normhist = (TH1F*)(*mapiter).second->Clone(Form("%s_norm",(*mapiter).first.Data()));
      normhist->Scale(1./normhist->Integral());
      fOutFile->cd();
      //      normhist->Write();

      TCanvas * normcanv = new TCanvas("normcanv","normcanv");
      normcanv->cd();
      normhist->Draw( fIsMC ? "HIST" : "PE" );
      
      normcanv->SetLogy(0);
      CMSLumi(normcanv);
      normcanv->SaveAs(Form("%s/%s/lin/%s_norm.%s",fOutDir.Data(),subdirmap[(*mapiter).first].Data(),(*mapiter).first.Data(),Config::outtype.Data()));
      
      normcanv->SetLogy(1);
      CMSLumi(normcanv);
      normcanv->SaveAs(Form("%s/%s/log/%s_norm.%s",fOutDir.Data(),subdirmap[(*mapiter).first].Data(),(*mapiter).first.Data(),Config::outtype.Data()));

      if (!fIsMC) {fTH1Dump << normhist->GetName()  << " " << subdirmap[(*mapiter).first].Data() << std::endl;}

      delete normhist;
      delete normcanv;

      // fit th1s with time in the name --> could factor out this copy-paste...

      // make it a "graph" with the right colors
      (*mapiter).second->SetLineColor(fColor);
      (*mapiter).second->SetMarkerColor(fColor);
      
      // declare fit, then pass it to prepper along with hist for prefitting
      TF1 * fit; 
      Analysis::PrepFit(fit,(*mapiter).second);      
      (*mapiter).second->Fit(fit->GetName(),"RBQ0");

      TCanvas * fitcanv = new TCanvas("fitcanv","fitcanv");
      fitcanv->cd();
      (*mapiter).second->Draw("PE");
      fit->SetLineWidth(3);
      fit->Draw("same");
      
      // draw sub components of fit it applies
      TF1 * sub1; TF1 * sub2;
      Analysis::DrawSubComp(fit,fitcanv,sub1,sub2);
      (*mapiter).second->Draw("PE SAME"); // redraw to put points on top

      // first save as linear, then log
      fitcanv->SetLogy(0);
      CMSLumi(fitcanv);
      fitcanv->SaveAs(Form("%s/%s/lin/%s_%s.%s",fOutDir.Data(),subdirmap[(*mapiter).first].Data(),(*mapiter).first.Data(),fit->GetName(),Config::outtype.Data()));
      
      fitcanv->SetLogy(1);
      CMSLumi(fitcanv);
      fitcanv->SaveAs(Form("%s/%s/log/%s_%s.%s",fOutDir.Data(),subdirmap[(*mapiter).first].Data(),(*mapiter).first.Data(),fit->GetName(),Config::outtype.Data()));
      
      delete fitcanv;
      Analysis::DeleteFit(fit,sub1,sub2);
    }
  }
}

void Analysis::SaveTH1andFit(TH1F *& hist, TString subdir, TF1 *& fit) 
{
  // now draw onto canvas to save as png
  TCanvas * canv = new TCanvas(Form("%s_%s",hist->GetName(),fit->GetName()),Form("%s_%s",hist->GetName(),fit->GetName()));
  canv->cd();
  hist->Draw("PE");
  fit->SetLineWidth(3);
  fit->Draw("same");

  // draw subcomponents, too, if they apply
  TF1 * sub1; TF1 * sub2;
  Analysis::DrawSubComp(fit,canv,sub1,sub2);
  hist->Draw("PE SAME"); // redraw to get data points on top

  fOutFile->cd();

  // write out the canvas, but only print canvases if specfied
  canv->SetLogy(0);
  CMSLumi(canv);
  canv->Write();
  if (Config::saveFits) {
    canv->SaveAs(Form("%s/%s/lin/%s_%s.%s",fOutDir.Data(),subdir.Data(),hist->GetName(),fit->GetName(),Config::outtype.Data()));
    
    canv->SetLogy(1);
    CMSLumi(canv);
    canv->SaveAs(Form("%s/%s/log/%s_%s.%s",fOutDir.Data(),subdir.Data(),hist->GetName(),fit->GetName(),Config::outtype.Data()));
  }
  delete canv;
  Analysis::DeleteFit(fit,sub1,sub2); // now that the fitting is done being used, delete it (as well as sub component gaussians)
}

void Analysis::SaveTH2s(TH2Map & th2map, TStrMap & subdirmap) 
{
  fOutFile->cd();

  TCanvas * canv = new TCanvas("canv","canv");
  for (TH2MapIter mapiter = th2map.begin(); mapiter != th2map.end(); ++mapiter) { 
    
    (*mapiter).second->Write(); // map is map["hist name",TH1D*]

    // now draw onto canvas to save as png
    canv->cd();
    (*mapiter).second->Draw("colz");
    
    // only save as linear
    canv->SetLogy(0);
    CMSLumi(canv);
    canv->SaveAs(Form("%s/%s/%s_2D.%s",fOutDir.Data(),subdirmap[(*mapiter).first].Data(),(*mapiter).first.Data(),Config::outtype.Data()));
  }

  delete canv;
}

void Analysis::DumpTH1Names(TH1Map & th1map, TStrMap & subdirmap) 
{
  for (TH1MapIter mapiter = th1map.begin(); mapiter != th1map.end(); ++mapiter) { 
    fTH1Dump << (*mapiter).first.Data()  << " " <<  subdirmap[(*mapiter).first].Data() << std::endl;
  }
}

void Analysis::DeleteFit(TF1 *& fit, TF1 *& sub1, TF1 *& sub2) 
{
  delete fit;
  if (!Config::formname.EqualTo("gaus1",TString::kExact)) { delete sub1; }
  if (!Config::formname.EqualTo("gaus1",TString::kExact)) { delete sub2; }
}

void Analysis::DeleteTH1s(TH1Map & th1map)
{
  for (TH1MapIter mapiter = th1map.begin(); mapiter != th1map.end(); ++mapiter) { 
    delete ((*mapiter).second);
  }
  th1map.clear();
}

void Analysis::DeleteTH2s(TH2Map & th2map) 
{
  for (TH2MapIter mapiter = th2map.begin(); mapiter != th2map.end(); ++mapiter) { 
    delete ((*mapiter).second);
  }
  th2map.clear();
}
  
void Analysis::InitTree() {
  // Set branch addresses and branch pointers
  fInTree->SetBranchAddress("event", &event, &b_event);
  fInTree->SetBranchAddress("run", &run, &b_run);
  fInTree->SetBranchAddress("lumi", &lumi, &b_lumi);
  fInTree->SetBranchAddress("hltsingleel", &hltsingleel, &b_hltsingleel);
  fInTree->SetBranchAddress("hltdoubleel", &hltdoubleel, &b_hltdoubleel);
  fInTree->SetBranchAddress("hltelnoiso", &hltelnoiso, &b_hltelnoiso);
  fInTree->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
  fInTree->SetBranchAddress("vtxX", &vtxX, &b_vtxX);
  fInTree->SetBranchAddress("vtxY", &vtxY, &b_vtxY);
  fInTree->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
  fInTree->SetBranchAddress("nvetoelectrons", &nvetoelectrons, &b_nvetoelectrons);
  fInTree->SetBranchAddress("nlooseelectrons", &nlooseelectrons, &b_nlooseelectrons);
  fInTree->SetBranchAddress("nmediumelectrons", &nmediumelectrons, &b_nmediumelectrons);
  fInTree->SetBranchAddress("ntightelectrons", &ntightelectrons, &b_ntightelectrons);
  fInTree->SetBranchAddress("nheepelectrons", &nheepelectrons, &b_nheepelectrons);
  fInTree->SetBranchAddress("el1pid", &el1pid, &b_el1pid);
  fInTree->SetBranchAddress("el1pt", &el1pt, &b_el1pt);
  fInTree->SetBranchAddress("el1eta", &el1eta, &b_el1eta);
  fInTree->SetBranchAddress("el1phi", &el1phi, &b_el1phi);
  fInTree->SetBranchAddress("el1E", &el1E, &b_el1E);
  fInTree->SetBranchAddress("el1p", &el1p, &b_el1p);
  fInTree->SetBranchAddress("el2pid", &el2pid, &b_el2pid);
  fInTree->SetBranchAddress("el2pt", &el2pt, &b_el2pt);
  fInTree->SetBranchAddress("el2eta", &el2eta, &b_el2eta);
  fInTree->SetBranchAddress("el2phi", &el2phi, &b_el2phi);
  fInTree->SetBranchAddress("el2E", &el2E, &b_el2E);
  fInTree->SetBranchAddress("el2p", &el2p, &b_el2p);
  fInTree->SetBranchAddress("el1scX", &el1scX, &b_el1scX);
  fInTree->SetBranchAddress("el1scY", &el1scY, &b_el1scY);
  fInTree->SetBranchAddress("el1scZ", &el1scZ, &b_el1scZ);
  fInTree->SetBranchAddress("el1scE", &el1scE, &b_el1scE);
  fInTree->SetBranchAddress("el2scX", &el2scX, &b_el2scX);
  fInTree->SetBranchAddress("el2scY", &el2scY, &b_el2scY);
  fInTree->SetBranchAddress("el2scZ", &el2scZ, &b_el2scZ);
  fInTree->SetBranchAddress("el2scE", &el2scE, &b_el2scE);
  fInTree->SetBranchAddress("el1rhXs", &el1rhXs, &b_el1rhXs);
  fInTree->SetBranchAddress("el1rhYs", &el1rhYs, &b_el1rhYs);
  fInTree->SetBranchAddress("el1rhZs", &el1rhZs, &b_el1rhZs);
  fInTree->SetBranchAddress("el1rhtimes", &el1rhtimes, &b_el1rhtimes);
  fInTree->SetBranchAddress("el2rhXs", &el2rhXs, &b_el2rhXs);
  fInTree->SetBranchAddress("el2rhYs", &el2rhYs, &b_el2rhYs);
  fInTree->SetBranchAddress("el2rhZs", &el2rhZs, &b_el2rhZs);
  fInTree->SetBranchAddress("el2rhtimes", &el2rhtimes, &b_el2rhtimes);
  fInTree->SetBranchAddress("el1seedX", &el1seedX, &b_el1seedX);
  fInTree->SetBranchAddress("el1seedY", &el1seedY, &b_el1seedY);
  fInTree->SetBranchAddress("el1seedZ", &el1seedZ, &b_el1seedZ);
  fInTree->SetBranchAddress("el1seedE", &el1seedE, &b_el1seedE);
  fInTree->SetBranchAddress("el1seedtime", &el1seedtime, &b_el1seedtime);
  fInTree->SetBranchAddress("el2seedX", &el2seedX, &b_el2seedX);
  fInTree->SetBranchAddress("el2seedY", &el2seedY, &b_el2seedY);
  fInTree->SetBranchAddress("el2seedZ", &el2seedZ, &b_el2seedZ);
  fInTree->SetBranchAddress("el2seedE", &el2seedE, &b_el2seedE);
  fInTree->SetBranchAddress("el2seedtime", &el2seedtime, &b_el2seedtime);
  fInTree->SetBranchAddress("el1nrh", &el1nrh, &b_el1nrh);
  fInTree->SetBranchAddress("el2nrh", &el2nrh, &b_el2nrh);
  fInTree->SetBranchAddress("zmass", &zmass, &b_zmass);
  fInTree->SetBranchAddress("zpt", &zpt, &b_zpt);
  fInTree->SetBranchAddress("zeta", &zeta, &b_zeta);
  fInTree->SetBranchAddress("zphi", &zphi, &b_zphi);
  fInTree->SetBranchAddress("zE", &zE, &b_zE);
  fInTree->SetBranchAddress("zp", &zp, &b_zp);
  
  if (fIsMC){ // initialize extra branches if MC
    fInTree->SetBranchAddress("puobs", &puobs, &b_puobs);
    fInTree->SetBranchAddress("putrue", &putrue, &b_putrue);
    fInTree->SetBranchAddress("wgt", &wgt, &b_wgt);
    fInTree->SetBranchAddress("genzpid", &genzpid, &b_genzpid);
    fInTree->SetBranchAddress("genzpt", &genzpt, &b_genzpt);
    fInTree->SetBranchAddress("genzeta", &genzeta, &b_genzeta);
    fInTree->SetBranchAddress("genzphi", &genzphi, &b_genzphi);
    fInTree->SetBranchAddress("genzmass", &genzmass, &b_genzmass);
    fInTree->SetBranchAddress("genel1pid", &genel1pid, &b_genel1pid);
    fInTree->SetBranchAddress("genel1pt", &genel1pt, &b_genel1pt);
    fInTree->SetBranchAddress("genel1eta", &genel1eta, &b_genel1eta);
    fInTree->SetBranchAddress("genel1phi", &genel1phi, &b_genel1phi);
    fInTree->SetBranchAddress("genel2pid", &genel2pid, &b_genel2pid);
    fInTree->SetBranchAddress("genel2pt", &genel2pt, &b_genel2pt);
    fInTree->SetBranchAddress("genel2eta", &genel2eta, &b_genel2eta);
    fInTree->SetBranchAddress("genel2phi", &genel2phi, &b_genel2phi);
  }
}
