#include "../src/graphical_utilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>
#include <filesystem>
#include <string>

void test_operationhist(){
    float b1,b2, b3;
    TFile file1("../datas/tree1.root","RECREATE"); 
    TTree * tree1 = new TTree("Events","Events");
    tree1->Branch("b3",&b1,"f/F");
    tree1->Branch("b2",&b2,"f/F");
    tree1->Branch("b1",&b3,"f/F");
    tree1->Write();
    file1.Close();
    float b4,b5, b6;
    TFile file2("../datas/tree2.root","RECREATE"); 
    TTree * tree2 = new TTree("Events","Events");
    tree2->Branch("b4",&b4,"f/F");
    tree2->Branch("b5",&b5,"f/F");
    tree2->Branch("b6",&b6,"f/F");
    tree2->Write();
    file2.Close();
    ROOT::RDataFrame df1("Events", "../datas/tree1.root");
    ROOT::RDataFrame df2("Events", "../datas/tree2.root");

    auto hist1 = df1.Histo2D({"cp,Df", "", 10, 0,10,10,0,10},"b1","b2","b3");
    auto hist2 = df2.Histo2D({"cp,Nf", "", 10, 0,10,10,0,10},"b4","b5","b6");
    for(int j=0; j< 1; j++){
	    hist1->Fill(4,5);
        hist2->Fill(1,2);
    }
    auto c=new TCanvas("","",1000, 800);
    hist1->SetMarkerColor(4);
    hist1->DrawClone("SAMELEGO");
    auto hist=operationhist(hist1, hist1, hist2, hist2);
    hist2->SetMarkerColor(3);
    hist2->DrawClone("SAMELEGO");
    hist->SetMarkerColor(2);
    hist->DrawClone("SAMELEGO");
  
    



}




   
