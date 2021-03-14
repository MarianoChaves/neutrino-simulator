#ifndef IONU_H
#define IONU_H

#include <vector>
#include <stdio.h>
#include "engine/Binned.h"

/*
    The class Nuio can be used to create
    new files and write them in a assecible way
*/

namespace nu
{
    class IO{
        private:
            char *header;
            FILE *file;
        public:
            void setHeader(char *header){this->header = header;};
            void setFile(char *filename){this->file = fopen(filename,"w");};
            void write(std::vector<double> col1, std::vector<double> col2);
            void write(std::vector<double> col1, std::vector<double> col2, std::vector<double> col3);
            void write(std::vector<double> col1, std::vector<double> col2, double(*f)(double x));
            

            IO(char *filename);
            IO();
            ~IO();

    };
};


#endif // IONU_H
