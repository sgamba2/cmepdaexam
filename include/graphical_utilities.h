/******************************************************************************
* 
* \file graphical_utilities.h
* \brief Graphical utilities for displaying histograms of Afb, Z spectrum, cos(theta*) and saving the plots.
* 
******************************************************************************/
#ifndef GRAPHICAL_UTILITIES_H
#define GRAPHICAL_UTILITIES_H

#include <filesystem>
#include <string>
#include <TH2D.h>
#include <TPad.h>
#include <TVirtualPad.h>
#include <TH1D.h>
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>

void save_histogram(TCanvas *c, string namehist, string type){
/******************************************************************************
* 
* \brief Save histogram in pdf mode and png mode in the folder "images" and 
* in the subfolder "images/type", if don't exist the program creates them
* 
* @param c: the canvas I have to save
* @param namehist: name of the histogram
* @param type: name of the subfolder
* 
* \return None
* 
******************************************************************************/
   namespace fs = std::filesystem;

   // define path where to save plot
   type = "/" + type;
   string subpath = "images" + type;
   string filepath_pdf = subpath + "/" + namehist + ".pdf"; 
   string filepath_png = subpath + "/" + namehist + ".png"; 
   
   //if the folder "images" doesn't exist, it will create it
   try {                                        
      if (!fs::is_directory("images") || !fs::exists("images")) 
         throw("images");
   } catch (const char *path) { 
      std::cerr << "The folder " << path << " does not exist." << std::endl;
      std::cerr << "Creating folder..." << std::endl;
      fs::create_directory(path); 
      std::cout << "The folder " << path << " successfully created!" << std::endl;
   }

   //if the subfolder "type" doesn't exist, it will create it
   try {          
      c->SaveAs(filepath_pdf.c_str());
      c->SaveAs(filepath_png.c_str());                          
      if (!fs::is_directory(subpath.c_str()) || !fs::exists(subpath.c_str())) 
         throw(subpath.c_str());
   }catch(const char *newpath){
      std::cerr << "The folder " << newpath << " does not exist." << std::endl;
      std::cerr << "Creating folder..." << std::endl;
      fs::create_directory(newpath);
      std::cout << "The folder " << newpath << " successfully created" << std::endl;
      c->SaveAs(filepath_pdf.c_str());
      c->SaveAs(filepath_png.c_str());
   }
}


void coshisto(ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_MC, ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_datas, string filename, string rapiditylim, float x1, float y1, float x2, float y2, string canvasname){
/******************************************************************************
* 
* \brief creating cos(theta*) histogram and save
* 
* @param df_MC: dataframe of the MonteCarlo datas
* @param df_datas: dataframe of the Run datas
* @param filename: name of the final file
* @param rapiditylim: limit of rapidity to write on the canvas
* @param x1: low limit of x for the legend
* @param y1: low limit of y for the legend
* @param x2: up limit of x for the legend
* @param y2: up limit of y for the legend
* @param canvasname: name of the canvas I create
* 
* \return None
* 
******************************************************************************/
   constexpr int nbins = 40; //widthbins = 0.05

   //creating new canvas
   auto c = new TCanvas(canvasname.c_str(), "", 1000, 800);

   //creating pads
   auto pad1 = new TPad("pad1","pad1",0., 0.33, 1., 1.00);
   auto pad2 = new TPad("pad2","pad2",0., 0.08, 1., 0.30);
   pad1->SetBottomMargin(0.05);
   pad1->SetBorderMode(0);
   pad1->SetLogy();
   pad2->SetTopMargin(0.00001);
   pad2->SetBottomMargin(0.25);
   pad2->SetBorderMode(0);
   pad1->Draw();
   pad2->Draw();

   //fill pad1
   pad1->cd();

   //creating a histogram 
   auto hist_MC = df_MC.Histo1D({"hist_MC", "", nbins, -1, 1}, "costheta");
   auto hist_datas = df_datas.Histo1D({"hist_datas", "", nbins, -1, 1}, "costheta");
   hist_datas->Scale(1./float((df_datas.Count()).GetValue()));
   hist_MC->Scale(1./float((df_MC.Count()).GetValue()));

   //creating report
   auto report_MC = df_MC.Report();
   report_MC->Print();
   auto report_datas = df_datas.Report();
   report_datas->Print();

   //setting histogram properties
   hist_MC->GetYaxis()->SetTitle("N_{events,norm}");
   hist_MC->GetYaxis()->SetTitleSize(0.06);
   hist_MC->GetYaxis()->SetTitleOffset(0.7);
   hist_MC->GetYaxis()->SetLabelSize(0.05);
   hist_MC->SetStats(0);
   hist_MC->SetFillColor(kOrange-3); 
   hist_MC->SetLineColor(kOrange-3); 
   hist_MC->SetLineStyle(0);
   hist_datas->SetMarkerStyle(8);
   hist_datas->SetStats(0);

   //draw the histogram
   hist_MC->DrawClone("HF3SAME");
   hist_datas->DrawClone("PESAME");

   //writing the rapidity limits on the histogram
   TLatex label;
   label.SetTextSize(0.04);
   label.SetNDC(true);
   label.DrawLatex(0.15, 0.96, "CMS");
   label.DrawLatex(0.15, 0.925, rapiditylim.c_str());
   label.DrawLatex(0.6, 0.94, "#sqrt{s} = 8 TeV, L_{int} = 18.8 fb^{-1}");

   //writing legend
   auto legend = new TLegend(x1, y1, x2, y2);
   legend->AddEntry("hist_MC","MC:Z->#mu#mu","f");
   legend->AddEntry("hist_datas","Datas","lep");
   legend->SetBorderSize(0);
   legend->SetFillColor(0);
   legend->Draw();

   //fill pad2 
   pad2->cd();

   //creating divide histo Data/MC
   hist_datas->Divide(hist_MC.GetPtr());

   //properties
   pad2->SetGridy();
   hist_datas->GetXaxis()->SetTitle("cos(#theta*)");
   hist_datas->GetYaxis()->SetTitle("Data/MC");
   hist_datas->GetXaxis()->SetLabelSize(0.12);
   hist_datas->GetYaxis()->SetLabelSize(0.08);
   hist_datas->GetYaxis()->SetLabelOffset(0.012);
   hist_datas->GetYaxis()->SetTitleSize(0.13);
   hist_datas->GetYaxis()->SetTitleOffset(0.27);
   hist_datas->GetXaxis()->SetTitleSize(0.12);
   hist_datas->GetXaxis()->SetTitleOffset(0.93);
   hist_datas->SetStats(0);
   hist_datas->DrawClone("PESAME");

   //save histogram in ../images/costheta/
   save_histogram(c, filename, "costheta");

}


void dmmasshisto(ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_MC, ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_datas, string filename, string rapiditylim, string canvasname){
/******************************************************************************
* 
* \brief creating Z dimuon spectrum histogram and save
* 
* @param df_MC: dataframe of the MonteCarlo datas
* @param df_datas: dataframe of the Run datas
* @param filename: name of the final file
* @param rapiditylim: limit of rapidity to write on the canvas
* @param canvasname: name of the canvas I create
* 
* \return None
* 
******************************************************************************/
   constexpr int nbins = 100; //widthbins = 0.05

   //creating new canvas
   auto c = new TCanvas(canvasname.c_str(), "", 1000, 800);

   //creating pads
   auto pad1 = new TPad("pad1","pad1",0., 0.33, 1., 1.00);
   auto pad2 = new TPad("pad2","pad2",0., 0.08, 1., 0.30);
   pad1->SetBottomMargin(0.05);
   pad1->SetBorderMode(0);
   pad1->SetLogy();
   pad2->SetTopMargin(0.00001);
   pad2->SetBottomMargin(0.25);
   pad2->SetBorderMode(0);
   pad1->Draw();
   pad2->Draw();

   //fill pad1
   pad1->cd();

   //creating a histogram
   auto hist_MC = df_MC.Histo1D({"hist_MC", "", nbins, 70, 110}, "dimuon_mass");
   auto hist_datas = df_datas.Histo1D({"hist_datas", "", nbins, 70, 110}, "dimuon_mass");
   hist_datas->Scale(1./float((df_datas.Count()).GetValue()));
   hist_MC->Scale(1./float((df_MC.Count()).GetValue()));

   //creating report
   auto report_MC = df_MC.Report();
   report_MC->Print();
   auto report_datas = df_datas.Report();
   report_datas->Print();

   //setting histogram properties
   hist_MC->GetYaxis()->SetTitle("N_{Events,norm}");
   hist_MC->GetYaxis()->SetTitleSize(0.06);
   hist_MC->GetYaxis()->SetTitleOffset(0.7);
   hist_MC->GetYaxis()->SetLabelSize(0.05);
   hist_MC->SetStats(0);
   hist_MC->SetFillColor(kOrange-3); 
   hist_MC->SetLineColor(kOrange-3); 
   hist_MC->SetLineStyle(0);
   hist_datas->SetMarkerStyle(8);
   hist_datas->SetStats(0);

   //draw the histogram
   hist_MC->DrawClone("HF3SAME");
   hist_datas->DrawClone("PESAME");
   
   //writing the rapidity limits on the histogram
   TLatex label;
   label.SetTextSize(0.04);
   label.SetTextAlign(12);
   label.SetNDC(true);
   label.SetTextAlign(11);
   label.DrawLatex(0.45, 0.8, "Z");
   label.DrawLatex(0.15, 0.84, "CMS");
   label.DrawLatex(0.15, 0.8, rapiditylim.c_str());
   label.SetTextAlign(31);
   label.DrawLatex(0.90, 0.92, "#sqrt{s} = 8 TeV, L_{int} = 18.8 fb^{-1}");

   //writing legend
   auto legend = new TLegend(0.6,0.80,0.85,0.86);
   legend->AddEntry("hist_MC","MC:Z->#mu#mu","f");
   legend->AddEntry("hist_datas","Datas","lep");
   legend->SetBorderSize(0);
   legend->SetFillColor(0);
   legend->Draw();

   //fill pad2 
   pad2->cd();

   //creating divide histo Data/MC
   hist_datas->Divide(hist_MC.GetPtr());

   //setting histogram properties
   pad2->SetGridy();
   hist_datas->GetXaxis()->SetTitle("m_{#mu#mu} (GeV)");
   hist_datas->GetYaxis()->SetTitle("Data/MC");
   hist_datas->GetXaxis()->SetLabelSize(0.12);
   hist_datas->GetYaxis()->SetLabelSize(0.08);
   hist_datas->GetYaxis()->SetLabelOffset(0.012);
   hist_datas->GetYaxis()->SetTitleSize(0.13);
   hist_datas->GetYaxis()->SetTitleOffset(0.27);
   hist_datas->GetXaxis()->SetTitleSize(0.12);
   hist_datas->GetXaxis()->SetTitleOffset(0.93);
   hist_datas->SetStats(0);
   hist_datas->DrawClone("PESAME");

   //save histogram in ../images/dimuonspectrum/
   save_histogram(c, filename, "dimuonspectrum");

}


auto operationhist( ROOT::RDF::RResultPtr<::TH2D> & histNf, ROOT::RDF::RResultPtr<::TH2D> & histDf, ROOT::RDF::RResultPtr<::TH2D> & histNb, ROOT::RDF::RResultPtr<::TH2D> & histDb){
/******************************************************************************
* 
* \brief making sum, division and rescaling of an histogram
* 
* @param histNf: 2D histogram of dimuon mass and rapidity, with costheta>0, weighted with wn
* @param histDf: 2D histogram of dimuon mass and rapidity, with costheta>0, weighted with wd
* @param histNb: 2D histogram of dimuon mass and rapidity, with costheta<0, weighted with wn
* @param histDb: 2D histogram of dimuon mass and rapidity, with costheta<0, weighted with wd
* 
* \return rescaled histogram
* 
******************************************************************************/
   //making operation on histogram
   histNf->Add(histNb.GetPtr(), -1.0);
   histDf->Add(histDb.GetPtr(), +1.0);
   histNf->Divide(histDf.GetPtr());
   histNf->Scale(0.375);

   return histNf;
}


void afbhist(ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_MC, ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_datas, int filenumber, string rapiditylim){
/******************************************************************************
* 
* \brief creating Afb histogram 
* 
* @param df_MC: dataframe of the MonteCarlo datas
* @param df_datas: dataframe of the RUN datas
* @param filenumber: number of the rapidity condition 
* @param rapiditylim: limit of rapidity to write on the canvas
* 
* \return None
* 
******************************************************************************/
   //creating two filtered datframes, one with costheta=>0, one with costheta<0
   auto df_cm_MC = df_MC.Filter("costheta<0", "backward");
   auto df_cp_MC = df_MC.Filter("costheta>=0", "forward");
   auto df_cm_datas = df_datas.Filter("costheta<0", "backward");
   auto df_cp_datas = df_datas.Filter("costheta>=0", "forward");

   //creating report
   auto report_cm_MC = df_cm_MC.Report();
   report_cm_MC->Print();
   auto report_cm_datas = df_cm_datas.Report();
   report_cm_datas->Print();
   auto report_cp_MC = df_cp_MC.Report();
   report_cp_MC->Print();
   auto report_cp_datas = df_cp_datas.Report();
   report_cp_datas->Print();

   //creating four histogram 2D of the dimuonmass and rapidity weighted with wn
   auto histDf_MC = df_cp_MC.Histo2D({"cp,Df", "", 5, 60,120,5,-2.4,2.4}, "dimuon_mass", "y", "wd");
   auto histNf_MC = df_cp_MC.Histo2D({"cp,Nf", "", 5, 60,120,5,-2.4,2.4}, "dimuon_mass", "y", "wn");
   auto histDb_MC = df_cm_MC.Histo2D({"cm,Db", "", 5, 60,120,5,-2.4,2.4}, "dimuon_mass", "y", "wd");
   auto histNb_MC = df_cm_MC.Histo2D({"cm,Nb", "", 5, 60,120,5,-2.4,2.4}, "dimuon_mass", "y", "wn");

   auto histDf_datas = df_cp_datas.Histo2D({"cp,Df", "", 5, 60,120,5,-2.4,2.4}, "dimuon_mass", "y", "wd");
   auto histNf_datas = df_cp_datas.Histo2D({"cp,Nf", "", 5, 60,120,5,-2.4,2.4}, "dimuon_mass", "y", "wn");
   auto histDb_datas = df_cm_datas.Histo2D({"cm,Db", "", 5, 60,120,5,-2.4,2.4}, "dimuon_mass", "y", "wd");
   auto histNb_datas = df_cm_datas.Histo2D({"cm,Nb", "", 5, 60,120,5,-2.4,2.4}, "dimuon_mass", "y", "wn");

   //normalizing histograms
   histDf_MC->Scale(1./float((df_cp_MC.Count()).GetValue()));
   histNf_MC->Scale(1./float((df_cp_MC.Count()).GetValue()));
   histDb_MC->Scale(1./float((df_cm_MC.Count()).GetValue()));
   histNb_MC->Scale(1./float((df_cm_MC.Count()).GetValue()));

   histDf_datas->Scale(1./float((df_cp_datas.Count()).GetValue()));
   histNf_datas->Scale(1./float((df_cp_datas.Count()).GetValue()));
   histDb_datas->Scale(1./float((df_cm_datas.Count()).GetValue()));
   histNb_datas->Scale(1./float((df_cm_datas.Count()).GetValue()));

   //operation on histogram
   auto hist_MC = operationhist(histNf_MC, histDf_MC, histNb_MC, histDb_MC);
   auto hist_datas = operationhist(histNf_datas, histDf_datas, histNb_datas, histDb_datas);
   
   //drawing two subpads
   auto pad1 = new TPad("pad1","pad1", 0.06, 0.33, 1., 1.00);
   auto pad2 = new TPad("pad2","pad2", 0.06, 0.08, 1., 0.30);
   pad1->SetBorderMode(0);
   pad2->SetTopMargin(0.00001);
   pad2->SetBorderMode(0);
   pad2->SetLeftMargin(0.17);
   pad1->SetLeftMargin(0.17);
   pad2->SetBottomMargin(0.2);
   pad1->Draw();
   pad2->Draw();

   //fill pad1 with the projections
   pad1->cd();
   
   //projection of the final histogram
   auto h_MC = hist_MC->ProjectionX("MC");
   auto h_datas = hist_datas->ProjectionX("datas");

   //graphical set
   h_MC->SetStats(0); 
   h_datas->SetStats(0);

   h_MC->SetLineColor(2);
   h_MC->GetXaxis()->SetTitle("m_{#mu#mu} (GeV)");
   h_MC->GetYaxis()->SetTitle("Afb");

   h_MC->GetXaxis()->CenterTitle(true);
   h_MC->GetYaxis()->CenterTitle(true);

   h_MC->GetXaxis()->SetTitleSize(0.13);
   h_MC->GetXaxis()->SetNdivisions(505);
   h_MC->GetXaxis()->SetLabelFont(42);
   h_MC->GetXaxis()->SetLabelSize(0.11);
   h_MC->GetXaxis()->SetLabelOffset(-0.055);
   h_MC->GetXaxis()->SetTitleOffset(0.34);
   h_MC->GetXaxis()->SetTickLength(0.05);

   h_MC->GetYaxis()->SetRangeUser(-1.2, 1.2);
   h_MC->GetYaxis()->SetLabelSize(0.09);
   h_MC->GetYaxis()->SetTitleSize(0.13);
   h_MC->GetYaxis()->SetLabelOffset(0.01);
   h_MC->GetYaxis()->SetTitleOffset(0.6);
   h_MC->GetYaxis()->SetTickLength(0.05);
   
   h_datas->SetMarkerColor(1); 
   h_datas->SetLineColor(1); 
   h_datas->SetMarkerStyle(8); 

   //drawing the final histogram
   h_MC->DrawClone("HIST SAME");
   h_datas->DrawClone("P SAME");

   //legend only on the first pad
   if (filenumber == 1){

      auto legend = new TLegend(0.30, 0.30, 0.50, 0.45);
      legend->AddEntry(h_MC, "MC", "l");
      legend->AddEntry(h_datas, "Datas", "lep");
      legend->SetBorderSize(0);
      legend->SetFillColor(0);
      legend->SetTextSize(0.13);
      legend->Draw();

   }

   //label on the histogram
   TLatex label;
   label.SetTextSize(0.11);
   label.SetTextAlign(12);
   label.SetNDC(true);
   label.DrawLatex(0.3, 0.2, rapiditylim.c_str());

   //residual pad
   pad2->cd();
   pad2->SetGridy();
   
   //creating histo Data-MC
   h_datas->Add(h_MC, -1.0);

   //setting histogram properties
   h_datas->SetStats(0);
   
   h_datas->GetXaxis()->SetTitle("m_{#mu#mu} (GeV)");
   h_datas->GetXaxis()->SetLabelSize(0.10);
   h_datas->GetXaxis()->SetNdivisions(505);
   h_datas->GetXaxis()->SetTitleSize(0.11);
   h_datas->GetXaxis()->SetTitleOffset(0.86);
   
   h_datas->GetYaxis()->SetTitle("Data-MC");
   h_datas->GetYaxis()->SetLabelSize(0.08);
   h_datas->GetYaxis()->SetNdivisions(505);
   h_datas->GetYaxis()->SetTitleOffset(0.6);
   h_datas->GetYaxis()->SetTitleSize(0.12);

   h_datas->DrawClone("PESAME");
}
#endif /* GRAPHICAL_UTILITIES_H */