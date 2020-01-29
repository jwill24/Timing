#include "TString.h"
#include "Common.cpp"
#include "TreePlotter2D.cpp"

void runTreePlotter2D( TString & infilename, TString & insignalfilename, TString & cutconfig, TString & varwgtmapconfig, 
			TString & plotconfig, TString & miscconfig, TString & era, TString & outfilename)
{
  TreePlotter2D plotter(infilename,insignalfilename,cutconfig,varwgtmapconfig,plotconfig,miscconfig,era,outfilename);
  plotter.MakeTreePlot2D();
}


int main ( int argc, char *argv[] ){

        if( argc != 9 ) { std::cout << "Insufficent arguments." << std::endl; }
        else {
                TString infilename(argv[1]);
                TString insignalfilename(argv[2]);
                TString cutconfig(argv[3]);
                TString varwgtmapconfig(argv[4]);
                TString plotconfig(argv[5]);
                TString miscconfig(argv[6]);
                TString era(argv[7]);
                TString outfilename(argv[8]);
		runTreePlotter2D( infilename, insignalfilename, cutconfig, varwgtmapconfig, plotconfig, miscconfig, era, outfilename);
        }
        return 1;
}

