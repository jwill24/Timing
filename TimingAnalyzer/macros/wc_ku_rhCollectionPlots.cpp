// ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TString.h"
#include "TColor.h"
#include "TPaveText.h"
#include "TText.h"

// STL includes
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <sys/stat.h>

enum ECAL {EB, EM, EP, NONE};
struct DetIDStruct
{
  DetIDStruct() {}
  DetIDStruct(const Int_t ni1, const Int_t ni2, const Int_t nTT, const Int_t & necal)
    : i1(ni1), i2(ni2), TT(nTT), ecal(necal) 
//  {}
  {
	//i1 = ni1;
	//i2 = ni2;
 	//TT = nTT;
	//ecal = necal; 
	//std::cout << "Setting " << i1 << " " << i2 << " " << ecal << std::endl; 
  }

  Int_t i1; // EB: iphi, EE: ix
  Int_t i2; // EB: ieta, EE: iy
  Int_t TT; // trigger tower
  Int_t ecal; // EB, EM, EP
};

void SetupDetIDsEB( std::map<UInt_t,DetIDStruct> &DetIDMap )
{
    const std::string detIDConfigEB("ecal_config/fullinfo_detids_EB.txt");
    std::ifstream infile( detIDConfigEB, std::ios::in);

    UInt_t cmsswId, dbID;
    Int_t hashedId, iphi, ieta, absieta, FED, SM, TT25, iTT, strip5, Xtal, phiSM, etaSM;
    TString pos;

    while (infile >> cmsswId >> dbID >> hashedId >> iphi >> ieta >> absieta >> pos >> FED >> SM >> TT25 >> iTT >> strip5 >> Xtal >> phiSM >> etaSM)
    {
	//std::cout << "DetID Input Line: " << cmsswId << " " << iphi << " "  << ieta << " " << 0 << std::endl;
    	DetIDMap[cmsswId] = {iphi,ieta,TT25,0};
        auto idinfo = DetIDMap[cmsswId];
        //std::cout << "DetID set to : " << idinfo.i1 << " " << idinfo.i2 << " " << idinfo.ecal << std::endl;
    }
}

void SetupDetIDsEE( std::map<UInt_t,DetIDStruct> &DetIDMap )
{
    const std::string detIDConfigEE("ecal_config/fullinfo_detids_EE.txt");
    std::ifstream infile( detIDConfigEE, std::ios::in);

    UInt_t cmsswId, dbID;
    Int_t hashedId, side, ix, iy, SC, iSC, Fed, TTCCU, strip, Xtal, quadrant;
    TString EE;

    while (infile >> cmsswId >> dbID >> hashedId >> side >> ix >> iy >> SC >> iSC >> Fed >> EE >> TTCCU >> strip >> Xtal >> quadrant)
    {
	int ec = 1;
	if( side > 0 ) ec = 2;
        //std::cout << "DetID Input Line: " << cmsswId << " " << ix << " "  << iy << " " << ec << std::endl; 
   	DetIDMap[cmsswId] = {ix,iy,TTCCU,ec};
        auto idinfo = DetIDMap[cmsswId];
        //std::cout << "DetID set to : " << idinfo.i1 << " " << idinfo.i2 << " " << idinfo.ecal << std::endl;
    }
}

void wc_ku_rhCollectionPlots( std::string infilename, std::string outfilename ){

    const int  nAlgos = 8; // { RtStc, RtOOTStc, kuMfootStc, kuMfootCCStc } -or- { Rt, Mini, WtStc, WtOOTStc }
    const int nOotAs = 10;
    const int bin_offset = 86;
    const std::string disphotreename("tree/disphotree");

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
    TH2F * rtMapEBt[nAlgos];
    TH2F * rtMapEBc[nAlgos];
    TH2F * rhtvE[nAlgos];
    TH2F * rhtvAmplitude[nAlgos];
//    std::vector<TH2F *> tempvect;
//    std::vector<std::vector<TH2F *>> rhtvOotA;
//    vector <TH2F *> rhtvOotA[nAlgos];
//    for( auto i = 0U; i < nAlgos; i++){ rhtvOotA.push_back( tempvect ); }
//    for( auto i = 0U; i < nAlgos; i++){ for(auto a = 0U; a < nOotAs; a++){ (rhtvOotA[i]).push_back(0); }}   
    TH2F * rhtvOotA0[nAlgos];
    TH2F * rhtvOotA1[nAlgos];
    TH2F * rhtvOotA2[nAlgos];
    TH2F * rhtvOotA3[nAlgos];
    TH2F * rhtvOotA4[nAlgos];
    TH2F * rhtvOotA5[nAlgos];
    TH2F * rhtvOotA6[nAlgos];
    TH2F * rhtvOotA7[nAlgos];
    TH2F * rhtvOotA8[nAlgos];
    TH2F * rhtvOotA9[nAlgos];
    TH1F * timeDist[nAlgos];
    TH1F * idDist[nAlgos];

    TH2F * timeDistMaps[nAlgos];   

    int tdiv = 12000;
    float tstart = -6000.0;
    float tend = 6000.0;

    int adiv = 400;
    float aend = 20.0;

    int ediv = 400;
    float eend = 2000.0;

    //int iddiv = 500;
    //int idstart = 835000000;
    //int idend = 840000000;

    std::cout << "Setting up Histograms." << std::endl;
//Mini, Rt, RtStc, RtOOTStc, WtStc, WtOOTStc, kuMfootStc, kuMfootCCStc
    std::string algostring[nAlgos] = { "Mini", "Rt", "RtStc", "RtOOTStc", "WtStc", "WtNotStc", "kuMfootStc", "kuMfootCCStc" };
//    std::string algostring[nAlgos] = { "RtStc", "RtOOTStc", "kuMfootStc", "kuMfootCCStc" };
//    std::string algostring[nAlgos] = { "Mini", "Rt", "WtStc", "WtNotStc" };
    std::string voot[nOotAs] = {"vootA0","vootA1","vootA2","vootA3","vootA4","vootA5","vootA6","vootA7","vootA8","vootA9"};
    for( auto i = 0; i < nAlgos; i++){
		std::cout << "Setting up Histograms for " << algostring[i] << std::endl;
		std::string hnameEB( "Xtal"+algostring[i]+"RecTimeEBMapEB"); 
                std::string htitleEB( "Xtal "+algostring[i]+" RecTimeEBMap EB ");
                rtMapEB[i] = new TH2F(hnameEB.c_str(),htitleEB.c_str(),171,-85.5,85.5,360,0.5,360.5);
                rtMapEB[i]->Sumw2();
                std::string hnameEBt( "Xtal"+algostring[i]+"RecTimeEBMapEBt");
                std::string htitleEBt( "Xtal "+algostring[i]+" RecTimeEBMap EBt ");
                rtMapEBt[i] = new TH2F(hnameEBt.c_str(),htitleEBt.c_str(),171,-85.5,85.5,360,0.5,360.5);
                rtMapEBt[i]->Sumw2();
                std::string hnameEBc( "Xtal"+algostring[i]+"RecTimeEBMapEBc");
                std::string htitleEBc( "Xtal "+algostring[i]+" RecTimeEBMap EBc ");
                rtMapEBc[i] = new TH2F(hnameEBc.c_str(),htitleEBc.c_str(),171,-85.5,85.5,360,0.5,360.5);
                rtMapEBc[i]->Sumw2();
                std::string hnameE( "rht"+algostring[i]+"vE");
                std::string htitleE( "rhTime "+algostring[i]+" v Energy ");
                rhtvE[i] = new TH2F(hnameE.c_str(),htitleE.c_str(),tdiv,tstart,tend,ediv,0,eend);
                rhtvE[i]->Sumw2();
                std::string hnameAm( "rht"+algostring[i]+"vAmplitue");
                std::string htitleAm( "rhTime "+algostring[i]+" v Amplitude ");
                rhtvAmplitude[i] = new TH2F(hnameAm.c_str(),htitleAm.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvAmplitude[i]->Sumw2();
		std::cout << "	Setting up Histograms for ootA "<< std::endl;
	    	//for(auto a = 0U; a < nOotAs; a++){
		//	std::cout << "  -- " << voot[a]  << std::endl;
                std::string hnameOotA0( "rht"+algostring[i]+voot[0]);
                std::string htitleOotA0( "rhTime "+algostring[i]+" v "+voot[0]);
                rhtvOotA0[i] = new TH2F(hnameOotA0.c_str(),htitleOotA0.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA0[i]->Sumw2();
                std::string hnameOotA1( "rht"+algostring[i]+voot[1]);
                std::string htitleOotA1( "rhTime "+algostring[i]+" v "+voot[1]);
                rhtvOotA1[i] = new TH2F(hnameOotA1.c_str(),htitleOotA1.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA1[i]->Sumw2();
                std::string hnameOotA2( "rht"+algostring[i]+voot[2]);
                std::string htitleOotA2( "rhTime "+algostring[i]+" v "+voot[2]);
                rhtvOotA2[i] = new TH2F(hnameOotA2.c_str(),htitleOotA2.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA2[i]->Sumw2();
                std::string hnameOotA3( "rht"+algostring[i]+voot[3]);
                std::string htitleOotA3( "rhTime "+algostring[i]+" v "+voot[3]);
                rhtvOotA3[i] = new TH2F(hnameOotA3.c_str(),htitleOotA3.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA3[i]->Sumw2();
                std::string hnameOotA4( "rht"+algostring[i]+voot[4]);
                std::string htitleOotA4( "rhTime "+algostring[i]+" v "+voot[4]);
                rhtvOotA4[i] = new TH2F(hnameOotA4.c_str(),htitleOotA4.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA4[i]->Sumw2();
                std::string hnameOotA5( "rht"+algostring[i]+voot[5]);
                std::string htitleOotA5( "rhTime "+algostring[i]+" v "+voot[5]);
                rhtvOotA5[i] = new TH2F(hnameOotA5.c_str(),htitleOotA5.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA5[i]->Sumw2();
                std::string hnameOotA6( "rht"+algostring[i]+voot[6]);
                std::string htitleOotA6( "rhTime "+algostring[i]+" v "+voot[6]);
                rhtvOotA6[i] = new TH2F(hnameOotA6.c_str(),htitleOotA6.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA6[i]->Sumw2();
                std::string hnameOotA7( "rht"+algostring[i]+voot[7]);
                std::string htitleOotA7( "rhTime "+algostring[i]+" v "+voot[7]);
                rhtvOotA7[i] = new TH2F(hnameOotA7.c_str(),htitleOotA7.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA7[i]->Sumw2();
                std::string hnameOotA8( "rht"+algostring[i]+voot[8]);
                std::string htitleOotA8( "rhTime "+algostring[i]+" v "+voot[8]);
                rhtvOotA8[i] = new TH2F(hnameOotA8.c_str(),htitleOotA8.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA8[i]->Sumw2();
                std::string hnameOotA9( "rht"+algostring[i]+voot[9]);
                std::string htitleOotA9( "rhTime "+algostring[i]+" v "+voot[9]);
                rhtvOotA9[i] = new TH2F(hnameOotA9.c_str(),htitleOotA9.c_str(),tdiv,tstart,tend,adiv,0,aend);
                rhtvOotA9[i]->Sumw2();
		//}
                std::string hnametd( "rht"+algostring[i]+"distribution");
                std::string htitletd( "rhTime "+algostring[i]+" Distribution ");
                timeDist[i] = new TH1F(hnametd.c_str(),htitletd.c_str(),tdiv,tstart,tend);
                timeDist[i]->Sumw2();
		std::cout << "Finished. " << std::endl;
		if( i < 2 ){ 
                        timeDistMaps[i] = 0;
		} else {
                	std::string hnametd( "rht"+algostring[i]+"vRtStc");
                	std::string htitletd( "rhTime "+algostring[i]+" vs RtStc ");
			timeDistMaps[i] = new TH2F(hnametd.c_str(),htitletd.c_str(),tdiv,tstart,tend,1200,-600.00,600.00);	        
		}
                //string hnameid( "id"+algostring[i]+"distro");
                //string htitleid( "ID "+algostring[i]+" Distro ");
                //idDist[i] = new TH1F(hnameid.c_str(),htitleid.c_str(),iddiv,idstart,idend);
                //idDist[i]->Sumw2();
    }


    std::cout << "Setting up DetIDs." << std::endl;
    std::map<UInt_t,DetIDStruct> DetIDMap;
    SetupDetIDsEB( DetIDMap );
    SetupDetIDsEE( DetIDMap );

    // >> calcs  <<
    std::cout << "Setting up For Main Loop." << std::endl;
    const auto nEntries = fInTree->GetEntries();
    //const auto nEntries = 100;
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

	//std::cout << "Finished getting braches." << std::endl;
        std::vector<Float_t> * ootAs[nOotAs] = { ootA0, ootA1, ootA2, ootA3, ootA4, ootA5, ootA6, ootA7, ootA8, ootA9 };

        //std::vector<UInt_t> * ids[nAlgos] = { rhID, kurhID, kuStcrhID, kuNotStcrhID, kuWtStcrhID, kuWootStcrhID, kuMfootStcrhID, kuMfootCCStcrhID };
	//for(auto i = 0U; i < nAlgos; i++){ for (auto j = 0U; j < (*(ids[i])).size(); j++){ idDist[i]->Fill((*(ids[i]))[j]); }}

        std::vector<Float_t> * tvects[nAlgos] = { rhtime, kurhtime, kuStcrhtime, kuNotStcrhtime, kuWtStcrhtime, kuWootStcrhtime, kuMfootStcrhtime, kuMfootCCStcrhtime };
//        std::vector<Float_t> * tvects[nAlgos] = { kuStcrhtime, kuNotStcrhtime, kuMfootStcrhtime, kuMfootCCStcrhtime };
//        std::vector<Float_t> * tvects[nAlgos] = { rhtime, kurhtime, kuWtStcrhtime, kuWootStcrhtime };
        for (auto j = 0U; j < (*rhID).size(); j++){


                        const auto id_j = (*rhID)[j]; 
                        const auto E_j  = (*rhE) [j];

			const auto idinfo = DetIDMap[id_j];
			//std::cout << "DetID Info: " << id_j << " " << idinfo.i1 << std::endl;

			float times[nAlgos] = {0.f};
                        times[0] = (*(tvects[0]))[j];
                        for(UInt_t seed = 0; seed < (*kurhID).size(); seed++ ){
                                if( (*kurhID)[seed] == id_j ){
                                        for(auto i = 1U; i < nAlgos; i++){ times[i] = (*(tvects[i]))[seed]; }
                                        break;
                                }
                        }
			//std::cout << "Finished getting rh times." << std::endl;

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
                        //std::cout << "Finished getting OOT amplitudes." << std::endl;

                        for(auto i = 0U; i < nAlgos; i++){ 
				timeDist[i]->Fill(times[i]);
				rhtvE[i]->Fill(times[i],E_j);
 				if(idinfo.ecal == 0){ 
					rtMapEBt[i]->Fill(idinfo.i2,idinfo.i1,times[i]); 
                                        rtMapEBc[i]->Fill(idinfo.i2,idinfo.i1,1);
				}
				//std::cout << "Finished filling time and energy histograms." << std::endl;
//				for(auto a = 0U; a < nOotAs; a++){ rhtvOotA[a][i]->Fill(times[i],oota[a]); }
				rhtvOotA0[i]->Fill(times[i],oota[0]);
                                rhtvOotA1[i]->Fill(times[i],oota[1]);
                                rhtvOotA2[i]->Fill(times[i],oota[2]);
                                rhtvOotA3[i]->Fill(times[i],oota[3]);
                                rhtvOotA4[i]->Fill(times[i],oota[4]);
                                rhtvOotA5[i]->Fill(times[i],oota[5]);
                                rhtvOotA6[i]->Fill(times[i],oota[6]);
                                rhtvOotA7[i]->Fill(times[i],oota[7]);
                                rhtvOotA8[i]->Fill(times[i],oota[8]);
                                rhtvOotA9[i]->Fill(times[i],oota[9]);
				rhtvAmplitude[i]->Fill(times[i],amp);
				//std::cout << "Finished filling OOT amplitude histograms." << std::endl;								
				if( i > 2 )  timeDistMaps[i]->Fill(times[i],times[2] );
			}
			//std::cout << "Finished filling histograms." << std::endl;

    	} // end outer double loop over rechits
        //std::cout << "RecHits Loop done "<< std::endl;
    }  //  end entry loop

    TFile* fOutFile = new TFile( outfilename.c_str(), "RECREATE" );
    fOutFile->cd();

    std::cout << "Write Output Maps and Hists" << std::endl;
    for( auto i = 0; i < nAlgos; i++){
        std::cout << "Make and write Output EB Maps for " << algostring[i] << std::endl;
	for( std::map<UInt_t,DetIDStruct>::iterator it=DetIDMap.begin(); it!=DetIDMap.end(); ++it){	
		auto info = DetIDMap[it->first];
		if(info.ecal == 0){
			auto ebt = rtMapEBt[i]->GetBinContent( info.i2 + bin_offset, info.i1);
                	auto ebc = rtMapEBc[i]->GetBinContent( info.i2 + bin_offset, info.i1);
			rtMapEB[i]->Fill(info.i2,info.i1, (ebt/ebc) );
		}		
	}
	rtMapEB[i]->Write();
        std::cout << "Writing Output Hists for " << algostring[i] << std::endl;
	timeDist[i]->Write();
	rhtvE[i]->Write();
        //idDist[i]->Write();
//	for(auto a = 0U; a < nOotAs; a++){ rhtvOotA[a][i]->Write(); }
	std::cout << "Writing Output OOTA Hists for " << algostring[i] << std::endl; 
        rhtvOotA0[i]->Write();
	rhtvOotA1[i]->Write();
        rhtvOotA2[i]->Write();
        rhtvOotA3[i]->Write();
        rhtvOotA4[i]->Write();
        rhtvOotA5[i]->Write();
        rhtvOotA6[i]->Write();
        rhtvOotA7[i]->Write();
        rhtvOotA8[i]->Write();
        rhtvOotA9[i]->Write();
	rhtvAmplitude[i]->Write();
	if( i > 2 )  timeDistMaps[i]->Write();
    }

    fInFile->Close();  
    fOutFile->Close();
    std::cout << "wc_ku_rhCollectionPlots : Thats all Folks!!" << std::endl;
}


int main ( int argc, char *argv[] ){

	if( argc != 3 ) { std::cout << "Insufficent arguments." << std::endl; }
	else {
		auto infilename = argv[1];
                auto outfilename = argv[2];
		wc_ku_rhCollectionPlots( infilename, outfilename );
	}
	return 1;
}
		



