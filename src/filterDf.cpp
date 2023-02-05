#include "../include/filterDf.h"
#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include <string>
#include <TFile.h>
#include <iostream>
#include <filesystem>

int filterDf(std::string filepath_MC, std::string filepath_datas, std::string filename_MC_fil, std::string filename_datas_fil){   

    namespace fs = std::filesystem;
    //checking if the paths exist
    if(TFile::Open(filepath_datas.c_str()) != nullptr && TFile::Open(filepath_MC.c_str()) != nullptr){
        
        //creating dataframes
        ROOT::RDataFrame df_MC("Events", filepath_MC);
        ROOT::RDataFrame df_datas("Events", filepath_datas);
        
        //checking if there are the right columns
        if(df_MC.HasColumn("nMuon") && df_MC.HasColumn("Muon_pt") && df_MC.HasColumn("Muon_mass") && df_MC.HasColumn("Muon_charge") && df_MC.HasColumn("Muon_phi") && df_MC.HasColumn("Muon_dxy") && df_MC.HasColumn("Muon_eta") && df_MC.HasColumn("Muon_pfRelIso03_chg") && df_datas.HasColumn("nMuon")&& df_datas.HasColumn("Muon_pt") && df_datas.HasColumn("Muon_mass")&& df_datas.HasColumn("Muon_charge") && df_datas.HasColumn("Muon_phi") && df_datas.HasColumn("Muon_dxy") && df_datas.HasColumn("Muon_eta") && df_datas.HasColumn("Muon_pfRelIso03_chg")){

            //filtering dataframes
            auto df1_MC = df_MC.Filter("nMuon == 2","Events with only two muons");
            df1_MC = df1_MC.Filter("Muon_charge[0]*Muon_charge[1] == -1","Muons with opposite charge");
            df1_MC = df1_MC.Filter("fabs(Muon_eta[0]) < 2.4 && fabs(Muon_eta[1]) < 2.4","Selection on muon eta");
            df1_MC = df1_MC.Filter("(Muon_pt[0] > 25 && Muon_pt[1] > 15)|| (Muon_pt[1] > 25 && Muon_pt[0] > 15)","Selection on muon pt");
            df1_MC = df1_MC.Filter("Muon_pfRelIso03_chg[0] < 0.1*Muon_pt[0] && Muon_pfRelIso03_chg[1] < 0.1*Muon_pt[1] ","Selection on muon isolation");
            df1_MC = df1_MC.Filter("Muon_dxy[0] < 0.2 && Muon_dxy[1] < 0.2","Selection on transverse distance");
            
            auto df1_datas = df_datas.Filter("nMuon == 2","Events with only two muons");
            df1_datas = df1_datas.Filter("Muon_charge[0]*Muon_charge[1] == -1","Muons with opposite charge");
            df1_datas = df1_datas.Filter("fabs(Muon_eta[0]) < 2.4 && fabs(Muon_eta[1]) < 2.4","Selection on muon eta");
            df1_datas = df1_datas.Filter("(Muon_pt[0] > 25 && Muon_pt[1] > 15)|| (Muon_pt[1] > 25 && Muon_pt[0] > 15)","Selection on muon pt");
            df1_datas = df1_datas.Filter("Muon_pfRelIso03_chg[0] < 0.1*Muon_pt[0] && Muon_pfRelIso03_chg[1] < 0.1*Muon_pt[1] ","Selection on muon isolation");
            df1_datas = df1_datas.Filter("Muon_dxy[0] < 0.2 && Muon_dxy[1] < 0.2","Selection on transverse distance");

            //number of events
            auto nEntries1_MC = df1_MC.Count();
            auto nEntries1_datas = df1_datas.Count();

            //reports
            auto report_MC = df1_MC.Report();
            auto report_datas = df1_datas.Report();

            if( nEntries1_MC.GetValue() <= 50 && nEntries1_datas.GetValue() <= 50){
                std::cerr << "Your filtered dataframes (MC and Run) are almost empty, change datas!" << std::endl;
                return 3;
            }else if(nEntries1_MC.GetValue() <= 50 && nEntries1_datas.GetValue() > 50){
                std::cerr << "Your filtered dataframe (MC) is almost empty, change datas!" << std::endl;
                return 3;
            }else if(nEntries1_MC.GetValue() > 50 && nEntries1_datas.GetValue() <= 50){
                std::cerr << "Your filtered dataframe (Run) is almost empty, change datas!" << std::endl;
                return 3;
            }else{   
                filename_MC_fil = "datas/" + filename_MC_fil; 
                filename_datas_fil = "datas/" + filename_datas_fil;                                       
                if (!fs::is_directory("datas") || !fs::exists("datas")) {
                    std::cerr << "Coudn't find the directory datas: creating new directory!" << std::endl;
                    fs::create_directory("datas");
                    std::cerr << "Creating filtered dataframes!" << std::endl;
                }
                df1_MC.Snapshot("Events",filename_MC_fil,
                        {"Muon_pt","Muon_eta","Muon_mass","Muon_phi"});
                df1_datas.Snapshot("Events",filename_datas_fil,
                        {"Muon_pt","Muon_eta","Muon_mass","Muon_phi"});
                std::cout << "Filtered dataframes successfully created in " << filename_MC_fil << " and " << filename_datas_fil << std::endl;
                report_MC->Print();
                report_datas->Print();
                return 0; 
            }    
        }else{
            std::cerr << "Your dataset can't be processed for our analysis, few columns!" << std::endl;
            return 2;
        }
    }else{
        std::cerr << "Doesn't exist the path you have insert or it is has wrong extension, can't reach the file! Try again!" << std::endl;
        return 1;
    }
}

