void analysis()
{
    // Load a single file
    TFile* f = new TFile("data/FHC/nue/run8a_00.root");
    // Create TTree object from it
    TTree* t = (TTree*)f->Get("default");

    // Alternatively use a TChain object to load a set of files
    TChain* in_chain = new TChain("default"); // initiate with the name of the TTree to be processed
    in_chain->Add("data/FHC/nue/run8a_0*.root"); // add files, wildcards work

    std::cout<<"TFile Entries = "<<t->GetEntries()<<std::endl;
    std::cout<<"TChain Entries = "<<in_chain->GetEntries()<<std::endl;

    // Define variables and assign them to the corresponding branches, same commands for TTree and TChain
    // Use TTree::Print() to list all available branches and data types
    int nue_signal;
    int accum_level[100]; // for array variables, reserve a large enough size
    float selelec_mom[100];
    t->SetBranchAddress("nue_signal",&nue_signal);
    t->SetBranchAddress("accum_level",accum_level);
    t->SetBranchAddress("selelec_mom",selelec_mom);

    // Initialize histogram for plotting
    TH1F* hist_mom = new TH1F("hist_mom","hist_mom",18,0,5400);
    for (int i=0; i<t->GetEntries();i++)
    {
        t->GetEntry(i); // loads all variables that have been connected to branches

        // Fill histogram if an event meets a certain condition
        if (nue_signal==1 && accum_level[0]>17)
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