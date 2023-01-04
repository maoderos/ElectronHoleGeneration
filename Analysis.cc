#include "TROOT.h"
#include "TFile.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TString.h"
#include <iostream>
#include <stdlib.h>

void Analysis() {

  ROOT::EnableImplicitMT();

  float energyMax = 5000.0;
  float energyMin = 20.0;
  float step = 50.0;
  std::cout << "Starting Analysis" << std::endl;
  std::vector<std::string> materials = {"Si", "SiC", "C"};
  auto mg1 = new TMultiGraph();
  for (size_t i = 0; i < materials.size(); i++) {
    std::cout << materials[i] << std::endl;
    // Join all .root files for analysis
    //system("cd results/");
    //system("hadd " + materials[i] + ".root results/" + materials[i] + "/*.root");
    //system("cd ..");
    auto filename = Form("results/%s.root",materials[i].c_str());
    //TFile* data = new TFile(filename, "READ");
    ROOT::RDataFrame df("Event", filename);
    std::vector<float> energyVec;
    std::vector<float> eDep;
    std::vector<float> eDepStd;
    float energy = energyMin;
    while(energy <= energyMax){
      auto filter = Form("fPrimaryEnergy == %f", energy);
      auto dfFiltered = df.Filter(filter);
      auto hEDep = dfFiltered.Histo1D("fEdep");
      auto hEDepIoni = dfFiltered.Histo1D("fEdepIoni");
      auto hNEH = dfFiltered.Histo1D("fNumberEH");


      energy = energy + step;
    }

    

  }
  
}
