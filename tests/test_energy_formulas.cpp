/******************************************************************************
* 
* \file test_energy_formulas.cpp
* \brief Testing if E_i^2=m^2+p_i^2
* 
******************************************************************************/
#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "../include/utilities.h"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <vector>
#include <iostream>

void test_energy_formulas(std::string filepath_MC, std::string filepath_datas){
/******************************************************************************
* 
* \brief Testing if the sum of E_i^2=m^2+p_i^2
*
* @param filepath_MC: dataframe of the MC datas
* @param filepath_datas: dataframe of the Run datas
*
* \return None
* 
******************************************************************************/
    if(TFile::Open(filepath_datas.c_str())!=nullptr && TFile::Open(filepath_MC.c_str())!=nullptr){
        //creating dataframes
        ROOT::RDataFrame df_MC("Events", filepath_MC);
        ROOT::RDataFrame df_datas("Events", filepath_datas);

        //checking if they have the right column
        if( df_MC.HasColumn("Muon_pt") && df_MC.HasColumn("Muon_mass") && df_MC.HasColumn("Muon_phi") && df_MC.HasColumn("Muon_eta") &&  df_datas.HasColumn("Muon_pt") && df_datas.HasColumn("Muon_mass") && df_datas.HasColumn("Muon_phi")  && df_datas.HasColumn("Muon_eta") ){
            //defining all quantities
            auto df_2mu_MC = allquantities(df_MC);
            auto df_2mu_datas = allquantities(df_datas);

            auto df_2mucontrol_MC=df_2mu_MC.Define("Px1","quadrivec1.Px()");
            df_2mucontrol_MC=df_2mucontrol_MC.Define("Py1","quadrivec1.Py()");
            df_2mucontrol_MC=df_2mucontrol_MC.Define("Py2","quadrivec2.Py()");
            df_2mucontrol_MC=df_2mucontrol_MC.Define("Px2","quadrivec2.Px()");
            df_2mucontrol_MC=df_2mucontrol_MC.Define("energynew1","pow(pow(Muon_mass[0],2)+pow(Px1,2)+pow(Py1,2)+pow(Pz1,2),0.5)");
            df_2mucontrol_MC=df_2mucontrol_MC.Define("energynew2","pow(pow(Muon_mass[0],2)+pow(Px2,2)+pow(Py2,2)+pow(Pz2,2),0.5)");

            auto df_2mucontrol_datas=df_2mu_datas.Define("Px1","quadrivec1.Px()");
            df_2mucontrol_datas=df_2mucontrol_datas.Define("Py1","quadrivec1.Py()");
            df_2mucontrol_datas=df_2mucontrol_datas.Define("Py2","quadrivec2.Py()");
            df_2mucontrol_datas=df_2mucontrol_datas.Define("Px2","quadrivec2.Px()");
            df_2mucontrol_datas=df_2mucontrol_datas.Define("energynew1","pow(pow(Muon_mass[0],2)+pow(Px1,2)+pow(Py1,2)+pow(Pz1,2),0.5)");
            df_2mucontrol_datas=df_2mucontrol_datas.Define("energynew2","pow(pow(Muon_mass[0],2)+pow(Px2,2)+pow(Py2,2)+pow(Pz2,2),0.5)");

            //testing if E1 and E2 are almost equal to their formulas E^2=m^2+p^2
            auto df_2mucontrol2_MC=df_2mucontrol_MC.Filter("fabs(energynew1-E1)>0.00001*E1 || fabs(energynew2-E2)>0.00001*E2 ","control");
            auto df_2mucontrol2_datas=df_2mucontrol_datas.Filter("fabs(energynew1-E1)>0.00001*E1 || fabs(energynew2-E2)>0.00001*E2 ","control");

            //counting how many rows are left
            auto nEntries_MC=df_2mucontrol2_MC.Count();
            auto nEntries_datas=df_2mucontrol2_datas.Count();

            std::cout<<"Testing if E_i^2 is almost equal to m^2+p_i^2"<<std::endl;

            if( nEntries_datas.GetValue()==0 && nEntries_MC.GetValue()==0){
                std::cout<<"Test passed!"<<std::endl;
            }else{
                std::cout<<"Test failed!"<<std::endl;
            }
        }else{
            std::cerr << "Your file haven't the right columns"<<std::endl;
        }
    }else{
        std::cerr << "Your files don't exist, change datas!"<<std::endl;
    }
}