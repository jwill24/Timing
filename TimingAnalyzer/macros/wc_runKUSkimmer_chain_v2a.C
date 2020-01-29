#include "TString.h"
#include "Common.cpp+"
#include "wc_ku_Skimmer_chain_v2a.cpp+"

void wc_runKUSkimmer_chain_v2a(const TString & indir, const TString & outdir, const TString & filename, const TString & skimconfig)
{
  Skimmer skimmer(indir, outdir, filename, skimconfig);
  skimmer.EventLoop();
}
