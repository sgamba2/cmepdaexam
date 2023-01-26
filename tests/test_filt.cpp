#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "../src/filter_df.cpp"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <vector>

void test_filt(){
    /*
    Testing when a dataframe is empty
    */
    TFile file1("../datas/SimpleTree1.root","RECREATE"); 
    TTree * tree1 = new TTree("Events","Events");

    //random numbers
    float f[2];
    f[0]=777;
    f[1]=88; 
    float n=7;
    tree1->Branch("Muon_dxy",f,"f[2]/F");
    tree1->Branch("Muon_pfRelIso03_chg",f,"f[2]/F");
    tree1->Branch("nMuon",&n,"f/F");
    tree1->Branch("Muon_eta",f,"f[2]/F");
    tree1->Branch("Muon_charge",f,"f[2]/F");
    tree1->Branch("Muon_pt",f,"f[2]/F");
    tree1->Branch("Muon_phi",f,"f[2]/F");
    tree1->Write(); 
    file1.Close();
    
    TFile file("../datas/SimpleTree.root","RECREATE"); 
    TTree * tree = new TTree("Events","Events");
    tree->Branch("Muon_dxy",f,"f[2]/F");
    tree->Branch("Muon_pfRelIso03_chg",f,"f[2]/F");
    tree->Branch("nMuon",&n,"f/F");
    tree->Branch("Muon_eta",f,"f[2]/F");
    tree->Branch("Muon_charge",f,"f[2]/F");
    tree->Branch("Muon_pt",f,"f[2]/F");
    tree->Branch("Muon_phi",f,"f[2]/F");
    tree->Branch("Muon_mass",f,"f[2]/F");
    tree->Write(); 
    file.Close();

    //test on number of columns
    int test0 = filter_df("../datas/SimpleTree1.root","../datas/SimpleTree1.root");//few column 
    int test1 = filter_df("../datas/SimpleTree.root","../datas/SimpleTree1.root");//looking for one file with few columns and one empty
    int test2 = filter_df("../datas/SimpleTree1.root","../datas/SimpleTree.root");//looking for one file with few columns and one empty
    
    //test on empty files
    int test3 = filter_df("../datas/SimpleTree.root","../datas/SimpleTree.root");//looking for two empty files
    int test4 = filter_df("../datas/SimpleTree.root","../datas/00C074C0-1C19-4933-9407-5A05484E1F1E.root");//looking for one empty file
    int test5 = filter_df("../datas/00C074C0-1C19-4933-9407-5A05484E1F1E.root","../datas/SimpleTree.root");//looking for one empty file
    
    //file che non hanno path giusto
    int test6 = filter_df("../datas/file.root","../datas/file.root"); //looking for files that don't exist
    int test7 = filter_df("../dati/00C074C0-1C19-4933-9407-5A05484E1F1E.root","../datas/file.root"); //looking for a file exist and a file that doesn't exist
    int test8 = filter_df("../datas/file.root","../dati/00C074C0-1C19-4933-9407-5A05484E1F1E.root"); //looking for a file exist and a file that doesn't exist
    int test9 = filter_df("../dati/file.root","../dati/file.root"); //looking for a file and a folder that don't exist
    int test10 = filter_df("../dati/00C074C0-1C19-4933-9407-5A05484E1F1E.root","../dati/00C074C0-1C19-4933-9407-5A05484E1F1E.root");//looking for a folder that doesn't exist
    int test11 = filter_df("../datas/00C074C0-1C19-4933-9407-5A05484E1F1E.root","../datas/00C074C0-1C19-4933-9407-5A05484E1F1E.root"); //looking for a file and a folder that exist

    //if they have a wrong extension
    TFile file2("../datas/filedummy.txt","RECREATE");
    int test12 = filter_df("../datas/filedummy.txt","../datas/filedummy.txt");
    int test13 = filter_df("../datas/00C074C0-1C19-4933-9407-5A05484E1F1E.root","../datas/filedummy.txt");
    int test14 = filter_df("../datas/filedummy.txt","../datas/00C074C0-1C19-4933-9407-5A05484E1F1E.root");
    

    if(test0==2 && test1==2 && test2==2 && test3==4 && test4==5 && test5==6 && test11==0 && test6==1 && test7==1 && test8==1 && test9==1 && test10==1 && test12==1 && test13==1 && test14==1){
        printf("test passed!");
    }else{
        printf("test failed!");
    }
}