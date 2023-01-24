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
#include <filesystem>
#include <string>

void dimuon_spectrum_Z(){
    
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
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df_MC("Events", "../datas/Events.root");
    
    auto df_mass_MC = df_MC.Define("dimuon_mass", computeInvariantMass, {"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"}); //
    
    df_mass_MC=df_mass_MC.Define("y", computey,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    auto df_mass1_MC= df_mass_MC.Filter("fabs(y)<0.4 ", "y1");
    auto df_mass2_MC= df_mass_MC.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
    auto df_mass3_MC= df_mass_MC.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");

    dmmasshisto(df_mass1_MC, "dimuon_spectrum_Z1","#bf{0.0<|y_{#mu#mu}|<0.4}","c1");
    dmmasshisto(df_mass2_MC, "dimuon_spectrum_Z2","#bf{1.2<|y_{#mu#mu}|<1.8}","c2");
    dmmasshisto(df_mass3_MC, "dimuon_spectrum_Z3","#bf{1.6<|y_{#mu#mu}|<2.0}","c3");

}