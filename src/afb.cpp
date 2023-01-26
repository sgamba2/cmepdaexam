#include "utilities.h"
#include "graphical_utilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>
#include <filesystem>
#include <string>

void afb(){

    /*
    Parameters
    ----------
    It doesn't take any parameter

    Returns
    ---------
    It is a void function and it generates different 
    plots (based on rapidity conditions) of the forward backward asimmetry.
    All the plots are saved in images/afb/file.pdf.
    */

    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df_MC("Events", "../datas/Events_MC.root");
    ROOT::RDataFrame df_datas("Events", "../datas/Events_datas.root");

    auto df_2mu_MC = allquantities(df_MC);
    auto df_2mu_datas = allquantities(df_datas);
    
    df_2mu_MC=df_2mu_MC.Define("wd","0.5*pow(costheta,2)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),3)");
    df_2mu_datas=df_2mu_datas.Define("wd","0.5*pow(costheta,2)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),3)");

    df_2mu_MC=df_2mu_MC.Define("wn","0.5*fabs(costheta)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),2)");
    df_2mu_datas=df_2mu_datas.Define("wn","0.5*fabs(costheta)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),2)");

    auto df_2mu_MC1= df_2mu_MC.Filter("fabs(y)<=0.4 ", "y1");
    auto df_2mu_MC2= df_2mu_MC.Filter("fabs(y)<=0.8 && fabs(y)>0.4", "y2");
    auto df_2mu_MC3= df_2mu_MC.Filter("fabs(y)<=1.2 && fabs(y)>0.8", "y3");
    auto df_2mu_MC4= df_2mu_MC.Filter("fabs(y)<=1.6 && fabs(y)>1.2", "y4");
    auto df_2mu_MC5= df_2mu_MC.Filter("fabs(y)<=2.0 && fabs(y)>1.6", "y5");
    auto df_2mu_MC6= df_2mu_MC.Filter("fabs(y)<=2.4 && fabs(y)>2.0", "y6");
    
    auto df_2mu_datas1= df_2mu_datas.Filter("fabs(y)<=0.4 ", "y1");
    auto df_2mu_datas2= df_2mu_datas.Filter("fabs(y)<=0.8 && fabs(y)>0.4", "y2");
    auto df_2mu_datas3= df_2mu_datas.Filter("fabs(y)<=1.2 && fabs(y)>0.8", "y3");
    auto df_2mu_datas4= df_2mu_datas.Filter("fabs(y)<=1.6 && fabs(y)>1.2", "y4");
    auto df_2mu_datas5= df_2mu_datas.Filter("fabs(y)<=2.0 && fabs(y)>1.6", "y5");
    auto df_2mu_datas6= df_2mu_datas.Filter("fabs(y)<=2.4 && fabs(y)>2.0", "y6");
    
    afbhist(df_2mu_MC1,df_2mu_datas1,"afb1","#bf{0.0<|y_{#mu#mu}|<0.4}","c1");
    afbhist(df_2mu_MC2,df_2mu_datas2,"afb2","#bf{0.4<|y_{#mu#mu}|<0.8}","c2");
    afbhist(df_2mu_MC3,df_2mu_datas3,"afb3","#bf{0.8<|y_{#mu#mu}|<1.2}","c3");
    afbhist(df_2mu_MC4,df_2mu_datas4,"afb4","#bf{1.2<|y_{#mu#mu}|<1.6}","c4");
    afbhist(df_2mu_MC5,df_2mu_datas5,"afb5","#bf{1.6<|y_{#mu#mu}|<2.0}","c5");
    afbhist(df_2mu_MC6,df_2mu_datas6,"afb6","#bf{2.0<|y_{#mu#mu}|<2.4}","c6");

}
