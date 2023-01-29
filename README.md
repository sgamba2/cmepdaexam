# CMEPDA exam

# Analysis of the di-muon spectrum using data from the MC simulation

Reproduction of the Analysis of the weak mixing angle using the forward-backward asymmetry of Drell–Yan events in pp collisions at 8 TeV.
Analysis using reduced files created from Montecarlo Simulation open data producing di-muon spectrum, the histogram of $\theta$* (the angle of the negative muon relative to the axis that bisects the angle between the direction of the quark and the reversed direction of the antiquark) and the forward-
backward asymmetry Afb histogram in function to the invariant mass.

## How to run this?

The whole project is done in C++ files, but the compilation is done with python.
This is simply done by typing in the terminal, in the main "cmepdaexam" folder:
```bash
$ python3 openfiles.py
```
Be careful: in order to make your analysis working you have to be in the main folder "cmepdaexam".
 
The program will ask you if you want to filter your datas or not. 
 
If you type 'y', you have to insert your root path to the file for MC and Run, and also the path where you want to save your filtered dataframes. 
 
We used root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola_merged.root for the MC simulation datas.
 
We used root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2012C_DoubleMuParked_merged.root for the Run datas.
 
This is simply done (this is an example) by typing in the terminal:
```bash
$ Insert your MC path:
$ root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola_merged.root
$ Insert your Run path:
$ root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2012C_DoubleMuParked_merged.root
```

Then the program will ask you where do you want to put your filtered dataframes.
 
This is simply done (this is an example) by typing in the terminal:
```bash
$ Insert where you want to save your filtered MC path:
$ datas/Events_MC.root
$ Insert where you want to save your filtered Run path:
$ datas/Events_datas.root
```
 
If you type 'n', you will have to insert the path of your filtered file. It only accepts root files, with the right columns.
This is simply done (this is an example) by typing in the terminal:
```bash
$ Insert your filtered MC path:
$ datas/Events_MC.root
$ Insert your filtered Run path:
$ datas/Events_datas.root
```

You will be able to choose the Analysis you want: 
 1: the measurement of the angle of the negative muon in the Collins–Soper frame of the dimuon system;
 2: the measurement of the Z resonance; 
 3: the measurement of the forward-backward asymmetry;
 0: quit.
 
 The default applied filters are on the following columns of the dataframes:
 - nMuon;
 - Muon_charge;
 - Muon_eta;
 - Muon_pt;
 - Muon_dxy;
 - Muon_pfRelIso03_chg.
