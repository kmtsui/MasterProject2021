# MasterProject2021

## FGD_nueCCAnalysis
Sample MC data for the nue cross-section analysis in https://link.springer.com/article/10.1007%2FJHEP10%282020%29114

### ref
Partial source code of event selection and variables

nueCCSelection/antiNueCCSelection: selection cuts and step numbers

nueCCAnalysis: variable definition

CategToolsNueCC: definition of signal and background topology

### data
Data files for neutrino mode (FHC) and antineutrino mode (RHC) run

### analysis.c
Sample analysis code to read data and make plots
#### Important variables
accum_level: accumulated number of cuts that an event passes

nuesimpletopo: 1 & 2 = nueCC, 3 = gamma bkg, 4 = muon bkg, others = others

particle: truth PDG ID of the event main track 