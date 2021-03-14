#ifndef PRECOMPUTED_H
#define PRECOMPUTED_H
#include<vector>

/*
        This class can be used to PreComputed
        pre-compilated functions.
        It can depends on the q variables, the 
        geometry of the problem or energy.

        You can PreComputed f(x) by using set()
        or g(f(x)) by using setGeo(f)
*/
namespace nu
{
    class PreComputed
    {
        private:
            double(*function)(double arg);
            std::vector<double> q;
            int q_size;



        public:
            std::vector<double> F;

            void setFunction(double(*f)(double arg)){function = f;};
            void setQ(std::vector<double> q){this->q=q; q_size = q.size();};

            void set();
            void setGeo(double(*geometry)(double(*f)(double arg), double arg));
            PreComputed(double(*f)(double arg), std::vector<double> q);
            PreComputed();
            ~PreComputed();

    };
};

#endif