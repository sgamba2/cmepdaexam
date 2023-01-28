/******************************************************************************
* 
* \file afb.cpp
* \brief Creating afb histogram in function of dimuon mass
* 
******************************************************************************/
#include "utilities.h"
#include "graphical_utilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>
#include <filesystem>
#include <string>
#include <iostream>


void afb(std::string filepath_MC){
/******************************************************************************
* 
* \brief Creating afb histogram in function of dimuon mass
* 
* @param filepath_MC: dataframe of the MC datas
*
* \return None
* 
******************************************************************************/

    //checking the correct path
    if( TFile::Open(filepath_MC.c_str())!=nullptr){

        //creating the dataframe
        ROOT::RDataFrame df_MC("Events", filepath_MC);
        
        //checking if there are the right columns
        if(df_MC.HasColumn("nMuon")&& df_MC.HasColumn("Muon_pt") && df_MC.HasColumn("Muon_mass")&& df_MC.HasColumn("Muon_charge") && df_MC.HasColumn("Muon_phi") && df_MC.HasColumn("Muon_eta") ){
            
            //defining all quantities
            auto df_2mu_MC = allquantities(df_MC);
            df_2mu_MC=df_2mu_MC.Define("wd","0.5*pow(costheta,2)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),3)");
            df_2mu_MC=df_2mu_MC.Define("wn","0.5*fabs(costheta)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),2)");

            //filter the dataframe
            auto df_2mu_MC1= df_2mu_MC.Filter("fabs(y)<=0.4 ", "y1");
            auto df_2mu_MC2= df_2mu_MC.Filter("fabs(y)<=0.8 && fabs(y)>0.4", "y2");
            auto df_2mu_MC3= df_2mu_MC.Filter("fabs(y)<=1.2 && fabs(y)>0.8", "y3");
            auto df_2mu_MC4= df_2mu_MC.Filter("fabs(y)<=1.6 && fabs(y)>1.2", "y4");
            auto df_2mu_MC5= df_2mu_MC.Filter("fabs(y)<=2.0 && fabs(y)>1.6", "y5");
            auto df_2mu_MC6= df_2mu_MC.Filter("fabs(y)<=2.4 && fabs(y)>2.0", "y6");
    
            //setting canvas and pads
            auto c = new TCanvas("c","",1000,800);
            auto pad1 = new TPad("pad1","pad1",0.03,0,0.18,1);
            auto pad2 = new TPad("pad2","pad2",0.19,0,0.34,1);
            auto pad3 = new TPad("pad3","pad3",0.35,0,0.50,1);
            auto pad4 = new TPad("pad4","pad4",0.52,0,0.67,1);
            auto pad5 = new TPad("pad5","pad5",0.69,0,0.84,1);
            auto pad6 = new TPad("pad6","pad6",0.86,0,1,1);
            pad1->SetTopMargin(0.1);
            pad1->SetLeftMargin(0.17);
            pad1->SetBottomMargin(0.1);
            pad1->SetBorderMode(0);
            pad2->SetTopMargin(0.1);
            pad2->SetLeftMargin(0.17);
            pad2->SetBottomMargin(0.1);
            pad2->SetBorderMode(0);
            pad3->SetTopMargin(0.1);
            pad3->SetLeftMargin(0.17);
            pad3->SetBottomMargin(0.1);
            pad3->SetBorderMode(0);
            pad4->SetTopMargin(0.1);
            pad4->SetLeftMargin(0.17);
            pad4->SetBottomMargin(0.1);
            pad4->SetBorderMode(0);
            pad5->SetTopMargin(0.1);
            pad5->SetLeftMargin(0.17);
            pad5->SetBottomMargin(0.1);
            pad5->SetBorderMode(0);
            pad6->SetTopMargin(0.1);
            pad6->SetLeftMargin(0.17);
            pad6->SetBottomMargin(0.1);
            pad6->SetBorderMode(0);
            pad1->Draw();
            pad2->Draw();
            pad3->Draw();
            pad4->Draw();
            pad5->Draw();
            pad6->Draw();

            //drawing pads
            pad1->cd();
            afbhist(df_2mu_MC1,"afb1","#bf{0.0<|y_{#mu#mu}|<0.4}");
            pad2->cd();
            afbhist(df_2mu_MC2,"afb2","#bf{0.4<|y_{#mu#mu}|<0.8}");
            pad3->cd();
            afbhist(df_2mu_MC3,"afb3","#bf{0.8<|y_{#mu#mu}|<1.2}");
            pad4->cd();
            afbhist(df_2mu_MC4,"afb4","#bf{1.2<|y_{#mu#mu}|<1.6}");
            pad5->cd();
            afbhist(df_2mu_MC5,"afb5","#bf{1.6<|y_{#mu#mu}|<2.0}");
            pad6->cd();
            afbhist(df_2mu_MC6,"afb6","#bf{2.0<|y_{#mu#mu}|<2.4}");

            //saving histogram
            save_histogram(c, "afb", "afb");

        }else{
            std::cout << "Your file haven't the right columns\n";
        }
    }else{
        std::cout << "Your files don't exist, change datas!\n";
    }
}
