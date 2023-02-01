/******************************************************************************
* 
* \file graphical_utilities.h
* \brief Graphical utilities for displaying histograms of Afb, Z spectrum, cos(theta*)
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
   string filepath_pdf =  subpath + "/"  + namehist + ".pdf"; 
   string filepath_png =  subpath + "/"  + namehist + ".png"; 
   
   //if the folder "images" doesn't exist, it will create it
   try {                                        
      if (!fs::is_directory("images") || !fs::exists("images")) 
         throw("images");
   } catch (const char *path) { 
      std::cerr << "The folder " << path << " does not exist.\n" << std::endl;
      std::cerr << "Creating folder...\n" << std::endl;
      fs::create_directory(path); 
      std::cout << "The folder " << path << " successfully created\n" << std::endl;
   }

   //if the subfolder "type" doesn't exist, it will create it
   try {          
      c->SaveAs(filepath_pdf.c_str());
      c->SaveAs(filepath_png.c_str());                          
      if (!fs::is_directory(subpath.c_str()) || !fs::exists(subpath.c_str())) 
         throw(subpath.c_str());
   }catch(const char *newpath){
      std::cerr << "The folder " << newpath << " does not exist.\n" << std::endl;
      std::cerr << "Creating folder...\n" << std::endl;
      fs::create_directory(newpath);
      std::cout << "The folder " << newpath << " successfully created\n" << std::endl;
      c->SaveAs(filepath_pdf.c_str());
      c->SaveAs(filepath_png.c_str());
   }
}


void coshisto(ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_MC,ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_datas, string filename, string rapiditylim, float x1, float y1, float x2, float y2,string canvasname){
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
   auto c = new TCanvas(canvasname.c_str(), "", 1000,800);

   //creating pads
   auto pad1 = new TPad("pad1","pad1",0,0.33,1,1);
   auto pad2 = new TPad("pad2","pad2",0,0.08,1,0.30);
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
   hist_datas->Scale(1/float((df_datas.Count()).GetValue()));
   hist_MC->Scale(1/float((df_MC.Count()).GetValue()));

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
   auto legend = new TLegend(x1,y1,x2,y2);
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


void dmmasshisto(ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_MC,ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_datas, string filename, string rapiditylim,string canvasname){
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
   auto c = new TCanvas(canvasname.c_str(), "", 1000,800);

   //creating pads
   auto pad1 = new TPad("pad1","pad1",0,0.33,1,1);
   auto pad2 = new TPad("pad2","pad2",0,0.08,1,0.30);
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
   hist_datas->Scale(1/float((df_datas.Count()).GetValue()));
   hist_MC->Scale(1/float((df_MC.Count()).GetValue()));

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


auto operationhist( ROOT::RDF::RResultPtr<::TH2D> & histNf, ROOT::RDF::RResultPtr<::TH2D> & histDf,ROOT::RDF::RResultPtr<::TH2D> & histNb, ROOT::RDF::RResultPtr<::TH2D> & histDb){
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
   histNf->Add(histNb.GetPtr(),-1.0);
   histDf->Add(histDb.GetPtr(),+1.0);
   histNf->Divide(histDf.GetPtr());
   histNf->Scale(0.375);

   return histNf;
}


void afbhist(ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df_MC, string filename, string rapiditylim){
/******************************************************************************
* 
* \brief creating Afb histogram 
* 
* @param df_MC: dataframe of the MonteCarlo datas
* @param filename: name of the final file
* @param rapiditylim: limit of rapidity to write on the canvas
* 
* \return None
* 
******************************************************************************/
   //creating two filtered datframes, one with costheta=>0, one with costheta<0
   auto df_cm_MC=df_MC.Filter("costheta<0", "backward");
   auto df_cp_MC=df_MC.Filter("costheta>=0", "forward");
   
   //creating four histogram 2D of the dimuonmass and rapidity weighted with wn
   auto histDf_MC = df_cp_MC.Histo2D({"cp,Df", "", 5, 60,120,5,-2.4,2.4},"dimuon_mass","y","wd");
   auto histNf_MC = df_cp_MC.Histo2D({"cp,Nf", "", 5, 60,120,5,-2.4,2.4},"dimuon_mass","y","wn");
   auto histDb_MC = df_cm_MC.Histo2D({"cm,Db", "", 5, 60,120,5,-2.4,2.4},"dimuon_mass","y","wd");
   auto histNb_MC = df_cm_MC.Histo2D({"cm,Nb", "", 5, 60,120,5,-2.4,2.4},"dimuon_mass","y","wn");

   //operation on histogram
   auto hist_MC=operationhist(histNf_MC, histDf_MC, histNb_MC, histDb_MC);
   
   //projection of the final histogram
   auto h_MC= hist_MC->ProjectionX();

   //graphical set
   h_MC->SetStats(0);;
   h_MC->SetMarkerStyle(8);
   h_MC->SetMarkerColor(1);

   h_MC->GetXaxis()->SetTitle("m_{#mu#mu}");
   h_MC->GetYaxis()->SetTitle("Afb MC");

   h_MC->GetXaxis()->CenterTitle(true);
   h_MC->GetYaxis()->CenterTitle(true);

   h_MC->GetXaxis()->SetTitleSize(0.13);
   h_MC->GetXaxis()->SetNdivisions(505);
   h_MC->GetXaxis()->SetLabelFont(42);
   h_MC->GetXaxis()->SetLabelSize(0.11);
   h_MC->GetXaxis()->SetLabelOffset(-0.055);
   h_MC->GetXaxis()->SetTitleOffset(0.34);
   h_MC->GetXaxis()->SetTickLength(0.05);

   
   h_MC->GetYaxis()->SetLabelSize(0.09);
   h_MC->GetYaxis()->SetTitleSize(0.11);
   h_MC->GetYaxis()->SetTitleOffset(0.66);
   h_MC->GetYaxis()->SetTickLength(0.05);

   //drawing the final histogram
   h_MC->DrawClone("PSAME");

   //label on the histogram
   TLatex label;
   label.SetTextSize(0.1);
   label.SetTextAlign(12);
   label.SetNDC(true);
   label.DrawLatex(0.3, 0.85, rapiditylim.c_str());
}
#endif /* GRAPHICAL_UTILITIES_H */