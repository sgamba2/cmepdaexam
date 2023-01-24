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

    ROOT::RDataFrame df("Events", "../datas/Events.root");

    auto df_2mu= allquantities(df);
    auto df_2mucontrol=df_2mu.Filter("costheta>1 || costheta<-1","coseno control");
    auto nEntries=df_2mucontrol.Count();

    printf("testing if |costheta|<1 \n");

    if( nEntries.GetValue()==0){
        printf("test passed!\n");
    }
    else{
        printf("test failed!\n");
    }
}