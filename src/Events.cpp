#include "Events.h"

namespace nu
{
    void Events::setEvents(Binned Energy)
    {
        this->setTrue_energy(Energy.energy);
        prob.interpolate((*this->channel).getEnergy());
    };

}