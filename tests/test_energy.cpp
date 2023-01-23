#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "utilities.h"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <vector>

void test_energy(){
    /*
    Testing if E**2 corresponds to m**2+p**2
    */
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df("Events_new", "Events.root");

    auto df_2mu= allquantities(df);

    //testing if sum of energies is almost equal to Etot
    auto df_2mucontrol2=df_2mu.Filter("fabs(E1+E2-E)>0.001","control"); 

    auto nEntries=df_2mucontrol2.Count();

    if( nEntries.GetValue()==0){
        printf("test passed!");
    }
    else{
        printf("test failed!");
    }
}

