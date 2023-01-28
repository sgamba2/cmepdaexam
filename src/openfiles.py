import ROOT
# Enable multi-threading
# The default here is set to a single thread. You can choose the number of threads based on your system.
ROOT.EnableImplicitMT()
fil = 0
filepath_datas = ""
filepath_MC = ""
choice = input('Do you want to filter your datas? [y/n]')
while(choice != 'y' and choice != 'n'):
    choice = input('Do you want to filter your datas? [y/n]') 
if(choice == 'y'):
    ROOT.gInterpreter.ProcessLine(".L filter_df.cpp")
    filepath_MC = input('Insert your MC path: ')
    filepath_datas = input('Insert your datas path: ')
    fil=ROOT.filter_df(filepath_MC, filepath_datas)
    filepath_MC="../datas/Events_MC.root"
    filepath_datas="../datas/Events_datas.root"
else:
    filepath_MC = input('Insert your filtered MC path: ')
    filepath_datas = input('Insert your filtered datas path: ')

if fil==0:
    analysis = int(input('Which analysis do you want to do? \n0: no analysis \n1: costheta histograms \n2: Dimuon spectrum of Z \n3: Asimmetry forward backward \n4: make tests '))
    while(analysis != 0):
        if (analysis==1): 
            ROOT.gInterpreter.ProcessLine(".L costheta_hist.cpp")
            ROOT.costheta_hist(filepath_MC,filepath_datas)
        if (analysis==2): 
            ROOT.gInterpreter.ProcessLine(".L dimuon_spectrum_Z.cpp") 
            ROOT.dimuon_spectrum_Z(filepath_MC,filepath_datas)
        if (analysis==3): 
            ROOT.gInterpreter.ProcessLine(".L afb.cpp")
            ROOT.afb(filepath_MC,filepath_datas)
        if (analysis==4):
            ROOT.gInterpreter.ProcessLine(".L ../tests/test_filt.cpp")
            ROOT.test_filt()
            ROOT.gInterpreter.ProcessLine(".L ../tests/test_cos.cpp")
            ROOT.test_cos(filepath_MC, filepath_datas)
            ROOT.gInterpreter.ProcessLine(".L ../tests/test_energy.cpp") 
            ROOT.test_energy(filepath_MC, filepath_datas)
            ROOT.gInterpreter.ProcessLine(".L ../tests/test_energy_formulas.cpp")
            ROOT.test_energy_formulas(filepath_MC, filepath_datas)
        analysis = int(input('Which analysis do you want to do? \n0: no analysis \n1: costheta histograms \n2: Dimuon spectrum of Z \n3: Asimmetry forward backward \n4: make tests '))
    print("Goodbye")
    
        
        
        
        


