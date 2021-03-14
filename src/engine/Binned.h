#ifndef ENGINE_BINNED_H
#define ENGINE_BINNED_H

#include<string>
#include<stdio.h>
#include<vector>
#include<gsl/gsl_spline.h>
#include<math.h>

#include <iostream>
#include <fstream>
#include <utility> // std::pair
#include <sstream> // std::stringstream

namespace nu
{
    class Binned{
            std::vector<double> true_value;
            std::vector<double> true_energy;
        public:
            std::vector<double> value;
            std::vector<double> energy;

            void setTrues(){true_value=value; true_energy=energy;};

            void setTrue_value(std::vector<double> value)
            {this->true_value=value; this->value=value;};
            void setTrue_energy(std::vector<double> energy)
            {this->true_energy=energy; this->energy=energy;};

            void interpolate(std::vector<double> energy);
            void interpolate(Binned energy);

            std::vector<double> getCenteredBin();

            Binned(double ini, double fin, int N, std::string spacing);
            Binned(double ini, double fin, int N);
            Binned(){};
            ~Binned(){};
            
    };

    class Input: public nu::Binned{
        private:
            std::vector<double> true_value;
            std::vector<double> true_energy;
            
            char *x_collumn;
            char *y_collumn;

            void read_input(char *file_name, char *collumn1, char *collumn2);
        public:

            Input(char *file_name, char *collumn1, char *collumn2);
            ~Input(){};
    };

};


#endif
