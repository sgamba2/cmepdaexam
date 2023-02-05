# CMEPDA exam

# Study of the CMS Monte Carlo and Run open data for the dimuon system

This C++/ROOT Library was created by Sara Gamba and Giulia Nigrelli for the Computing Methods
for Experimental Physics and Data Analysis exam.

# Introduction
Using MC and Run datas of the dimuon events of CMS, the main goals of this library are essentially three:
-the measurement of the Z resonance; 
-the measurement of the angle of the negative muon in the Collins–Soper frame of the dimuon system;
-the measurement of the forward-backward asymmetry.

This functionalities are built in order to recreate similar plots of the article  
[Measurement of the weak mixing angle using the forward-backward asymmetry of Drell–Yan events in pp collisions at 8 TeV](https://arxiv.org/abs/1806.00863) 
by the CMS collaboration.

For simplifying the usage, a main is provided in order to execute the program.

## Requirements

 - CERN ROOT 6.26
 - Python3

## An example of usage

The whole project is done in C++ files, but the compilation is done with python.
You can type in the terminal, in the main "cmepdaexam" folder:
```bash
python3 openfiles.py --help
```

You can have some options:
```bash
options:
-h, --help            show this help message and exit
--filter FILTER       Do you want to filter your datas? [y/n]
--filterMC FILTERMC   If filter is y: Choose the path of your MC dataframe  
--filterRUN FILTERRUN If filter is y: Choose the path of your RUN dataframe 
--MCfile MCFILE       Choose the name of your filtered MC dataframe in datas (add .root extension)
--RUNfile RUNFILE     Choose the name of your filtered RUN dataframe in datas (add .root extension)
--analysis ANALYSIS   Which analysis do you want to do? 0: no analysis, cos: costheta histograms, dimspec: Dimuon spectrum of Z, afb: Asimmetry forward backward
```


You have to choose (the filter option is mandatory) if you want to filter your datas or not. In the first case:
```bash
--filter y
```
In this case you have to write also:
```bash
--filterMC fileMC --filterRUN fileRUN --MCfile Events_MC.root --RUNfile Events_datas.root
```
For example we chose file from [here](https://eospublichttp01.cern.ch/eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/):
```bash
--fileMC root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola_merged.root
--fileRUN root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2012C_DoubleMuParked_merged.root
```
The program will accept only files that exist and that have the right columns, if there aren't the program will stop.
Then you have to choose the name of your filtered dataframes files.
Be careful: you have to put the .root extension to your filtered files or you won't be able to use them.
In this case you have to choose only file name already filtered:
```bash
--MCfile Events_MC.root --RUNfile Events_datas.root
```
If you have already used the filter function for one of the analysis and you don't want to
repeat it, you can choose to not filter your datas:
```bash
--filter n
```
Then you have to choose the name of your filtered dataframes files.
Be careful: you have to put the .root extension to your filtered files or you won't be able to use them.
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



## Testing

We have done tests in C++, but the compilation is done with python.
You can type in the terminal, in the main "cmepdaexam" folder:
```bash
python3 testing.py --help
```

You can have some options:
```bash
 options:
 -h, --help            show this help message and exit
 --filter FILTER       Do you want to filter your datas? [y/n]
 --filterMC FILTERMC   If filter is y: Choose the path of your MC dataframe  
 --filterRUN FILTERRUN If filter is y: Choose the path of your RUN dataframe 
 --MCfile MCFILE       Choose the name of your filtered MC dataframe in datas (add .root extension)
 --RUNfile RUNFILE     Choose the name of your filtered RUN dataframe in datas (add .root extension)
 --testopt TESTOPT     Which test do you want to do? 0: no test, 1: test on
                       filter function (no files needed), 2: costheta test
                       (files needed), 3: test on energy (files needed), 4:
                       test on energy formulas (files needed), 5: test on
                       operation_hist (no files needed)
```


You have to choose (the filter option is mandatory only for tests 2, 3, 4) if you want to filter your datas or not. In the first case:
```bash
--filter y
```
In this case you have to write also:
```bash
--filterMC fileMC --filterRUN fileRUN --MCfile Events_MC.root --RUNfile Events_datas.root
```
For example we chose file from [here](https://eospublichttp01.cern.ch/eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/):
```bash
--fileMC root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola_merged.root
--fileRUN root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2012C_DoubleMuParked_merged.root
```
The program will accept only files that exist and that have the right columns, if there aren't the program will stop.
Then you have to choose the name of your filtered dataframes files.
Be careful: you have to put the .root extension to your filtered files or you won't be able to use them.
In this case you have to choose only file name already filtered:
```bash
--MCfile Events_MC.root --RUNfile Events_datas.root
```
If you have already used the filter function for one of the analysis and you don't want to
repeat it, you can choose to not filter your datas:
```bash
 --filter n
```
Then you have to choose the name of your filtered dataframes files.
Be careful: you have to put the .root extension to your filtered files or you won't be able to use them.
In this case you have to choose only file name already filtered:
```bash
--MCfile Events_MC.root --RUNfile Events_datas.root
```
Then you have to insert which test you want to do, with this option:
```bash
 --testopt 
```
If you want to do test 5 or 1 it is not necessary to write the filter option. You can only put the testopt.
 
You will be able to choose the test you want to do: 
- 1: test on filter function;
- 2: test on costheta value; 
- 3: test on energy value;
- 4: test on energy formula value;
- 5: test on operation histograms;
- 0: quit.
 
After a test your program will stop. If the test well ended there will be written "Test passed!".
The default applied filters are on the following columns of the dataframes:
- nMuon;
- Muon_charge;
- Muon_eta;
- Muon_pt;
- Muon_dxy;
- Muon_pfRelIso03_chg.
 

## Documentation
If you want to see the documentation done by Doxygen, click [here](https://sgamba2.github.io/index.html)
