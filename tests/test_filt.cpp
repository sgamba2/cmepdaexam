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
    TFile file("../datas/SimpleTree.root","RECREATE"); 
    TTree * tree = new TTree("Events","Events");

    //random numbers
    float f[2];
    f[0]=777;
    f[1]=88; 
    float n=7;
    tree->Branch("Muon_dxy",f,"f[2]/F");
    tree->Branch("Muon_pfRelIso03_chg",f,"f[2]/F");
    tree->Branch("nMuon",&n,"f/F");
    tree->Branch("Muon_eta",f,"f[2]/F");
    tree->Branch("Muon_charge",f,"f[2]/F");
    tree->Branch("Muon_pt",f,"f[2]/F");
    tree->Branch("Muon_phi",f,"f[2]/F");
    tree->Branch("Muon_mass",f,"f[2]/F");
    tree->Write(); 
    file.Close();

    int test1 = filter_df("../datas/SimpleTree.root"); //looking for an empty file
    int test2 = filter_df("../datas/file.root"); //looking for a file that doesn't exist
    int test3 = filter_df("../dati/file.root"); //looking for a file and a folder that don't exist
    int test4 = filter_df("../dati/00C074C0-1C19-4933-9407-5A05484E1F1E.root"); //looking for a folder that doesn't exist
    int test5 = filter_df("../datas/00C074C0-1C19-4933-9407-5A05484E1F1E.root"); //looking for a file and a folder that exist
    int test6 = filter_df("../datas/Events.root");
    if(test1==4 && test2==1 && test3==1 && test4==1 && test5==0 && test6==2){
        printf("test passed!");
    }else{
        printf("test failed!");
    }
}