# CMEPDA exam

# Study of the CMS Monte Carlo and Run open data for the dimuon system

Reproduction of the Analysis of the weak mixing angle using the forward-backward asymmetry of Drell–Yan events in pp collisions at 8 TeV.
Analysis using reduced files created from Montecarlo Simulation open data producing di-muon spectrum, the histogram of $\theta$* (the angle of the negative muon relative to the axis that bisects the angle between the direction of the quark and the reversed direction of the antiquark) and the forward-
backward asymmetry Afb histogram in function to the invariant mass.

## How to run the code?

The whole project is done in C++ files, but the compilation is done with python.
This is simply done by typing in the terminal, in the main "cmepdaexam" folder:
```bash
$ python3 openfiles.py --help
```

You can have some options:

```bash
options:
  -h, --help            show this help message and exit
  --filter FILTER       Do you want to filter your datas? [y/n]
  --filterMC FILTERMC   If filter is y: Choose the path of your MC dataframe (with .root extension) if filter is n: write none
  --filterRUN FILTERRUN
                        Choose the path of your RUN dataframe (with .root extension)
  --MCfile MCFILE       Choose the name of your filtered MC dataframe in datas (with .root extension)
  --RUNfile RUNFILE     Choose the name of your filtered RUN dataframe in datas (with .root extension)
  --analysis ANALYSIS   Which analysis do you want to do? 0: no analysis, cos: costheta histograms, dimspec: Dimuon spectrum of
                        Z, afb: Asimmetry forward backward
```

You can choose (it is mandatory):
```bash
--filter y
```
if you want to filter you data. In this case you have to write also:
```bash
--filterMC fileMC --filterRUN fileRUN --MCfile Events_MC.root --RUNfile Events_datas.root
```
For example we chose file from [here](https://eospublichttp01.cern.ch/eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/):
```bash
--filterMC root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola_merged.root
```
You can also choose:
```bash
--filter n
```
In this case you have to choose only file name already filtered:
```bash
--MCfile Events_MC.root --RUNfile Events_datas.root
```
Then you have to insert which analysis you want to do, with this option:
```bash
--analysis 
```
You can choose between:
- cos: the measurement of the angle of the negative muon in the Collins–Soper frame of the dimuon system;
- dimspec: the measurement of the Z resonance; 
- afb: the measurement of the forward-backward asymmetry;
- 0: quit.
 
After the analysis the program will stop. If your analysis well ended, you can find your plots on the directory "images". 
 
The default applied filters are on the following columns of the dataframes:
 - nMuon;
 - Muon_charge;
 - Muon_eta;
 - Muon_pt;
 - Muon_dxy;
 - Muon_pfRelIso03_chg.

Be careful: if files don't exist or they haven't the right column, the program will stop.

## How to run tests?
You can run tests just making:
```bash
$ python3 testing.py --help
```

It will appear some options:
```bash
options:
  -h, --help            show this help message and exit
  --filter FILTER       Do you want to filter your datas? [y/n]
  --filterMC FILTERMC   If filter is y: Choose the path of your MC dataframe (with .root extension)
  --filterRUN FILTERRUN
                        If filter is y: Choose the path of your RUN dataframe (with .root extension)
  --MCfile MCFILE       Choose the name of your filtered MC dataframe in datas (with .root extension)
  --RUNfile RUNFILE     Choose the name of your filtered RUN dataframe in datas (with .root extension)
  --testopt TESTOPT     Which test do you want to do? 0: no test, 1: test on filter function (no files input needed), 2: costheta
                        test (files needed), 3: test on energy (files needed), 4: test on energy formulas (files needed)
```
So you can run Test1 without any other parameter, then for the others you have to insert file names and path, as before.

Be careful: if files don't exist or they haven't the right column, the program will stop.

For semplicity you'll have to write your datas and MC names also if you want to do test1 (filter function test).
You will be able to choose the test you want to do: 
- 1: test on filter function;
- 2: test on costheta value; 
- 3: test on energy value;
- 4: test on energy formula value;
- 0: quit.

## Documentation
If you want to see the documentation done by Doxygen, click [here](https://sgamba2.github.io/index.html)
