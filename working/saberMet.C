void saberMet(Int_t scaleNum=100){
#include "TTree.h"
Int_t numCuts=10;
Int_t MaxNChannels=8;

TFile * file = new TFile("infl20/infl20_scale1000.root");
TTree * tree = (TTree *) file->Get("tree");
tree->Print();

  Float_t cal3=0.1310;//de
  Float_t cal4=11.030;
  Float_t cal1=0.0335;//e
  Float_t cal2=-1.610;//
  Float_t tcal1=0.4749;//t
  Float_t tcal2=306.69;//

  // tree->SetAlias("decal",Form("e[1]*%f+%f",cal1,cal2));
  // tree->SetAlias("ecal",Form("e[4]*%f+%f",cal3,cal4));
  // tree->SetAlias("etotcal","decal+ecal");
  // tree->SetAlias("tofcal",Form("((timeStamp[1]-timeStamp[7])*2.0+400)*%f+%f",tcal1,tcal2));

tree->SetBranchStatus("*",0);
tree->SetBranchStatus("e",1);
tree->SetBranchStatus("t",1);

UInt_t    e[MaxNChannels]; TBranch * b_energy;
ULong64_t t[MaxNChannels]; TBranch * b_timeStamp;

tree->SetBranchAddress("e", e, &b_energy);
tree->SetBranchAddress("t", t, &b_timeStamp);

Long64_t totalEvent = tree->GetEntries();

printf("Number of event : %lld \n", totalEvent);

ULong64_t timeZero = 0;
ULong64_t oldTime = 0;
ULong64_t timeEnd = 0;

Double_t timeDiff;
Int_t count = 0;

ULong64_t initTimeStamp = 0;
ULong64_t finalTimeStamp = 0;

//histograms
TH2F *hdEtotE[numCuts];
for (Int_t i=0;i<numCuts;i++) {
  hdEtotE[i] = new TH2F(Form("hdEtotE%d",i),Form("hdEtotE%d; Total E [MeV]; DE [MeV]",i),
  500,360,480,
  500,80,160);
}
Float_t decal,ecal,tofcal;
//event loop
for(int ev = 0; ev < totalEvent; ev++){
  tree->GetEntry(ev);
  decal=(float)e[1]*cal1+cal2;
  ecal=(float)e[4]*cal3+cal4;
  hdEtotE[0]->Fill(e[4],e[1]);
}

hdEtotE[0]->Draw("colz");
}
