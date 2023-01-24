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

    ROOT::RDataFrame df_MC("Events", "../datas/Events.root");

    auto df_2mu_MC = allquantities(df_MC);
    
    df_2mu_MC=df_2mu_MC.Define("wd","0.5*pow(costheta,2)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),3)");

    df_2mu_MC=df_2mu_MC.Define("wn","0.5*fabs(costheta)/pow((pow(costheta,2)+1+0.005*(1-3*pow(costheta,2))),2)");

    auto df_2mu_MC1= df_2mu_MC.Filter("fabs(y)<0.4 ", "y1");
    auto df_2mu_MC2= df_2mu_MC.Filter("fabs(y)<0.8 && fabs(y)>0.4", "y2");
    auto df_2mu_MC3= df_2mu_MC.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y3");
    auto df_2mu_MC4= df_2mu_MC.Filter("fabs(y)<1.6 && fabs(y)>1.2", "y4");
    auto df_2mu_MC5= df_2mu_MC.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y5");
    auto df_2mu_MC6= df_2mu_MC.Filter("fabs(y)<2.4 && fabs(y)>2.0", "y6");
  
    auto df_cm1=df_2mu_MC1.Filter("costheta<0", "backward");
    auto df_cp1=df_2mu_MC1.Filter("costheta>=0", "forward");
    auto df_cm2=df_2mu_MC2.Filter("costheta<0", "backward");
    auto df_cp2=df_2mu_MC2.Filter("costheta>=0", "forward");
    auto df_cm3=df_2mu_MC3.Filter("costheta<0", "backward");
    auto df_cp3=df_2mu_MC3.Filter("costheta>=0", "forward");
    auto df_cm4=df_2mu_MC4.Filter("costheta<0", "backward");
    auto df_cp4=df_2mu_MC4.Filter("costheta>=0", "forward");
    auto df_cm5=df_2mu_MC5.Filter("costheta<0", "backward");
    auto df_cp5=df_2mu_MC5.Filter("costheta>=0", "forward");
    auto df_cm6=df_2mu_MC6.Filter("costheta<0", "backward");
    auto df_cp6=df_2mu_MC6.Filter("costheta>=0", "forward");
    gStyle->SetMarkerStyle(4);
    gStyle->SetMarkerColor(1);
    //gStyle->SetOptStats(0);
    gStyle->SetPalette(1);
    gStyle->SetLabelFont(72);
    gStyle->SetPadTickX(30);
    gStyle->SetEndErrorSize(0);
    //first condition of rapidity
    auto histDf1 = df_cp1.Histo2D({"cp,Df1", "", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNf1 = df_cp1.Histo2D({"cp,Nf1", "cp,Nf", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wn");
    auto histDb1 = df_cm1.Histo2D({"cm,Db1", "cm,Db", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNb1 = df_cm1.Histo2D({"cm,Nb1", "cm,Nb", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wn");

    histNf1->Add(histNb1.GetPtr(),-1.0);
    histDf1->Add(histDb1.GetPtr(),+1.0);
    histNf1->Divide(histDf1.GetPtr());
    histNf1->Scale(0.375);

    auto c1 = new TCanvas("c1", "c1", 1000, 800);
    histNf1->GetXaxis()->SetTitle("m_{#mu#mu}");
    histNf1->GetXaxis()->SetTitleSize(0.04);
    histNf1->GetYaxis()->SetTitle("MC");
    histNf1->GetYaxis()->SetTitleSize(0.04);
    histNf1->SetStats(0);
    c1->Divide(6,1,0,0);
    c1->cd(1);
    histNf1->ProjectionX("",0,10,"s")->DrawClone("P");

    //second condition of rapidity
    auto histDf2 = df_cp2.Histo2D({"cp,Df2", "", 10,70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNf2 = df_cp2.Histo2D({"cp,Nf2", "", 10,70,110,10,-2.4,2.4},"dimuon_mass","y","wn");
    auto histDb2 = df_cm2.Histo2D({"cm,Db2", "", 10,70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNb2 = df_cm2.Histo2D({"cm,Nb2", "", 10,70,110,10,-2.4,2.4},"dimuon_mass","y","wn");

    histNf2->Add(histNb2.GetPtr(),-1.0);
    histDf2->Add(histDb2.GetPtr(),+1.0);
    histNf2->Divide(histDf2.GetPtr());
    histNf2->Scale(0.375);

    //auto c2 = new TCanvas("c2", "c2", 1000, 700);
    histNf2->GetXaxis()->SetTitle("m_{#mu#mu}");
    histNf2->GetXaxis()->SetTitleSize(0.04);
    histNf2->GetYaxis()->SetTitle("MC");
    histNf2->GetYaxis()->SetTitleSize(0.04);
    histNf2->SetStats(0);
    c1->cd(2);
    histNf2->ProjectionX("",0,10,"s")->DrawClone("P");

    //third condition of rapidity
    auto histDf3 = df_cp3.Histo2D({"cp,Df3", "", 10,70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNf3 = df_cp3.Histo2D({"cp,Nf3", "", 10,70,110,10,-2.4,2.4},"dimuon_mass","y","wn");
    auto histDb3 = df_cm3.Histo2D({"cm,Db3", "", 10,70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNb3 = df_cm3.Histo2D({"cm,Nb3", "", 10,70,110,10,-2.4,2.4},"dimuon_mass","y","wn");

    histNf3->Add(histNb3.GetPtr(),-1.0);
    histDf3->Add(histDb3.GetPtr(),+1.0);
    histNf3->Divide(histDf3.GetPtr());
    histNf3->Scale(0.375);

    //auto c3 = new TCanvas("c3", "c3", 1000, 700);
    histNf3->GetXaxis()->SetTitle("m_{#mu#mu}");
    histNf3->GetXaxis()->SetTitleSize(0.04);
    histNf3->GetYaxis()->SetTitle("MC");
    histNf3->GetYaxis()->SetTitleSize(0.04);
    histNf3->SetStats(0);
    c1->cd(3);
    histNf3->ProjectionX("",0,10,"s")->DrawClone("P");
    
    //fourth condition of rapidity 
    auto histDf4 = df_cp4.Histo2D({"cp,Df4", "", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNf4 = df_cp4.Histo2D({"cp,Nf4", "cp,Nf4", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wn");
    auto histDb4 = df_cm4.Histo2D({"cm,Db4", "cm,Db4", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNb4 = df_cm4.Histo2D({"cm,Nb4", "cm,Nb4", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wn");

    histNf4->Add(histNb4.GetPtr(),-1.0);
    histDf4->Add(histDb4.GetPtr(),+1.0);
    histNf4->Divide(histDf4.GetPtr());
    histNf4->Scale(0.375);

    //auto c4 = new TCanvas("c4", "c4", 1000, 700);
    histNf4->GetXaxis()->SetTitle("m_{#mu#mu}");
    histNf4->GetXaxis()->SetTitleSize(0.04);
    histNf4->GetYaxis()->SetTitle("MC");
    histNf4->GetYaxis()->SetTitleSize(0.04);
    histNf4->SetStats(0);
    c1->cd(4);
    histNf4->ProjectionX("",0,10,"s")->DrawClone("P");

    //fifth condition of rapidity 
    auto histDf5 = df_cp5.Histo2D({"cp,Df5", "", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNf5 = df_cp5.Histo2D({"cp,Nf5", "cp,Nf5", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wn");
    auto histDb5 = df_cm5.Histo2D({"cm,Db5", "cm,Db5", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNb5 = df_cm5.Histo2D({"cm,Nb5", "cm,Nb5", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wn");

    histNf5->Add(histNb5.GetPtr(),-1.0);
    histDf5->Add(histDb5.GetPtr(),+1.0);
    histNf5->Divide(histDf5.GetPtr());
    histNf5->Scale(0.375);

    //auto c5 = new TCanvas("c5", "c5", 1000, 700);
    histNf5->GetXaxis()->SetTitle("m_{#mu#mu}");
    histNf5->GetXaxis()->SetTitleSize(0.04);
    histNf5->GetYaxis()->SetTitle("MC");
    histNf5->GetYaxis()->SetTitleSize(0.04);
    histNf5->SetStats(0);
    c1->cd(5);
    histNf5->ProjectionX("",0,10,"s")->DrawClone("P");
    
     //sixth condition of rapidity 
    auto histDf6 = df_cp6.Histo2D({"cp,Df6", "", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNf6 = df_cp6.Histo2D({"cp,Nf6", "cp,Nf6", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wn");
    auto histDb6 = df_cm6.Histo2D({"cm,Db6", "cm,Db6", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wd");
    auto histNb6 = df_cm6.Histo2D({"cm,Nb6", "cm,Nb6", 10, 70,110,10,-2.4,2.4},"dimuon_mass","y","wn");

    histNf6->Add(histNb6.GetPtr(),-1.0);
    histDf6->Add(histDb6.GetPtr(),+1.0);
    histNf6->Divide(histDf6.GetPtr());
    histNf6->Scale(0.375);

    //auto c6 = new TCanvas("c6", "c6", 1000, 700);
    histNf6->GetXaxis()->SetTitle("m_{#mu#mu}");
    histNf6->GetXaxis()->SetTitleSize(0.04);
    histNf6->GetYaxis()->SetTitle("MC");
    histNf6->GetYaxis()->SetTitleSize(0.04);
    histNf6->SetStats(0);
    c1->cd(6);
    histNf6->ProjectionX("",0,10,"s")->DrawClone("P");
    save_histogram(c1, "afb", "afb");
    
}
