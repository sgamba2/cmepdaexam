/******************************************************************************
* 
* \file dimuonSpectrumZ.cpp
* \brief Creating dimuon spectrum histogram of Z from filtered dataframe
* 
******************************************************************************/
#ifndef DIMUONSPECTRUMZ_H
#define DIMUONSPECTRUMZ_H

#include "graphicalUtilities.h"
#include "utilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TPad.h>
#include <filesystem>
#include <string>
#include <iostream>

/******************************************************************************
* 
* \brief Creating dimuon spectrum histogram of Z from filtered dataframe. Firstly checks if in the dataframes exist and if
* there are the right columns, then creates all quantities necessary to the analysis, then makes 
* three filters for the rapidity conditions and creates three histograms, saving them in .pdf and .png
* 
* @param filepath_MC: file path of the dataframe of the MC datas
* @param filepath_datas: file path of the dataframe of the Run datas
* 
* \return None
* 
*****************************************************************************/
void dimuonSpectrumZ(std::string filepath_MC, std::string filepath_datas);

#endif /* DIMUON_SPECTRUM_Z_H */

