#include "hello.h"
//#include "ctag_reshaping.h"

int main()
{
    printf("Hello World!\n");

    test_run();
    ////--------------- ctag reshaping ---------------//
    //retrieve_scale_factor sf;
    //TRandom3 random(1234);

    //double cvsl = random.Rndm();
    //double cvsb = random.Rndm();
    //TString type_flavour = "b";
    //TString name = "SF" + type_flavour + "_hist";

    //sf.debug_mode();
    //double scale_factor = sf.get_scale_factor(name, cvsl, cvsb);
    ////----------------------------------------------//

    std::cout << "This is the end of file" << std::endl;
    return 0;
}

void test_run()
{
    retrieve_scale_factor sf;
    TRandom3 random(1234);

    TString type_flavour[3] = {"b", "c", "l"}; 
    TString type_uncertainty[16] = {"", "_Stat", "_EleIDSF", "_LHEScaleWeight_muF", "_LHEScaleWeight_muR", "_MuIDSF", "_PSWeightFSR", "_PSWeightISR", "_PUWeight", "_XSec_DYJets", "_XSec_ST", "_XSec_WJets", "_XSec_ttbar", "_jer", "_jesTotal", "_TotalUnc"};

    double cvsl = random.Rndm();
    double cvsb = random.Rndm();

    sf.debug_mode();
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<16; ++j)
        {
            if(!(i==0)) continue;
            //if(!(i==0 and (j==0 or j==8))) continue; //check "_PUWeight" only
    //------------------------------------------------------------------------------------------//
            TString name = "SF" + type_flavour[i] + "_hist" + type_uncertainty[j];
            if(j==0){
                sf.init_raw_histogram(name);
                sf.print_th2d_content(name);
            } else if(j+1==16){
                sf.print_th2d_content(name + "Up");
                sf.print_overall_uncertainty();
            } else{
                sf.accumulate_th2d_uncertainty(name + "Up");
                sf.print_th2d_content(name + "Up");
                sf.print_th2d_difference(name + "Up");
            }
    //------------------------------------------------------------------------------------------//
        }
    }
    std::cout << "This is the end of test run" << std::endl;
}
