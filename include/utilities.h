/******************************************************************************
* 
* \file utilities.h
* \brief Utilities to define new columns on the dataframe
* 
******************************************************************************/
#ifndef UTILITIES_H
#define UTILITIES_H

#include <ROOT/RDataFrame.hxx>
#include "ROOT/RVec.hxx"
#include "Math/Vector4Dfwd.h"
#include "Math/Vector4D.h"

using namespace ROOT::VecOps;

ROOT::Math::PtEtaPhiMVector quadrivectot(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass){
/******************************************************************************
* 
* \brief Creating a fourvector of the dimuon system
* 
* @param pt: Column pt of the dataframe
* @param eta: Column eta of the dataframe
* @param phi: Column phi of the dataframe
* @param mass: Column mass of the dataframe
* 
* \return Dimuon system fourvector
* 
******************************************************************************/

    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);

    return m1+m2;

}


ROOT::Math::PtEtaPhiMVector quadrivec1(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass){
/******************************************************************************
* 
* \brief Creating a fourvector of the first muon 
* 
* @param pt: Column pt of the dataframe
* @param eta: Column eta of the dataframe
* @param phi: Column phi of the dataframe
* @param mass: Column mass of the dataframe
* 
* \return First muon fourvector
* 
******************************************************************************/
    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);

    return m1;

}


ROOT::Math::PtEtaPhiMVector quadrivec2(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass){
/******************************************************************************
* 
* \brief Creating a fourvector of the second muon
* 
* @param pt: Column pt of the dataframe
* @param eta: Column eta of the dataframe
* @param phi: Column phi of the dataframe
* @param mass: Column mass of the dataframe
* 
* \return Second muon fourvector
* 
******************************************************************************/
    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);

    return m2;

}


auto allquantities(ROOT::RDataFrame df){
/******************************************************************************
* 
* \brief Creating all the quantities necessary for the analysis
* 
* @param df: Dataframe we need to process
* 
* \return Dataframe with added column
* 
******************************************************************************/

    auto df_2mu_MC = df.Define("quadrivectot", quadrivectot,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    df_2mu_MC = df_2mu_MC.Define("quadrivec1", quadrivec1,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    df_2mu_MC = df_2mu_MC.Define("quadrivec2", quadrivec2,{"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});

    df_2mu_MC = df_2mu_MC.Define("dimuon_mass", "quadrivectot.mass()");

    df_2mu_MC = df_2mu_MC.Define("y","quadrivectot.Rapidity()");

    df_2mu_MC = df_2mu_MC.Define("ptll","quadrivectot.Pt()");

    df_2mu_MC = df_2mu_MC.Define("Pztot","quadrivectot.Pz()");

    df_2mu_MC = df_2mu_MC.Define("Pz1", "quadrivec1.Pz()");

    df_2mu_MC = df_2mu_MC.Define("Pz2", "quadrivec2.Pz()");

    df_2mu_MC = df_2mu_MC.Define("E", "quadrivectot.E()");

    df_2mu_MC = df_2mu_MC.Define("E1", "quadrivec1.E()");

    df_2mu_MC = df_2mu_MC.Define("E2", "quadrivec2.E()");

    df_2mu_MC = df_2mu_MC.Define("Pp1","(E1+Pz1)/pow(2,0.5)");

    df_2mu_MC = df_2mu_MC.Define("Pp2","(E2+Pz2)/pow(2,0.5)");

    df_2mu_MC = df_2mu_MC.Define("Pm1","(E1-Pz1)/pow(2,0.5)");

    df_2mu_MC = df_2mu_MC.Define("Pm2","(E2-Pz2)/pow(2,0.5)");

    df_2mu_MC = df_2mu_MC.Define("costheta", "2*(Pp1*Pm2-Pm1*Pp2)*Pztot/(pow(pow(dimuon_mass,2)*(pow(dimuon_mass,2)+pow(ptll,2)),0.5)*fabs(Pztot))");

    return df_2mu_MC;
}
#endif /* UTILITIES_H */
