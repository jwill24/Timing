#include "Skimmer.hh"
#include "TROOT.h"

#include <iostream>
#include<string>

void wc_ku_CaliPlots( string infilename0, string infilename1, string outfilename, int nIter ){

    string disphotreename("disphotree");

    auto fInFile0 = TFile::Open(infilename0.c_str(), "update");
    //auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());

    auto fInFile1 = TFile::Open(infilename1.c_str(), "update");
    //auto fCaliTree = (TTree*)fInFile->Get(disphotreename.c_str());

    std::cout << "Opened files : " << infilename0 << " : " << fInFile0 << std::endl;
    std::cout << "Opened files : " << infilename1 << " : " << fInFile1 << std::endl;

    //auto MHist = new TH1F( "MHist", "M Histogram", nIterations, 0, nIterations);
    //auto MnotHist = new TH1F( "MnotHist", "Mnot Histogram", nIterations, 0, nIterations);

    TH2F* ebmaps0[nIter];
    TH2F* ebmaps1[nIter];
    
    for( int i = 1; i <= nIter; i++ ){
	string histname( "AveXtalRtOOTStcPhoIcRecTimeEBMap_i" + to_string(i) );
    	ebmaps0[i] = (TH2F*)fInFile0->Get(histname.c_str());
        ebmaps1[i] = (TH2F*)fInFile1->Get(histname.c_str());
        std::cout << "Pulling ebmaps: " << ebmaps0[i] << " and " << ebmaps1[i] << " for iteration " << i << std::endl;
    	//epmapic = (TH2F*)fCaliFile->Get("AveXtalRtOOTStcPhoIcRecTimeEPMap_i25");
    	//emmapic = (TH2F*)fCaliFile->Get("AveXtalRtOOTStcPhoIcRecTimeEMMap_i25");
    }

    auto MHist0 = (TH1F*)fInFile0->Get("MHist");
    MHist0->SetName("MHist0");
    auto MnotHist0 = (TH1F*)fInFile0->Get("MnotHist");
    MnotHist0->SetName("MnotHist0");
    auto MHist1 = (TH1F*)fInFile1->Get("MHist");
    MHist1->SetName("MHist1");
    auto MnotHist1 = (TH1F*)fInFile1->Get("MnotHist");
    MnotHist1->SetName("MnotHist1");

    std::cout << "Opened MHist0 and MnotHist0 : " << MHist0 << " : " << MnotHist0 << std::endl;
    std::cout << "Opened MHist1 and MnotHist1 : " << MHist1 << " : " << MnotHist1 << std::endl;

    TFile* fOutFile = new TFile( outfilename.c_str(), "RECREATE" );
    fOutFile->cd();  

    TH1F* ivhist[2][6];
    string loccode[6] = { "s65x90", "s65x270", "s10x90", "p10x270", "p65x90", "p65x270" };
    for( int i = 0; i < 2; i++ ){
	for( int j= 0; j < 6; j++ ){
		string name("ivhist_" + loccode[j] + "_cali" + to_string(i) );
    		ivhist[i][j] = new TH1F( name.c_str(), name.c_str(), nIter, 0, nIter);
        }
    }

    int i2[6] = { 21, 21, 76, 96, 151, 151 };    
    int i1[6] = { 90, 270, 90, 270, 90, 270};
    //int bin_offset = 86;
    float adjust = 100.0;
    for( int j = 0; j < 6; j++ ){
	for( int i = 1; i <= nIter; i++ ){
    		ivhist[0][j]->Fill( i, ebmaps0[i]->GetBinContent( i2[j], i1[j] ) - adjust );  
    		ivhist[1][j]->Fill( i, ebmaps1[i]->GetBinContent( i2[j], i1[j] ) - adjust );
    	}
    }

    std::cout << "Create output hists " << std::endl;
    auto icdist0hist = new TH1F( "icdist0", "Cali0 EB Dist Plot", 400, -20.0, 20.0 );
    auto icdist1hist = new TH1F( "icdist1", "Cali1 EB Dist Plot", 400, -20.0, 20.0 );

    auto polehist = new TH1F( "icpole", "Cali EB Pole Plot", 400, -20.0, 20.0 );

    int count = 0;
    for( int i2p = 1; i2p <= 170; i2p++ ){
	for( int i1p = 1; i1p <= 360; i1p++ ){
		count++;
		if( ebmaps0[nIter]->GetBinContent( i2p, i1p ) == 0 ) continue; 	
    		polehist->Fill( ebmaps0[nIter]->GetBinContent( i2p, i1p ) - ebmaps1[nIter]->GetBinContent( i2p, i1p )); 
                icdist0hist->Fill( ebmaps0[nIter]->GetBinContent( i2p, i1p ) - adjust );
                icdist1hist->Fill( ebmaps1[nIter]->GetBinContent( i2p, i1p ) - adjust );
	}
    } 
    
    std::cout << "Count: " << count << std::endl;    

    for( int i = 0; i < 2; i++ ){
        for( int j= 0; j < 6; j++ ){
                ivhist[i][j]->Write(); 
        }
    }

    polehist->Write();
    icdist0hist->Write();
    icdist1hist->Write();

    MHist0->Write();
    MnotHist0->Write();
    MHist1->Write();
    MnotHist1->Write();
   
//    fOutFile->Write();
    delete fOutFile;
}

int main ( int argc, char *argv[] ){

        if( argc != 5 ) { std::cout << "Insufficent arguments." << std::endl; }
        else {
                auto infilename0 = argv[1];
                auto infilename1 = argv[2];
                auto outfilename = argv[3];
                auto niter = std::atoi(argv[4]);
		wc_ku_CaliPlots( infilename0, infilename1, outfilename, niter );
        }
        return 1;
}


