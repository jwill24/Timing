#include "TString.h"
#include "Common.cpp+"
#include "wc_ku_Skimmer_v2sp.cpp+"

void wc_runKUSkimmer(const TString & indir, const TString & outdir, const TString & filename, const TString & skimconfig)
{
  Skimmer skimmer(indir, outdir, filename, skimconfig);
  skimmer.EventLoop();
}
