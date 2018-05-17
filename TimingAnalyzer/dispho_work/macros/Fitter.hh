#ifndef __Fitter__
#define __Fitter__

// ROOT inludes
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TString.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TPaveText.h"

// RooFit includes
#include "RooFit.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooAbsPdf.h"
#include "RooWorkspace.h"

// STL includes
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

// Common include
#include "Common.hh"

// Special enum for type of fit
enum FitType {TwoD, X, Y};

// Special struct for each fit
struct FitInfo
{
  FitInfo(const RooArgList & arglist, const TString & text, const FitType & fit)
    : ArgList(arglist), Text(text), Fit(fit) {}

  // input params
  const RooArgList ArgList;
  const TString Text;
  const FitType Fit;

  // PDF inputs/outputs
  std::map<TString,RooDataHist*> DataHistMap;
  std::map<TString,RooHistPdf*>  HistPdfMap;
  RooAddPdf * BkgdPdf;

  // model for fit
  RooExtendPdf * BkgdExtPdf;
  RooExtendPdf * SignExtPdf;
  RooAddPdf    * ModelPdf;
};

class Fitter
{
public:
  Fitter(const TString & fitconfig, const TString & outfiletext);
  ~Fitter();

  // Initialize
  void SetupDefaultValues();
  void SetupConfig();
  void ReadFitConfig();
  void ReadPlotConfig();
  void SetupOutTree();

  // Deleting
  void DeleteFitInfo(FitInfo & fitInfo);
  template <typename T>
  void DeleteMap(T & Map);

  // Main calls
  void DoMain();
  void PrepareCommon();
  template <typename T>
  void PreparePdfs(const T & HistMap, FitInfo & fitInfo);
  void RunExperiments(FitInfo & fitInfo);
  void ImportToWS(FitInfo & fitInfo);
  void SaveOutTree();
  void MakeConfigPave();
  
  // Prep for common variables/datasets/etc
  void GetInputHists();
  void ScaleCRtoSR();
  void DumpInputInfo();
  void DumpIntegralsAndDraw(TH2F *& hist2D, const TString & text, const Bool_t isBlind, const Bool_t isDraw);
  void Project2DHistTo1D();
  void DeclareCoefficients();
  void DeclareXYVars();

  // Prep for pdfs
  template <typename T>
  void DeclareDatasets(const T & HistMap, FitInfo & fitInfo);
  void DeclareSamplePdfs(FitInfo & fitInfo);

  // Subroutines for fitting
  void MakeFit(FitInfo & fitInfo);
  void ThrowPoisson(const FitInfo & fitInfo);
  void BuildModel(FitInfo & fitInfo);
  void GenerateData(FitInfo & fitInfo);
  void FitModel(FitInfo & fitInfo);
  void GetPredicted(FitInfo & fitInfo);
  void DrawFit(RooRealVar *& var, const TString & title, const FitInfo & fitInfo);
  void FillOutTree(const FitInfo & fitInfo);
  void DeleteModel(FitInfo & fitInfo, const Int_t ifit);

  // Subroutines for dumping ws 
  void DumpWS(const FitInfo & fitInfo, const TString & label);

  // Helper Routines
  Float_t GetMinimum(TGraphAsymmErrors *& graph, TH1F *& hist1, TH1F *& hist2);
  Float_t GetMaximum(TGraphAsymmErrors *& graph, TH1F *& hist);

private:
  // settings
  const TString fFitConfig;
  const TString fOutFileText;
  TString fPlotConfig;

  // Bools+Values
  Bool_t fBkgdOnly;
  Bool_t fGenData;
  Bool_t fDoFits;
  Bool_t fMakeWS;
  Bool_t fDumpWS;
  Int_t  fNFits;
  Int_t  fNDraw;

  // scale factors of initial guess for fit range * fNTotal{Bkgd/Sign}
  Float_t fScaleRangeLow;
  Float_t fScaleRangeHigh;

  // Hist info
  std::vector<Double_t> fXBins;
  Bool_t fXVarBins;
  TString fXTitle;
  std::vector<Double_t> fYBins;
  Bool_t fYVarBins;
  TString fYTitle;

  // Input names
  TString fGJetsFileName;
  TString fQCDFileName;
  TString fSRFileName;
  TString fSignalsFileName;

  // Input files
  TFile * fGJetsFile;
  TFile * fQCDFile;
  TFile * fSRFile;
  TFile * fSignalsFile;

  // Input Hists
  TH2F * fGJetsHistMC_CR;
  TH2F * fGJetsHistMC_SR;
  TH2F * fQCDHistMC_CR;
  TH2F * fQCDHistMC_SR;
  std::map<TString,TH2F*> fHistMap2D;
  std::map<TString,TH1F*> fHistMapX;
  std::map<TString,TH1F*> fHistMapY;

  // Counts + scaling norm from the start
  Float_t fScaleTotalBkgd;
  Float_t fScaleTotalSign;
  Float_t fNTotalBkgd;
  Float_t fNTotalSign;

  // Constants used to build model + post-fit numbers
  std::map<TString,RooRealVar*> fFracMap; 
  RooRealVar * fNPredBkgd;
  RooRealVar * fNPredSign;

  // Number of events to generate, and scale norm up or down when throwing poisson for building generation template
  Float_t fScaleGenBkgd;
  Float_t fScaleGenSign;
  Float_t fNGenBkgd;
  Float_t fNGenSign;

  // Blinding (for RooPlots)
  TString fXCut;
  TString fYCut;
  
  // Blinding (for TH's)
  Bool_t  fXBlindedLow;
  Bool_t  fXBlindedUp;
  Bool_t  fYBlindedLow;
  Bool_t  fYBlindedUp;
  Float_t fXLowCut;
  Float_t fXUpCut;
  Float_t fYLowCut;
  Float_t fYUpCut;

  // Roo vars and bins
  RooRealVar * fX;
  RooRealVar * fY;
  
  RooBinning * fXRooBins;
  RooBinning * fYRooBins;

  // Style
  TStyle * fTDRStyle;

  // Output
  TFile     * fOutFile;
  TPaveText * fConfigPave;

  // Experiment output
  TTree * fOutTree;
  Float_t fNFitBkgd;
  Float_t fNFitBkgdErr;
  Float_t fNFitSign;
  Float_t fNFitSignErr;
  std::string fFitID;
};

#endif
