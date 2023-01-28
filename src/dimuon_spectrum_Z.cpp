#include "utilities.h"
#include "graphical_utilities.h"
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

void dimuon_spectrum_Z(std::string filepath_MC, std::string filepath_datas){
    
    /*
    Parameters
    ----------
    It doesn't take any parameter

    Returns
    ---------
    It is a void function and it generates three different 
    plots (based on rapidity conditions) of the dimuon invariant mass.
    All the plots are saved in images/dimuonspectrumZ/file.pdf.
    */

    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    if(TFile::Open(filepath_datas.c_str())!=nullptr && TFile::Open(filepath_MC.c_str())!=nullptr){
        

        ROOT::RDataFrame df_MC("Events", filepath_MC);
        ROOT::RDataFrame df_datas("Events", filepath_datas);
        if(df_MC.HasColumn("nMuon")&& df_MC.HasColumn("Muon_pt") && df_MC.HasColumn("Muon_mass")&& df_MC.HasColumn("Muon_charge") && df_MC.HasColumn("Muon_phi") && df_MC.HasColumn("Muon_eta") &&  df_datas.HasColumn("nMuon")&& df_datas.HasColumn("Muon_pt") && df_datas.HasColumn("Muon_mass")&& df_datas.HasColumn("Muon_charge") && df_datas.HasColumn("Muon_phi")  && df_datas.HasColumn("Muon_eta") ){

            auto df_mass_MC=df_MC.Define("quadrivectot", quadrivectot,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
            auto df_mass_datas=df_datas.Define("quadrivectot", quadrivectot,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
            df_mass_MC = df_mass_MC.Define("dimuon_mass", "quadrivectot.mass()"); //
            df_mass_datas = df_mass_datas.Define("dimuon_mass", "quadrivectot.mass()");
    
            df_mass_MC=df_mass_MC.Define("y", "quadrivectot.Rapidity()");
            df_mass_datas=df_mass_datas.Define("y",  "quadrivectot.Rapidity()");

            auto df_mass1_MC= df_mass_MC.Filter("fabs(y)<0.4 ", "y1");
            auto df_mass2_MC= df_mass_MC.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
            auto df_mass3_MC= df_mass_MC.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");

            auto df_mass1_datas= df_mass_datas.Filter("fabs(y)<0.4 ", "y1");
            auto df_mass2_datas= df_mass_datas.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
            auto df_mass3_datas= df_mass_datas.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");

            dmmasshisto(df_mass1_MC,df_mass1_datas, "dimuon_spectrum_Z1","#bf{0.0<|y_{#mu#mu}|<0.4}","c1");
            dmmasshisto(df_mass2_MC,df_mass2_datas, "dimuon_spectrum_Z2","#bf{1.2<|y_{#mu#mu}|<1.8}","c2");
            dmmasshisto(df_mass3_MC,df_mass3_datas, "dimuon_spectrum_Z3","#bf{1.6<|y_{#mu#mu}|<2.0}","c3");
        }else{
            printf("your files haven t the right columns");
        }
    }else{
        printf("your files don t exist!");
    }
}