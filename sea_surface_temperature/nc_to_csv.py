# This script assumes that you have downloaded the sst.mon.mean.nc file from the download sites described in the README.md
# It will extract the information from the .nc file and convert it to the given folder structures using a more accessible csv format
import scipy.io as sio
import h5py
import numpy as np

import os

nc_file = "sst.mon.mean.nc"
infile =  h5py.File(nc_file,'r')
sst = infile.get("sst")


# 1891/01 - 2022/07
def index_to_month(index):
    year, month = divmod(index,12)
    return (1850+year,month+1)

for i in range(0,len(sst)):
    year,month = index_to_month(i)
    print(year,month)
    try:
        os.makedirs(f"./{year}", exist_ok = True)
    except :
        pass

    np.savetxt(f"{year}/{month}.csv",sst[i], delimiter=",")
