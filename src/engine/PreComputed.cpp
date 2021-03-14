#include "PreComputed.h"
#include <stdio.h>
#include <stdlib.h>

namespace nu
{
    PreComputed::PreComputed(double(*f)(double arg), std::vector<double> q){
        this->setFunction(f);
        this->setQ(q);
    }
    PreComputed::~PreComputed(){};

    void PreComputed::set()
    {
        for(int i=0; i<q_size; i++)
        {
            F.push_back(function(q[i]));
        }
    }

    void PreComputed::setGeo(double(*geometry)(double(*f)(double arg), double arg))
    {
        for(int i=0; i<q_size; i++)
        {
            F.push_back(geometry(function,q[i]));
        }
    }
}