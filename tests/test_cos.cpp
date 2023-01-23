#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "utilities.h"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <vector>

void test_cos(){
    /*
    Testing if cos is > or < 0
    */
    //ROOT::EnableImplicitMT();

    ROOT::RDataFrame df("Events_new", "Events.root");

    auto df_2mu= allquantities(df);
    auto df_2mucontrol=df_2mu.Filter("costheta>1 || costheta<-1","coseno control");
    auto nEntries=df_2mucontrol.Count();

    if( nEntries.GetValue()==0){
        printf("test passed!");
    }
    else{
        printf("test failed!");
    }
}