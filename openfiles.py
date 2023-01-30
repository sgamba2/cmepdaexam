##@file openfiles.py
#In this program the user can choose to filter (or not) the datas and which analysis wants to do.
#
# We enabled multi-threading. The default here is set to a single thread. You can choose the number of threads based on your system.
#
import ROOT

ROOT.EnableImplicitMT()

#infos
print("Hi! These are the function implemented by Sara Gamba and Giulia Nigrelli for the analysis : \n")
print("Measurement of the dimuon mass, the cos(theta*) and the forward-backward asymmetry of Drell–Yan events in pp collisions at 8 TeV \n")
print("Decide if you want to filter your datas or not and then write down the name of your filtered dataframes \n")
print("Then choose which analysis you want to do! \nEach time an analysis will be done, the program will stop and you have to restart \n")
print("Be careful to choose the datas correctly or the program will stop \n")

## 
# fil is the variable that enables the analysis
# initially we are setting fil to 0, then it will change values if the filter function returns something else
#
fil = 0

## 
# filepath of the Run datas to filter
#
filepath_datas = ""

## 
# the filepath of the MC datas to filter
#
filepath_MC = ""

##
# the filename of the MC filtered datas 
#
filename_MC_fil=""

##
# the filename of the Run filtered datas
#
filename_datas_fil=""

## 
# choice make choosing if the user wants to filter datas or not
#it can be 'y' if you want to filter your dataframe or 'n' if you don't
#
choice = input('Do you want to filter your datas? [y/n]')

while(choice != 'y' and choice != 'n'):
    choice = input('Do you want to filter your datas? [y/n]') 

#filtering datas and opening filtered datas
if(choice == 'y'):
    ROOT.gInterpreter.ProcessLine(".L src/filter_df.cpp")
    filepath_MC = input('Insert your MC path: ')
    filepath_datas = input('Insert your datas path: ')
    filename_MC_fil = input('Insert your filtered MC name (Be careful, put file extension .root too): \n ')
    filename_datas_fil = input('Insert your filtered Run name (Be careful, put file extension .root too): \n ')
    fil=ROOT.filter_df(filepath_MC, filepath_datas, filename_MC_fil, filename_datas_fil)

#not filtering datas, opening MC and Run filtered datas
else:
    filename_MC_fil = input('Insert your filtered MC name (Be careful, put file extension .root too): \n  ')
    filename_datas_fil = input('Insert your filtered datas name (Be careful, put file extension .root too): \n  ')

filename_MC_fil="datas/"+filename_MC_fil
filename_datas_fil="datas/"+filename_datas_fil

#if the filtered datas returns 0 you can access your filtered datas, if you chose not to filter datas, fil is already 0
if fil==0:
    ##
    # analysis can be 0: no analysis, 1: costheta histograms, 2: Dimuon spectrum of Z, 3: Asimmetry forward backward
    #
    analysis = int(input('Which analysis do you want to do? \n0: no analysis \n1: costheta histograms \n2: Dimuon spectrum of Z \n3: Asimmetry forward backward \n'))
    while(analysis != 0 and analysis != 1 and analysis != 2 and analysis != 3):
        analysis = int(input('Which analysis do you want to do? \n0: no analysis \n1: costheta histograms \n2: Dimuon spectrum of Z \n3: Asimmetry forward backward \n'))
    if(analysis==0):
        print("Goodbye!")  
        quit()
    if (analysis==1): 
        ROOT.gInterpreter.ProcessLine(".L src/costheta_hist.cpp")
        ROOT.costheta_hist(filename_MC_fil,filename_datas_fil)
        print("Goodbye!")  
        quit()
    if (analysis==2): 
        ROOT.gInterpreter.ProcessLine(".L src/dimuon_spectrum_Z.cpp") 
        ROOT.dimuon_spectrum_Z(filename_MC_fil,filename_datas_fil)
        print("Goodbye!")  
        quit()
    if (analysis==3): 
        ROOT.gInterpreter.ProcessLine(".L src/afb.cpp")
        ROOT.afb(filename_MC_fil)
        print("Goodbye!")  
        quit()

    
        


