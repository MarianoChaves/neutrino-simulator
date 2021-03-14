#include"src/utilities.hpp"



int main()
{
    nu::Input   flux_Pu239("input/Pu239.csv","energy","nue_bar");
    nu::Input   flux_Pu241("input/Pu241.csv","energy","nue_bar");
    nu::Input   flux_U235("input/U235.csv","energy","nue_bar");
    nu::Input   flux_U238("input/U238.csv","energy","nue_bar");
    nu::Input2D inv_beta_xsec("input/kamland_xsec/rec_cross_section.csv","energy_nu","energy_pos","xsec");

    nu::Binned pos_energy_bin(0.9,8.5,17);
    nu::Binned2D rec_mat;

    rec_mat = inv_beta_xsec.integrate(pos_energy_bin, false);
}