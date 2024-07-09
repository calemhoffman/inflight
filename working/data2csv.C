#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TObjArray.h>
#include <TStyle.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TSpectrum.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TObjArray.h>
#include <iostream>
#include <fstream>
#include <TCutG.h>

using namespace std;

TString run="infl41_final6";
TString rootfile = Form("/Users/calemhoffman/Research/anl/inflight/data/infl41_cl34/%s.root",run.Data());
TString outfile = Form("/Users/calemhoffman/Research/anl/inflight/data/infl41_cl34/%s.csv",run.Data());
UInt_t e[16];
ULong64_t t[16];



void data2csv() {
    TFile *file0 = new TFile (rootfile, "read"); 
    TTree *tree = (TTree*)file0->Get("tree");
    tree->Print();
    tree->SetBranchAddress("e",e);
    tree->SetBranchAddress("t",t);
    printf("=====> /// %20s //// is loaded. Total #Entry: %10lld \n", rootfile.Data(),  tree->GetEntries());

    std::ofstream myfile;
    myfile.open(outfile);
    for (int i=0;i<16;i++) myfile << "e" << i << "," << "t" << i << ",";
    myfile << endl;

    // myfile << "detID,e,z,x,Ex,rdtID,de,e,rdte,tde,te,trdte,coinTime,thetaCM,target" << endl;
    for (int k=0;k<tree->GetEntries()-1;k++) {
        tree->GetEntry(k);
        for (int i=0;i<16;i++) myfile << e[i] << "," << t[i] << ","; 
        myfile << endl;
    }
}