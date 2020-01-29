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

using namespace std;

template <typename T> std::string to_string(T value)
{  
   //create an output string stream
   std::ostringstream os ;
   
   //throw the value into the string stream
   os << value ;
   
   //convert the string stream into a string and return
   return os.str() ;

//you can also do this
//std::string output;
//os >> output;  //throw whats in the string stream into the string
}

enum ECAL {EB, EM, EP, NONE};
std::string ecal_config_path("/home/t3-ku/jaking/ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/macros/ecal_config/");

struct DetIDStruct
{
  DetIDStruct() {}
  DetIDStruct(const Int_t inI1, const Int_t inI2, const Int_t inTT, const Int_t & inEcal) : i1(inI1), i2(inI2), TT(inTT), ecal(inEcal)  {}

  Int_t i1; // EB: iphi, EE: ix
  Int_t i2; // EB: ieta, EE: iy
  Int_t TT; // trigger tower
  Int_t ecal; // EB, EM, EP
};

void SetupDetIDsEB( std::map<UInt_t,DetIDStruct> &DetIDMap )
{
    const std::string detIDConfigEB(ecal_config_path+"fullinfo_detids_EB.txt");
    std::ifstream infile( detIDConfigEB, std::ios::in);

    UInt_t cmsswId, dbID;
    Int_t hashedId, iphi, ieta, absieta, FED, SM, TT25, iTT, strip5, Xtal, phiSM, etaSM;
    TString pos;

    while (infile >> cmsswId >> dbID >> hashedId >> iphi >> ieta >> absieta >> pos >> FED >> SM >> TT25 >> iTT >> strip5 >> Xtal >> phiSM >> etaSM)
    {
        //std::cout << "DetID Input Line: " << cmsswId << " " << iphi << " "  << ieta << " " << EB << std::endl;
        DetIDMap[cmsswId] = {iphi,ieta,TT25,EB};
        auto idinfo = DetIDMap[cmsswId];
        //std::cout << "DetID set to : " << idinfo.i1 << " " << idinfo.i2 << " " << idinfo.ecal << std::endl;
    }
}

void SetupDetIDsEE( std::map<UInt_t,DetIDStruct> &DetIDMap )
{
    const std::string detIDConfigEE(ecal_config_path+"fullinfo_detids_EE.txt");
    std::ifstream infile( detIDConfigEE, std::ios::in);

    UInt_t cmsswId, dbID;
    Int_t hashedId, side, ix, iy, SC, iSC, Fed, TTCCU, strip, Xtal, quadrant;
    TString EE;

    while (infile >> cmsswId >> dbID >> hashedId >> side >> ix >> iy >> SC >> iSC >> Fed >> EE >> TTCCU >> strip >> Xtal >> quadrant)
    {
        ECAL ec = EM;
        if( side > 0 ) ec = EP;
        //std::cout << "DetID Input Line: " << cmsswId << " " << ix << " "  << iy << " " << ec << std::endl; 
        DetIDMap[cmsswId] = {ix,iy,TTCCU,ec};
        auto idinfo = DetIDMap[cmsswId];
        //std::cout << "DetID set to : " << idinfo.i1 << " " << idinfo.i2 << " " << idinfo.ecal << std::endl;
    }
}


void wc_ku_InterCali_global_v2( string infilename, string outfilename, int mfc  ){

    const int  nIterations = 50;
    const int  nAlgos = 2; // RtStc, RtOOTStc //, WtOOTStc
    const int  nPhotons = 4;
    const double offset = 100.0;
    const int bin_offset = 86;
    const int mfcorrection = mfc;

    const double ri_ecut = 5.0;
    const double rj_ecut = 3.0;

    double M[nIterations] = {0.0};
    double Mnot[nIterations] = {0.0};
    double Mwoot[nIterations] = {0.0};
    int nM[nIterations] = {0};
    const int power = 2;

    auto MHist = new TH1F( "MHist", "M Histogram", nIterations, 0, nIterations);
    auto MnotHist = new TH1F( "MnotHist", "Mnot Histogram", nIterations, 0, nIterations);

    const string disphotreename("disphotree");

    auto fInFile = TFile::Open(infilename.c_str(), "update");
    auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());
    
    auto ebmape0 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE0EBMap");
    auto epmape0 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE0EPMap");
    auto emmape0 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE0EMMap");
    std::cout << " E0 hists: " << ebmape0 << " " << epmape0 << " " << emmape0 << std::endl;
    auto ebmape1 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE1EBMap");
    auto epmape1 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE1EPMap");
    auto emmape1 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE1EMMap");
    std::cout << " E1 hists: " << ebmape1 << " " << epmape1 << " " << emmape1 << std::endl;
    auto ebmap2e1 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime2E1EBMap");
    auto epmap2e1 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime2E1EPMap");
    auto emmap2e1 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime2E1EMMap");
    std::cout << " 2E1 hists: " << ebmap2e1 << " " << epmap2e1 << " " << emmap2e1 << std::endl;
    auto ebmap4e1 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime4E1EBMap");
    auto epmap4e1 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime4E1EPMap");
    auto emmap4e1 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime4E1EMMap");
    std::cout << " 4E1 hists: " << ebmap4e1 << " " << epmap4e1 << " " << emmap4e1 << std::endl;
    auto ebmape2 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE2EBMap");
    auto epmape2 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE2EPMap");
    auto emmape2 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE2EMMap");
    std::cout << " E2 hists: " << ebmape2 << " " << epmape2 << " " << emmape2 << std::endl;
    auto ebmapkue5 = (TH2F*)fInFile->Get("AveXtalRtStcRecTimeE5EBMap");
    auto epmapkue5 = (TH2F*)fInFile->Get("AveXtalRtStcRecTimeE5EPMap");
    auto emmapkue5 = (TH2F*)fInFile->Get("AveXtalRtStcRecTimeE5EMMap");
    std::cout << " E5 hists: " << ebmapkue5 << " " << epmapkue5 << " " << emmapkue5 << std::endl;
    auto ebmape5 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE5EBMap");
    auto epmape5 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE5EPMap");
    auto emmape5 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE5EMMap");
    std::cout << " E5 hists: " << ebmape5 << " " << epmape5 << " " << emmape5 << std::endl;
    auto ebmap2e5 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime2E5EBMap");
    auto epmap2e5 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime2E5EPMap");
    auto emmap2e5 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime2E5EMMap");
    std::cout << " 2E5 hists: " << ebmap2e5 << " " << epmap2e5 << " " << emmap2e5 << std::endl;
    auto ebmap4e5 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime4E5EBMap");
    auto epmap4e5 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime4E5EPMap");
    auto emmap4e5 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTime4E5EMMap");
    std::cout << " 4E5 hists: " << ebmap4e5 << " " << epmap4e5 << " " << emmap4e5 << std::endl;
    auto ebmape10 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE10EBMap");
    auto epmape10 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE10EPMap");
    auto emmape10 = (TH2F*)fInFile->Get("AveXtalRtOOTStcRecTimeE10EMMap");
    std::cout << " E10 hists: " << ebmape10 << " " << epmape10 << " " << emmape10 << std::endl;
    auto ebmapcl = (TH2F*)fInFile->Get("AveXtalRtOOTStcPhoClRecTimeEBMap");
    auto epmapcl = (TH2F*)fInFile->Get("AveXtalRtOOTStcPhoClRecTimeEPMap");
    auto emmapcl = (TH2F*)fInFile->Get("AveXtalRtOOTStcPhoClRecTimeEMMap");
    std::cout << " Cl hists: " << ebmapcl << " " << epmapcl << " " << emmapcl << std::endl;
    auto ebmapic = (TH2F*)fInFile->Get("AveXtalRtOOTStcPhoIcRecTimeEBMap");
    auto epmapic = (TH2F*)fInFile->Get("AveXtalRtOOTStcPhoIcRecTimeEPMap");
    auto emmapic = (TH2F*)fInFile->Get("AveXtalRtOOTStcPhoIcRecTimeEMMap");
    std::cout << " Ic hists: " << ebmapic << " " << epmapic << " " << emmapic << std::endl;

    std::vector<Int_t> * npho_recHits_0 = 0;
    std::vector<Int_t> * npho_recHits_1 = 0;
    std::vector<Int_t> * npho_recHits_2 = 0;
    std::vector<Int_t> * npho_recHits_3 = 0;
    std::vector<Float_t> *   fInRecHits_E = 0;
    std::vector<UInt_t> *   fInRecHits_ID = 0;
    std::vector<Float_t> *   fInRecHits_time = 0;
    std::vector<Float_t> *   fInRecHits_TOF = 0;
    std::vector<Float_t> *   kurhtime = 0;
    std::vector<UInt_t> *   kurhID = 0;
    std::vector<Float_t> *   kuStcrhtime = 0;
    std::vector<Float_t> *   kuNotrhtime = 0;
    std::vector<Float_t> *   kuNotStcrhtime = 0;
    std::vector<Float_t> *   kuWootStcrhtime = 0;

//{sumXtalRtStcPhoIcRecTime, sumXtalRtOOTStcPhoIcRecTime }; //, sumXtalWtOOTStcPhoIcRecTime };

    std::map<UInt_t,Float_t> sumXtalRtStcPhoIcRecTime;
    std::map<UInt_t,Float_t> sumXtalRtOOTStcPhoIcRecTime;
    std::map<UInt_t,Float_t> sumXtalWtOOTStcPhoIcRecTime;
    std::map<UInt_t,Float_t> numXtalIcRecTime;
    //double normRtStc = 0.0;
    //double normRtOOTStc = 0.0;
    //double normWtOOTStc = 0.0;

    bool isOOT_0;
    bool isOOT_1;
    bool isOOT_2;
    bool isOOT_3;
    double smin_0;
    double smin_1;
    double smin_2;
    double smin_3;
    double smaj_0;
    double smaj_1;
    double smaj_2;
    double smaj_3;
    UInt_t seedID_0;
    UInt_t seedID_1;
    double seedE_0;
    double seedE_1;
    double seedTOF_0;
    double seedTOF_1;

    TBranch * b_npho_recHits_0;
    TBranch * b_npho_recHits_1;
    TBranch * b_npho_recHits_2;
    TBranch * b_npho_recHits_3;
    TBranch * b_fInRecHits_E;
    TBranch * b_fInRecHits_ID;
    TBranch * b_fInRecHits_time;
    TBranch * b_fInRecHits_TOF;
    TBranch * b_kurhtime;
    TBranch * b_kurhID;
    TBranch * b_kuStcrhtime;
    TBranch * b_kuNotrhtime;
    TBranch * b_kuNotStcrhtime;
    TBranch * b_kuWootStcrhtime;
    TBranch * b_isOOT_0;
    TBranch * b_isOOT_1;
    TBranch * b_isOOT_2;
    TBranch * b_isOOT_3;
    TBranch * b_smin_0;
    TBranch * b_smin_1;
    TBranch * b_smin_2;
    TBranch * b_smin_3;
    TBranch * b_smaj_0;
    TBranch * b_smaj_1;
    TBranch * b_smaj_2;
    TBranch * b_smaj_3;
    TBranch * b_seedID_0;
    TBranch * b_seedID_1;
    TBranch * b_seedE_0;
    TBranch * b_seedE_1;
    TBranch * b_seedTOF_0;
    TBranch * b_seedTOF_1;

    //fInTree->SetBranchAddress("phoseedID_0",&seedID_0,&b_seedID_0);
    //fInTree->SetBranchAddress("phoseedID_1",&seedID_1,&b_seedID_1);
    //fInTree->SetBranchAddress("phoseedE_0",&seedE_0,&b_seedE_0);
    //fInTree->SetBranchAddress("phoseedE_1",&seedE_1,&b_seedE_1);
    //fInTree->SetBranchAddress("phoseedTOF_0",&seedTOF_0,&b_seedTOF_0);
    //fInTree->SetBranchAddress("phoseedTOF_1",&seedTOF_1,&b_seedTOF_1);

    //fInTree->SetBranchAddress("phoisOOT_0",&isOOT_0,&b_isOOT_0);
    //fInTree->SetBranchAddress("phoisOOT_1",&isOOT_1,&b_isOOT_1);
    //fInTree->SetBranchAddress("phoisOOT_2",&isOOT_2,&b_isOOT_2);
    //fInTree->SetBranchAddress("phoisOOT_3",&isOOT_3,&b_isOOT_3);
    //fInTree->SetBranchAddress("phosmin_0",&smin_0,&b_smin_0);
    //fInTree->SetBranchAddress("phosmin_1",&smin_1,&b_smin_1);
    //fInTree->SetBranchAddress("phosmin_2",&smin_2,&b_smin_2);
    //fInTree->SetBranchAddress("phosmin_3",&smin_3,&b_smin_3);
    //fInTree->SetBranchAddress("phosmaj_0",&smaj_0,&b_smaj_0);
    //fInTree->SetBranchAddress("phosmaj_1",&smaj_1,&b_smaj_1);
    //fInTree->SetBranchAddress("phosmaj_2",&smaj_2,&b_smaj_2);
    //fInTree->SetBranchAddress("phosmaj_3",&smaj_3,&b_smaj_3);
    fInTree->SetBranchAddress("out_npho_recHits_0",&npho_recHits_0,&b_npho_recHits_0);
    fInTree->SetBranchAddress("out_npho_recHits_1",&npho_recHits_1,&b_npho_recHits_1);
    fInTree->SetBranchAddress("out_npho_recHits_2",&npho_recHits_2,&b_npho_recHits_2);
    fInTree->SetBranchAddress("out_npho_recHits_3",&npho_recHits_3,&b_npho_recHits_3);
    fInTree->SetBranchAddress("out_fInRecHits_E",&fInRecHits_E,&b_fInRecHits_E);
    fInTree->SetBranchAddress("out_fInRecHits_ID",&fInRecHits_ID,&b_fInRecHits_ID);
    //fInTree->SetBranchAddress("out_fInRecHits_time",&fInRecHits_time,&b_fInRecHits_time);
    fInTree->SetBranchAddress("out_fInRecHits_TOF",&fInRecHits_TOF,&b_fInRecHits_TOF);
    fInTree->SetBranchAddress("out_kurhtime",&kurhtime,&b_kurhtime);
    fInTree->SetBranchAddress("out_kurhID",&kurhID,&b_kurhID);
    fInTree->SetBranchAddress("out_kuStcrhtime",&kuStcrhtime,&b_kuStcrhtime);
    //fInTree->SetBranchAddress("out_kuNotrhtime",&kuNotrhtime,&b_kuNotrhtime);
    fInTree->SetBranchAddress("out_kuNotStcrhtime",&kuNotStcrhtime,&b_kuNotStcrhtime);
    //fInTree->SetBranchAddress("out_kuWootStcrhtime",&kuWootStcrhtime,&b_kuWootStcrhtime);

    TH2F * IcMapEB[nAlgos][nIterations+1];
    TH2F * IcMapEP[nAlgos][nIterations+1];
    TH2F * IcMapEM[nAlgos][nIterations+1];

    string algostring[4] = { "RtStc", "RtOOTStc", "WtStc", "WtOOTStc" };
    IcMapEB[0][0] =  ebmapkue5;
    IcMapEP[0][0] =  ebmapkue5;
    IcMapEM[0][0] =  ebmapkue5;
    IcMapEB[1][0] =  ebmape5;
    IcMapEP[1][0] =  epmape5;
    IcMapEM[1][0] =  emmape5;
    for( auto i = 0; i < nAlgos; i++){
            for( auto j = 1; j < nIterations+1; j++ ){
		string hnameEB( "AveXtal"+algostring[i]+"PhoIcRecTimeEBMap_i"+to_string(j)); 
                string htitleEB( "AveXtal"+algostring[i]+"IcRecTimeEBMap EB "+to_string(j));
                IcMapEB[i][j] = new TH2F(hnameEB.c_str(),htitleEB.c_str(),171,-85.5,85.5,360,0.5,360.5);
                IcMapEB[i][j]->Sumw2();
                string hnameEP( "AveXtal"+algostring[i]+"PhoIcRecTimeEPMap_i"+to_string(j)); 
                string htitleEP( "AveXtal"+algostring[i]+"IcRecTimeEPMap EB "+to_string(j));
                IcMapEP[i][j] = new TH2F(hnameEP.c_str(),htitleEP.c_str(),100,0.5,100.5,100,0.5,100.5);
                IcMapEP[i][j]->Sumw2();
                string hnameEM( "AveXtal"+algostring[i]+"PhoIcRecTimeEMMap_i"+to_string(j)); 
                string htitleEM( "AveXtal"+algostring[i]+"IcRecTimeEBMap EM "+to_string(j));
                IcMapEM[i][j] = new TH2F(hnameEM.c_str(),htitleEM.c_str(),100,0.5,100.5,100,0.5,100.5);
                IcMapEM[i][j]->Sumw2();
             }
    }

    std::cout << "Setting up DetIDs." << std::endl;
    std::map<UInt_t,DetIDStruct> DetIDMap;
    SetupDetIDsEB( DetIDMap );
    SetupDetIDsEE( DetIDMap );

    // >> calcs  <<

    std::cout << "Starting entry and iterations loops "<< std::endl;
    const auto nEntries = fInTree->GetEntries();
    //const auto nEntries = 100;
    for( auto iter = 0; iter < nIterations; iter++){
    for (auto entry = 0U; entry < nEntries; entry++){
	if( entry%100000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries for " << iter << " of " << nIterations << " Iterations." << std::endl;

        b_npho_recHits_0->GetEntry(entry);
        b_npho_recHits_1->GetEntry(entry);
        //std::cout << "GetEntries rh for photons 0,1 Finished "<< std::endl;
        b_npho_recHits_2->GetEntry(entry);
        //std::cout << "GetEntries rh for photons 2 Finished "<< std::endl;
        b_npho_recHits_3->GetEntry(entry);
        //std::cout << "GetEntries rh for photons 3 Finished "<< std::endl;
        //b_seedID_0->GetEntry(entry);
        //b_seedID_1->GetEntry(entry);
        //b_seedE_0->GetEntry(entry);
        //b_seedE_1->GetEntry(entry);
        //std::cout << "GetEntries seed Finished "<< std::endl;
        //b_isOOT_0->GetEntry(entry);
        //b_isOOT_1->GetEntry(entry);
        //b_isOOT_2->GetEntry(entry);
        //b_isOOT_3->GetEntry(entry);
        //std::cout << "GetEntries isOOT Finished "<< std::endl;
        //b_smin_0->GetEntry(entry);
        //b_smin_1->GetEntry(entry);
        //b_smin_2->GetEntry(entry);
        //b_smin_3->GetEntry(entry);
        //b_smaj_0->GetEntry(entry);
        //b_smaj_1->GetEntry(entry);
        //b_smaj_2->GetEntry(entry);
        //b_smaj_3->GetEntry(entry);
        //std::cout << "GetEntries smin smaj Finished "<< std::endl;
        b_fInRecHits_E->GetEntry(entry);
        b_fInRecHits_ID->GetEntry(entry);
        //b_fInRecHits_time->GetEntry(entry);
        b_fInRecHits_TOF->GetEntry(entry);
        //std::cout << "GetEntries rh info Finished "<< std::endl;
        b_kurhtime->GetEntry(entry);
        b_kurhID->GetEntry(entry);
        b_kuStcrhtime->GetEntry(entry);
        //b_kuNotrhtime->GetEntry(entry);
        b_kuNotStcrhtime->GetEntry(entry);
        //b_kuWootStcrhtime->GetEntry(entry);
        //std::cout << "GetEntries kurh times Finished "<< std::endl;

	std::vector<Int_t> * cluster[nPhotons] = {npho_recHits_0,npho_recHits_1,npho_recHits_2,npho_recHits_3};
	//double cl_smin[nPhotons] = { smin_0, smin_1, smin_2, smin_3};
        //double cl_smaj[nPhotons] = { smaj_0, smaj_1, smaj_2, smaj_3};
        //bool cl_isOOT[nPhotons] = { isOOT_0, isOOT_1, isOOT_2, isOOT_3};

        //std::cout << "Looping over Photons "<< std::endl;
//        for (auto ipho = 0; ipho < nPhotons; ipho++){

             //auto & inpho = cluster[ipho];
    
             // skip OOT for now
             //inpho.b_isOOT->GetEntry(entry);
             //if (cl_isOOT[ipho]) continue;
    
             //inpho.b_smin->GetEntry(entry);
             //inpho.b_smaj->GetEntry(entry);
    
             //if (cl_smin[ipho] > 0.3) continue;
             //if (cl_smaj[ipho] > 0.5) continue;
    
             // get pair of rechits that are good candidates : double loop, yo
             // inpho.b_recHits->GetEntry(entry);

	     int ipho0 = 0;
	     int ipho1 = 1;    

             const auto nRecHits1 = (cluster[ipho0])->size();
             //std::cout << "Looping over first recHits"  << std::endl;
             for (auto i = 0U; i < nRecHits1; i++){
             //for (auto i = 0U; i < 1; i++){
		  double subM = 0.0;
                  double subsum = 0.0;
                  double subsumE = 0.0;
                  int subsumnum = 0;
                  double subMnot = 0.0;
                  double subsumnot = 0.0;
                  double subsumwoot = 0.0;
    
                  const auto rh_i = (*(cluster[ipho0]))[i]; // position within event rec hits vector
                  //const auto E_i  = seedE_0; //(*fInRecHits_E) [rh_i];
                  const auto E_i  = (*fInRecHits_E) [rh_i];
                  //const auto id_i = seedID_0; //(*fInRecHits_ID)[rh_i];
                  const auto id_i = (*fInRecHits_ID)[rh_i];
                  //const auto t_i = seedtime_0; //(*fInRecHits_time)[rh_i];
                  //const auto t_i = (*fInRecHits_time)[rh_i];
                  //const auto tof_i = seedTOF_0; //(*fInRecHits_TOF)[rh_i];
                  const auto tof_i = (*fInRecHits_TOF)[rh_i];
                  auto RtStc_t_i = 0.0;
                  auto RtOOTStc_t_i = 0.0;
                  auto WtOOTStc_t_i = 0.0;
		  double prev_i[nAlgos] = {0.0};   			

                  //std::cout << "Getting KU times " << std::endl;
		  if( E_i < ri_ecut ) continue;
                  for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                          if( (*kurhID)[kuseed] == id_i ){
                                  RtStc_t_i = (*kuStcrhtime)[kuseed];
                                  RtOOTStc_t_i = (*kuNotStcrhtime)[kuseed];
         //                         WtOOTStc_t_i = (*kuWootStcrhtime)[kuseed];
                                  break;
                          }
    
                  }
		  //std::cout << "Getting maps " << std::endl;
                  RtStc_t_i += tof_i;
                  RtOOTStc_t_i += tof_i;
                  // WtOOTStc_t_i += tof_i;
                  const auto & id_i_info = DetIDMap[id_i];
	          double mfcor = 1.0;
		  if( iter == 0 ) mfcor = mfcorrection;
                  for( auto a = 0; a < nAlgos; a++ ){
                          if( id_i_info.ecal == ECAL::EB ){
                                  prev_i[a] = (((IcMapEB[a][iter])->GetBinContent( id_i_info.i2 + bin_offset, id_i_info.i1))/mfcor) - offset;  //  
//				  //std::cout << "For EB a = " << a << " prev_i[a] = " << prev_i[a]  << " at " << id_i_info.i2 << " " << id_i_info.i1  << std::endl;
                          } else if( id_i_info.ecal == ECAL::EP ){
                                  prev_i[a] = (((IcMapEP[a][iter])->GetBinContent( id_i_info.i2, id_i_info.i1))/mfcor) - offset;  //  
 ///                                //std::cout << "For EP a = " << a << " prev_i[a] = " << prev_i[a]  << " at " << id_i_info.i2 << " " << id_i_info.i1  << std::endl;
                          } else if( id_i_info.ecal == ECAL::EM ){
                                  prev_i[a] = (((IcMapEM[a][iter])->GetBinContent( id_i_info.i2, id_i_info.i1))/mfcor) - offset;  //  
   //                               //std::cout << "For EM a = " << a << " prev_i[a] = " << prev_i[a]  << " at " << id_i_info.i2 << " " << id_i_info.i1  << std::endl;
                          }
                  }
                  //std::cout << "Looping over second recHits" << std::endl;
                  const auto nRecHits2 = (cluster[ipho1])->size();
                  for (auto j = 0U; j < nRecHits2; j++){
                  //for (auto j = 0U; j < 1; j++){

			//if( i == j ) continue;
			//std::cout << "Getting cluster info" << std::endl;
                        const auto rh_j = (*(cluster[ipho1]))[j]; // position within event rec hits vector
                        //const auto E_j  = seedE_1; //(*fInRecHits_E) [rh_j];
                        const auto E_j  = (*fInRecHits_E) [rh_j];
                        //const auto id_j = seedID_1; //(*fInRecHits_ID)[rh_j];
                        const auto id_j = (*fInRecHits_ID)[rh_j];
                        auto RtStc_t_j = 0.0;
                        auto RtOOTStc_t_j = 0.0;
                        auto WtOOTStc_t_j = 0.0;
                        //const auto tof_j = seedTOF_1; //(*fInRecHits_TOF)[rh_j];
                        const auto tof_j = (*fInRecHits_TOF)[rh_j];
                        double prev_j[nAlgos] = {0.0};
		        if( E_j < rj_ecut ) continue;
			//std::cout << "Getting ku time info" << std::endl;
                        for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                                if( (*kurhID)[kuseed] == id_j ){
                                        RtStc_t_j = (*kuStcrhtime)[kuseed];
                                        RtOOTStc_t_j = (*kuNotStcrhtime)[kuseed];
         //                               WtOOTStc_t_j = (*kuWootStcrhtime)[kuseed];
                                        break;
                                }
                        }

                        RtStc_t_j += tof_j;
                        RtOOTStc_t_j += tof_j;
                        //WtOOTStc_t_j += tof_j;
                        const auto & id_j_info = DetIDMap[id_j];
                  	double mfcor = 1.0;
                  	if( iter == 0 ) mfcor = mfcorrection;
			for( auto a = 0; a < nAlgos; a++ ){
              			if( id_j_info.ecal == ECAL::EB ){
                      			prev_j[a] = (((IcMapEB[a][iter])->GetBinContent( id_j_info.i2 + bin_offset, id_j_info.i1))/mfcor) - offset;  // 
              			} else if( id_j_info.ecal == ECAL::EP ){
                                        prev_j[a] = (IcMapEP[a][iter])->GetBinContent( id_j_info.i2, id_j_info.i1) - offset;  //  
              			} else if( id_j_info.ecal == ECAL::EM ){
                                        prev_j[a] = (IcMapEM[a][iter])->GetBinContent( id_j_info.i2, id_j_info.i1) - offset;  //  
              			}
			}

//			auto tmpsum1 = RtStc_t_i - prev_i[0] - RtStc_t_j + prev_j[0];
			//subM += (tmpsum1 * tmpsum1);
			//(RtStc_t_i - prev_i[0] - RtStc_t_j + prev_j[0])*(RtStc_t_i - prev_i[0] - RtStc_t_j + prev_j[0]));
                        //subsum += (tmpsum1 + prev_i[0]); 
                        subsum += E_j*(RtStc_t_j - prev_j[0]);
			//auto tmpsum2 = RtOOTStc_t_i - prev_i[1] - RtOOTStc_t_j + prev_j[1];
                        //subMnot += (tmpsum2 * tmpsum2);
			//(RtOOTStc_t_i - prev_i[1] - RtOOTStc_t_j + prev_j[1])*(RtOOTStc_t_i - prev_i[1] - RtOOTStc_t_j + prev_j[1]));
                        //subsumnot += (tmpsum2 + prev_i[1]);
                        subsumnot += E_j*(RtOOTStc_t_j - prev_j[1]);
                        //subsumwoot += (WtOOTStc_t_i - WtOOTStc_t_j ); //+ prev[2]);
                        subsumE += E_j;
                        subsumnum += 1;

                  } // end inner double loop over rechit
    //            >>>>  do subsums
                  if( subsumnum == 0. ) continue;
                  auto tot = ( RtStc_t_i - prev_i[0] - (subsum/subsumE) );
                  auto totnot = ( RtOOTStc_t_i - prev_i[1] - (subsumnot/subsumE) );
	          M[iter] += tot*tot;
		  Mnot[iter] += totnot*totnot;
		  nM[iter] += 1;
		  //normRtStc += subsum;
                  //normRtOOTStc += subsumnot;
                  //normWtOOTStc += subsumwoot;
                  sumXtalRtStcPhoIcRecTime[id_i] += (tot + prev_i[0]); //(subsum/subsumnum);
                  sumXtalRtOOTStcPhoIcRecTime[id_i] += (totnot + prev_i[1]); //(subsumnot/subsumnum);
                  //sumXtalWtOOTStcPhoIcRecTime[id_i] += subsumwoot; //(subsumwoot/subsumnum);
                  numXtalIcRecTime[id_i] += 1; //1;
             } // end outer double loop over rechits
             //std::cout << "RecHits Loop done "<< std::endl;
 //       } // end loop over photons
        //std::cout << "Photon Loop done "<< std::endl;
   

 
    }  //  end entry loop

    //double  norm[nAlgos] = { normRtStc, normRtOOTStc };
    std::map<UInt_t,Float_t> *  icmaps[nAlgos] = {&sumXtalRtStcPhoIcRecTime, &sumXtalRtOOTStcPhoIcRecTime }; //, sumXtalWtOOTStcPhoIcRecTime };

    for( auto ai = 0; ai < nAlgos; ai++ ){
	 double drift = 0.0;
	 for( std::map<UInt_t,Float_t>::iterator it=(*icmaps[ai]).begin(); it!=(*icmaps[ai]).end(); ++it){ drift += (((*icmaps[ai])[it->first])/(numXtalIcRecTime[it->first])); }
         for( std::map<UInt_t,Float_t>::iterator it=(*icmaps[ai]).begin(); it!=(*icmaps[ai]).end(); ++it){
                   const auto & fill_idinfo = DetIDMap[it->first];
                   const auto & map_time = (((*icmaps[ai])[it->first])/(numXtalIcRecTime[it->first]) - (drift/(icmaps[ai]->size()))) + offset;
		   //std::cout << "Fill hist for Algo " << i << " at " << fill_idinfo.i2 << " " << fill_idinfo.i1 << " with " << map_time << " for iter " << iter << std::endl;
                   if( fill_idinfo.ecal == ECAL::EB ){
//		   std::cout << "Fill EB hist for Algo " << ai << " at " << fill_idinfo.i2 << " " << fill_idinfo.i1 << " with " << map_time << " for iter " << iter << std::endl;
                           (IcMapEB[ai][iter+1])->Fill( fill_idinfo.i2, fill_idinfo.i1, map_time );
                   } else if( fill_idinfo.ecal == ECAL::EP ){
//                 std::cout << "Fill EP hist for Algo " << ai << " at " << fill_idinfo.i2 << " " << fill_idinfo.i1 << " with " << map_time << " for iter " << iter << std::endl;
                           (IcMapEP[ai][iter+1])->Fill( fill_idinfo.i2, fill_idinfo.i1, map_time );
                   } else if( fill_idinfo.ecal == ECAL::EM ){
//                 std::cout << "Fill EM hist for Algo " << ai << " at " << fill_idinfo.i2 << " " << fill_idinfo.i1 << " with " << map_time << " for iter " << iter << std::endl;
                           (IcMapEM[ai][iter+1])->Fill( fill_idinfo.i2, fill_idinfo.i1, map_time );
                   }
         }
    }

    std::cout << "For iter " << iter << " found: " << M[iter]/nM[iter] << std::endl;
    //normRtStc = 0.0;
    //normRtOOTStc = 0.0;
    //normWtOOTStc = 0.0;
    sumXtalRtStcPhoIcRecTime.clear();
    sumXtalRtOOTStcPhoIcRecTime.clear();
    sumXtalWtOOTStcPhoIcRecTime.clear();
    numXtalIcRecTime.clear();

    }  //  end iteration loop
    std::cout << " End of Interation Loops " << std::endl;

    std::cout << "Fill M hists  ( M vs iter )" << std::endl;
    for( auto  iter = 0; iter < nIterations; iter++){  
	std::cout << "For iter " << iter << " filling " << M[iter]/nM[iter] << " for " << M[iter] << " / " << nM[iter] << std::endl;
	MHist->Fill( iter, M[iter]/nM[iter] );
 	MnotHist->Fill( iter, Mnot[iter]/nM[iter] );
    }

    TFile* fOutFile = new TFile( outfilename.c_str(), "RECREATE" );
    fOutFile->cd();

    std::cout << "Write IcMaps" << std::endl;
    //fInFile->cd();
    for( auto i = 0; i < nAlgos; i++){
	    for( auto j = 1; j < nIterations+1; j++ ){
		IcMapEB[i][j]->Write();
        	IcMapEP[i][j]->Write();
        	IcMapEM[i][j]->Write();
    	     } 
    }

    std::cout << "Write M hists  ( M vs iter )" << std::endl;
    MHist->Write();
    MnotHist->Write();

    //fInTree->Write(); 
}

int main ( int argc, char *argv[] ){

        if( argc != 4 ) { std::cout << "Insufficent arguments." << std::endl; }
        else {
                auto infilename = argv[1];
                auto outfilename = argv[2];
                auto mfc = atoi(argv[3]);
                wc_ku_InterCali_global_v2( infilename, outfilename, mfc );
        }
        return 1;
}

