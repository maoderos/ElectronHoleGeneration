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
  std::vector<std::string> materials = {"C"};
  //Create new file to store histograms
  auto hFilename = "DepositedCharge.root";
  TFile* pFile = new TFile(hFilename, "recreate");
  // Loop in materials
  for(size_t i = 0; i < materials.size(); i++) {
    std::cout << "----------- " << materials[i].c_str() << " -----------" << std::endl;
    auto h1Title = Form("%s Charge Deposit", materials[i].c_str());
    TH1D* h1 = new TH1D(materials[i].c_str(), h1Title, 100, 0.0, 2);
    h1->GetXaxis()->SetTitle("Charge [fC]");
    auto h2Title = Form("%s Energy Deposit", materials[i].c_str());
    TH1D* h2 = new TH1D(materials[i].c_str(), h2Title, 100, 0.0, 0.2);
    h2->GetXaxis()->SetTitle("Energy [MeV]");
    //auto filename = Form("results/%s.root",materials[i].c_str());
    auto filename = Form("result/output_%s_0.root", materials[i].c_str());
    TFile* data = new TFile(filename, "READ");
    auto tree = data->Get<TTree>("Event");

    double chargeDeposited;
    double eDep;
    tree->SetBranchAddress("fCharge", &chargeDeposited);
    tree->SetBranchAddress("fEdep", &eDep); // just for testing 

    for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; iEntry++){
      tree->GetEntry(iEntry);
      h1->Fill(chargeDeposited);
      h2->Fill(eDep);
    }

    std::cout << "####### CHARGE GENERATED FIT #########" << std::endl;
    auto infoFit1 = h1->Fit("landau", "S");
    TF1* f1 = h1->GetFunction("landau");
    std::cout << "####### ENERGY DEPOSIT FIT #########" << std::endl;
    auto infoFit2 = h2->Fit("landau","S");
    TF1* f2 = h2->GetFunction("landau");
    
    auto legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    gStyle->SetOptStat(0);
    TCanvas* c1 = new TCanvas();
    c1->Divide(1,2);
    c1->cd(1);
    auto legend1 = new TLegend(0.7, 0.7, 0.9, 0.9);
    h1->Draw();
    legend1->AddEntry(h1, "Simulation");
    legend1->AddEntry(f1, "Landau distribution");
    legend1->Draw();
    c1->cd(2);
    auto legend2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    h2->Draw();
    legend2->AddEntry(h1, "Simulation");
    legend2->AddEntry(f1, "Landau distribution");
    legend2->Draw();

    
    auto outputFile = Form("%s.pdf", materials[i].c_str());
    c1->SaveAs(outputFile);
    c1->SaveAs(hFilename);
  } 
}
