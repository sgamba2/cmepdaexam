#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "../src/filter_df.cpp"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <vector>

void test_filt(){
    /*
    Testing when a dataframe is empty
    */
    TFile file("SimpleTree.root","RECREATE"); 
    TTree * tree = new TTree("Events","Events");

    float f[2];
    f[0]=777;
    f[1]=88; //random numbers
    float n=7;
    tree->Branch("Muon_dxy",f,"f[2]/F");
    tree->Branch("Muon_pfRelIso03_chg",f,"f[2]/F");
    tree->Branch("nMuon",&n,"f/F");
    tree->Branch("Muon_eta",f,"f[2]/F");
    tree->Branch("Muon_charge",f,"f[2]/F");
    tree->Branch("Muon_pt",f,"f[2]/F");
    tree->Branch("Muon_phi",f,"f[2]/F");
    tree->Branch("Muon_mass",f,"f[2]/F");
    //tree->Show();
    tree->Write(); 
    //file.ls();
    //file.Print();
    file.Close();
    filter_df("../tests/SimpleTree.root");
}