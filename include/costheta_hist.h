/******************************************************************************
* 
* \file costheta_hist.cpp
* \brief Creating costheta histogram from filtered dataframe
* 
******************************************************************************/
#ifndef COSTHETA_HIST_H
#define COSTHETA_HIST_H

#include "utilities.h"
#include "graphical_utilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>
#include <string>
#include <filesystem>
#include <iostream>

/******************************************************************************
* 
* \brief Creating costheta histogram from filtered dataframe. Firstly checks if in the dataframes exist and if
* there are the right columns, then creates all quantities necessary to the analysis, then makes 
* three filters for the rapidity conditions and creates three histograms, saving them in .pdf and .png
* 
* @param filepath_MC: file path of the dataframe of the MC datas
* @param filepath_datas: file path of the dataframe of the Run datas
* 
* \return None
* 
******************************************************************************/
void costheta_hist(std::string filepath_MC, std::string filepath_datas);

#endif /* COSTHETA_HIST_H */