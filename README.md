# CMEPDA exam

# Analysis of the di-muon spectrum using data from the MC simulation

Reproduction of the Analysis of the weak mixing angle using the forward-backward asymmetry of Drell–Yan events in p$\bar{p}$ collisions at 8 TeV.
Analysis using reduced files created from Montecarlo Simulation open data producing di-muon spectrum, the histogram of $\theta$* (the angle of the negative muon relative to the axis that bisects the angle between the direction of the quark and the reversed direction of the antiquark) and the forward-
backward asymmetry ($A_{FB}$) histogram in function to the invariant mass.

![](images/dimuonspectrumZ/dimuonSpectrum_Z1.pdf)

## How to run this?

The analysis needs solely a ROOT installation (6.16 or greater). You have to download a set of datas from this site:

```bash
[source /cvmfs/sft.cern.ch/lcg/views/LCG_95/x86_64-slc6-gcc8-opt/setup.sh](https://eospublichttp01.cern.ch/eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola)
```

Just run the filter_df.cpp, then you'll create the file `Events.root`, where there are some filtered columns of the initial dataframe. Be sure in the first dataset there are the following columns:

```bash
nMuon
Muon_charge
Muon_mass
Muon_eta
Muon_phi
Muon_pt
Muon_dxy
Muon_pfRelIso03
```

The analysis code itself is provided in C++. There are different files for each macro. The instructions to run the scripts is shown below:

**Root (interactive):**

```bash
root[0] .L dimuon_spectrum_Z.cpp
root[1] dimuon_spectrum_Z()
```
or 

```bash
root[0] .L costheta.cpp
root[1] costheta()
```
or

```bash
root[0] .L afb.cpp
root[1] afb()
```

**C++ (interactive):**

```bash
root -l dimuon_spectrum_Z.cpp
```
or

```bash
root -l costheta.cpp
```
or
```bash
root -l afb.cpp
```

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxxxx
**C++ (compiled):**

Note that you have to select the compiler based on your system.

```bash
g++ -O3 -o dimuonSpectrum dimuonSpectrum.C $(root-config --cflags --libs)
./dimuonSpectrum
```
