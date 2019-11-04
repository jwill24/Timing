#include "Skimmer.hh"
#include "TROOT.h"

#include <iostream>

void wc_ku_Cali( string infilename, string outfilename ){

    string disphotreename("disphotree");

    auto fInFile = TFile::Open(infilename.c_str(), "update");
    auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());
    
    double phoseedtimeCaliE0_0;
    double phoseedtimeCaliE0_1;
    double phoseedtimeCaliE1_0;
    double phoseedtimeCaliE1_1;

    double phoseedtimeCali2E1_0;
    double phoseedtimeCali2E1_1;
    double phoseedtimeCali4E1_0;
    double phoseedtimeCali4E1_1;

    double phoseedtimeCaliE2_0;
    double phoseedtimeCaliE2_1;
    double phoseedtimeCaliE5_0;
    double phoseedtimeCaliE5_1;

    double phoseedtimeCali2E5_0;
    double phoseedtimeCali2E5_1;
    double phoseedtimeCali4E5_0;
    double phoseedtimeCali4E5_1;

    double phoseedtimeCaliE10_0;
    double phoseedtimeCaliE10_1;

    double phoseedtimeCaliCl_0;
    double phoseedtimeCaliCl_1;

    double phoseedtimeCaliIc_0;
    double phoseedtimeCaliIc_1;

    Int_t   phoseedI1_0; // EB: iphi, EE: ix
    Int_t   phoseedI2_0; // EB: ieta, EE: iy
    Int_t    phoseedEcal_0; // EB, EM, EP
  
    TBranch * b_phoseedI1_0;
    TBranch * b_phoseedI2_0;
    TBranch * b_phoseedEcal_0;
  
    Int_t   phoseedI1_1; // EB: iphi, EE: ix
    Int_t   phoseedI2_1; // EB: ieta, EE: iy
    Int_t    phoseedEcal_1; // EB, EM, EP
  
    TBranch * b_phoseedI1_1;
    TBranch * b_phoseedI2_1;
    TBranch * b_phoseedEcal_1;

    
    fInTree->SetBranchAddress("phoseedI1_0", &phoseedI1_0, &b_phoseedI1_0);
    fInTree->SetBranchAddress("phoseedI2_0", &phoseedI2_0, &b_phoseedI2_0);
    fInTree->SetBranchAddress("phoseedEcal_0", &phoseedEcal_0, &b_phoseedEcal_0);
    fInTree->SetBranchAddress("phoseedI1_1", &phoseedI1_1, &b_phoseedI1_1);
    fInTree->SetBranchAddress("phoseedI2_1", &phoseedI2_1, &b_phoseedI2_1);
    fInTree->SetBranchAddress("phoseedEcal_1", &phoseedEcal_1, &b_phoseedEcal_1);

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

    TFile* fOutFile = new TFile( outfilename.c_str(), "RECREATE" );
    fOutFile->cd();  
    auto fOutTree = fInTree->CloneTree();
    //TTree* fOutTree = new TTree(   
    //auto fOutTree = fInTree;
    //auto fOutFile = fInFile;

    auto b_phoseedtimeCaliE0_0 = fOutTree->Branch("phoseedtimeCaliE0_0",&phoseedtimeCaliE0_0);
    auto b_phoseedtimeCaliE0_1 = fOutTree->Branch("phoseedtimeCaliE0_1",&phoseedtimeCaliE0_1);
    auto b_phoseedtimeCaliE1_0 = fOutTree->Branch("phoseedtimeCaliE1_0",&phoseedtimeCaliE1_0);
    auto b_phoseedtimeCaliE1_1 = fOutTree->Branch("phoseedtimeCaliE1_1",&phoseedtimeCaliE1_1);
    auto b_phoseedtimeCali2E1_0 = fOutTree->Branch("phoseedtimeCali2E1_0",&phoseedtimeCali2E1_0);
    auto b_phoseedtimeCali2E1_1 = fOutTree->Branch("phoseedtimeCali2E1_1",&phoseedtimeCali2E1_1);
    auto b_phoseedtimeCali4E1_0 = fOutTree->Branch("phoseedtimeCali4E1_0",&phoseedtimeCali4E1_0);
    auto b_phoseedtimeCali4E1_1 = fOutTree->Branch("phoseedtimeCali4E1_1",&phoseedtimeCali4E1_1);
    auto b_phoseedtimeCaliE2_0 = fOutTree->Branch("phoseedtimeCaliE2_0",&phoseedtimeCaliE2_0);
    auto b_phoseedtimeCaliE2_1 = fOutTree->Branch("phoseedtimeCaliE2_1",&phoseedtimeCaliE2_1);
    auto b_phoseedtimeCaliE5_0 = fOutTree->Branch("phoseedtimeCaliE5_0",&phoseedtimeCaliE5_0);
    auto b_phoseedtimeCaliE5_1 = fOutTree->Branch("phoseedtimeCaliE5_1",&phoseedtimeCaliE5_1);
    auto b_phoseedtimeCali2E5_0 = fOutTree->Branch("phoseedtimeCali2E5_0",&phoseedtimeCali2E5_0);
    auto b_phoseedtimeCali2E5_1 = fOutTree->Branch("phoseedtimeCali2E5_1",&phoseedtimeCali2E5_1);
    auto b_phoseedtimeCali4E5_0 = fOutTree->Branch("phoseedtimeCali4E5_0",&phoseedtimeCali4E5_0);
    auto b_phoseedtimeCali4E5_1 = fOutTree->Branch("phoseedtimeCali4E5_1",&phoseedtimeCali4E5_1);
    auto b_phoseedtimeCaliE10_0 = fOutTree->Branch("phoseedtimeCaliE10_0",&phoseedtimeCaliE10_0);
    auto b_phoseedtimeCaliE10_1 = fOutTree->Branch("phoseedtimeCaliE10_1",&phoseedtimeCaliE10_1);

    auto b_phoseedtimeCaliCl_0 = fOutTree->Branch("phoseedtimeCaliCl_0",&phoseedtimeCaliCl_0);
    auto b_phoseedtimeCaliCl_1 = fOutTree->Branch("phoseedtimeCaliCl_1",&phoseedtimeCaliCl_1);

    auto b_phoseedtimeCaliIc_0 = fOutTree->Branch("phoseedtimeCaliIc_0",&phoseedtimeCaliIc_0);
    auto b_phoseedtimeCaliIc_1 = fOutTree->Branch("phoseedtimeCaliIc_1",&phoseedtimeCaliIc_1);

    b_phoseedtimeCaliE0_0->SetFile(outfilename.c_str());
    b_phoseedtimeCaliE0_1->SetFile(outfilename.c_str());
    b_phoseedtimeCaliE1_0->SetFile(outfilename.c_str());
    b_phoseedtimeCaliE1_1->SetFile(outfilename.c_str());
    b_phoseedtimeCali2E1_0->SetFile(outfilename.c_str());
    b_phoseedtimeCali2E1_1->SetFile(outfilename.c_str());
    b_phoseedtimeCali4E1_0->SetFile(outfilename.c_str());
    b_phoseedtimeCali4E1_1->SetFile(outfilename.c_str());
    b_phoseedtimeCaliE2_0->SetFile(outfilename.c_str());
    b_phoseedtimeCaliE2_1->SetFile(outfilename.c_str());
    b_phoseedtimeCaliE5_0->SetFile(outfilename.c_str());
    b_phoseedtimeCaliE5_1->SetFile(outfilename.c_str());
    b_phoseedtimeCali2E5_0->SetFile(outfilename.c_str());
    b_phoseedtimeCali2E5_1->SetFile(outfilename.c_str());
    b_phoseedtimeCali4E5_0->SetFile(outfilename.c_str());
    b_phoseedtimeCali4E5_1->SetFile(outfilename.c_str());
    b_phoseedtimeCaliE10_0->SetFile(outfilename.c_str());
    b_phoseedtimeCaliE10_1->SetFile(outfilename.c_str());

    b_phoseedtimeCaliCl_0->SetFile(outfilename.c_str());
    b_phoseedtimeCaliCl_1->SetFile(outfilename.c_str());

    b_phoseedtimeCaliIc_0->SetFile(outfilename.c_str());
    b_phoseedtimeCaliIc_1->SetFile(outfilename.c_str());

    // >> calcs  <<

    const auto nEntries = fInTree->GetEntries();
    for (auto entry = 0U; entry < nEntries; entry++){
       // if( entry%int(nEntries*0.1) == 0 ) std::cout << "Proccessed " << entry/nEntries << "\% of " << nEntries << " entries." << std::endl;
	if( entry%100000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries." << std::endl;        

        b_phoseedI1_0->GetEntry(entry);
	b_phoseedI2_0->GetEntry(entry);	
	b_phoseedEcal_0->GetEntry(entry);

        b_phoseedI1_1->GetEntry(entry);
        b_phoseedI2_1->GetEntry(entry);
        b_phoseedEcal_1->GetEntry(entry);

	int bin_offset = 86;
	int adjust = 100.0;

    	if ( phoseedEcal_0 == ECAL::EB ){
    		phoseedtimeCaliE0_0 = ebmape0->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE1_0 = ebmape1->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCali2E1_0 = ebmap2e1->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCali4E1_0 = ebmap4e1->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE2_0 = ebmape2->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE5_0 = ebmape5->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCali2E5_0 = ebmap2e5->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCali4E5_0 = ebmap4e5->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE10_0 = ebmape10->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCaliCl_0 = ebmapcl->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
                phoseedtimeCaliIc_0 = ebmapic->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
		//if( phoseedtimeCaliCl_0 > 1.0 ){
		//	std::cout << "Filling EB 0 with " << phoseedI2_0 << " by " << phoseedI1_0 << " : " << phoseedtimeCaliE0_0 << " and " << phoseedtimeCaliIc_0;
		//	std::cout << phoseedtimeCaliE1_0 << phoseedtimeCaliE2_0 << phoseedtimeCaliE5_0 << phoseedtimeCaliE10_0 << phoseedtimeCaliCl_0 << std::endl;
		//}
   	}else if ( phoseedEcal_0 == ECAL::EP ){
                phoseedtimeCaliE0_0 = epmape0->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE1_0 = epmape1->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCali2E1_0 = epmap2e1->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCali4E1_0 = epmap4e1->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE2_0 = epmape2->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE5_0 = epmape5->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCali2E5_0 = epmap2e5->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCali4E5_0 = epmap4e5->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE10_0 = epmape10->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliCl_0 = epmapcl->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliIc_0 = epmapic->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                //std::cout << "Filling EP 0 with " << phoseedI1_0 << " by " << phoseedI2_0 << " : " << phoseedtimeCali_0 << " and " << phoseedtimeStcCali_0 << std::endl;
        }else if (phoseedEcal_0 == ECAL::EM ){
                phoseedtimeCaliE0_0 = emmape0->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE1_0 = emmape1->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCali2E1_0 = emmap2e1->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCali4E1_0 = emmap4e1->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE2_0 = emmape2->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE5_0 = emmape5->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCali2E5_0 = emmap2e5->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCali4E5_0 = emmap4e5->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliE10_0 = emmape10->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliCl_0 = emmapcl->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
                phoseedtimeCaliIc_0 = emmapic->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
		//std::cout << "Filling EM 0 with " << phoseedI1_0 << " by " << phoseedI2_0 << " : " << phoseedtimeCali_0 << " and " << phoseedtimeStcCali_0 << std::endl;
        }

	if ( phoseedEcal_1 == ECAL::EB ){
                phoseedtimeCaliE0_1 = ebmape0->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE1_1 = ebmape1->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCali2E1_1 = ebmap2e1->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCali4E1_1 = ebmap4e1->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE2_1 = ebmape2->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE5_1 = ebmape5->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCali2E5_1 = ebmap2e5->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCali4E5_1 = ebmap4e5->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE10_1 = ebmape10->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCaliCl_1 = ebmapcl->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                phoseedtimeCaliIc_1 = ebmapic->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
                //std::cout << "Filling EB 1 with " << phoseedI2_1 << " by " << phoseedI1_1 << " : " << phoseedtimeCali_1 << " and " << phoseedtimeStcCali_1 << std::endl;
        }else if ( phoseedEcal_1 == ECAL::EP ){
                phoseedtimeCaliE0_1 = epmape0->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE1_1 = epmape1->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCali2E1_1 = epmap2e1->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCali4E1_1 = epmap4e1->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE2_1 = epmape2->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE5_1 = epmape5->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCali2E5_1 = epmap2e5->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCali4E5_1 = epmap4e5->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE10_1 = epmape10->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliCl_1 = epmapcl->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliIc_1 = epmapic->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                //std::cout << "Filling EP 1 with " << phoseedI1_1 << " by " << phoseedI2_1 << " : " << phoseedtimeCali_1 << " and " << phoseedtimeStcCali_1 << std::endl;
        }else if (phoseedEcal_1 == ECAL::EM ){
                phoseedtimeCaliE0_1 = emmape0->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE1_1 = emmape1->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCali2E1_1 = emmap2e1->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCali4E1_1 = emmap4e1->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE2_1 = emmape2->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE5_1 = emmape5->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCali2E5_1 = emmap2e5->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCali4E5_1 = emmap4e5->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliE10_1 = emmape10->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliCl_1 = emmapcl->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                phoseedtimeCaliIc_1 = emmapic->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
                //std::cout << "Filling EM 1 with " << phoseedI1_1 << " by " << phoseedI2_1 << " : " << phoseedtimeCali_1 << " and " << phoseedtimeStcCali_1 << std::endl;
        }
    
 	b_phoseedtimeCaliE0_0->Fill();
        b_phoseedtimeCaliE0_1->Fill();
        b_phoseedtimeCaliE1_0->Fill();
        b_phoseedtimeCaliE1_1->Fill();
        b_phoseedtimeCali2E1_0->Fill();
        b_phoseedtimeCali2E1_1->Fill();
        b_phoseedtimeCali4E1_0->Fill();
        b_phoseedtimeCali4E1_1->Fill();
        b_phoseedtimeCaliE2_0->Fill();
        b_phoseedtimeCaliE2_1->Fill();
        b_phoseedtimeCaliE5_0->Fill();
        b_phoseedtimeCaliE5_1->Fill();
        b_phoseedtimeCali2E5_0->Fill();
        b_phoseedtimeCali2E5_1->Fill();
        b_phoseedtimeCali4E5_0->Fill();
        b_phoseedtimeCali4E5_1->Fill();
        b_phoseedtimeCaliE10_0->Fill();
        b_phoseedtimeCaliE10_1->Fill();

        b_phoseedtimeCaliCl_0->Fill();
        b_phoseedtimeCaliCl_1->Fill();

        b_phoseedtimeCaliIc_0->Fill();
        b_phoseedtimeCaliIc_1->Fill();       
 //   	fOutTree->Fill();
    
    }
    
    fInFile->cd();
    fInTree->Delete(); 
    fOutFile->cd();
//    fOutTree->Write();
//    fOutTree->Print();
    fOutFile->Write();
}
