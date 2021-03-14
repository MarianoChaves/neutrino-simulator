import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from math import sqrt
from math import pi
from itertools import product
import scipy.integrate as integrate

#UNITS
Mp = 938.27231
Mn = 939.56563
Delta = Mn-Mp
me = 0.5109991
print(Delta+me)
emax=14
################################################
# CROSS-SECTION ZEROTH ORDER FROM hep-ph/9903554
################################################

xsec_df = pd.DataFrame()

def pe(Ee):
    return sqrt(Ee**2-me**2)

def xsec(x): #x = [Enu, Epos]
    sigma0 = 0.0952*(x[0]-Delta)*pe(x[1])
    return sigma0

#COMPUNTING CROSS-SECTION
Enu = np.geomspace(Delta, emax, 100)
Ep = np.geomspace(me, emax, 100)
Egrid = list(product(Enu,Ep))
result_xsec = list( map(xsec,Egrid) )

#ORGANIZING DATA
data_xy = pd.DataFrame(Egrid, columns = ['energy_nu','energy_pos'])
data_xsec =pd.DataFrame( result_xsec, columns = ['xsec'] )
data_xy = pd.concat( [data_xy, data_xsec], axis=1 )

xsec_df = pd.concat([xsec_df,data_xy], axis=0, sort=False)

fig, ax1 = plt.subplots(1,2,constrained_layout=True, figsize=[6,3])
#PLOTTING
if(False):    
    ct = ax1[0].tricontourf(xsec_df['energy_nu'], xsec_df['energy_pos'], xsec_df['xsec'], levels=200, cmap='magma',vmin=0, vmax=4)
    fig.colorbar(ct,ax=ax1)
    plt.suptitle("Inverse $\\beta$ cross-section $(10^{-42})$ cm$^2$")
    ax1[0].set_title("cross-section")
    ax1[0].set_xlabel("$E_\\nu(MeV)$")
    ax1[0].set_ylabel("$E_{e^+}(MeV)$")
    ax1[0].set_yscale('log')
    ax1[0].set_xscale('log')

    #plt.show()



################################################
#ENERGY RESOLUTION
################################################

def Res(x, sigma): #x = [Etrue,Erec]
    a = 0.065
    gauss=np.exp( -(x[1]-x[0])**2/(2*sigma(x[0], a)**2) )
    denom = sqrt(2*pi)*sigma(x[0], a)
    return gauss/denom

def sig_inv_beta_old(En, a):
    if(En>1.8):
        return a*np.sqrt(En-0.8)
    else:
        return a

def sig_inv_beta(En, a):
    if(En>1.9):
        return a*np.sqrt(En-0.9)
    else:
        return a
#COMPUNTING RESOLUTION
Erec = np.geomspace(0.8, 20, 200)
Etrue = np.geomspace(Delta, 20, 200)
Egrid = list(product(Etrue,Erec))
result_res = list( map( lambda x: Res(x, sig_inv_beta), Egrid ) )

#ORGANIZING DATA
res_df = pd.DataFrame()

data_res_xy = pd.DataFrame(Egrid, columns = ['energy_true','energy_rec'])
data_res = pd.DataFrame( result_res, columns = ['distri'] )
data_res_xy = pd.concat( [data_res_xy, data_res], axis=1 )

res_df = pd.concat([res_df,data_res_xy], axis=0, sort=False)

if(False):
    fig2, ax2 = plt.subplots(1,1,constrained_layout=True)
    ct = ax2.tricontourf(res_df['energy_rec'], res_df['energy_true'], res_df['distri'], levels=200)
    fig2.colorbar(ct,ax=ax1)
    ax2.set_title("Energy resolution distribution")
    ax2.set_ylabel("$E_{true}(MeV)$")
    ax2.set_xlabel("$E_{rec}(MeV)$")
    ax2.set_yscale('log')
    ax2.set_xscale('log')
    plt.savefig("reconstructed_kamland.pdf")

    plt.show()



################################################
#CROSS-SECTION CONVOLUTION WITH ENERGY RESOLUTION
################################################

def xsec_resol(x): #x = [Enu,Epos]
    xsec_int = integrate.quad(lambda Etrue: xsec([x[0],Etrue]) * Res([Etrue,x[1]],sig_inv_beta), me, np.inf, epsabs=1.49e-300)
    return xsec_int[0]

#COMPUNTING CROSS x RESOLUTION
Enur = np.geomspace(Delta, emax, 100)
Epr = np.geomspace(me, emax, 100)
Egridr = list(product(Enur,Epr))
result_xsecr = list( map(xsec_resol,Egridr) )

#ORGANIZING DATA
xsecr_df = pd.DataFrame()

data_xyr = pd.DataFrame(Egridr, columns = ['energy_nu','energy_pos'])
data_xsecr =pd.DataFrame( result_xsecr, columns = ['xsec'] )
data_xyr = pd.concat( [data_xyr, data_xsecr], axis=1 )

xsecr_df = pd.concat([xsecr_df,data_xyr], axis=0, sort=False)

print(xsecr_df.describe())
print(xsecr_df.info())

xsecr_df.to_csv("kamland/rec_cross_section.csv")
#PLOTTING
if(False):
    ct = ax1[1].tricontourf(xsecr_df['energy_nu'], xsecr_df['energy_pos'], xsecr_df['xsec'], levels=200, cmap='magma',vmin=0, vmax=4)
    #fig.colorbar(ct,ax=ax1[1])
    #plt.title("Inverse $\\beta$ cross-section $(10^{-42})$ cm$^2$")
    ax1[1].set_title("rec. cross-section")
    ax1[1].set_xlabel("$E_\\nu(MeV)$")
    ax1[1].set_ylabel("$E_{e^+}(MeV)$")
    ax1[1].set_yscale('log')
    ax1[1].set_xscale('log')
    plt.savefig("cross_section_kamland.pdf")

    plt.show()
