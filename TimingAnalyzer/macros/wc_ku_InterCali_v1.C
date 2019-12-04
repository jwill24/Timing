#include "Skimmer.hh"
#include "Common.cpp+"
#include "TROOT.h"

#include <iostream>

void wc_ku_InterCali_v1( string infilename ){

    const int  nIterations = 25;
    const int  nAlgos = 2; // RtStc, RtOOTStc //, WtOOTStc
    const int  nPhotons = 4;
    const float offset = 100.0;
    const int bin_offset = 86;

    float M[nIterations] = {0.f};
    float Mnot[nIterations] = {0.f};
    float Mwoot[nIterations] = {0.f};
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
    //float normRtStc = 0.f;
    //float normRtOOTStc = 0.f;
    //float normWtOOTStc = 0.f;

    bool isOOT_0;
    bool isOOT_1;
    bool isOOT_2;
    bool isOOT_3;
    float smin_0;
    float smin_1;
    float smin_2;
    float smin_3;
    float smaj_0;
    float smaj_1;
    float smaj_2;
    float smaj_3;

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

    fInTree->SetBranchAddress("phoisOOT_0",&isOOT_0,&b_isOOT_0);
    fInTree->SetBranchAddress("phoisOOT_1",&isOOT_1,&b_isOOT_1);
    fInTree->SetBranchAddress("phoisOOT_2",&isOOT_2,&b_isOOT_2);
    fInTree->SetBranchAddress("phoisOOT_3",&isOOT_3,&b_isOOT_3);
    fInTree->SetBranchAddress("phosmin_0",&smin_0,&b_smin_0);
    fInTree->SetBranchAddress("phosmin_1",&smin_1,&b_smin_1);
    fInTree->SetBranchAddress("phosmin_2",&smin_2,&b_smin_2);
    fInTree->SetBranchAddress("phosmin_3",&smin_3,&b_smin_3);
    fInTree->SetBranchAddress("phosmaj_0",&smaj_0,&b_smaj_0);
    fInTree->SetBranchAddress("phosmaj_1",&smaj_1,&b_smaj_1);
    fInTree->SetBranchAddress("phosmaj_2",&smaj_2,&b_smaj_2);
    fInTree->SetBranchAddress("phosmaj_3",&smaj_3,&b_smaj_3);
    fInTree->SetBranchAddress("out_npho_recHits_0",&npho_recHits_0,&b_npho_recHits_0);
    fInTree->SetBranchAddress("out_npho_recHits_1",&npho_recHits_1,&b_npho_recHits_1);
    fInTree->SetBranchAddress("out_npho_recHits_2",&npho_recHits_2,&b_npho_recHits_2);
    fInTree->SetBranchAddress("out_npho_recHits_3",&npho_recHits_3,&b_npho_recHits_3);
    fInTree->SetBranchAddress("out_fInRecHits_E",&fInRecHits_E,&b_fInRecHits_E);
    fInTree->SetBranchAddress("out_fInRecHits_ID",&fInRecHits_ID,&b_fInRecHits_ID);
    fInTree->SetBranchAddress("out_fInRecHits_time",&fInRecHits_time,&b_fInRecHits_time);
    fInTree->SetBranchAddress("out_fInRecHits_TOF",&fInRecHits_TOF,&b_fInRecHits_TOF);
    fInTree->SetBranchAddress("out_kurhtime",&kurhtime,&b_kurhtime);
    fInTree->SetBranchAddress("out_kurhID",&kurhID,&b_kurhID);
    fInTree->SetBranchAddress("out_kuStcrhtime",&kuStcrhtime,&b_kuStcrhtime);
    fInTree->SetBranchAddress("out_kuNotrhtime",&kuNotrhtime,&b_kuNotrhtime);
    fInTree->SetBranchAddress("out_kuNotStcrhtime",&kuNotStcrhtime,&b_kuNotStcrhtime);
    //fInTree->SetBranchAddress("out_kuWootStcrhtime",&kuWootStcrhtime,&b_kuWootStcrhtime);

    TH2F * IcMapEB[nAlgos][nIterations+1];
    TH2F * IcMapEP[nAlgos][nIterations+1];
    TH2F * IcMapEM[nAlgos][nIterations+1];

    string algostring[nAlgos] = { "RtStc", "RtOOTStc" }; // "WtOOTStc" };
    IcMapEB[0][0] =  ebmapkue5;
    IcMapEP[0][0] =  ebmapkue5;
    IcMapEM[0][0] =  ebmapkue5;
    IcMapEB[1][0] =  ebmapic;
    IcMapEP[1][0] =  epmapcl;
    IcMapEM[1][0] =  emmapcl;
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

    Common::SetupDetIDs();

    // >> calcs  <<

    const auto nEntries = fInTree->GetEntries();
    //const auto nEntries = 10000;
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
        b_isOOT_0->GetEntry(entry);
        b_isOOT_1->GetEntry(entry);
        b_isOOT_2->GetEntry(entry);
        b_isOOT_3->GetEntry(entry);
        //std::cout << "GetEntries isOOT Finished "<< std::endl;
        b_smin_0->GetEntry(entry);
        b_smin_1->GetEntry(entry);
        b_smin_2->GetEntry(entry);
        b_smin_3->GetEntry(entry);
        b_smaj_0->GetEntry(entry);
        b_smaj_1->GetEntry(entry);
        b_smaj_2->GetEntry(entry);
        b_smaj_3->GetEntry(entry);
        //std::cout << "GetEntries smin smaj Finished "<< std::endl;
        b_fInRecHits_E->GetEntry(entry);
        b_fInRecHits_ID->GetEntry(entry);
        b_fInRecHits_time->GetEntry(entry);
        b_fInRecHits_TOF->GetEntry(entry);
        //std::cout << "GetEntries rh info Finished "<< std::endl;
        b_kurhtime->GetEntry(entry);
        b_kurhID->GetEntry(entry);
        b_kuStcrhtime->GetEntry(entry);
        b_kuNotrhtime->GetEntry(entry);
        b_kuNotStcrhtime->GetEntry(entry);
        //b_kuWootStcrhtime->GetEntry(entry);
        //std::cout << "GetEntries kurh times Finished "<< std::endl;

	std::vector<Int_t> * cluster[nPhotons] = {npho_recHits_0,npho_recHits_1,npho_recHits_2,npho_recHits_3};
	float cl_smin[nPhotons] = { smin_0, smin_1, smin_2, smin_3};
        float cl_smaj[nPhotons] = { smaj_0, smaj_1, smaj_2, smaj_3};
        bool cl_isOOT[nPhotons] = { isOOT_0, isOOT_1, isOOT_2, isOOT_3};

        //std::cout << "Looping over Photons "<< std::endl;
        for (auto ipho = 0; ipho < nPhotons; ipho++){

             //auto & inpho = cluster[ipho];
    
             // skip OOT for now
             //inpho.b_isOOT->GetEntry(entry);
             if (cl_isOOT[ipho]) continue;
    
             //inpho.b_smin->GetEntry(entry);
             //inpho.b_smaj->GetEntry(entry);
    
             if (cl_smin[ipho] > 0.3) continue;
             if (cl_smaj[ipho] > 0.5) continue;
    
             // get pair of rechits that are good candidates : double loop, yo
             // inpho.b_recHits->GetEntry(entry);
    
             const auto nRecHits = (cluster[ipho])->size();
             //std::cout << "Looping over recHits n = " << n << std::endl;
             for (auto i = 0U; i < nRecHits; i++){
		  float subM = 0.f;
                  float subsum = 0.f;
                  int subsumnum = 0;
                  float subMnot = 0.f;
                  float subsumnot = 0.f;
                  float subsumwoot = 0.f;
    
                  const auto rh_i = (*(cluster[ipho]))[i]; // position within event rec hits vector
                  const auto E_i  = (*fInRecHits_E) [rh_i];
                  const auto id_i = (*fInRecHits_ID)[rh_i];
                  const auto t_i = (*fInRecHits_time)[rh_i];
                  const auto tof_i = (*fInRecHits_TOF)[rh_i];
                  auto RtStc_t_i = 0.f;
                  auto RtOOTStc_t_i = 0.f;
                  auto WtOOTStc_t_i = 0.f;
		  float prev_i[nAlgos] = {0.f};   			

		  if( E_i < 5.0 ) continue;
                  for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                          if( (*kurhID)[kuseed] == id_i ){
                                  RtStc_t_i = (*kuStcrhtime)[kuseed];
                                  RtOOTStc_t_i = (*kuNotStcrhtime)[kuseed];
         //                         WtOOTStc_t_i = (*kuWootStcrhtime)[kuseed];
                                  break;
                          }
    
                  }

                  RtStc_t_i += tof_i;
                  RtOOTStc_t_i += tof_i;
                 // WtOOTStc_t_i += tof_i;
                  const auto & id_i_info = Common::DetIDMap[id_i];
                  for( auto a = 0; a < nAlgos; a++ ){
                          if( id_i_info.ecal == ECAL::EB ){
                                  prev_i[a] = (IcMapEB[a][iter])->GetBinContent( id_i_info.i2 + bin_offset, id_i_info.i1) - offset;  //  
//				  std::cout << "For EB a = " << a << " prev_i[a] = " << prev_i[a]  << " at " << id_i_info.i2 << " " << id_i_info.i1  << std::endl;
                          } else if( id_i_info.ecal == ECAL::EP ){
                                  prev_i[a] = (IcMapEP[a][iter])->GetBinContent( id_i_info.i2, id_i_info.i1) - offset;  //  
 ///                                std::cout << "For EP a = " << a << " prev_i[a] = " << prev_i[a]  << " at " << id_i_info.i2 << " " << id_i_info.i1  << std::endl;
                          } else if( id_i_info.ecal == ECAL::EM ){
                                  prev_i[a] = (IcMapEM[a][iter])->GetBinContent( id_i_info.i2, id_i_info.i1) - offset;  //  
   //                               std::cout << "For EM a = " << a << " prev_i[a] = " << prev_i[a]  << " at " << id_i_info.i2 << " " << id_i_info.i1  << std::endl;
                          }
                  }
                  for (auto j = 0U; j < nRecHits; j++){

			if( i == j ) continue;

                        const auto rh_j = (*(cluster[ipho]))[j]; // position within event rec hits vector
                        const auto E_j  = (*fInRecHits_E) [rh_j];
                        const auto id_j = (*fInRecHits_ID)[rh_j];
                        auto RtStc_t_j = 0.f;
                        auto RtOOTStc_t_j = 0.f;
                        auto WtOOTStc_t_j = 0.f;
                        const auto tof_j = (*fInRecHits_TOF)[rh_j];
                        float prev_j[nAlgos] = {0.f};
		        if( E_j < 3.0 ) continue;
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
                        const auto & id_j_info = Common::DetIDMap[id_j];
			for( auto a = 0; a < nAlgos; a++ ){
              			if( id_j_info.ecal == ECAL::EB ){
                      			prev_j[a] = (IcMapEB[a][iter])->GetBinContent( id_j_info.i2 + bin_offset, id_j_info.i1) - offset;  //  
              			} else if( id_j_info.ecal == ECAL::EP ){
                                        prev_j[a] = (IcMapEP[a][iter])->GetBinContent( id_j_info.i2, id_j_info.i1) - offset;  //  
              			} else if( id_j_info.ecal == ECAL::EM ){
                                        prev_j[a] = (IcMapEM[a][iter])->GetBinContent( id_j_info.i2, id_j_info.i1) - offset;  //  
              			}
			}

			auto tmpsum1 = RtStc_t_i - prev_i[0] - RtStc_t_j + prev_j[0];
			subM += (tmpsum1 * tmpsum1);
			//(RtStc_t_i - prev_i[0] - RtStc_t_j + prev_j[0])*(RtStc_t_i - prev_i[0] - RtStc_t_j + prev_j[0]));
                        subsum += (tmpsum1 + prev_i[0]); 
			auto tmpsum2 = RtOOTStc_t_i - prev_i[1] - RtOOTStc_t_j + prev_j[1];
                        subMnot += (tmpsum2 * tmpsum2);
			//(RtOOTStc_t_i - prev_i[1] - RtOOTStc_t_j + prev_j[1])*(RtOOTStc_t_i - prev_i[1] - RtOOTStc_t_j + prev_j[1]));
                        subsumnot += (tmpsum2 + prev_i[1]);
                        //subsumwoot += (WtOOTStc_t_i - WtOOTStc_t_j ); //+ prev[2]);
                        subsumnum += 1;

                  } // end inner double loop over rechit
    //            >>>>  do subsums
                  if( subsumnum == 0. ) continue;
	          M[iter] += subM;
		  Mnot[iter] += subMnot;
		  nM[iter] += subsumnum;
		  //normRtStc += subsum;
                  //normRtOOTStc += subsumnot;
                  //normWtOOTStc += subsumwoot;
                  sumXtalRtStcPhoIcRecTime[id_i] += subsum; //(subsum/subsumnum);
                  sumXtalRtOOTStcPhoIcRecTime[id_i] += subsumnot; //(subsumnot/subsumnum);
                  //sumXtalWtOOTStcPhoIcRecTime[id_i] += subsumwoot; //(subsumwoot/subsumnum);
                  numXtalIcRecTime[id_i] += subsumnum; //1;
             } // end outer double loop over rechits
             //std::cout << "RecHits Loop done "<< std::endl;
        } // end loop over photons
        //std::cout << "Photon Loop done "<< std::endl;
   

 
    }  //  end entry loop

    //float  norm[nAlgos] = { normRtStc, normRtOOTStc };
    std::map<UInt_t,Float_t> *  icmaps[nAlgos] = {&sumXtalRtStcPhoIcRecTime, &sumXtalRtOOTStcPhoIcRecTime }; //, sumXtalWtOOTStcPhoIcRecTime };

    for( auto ai = 0; ai < nAlgos; ai++ ){
	 float drift = 0.f;
	 for( std::map<UInt_t,Float_t>::iterator it=(*icmaps[ai]).begin(); it!=(*icmaps[ai]).end(); ++it){ drift += (((*icmaps[ai])[it->first])/(numXtalIcRecTime[it->first])); }
         for( std::map<UInt_t,Float_t>::iterator it=(*icmaps[ai]).begin(); it!=(*icmaps[ai]).end(); ++it){
                   const auto & fill_idinfo = Common::DetIDMap[it->first];
                   const auto & map_time = ((*icmaps[ai])[it->first])/(numXtalIcRecTime[it->first]) + offset - (drift/(icmaps[ai]->size()));
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

    //normRtStc = 0.f;
    //normRtOOTStc = 0.f;
    //normWtOOTStc = 0.f;
    sumXtalRtStcPhoIcRecTime.clear();
    sumXtalRtOOTStcPhoIcRecTime.clear();
    sumXtalWtOOTStcPhoIcRecTime.clear();
    numXtalIcRecTime.clear();

    }  //  end iteration loop
    //std::cout << " End of Interation Loops " << std::endl;

    std::cout << "Fill M hists  ( M vs iter )" << std::endl;
    for( auto  iter = 0; iter < nIterations; iter++){  
	std::cout << "For iter " << iter+1 << " filling " << M[iter]/nM[iter] << " for " << M[iter] << " / " << nM[iter] << std::endl;
	MHist->Fill( iter, M[iter]/nM[iter] );
 	MnotHist->Fill( iter, Mnot[iter]/nM[iter] );
    }

    std::cout << "Write IcMaps" << std::endl;
    fInFile->cd();
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
