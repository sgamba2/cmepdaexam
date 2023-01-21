#include "utilities.h"
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

void afb(){

    //ROOT::EnableImplicitMT(1);
    ROOT::RDataFrame df_MC("Events_new", "Events.root");

    auto df_2mu_MC = allquantities(df_MC);
    
    df_2mu_MC=df_2mu_MC.Define("wd","0.5*pow(costheta,2)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),3)");

    df_2mu_MC=df_2mu_MC.Define("wn","0.5*fabs(costheta)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),2)");

    auto df_2mu_MC1= df_2mu_MC.Filter("fabs(y)<0.4 ", "y1");
    auto df_2mu_MC2= df_2mu_MC.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
    auto df_2mu_MC3= df_2mu_MC.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");
  
    auto df_cm1=df_2mu_MC1.Filter("costheta<0", "backward");
    auto df_cp1=df_2mu_MC1.Filter("costheta>=0", "forward");
    auto df_cm2=df_2mu_MC2.Filter("costheta<0", "backward");
    auto df_cp2=df_2mu_MC2.Filter("costheta>=0", "forward");
    auto df_cm3=df_2mu_MC3.Filter("costheta<0", "backward");
    auto df_cp3=df_2mu_MC3.Filter("costheta>=0", "forward");

    //first condition of rapidity
    auto histDf1 = df_cp1.Histo2D({"cp,Df1", "", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNf1 = df_cp1.Histo2D({"cp,Nf1", "cp,Nf", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wn");
    auto histDb1 = df_cm1.Histo2D({"cm,Db1", "cm,Db", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNb1 = df_cm1.Histo2D({"cm,Nb1", "cm,Nb", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wn");

    histNf1->Add(histNb1.GetPtr(),-1.0);
    histDf1->Add(histDb1.GetPtr(),+1.0);
    histNf1->Divide(histDf1.GetPtr());
    histNf1->Scale(0.375);

    auto c1 = new TCanvas("c1", "c1", 1000, 700);
    histNf1->GetXaxis()->SetTitle("m_{#mu#mu}");
    histNf1->GetXaxis()->SetTitleSize(0.04);
    histNf1->GetYaxis()->SetTitle("MC");
    histNf1->GetYaxis()->SetTitleSize(0.04);
    histNf1->SetStats(0);
    histNf1->DrawClone();

    //second condition of rapidity
    auto histDf2 = df_cp2.Histo2D({"cp,Df2", "", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNf2 = df_cp2.Histo2D({"cp,Nf2", "", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wn");
    auto histDb2 = df_cm2.Histo2D({"cm,Db2", "", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNb2 = df_cm2.Histo2D({"cm,Nb2", "", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wn");

    histNf2->Add(histNb2.GetPtr(),-1.0);
    histDf2->Add(histDb2.GetPtr(),+1.0);
    histNf2->Divide(histDf2.GetPtr());
    histNf2->Scale(0.375);

    auto c2 = new TCanvas("c2", "c2", 1000, 700);
    histNf2->GetXaxis()->SetTitle("m_{#mu#mu}");
    histNf2->GetXaxis()->SetTitleSize(0.04);
    histNf2->GetYaxis()->SetTitle("MC");
    histNf2->GetYaxis()->SetTitleSize(0.04);
    histNf2->SetStats(0);
    histNf2->DrawClone();

    //third condition of rapidity
    auto histDf3 = df_cp3.Histo2D({"cp,Df3", "", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNf3 = df_cp3.Histo2D({"cp,Nf3", "", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wn");
    auto histDb3 = df_cm3.Histo2D({"cm,Db3", "", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNb3 = df_cm3.Histo2D({"cm,Nb3", "", 30, 0.25,300,30,-2.4,2.4},"dimuon_mass","y","wn");

    histNf3->Add(histNb3.GetPtr(),-1.0);
    histDf3->Add(histDb3.GetPtr(),+1.0);
    histNf3->Divide(histDf3.GetPtr());
    histNf3->Scale(0.375);

    auto c3 = new TCanvas("c3", "c3", 1000, 700);
    histNf3->GetXaxis()->SetTitle("m_{#mu#mu}");
    histNf3->GetXaxis()->SetTitleSize(0.04);
    histNf3->GetYaxis()->SetTitle("MC");
    histNf3->GetYaxis()->SetTitleSize(0.04);
    histNf3->SetStats(0);
    histNf3->DrawClone();
}
