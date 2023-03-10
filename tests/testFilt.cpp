/******************************************************************************
* 
* \file testFilt.cpp
* \brief Testing if the filter function works
* 
******************************************************************************/
#include "../src/filterDf.cpp"
#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <iostream>
#include <filesystem>

void testFilt(){
/******************************************************************************
* 
* \brief Testing if the filter function works
*
* \return None
* 
******************************************************************************/
    namespace fs = std::filesystem;
    //checking if datas exists
    if (!fs::is_directory("datas") || !fs::exists("datas")) {
        fs::create_directory("datas");
    }

    //creating an empty dataframe with all columns and an empty dataframe with a missing column
    TFile file1("datas/SimpleTree1.root", "RECREATE"); 
    TTree * tree1 = new TTree("Events", "Events");

    //random numbers 
    float n=2.,f[2]={1.,2.};
    int v[2]={3,3};

    tree1->Branch("Muon_dxy",f,"f[2]/F");
    tree1->Branch("Muon_pfRelIso03_chg",f,"f[2]/F");
    tree1->Branch("nMuon",&n,"n/F");
    tree1->Branch("Muon_eta",f,"f[2]/F");
    tree1->Branch("Muon_charge",v,"v[2]/I");
    tree1->Branch("Muon_pt",f,"f[2]/F");
    tree1->Branch("Muon_phi",f,"f[2]/F");
    tree1->Write(); 
    file1.Close();
    
    TFile file("datas/SimpleTree.root", "RECREATE"); 
    TTree * tree = new TTree("Events","Events");
    tree->Branch("Muon_dxy",f,"f[2]/F");
    tree->Branch("Muon_pfRelIso03_chg",f,"f[2]/F");
    tree->Branch("nMuon",&n,"n/F");
    tree->Branch("Muon_eta",f,"f[2]/F");
    tree->Branch("Muon_charge",v,"v[2]/I");
    tree->Branch("Muon_pt",f,"f[2]/F");
    tree->Branch("Muon_phi",f,"f[2]/F");
    tree->Branch("Muon_mass",f,"f[2]/F");
    tree->Write(); 
    file.Close();

    //test on number of columns
    int test0 = filterDf("datas/SimpleTree1.root", "datas/SimpleTree1.root", "MC.root", "dat.root");//few column 
    int test1 = filterDf("datas/SimpleTree.root", "datas/SimpleTree1.root", "MC.root", "dat.root");//looking for one file with few columns and one empty
    int test2 = filterDf("datas/SimpleTree1.root", "datas/SimpleTree.root", "MC.root", "dat.root");//looking for one file with few columns and one empty
    
    //test on empty files
    int test3 = filterDf("datas/SimpleTree.root", "datas/SimpleTree.root", "MC.root", "dat.root");//looking for two empty files
    int test4 = filterDf("datas/SimpleTree.root", "root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola/0A55428E-3FFA-40D8-ABDE-BD877B402134.root", "MC.root", "dat.root");//looking for one empty file
    int test5 = filterDf("root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola/0A55428E-3FFA-40D8-ABDE-BD877B402134.root", "datas/SimpleTree.root", "MC.root", "dat.root");//looking for one empty file
    
    //test on files with wrong path
    int test6 = filterDf("datas/file.root", "datas/file.root", "MC.root", "dat.root"); //looking for files that don't exist
    int test7 = filterDf("dati/SimpleTree.root", "datas/file.root", "MC.root", "dat.root"); //looking for a file exist and a file that doesn't exist
    int test8 = filterDf("datas/file.root", "dati/SimpleTree.root", "MC.root", "dat.root"); //looking for a file exist and a file that doesn't exist
    int test9 = filterDf("dati/file.root", "dati/file.root", "MC.root", "dat.root"); //looking for a file and a folder that don't exist
    int test10 = filterDf("dati/SimpleTree.root", "dati/SimpleTree.root", "MC.root", "dat.root");//looking for a folder that doesn't exist
    int test11 = filterDf("root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola/0A55428E-3FFA-40D8-ABDE-BD877B402134.root", "root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola/0A55428E-3FFA-40D8-ABDE-BD877B402134.root", "MC.root", "dat.root"); //looking for a file and a folder that exist

    //test on files with a wrong extension
    TFile file2("datas/filedummy.txt", "RECREATE");
    int test12 = filterDf("datas/filedummy.txt", "datas/filedummy.txt", "MC.root", "dat.root");//two files with wrong extention
    int test13 = filterDf("root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola/0A55428E-3FFA-40D8-ABDE-BD877B402134.root", "datas/filedummy.txt", "MC.root", "dat.root");//second file with wrong extention
    int test14 = filterDf("datas/filedummy.txt", "root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola/0A55428E-3FFA-40D8-ABDE-BD877B402134.root", "MC.root", "dat.root");//first file with wrong extention
  
    if(test0 == 2 && test1 == 2 && test2 == 2 && test3 == 3 && test4 == 3 && test5 == 3 && test11 == 0 && test6 == 1 && test7 == 1 && test8 == 1 && test9 == 1 && test10 == 1 && test12 == 1 && test13 == 1 && test14 == 1){
        std::cout << "Test passed!" << std::endl;
    }else{
        std::cout << "Test failed!" << std::endl;
    }
}