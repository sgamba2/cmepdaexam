/******************************************************************************
* 
* \file test_cos.cpp
* \brief Testing if the |cos(theta*)|<1
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

void test_cos(std::string filepath_MC, std::string filepath_datas){
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
    //creating dataframes
    ROOT::RDataFrame df_MC("Events", filepath_MC);
    ROOT::RDataFrame df_datas("Events", filepath_datas);

    //defining all quantities
    auto df_2mu_MC= allquantities(df_MC);
    auto df_2mucontrol_MC=df_2mu_MC.Filter("costheta>1 || costheta<-1","coseno control");
    auto nEntries_MC=df_2mucontrol_MC.Count();
    auto df_2mu_datas= allquantities(df_datas);
    auto df_2mucontrol_datas=df_2mu_datas.Filter("costheta>1 || costheta<-1","coseno control");

    //counting how many rows are left
    auto nEntries_datas=df_2mucontrol_datas.Count();

    std::cout<<"Testing if |costheta|<1 \n";

    if( nEntries_MC.GetValue()==0 && nEntries_datas.GetValue()==0){
        std::cout<<"Test passed!\n";
    }
    else{
        std::cout<<"Test failed!\n";
    }
}