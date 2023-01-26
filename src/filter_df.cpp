#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include <string>
#include <TFile.h>
#include <iostream>
/*
string extension(string file_name){
  //store the position of last '.' in the file name
  int position=file_name.find_last_of(".");
  //store the characters after the '.' from the file_name string
  string result = file_name.substr(position+1);
  //print the result
  cout<<"The file "<< file_name<<" has <." << result << "> extension."<<endl;
  return result;
}
*/
int filter_df(std::string filepath_MC, std::string filepath_datas){    
    /*
    Parameters
    ----------
    filepath : string of the filepath with generated MC events from 
    https://eospublichttp01.cern.ch/eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola
    ("../datas/filename.root")
    Returns
    ---------
    It is an int function and it generates a new filtered dataframe in Events.root,
    in the same folder of this program. Also this new dataframe contains less 
    columns compared to the previous file. 
    return value:
    0: everything is ok
    1: doesn't exist the path or wrong file extension
    2:few columns
    */

    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT();

    if(TFile::Open(filepath_datas.c_str())!=nullptr && TFile::Open(filepath_MC.c_str())!=nullptr){
        
        ROOT::RDataFrame df_MC("Events", filepath_MC);
        ROOT::RDataFrame df_datas("Events", filepath_datas);
        
        if(df_MC.HasColumn("nMuon")&& df_MC.HasColumn("Muon_pt") && df_MC.HasColumn("Muon_mass")&& df_MC.HasColumn("Muon_charge") && df_MC.HasColumn("Muon_phi") && df_MC.HasColumn("Muon_dxy") && df_MC.HasColumn("Muon_eta") && df_MC.HasColumn("Muon_pfRelIso03_chg") && df_datas.HasColumn("nMuon")&& df_datas.HasColumn("Muon_pt") && df_datas.HasColumn("Muon_mass")&& df_datas.HasColumn("Muon_charge") && df_datas.HasColumn("Muon_phi") && df_datas.HasColumn("Muon_dxy") && df_datas.HasColumn("Muon_eta") && df_datas.HasColumn("Muon_pfRelIso03_chg")){
           
            auto df1_MC = df_MC.Filter("nMuon == 2","Events with only two muons");
            df1_MC = df1_MC.Filter("Muon_charge[0]*Muon_charge[1]==-1","Muons with opposite charge");
            df1_MC = df1_MC.Filter("fabs(Muon_eta[0])<2.4 && fabs(Muon_eta[1])<2.4","Selection on muon eta");
            df1_MC = df1_MC.Filter("(Muon_pt[0]>25 && Muon_pt[1]>15)|| (Muon_pt[1]>25 && Muon_pt[0]>15)","Selection on muon pt");
            df1_MC = df1_MC.Filter("Muon_pfRelIso03_chg[0] < 0.1*Muon_pt[0] && Muon_pfRelIso03_chg[1] < 0.1*Muon_pt[1] ","Selection on muon isolation");
            df1_MC = df1_MC.Filter("Muon_dxy[0]<0.2 && Muon_dxy[1]<0.2","Selection on transverse distance");

            auto df1_datas = df_datas.Filter("nMuon == 2","Events with only two muons");
            df1_datas = df1_datas.Filter("Muon_charge[0]*Muon_charge[1]==-1","Muons with opposite charge");
            df1_datas = df1_datas.Filter("fabs(Muon_eta[0])<2.4 && fabs(Muon_eta[1])<2.4","Selection on muon eta");
            df1_datas = df1_datas.Filter("(Muon_pt[0]>25 && Muon_pt[1]>15)|| (Muon_pt[1]>25 && Muon_pt[0]>15)","Selection on muon pt");
            df1_datas = df1_datas.Filter("Muon_pfRelIso03_chg[0] < 0.1*Muon_pt[0] && Muon_pfRelIso03_chg[1] < 0.1*Muon_pt[1] ","Selection on muon isolation");
            df1_datas = df1_datas.Filter("Muon_dxy[0]<0.2 && Muon_dxy[1]<0.2","Selection on transverse distance");

            auto nEntries1_MC = df1_MC.Count();
            auto nEntries1_datas = df1_datas.Count();
            auto report_MC = df1_MC.Report();
            auto report_datas = df1_datas.Report();

            if( nEntries1_MC.GetValue() == 0 && nEntries1_datas.GetValue() == 0){
                printf("Your filtered dataframes (MC and Run) are empty, change datas! \n");
                return 4;
            }else if(nEntries1_MC.GetValue() == 0 && nEntries1_datas.GetValue() != 0){
                printf("Your filtered dataframe (MC) is empty, change datas! \n");
                return 5;
            }else if(nEntries1_MC.GetValue() != 0 && nEntries1_datas.GetValue() == 0){
                printf("Your filtered dataframe (Run) is empty, change datas! \n");
                return 6;
            }else{
                /*if(nEntries1_MC.GetValue() < 50 && nEntries1_datas.GetValue() > 50){
                    printf("Your filtered dataframe (MC) has few events, change datas! \n");
                    return 7;
                }else if(nEntries1_MC.GetValue() > 50 && nEntries1_datas.GetValue() < 50){
                    printf("Your filtered dataframe (Run) has few events, change datas! \n");
                    return 8;
                }else if(nEntries1_MC.GetValue() < 50 && nEntries1_datas.GetValue() < 50){
                    printf("Your filtered dataframes have few events, change datas! \n");
                    return 9;
                }else{*/
                    printf("Creating filtered dataframes! \n");
                    df1_MC.Snapshot("Events","../datas/Events_MC.root",
                            {"Muon_pt","nMuon","Muon_eta","Muon_charge","Muon_mass","Muon_phi"});
                    df1_datas.Snapshot("Events","../datas/Events_datas.root",
                            {"Muon_pt","nMuon","Muon_eta","Muon_charge","Muon_mass","Muon_phi"});
                    report_MC->Print();
                    report_datas->Print();
                    return 0;
                 
            } 
        }else{
            printf("your dataset can't be processed for our analysis, few columns! \n");
            return 2;
        }
    }else {
        printf("Doesn't exist the path you have insert or it is has wrong extension, can't reach the file! Try again!\n");
        return 1;
    }
}

