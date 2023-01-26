#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "../src/utilities.h"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <vector>

void test_cos(){
    /*
    Testing if cos is > or < 0
    */
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df_MC("Events", "../datas/Events_MC.root");
    ROOT::RDataFrame df_datas("Events", "../datas/Events_datas.root");

    auto df_2mu_MC= allquantities(df_MC);
    auto df_2mucontrol_MC=df_2mu_MC.Filter("costheta>1 || costheta<-1","coseno control");
    auto nEntries_MC=df_2mucontrol_MC.Count();
    auto df_2mu_datas= allquantities(df_datas);
    auto df_2mucontrol_datas=df_2mu_datas.Filter("costheta>1 || costheta<-1","coseno control");
    auto nEntries_datas=df_2mucontrol_datas.Count();

    printf("testing if |costheta|<1 \n");

    if( nEntries_MC.GetValue()==0 && nEntries_datas.GetValue()==0){
        printf("test passed!\n");
    }
    else{
        printf("test failed!\n");
    }
}