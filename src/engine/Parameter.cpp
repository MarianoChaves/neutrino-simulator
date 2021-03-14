#include"Parameter.h"

/*
    Standard Oscillation values were taken
    from JHEP 01 (2019) 106 [arXiv:1811.05487] 
    as well as NuFIT 4.1 (2019), www.nu-fit.org.

    The CP violation fase is taken as zero.
*/

namespace nu
{
    Parameter::Parameter(std::string so){
        if(so == "Standard Oscillation" || so == "SO" || so == "so"
        || so == "standard oscillation" || so =="standard"){
            p.push_back(sqrt(asin(0.310))); // th12
            p.push_back(sqrt(asin(0.558))); // th23
            p.push_back(sqrt(asin(0.02241))); // th13
            p.push_back(0.0000739); // dm21
            p.push_back(0.00253); // dm31
            p.push_back(0); // cp phase
        };
    }
};