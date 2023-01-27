#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "../src/utilities.h"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <vector>

void test_energy(std::string filepath_MC, std::string filepath_datas){
    /*
    Testing if E**2 corresponds to m**2+p**2
    */
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df_MC("Events", filepath_MC);
    ROOT::RDataFrame df_datas("Events", filepath_datas);

    auto df_2mu_MC= allquantities(df_MC);
    auto df_2mu_datas= allquantities(df_datas);

    //testing if sum of energies is almost equal to Etot
    auto df_2mucontrol2_MC=df_2mu_MC.Filter("fabs(E1+E2-E)>0.00001*E","control"); 
    auto df_2mucontrol2_datas=df_2mu_datas.Filter("fabs(E1+E2-E)>0.00001*E","control"); 

    auto nEntries_datas=df_2mucontrol2_datas.Count();
    auto nEntries_MC=df_2mucontrol2_MC.Count();

    printf("testing if sum of energies is almost equal to Etot \n");
    
    if( nEntries_MC.GetValue()==0 && nEntries_datas.GetValue()==0){
        printf("test passed! \n");
    }
    else{
        printf("test failed! \n");
    }
}

