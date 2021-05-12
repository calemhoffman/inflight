void statSheet(Int_t loc=1,Int_t expNum=21,Int_t scaleNum=100){
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
    deGain = 0.25;
    eGain = 1.0;
    title = Form("ZD or Target: Scale %d",scaleNum);
    nDe = 2;
    nE = 5;
  } else if (location == 1) {
    deGain = 1.0;//0.25;//0.05;//0.25
    eGain = 1.0;
    title = Form("cross: Scale %.1f",scaleNum/10.0);
    nDe = 1;
    nE = 4;
    //if (expNum==21)
  } else if (location == 0) {
    deGain = 0.25;
    eGain = 1.0;
    title = Form("exit: Scale %d",scaleNum);
    nDe = 0;
    nE = 3;
  }

  //Histos and draw
  Int_t xBin = 1000;
  Int_t yBin = 1000;
  Int_t xLow = 0;
  Int_t yLow=0;
  Int_t xHigh = 40000;
  Int_t yHigh = 10000;

  if (expNum == 10) {
    xHigh=10000;
    yHigh=1500;
  }
  if (expNum == 11) {
    xLow=4000;
    xHigh=7500;
    yHigh=3500;
  }
  if (expNum == 12) {
    xLow=3000;
    xHigh=8000;
    yHigh=1500;
  }
  if (expNum == 16) {
    xLow=5000;
    xHigh=14000;
    yHigh=2400;
  }
  if (expNum == 17) {
    xHigh=8000;
    xLow=3000;
    yHigh=3000;
  }
  if (expNum == 19) {
    xHigh=200;//300;
    xLow=0;
    yHigh=150;//
  }
  if (expNum == 20) {
    xHigh=480;//300;
    xLow=360;
    yLow=80;
    yHigh=160;//
  }


TH2F *hdEtotE = new TH2F("hdEtotE",Form("%s; Total E [MeV]; DE [MeV]",title.Data()),
xBin,xLow,xHigh,
yBin,yLow,yHigh);
TH2F *hdEtotEg = new TH2F("hdEtotEg",Form("gated %s; Total E [MeV]; DE [MeV]",title.Data()),
xBin,xLow,xHigh,
yBin,yLow,yHigh);

TH2F *hdEdT = new TH2F("hdEdT",Form("%s; TOF [ns]; DE [MeV]",title.Data()),
50,380,430,
yBin,yLow,yHigh);
TH2F *hdEdTg = new TH2F("hdEdTg",Form("gated %s; TOF [ns]; DE [MeV]",title.Data()),
50,380,430,
yBin,yLow,yHigh);

TH1F *htotE = new TH1F("htotE",Form("%s; Total E [MeV]",title.Data()),
xBin,xLow,xHigh);
TH1F *htotEg = new TH1F("htotEg",Form("%s; Total E [MeV]",title.Data()),
xBin,xLow,xHigh);

  TCanvas *cc = new TCanvas("cc","cc",800,800);
  cc->Clear(); cc->Divide(1,2);
  cc->cd(1); gPad->Divide(2,1); cc->cd(1)->cd(1); gPad->SetLogz(1);
  cc->cd(2); gPad->Divide(2,1); cc->cd(2)->cd(1); gPad->SetLogz(1);

Float_t cal1=0.1310;//e
Float_t cal2=11.030;
Float_t cal3=0.0335;//de
Float_t cal4=-1.610;//
Float_t tcal1=0.4749;//
Float_t tcal2=306.69;//

if (expNum<20) {
  cal1 = 1.0;
  cal2 = cal1; cal3 = cal1; cal4 = cal1;
}

tree->SetAlias("decal",Form("e[%d]*%f+%f",nDe,cal3,cal4));
tree->SetAlias("ecal",Form("e[%d]*%f+%f",nE,cal1,cal2));
tree->SetAlias("etotcal","decal+ecal");
tree->SetAlias("tofcal",Form("((timeStamp[1]-timeStamp[7])*2.0+400)*%f+%f",tcal1,tcal2));

 if (location<3) {
    cc->cd(1)->cd(1);
    tree->Draw(Form("decal:etotcal>>hdEtotE"),"","colz");
    tree->Draw(Form("decal:etotcal>>hdEtotEg"),Form(""),"colz");
    tree->Draw(Form("etotcal>>htotE"));
    tree->Draw(Form("etotcal>>htotEg"),Form("e[%d]>100",nDe),"");
    tree->Draw(Form("decal:tofcal>>hdEdT"),Form(""),Form(""));
    tree->Draw(Form("decal:tofcal>>hdEdTg"),Form("cut_dee1_1030"),Form(""));
  } else {
    cc->cd(1)->cd(1);
    tree->Draw(Form("(e[%d]+e[%d])*%f:e[%d]*%f>>hdEtotE",
    nDe,nDe+3,deGain,
    nE,eGain),"","colz");
    tree->Draw(Form("e[%d]*%f>>htotE",
    nE,eGain));
  }

  //Draw nicely
  cc->cd(1)->cd(1);
  hdEtotE->SetMinimum(1);
  hdEtotE->SetStats(0);
  hdEtotE->Draw("colz");
  cc->cd(1)->cd(2);
  hdEtotEg->SetMarkerColor(kRed);
  hdEtotEg->Draw("same");

  cc->cd(2)->cd(1);
  // htotEg->SetLineColor(kRed);
  // htotEg->SetFillColor(kRed);
  // htotEg->Draw();
  // htotE->Draw("same");
  hdEdT->SetMinimum(1);
  hdEdT->Draw("colz");
  hdEdT->SetStats(0);
  cc->cd(2)->cd(2);
  hdEdTg->SetMarkerColor(kRed);hdEdTg->Draw("same");

  cc->SaveAs(Form("figures/infl%d_scale%d.C",expNum,scaleNum));
  cc->SaveAs(Form("figures/infl%d_scale%d.png",expNum,scaleNum));


}
