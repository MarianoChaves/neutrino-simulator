#include "Binned.h"

namespace nu
{
    Binned::Binned(double ini, double fin, int N){
        double dE = (fin-ini)/N;
        for(int i=0; i<=N; i++ ){
            double En = ini +dE*i;
            this->energy.push_back(En);
            this->true_energy.push_back(En);
        }
    }

    Binned::Binned(double ini, double fin, int N, std::string spacing){
        if(spacing=="log")
        {
            double dE = (log10(fin)-log10(ini))/N;
            for(int i=0; i<=N; i++ ){
                double En = log10(ini) +dE*i;
                this->energy.push_back( pow(10, En) );
                this->true_energy.push_back( pow(10, En) );
            }
        }else printf("ERROR: there is no spacing of type %s\n", spacing.c_str());
    }

    std::vector<double> Binned::getCenteredBin(){
        std::vector<double> aux;
        for(int i = 0; i<energy.size()-1; i++){
            aux.push_back((energy[i]+energy[i+1])/2);
        }
        return aux;
    }

    void Binned::interpolate(std::vector<double> new_energy){
        int N_new = new_energy.size();
        int N_old = energy.size();    

        gsl_interp_accel *acc = gsl_interp_accel_alloc ();
        gsl_spline *spline = gsl_spline_alloc (gsl_interp_cspline, N_old);
        gsl_spline_init (spline, &true_energy[0], &true_value[0], N_old);

        energy.clear();
        value.clear();
        for(int i = 0; i<N_new; i++){
            value.push_back(gsl_spline_eval (spline, new_energy[i], acc));
            energy.push_back(new_energy[i]);
        }
    }

    void Binned::interpolate(Binned new_energy){
        int N_new = new_energy.energy.size();
        int N_old = energy.size();    

        gsl_interp_accel *acc = gsl_interp_accel_alloc ();
        gsl_spline *spline = gsl_spline_alloc (gsl_interp_cspline, N_old);
        gsl_spline_init (spline, &true_energy[0], &true_value[0], N_old);

        energy.clear();
        value.clear();
        for(int i = 0; i<N_new; i++){
            value.push_back(gsl_spline_eval (spline, new_energy.energy[i], acc));
            energy.push_back(new_energy.energy[i]);
        }
    }



void Input::read_input(char *file_name, char *collumn1, char *collumn2){

    std::ifstream myFile(file_name);
    std::string x_col(collumn1);
    std::string y_col(collumn2);

    if(!myFile.is_open()) std::cout << "\nCould not open file!\n";
 

    // Helper vars
    std::string line, colname;
    int count = 0;

    int col_y[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int col_x[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colname, ',')){
            if(colname==x_col) {
                col_x[count]=1;
            };
            if(colname==y_col) {
                col_y[count]=1;
            };
            count++;
        };
    }

    while(std::getline(myFile, line))
    {
        count =0;

        // Create a stringstream of the current line
        std::stringstream ss(line);
        
        while(std::getline(ss, colname, ',')){
            if(col_x[count] == 1) {
                double xx = std::stold(colname); 
                energy.push_back(xx);
            };
            if(col_y[count] == 1) {
                double xx = std::stold(colname); 
                value.push_back(xx);
            };
            count++;
            
        };
    }
    myFile.close();
}

Input::Input(char *file_name, char *collumn1, char *collumn2){
    this->x_collumn = collumn1;
    this->y_collumn = collumn2;
    read_input(file_name, collumn1, collumn2);
    setTrues();     
}

};

