#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "../src/utilities.h"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <vector>

float computepx1(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { 
    
    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the dimuon Px1
    */

    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);

    return (m1).Px();
}
float computepy1(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { 
    
    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the dimuon Py1
    */

    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);

    return (m1).Py();
}


float computepx2(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { 
    
    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the dimuon Px2
    */

    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);

    return (m2).Px();
}
float computepy2(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { 
    
    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the dimuon Py2 
    */

    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);

    return (m2).Py();
}

void test_energy_formulas(std::string filepath_MC, std::string filepath_datas){
    /*
    Testing if E**2 corresponds to m**2+p**2
    */
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df_MC("Events", filepath_MC);
    ROOT::RDataFrame df_datas("Events", filepath_datas);

    auto df_2mu_MC = allquantities(df_MC);
    auto df_2mu_datas = allquantities(df_datas);

    auto df_2mucontrol_MC=df_2mu_MC.Define("Px1",computepx1,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol_MC=df_2mucontrol_MC.Define("Py1",computepy1,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol_MC=df_2mucontrol_MC.Define("Py2",computepy2,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol_MC=df_2mucontrol_MC.Define("Px2",computepx2,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol_MC=df_2mucontrol_MC.Define("energynew1","pow(pow(Muon_mass[0],2)+pow(Px1,2)+pow(Py1,2)+pow(Pz1,2),0.5)");
    df_2mucontrol_MC=df_2mucontrol_MC.Define("energynew2","pow(pow(Muon_mass[0],2)+pow(Px2,2)+pow(Py2,2)+pow(Pz2,2),0.5)");

    auto df_2mucontrol_datas=df_2mu_datas.Define("Px1",computepx1,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol_datas=df_2mucontrol_datas.Define("Py1",computepy1,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol_datas=df_2mucontrol_datas.Define("Py2",computepy2,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol_datas=df_2mucontrol_datas.Define("Px2",computepx2,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol_datas=df_2mucontrol_datas.Define("energynew1","pow(pow(Muon_mass[0],2)+pow(Px1,2)+pow(Py1,2)+pow(Pz1,2),0.5)");
    df_2mucontrol_datas=df_2mucontrol_datas.Define("energynew2","pow(pow(Muon_mass[0],2)+pow(Px2,2)+pow(Py2,2)+pow(Pz2,2),0.5)");

    //testing if E1 and E2 are almost equal to their formulas
    auto df_2mucontrol2_MC=df_2mucontrol_MC.Filter("fabs(energynew1-E1)>0.00001*E1 || fabs(energynew2-E2)>0.00001*E2 ","control");
    auto df_2mucontrol2_datas=df_2mucontrol_datas.Filter("fabs(energynew1-E1)>0.00001*E1 || fabs(energynew2-E2)>0.00001*E2 ","control");

    auto nEntries_MC=df_2mucontrol2_MC.Count();
    auto nEntries_datas=df_2mucontrol2_datas.Count();

    printf("testing if E_i^2 is almost equal to m^2+p_i^2 \n");

    if( nEntries_datas.GetValue()==0 && nEntries_MC.GetValue()==0){
        printf("test passed!\n");
    }
    else{
        printf("test failed!\n");
    }
}