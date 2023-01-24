#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include <string>
#include <TFile.h>

int filter_df(std::string filepath){    
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
    If the return is 0 everything was done correctly.
    1: doesn't exist the path
    4: it was an empty file
    */

    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT();

    if(TFile::Open(filepath.c_str())!=nullptr){

        TFile * file= new TFile(filepath.c_str()); 
        ROOT::RDataFrame df("Events", filepath);

        auto df1 = df.Filter("nMuon == 2","Events with only two muons");
        df1 = df1.Filter("Muon_charge[0]*Muon_charge[1]==-1","Muons with opposite charge");
        df1 = df1.Filter("fabs(Muon_eta[0])<2.4 && fabs(Muon_eta[1])<2.4","Selection on muon eta");
        df1 = df1.Filter("(Muon_pt[0]>25 && Muon_pt[1]>15)|| (Muon_pt[1]>25 && Muon_pt[0]>15)","Selection on muon pt");
        df1 = df1.Filter("Muon_pfRelIso03_chg[0] < 0.1*Muon_pt[0] && Muon_pfRelIso03_chg[1] < 0.1*Muon_pt[1] ","Selection on muon isolation");
        df1 = df1.Filter("Muon_dxy[0]<0.2 && Muon_dxy[1]<0.2","Selection on transverse distance");

        auto nEntries1 = df1.Count();
        auto report = df1.Report();

        if( nEntries1.GetValue() == 0){
            printf("Your filtered dataframe is empty, change datas! \n");
            return 4;
        }
        else{
            printf("Creating filtered dataframe! \n");
            df1.Snapshot("Events_new","../datas/Events.root",
                    {"Muon_pt","nMuon","Muon_eta","Muon_charge","Muon_mass","Muon_phi"});
            report->Print();
            return 0;
        }  
    } else{
        printf("Doesn't exist the path you have insert, can't reach the file! Try again!\n");
        return 1;
    }
}

