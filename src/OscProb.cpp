#include"OscProb.h"

namespace nu
{
    void OscProb::setParameter(std::vector<double> physics){
        this->physics.setParam(physics);
    };

    void OscProb::calculate()
    {
        int N = energy.size();
        for(int i = 0; i<N; i++){
            value.push_back(Pro(energy[i], physics.getParam()));
        }
    }
}