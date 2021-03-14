#ifndef ENGINE_PARAMETER_H
#define ENGINE_PARAMETER_H

#include<vector>
#include<string>
#include<math.h>

namespace nu
{
    class Parameter{
        private:
            std::vector<double> p;
        
        public:

            void setParam(std::vector<double> p){this->p = p;};
            void setParam(double p, int n){this->p[n] = p;};
            double getParam(int n){return p[n];};
            std::vector<double> getParam(){return this->p;};
            void newParam(double p){this->p.push_back(p);};

            Parameter(std::string so);
            Parameter(){};
            Parameter(std::vector<double> p){this->p=p;};
            ~Parameter(){p.clear();};
    };
};

#endif