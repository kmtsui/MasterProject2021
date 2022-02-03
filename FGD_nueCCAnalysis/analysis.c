void analysis()
{
    // Load a single file
    TFile* f = new TFile("data/FHC/nue/run8a_00.root");
    // Create TTree object from it
    TTree* t = (TTree*)f->Get("default");

    // Alternatively use a TChain object to load a set of files
    TChain* in_chain = new TChain("default"); // initiate with the name of the TTree to be processed
    in_chain->Add("data/FHC/nue/run8*.root"); // add files, wildcards work

    std::cout<<"TFile Entries = "<<t->GetEntries()<<std::endl;
    std::cout<<"TChain Entries = "<<in_chain->GetEntries()<<std::endl;

    // Define variables and assign them to the corresponding branches, same commands for TTree and TChain
    // Use TTree::Print() to list all available branches and data types
    int nue_signal;
    int nuesimpletopo;
    int accum_level[100]; // for array variables, reserve a large enough size
    float selelec_mom[100];
    int nEntries;

    // Uncomment if using the single TTree
    // t->SetBranchAddress("nue_signal",&nue_signal);
    // t->SetBranchAddress("accum_level",accum_level);
    // t->SetBranchAddress("selelec_mom",selelec_mom);
    // t->SetBranchAddress("nuesimpletopo",&nuesimpletopo);
    // nEntries = t->GetEntries();

    // Uncomment if using the TChain
    in_chain->SetBranchAddress("nue_signal",&nue_signal);
    in_chain->SetBranchAddress("nuesimpletopo",&nuesimpletopo);
    in_chain->SetBranchAddress("accum_level",accum_level);
    in_chain->SetBranchAddress("selelec_mom",selelec_mom);
    nEntries = in_chain->GetEntries();
	
    // Initialize histogram for plotting
    // For stack histograms one may use THStack
    TH1F* hist_mom = new TH1F("hist_mom","hist_mom",18,0,5400);
    for (int i=0; i<nEntries;i++)
    {
	    if (i%100000==0) std::cout<<"Processing "<<i<<" out of "<<nEntries<<std::endl;

        // Choose the correct input 
        // t->GetEntry(i); // loads all variables that have been connected to branches
	    in_chain->GetEntry(i);

        // Fill histogram if an event meets a certain condition
        //if ((nuesimpletopo==1 || nuesimpletopo==2) && accum_level[0]>17)
        if ((nuesimpletopo==3) && accum_level[0]>17)
        {
            hist_mom->Fill(selelec_mom[0]);
        }
    }

    // Create a canvas for display
    TCanvas* c1 = new TCanvas();
    hist_mom->Draw();
    // Save as pdf if necessary
    // c1->SaveAs("hist_mom.pdf");
}
