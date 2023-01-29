/******************************************************************************
* 
* \file test_energy.cpp
* \brief Testing if the sum of E1 and E2 is almost equal to Etot
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

void test_energy(std::string filepath_MC, std::string filepath_datas){
/******************************************************************************
* 
* \brief Testing if the sum of E1 and E2 is almost equal to Etot
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
    auto df_2mu_datas= allquantities(df_datas);

    //testing if sum of energies is almost equal to Etot
    auto df_2mucontrol2_MC=df_2mu_MC.Filter("fabs(E1+E2-E)>0.00001*E","control"); 
    auto df_2mucontrol2_datas=df_2mu_datas.Filter("fabs(E1+E2-E)>0.00001*E","control"); 

    //counting how many rows are left
    auto nEntries_datas=df_2mucontrol2_datas.Count();
    auto nEntries_MC=df_2mucontrol2_MC.Count();

    std::cout<<"Testing if sum of energies is almost equal to Etot \n";
    
    if( nEntries_MC.GetValue()==0 && nEntries_datas.GetValue()==0){
        std::cout<<"Test passed! \n";
    }
    else{
        std::cout<<"Test failed! \n";
    }
}

