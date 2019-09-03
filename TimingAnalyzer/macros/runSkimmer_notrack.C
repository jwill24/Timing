#include "TString.h"
#include "Common.cpp+"
#include "Skimmer_notrack.cpp+"

void runSkimmer_notrack(const TString & indir, const TString & outdir, const TString & filename, const TString & skimconfig)
{
  Skimmer  skimmer(indir, outdir, filename, skimconfig);
  skimmer.EventLoop();
}
