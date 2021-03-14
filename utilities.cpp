#include<stdio.h>
#include<math.h>
#include"src/utilities.hpp"

#include "input/dayabay.h"
#include "input/nue_dis.h"

using namespace nu;

double sin2 (double x){
    return sin(x)*sin(x);
}

int main()
{

    if(true){
	    nu::Input2D rec_test("input/rec_test.csv","x","y","z");
        nu::Binned x(0,1,100);
        nu::Binned y(0,1,50);

        rec_test.interpolate(x,y);

        std::vector<double> x_line, y_line, z_line;

        rec_test.getLineData(x_line, y_line, z_line);
 
        char filename[16] = "output/data.csv"; 
        char header[6] = "x,y,z";
        nu::IO out(filename);
        out.setHeader(header);
        out.write(x_line , y_line, z_line);    
    };
    /* Here is how to compute events */
    if(false){
        /* Read files */
	    nu::Input   flux("input/Pure_Pu239.csv","energy","nue_bar"),
                    xsec("input/inverse_beta.csv", "energy", "value");

        nu::Binned2D rec_mat("x","y","z");
        

        /* Create rules */
        nu::Channel ee;
        ee.setFlux(flux);
        ee.setXSec(xsec);

        Binned energy(2/1000,10/1000,50); //MeV to GeV
        ee.setUniformEnergy(energy);
        
        /* Simulate Events */
        Events simu(&ee);

        /* Define Probability */
        Parameter std_param("so");
        OscProb std_prob;

        std_prob.setParameter(std_param);
        std_prob.setOscProbFunction(&dis_nue);
        std_prob.energy = ee.getEnergy().energy;
        std_prob.calculate();
        simu.setOscProb(std_prob);
        

    }
    /* Here is how to compute probabilities */
    if(false){
        int N = 500;
        // Get a Binned log energy distributed
        Binned Energy(0.001, 0.1, N, "log");
        Parameter std_param("so");

        OscProb std_prob;
        std_prob.setParameter(std_param);
        std_prob.setOscProbFunction(&dis_nue);
        std_prob.energy = Energy.energy;
        std_prob.calculate();

        char filename[16] = "output/data.csv"; 
        char header[4] = "x,y";
        IO out(filename);
        out.setHeader(header);
        out.write(std_prob.energy,std_prob.value);
    }
    /* Here is how to compute pre-computaded functions */
    if(false){
        int N = 1000;
        Binned Q(0.1, 2000, N, "log");
        std::vector<double> q = Q.energy;

        PreComputed s2(&sin2, q);
        s2.setGeo(&(geo::DB_AD8));
    }
    /*Here is how to write two collum csv output*/
    if(false){
        char filename[16] = "output/data.csv"; 
        char header[4] = "x,y";
        IO out(filename);
        out.setHeader(header);
        out.write({1,10,100,1000},{0,1,2,3}, &log10);
    }

}
