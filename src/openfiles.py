import ROOT
ROOT.gInterpreter.ProcessLine(".L costheta_hist.cpp")
ROOT.costheta_hist()
ROOT.gInterpreter.ProcessLine(".L dimuonspectrum_hist.cpp")
ROOT.dimuonspectrum_hist()
ROOT.gInterpreter.ProcessLine(".L afb_hist.cpp")
ROOT.afb()
