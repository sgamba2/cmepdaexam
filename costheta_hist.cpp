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

    ROOT::RDataFrame df_MC("Events_new", "Events.root");

    auto df_2mu_MC= allquantities(df_MC);
    
    auto df_2mu_MCy1= df_2mu_MC.Filter("fabs(y)<0.4 ", "y1");
    auto df_2mu_MCy2= df_2mu_MC.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
    auto df_2mu_MCy3= df_2mu_MC.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");

    auto c1 = new TCanvas("c1", "c1", 1000, 700);
    constexpr int nbins = 40; //widthbins = 0.05
    auto hist1 = df_2mu_MCy1.Histo1D({"hist1", "",nbins, -1, 1}, "costheta");
    
    hist1->SetFillColor(kOrange-3); 
    hist1->SetLineColor(kOrange-3); 
    hist1->SetMarkerStyle(20);
    hist1->SetMarkerColor(kBlack); 
    hist1->SetLineStyle(0);
    hist1->GetXaxis()->SetTitle("cos(#theta*)");
    hist1->GetXaxis()->SetTitleSize(0.04);
    hist1->GetYaxis()->SetTitle("N_{Events} MC");
    hist1->GetYaxis()->SetTitleSize(0.04);
    hist1->SetStats(0);
    hist1->DrawClone("PHF3");
    TLatex label1;
    label1.SetTextSize(0.04);
    label1.SetNDC(true);
    label1.DrawLatex(0.15, 0.85, "CMS");
    label1.DrawLatex(0.15, 0.8, "#bf{0.0<|y_{#mu#mu}|<0.4}");
    label1.DrawLatex(0.6, 0.94, "#sqrt{s} = 8 TeV, L_{int} = 18.8 fb^{-1}");
    auto legend1 = new TLegend(0.65,0.80,0.85,0.86);
    legend1->AddEntry("hist1","MC:Z->#mu#mu","f");
    legend1->SetBorderSize(0);
    legend1->SetFillColor(0);
    legend1->Draw();
    c1->SaveAs("images/costheta/costheta1.pdf");
    
    auto c2 = new TCanvas("c2", "c2", 1000, 700);
    auto hist2 = df_2mu_MCy2.Histo1D({"hist2", "", nbins, -1, 1}, "costheta");
    hist2->SetFillColor(kOrange-3); 
    hist2->SetLineColor(kOrange-3); 
    hist2->SetMarkerStyle(20);
    hist2->SetMarkerColor(kBlack); 
    hist2->SetLineStyle(0);
    hist2->GetXaxis()->SetTitle("cos(#theta*)");
    hist2->GetXaxis()->SetTitleSize(0.04);
    hist2->GetYaxis()->SetTitle("N_{Events} MC");
    hist2->GetYaxis()->SetTitleSize(0.04);
    hist2->SetStats(0);
    hist2->DrawClone("PHF3");
    TLatex label2;
    label2.SetTextSize(0.04);
    label2.SetNDC(true);
    label2.DrawLatex(0.15, 0.85, "CMS");
    label2.DrawLatex(0.15, 0.8, "#bf{1.2<|y_{#mu#mu}|<1.8}");
    label2.DrawLatex(0.6, 0.94, "#sqrt{s} = 8 TeV, L_{int} = 18.8 fb^{-1}");
    auto legend2 = new TLegend(0.6,0.82,0.8,0.88);
    legend2->SetBorderSize(0);
    legend2->SetFillColor(0);
    legend2->AddEntry("hist2","MC:Z->#mu#mu","f");
    legend2->Draw();
    c2->SaveAs("images/costheta/costheta2.pdf");

    auto c3 = new TCanvas("c3", "c3", 1000, 700);
    auto hist3 = df_2mu_MCy3.Histo1D({"hist3", "", nbins, -1, 1}, "costheta"); 
    hist3->SetFillColor(kOrange-3); 
    hist3->SetLineColor(kOrange-3); 
    hist3->SetMarkerStyle(20);
    hist3->SetMarkerColor(kBlack); 
    hist3->SetLineStyle(0);
    hist3->GetXaxis()->SetTitle("cos(#theta*)");
    hist3->GetXaxis()->SetTitleSize(0.04);
    hist3->GetYaxis()->SetTitle("N_{Events} MC");
    hist3->GetYaxis()->SetTitleSize(0.04);
    hist3->SetStats(0);
    hist3->DrawClone("PHF3");
    TLatex label3;
    label3.SetTextSize(0.04);
    label3.SetNDC(true);
    label3.DrawLatex(0.15, 0.85, "CMS");
    label3.DrawLatex(0.15, 0.8,"#bf{1.6<|y_{#mu#mu}|<2.0}");
    label3.DrawLatex(0.6, 0.94, "#sqrt{s} = 8 TeV, L_{int} = 18.8 fb^{-1}");
    auto legend3 = new TLegend(0.7,0.80,0.9,0.86);
    legend3->AddEntry("hist3","MC:Z->#mu#mu","f");
    legend3->SetBorderSize(0);
    legend3->SetFillColor(0);
    legend3->Draw();    
    c3->SaveAs("images/costheta/costheta3.pdf");
}