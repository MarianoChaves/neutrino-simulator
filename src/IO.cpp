#include "IO.h"


namespace nu
{
    IO::IO(char* filename){
        setFile(filename);
    }
    IO::~IO(){};

    void IO::write(std::vector<double> col1, std::vector<double> col2){
        if(header!=NULL){
            fprintf(file,"%s",header);
            fprintf(file,"\n");
        };
        for(int i = 0; i<int(col1.size()); i++){
            fprintf(file,"%f,%f\n", col1[i], col2[i]);
        }
    }

    void IO::write(std::vector<double> col1, std::vector<double> col2, std::vector<double> col3){
        if(header!=NULL){
            fprintf(file,"%s",header);
            fprintf(file,"\n");
        };
        for(int i = 0; i<int(col1.size()); i++){
            fprintf(file,"%f,%f,%f\n", col1[i], col2[i], col3[i]);
        }
    }

    void IO::write(std::vector<double> col1, std::vector<double> col2, double(*f)(double x)){
        if(header!=NULL){
            fprintf(file,"%s",header);
            fprintf(file,"\n");
        };
        for(int i = 0; i<int(col1.size()); i++){
            fprintf(file,"%f,%f\n", f(col1[i]), col2[i]);
        }
    }
}
