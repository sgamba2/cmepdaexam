#include "../include/dimuonSpectrumZ.h"
#include "../include/graphicalUtilities.h"
#include "../include/utilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TPad.h>
#include <filesystem>
#include <string>
#include <iostream>


void dimuonSpectrumZ(std::string filepath_MC, std::string filepath_datas){

    //check if the path is correct
    if(TFile::Open(filepath_datas.c_str()) != nullptr && TFile::Open(filepath_MC.c_str()) != nullptr){

        //creating dataframes
        ROOT::RDataFrame df_MC("Events", filepath_MC);
        ROOT::RDataFrame df_datas("Events", filepath_datas);

        //checking if they have the right column
        if(df_MC.HasColumn("Muon_pt") && df_MC.HasColumn("Muon_mass") && df_MC.HasColumn("Muon_phi") && df_MC.HasColumn("Muon_eta") &&  df_datas.HasColumn("Muon_pt") && df_datas.HasColumn("Muon_mass") && df_datas.HasColumn("Muon_phi") && df_datas.HasColumn("Muon_eta")){
        
            //defining all the necessary quantities
            auto df_mass_MC = df_MC.Define("quadrivectot", quadrivectot,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
            df_mass_MC = df_mass_MC.Define("dimuon_mass", "quadrivectot.mass()");
            df_mass_MC = df_mass_MC.Define("y", "quadrivectot.Rapidity()");

            auto df_mass_datas = df_datas.Define("quadrivectot", quadrivectot,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
            df_mass_datas = df_mass_datas.Define("dimuon_mass", "quadrivectot.mass()");
            df_mass_datas = df_mass_datas.Define("y", "quadrivectot.Rapidity()");

            //filter the dataframes
            auto df_mass1_MC = df_mass_MC.Filter("fabs(y)<0.4 ", "y1");
            auto df_mass2_MC = df_mass_MC.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
            auto df_mass3_MC = df_mass_MC.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");

            auto df_mass1_datas = df_mass_datas.Filter("fabs(y)<0.4 ", "y1");
            auto df_mass2_datas = df_mass_datas.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
            auto df_mass3_datas = df_mass_datas.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");

            //creating histograms
            dmMassHisto(df_mass1_MC, df_mass1_datas, "dimuon_spectrum_Z1", "#bf{0.0<|y_{#mu#mu}|<0.4}", "c1");
            dmMassHisto(df_mass2_MC, df_mass2_datas, "dimuon_spectrum_Z2", "#bf{0.8<|y_{#mu#mu}|<1.2}", "c2");
            dmMassHisto(df_mass3_MC, df_mass3_datas, "dimuon_spectrum_Z3", "#bf{1.6<|y_{#mu#mu}|<2.0}", "c3");

        }else{
            std::cerr << "Your file haven't the right columns" << std::endl;
        }
    }else{
        std::cerr << "Your files don't exist, change datas!" << std::endl;
    }
}