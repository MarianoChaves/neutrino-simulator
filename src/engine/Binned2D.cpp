#include "Binned2D.h"

namespace nu
{
    Binned2D::Binned2D(double *ini, double *fin, int *N){
        double dx = (fin[0]-ini[0])/N[0];
        double dy = (fin[1]-ini[1])/N[1];
        for(int i=0; i<=N[0]; i++ ){
            double X = ini[0] +dx*i;
            this->x.push_back(X);
            this->true_x.push_back(X);
        }
        for(int i=0; i<=N[1]; i++ ){
            double Y = ini[1] +dy*i;
            this->y.push_back(Y);
            this->true_y.push_back(Y);
        }
    }

    Binned2D::Binned2D(double *ini, double *fin, int *N, std::string spacing){
        if(spacing=="log")
        {
            double dx = (log10(fin[0])-log10(ini[0]))/N[0];
            double dy = (log10(fin[1])-log10(ini[1]))/N[1];
            for(int i=0; i<=N[0]; i++ ){
                double X = log10(ini[0]) +dx*i;
                this->x.push_back( pow(10, X) );
                this->true_x.push_back( pow(10, X) );
            }
            for(int i=0; i<=N[1]; i++ ){
                double Y = log10(ini[1]) +dy*i;
                this->y.push_back( pow(10, Y) );
                this->true_y.push_back( pow(10, Y) );
            }
        }else printf("ERROR: there is no spacing of type %s\n", spacing.c_str());
    }


    void Binned2D::interpolate(std::vector<double> new_x, std::vector<double> new_y){
        int Nx_new = new_x.size();
        int Nx_old = x.size();    
        int Ny_new = new_y.size();
        int Ny_old = y.size();    
        double *z_old = (double*)malloc(Nx_old*Ny_old*sizeof(double));

        gsl_interp_accel *xacc = gsl_interp_accel_alloc ();
        gsl_interp_accel *yacc = gsl_interp_accel_alloc ();
        const gsl_interp2d_type *T = gsl_interp2d_bilinear;
        gsl_spline2d *spline2d = gsl_spline2d_alloc (T, Nx_old, Ny_old);


        for(int i = 0; i<Nx_old; i++){
            for(int j = 0; j<Ny_old; j++){
                gsl_spline2d_set(spline2d, z_old, x[i], y[j], this->true_value[i][j]);
            };
        };
        gsl_spline2d_init (spline2d, &true_x[0], &true_y[0], z_old, Nx_old, Ny_old);


        x.clear();
        y.clear();
        value.clear();
        for(int i = 0; i<Nx_new; i++){
            std::vector<double> lin_value;
            for(int j = 0; j<Ny_new; j++){
                lin_value.push_back(gsl_spline2d_eval (spline2d, new_x[i], new_y[j], xacc, yacc));
                if(i==0){this->y.push_back(new_y[j]);};
            };
            this->value.push_back(lin_value);
            this->x.push_back(new_x[i]);;
        };
    }

    void Binned2D::interpolate(Binned new_x, Binned new_y){

        int Nx_new = new_x.energy.size();
        int Nx_old = x.size();    
        int Ny_new = new_y.energy.size();
        int Ny_old = y.size();    
        double *z_old = (double*)malloc(Nx_old*Ny_old*sizeof(double));

        gsl_interp_accel *xacc = gsl_interp_accel_alloc ();
        gsl_interp_accel *yacc = gsl_interp_accel_alloc ();
        const gsl_interp2d_type *T = gsl_interp2d_bilinear;
        gsl_spline2d *spline2d = gsl_spline2d_alloc (T, Nx_old, Ny_old);


        for(int i = 0; i<Nx_old; i++){
            for(int j = 0; j<Ny_old; j++){
                gsl_spline2d_set(spline2d, z_old, x[i], y[j], this->true_value[i][j]);
            };
        };
        gsl_spline2d_init (spline2d, &true_x[0], &true_y[0], z_old, Nx_old, Ny_old);


        x.clear();
        y.clear();
        value.clear();
        for(int i = 0; i<Nx_new; i++){
            std::vector<double> lin_value;
            for(int j = 0; j<Ny_new; j++){
                lin_value.push_back(gsl_spline2d_eval (spline2d, new_x.energy[i], new_y.energy[j], xacc, yacc));
                if(i==0){this->y.push_back(new_y.energy[j]);};
            };
            this->value.push_back(lin_value);
            this->x.push_back(new_x.energy[i]);;
        };

    }

    void Binned2D::interpolate(Binned2D new_axis){

        int Nx_new = new_axis.x.size();
        int Nx_old = x.size();    
        int Ny_new = new_axis.y.size();
        int Ny_old = y.size();    
        double *z_old = (double*)malloc(Nx_old*Ny_old*sizeof(double));

        gsl_interp_accel *xacc = gsl_interp_accel_alloc ();
        gsl_interp_accel *yacc = gsl_interp_accel_alloc ();
        const gsl_interp2d_type *T = gsl_interp2d_bilinear;
        gsl_spline2d *spline2d = gsl_spline2d_alloc (T, Nx_old, Ny_old);


        for(int i = 0; i<Nx_old; i++){
            for(int j = 0; j<Ny_old; j++){
                gsl_spline2d_set(spline2d, z_old, x[i], y[j], this->true_value[i][j]);
            };
        };
        gsl_spline2d_init (spline2d, &true_x[0], &true_y[0], z_old, Nx_old, Ny_old);


        x.clear();
        y.clear();
        value.clear();
        for(int i = 0; i<Nx_new; i++){
            std::vector<double> lin_value;
            for(int j = 0; j<Ny_new; j++){
                lin_value.push_back(gsl_spline2d_eval (spline2d, new_axis.x[i], new_axis.y[j], xacc, yacc));
                if(i==0){this->y.push_back(new_axis.y[j]);};
            };
            this->value.push_back(lin_value);
            this->x.push_back(new_axis.x[i]);;
        };

    }

    void Binned2D::getLineData(std::vector<double> &x0, std::vector<double> &y0, std::vector<double> &z0){
        int Nx = this->x.size();
        int Ny = this->y.size();
        for(int i = 0; i<Nx; i++){
            for(int j = 0; j<Ny; j++){
                x0.push_back(this->x[i]);
                y0.push_back(this->y[j]);
                z0.push_back(this->value[i][j]);           
            };
        };
    };

    int Binned2D::locate(double x, bool is_x){

        std::vector<double> array;
        if(is_x) array = this->true_x;
        else array = this->true_y;
        
        int pos = 0;
        double dif = abs(x-array[0]);
        for(int i = 1; i<array.size(); i++){
            double dif_test = abs(x-array[i]);
            if(dif_test<dif){
                pos = i;
                dif = dif_test;
            };
        };
        return pos;
    }

    Binned Binned2D::integrate(double xini, double xfin, bool is_x){
        int i_pos = locate(xini, is_x);
        int f_pos = locate(xfin, is_x);

        std::vector<double> array;
        std::vector<double> out_array;
        if(is_x){
            array = this->true_x;
            out_array = this->true_y;
        }
        else{
            array = this->true_y;
            out_array = this->true_x;
        };

        if(i_pos==f_pos){
            return Binned(0,0,1);
        }

        std::vector<double> integrated;
        for(int i = 0; i<out_array.size(); i++){
            double sum = 0;            
            for(int j = i_pos; j<f_pos; j++){
                if(is_x){
                    sum+= (array[j+1]-array[j])*(this->true_value[j][i]+this->true_value[j+1][i])/2;
                }else{
                    sum+= (array[j+1]-array[j])*(this->true_value[i][j]+this->true_value[i][j+1])/2;
                }
            }
            integrated.push_back(sum);
        };
        Binned reduced;
        reduced.setTrue_value(integrated);
        reduced.setTrue_energy(out_array);
        return reduced;
    };

    Binned2D Binned2D::integrate(Binned bins, bool is_x){
        Binned2D bins_out;
        Binned aux;
        std::vector<std::vector <double> > val;
        for(int i = 0; i<bins.energy.size()-1; i++){
            aux = integrate(bins.energy[i],bins.energy[i+1], is_x);
            val.push_back(aux.value);
        }
        bins_out.setTrue_value(val);
        bins_out.setTrue_y(aux.energy);
        bins_out.setTrue_x(bins.getCenteredBin());
        return bins_out;
    }

    /* INPUT CLASS */
    void Input2D::read_input(char *file_name, char *collumn1, char *collumn2, char *collumn3){

    std::ifstream myFile(file_name);
    std::string x_col(collumn1);
    std::string y_col(collumn2);
    std::string z_col(collumn3);

    if(!myFile.is_open()) std::cout << "\nCould not open file!\n";
 

    // Helper vars
    std::string line, colname;
    int count = 0;

    int col_y[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int col_x[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int col_z[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

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
            if(colname==z_col) {
                col_z[count]=1;
            };
            count++;
        };
    }


    int this_line = 0;
    int next_line = 2;
    std::vector<double> line_value;
    double line_test = -10000000000000000000000000000123;
    while(std::getline(myFile, line))
    {
        count =0;

        // Create a stringstream of the current line
        // The data should be a organized as three collumns
        // where the first is x and the second is y ordered by x before y
        // x1 y1 z1
        // x1 y2 z2
        // ... ... ...
        // x2 y1 zn
        std::stringstream ss(line);

        while(std::getline(ss, colname, ',')){
            if(col_x[count] == 1) {
                double xx = std::stold(colname);
                if(xx != line_test){
                    x.push_back(xx);
                    line_test = xx;
                    this_line++;      
                };
            };
            if(col_y[count] == 1) {
                double xx = std::stold(colname);
                if(this_line==1){ y.push_back(xx);};
            };
            if(col_z[count] == 1) {
                double xx = std::stold(colname);
                if(next_line==this_line){
                    value.push_back(line_value);
                    line_value.clear();
                    next_line++;
                };
                line_value.push_back(xx);
            };
            count++;
            
        };

    }
    value.push_back(line_value);
    
    myFile.close();
}

    Input2D::Input2D(char *file_name, char *collumn1, char *collumn2, char *collumn3){
        this->x_collumn = collumn1;
        this->y_collumn = collumn2;
        this->z_collumn = collumn3;
        read_input(file_name, collumn1, collumn2, collumn3);
        setTrues();
    }

};

