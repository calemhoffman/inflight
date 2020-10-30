void statSheet(Int_t loc=0){
#include "TTree.h"

  TTree * t = tree;
  t->Print();

  //Set cals
  Int_t location = loc; //0 - HP (exit), 1 - SSX (cross), 2 - SST (target)
  Float_t deGain=1.0,deOffset=0.0;
  Float_t eGain=1.0,eOffset=0.0;
  Int_t nDe = 0;
  Int_t nE = 0;
  TString title;
  if (location == 3) {
   deGain = 0.03;
   eGain = 0.5;
   title = "XY Target";
   nDe = 1;
   nE = 7;
  } else if (location == 2) {
    deGain = 0.2;
    eGain = 1.0;
    title = "ZD or Target";
    nDe = 2;
    nE = 5;
  } else if (location == 1) {
    deGain = 0.25;
    eGain = 1.0;
    title = "Cross";
    nDe = 1;
    nE = 4;
  } else if (location == 0) {
    deGain = 0.25;
    eGain = 1.0;
    title = "Exit: 2.5% Scale";
    nDe = 0;
    nE = 3;
  }

  //Histos and draw
  Int_t xBin = 1000;
  Int_t yBin = 1000;
  Int_t xLow = 3000;
  Int_t xHigh = 7500;
  Int_t yHigh = 3000;

  TH2F *hdEtotE = new TH2F("hdEtotE",Form("%s; Total E [MeV]; DE [MeV]",title.Data()),
			   xBin,xLow,xHigh,
			   yBin,0,yHigh);

  TH1F *htotE = new TH1F("htotE",Form("%s; Total E [MeV]",title.Data()),
			 xBin,xLow,xHigh);

  TCanvas *cc = new TCanvas("cc","cc",800,800);
  cc->Clear(); cc->Divide(1,2); cc->cd(1); gPad->SetLogz(1); cc->cd(2); gPad->SetLogy(1);


 if (location<3) {
    cc->cd(1);
    tree->Draw(Form("e[%d]*%f:e[%d]*%f+e[%d]*%f>>hdEtotE",nDe,deGain,
    	  nDe,deGain,nE,eGain),
         "","colz");
    tree->Draw(Form("e[%d]*%f+e[%d]*%f>>htotE",nDe,deGain,nE,eGain));
  } else {
    cc->cd(1);
    tree->Draw(Form("(e[%d]+e[%d])*%f:e[%d]*%f>>hdEtotE",
    nDe,nDe+3,deGain,
    nE,eGain),"","colz");
    tree->Draw(Form("e[%d]*%f>>htotE",
    nE,eGain));
  }

  //Draw nicely
  hdEtotE->SetMinimum(1);
  //hdEtotE->SetStats(0);
  hdEtotE->Draw("colz");

  cc->cd(2);
  htotE->Draw();

  cc->SaveAs("n16.C");
  cc->SaveAs("n16.png");


}
