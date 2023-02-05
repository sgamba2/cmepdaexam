#include "../include/costheta.h"
#include "../include/utilities.h"
#include "../include/graphicalUtilities.h"
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
#include <string>
#include <filesystem>
#include <iostream>


void costheta(std::string filepath_MC, std::string filepath_datas){

    //check if the path is correct
    if(TFile::Open(filepath_datas.c_str()) != nullptr && TFile::Open(filepath_MC.c_str()) != nullptr){

        //creating dataframes
        ROOT::RDataFrame df_MC("Events", filepath_MC);
        ROOT::RDataFrame df_datas("Events", filepath_datas);

        //checking if they have the right column
        if(df_MC.HasColumn("Muon_pt") && df_MC.HasColumn("Muon_mass") && df_MC.HasColumn("Muon_phi") && df_MC.HasColumn("Muon_eta") && df_datas.HasColumn("Muon_pt") && df_datas.HasColumn("Muon_mass") && df_datas.HasColumn("Muon_phi")  && df_datas.HasColumn("Muon_eta") ){
        
            //defining all the necessary quantities
            auto df_2mu_MC = allquantities(df_MC);
            auto df_2mu_datas = allquantities(df_datas);
    
            //filter the dataframes
            auto df_2mu_MCy1 = df_2mu_MC.Filter("fabs(y)<0.4 ", "y1");
            auto df_2mu_MCy2 = df_2mu_MC.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
            auto df_2mu_MCy3 = df_2mu_MC.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");

            auto df_2mu_datasy1 = df_2mu_datas.Filter("fabs(y)<0.4 ", "y1");
            auto df_2mu_datasy2 = df_2mu_datas.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
            auto df_2mu_datasy3 = df_2mu_datas.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");
    
            //making histograms
            cosHisto(df_2mu_MCy1, df_2mu_datasy1, "costheta1", "#bf{0.0<|y_{#mu#mu}|<0.4}", 0.45, 0.80, 0.65, 0.86, "c1");
            cosHisto(df_2mu_MCy2, df_2mu_datasy2, "costheta2", "#bf{0.8<|y_{#mu#mu}|<1.2}", 0.15, 0.82, 0.35, 0.88, "c2");
            cosHisto(df_2mu_MCy3, df_2mu_datasy3, "costheta3", "#bf{1.6<|y_{#mu#mu}|<2.0}", 0.70, 0.80, 0.90, 0.86, "c3");

        }else{
            std::cerr << "Your file haven't the right columns" << std::endl;
        }
    }else{
        std::cerr << "Your files don't exist, change datas!" << std::endl;
    }
}