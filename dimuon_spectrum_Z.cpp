#include "utilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLatex.h>
#include <TStyle.h>

void invariantmass_dimuonZ(){
    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    //ROOT::EnableImplicitMT(1);
    ROOT::RDataFrame df_MC("Events_new", "Events.root");
    
    auto df_mass_MC = df_MC.Define("dimuon_mass", computeInvariantMass, {"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"}); //
    
    df_mass_MC=df_mass_MC.Define("y", computey,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    auto df_mass1_MC= df_mass_MC.Filter("fabs(y)<0.4 ", "y1");
    auto df_mass2_MC= df_mass_MC.Filter("fabs(y)<1.2 && fabs(y)>0.8", "y2");
    auto df_mass3_MC= df_mass_MC.Filter("fabs(y)<2.0 && fabs(y)>1.6", "y3");

    const auto bins = 60; // Number of bins in the histogram
    const auto low = 70; // Lower edge of the histogram
    const auto up = 110.0; // Upper edge of the histogram
    
    auto hist1 = df_mass1_MC.Histo1D({"hist1", "", bins, low, up}, "dimuon_mass");
    // Request cut-flow report
    auto report1 = df_mass1_MC.Report();

    // Create canvas for plotting
    auto c1 = new TCanvas("c1", "c1", 800, 700);
    c1->SetLogy();

    // Draw histogram
    hist1->GetXaxis()->SetTitle("m_{#mu#mu} (GeV)");
    hist1->GetXaxis()->SetTitleSize(0.04);
    hist1->GetYaxis()->SetTitle("N_{Events}");
    hist1->GetYaxis()->SetTitleSize(0.04);
    hist1->SetStats(0);
    hist1->SetFillColor(kOrange-3); 
    hist1->SetLineColor(kOrange-3); 
    hist1->SetMarkerStyle(20);
    hist1->SetMarkerColor(kBlack); 
    hist1->SetLineStyle(0);
    hist1->DrawClone("PHF3");


    // Draw labels
    TLatex label1;
    label1.SetTextSize(0.04);
    label1.SetTextAlign(12);
    label1.SetNDC(true);
    label1.SetTextAlign(11);
    label1.DrawLatex(0.45, 0.8, "Z");
    label1.DrawLatex(0.10, 0.92, "CMS");
    label1.DrawLatex(0.15, 0.8, "#bf{0.0<|y_{#mu#mu}|<0.4}");
    label1.SetTextAlign(31);
    label1.DrawLatex(0.90, 0.92, "#sqrt{s} = 8 TeV, L_{int} = 11.6 fb^{-1}");

    //legend
    auto legend1 = new TLegend(0.65,0.80,0.85,0.86);
    legend1->AddEntry("hist1","MC:Z->#mu#mu","f");
    legend1->SetBorderSize(0);
    legend1->SetFillColor(0);
    legend1->Draw();
    
    c1->SaveAs("images/dimuonspectrumZ/dimuonSpectrum_Z1.pdf");
    report1->Print();

    auto hist2 = df_mass2_MC.Histo1D({"hist2", "", bins, low, up}, "dimuon_mass");
    // Request cut-flow report
    auto report2 = df_mass2_MC.Report();

    // Create canvas for plotting
    auto c2 = new TCanvas("c2", "c2", 800, 700);
    c2->SetLogy();

    // Draw histogram
    hist2->GetXaxis()->SetTitle("m_{#mu#mu} (GeV)");
    hist2->GetXaxis()->SetTitleSize(0.04);
    hist2->GetYaxis()->SetTitle("N_{Events}");
    hist2->GetYaxis()->SetTitleSize(0.04);
    hist2->SetStats(0);
    hist2->SetFillColor(kOrange-3); 
    hist2->SetLineColor(kOrange-3); 
    hist2->SetMarkerStyle(20);
    hist2->SetMarkerColor(kBlack); 
    hist2->SetLineStyle(0);
    hist2->DrawClone("PHF3");


    // Draw labels
    TLatex label2;
    label2.SetTextSize(0.04);
    label2.SetTextAlign(12);
    label2.SetNDC(true);
    label2.SetTextAlign(11);
    label1.DrawLatex(0.45, 0.8, "Z");
    label2.DrawLatex(0.10, 0.92, "CMS");
    label2.DrawLatex(0.15, 0.8, "#bf{1.2<|y_{#mu#mu}|<1.8}");
    label2.SetTextAlign(31);
    label2.DrawLatex(0.90, 0.92, "#sqrt{s} = 8 TeV, L_{int} = 11.6 fb^{-1}");

    //legend
    auto legend2 = new TLegend(0.65,0.80,0.85,0.86);
    legend2->AddEntry("hist2","MC:Z->#mu#mu","f");
    legend2->SetBorderSize(0);
    legend2->SetFillColor(0);
    legend2->Draw();
    
    c2->SaveAs("images/dimuonspectrumZ/dimuonSpectrum_Z2.pdf");
    report2->Print();

    auto hist3 = df_mass3_MC.Histo1D({"hist3", "", bins, low, up}, "dimuon_mass");
    // Request cut-flow report
    auto report3 = df_mass3_MC.Report();

    // Create canvas for plotting
    auto c3 = new TCanvas("c3", "c3", 800, 700);
    c3->SetLogy();

    // Draw histogram
    hist3->GetXaxis()->SetTitle("m_{#mu#mu} (GeV)");
    hist3->GetXaxis()->SetTitleSize(0.04);
    hist3->GetYaxis()->SetTitle("N_{Events}");
    hist3->GetYaxis()->SetTitleSize(0.04);
    hist3->SetStats(0);
    hist3->SetFillColor(kOrange-3); 
    hist3->SetLineColor(kOrange-3); 
    hist3->SetMarkerStyle(20);
    hist3->SetMarkerColor(kBlack); 
    hist3->SetLineStyle(0);
    hist3->DrawClone("PHF3");


    // Draw labels
    TLatex label3;
    label3.SetTextSize(0.04);
    label3.SetTextAlign(12);
    label3.SetNDC(true);
    label3.SetTextAlign(11);
    label1.DrawLatex(0.45, 0.8, "Z");
    label3.DrawLatex(0.10, 0.92, "CMS");
    label3.DrawLatex(0.15, 0.8,"#bf{1.6<|y_{#mu#mu}|<2.0}");
    label3.SetTextAlign(31);
    label3.DrawLatex(0.90, 0.92, "#sqrt{s} = 8 TeV, L_{int} = 11.6 fb^{-1}");

    //legend
    auto legend3 = new TLegend(0.65,0.80,0.85,0.86);
    legend3->AddEntry("hist3","MC:Z->#mu#mu","f");
    legend3->SetBorderSize(0);
    legend3->SetFillColor(0);
    legend3->Draw();
    
    c3->SaveAs("images/dimuonspectrumZ/dimuonSpectrum_Z3.pdf");
    report3->Print();
}