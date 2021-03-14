#ifndef OSCPROB_H
#define OSCPROB_H

#include<string>
#include"engine/Binned.h"
#include"engine/Parameter.h"

namespace nu
{
    class OscProb: public Binned{
        private:
            Parameter physics;

            double (*Pro)(double x, std::vector<double> physics);

        public:
            void setParameter(std::vector<double> physics);
            void setParameter(Parameter physics){this->physics = physics;};
            void setOscProbFunction(
                double (*Pro)(double x, std::vector<double> physics))
                {this->Pro=Pro;};
            void calculate();

            OscProb(Parameter physics){this->physics=physics;};
            OscProb(){};
        ~OscProb(){};
    };
}
#endif