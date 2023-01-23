#include <filesystem>
#include <string>

void save_histogram(TCanvas *c, string namehist, string type){
   namespace fs = std::filesystem;
   type = "/" + type;
   string subpath = "../images" + type;
   string filepath =  subpath + "/"  + namehist + ".pdf"; // define path where to save plot
   try { //The try statement allows you to define a block of code to be tested for errors while it is being executed.                                         // save canvas in filepath
      if (!fs::is_directory("../images") || !fs::exists("../images")) // if directory does not exist
         throw("../images");//The throw keyword throws an exception when a problem is detected, which lets us create a custom error.                                        // throw exception
   } catch (const char *path) { //The catch statement allows you to define a block of code to be executed, if an error occurs in the try block.
      std::cerr << "The folder " << path << " does not exist.\n" << std::endl;
      std::cerr << "Creating folder...\n" << std::endl;
      fs::create_directory(path); // create directory
      std::cout << "The folder " << path << " successfully created\n" << std::endl;
   }
   try {          
      c->SaveAs(filepath.c_str());                              
      if (!fs::is_directory(subpath.c_str()) || !fs::exists(subpath.c_str())) // if directory does not exist
         throw(subpath.c_str());
   }catch(const char *newpath){
      std::cerr << "The folder " << newpath << " does not exist.\n" << std::endl;
      std::cerr << "Creating folder...\n" << std::endl;
      fs::create_directory(newpath);
      std::cout << "The folder " << newpath << " successfully created\n" << std::endl;
      c->SaveAs(filepath.c_str());
   }
}


//There is a special catch block called the ‘catch all’ block, written as catch(…), 
//that can be used to catch all types of exceptions.
// For example, in the following program, an int is thrown as an exception, 
//but there is no catch block for int, so the catch(…) block will be executed. 


void coshisto(ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df, string filename, string rapiditylim, float x1, float y1, float x2, float y2,string canvasname){
   
   constexpr int nbins = 40; //widthbins = 0.05

   //creating new canvas
   auto c = new TCanvas(canvasname.c_str(), "", 1000,800);

   //creating a histogram
   auto hist = df.Histo1D({"hist", "", nbins, -1, 1}, "costheta");

   //setting histogram properties
   hist->SetFillColor(kOrange-3); 
   hist->SetLineColor(kOrange-3); 
   hist->SetMarkerStyle(20);
   hist->SetMarkerColor(kBlack); 
   hist->SetLineStyle(0);
   hist->GetXaxis()->SetTitle("cos(#theta*)");
   hist->GetXaxis()->SetTitleSize(0.04);
   hist->GetYaxis()->SetTitle("N_{Events} MC");
   hist->GetYaxis()->SetTitleSize(0.04);
   hist->SetStats(0);

   //draw the histogram
   hist->DrawClone("PHF3");

   //writing the rapidity limits on the histogram
   TLatex label;
   label.SetTextSize(0.04);
   label.SetNDC(true);
   label.DrawLatex(0.15, 0.96, "CMS");
   label.DrawLatex(0.15, 0.925, rapiditylim.c_str());
   label.DrawLatex(0.6, 0.94, "#sqrt{s} = 8 TeV, L_{int} = 18.8 fb^{-1}");

   //writing legend
   auto legend = new TLegend(x1,y1,x2,y2);
   legend->AddEntry("hist","MC:Z->#mu#mu","f");
   legend->SetBorderSize(0);
   legend->SetFillColor(0);
   legend->Draw();

   //save histogram in ../images/costheta/
   save_histogram(c, filename, "costheta");

}

void dmmasshisto(ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter, void> df, string filename, string rapiditylim,string canvasname){
   
   constexpr int nbins = 100; //widthbins = 0.05

   //creating new canvas
   auto c = new TCanvas(canvasname.c_str(), "", 1000,800);

   //creating a histogram
   auto hist = df.Histo1D({"hist", "", nbins, 70, 110}, "dimuon_mass");

   //creating report
   auto report = df.Report();
   report->Print();

   //setting histogram properties
   hist->GetXaxis()->SetTitle("m_{#mu#mu} (GeV)");
   hist->GetXaxis()->SetTitleSize(0.04);
   hist->GetYaxis()->SetTitle("N_{Events}");
   hist->GetYaxis()->SetTitleSize(0.04);
   hist->SetStats(0);
   hist->SetFillColor(kOrange-3); 
   hist->SetLineColor(kOrange-3); 
   hist->SetMarkerStyle(20);
   hist->SetMarkerColor(kBlack); 
   hist->SetLineStyle(0);

   //setting semilog histo
   c->SetLogy();

   //draw the histogram
   hist->DrawClone("PHF3");

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
   auto legend = new TLegend(0.65,0.80,0.85,0.86);
   legend->AddEntry("hist","MC:Z->#mu#mu","f");
   legend->SetBorderSize(0);
   legend->SetFillColor(0);
   legend->Draw();

   //save histogram in ../images/dimuonspectrum/
   save_histogram(c, filename, "dimuonspectrum");

}