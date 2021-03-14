#include "Channel.h"

namespace nu{
    void Channel::setUniformEnergy(Binned energy)
    {
        this->energy = energy;
        flux.interpolate(energy);
        xsec.interpolate(energy);
        effi.interpolate(energy);
        rec_matrix.interpolate(energy);
    }
}