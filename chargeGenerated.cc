#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <TMath.h>
#include <TH1D.h>
#include <TH1.h>
#include <TLegend.h>
#include "TString.h"
#include <vector>
#include <iostream>

void chargeGenerated(){

  //std::vector<std::string> materials = {"Si", "SiC", "C"};
  std::vector<std::string> materials = {"Si"};
  //Create new file to store histograms
  auto hFilename = "DepositedCharge.root";
  TFile* pFile = new TFile(hFilename, "recreate");
  // Loop in materials
  for(size_t i = 0; i < materials.size(); i++) {
    std::cout << "----------- " << materials[i].c_str() << " -----------" << std::endl;
    auto hTitle = Form("%s Charge Deposit", materials[i].c_str());
    TH1D* h1 = new TH1D(materials[i].c_str(), hTitle, 100, 0.0, 15);
    h1->GetXaxis()->SetTitle("Charge [fC]");
    //auto filename = Form("results/%s.root",materials[i].c_str());
    auto filename = "output_Si_10.root";
    TFile* data = new TFile(filename, "READ");
    auto tree = data->Get<TTree>("Event");

    double chargeDeposited;
    //tree->SetBranchAddress("fCharge", &chargeDeposited);
    tree->SetBranchAddress("fEdep", &chargeDeposited); // just for testing 

    for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; iEntry++){
      tree->GetEntry(iEntry);
      h1->Fill(chargeDeposited);
    }
    auto infoFit = h1->Fit("landau", "S");
    TF1* f1 = h1->GetFunction("landau");
    
    /*
    std::ostringstream mpv;
    mpv << "MPV = " << f1->GetParameter(1) << "#pm " << f1->GetParError(1) << " fC";  
    //std::cout >> mpv.str().c_str() >> std::endl;
    */

    auto legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    TCanvas* c1 = new TCanvas();
    c1->cd();
    gStyle->SetOptStat(0);
    h1->Draw();
    legend->AddEntry(h1, "Simulation");
    legend->AddEntry(f1, "Landau distribution");
    legend->Draw();
    auto outputFile = Form("%s.pdf", materials[i].c_str());
    c1->SaveAs(outputFile);
    c1->SaveAs(hFilename);
  } 
}
