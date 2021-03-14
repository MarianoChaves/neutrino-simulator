#ifndef ENGINE_BINNED2D_H
#define ENGINE_BINNED2D_H

#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<gsl/gsl_spline2d.h>
#include<math.h>
#include"Binned.h"

#include <iostream>
#include <fstream>
#include <utility> // std::pair
#include <sstream> // std::stringstream

namespace nu
{
    class Binned2D{
            std::vector<std::vector<double> > true_value;
            std::vector<double> true_x;
            std::vector<double> true_y;

            int locate(double x, bool is_x);

        public:
            std::vector<std::vector<double> > value;
            std::vector<double> x;
            std::vector<double> y;

            void setTrues(){true_value=value; true_x=x; true_y=y;};

            void setTrue_value(std::vector<std::vector<double> > value)
            {this->true_value=value; this->value=value;};
            void setTrue_x(std::vector<double> x)
            {this->true_x=x; this->x=x;};
            void setTrue_y(std::vector<double> y)
            {this->true_y=y; this->y=y;};

            void interpolate(std::vector<double> x, std::vector<double> y);
            void interpolate(Binned x, Binned y);
            void interpolate(Binned2D x);

            Binned integrate(double xi, double xf, bool is_x);
            Binned2D integrate(Binned bins, bool is_x);

            void getLineData(std::vector<double> &x, std::vector<double> &y, std::vector<double> &z);
            
            Binned2D(double *ini, double *fin, int *N, std::string spacing);
            Binned2D(double *ini, double *fin, int *N); // [x,y]
            Binned2D(){};
            ~Binned2D(){};
            
    };

    class Input2D: public nu::Binned2D{
        private:
            std::vector<std::vector<double> > true_value;
            std::vector<double> true_x;
            std::vector<double> true_y;
            
            char *x_collumn;
            char *y_collumn;
            char *z_collumn;

            void read_input(char *file_name, char *collumn1, char *collumn2, char *collumn3);
        public:

            Input2D(char *file_name, char *collumn1, char *collumn2, char *collumn3);
            ~Input2D(){};
    };

};


#endif
