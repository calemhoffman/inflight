{
#include "TTree.h"
  
  TTree * t = tree;
  t->Print();

  //Set cals
  Int_t location = 1; //0 - HP (exit), 1 - SSX (cross), 2 - SST (target)
  Float_t deGain=1,deOffset=0;
  Float_t eGain=1,eOffset=0;
  Int_t nDe = 2;
  Int_t nE = 5;
  TString title;
  if (location == 0) {
    deGain = 0.1;
    eGain = 0.606;
    title = "^{29}Al at the target";
    nDe = 2;
    nE = 5;
  } else if (location == 1) {
    deGain = 0.1;
    eGain = 0.606;
    title = "^{29}Al at the cross";
    nDe = 1;
    nE = 4;
  } else if (location == 2) {
    deGain = 0.1;
    eGain = 0.1;
    title = "^{29}Al at the exit";
    nDe = 0;
    nE = 3;
  }

  //Histos and draw
  Int_t xBin = 1000;
  Int_t yBin = 1000;
  Int_t xHigh = 1500;
  Int_t yHigh = 6000;

  TH2F *hdEtotE = new TH2F("hdEtotE",Form("%s; Total E [MeV]; DE [MeV]",title.Data()),
			   yBin,0,yHigh,
			   xBin,0,xHigh);

  TH1F *htotE = new TH1F("htotE",Form("%s; Total E [MeV]",title.Data()),
			 yBin,0,yHigh);

  TCanvas *cc = new TCanvas("cc","cc",800,800);
  cc->Clear(); cc->Divide(1,2); cc->cd(1); gPad->SetLogz(1); cc->cd(2); gPad->SetLogy(1);

  cc->cd(1);
  tree->Draw(Form("e[%d]*%f:e[%d]*%f+e[%d]*%f>>hdEtotE",nDe,deGain,
		  nDe,deGain,nE,eGain),
	     "","colz");
  tree->Draw(Form("e[%d]*%f+e[%d]*%f>>htotE",nDe,deGain,nE,eGain));


  //Draw nicely
  hdEtotE->SetMinimum(1);
  
  hdEtotE->Draw("colz");

  cc->cd(2);
  htotE->Draw();

  
}
