/******************************************************************************
* 
* \file filter_df.cpp
* \brief Creating filtered dataframes
* 
******************************************************************************/
#ifndef DF_FILTER_H
#define DF_FILTER_H

#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include <string>
#include <TFile.h>
#include <iostream>
#include <filesystem>

/******************************************************************************
* 
* \brief This function creates filtered dataframes of MC datas and Run datas with 
* a snapshot function with columns "Muon_pt" , "Muon_mass" , "Muon_phi" , "Muon_eta".
* This will be saved in the folder "datas". If it doesn't exist, the program will create it.
* The filter is based on the following columns: "Muon_pt" , "Muon_eta",
* "nMuon", "Muon_dxy", "Muon_charge", "Muon_pfRelIso03_chg".
* 
* @param filepath_MC: dataframe of the MC datas 
* @param filepath_datas: dataframe of the Run datas
* @param filename_MC_fil: file name of the dataframe of the MC datas filtered
* @param filename_datas_fil: file name of the dataframe of the Run datas filtered
*
* \return 0: filtered dataframes have been created, 1: Doesn't exist the path of the files, 2: files with few columns, 3: files with few datas 
* 
******************************************************************************/ 
int filter_df(std::string filepath_MC, std::string filepath_datas, std::string filename_MC_fil, std::string filename_datas_fil);

#endif /* DF_FILTER_H */