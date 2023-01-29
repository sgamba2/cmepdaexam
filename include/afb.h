/******************************************************************************
* 
* \file afb.cpp
* \brief Creating afb histogram in function of dimuon mass
* 
******************************************************************************/
#ifndef AFB_H
#define AFB_H

#include "utilities.h"
#include "graphical_utilities.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>
#include <filesystem>
#include <string>
#include <iostream>

/******************************************************************************
* 
* \brief Creating afb histogram in function of dimuon mass. Firstly checks if in the dataframe exists and if
* there are the right columns, then creates all quantities necessary to the analysis, then makes 
* six filters for the rapidity conditions and creates six histograms in one canvas, saving them in .pdf and .png
* 
* @param filepath_MC: dataframe of the MC datas
*
* \return None
* 
******************************************************************************/
void afb(std::string filepath_MC);

#endif /* AFB_H */