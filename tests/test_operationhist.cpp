/******************************************************************************
* 
* \file test_operationhist.cpp
* \brief Testing if the the content of bins are almost equal to the calculated value after operation on histograms
* 
******************************************************************************/
#include "../include/graphical_utilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <stdio.h>
#include <TH2D.h>


void test_operationhist(){
/******************************************************************************
* 
* \brief Testing if the the content of some bins are almost equal to the calculated value after operation on histograms
* given by operation_hist in graphical_utilities.h
*
* \return None
* 
******************************************************************************/
  //creating two files to put inside the dataframe
  float b1,b2, b3;
  TFile file1("../datas/tree1.root","RECREATE"); 
  TTree * tree1 = new TTree("Events","Events");
  tree1->Branch("b3",&b1,"f/F");
  tree1->Branch("b2",&b2,"f/F");
  tree1->Branch("b1",&b3,"f/F");
  tree1->Write();
  file1.Close();

  //opening dataframes
  ROOT::RDataFrame df1("Events", "../datas/tree1.root");

  auto hist1 = df1.Histo2D({"", "", 10, 0.,10.,10,-1000,1000},"b1","b2","b3");
  auto hist2 = df1.Histo2D({"", "", 10, 0.,10.,10,-1000,1000},"b1","b2","b3");
  auto hist3 = df1.Histo2D({"", "", 10, 0.,10.,10,-1000,1000},"b1","b2","b3");
  auto hist4 = df1.Histo2D({"", "", 10, 0.,10.,10,-1000,1000},"b1","b2","b3");

  //adding to the histograms some content
  hist1->AddBinContent(1,120);
  hist2->AddBinContent(1,80);
  hist3->AddBinContent(1,10);
  hist4->AddBinContent(1,90);
  hist1->AddBinContent(2,-120);
  hist2->AddBinContent(2,80);
  hist3->AddBinContent(2,10);
  hist4->AddBinContent(2,90);
  hist1->AddBinContent(4,0.1);
  hist2->AddBinContent(4,-2);
  hist3->AddBinContent(4,0.3);
  hist4->AddBinContent(4,0.09);
  hist1->AddBinContent(9,-1.);
  hist2->AddBinContent(9,8.);
  hist3->AddBinContent(9,-0.10);
  hist4->AddBinContent(9,9);
    
  //try to do operations on histograms
  auto hista=operationhist(hist1, hist2, hist3, hist4);

  std::cout<<"Testing if the operations between histograms works! \n";

  if(fabs(hista->GetBinContent(1)-0.242647)<0.242647*0.0001 && fabs(hista->GetBinContent(2)+0.286765)<0.0001*0.286765 && fabs(hista->GetBinContent(4)-0.039267)<0.0001*0.039267 && fabs(hista->GetBinContent(9)+0.0198529)<0.0001*0.0198529){
    std::cout<<"Test passed! \n";
  }else{
    std::cout<<"Test failed! \n";
  }
}




   
