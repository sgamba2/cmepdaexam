#include <ROOT/RDataFrame.hxx>
#include <cmath>

void filter_df(std::string filename){    
    /*
    Parameters
    ----------
    filename : string of the file with generated MC events from 
    https://eospublichttp01.cern.ch/eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola

    Returns
    ---------
    It is a void function and it generates a new filtered dataframe in Events.root,
    in the same folder of this program. Also this new dataframe contains less 
    columns compared to the previous file.
    */
   // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT();
    ROOT::RDataFrame df("Events", filename);
    
    auto df1 = df.Filter("nMuon == 2","Events with only two muons");
    df1 = df1.Filter("Muon_charge[0]*Muon_charge[1]==-1","Muons with opposite charge");
    df1 = df1.Filter("fabs(Muon_eta[0])<2.4 && fabs(Muon_eta[1])<2.4","Selection on muon eta");
    df1 = df1.Filter("(Muon_pt[0]>25 && Muon_pt[1]>15)|| (Muon_pt[1]>25 && Muon_pt[0]>15)","Selection on muon pt");
    df1 = df1.Filter("Muon_pfRelIso03_chg[0] < 0.1*Muon_pt[0] && Muon_pfRelIso03_chg[1] < 0.1*Muon_pt[1] ","Selection on muon isolation");
    df1 = df1.Filter("Muon_dxy[0]<0.2 && Muon_dxy[1]<0.2","Selection on transverse distance");

    auto nEntries = df.Count();
    auto report = df1.Report();

    if( nEntries.GetValue() == 0){
        printf("Your filtered dataframe is empty, change datas! \n");
    }
    else{
        printf("Creating filtered dataframe! \n");
        df1.Snapshot("Events_new","Events.root",
               {"Muon_pt","nMuon","Muon_eta","Muon_charge","Muon_mass","Muon_phi"});
        report->Print();
    }
  
}
