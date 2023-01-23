#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "utilities.h"
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

void test_energy_formulas(){
    /*
    Testing if E**2 corresponds to m**2+p**2
    */
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df("Events_new", "Events.root");

    auto df_2mu= allquantities(df);

    auto df_2mucontrol=df_2mu.Define("Px1",computepx1,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol=df_2mucontrol.Define("Py1",computepy1,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol=df_2mucontrol.Define("Py2",computepy2,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol=df_2mucontrol.Define("Px2",computepx2,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    df_2mucontrol=df_2mucontrol.Define("energynew1","pow(pow(Muon_mass[0],2)+pow(Px1,2)+pow(Py1,2)+pow(Pz1,2),0.5)");
    df_2mucontrol=df_2mucontrol.Define("energynew2","pow(pow(Muon_mass[0],2)+pow(Px2,2)+pow(Py2,2)+pow(Pz2,2),0.5)");

    //testing if E1 and E2 are almost equal to their formulas
    auto df_2mucontrol2=df_2mucontrol.Filter("fabs(energynew1-E1)>0.001 || fabs(energynew2-E2)>0.001","control");
    
    auto nEntries=df_2mucontrol2.Count();
    if( nEntries.GetValue()==0){
        printf("test passed!");
    }
    else{
        printf("test failed!");
    }
}