#include "TString.h"
#include "Common.cpp+"
#include "wc_ku_Skimmer_v2wt.cpp+"

void wc_runKUSkimmer_v2wt(const TString & indir, const TString & outdir, const TString & filename, const TString & skimconfig)
{
  Skimmer skimmer(indir, outdir, filename, skimconfig);
  skimmer.EventLoop();
}
