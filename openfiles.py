##@file openfiles.py
#In this program the user can choose to filter (or not) the datas and which analysis wants to do.
#
# We enabled multi-threading. The default here is set to a single thread. You can choose the number of threads based on your system.
#

import argparse
import ROOT

ROOT.EnableImplicitMT()

def process(choice, filepath_MC, filepath_datas, filename_MC_fil, filename_datas_fil, analysis):
    '''
    This function takes six strings given by argparse, which the user will give from terminal. It will process datas
    and it will do the test chosen by the user.
   
    choice: string that could be 'y' or 'n', if 'y' the program will filter the datas, if 'n' it will look for 
    files already filtered
    filepath_MC: string of the path of the MC file to filter
    filepath_datas: string of the path of the RUN file to filter
    filename_MC_fil: string of the name of the MC file already filtered
    filename_datas_fil: string of the name of the RUN file already filtered
    analysis: string that represents the test I want to do  0: no analysis, 
    cos: costheta histograms, dimspec: Dimuon spectrum of Z, afb: Asimmetry forward backward
    
    return: None
    '''

    #only if fil is equal to 0 I can process the datas
    fil = 0
    if(choice == 'y'):
        ROOT.gInterpreter.ProcessLine('.L src/filterDf.cpp')
        fil=ROOT.filterDf(filepath_MC, filepath_datas, filename_MC_fil, filename_datas_fil)
        
    filename_MC_fil = 'datas/' + filename_MC_fil
    filename_datas_fil = 'datas/' + filename_datas_fil
    
    if fil == 0:
        if(analysis == '0'):
            print('Goodbye!')  
            quit()

        if(analysis == 'cos'): 
            ROOT.gInterpreter.ProcessLine('.L src/costheta.cpp')
            ROOT.costheta(filename_MC_fil, filename_datas_fil)
            print('If the process was fine, you will find your files in images/costheta. Goodbye!')  

        if(analysis == 'dimspec'): 
            ROOT.gInterpreter.ProcessLine('.L src/dimuonSpectrumZ.cpp') 
            ROOT.dimuonSpectrumZ(filename_MC_fil, filename_datas_fil)
            print('If the process was fine, you will find your files in images/dimuonspectrum. Goodbye!') 

        if(analysis == 'afb'): 
            ROOT.gInterpreter.ProcessLine('.L src/afb.cpp')
            ROOT.afb(filename_MC_fil, filename_datas_fil)
            print('If the process was fine, you will find your files in images/afb. Goodbye!')  


if __name__ == '__main__':

    parser = argparse.ArgumentParser(description = 'Study of the CMS Monte Carlo and Run open data for the dimuon system')

    parser.add_argument('--filter', type = str, help = 'Do you want to filter your datas? [y/n]')
    parser.add_argument('--filterMC', type = str, help = 'Only if filter is y: Choose the path of your MC dataframe (with .root extension)')
    parser.add_argument('--filterRUN', type = str, help = 'Only if filter is y: Choose the path of your RUN dataframe (with .root extension)')
    parser.add_argument('--MCfile', type = str, help = 'Choose the name of your filtered MC dataframe in datas (add .root extension)')
    parser.add_argument('--RUNfile', type = str, help = 'Choose the name of your filtered RUN dataframe in datas (add .root extension)')
    parser.add_argument('--analysis', type = str, help = 'Which analysis do you want to do? 0: no analysis, cos: costheta histograms, dimspec: Dimuon spectrum of Z, afb: Asimmetry forward backward')
    
    args = parser.parse_args()

    #if this stats are true I can process datas and make analysis
    if(args.filter is None or args.analysis is None):
        print('Cannot start the program: missing one of the arguments (filter or analysis)!')
    elif(args.filter != 'n' and args.filter != 'y'):
        print('Cannot start the program: filter is incorrect, please choose y or n!')
    elif(args.analysis != '0' and args.analysis != 'cos' and args.analysis != 'dimspec' and args.analysis != 'afb'):
        print('Cannot start the program: analysis is incorrect! Please choose between 0, dimspec, cos or afb')
    elif(args.filter == 'y' and (args.filterMC is None or args.filterRUN is None or args.MCfile is None or args.RUNfile is None)):
        print('Cannot start the program: missing the path of your files or the name of your filtered files!')
    elif(args.filter == 'n' and (args.MCfile is None or args.RUNfile is None)):
        print('Cannot start the program: few arguments!')
    elif(args.filter == 'n'):
       process(args.filter, ' ', ' ', args.MCfile, args.RUNfile, args.analysis) 
    else:
        process(args.filter, args.filterMC, args.filterRUN, args.MCfile, args.RUNfile, args.analysis)
  
        


