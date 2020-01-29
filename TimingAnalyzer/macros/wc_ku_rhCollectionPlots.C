#include "Skimmer.hh"
#include "Common.cpp+"
#include "TROOT.h"

#include <iostream>

void wc_ku_rhCollectionPlots( string infilename, string outfilename ){

    const int  nAlgos = 4; // { RtStc, RtOOTStc, kuMfootStc, kuMfootCCStc } -or- { Rt, Mini, WtStc, WtOOTStc }
    const int nOotAs = 10;
    const string disphotreename("tree/disphotree");

    auto fInFile = TFile::Open(infilename.c_str(), "update");
    auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());
    std::cout << "Opened Tree: " << fInTree << " in File : " << fInFile << std::endl; 
    
    std::vector<Float_t> *   rhE = 0;
    std::vector<UInt_t> *   rhID = 0;
    std::vector<Float_t> *   rhtime = 0;
    std::vector<Float_t> *   rhTOF = 0;
    std::vector<Float_t> *   kurhtime = 0;
    std::vector<UInt_t> *   kurhID = 0;
    std::vector<Float_t> *   kuStcrhtime = 0;
    std::vector<UInt_t> *   kuStcrhID = 0;
    std::vector<Float_t> *   kuNotStcrhtime = 0;
    std::vector<UInt_t> *   kuNotStcrhID = 0;
    std::vector<Float_t> *   kuWtStcrhtime = 0;
    std::vector<UInt_t> *   kuWtStcrhID = 0;
    std::vector<Float_t> *   kuWootStcrhtime = 0;
    std::vector<UInt_t> *   kuWootStcrhID = 0;
    std::vector<Float_t> *   kuMfootStcrhtime = 0;
    std::vector<UInt_t> *   kuMfootStcrhID = 0;
    std::vector<Float_t> *   kuMfootCCStcrhtime = 0;
    std::vector<UInt_t> *   kuMfootCCStcrhID = 0;

    std::vector<unsigned int> * uRhId = 0;  
    std::vector<float> * amplitude = 0;
    std::vector<float> * ootA0 = 0;
    std::vector<float> * ootA1 = 0;
    std::vector<float> * ootA2 = 0;
    std::vector<float> * ootA3 = 0;
    std::vector<float> * ootA4 = 0;
    std::vector<float> * ootA5 = 0;
    std::vector<float> * ootA6 = 0;
    std::vector<float> * ootA7 = 0;
    std::vector<float> * ootA8 = 0;
    std::vector<float> * ootA9 = 0;

    TBranch * b_rhE;
    TBranch * b_rhID;
    TBranch * b_rhtime;
    TBranch * b_rhTOF;
    TBranch * b_kurhtime;
    TBranch * b_kurhID;
    TBranch * b_kuStcrhtime;
    TBranch * b_kuStcrhID;
    TBranch * b_kuNotStcrhtime;
    TBranch * b_kuNotStcrhID;
    TBranch * b_kuWtStcrhtime;
    TBranch * b_kuWtStcrhID;
    TBranch * b_kuWootStcrhtime;
    TBranch * b_kuWootStcrhID;
    TBranch * b_kuMfootStcrhtime;
    TBranch * b_kuMfootStcrhID;
    TBranch * b_kuMfootCCStcrhtime;
    TBranch * b_kuMfootCCStcrhID;

    TBranch * b_uRhId;
    TBranch * b_amplitude;
    TBranch * b_ootA0;
    TBranch * b_ootA1;
    TBranch * b_ootA2;
    TBranch * b_ootA3;
    TBranch * b_ootA4;
    TBranch * b_ootA5;
    TBranch * b_ootA6;
    TBranch * b_ootA7;
    TBranch * b_ootA8;
    TBranch * b_ootA9; 

    fInTree->SetBranchAddress("rhE",&rhE,&b_rhE);
    fInTree->SetBranchAddress("rhID",&rhID,&b_rhID);
    fInTree->SetBranchAddress("rhtime",&rhtime,&b_rhtime);
    fInTree->SetBranchAddress("rhTOF",&rhTOF,&b_rhTOF);
    fInTree->SetBranchAddress("kurhtime",&kurhtime,&b_kurhtime);
    fInTree->SetBranchAddress("kurhID",&kurhID,&b_kurhID);
    fInTree->SetBranchAddress("kuStcrhtime",&kuStcrhtime,&b_kuStcrhtime);
    fInTree->SetBranchAddress("kuStcrhID",&kuStcrhID,&b_kuStcrhID);
    fInTree->SetBranchAddress("kuNotStcrhtime",&kuNotStcrhtime,&b_kuNotStcrhtime);
    fInTree->SetBranchAddress("kuNotStcrhID",&kuNotStcrhID,&b_kuNotStcrhID);
    fInTree->SetBranchAddress("kuWtStcrhtime",&kuWtStcrhtime,&b_kuWtStcrhtime);
    fInTree->SetBranchAddress("kuWtStcrhID",&kuWtStcrhID,&b_kuWtStcrhID);
    fInTree->SetBranchAddress("kuWootStcrhtime",&kuWootStcrhtime,&b_kuWootStcrhtime);
    fInTree->SetBranchAddress("kuWootStcrhID",&kuWootStcrhID,&b_kuWootStcrhID);
    fInTree->SetBranchAddress("kuMfootStcrhtime",&kuMfootStcrhtime,&b_kuMfootStcrhtime);
    fInTree->SetBranchAddress("kuMfootStcrhID",&kuMfootStcrhID,&b_kuMfootStcrhID);
    fInTree->SetBranchAddress("kuMfootCCStcrhtime",&kuMfootCCStcrhtime,&b_kuMfootCCStcrhtime);
    fInTree->SetBranchAddress("kuMfootCCStcrhID",&kuMfootCCStcrhID,&b_kuMfootCCStcrhID);

    fInTree->SetBranchAddress("uRhId",&uRhId,&b_uRhId);
    fInTree->SetBranchAddress("amplitude",&amplitude,&b_amplitude);
    fInTree->SetBranchAddress("ootA0",&ootA0,&b_ootA0);
    fInTree->SetBranchAddress("ootA1",&ootA1,&b_ootA1);
    fInTree->SetBranchAddress("ootA2",&ootA2,&b_ootA2);
    fInTree->SetBranchAddress("ootA3",&ootA3,&b_ootA3);
    fInTree->SetBranchAddress("ootA4",&ootA4,&b_ootA4);
    fInTree->SetBranchAddress("ootA5",&ootA5,&b_ootA5);
    fInTree->SetBranchAddress("ootA6",&ootA6,&b_ootA6);
    fInTree->SetBranchAddress("ootA7",&ootA7,&b_ootA7);
    fInTree->SetBranchAddress("ootA8",&ootA8,&b_ootA8);
    fInTree->SetBranchAddress("ootA9",&ootA9,&b_ootA9);


    TH2F * rtMapEB[nAlgos];
    TH2F * rhtvE[nAlgos];
    TH2F * rhtvAmplitude[nAlgos];
//    std::vector<TH2F *> tempvect;
//    std::vector<std::vector<TH2F *>> rhtvOotA;
//    vector <TH2F *> rhtvOotA[nAlgos];
//    for( auto i = 0U; i < nAlgos; i++){ rhtvOotA.push_back( tempvect ); }
//    for( auto i = 0U; i < nAlgos; i++){ for(auto a = 0U; a < nOotAs; a++){ (rhtvOotA[i]).push_back(0); }}   
    TH2F * rhtvOotA[nAlgos][nOotAs];
    TH1F * timeDist[nAlgos];
    TH1F * idDist[nAlgos];

    int tdiv = 200000;
    float tstart = -20000.0;
    float tend = 20000.0;

    int adiv = 400;
    float aend = 20.0;

    int ediv = 400;
    float eend = 2000.0;

    //int iddiv = 500;
    //int idstart = 835000000;
    //int idend = 840000000;

    std::cout << "Setting up Histograms." << std::endl;
//Mini, Rt, RtStc, RtOOTStc, WtStc, WtOOTStc, kuMfootStc, kuMfootCCStc
//    string algostring[nAlgos] = { "Mini", "Rt", "RtStc", "RtOOTStc", "WtStc", "WtNotStc", "kuMfootStc", "kuMfootCCStc" };
    string algostring[nAlgos] = { "RtStc", "RtOOTStc", "kuMfootStc", "kuMfootCCStc" };
//    string algostring[nAlgos] = { "Mini", "Rt", "WtStc", "WtNotStc" };
    string voot[nOotAs] = {"vootA0","vootA1","vootA2","vootA3","vootA4","vootA5","vootA6","vootA7","vootA8","vootA9"};
    for( auto i = 0; i < nAlgos; i++){
		std::cout << "Setting up Histograms for " << algostring[i] << std::endl;
		string hnameEB( "Xtal"+algostring[i]+"RecTimeEBMapEB"); 
                string htitleEB( "Xtal "+algostring[i]+" RecTimeEBMap EB ");
                rtMapEB[i] = new TH2F(hnameEB.c_str(),htitleEB.c_str(),171,-85.5,85.5,360,0.5,360.5);
                rtMapEB[i]->Sumw2();
                string hnameE( "rht"+algostring[i]+"vE");
                string htitleE( "rhTime "+algostring[i]+" v Energy ");
                rhtvE[i] = new TH2F(hnameE.c_str(),htitleE.c_str(),tdiv,tstart,tend,ediv,0,eend);
                rhtvE[i]->Sumw2();
                string hnameAm( "rht"+algostring[i]+"vAmplitue");
                string htitleAm( "rhTime "+algostring[i]+" v Amplitude ");
                rhtvAmplitude[i] = new TH2F(hnameAm.c_str(),htitleAm.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvAmplitude[i]->Sumw2();
		std::cout << "	Setting up Histograms for ootA "<< std::endl;
	    	for(auto a = 0U; a < nOotAs; a++){
			std::cout << "  -- " << voot[a]  << std::endl;
                	string hnameOotA( "rht"+algostring[i]+voot[a]);
                	string htitleOotA( "rhTime "+algostring[i]+" v "+voot[a]);
                	rhtvOotA[a][i] = new TH2F(hnameOotA.c_str(),htitleOotA.c_str(),tdiv,tstart,tend,adiv,0,aend);
                	rhtvOotA[a][i]->Sumw2();
		}
                string hnametd( "rht"+algostring[i]+"distribution");
                string htitletd( "rhTime "+algostring[i]+" Distribution ");
                timeDist[i] = new TH1F(hnametd.c_str(),htitletd.c_str(),tdiv,tstart,tend);
                timeDist[i]->Sumw2();
		std::cout << "Finished. " << std::endl;
                //string hnameid( "id"+algostring[i]+"distro");
                //string htitleid( "ID "+algostring[i]+" Distro ");
                //idDist[i] = new TH1F(hnameid.c_str(),htitleid.c_str(),iddiv,idstart,idend);
                //idDist[i]->Sumw2();
    }

    std::cout << "Setting up DetIDs." << std::endl;
    Common::SetupDetIDs();

    // >> calcs  <<
    std::cout << "Setting up For Main Loop." << std::endl;
    //const auto nEntries = fInTree->GetEntries();
    const auto nEntries = 100;
    std::cout << "Proccessing " << nEntries << " entries." << std::endl;
    for (auto entry = 0U; entry < nEntries; entry++){
	if( entry%100000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries." << std::endl; 

        b_rhE->GetEntry(entry);
        b_rhID->GetEntry(entry);
        b_rhtime->GetEntry(entry);
        b_rhTOF->GetEntry(entry);
        b_kurhtime->GetEntry(entry);
        b_kurhID->GetEntry(entry);
        b_kuStcrhtime->GetEntry(entry);
        b_kuStcrhID->GetEntry(entry);
        b_kuNotStcrhtime->GetEntry(entry);
        b_kuNotStcrhID->GetEntry(entry);
        b_kuWtStcrhtime->GetEntry(entry);
        b_kuWtStcrhID->GetEntry(entry);
        b_kuWootStcrhtime->GetEntry(entry);
        b_kuWootStcrhID->GetEntry(entry);
        b_kuMfootStcrhtime->GetEntry(entry);
        b_kuMfootStcrhID->GetEntry(entry);
        b_kuMfootCCStcrhtime->GetEntry(entry);
        b_kuMfootCCStcrhID->GetEntry(entry);

        b_uRhId->GetEntry(entry);
        b_amplitude->GetEntry(entry);

        b_ootA0->GetEntry(entry);
        b_ootA1->GetEntry(entry);
        b_ootA2->GetEntry(entry);
        b_ootA3->GetEntry(entry);
        b_ootA4->GetEntry(entry);
        b_ootA5->GetEntry(entry);
        b_ootA6->GetEntry(entry);
        b_ootA7->GetEntry(entry);
        b_ootA8->GetEntry(entry);
        b_ootA9->GetEntry(entry);

        std::vector<Float_t> * ootAs[nOotAs] = { ootA0, ootA1, ootA2, ootA3, ootA4, ootA5, ootA6, ootA7, ootA8, ootA9 };

        //std::vector<UInt_t> * ids[nAlgos] = { rhID, kurhID, kuStcrhID, kuNotStcrhID, kuWtStcrhID, kuWootStcrhID, kuMfootStcrhID, kuMfootCCStcrhID };
	//for(auto i = 0U; i < nAlgos; i++){ for (auto j = 0U; j < (*(ids[i])).size(); j++){ idDist[i]->Fill((*(ids[i]))[j]); }}

//        std::vector<Float_t> * tvects[nAlgos] = { rhtime, kurhtime, kuStcrhtime, kuNotStcrhtime, kuWtStcrhtime, kuWootStcrhtime, kuMfootStcrhtime, kuMfootCCStcrhtime };
        std::vector<Float_t> * tvects[nAlgos] = { kuStcrhtime, kuNotStcrhtime, kuMfootStcrhtime, kuMfootCCStcrhtime };
//        std::vector<Float_t> * tvects[nAlgos] = { rhtime, kurhtime, kuWtStcrhtime, kuWootStcrhtime };
        for (auto j = 0U; j < (*rhID).size(); j++){


                        const auto id_j = (*rhID)[j]; 
                        const auto E_j  = (*rhE) [j];
			const auto & idinfo = Common::DetIDMap[id_j];

			float times[nAlgos] = {0.f};
                        times[0] = (*(tvects[0]))[j];
                        for(UInt_t seed = 0; seed < (*kurhID).size(); seed++ ){
                                if( (*kurhID)[seed] == id_j ){
                                        for(auto i = 1U; i < nAlgos; i++){ times[i] = (*(tvects[i]))[seed]; }
                                        break;
                                }
                        }

			float oota[nOotAs] = {0.f};
			float amp = 0;
                        for(UInt_t seed = 0; seed < (*uRhId).size(); seed++ ){
                                if( (*uRhId)[seed] == id_j ){
					amp = (*amplitude)[seed];
                                        for(auto i = 1U; i < nAlgos; i++){ 
						for(auto a = 0U; a < nOotAs; a++){ oota[a] = (*(ootAs[a]))[seed];} 
					}
                                        break;
                                }
                        }

                        for(auto i = 0U; i < nAlgos; i++){ 
				timeDist[i]->Fill(times[i]);
				rhtvE[i]->Fill(times[i],E_j);
 				if(idinfo.ecal == ECAL::EB){ rtMapEB[i]->Fill(idinfo.i2,idinfo.i1,times[i]); }
				for(auto a = 0U; a < nOotAs; a++){ rhtvOotA[a][i]->Fill(times[i],oota[a]); }
				rhtvAmplitude[i]->Fill(times[i],amp);				
			}

    	} // end outer double loop over rechits
             //std::cout << "RecHits Loop done "<< std::endl;
    }  //  end entry loop

    TFile* fOutFile = new TFile( outfilename.c_str(), "RECREATE" );
    fOutFile->cd();

    std::cout << "Write Output Maps and Hists" << std::endl;
    for( auto i = 0; i < nAlgos; i++){
	rtMapEB[i]->Write();
	timeDist[i]->Write();
	rhtvE[i]->Write();
        //idDist[i]->Write();
	for(auto a = 0U; a < nOotAs; a++){ rhtvOotA[a][i]->Write(); }
	rhtvAmplitude[i]->Write();
    }

}
