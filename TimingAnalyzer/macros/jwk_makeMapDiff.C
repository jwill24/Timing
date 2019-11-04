// ROOT inludes
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TString.h"
#include "TPaveText.h"

// STL includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>  


void jwk_makeMapDiff(){

TFile* infile = TFile::Open("skimmed/dispho_2t_eg2018B.root");
TFile* outfile = new TFile("skimmed/dispho_dif4_eg2018B.root","RECREATE");

//auto result1 = new TH2F("DifXtalRtDifStcPhoRecTimeEBMap","DifXtalRtDifStcPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
//result1->Sumw2();
auto result2 = new TH2F("DifXtalRtDifOOTPhoRecTimeEBMap","DifXtalRtDifOOTPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
result2->Sumw2();

//auto result1 = new TH2F("DifXtalRtDifStcPhoRecTimeEBMap","DifXtalRtDifStcPhoRecTime Map EB",86,-43.5,43.5,180,0.5,180.5);
//result1->Sumw2();
//auto result2 = new TH2F("DifXtalRtDifOOTPhoRecTimeEBMap","DifXtalRtDifOOTPhoRecTime Map EB",86,-43.5,43.5,180,0.5,180.5);
//result2->Sumw2();

auto hist1 = (TH2F*)infile->Get("DifXtalRtPhoRecTimeEBMap");
auto hist2 = (TH2F*)infile->Get("DifXtalRtStcPhoRecTimeEBMap");
auto hist3 = (TH2F*)infile->Get("DifXtalRtOOTPhoRecTimeEBMap");

int Nx = hist1->GetNbinsX();
int Ny = hist1->GetNbinsY();

float tmap[Nx][Ny];
int   nmap[Nx][Ny];

for(int i = 0; i < Nx; i++){
        for(int j = 0; j < Ny; j++){
		tmap[i][j] = 0;
		nmap[i][j] = 0;
	}
}

for(int i = 0; i < Nx; i++){
	for(int j = 0; j < Ny; j++){
		auto e1 = hist1->GetBinError(i,j);
		if( e1 > 0 ){
                        auto t3 = hist3->GetBinContent(i,j);
                	auto t1 = hist1->GetBinContent(i,j);
			auto t2 = hist2->GetBinContent(i,j);
			auto a = i; //(int)(i/2);
			auto b = 1; //(int)(j/2);
			if( j > 180 ) b = 2;
			tmap[a][b] += (t1-t3);
			nmap[a][b] += 1;			
		}
	}
}

for(int i = 0; i < Nx; i++){
        for(int j = 0; j < Ny; j++){
                auto e1 = hist1->GetBinError(i,j);
                if( e1 > 0 ){
                        auto a = i; //(int)(i/2);
                        auto b = j; //(int)(j/2);
			int c = 1;
			if( j > 180 ) c = 2;
                        result2->SetBinContent(a,b,(tmap[a][c]/nmap[a][c])+100 );
                        //result1->SetBinContent(a,b,((t1-t3)+100) );
                }
        }
}

result2->SetBinContent(1,1,120 );

outfile->cd();
//result1->Write();
result2->Write();

infile->Close();
outfile->Close();

}
