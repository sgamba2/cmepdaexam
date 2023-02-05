/******************************************************************************
* 
* \file testCos.cpp
* \brief Testing if the |cos(theta*)|<1
* 
******************************************************************************/
#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "../include/utilities.h"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <iostream>

void testCos(std::string filepath_MC, std::string filepath_datas){
/******************************************************************************
* 
* \brief Testing if |cos(theta*)|<1
*
* @param filepath_MC: dataframe of the MC datas
* @param filepath_datas: dataframe of the Run datas
*
* \return None
* 
******************************************************************************/

    //checking the correct path
    if(TFile::Open(filepath_datas.c_str()) != nullptr && TFile::Open(filepath_MC.c_str()) != nullptr){

        //creating dataframes
        ROOT::RDataFrame df_MC("Events", filepath_MC);
        ROOT::RDataFrame df_datas("Events", filepath_datas);

        //checking if they have the right column
        if(df_MC.HasColumn("Muon_pt") && df_MC.HasColumn("Muon_mass") && df_MC.HasColumn("Muon_phi") && df_MC.HasColumn("Muon_eta") && df_datas.HasColumn("Muon_pt") && df_datas.HasColumn("Muon_mass") && df_datas.HasColumn("Muon_phi") && df_datas.HasColumn("Muon_eta")){
            
            //defining all quantities
            auto df_2mu_MC = allquantities(df_MC);
            auto df_2mucontrol_MC = df_2mu_MC.Filter("costheta>1 || costheta<-1", "coseno control");
            auto nEntries_MC = df_2mucontrol_MC.Count();
            auto df_2mu_datas = allquantities(df_datas);
            auto df_2mucontrol_datas = df_2mu_datas.Filter("costheta>1 || costheta<-1", "coseno control");

            //counting how many rows are left
            auto nEntries_datas = df_2mucontrol_datas.Count();

            std::cout << "Testing if |costheta|<1" << std::endl;

            if(nEntries_MC.GetValue() == 0 && nEntries_datas.GetValue() == 0){
                std::cout << "Test passed!" << std::endl;
            }else{
                std::cout << "Test failed!" << std::endl;
            }
        }else{
            std::cerr << "Your file haven't the right columns" << std::endl;
        }
    }else{
        std::cerr << "Your files don't exist, change datas!" << std::endl;
    }
}