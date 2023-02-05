/******************************************************************************
* 
* \file testOperationHist.cpp
* \brief Testing if the the content of bins are almost equal to the calculated value after operation on histograms
* 
******************************************************************************/
#include "../include/graphicalUtilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TH2D.h>
#include <iostream>
#include <cmath>
#include <cstdlib>

void testOperationHist(){
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

  //creating four different histos
  auto hist1 = df1.Histo2D({"", "", 10, 0.,10.,10,-1000,1000},"b1","b2","b3");
  auto hist2 = df1.Histo2D({"", "", 10, 0.,10.,10,-1000,1000},"b1","b2","b3");
  auto hist3 = df1.Histo2D({"", "", 10, 0.,10.,10,-1000,1000},"b1","b2","b3");
  auto hist4 = df1.Histo2D({"", "", 10, 0.,10.,10,-1000,1000},"b1","b2","b3");
 
  //creating random variables from 0 to 1 or -1 to 0
  float n1= static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX));
  float n2= (-1) * static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX));
  float n3= (-1) * static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX));
  float n4= static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX));

  //adding to the histograms some content
  hist1->AddBinContent(1,n1);
  hist2->AddBinContent(1,n2);
  hist3->AddBinContent(1,n3);
  hist4->AddBinContent(1,n4);
  hist1->AddBinContent(2,n1*100);
  hist2->AddBinContent(2,n2*(-4));
  hist3->AddBinContent(2,n3*5);
  hist4->AddBinContent(2,n4);
  hist1->AddBinContent(4,n1*2);
  hist2->AddBinContent(4,n2*(-1));
  hist3->AddBinContent(4,n3*22);
  hist4->AddBinContent(4,n4);
  hist1->AddBinContent(9,n1-10);
  hist2->AddBinContent(9,n2+3);
  hist3->AddBinContent(9,n3+17);
  hist4->AddBinContent(9,n4*8);
  
  //creating variables I expect
  auto var1=(n1-n3)*0.375/(n2+n4);
  auto var2=(n1*100-n3*5)*0.375/(n2*(-4)+n4);
  auto var3=(n1*2-n3*22)*0.375/(n2*(-1)+n4);
  auto var4=(n1-10-n3-17)*0.375/(n2+3+n4*8);

  //try to do operations on histograms
  auto hista = operationHist(hist1, hist2, hist3, hist4);

  std::cout << "Testing if the operations between histograms works!" << std::endl;

  if(fabs(hista->GetBinContent(1)-var1) < fabs(var1*0.0001) && fabs(hista->GetBinContent(2)-var2) < fabs(var2*0.0001) && fabs(hista->GetBinContent(4)-var3) < fabs(var3*0.0001) && fabs(hista->GetBinContent(9)-var4) < fabs(var4*0.0001) && hista->GetBinContent(9)*var4 > 0 && hista->GetBinContent(4)*var3 > 0 && hista->GetBinContent(2)*var2 > 0 && hista->GetBinContent(1)*var1 > 0){
    std::cout << "Test passed!" << std::endl;
  }else{
    std::cout << "Test failed!" << std::endl;
  }
}




   
