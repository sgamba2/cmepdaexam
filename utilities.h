#ifndef UTILITIES_H
#define UTILITIES_H
#include <ROOT/RDataFrame.hxx>
#include "ROOT/RVec.hxx"
#include "Math/Vector4Dfwd.h"
#include "Math/Vector4D.h"


using namespace ROOT::VecOps;

float computeInvariantMass(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { 

    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates the four vector and it returns the dimuon invariant mass 
    */
    
    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);
   
    return (m1 + m2).mass();   
}

float computepztot(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { 

    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a four vector and it returns the dimuon Pz 
    */
    
    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);

    return (m1+m2).Pz();
}

float computepz1(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { 

    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the first muon Pz 
    */
    
    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    
    return m1.Pz();
}

float computepz2(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { 
    
    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the second muon Pz 
    */

    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);

    return m2.Pz();
}

float computeEtot(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { //
    
     /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the energy of the dimuon system
    */

    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);

    return (m2+m1).E();
}

float computeE1(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { //
    
    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the first muon energy
    */

    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    
    return m1.E();
}

float computeE2(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { //
    
    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the second muon energy 
    */

    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);

    return m2.E();
}

float computey(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) { //
    
    /*
    Parameters
    ----------
    pt : Muon_pt of the dataframe
    eta : Muon_eta of the dataframe
    phi : Muon_phi of the dataframe
    mass : Muon_mass of the dataframe

    Returns
    ---------
    It creates a fourvector and it returns the dimuon rapidity
    */

    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);

    return (m1 + m2).Rapidity();
}

auto allquantities(ROOT::RDataFrame df){

    /*
    Parameters
    ----------
    df: Dataframe of the events 

    Returns
    ---------
    It returns the first node of the computation graph for which the new quantity is defined.
    This function adds new columns to the input dataframe, with new values as total energy or pz, 
    first or second muon energy or pz, total rapidity, cos(theta*), pm1,pp1,pm2,pp2
    */
    
    auto df_2mu_MC=df.Define("ptll","pow(pow(Muon_pt[0],2)+pow(Muon_pt[1],2),0.5)");

    df_2mu_MC=df_2mu_MC.Define("dimuon_mass", computeInvariantMass,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    df_2mu_MC=df_2mu_MC.Define("Pztot", computepztot,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    df_2mu_MC=df_2mu_MC.Define("Pz1", computepz1,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
  
    df_2mu_MC=df_2mu_MC.Define("Pz2", computepz2,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    df_2mu_MC=df_2mu_MC.Define("E", computeEtot,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    df_2mu_MC=df_2mu_MC.Define("E1", computeE1,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    df_2mu_MC=df_2mu_MC.Define("E2", computeE2,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
  
    df_2mu_MC=df_2mu_MC.Define("y", computey,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    df_2mu_MC=df_2mu_MC.Define("Pp1","(E1+Pz1)/pow(2,0.5)");

    df_2mu_MC=df_2mu_MC.Define("Pp2","(E2+Pz2)/pow(2,0.5)");

    df_2mu_MC=df_2mu_MC.Define("Pm1","(E1-Pz1)/pow(2,0.5)");

    df_2mu_MC=df_2mu_MC.Define("Pm2","(E2-Pz2)/pow(2,0.5)");

    df_2mu_MC=df_2mu_MC.Define("costheta", "2*(Pp1*Pm2-Pm1*Pp2)*Pztot/(pow(pow(dimuon_mass,2)*(pow(dimuon_mass,2)+pow(ptll,2)),0.5)*fabs(Pztot))");

    return df_2mu_MC;
}
#endif
