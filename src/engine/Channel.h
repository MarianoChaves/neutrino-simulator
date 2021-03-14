#ifndef CHANNEL_H
#define CHANNEL_H

#include"Binned.h"

/*  In this class we pre-define data values 
    that will be used to calculate a certain
    number of events.
*/
namespace nu
{
    class Channel
    {
        private:
            Binned flux;
            Binned xsec;
            Binned effi;
            Binned rec_matrix;
            /* 
                Binned energy will set the 
                precision of the events 
                calculation
            */
            Binned energy;
        public:
            void setFlux(Binned flux){this->flux = flux;}
            void setXSec(Binned xsec){this->xsec = xsec;}
            void setEffi(Binned effi){this->effi = effi;}
            void setRec(Binned rec){this->rec_matrix = rec;}
            
            void setUniformEnergy(Binned energy);
            Binned getEnergy(){return energy;};
            Channel(){};
            ~Channel(){};
    };

}
#endif