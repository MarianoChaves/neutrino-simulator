import matplotlib.pyplot as plt
import pandas as pd


# REACTOR FLUX FROM 1101.2663

Pu239 = pd.read_csv("Pu239.csv")
Pu241 = pd.read_csv("Pu241.csv")
U235 = pd.read_csv("U235.csv")
U238 = pd.read_csv("U238.csv")

plt.plot(Pu239.energy*1000,Pu239.nue_bar,label='Pu239')
plt.plot(Pu241.energy*1000,Pu241.nue_bar,label='Pu241')
plt.plot(U235.energy*1000,U235.nue_bar,label='Pu235')
plt.plot(U238.energy*1000,U238.nue_bar,label='Pu238')
plt.yscale("log")
plt.legend()
plt.title("Reactor flux spectra normalized to one.")
plt.xlabel("$E_\\nu(MeV)$")
plt.ylim([0.0003,2])
plt.xlim([2,8])

plt.show()