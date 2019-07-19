//code to read in the beam scanner data and then plot the 2d XY plot
//at this point need to rip the data from pdf using graphClick

#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TRandom3.h"
#include "TString.h"
#include "TVector3.h"
#include "TCanvas.h"

using namespace std;

TString fileName;
TGraphErrors *dataGraphIn;
TGraph *graphFit;
TF1 *fitDistX;TF1 *fitDistY;

Double_t distFunction(Double_t *dataInX, Double_t *){
  return graphFit->Eval(dataInX[0]);
}


void phasePlot(void) {

  dataGraphIn = new TGraphErrors("pma001.dat","%lg %lg");

  Int_t numPoints = dataGraphIn->GetN();
  Double_t *dataInX = new Double_t[numPoints];
  Double_t *dataInY = new Double_t[numPoints];

  dataInX = dataGraphIn->GetX();
  dataInY = dataGraphIn->GetY();

  graphFit = new TGraph(numPoints);

  for (Int_t i=0;i<numPoints;i++) {
    graphFit->SetPoint(i,dataInX[i],dataInY[i]);
  }

  graphFit->Sort();
  fitDistX = new TF1("fitDistX",distFunction,75,175,0);
  fitDistX->FixParameter(0,0);
  fitDistY = new TF1("fitDistY",distFunction,325,425,0);
  fitDistY->FixParameter(0,0);

  delete[] dataInX;
  delete[] dataInY;


  TH1F *hprojX = new TH1F("hprojX","Projections",1000,-50,50);
  TH1F *hprojY = new TH1F("hprojY","Projections",1000,-50,50);
  TH2F *hXY = new TH2F("hXY","X-Y Plot; X; Y",100,-50,50,100,-50,50);
  for (Int_t i=0;i<1e6;i++) {
    double randoX = fitDistX->GetRandom()-125.0;
    double randoY = fitDistY->GetRandom()-375.0;
    //printf("randoX: %f\n",randoX);
    hprojX->Fill(randoX);
    hprojY->Fill(randoY);
    //   hXY->Fill(randoX,randoY);
  }

  //for loop to get integral points for each bin, then fill xy with sum of counts at the bin
  //Double_t tempBin = hprojX->Integral(0,100);
  for (Int_t i=0;i<100;i++) {
    for (Int_t j=0;j<100;j++) {
      Double_t tempBinX = (hprojX->Integral(i*10,i*10+10));
      Double_t tempBinY = (hprojY->Integral(j*10,j*10+10));
      Double_t temp = tempBinX + tempBinY;
      hXY->Fill(i-50,j-50,temp);
    }
  }
  // h1f->SetFillColor(45);
  // h1f->FillRandom("fitDist",100000);
  TCanvas *cc = new TCanvas("cc","Beam Profile Monitor",1000,1000);
  cc->Clear(); cc->Divide(2,2);
  cc->cd(1);
  hprojY->SetLineColor(kRed); hprojY->Draw();
  cc->cd(2);
  hXY->Draw("colz");
  cc->cd(4);
  hprojX->Draw();
}
