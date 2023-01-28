## @package openfiles.py
#  In this program the user can choose to filter (or not) the datas
#  and which analysis wants to do
#  

import ROOT

#Enable multi-threading
#The default here is set to a single thread. You can choose the number of threads based on your system.
ROOT.EnableImplicitMT()

#declering variables for the analysis
fil = 0
filepath_datas = ""
filepath_MC = ""
filepath_MC_fil=""
filepath_datas_fil=""

#make choosing if the user wants to filter datas or not
choice = input('Do you want to filter your datas? [y/n]')

#if the choice is uncorrect repeat the question
while(choice != 'y' and choice != 'n'):
    choice = input('Do you want to filter your datas? [y/n]') 

#filtering datas and opening filtered datas
if(choice == 'y'):
    ROOT.gInterpreter.ProcessLine(".L filter_df.cpp")
    filepath_MC = input('Insert your MC path: ')
    filepath_datas = input('Insert your datas path: ')
    filepath_MC_fil = input('Insert wher you want to save your filtered MC path: ')
    filepath_datas_fil = input('Insert wher you want to save your filtered datas path: ')
    fil=ROOT.filter_df(filepath_MC, filepath_datas, filepath_MC_fil, filepath_datas_fil)

#not filtering datas, opening MC and Run filtered datas
else:
    filepath_MC_fil = input('Insert your filtered MC path: ')
    filepath_datas_fil = input('Insert your filtered datas path: ')

#if the filtered datas returns 0 you can access your filtered datas
#if you chose not to filter datas, fil is already 0
if fil==0:
    #user can choose which analysis can do
    analysis = int(input('Which analysis do you want to do? \n0: no analysis \n1: costheta histograms \n2: Dimuon spectrum of Z \n3: Asimmetry forward backward \n4: make tests '))
    while(analysis != 0):
        if (analysis==1): 
            ROOT.gInterpreter.ProcessLine(".L costheta_hist.cpp")
            ROOT.costheta_hist(filepath_MC_fil,filepath_datas_fil)
        if (analysis==2): 
            ROOT.gInterpreter.ProcessLine(".L dimuon_spectrum_Z.cpp") 
            ROOT.dimuon_spectrum_Z(filepath_MC_fil,filepath_datas_fil)
        if (analysis==3): 
            ROOT.gInterpreter.ProcessLine(".L afb.cpp")
            ROOT.afb(filepath_MC_fil,filepath_datas_fil)
        if (analysis==4):
            ROOT.gInterpreter.ProcessLine(".L ../tests/test_filt.cpp")
            ROOT.test_filt()
            ROOT.gInterpreter.ProcessLine(".L ../tests/test_cos.cpp")
            ROOT.test_cos(filepath_MC_fil, filepath_datas_fil)
            ROOT.gInterpreter.ProcessLine(".L ../tests/test_energy.cpp") 
            ROOT.test_energy(filepath_MC_fil, filepath_datas_fil)
            ROOT.gInterpreter.ProcessLine(".L ../tests/test_energy_formulas.cpp")
            ROOT.test_energy_formulas(filepath_MC_fil, filepath_datas_fil)
        analysis = int(input('Which analysis do you want to do? \n0: no analysis \n1: costheta histograms \n2: Dimuon spectrum of Z \n3: Asimmetry forward backward \n4: make tests '))
    print("Goodbye!")
    
        
        
        
        


