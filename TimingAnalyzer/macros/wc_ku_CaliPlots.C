#include "Skimmer.hh"
#include "TROOT.h"

#include <iostream>
#include<string>

void wc_ku_CaliPlots( string infilename0, string infilename1, string outfilename ){

    string disphotreename("disphotree");
    int nIter = 25;

    auto fInFile0 = TFile::Open(infilename0.c_str(), "update");
    //auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());

    auto fInFile1 = TFile::Open(infilename1.c_str(), "update");
    //auto fCaliTree = (TTree*)fInFile->Get(disphotreename.c_str());

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

    TFile* fOutFile = new TFile( outfilename.c_str(), "RECREATE" );
    fOutFile->cd();  

    TH1F* ivhist[2][6];
    string loccode[6] = { "s65x90", "s65x270", "s10x90", "p10x270", "p65x90", "p65x270" };
    for( int i = 0; i < 2; i++ ){
	for( int j= 0; j < 6; j++ ){
		string name("ivhist_" + loccode[j] + "_cali" + to_string(i) );
    		ivhist[i][j] = new TH1F( name.c_str(), name.c_str(), 25, 0, 25);
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

    auto polehist = new TH1F( "icpole", "Cali Pole Plot", 1001, -0.020, 0.020 );

    for( int i2p = -85; i2p <= 85; i2p++ ){
	for( int i1p = 0; i1p <= 360; i1p++ ){ 	
    		polehist->Fill( ebmaps0[nIter]->GetBinContent( i2p, i1p ) - ebmaps1[nIter]->GetBinContent( i2p, i1p ) ); 
	}
    }

    for( int i = 0; i < 2; i++ ){
        for( int j= 0; j < 6; j++ ){
                ivhist[i][j]->Write(); 
        }
    }

    polehist->Write();

    MHist0->Write();
    MnotHist0->Write();
    MHist1->Write();
    MnotHist1->Write();
   
    //fOutFile->Write();
}


//
//        int bin_offset = 86;
//        int adjust = 100.0;
//
//        if ( phoseedEcal_0 == ECAL::EB ){
//              phoseedtimeCaliE0_0 = ebmape0->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
