#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <TMath.h>
#include <TH1D.h>
#include <TH1.h>
#include <TLegend.h>
#include "TString.h"
#include <vector>

void chargeGenerated(){

  //std::vector<std::string> materials = {"Si", "SiC", "C"};
  std::vector<std::string> materials = {"Si"};
  //Create new file to store histograms
  auto hFilename = "DepositedCharge.root";
  TFile* pFile = new TFile(hFilename, "recreate");
  // Loop in materials
  for(size_t i = 0; i < materials.size(); i++) {

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
    h1->SaveAs(hFilename);
  }

}
