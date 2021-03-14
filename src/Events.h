#ifndef EVENTS_H
#define EVENTS_H

#include "engine/Channel.h"
#include "OscProb.h"

namespace nu
{
    class Events: public Binned{
        private:
            Channel *channel;
            OscProb prob;
        public:
            void setChannel(Channel *channel){this->channel = channel;};
            void setOscProb(OscProb prob){this->prob = prob;};
            void setEvents(Binned Energy);
            void setEvents();  

            Events(){};
            Events(Channel *channel){ this->channel = channel; 
                                this->energy = (*channel).getEnergy().energy;};
            ~Events(){};
    };
};


#endif