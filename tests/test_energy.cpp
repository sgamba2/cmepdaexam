#include <ROOT/RDataFrame.hxx>
#include <cmath>
#include "../src/utilities.h"
#include <ROOT/RVec.hxx>
#include <Math/Vector4Dfwd.h>
#include <Math/Vector4D.h>
#include <vector>

void test_energy(){
    /*
    Testing if E**2 corresponds to m**2+p**2
    */
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df("Events", "../datas/Events.root");

    auto df_2mu= allquantities(df);

    //testing if sum of energies is almost equal to Etot
    auto df_2mucontrol2=df_2mu.Filter("fabs(E1+E2-E)>0.00001*E","control"); 

    auto nEntries=df_2mucontrol2.Count();

    printf("testing if sum of energies is almost equal to Etot \n");
    
    if( nEntries.GetValue()==0){
        printf("test passed! \n");
    }
    else{
        printf("test failed! \n");
    }
}

