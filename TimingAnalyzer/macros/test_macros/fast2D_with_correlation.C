#include "Common.cpp+"

void fast2D_with_correlation(const TString & filename, const TString & treename, TString selection, const TString & label, 
			     const TString & timevar, const TString & timelabel, const TString & metvar, const TString & metlabel,
			     const TString & textfile, const TString & outdir)
{
  // get text file
  std::ofstream norms(textfile.Data(),std::ios_base::app);

  if      (selection.EqualTo("NONE",TString::kExact))
  {
    selection = "";
  }
  else if (selection.Contains("MC",TString::kExact))
  {
    selection.ReplaceAll("MC","");
    selection += " * (evtwgt * puwgt)";
  }

  // set style
  auto tdrStyle = new TStyle("TDRStyle","Style for P-TDR");
  Common::SetTDRStyle(tdrStyle);
  Common::SetupEras();

  // get inputs
  auto file = TFile::Open(filename.Data());
  Common::CheckValidFile(file,filename);
  
  auto tree = (TTree*)file->Get(treename.Data());
  Common::CheckValidTree(tree,treename,filename);

  // setup hist --> adjust by hand for each version
  Double_t xbins[3] = {-2,3,25};
  Double_t ybins[3] = {0,100,3000};
  auto hist = new TH2F("hist",Form("MET vs Time;Photon %s Time [ns];%s MET [GeV]",timelabel.Data(),metlabel.Data()),2,xbins,2,ybins);
  hist->SetMarkerSize(2);
  hist->Sumw2();

  // fill hist
  std::cout << "Filling hist..." << std::endl;
  tree->Draw(Form("%s:%s>>hist",metvar.Data(),timevar.Data()),selection.Data(),"goff");

  // fill output file
  std::cout << "Filling text file..." << std::endl;
  const auto A = hist->GetBinContent(1,1);
  const auto B = hist->GetBinContent(1,2);
  const auto C = hist->GetBinContent(2,2);
  const auto D = hist->GetBinContent(2,1);

  const auto Aunc = hist->GetBinError(1,1);
  const auto Bunc = hist->GetBinError(1,2);
  const auto Dunc = hist->GetBinError(2,1);

  const auto predC    = B*D/A;
  const auto predCunc = predC*std::sqrt(std::pow(Bunc/B,2)+std::pow(Dunc/D,2)+std::pow(Aunc/A,2));

  norms << label.Data() << ","
	<< A << "," << B << "," << C << "," << D << ","
	<< B/A << "," << C/D << "," << D/A << "," << C/B << ","
	<< predC << "," << predCunc << std::endl;
  
  // draw it
  std::cout << "Drawing and saving..." << std::endl;
  auto canv = new TCanvas();
  canv->cd();
  canv->SetLogz(1);

  hist->Draw("colz text");

  // print correlation
  auto text = new TPaveText(0.68,0.7,0.81,0.93,"NDC");
  text->SetTextAlign(11);
  text->SetFillColorAlpha(text->GetFillColor(),0);
  text->AddText(Form("CF: %6.3f",hist->GetCorrelationFactor()));
  text->Draw("same");

  // save it
  const TString outname = label+"_"+metlabel+"MET_"+timelabel+"Time_Box";

  Common::CMSLumi(canv,0,"Full");
  Common::SaveAs(canv,outname);

  // move it to www
  gSystem->Exec("mv "+outname+".png "+outdir);
  gSystem->Exec("mv "+outname+".pdf "+outdir);

  // delete it all
  std::cout << "Deleting..." << std::endl;
  delete text;
  delete canv;
  delete hist;
  delete tree;
  delete file;
  delete tdrStyle;
}
