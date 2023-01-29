##@file testing.py
# In this program the user can choose to filter (or not) the datas and which test wants to do.
#
# We enabled multi-threading. The default here is set to a single thread. You can choose the number of threads based on your system.
#
import ROOT

ROOT.EnableImplicitMT()

#infos
print("Hi! These are the function implemented by Sara Gamba and Giulia Nigrelli to test the analysis \n")
print("Decide if you want to filter your datas or not and then write down the name of your filtered dataframes \n")
print("Then choose which test you want to do! \n Each time one of the tests will be done, the program will stop and you have to restart \n")
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
# the filepath of the MC filtered datas 
#
filepath_MC_fil=""

##
# the filepath of the Run filtered datas
#
filepath_datas_fil=""

## 
# choice make choosing if the user wants to filter datas or not
#it can be 'y' if you want to filter your dataframe or 'n' if you don't
#
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
    ##
    # testopt can be 0: no analysis, 1: costheta histograms, 2: Dimuon spectrum of Z, 3: Asimmetry forward backward
    #
    testopt = int(input('Which test do you want to do? \n0: no test \n1: test on filter function \n2: costheta test \n3: test on energy \n4: test on energy formulas\n '))
    while(testopt != 0 and testopt != 1 and testopt != 2 and testopt != 3 and testopt != 4):
        testopt = int(input('Which test do you want to do? \n0: no test \n1: test on filter function \n2: costheta test \n3: test on energy \n4: test on energy formulas\n'))
    if (testopt==0):
        print("Goodbye!")
        quit()
    if (testopt==1): 
        ROOT.gInterpreter.ProcessLine(".L tests/test_filt.cpp")
        ROOT.test_filt()
        print("Goodbye!")
        quit()
    if (testopt==2): 
        ROOT.gInterpreter.ProcessLine(".L tests/test_cos.cpp")
        ROOT.test_cos(filepath_MC_fil, filepath_datas_fil)
        print("Goodbye!")
        quit()
    if (testopt==3): 
        ROOT.gInterpreter.ProcessLine(".L tests/test_energy.cpp") 
        ROOT.test_energy(filepath_MC_fil, filepath_datas_fil)
        print("Goodbye!")
        quit()
    if (testopt==4):
        ROOT.gInterpreter.ProcessLine(".L tests/test_energy_formulas.cpp")
        ROOT.test_energy_formulas(filepath_MC_fil, filepath_datas_fil)
        print("Goodbye!")
        quit()