##@file testing.py
# In this program the user can choose to filter (or not) the datas and which test wants to do.
#
# We enabled multi-threading. The default here is set to a single thread. You can choose the number of threads based on your system.
#
import argparse
import ROOT

ROOT.EnableImplicitMT()

def process(choice, filepath_MC, filepath_datas, filename_MC_fil, filename_datas_fil, testopt):
    '''
    This function takes six strings given by argparse, which the user will give from terminal. It will process datas
    and it will do the test chosen by the user.
   
    choice: could be 'y' or 'n', if 'y' the program will filter the datas, if 'n' it will look for 
    files already filtered (if testopt is not equal to 1)
    filepath_MC: the path of the MC file to filter
    filepath_datas: the path of the RUN file to filter
    filename_MC_fil: the name of the MC file already filtered
    filename_datas_fil: the name of the RUN file already filtered
    testopt: it is a string that represents the test I want to do 0: no test, 1: test on filter function 
    (no files input needed), 2: costheta test (files needed), 3: test on energy (files needed), 
    4: test on energy formulas (files needed)
    
    return: None
    '''

    #only if fil is equal to 0 I can process the datas
    fil=0
    if(choice == 'y'):
        ROOT.gInterpreter.ProcessLine('.L src/filter_df.cpp')
        fil=ROOT.filter_df(filepath_MC, filepath_datas, filename_MC_fil, filename_datas_fil)
   
    filename_MC_fil='datas/'+filename_MC_fil
    filename_datas_fil='datas/'+filename_datas_fil

    #if the filtered datas returns 0 you can access your filtered datas, if you chose not to filter datas, fil is already 0
    if fil==0:
        if (testopt=='0'):
            print('Goodbye!')
            quit()
        if (testopt=='1'): 
            ROOT.gInterpreter.ProcessLine('.L tests/test_filt.cpp')
            ROOT.test_filt()
            print('Goodbye!')
            quit()
        if (testopt=='2'): 
            ROOT.gInterpreter.ProcessLine('.L tests/test_cos.cpp')
            ROOT.test_cos(filename_MC_fil, filename_datas_fil)
            print('Goodbye!')
            quit()
        if (testopt=='3'): 
            ROOT.gInterpreter.ProcessLine('.L tests/test_energy.cpp') 
            ROOT.test_energy(filename_MC_fil, filename_datas_fil)
            print('Goodbye!')
            quit()
        if (testopt=='4'):
            ROOT.gInterpreter.ProcessLine('.L tests/test_energy_formulas.cpp')
            ROOT.test_energy_formulas(filename_MC_fil, filename_datas_fil)
            print('Goodbye!')
            quit()
        if (testopt=='5'):
            ROOT.gInterpreter.ProcessLine('.L tests/test_operationhist.cpp')
            ROOT.test_operationhist()
            print('Goodbye!')
            quit()


if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Tests on the study of the CMS Monte Carlo and Run open data for the dimuon system')

    parser.add_argument('--filter', type=str, help='Do you want to filter your datas? [y/n]')
    parser.add_argument('--filterMC', type=str, help='If filter is y: Choose the path of your MC dataframe (with .root extension) ')
    parser.add_argument('--filterRUN', type=str, help='If filter is y: Choose the path of your RUN dataframe (with .root extension)')
    parser.add_argument('--MCfile', type=str, help='Choose the name of your filtered MC dataframe in datas (with .root extension)')
    parser.add_argument('--RUNfile', type=str, help='Choose the name of your filtered RUN dataframe in datas (with .root extension)')
    parser.add_argument('--testopt', type=str, help='Which test do you want to do? 0: no test, 1: test on filter function (no files needed), 2: costheta test (files needed), 3: test on energy (files needed), 4: test on energy formulas (files needed), 5: test on operation_hist (no files needed)')
    
    args = parser.parse_args()

    #if this stats are true I can process datas and make tests
    if (args.testopt is None):
        print('Cannot start the program: missing the testopt!')
    elif(args.filter is None and args.testopt != '1' and args.testopt != '5'):
        print('Cannot start the program: missing one of the arguments (filter or testopt)!')
    elif(args.filter!= 'n' and args.filter!= 'y' and args.testopt != '1' and args.testopt != '5'):
        print('Cannot start the program: filter is incorrect!')
    elif(args.testopt!= '0' and args.testopt!= '1' and args.testopt!= '2' and args.testopt!= '3' and args.testopt!= '4' and args.testopt != '5'):
        print('Cannot start the program: testopt is incorrect!')
    elif(args.filter == 'y' and (args.filterMC is None or args.filterRUN is None or args.MCfile is None or args.RUNfile is None) and args.testopt != '1' and args.testopt != '5'):
        print('Cannot start the program: missing the path of your files or the name of your filtered files!')
    elif(args.filter=='n' and (args.MCfile is None or args.RUNfile is None) and args.testopt != '1' and args.testopt != '5'):
        print('Cannot start the program: few arguments!')
    elif(args.testopt=='1'):
        process('n','','','','',args.testopt)
    elif(args.testopt=='5'):
        process('n','','','','',args.testopt)
    elif(args.filter=='n' and args.testopt != '1' and args.testopt != '5'):
        process(args.filter,'','',args.MCfile,args.RUNfile,args.testopt)
    else:
        process(args.filter,args.filterMC,args.filterRUN,args.MCfile, args.RUNfile,args.testopt)