#include "TString.h"
#include "Common.cpp"
#include "CommonTimeFit.cpp"
#include "TimeFitter.cpp"

void runTimeFitter(const TString & infilename, const TString & plotconfig, const TString & miscconfig,
		   const TString & timefitconfig, const TString & era, const TString & outfiletext)
{
  TimeFitter fitter(infilename,plotconfig,miscconfig,timefitconfig,era,outfiletext);
  fitter.MakeTimeFits();
}

int main ( int argc, char *argv[] ){

        if( argc != 7 ) { std::cout << "Insufficent arguments." << std::endl; }
        else {
                TString infilename(argv[1]);
                TString plotconfig(argv[2]);
                TString miscconfig(argv[3]);
                TString timefitconfig(argv[4]);
                TString era(argv[5]);
                TString outfiletext(argv[6]);
                runTimeFitter( infilename, plotconfig, miscconfig, timefitconfig, era, outfiletext );
        }
        return 1;
}

