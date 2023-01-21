#include <ROOT/RDataFrame.hxx>

void filterdf(std::string filename){    
    ROOT::RDataFrame df("Events", filename);
    df.Snapshot("Events_new","Events.root",
               {"Muon_pt","nMuon","Muon_pfRelIso03_chg","Muon_eta","Muon_dxy","Muon_charge","Muon_mass","Muon_phi"});
    
    auto df1 = df.Filter("nMuon == 2","Events with only two muons");
    df1 = df1.Filter("Muon_charge[0]*Muon_charge[1]==-1","Muons with opposite charge");
    df1=df1.Filter("fabs(Muon_eta[0])<2.4 && fabs(Muon_eta[1])<2.4","Selection on muon eta");
    df1=df1.Filter("(Muon_pt[0]>25 && Muon_pt[1]>15)|| (Muon_pt[1]>25 && Muon_pt[0]>15)","Selection on muon pt");
    df1=df1.Filter("Muon_pfRelIso03_chg[0] < 0.1*Muon_pt[0] && Muon_pfRelIso03_chg[1] < 0.1*Muon_pt[1] ","Selection on muon isolation");
    df1=df1.Filter("Muon_dxy[0]<0.2 && Muon_dxy[1]<0.2","Selection on transverse distance");
}