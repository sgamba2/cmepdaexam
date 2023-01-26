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
#include <TROOT.h>
#include <TLegend.h>
#include <string>
#include <filesystem>


void costheta_hist(){
    
    /*
    Parameters
    ----------
    It doesn't take any parameter

    Returns
    ---------
    It is a void function and it generates three different 
    plots (based on rapidity conditions) of the cos(theta*) of the dimuon system.
    All the plots are saved in images/costheta/file.pdf.
    */

    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df_MC("Events", "../datas/Events_MC.root");
    ROOT::RDataFrame df_datas("Events", "../datas/Events_datas.root");

    auto df_2mu_MC= allquantities(df_MC);
    auto df_2mu_datas= allquantities(df_datas);
    
    auto df_2mu_MCy1= df_2mu_MC.Filter("fabs(y)<0.4 ", "y1");
    auto df_2mu_MCy2= df_2mu_MC.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
    auto df_2mu_MCy3= df_2mu_MC.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");

    auto df_2mu_datasy1= df_2mu_datas.Filter("fabs(y)<0.4 ", "y1");
    auto df_2mu_datasy2= df_2mu_datas.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
    auto df_2mu_datasy3= df_2mu_datas.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");
    
    coshisto(df_2mu_MCy1,df_2mu_datasy1, "costheta1","#bf{0.0<|y_{#mu#mu}|<0.4}",0.45,0.80,0.65,0.86,"c1");
    coshisto(df_2mu_MCy2,df_2mu_datasy2, "costheta2","#bf{1.2<|y_{#mu#mu}|<1.8}",0.15,0.82,0.35,0.88,"c2");
    coshisto(df_2mu_MCy3,df_2mu_datasy3, "costheta3","#bf{1.6<|y_{#mu#mu}|<2.0}",0.7,0.80,0.9,0.86,"c3");

}