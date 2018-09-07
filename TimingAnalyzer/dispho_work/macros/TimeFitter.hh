#ifndef __TimeFitter__
#define __TimeFitter__

// ROOT inludes
#include "TStyle.h"
#include "TFile.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TF1.h"
#include "TString.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"

// STL includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

// Common include
#include "Common.hh"

// fit struct
struct FitStruct
{
  FitStruct() {}
  FitStruct(const TString & label, const TString & inHistName) : label(label), inHistName(inHistName) {}

  const TString label;
  const TString inHistName;

  TH2F * Hist2D;
  std::map<Int_t,TH1F*>   Hist1DMap;
  std::map<Int_t,TF1*>    FitMap;
  std::map<TString,TH1F*> ResultsMap;
  TF1 * SigmaFit;
};

// fit result struct
struct FitResult
{
  FitResult() {}
  
  Float_t chi2ndf;
  Float_t chi2prob;
  Float_t mu;
  Float_t emu;
  Float_t sigma;
  Float_t esigma;
};

// sigma fit params
struct SigmaFitParams
{
  SigmaFitParams() {}
  
  Float_t low;
  Float_t val;
  Float_t up;
};

enum FitEnum {Gaus1, Gaus1core, Gaus2fm, Gaus2fmcore, Gaus3fm, Gaus3fmcore};

class TimeFitter
{
public:
  TimeFitter(const TString & infilename, const TString & plotconfig, const TString & miscconfig,
	     const TString & timefitconfig, const TString & era, const TString & outfiletext);
  ~TimeFitter();

  // config
  void SetupDefaults();
  void SetupCommon();
  void SetupPlotConfig();
  void SetupMiscConfig();
  void SetupTimeFitConfig();
  void ReadInitParams(const std::string & str, SigmaFitParams & params);

  // main calls
  void MakeTimeFits();
  void MakePlots(FitStruct & DataInfo, FitStruct & BkgdInfo);
  void DeleteInfo(FitStruct & FitInfo);

  // subroutines for making fits to variables
  void MakeTimeFit(FitStruct & FitInfo);
  void GetInputHist(FitStruct & FitInfo);
  void Project2Dto1DHists(FitStruct & FitInfo);
  void Fit1DHists(FitStruct & FitInfo);
  void ExtractFitResults(FitStruct & FitInfo);

  // helper functions for making fits to variables
  void PrepFit(TH1F *& hist1D, TF1 *& fit);
  void GetFitResult(const TF1 * fit, FitResult & result);

  // subroutines for making fits to sigma
  void MakeSigmaFit(FitStruct & FitInfo);
  void PrepSigmaFit(FitStruct & FitInfo);
  void FitSigmaHist(FitStruct & FitInfo);

  // subroutines for plotting
  void PrintCanvas(FitStruct & DataInfo, FitStruct & MCInfo, Float_t min, Float_t max, 
		   const TString & key, const Bool_t isLogy);

  // save meta data
  void MakeConfigPave();

  // additional helper functions
  template <typename T>
  void DeleteMap(T & Map);
  void GetMinMax(const TH1F * hist, Float_t & min, Float_t & max, const TString & key);
  TH1F * SetupHist(const TString & ytitle, const TString & yextra, const TString & label);

private:
  // settings
  const TString fInFileName;
  const TString fPlotConfig;
  const TString fMiscConfig;
  const TString fTimeFitConfig;
  const TString fEra;
  const TString fOutFileText;

  // style
  TStyle * fTDRStyle;
  TString fTitle;
  TString fXTitle;
  std::vector<Double_t> fXBins;
  Bool_t fXVarBins;
  TString fYTitle;
  Bool_t fDoLogX; // technically, read in from miscconfig

  // var fit config
  FitEnum fFit;
  Float_t fRangeLow;
  Float_t fRangeUp;
  TString fTimeText;

  // sigma fit config
  Bool_t fDoSigmaFit;
  TString fSigmaVarText;
  TString fSigmaVarUnit;
  SigmaFitParams fSigmaInitN;
  SigmaFitParams fSigmaInitC;

  // input
  TFile * fInFile;

  // output
  TFile * fOutFile;
  TPaveText * fConfigPave;
};

#endif