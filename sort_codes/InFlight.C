#define InFlight_cxx
//test
#include "InFlight.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCutG.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TString.h>
#include <TSystem.h>
#include <TObjArray.h>


#define NUMPRINT 20 //>0
#define COUNTINTERVAL 5000000
ULong64_t NUMSORT=100000000;
ULong64_t NumEntries = 0;
ULong64_t ProcessedEntries = 0;
Float_t Frac = 0.1; //Progress bar
TStopwatch StpWatch;

TCanvas *cCanvas;
TCanvas *cEX;
TGraph *graphRate;// = new TGraph(n,x,y);
Int_t n=1;

TString cutName("cut1");
TCutG* cutG; //!
TObjArray * cutList;
TString cutTag;
Bool_t isCutFileOpen;
int numCut;
vector<int> countFromCut;
TGraph ** graphRateCut; //!
TMultiGraph * rateGraph; //!

//INFL001
TH2F *hExAt;
TH2F *hExDeE,*hAtDeE;
TH2F *hExDeT,*hAtDeT;
TH2F *hExET, *hAtET;
TH2F *hAtEtotT;
TH2F *hExDeEtot,*hAtDeEtot;

//applied cut
TH2F *hExDeEg,*hAtDeEg;
TH2F *hExDeTg,*hAtDeTg;
TH2F *hExETg, *hAtETg;
TH2F *hAtEtotTg;
TH2F *hExDeEtotg,*hAtDeEtotg;

//calibrated, no cut
TH2F *hExDeEc,*hAtDeEc;
TH2F *hExDeTc;
TH2F *hExETc;
TH2F *hExDeEtotc,*hAtDeEtotc;

//calibrated, and cut!!
TH2F *hExDeEgc,*hAtDeEgc;
TH2F *hExDeTgc;
TH2F *hExETgc;
TH2F *hExDeEtotgc,*hAtDeEtotgc;

//time in sec
Float_t timeZero=0;
Float_t timeCurrent=0;
Float_t timeRef=0;

Float_t ezero[10];

Float_t ezero_cal[5][4]={{1.286e-9,-8.463e-6,0.0519,-1.3835},{1.286e-9,-8.463e-6,0.0519,-1.3835},
			 {0.0,0.0,0.0203,-10.757},{0.0,0.0,0.0203,-10.757},{0.0,0.0,0.0203,-10.757}};
Float_t tac_slope=0.07048;//ns/ch
Float_t tac_offset=100.0;//122.0;

Float_t tempTime=-1000;
Long64_t tempTimeLong=10001;

void InFlight::Begin(TTree *tree)
{
  TString option = GetOption();
  NumEntries = tree->GetEntries();
  
  //Generate all of the histograms needed for drawing later on
  //EZERO
  //INFL001
  hExAt = new TH2F("hExAt","Raw RF (0), Exit (1,2) and ATSCAT (3,4,5) Data; Detector ; Energy [ch]",2000,-8000,16000,6,0,6);//Raw Data
  hExDeE = new TH2F("hExDeE","Exit DE-E; E [ch]; DE [ch]",2000,0,16000,12000,0,12000);//EXIT
  hExDeT = new TH2F("hExDeT","Exit DE-RF; RF [ch]; DE [ch]",500,2000,3500,2000,0,12000);//
  hExET = new TH2F("hExET","Exit E-RF; RF [ch]; E [ch]",500,2000,3500,2000,0,16000);//
  hExDeEtot = new TH2F("hExDeEtot","Exit DE-ETOT; ETOT [ch]; DE [ch]",2000,0,16000,2000,0,12000);//
  hAtDeE = new TH2F("hAtDeE","ATSCAT DE-E; E [ch]; DE [ch]",1000,0,12000,1000,0,12000);//ATSCAT
  hAtDeT = new TH2F("hAtDeT","ATSCAT DE-RF; RF [ch]; DE [ch]",1000,12000,3500,1000,0,12000);//
  hAtET = new TH2F("hAtET","ATSCAT E-RF; RF [ch]; E [ch]",500,12000,3500,500,0,16000);//
  hAtEtotT = new TH2F("hAtEtotT","ATSCAT ETOT-RF; RF [ch]; ETOT [ch]",500,12000,3500,1000,0,12000);//
  hAtDeEtot = new TH2F("hAtDeEtot","ATSCAT DE-ETOT; ETOT [ch]; DE [ch]",12000,0,24000,12000,0,12000);//ATSCAT
  
  //gated
  hExDeEg = new TH2F("hExDeEg","Exit DE-E (cut); E [ch]; DE [ch]",500,0,16000,500,0,16000);//EXIT
  hExDeTg = new TH2F("hExDeTg","Exit DE-RF (cut); RF [ch]; DE [ch]",500,12000,3500,500,0,16000);//
  hExETg = new TH2F("hExETg","Exit E-RF (cut); RF [ch]; E [ch]",500,12000,3500,500,0,16000);//
  hAtDeEg = new TH2F("hAtDeEg","ATSCAT DE-E (cut); E [ch]; DE [ch]",500,0,16000,500,0,16000);//ATSCAT
  hAtDeTg = new TH2F("hAtDeTg","ATSCAT DE-RF (cut); RF [ch]; DE [ch]",500,12000,3500,500,0,16000);//
  hAtETg = new TH2F("hAtETg","ATSCAT E-RF (cut); RF [ch]; E [ch]",500,12000,3500,500,0,16000);//
  hAtEtotTg = new TH2F("hAtEtotTg","ATSCAT ETOT-RF (cut); RF [ch]; ETOT [ch]",500,12000,3500,500,0,16000);//

  //calibrated
  hExDeEc = new TH2F("hExDeEc","Exit DE-E (cal); E [MeV]; DE [MeV]",12000,0,200,12000,0,50);//EXIT
  hExDeTc = new TH2F("hExDeTc","Exit DE-RF (cal); TAC [ns]; DE [MeV]",4000,0,1000,12000,0,50);//EXIT
  hExETc = new TH2F("hExETc","Exit E-RF (cal); TAC [ns]; E [MeV]",150,80,200,1000,0,200);//EXIT
  hExDeEtotc = new TH2F("hExDeEtotc","Exit DE-ETOT (cal); ETOT [MeV]; DE [MeV]",2500,0,250,12000,0,50);//
  hAtDeEc = new TH2F("hAtDeEc","ATSCAT DE-E (cal); E [MeV]; DE [MeV]",500,0,200,500,0,200);//ATSCAT
  hAtDeEtotc = new TH2F("hAtDeEtotc","ATSCAT DE-ETOT (cal); ETOT [MeV]; DE [MeV]",2500,0,250,12000,0,200);//ATSCAT

  //calibrated & cut
  hExDeEgc = new TH2F("hExDeEgc","Exit DE-E (cal & cut); E [MeV]; DE [MeV]",12000,0,200,12000,0,80);//EXIT
  hExDeTgc = new TH2F("hExDeTgc","Exit DE-RF (cal & cut); TAC [ns]; DE [MeV]",4000,100,180,12000,0,80);//EXIT
  hExETgc = new TH2F("hExETgc","Exit E-RF (cal & cut); TAC [ns]; E [MeV]",150,80,200,1000,0,200);//EXIT
  hExDeEtotgc = new TH2F("hExDeEtotgc","Exit DE-ETOT (cal & cut); ETOT [MeV]; DE [MeV]",2500,0,250,12000,0,50);//
  hAtDeEgc = new TH2F("hAtDeEgc","ATSCAT DE-E (cal & cut); E [MeV]; DE [MeV]",500,0,200,500,0,200);//ATSCAT

  rateGraph = new TMultiGraph();
  graphRate = new TGraph();
  graphRate->SetTitle("Total Rate [pps]");
  graphRate->SetMarkerColor(4);
  graphRate->SetMarkerStyle(20);
  graphRate->SetMarkerSize(1);

  //rateGraph->Add(graphRate);
  rateGraph->SetTitle("Instantaneous Beam rate [pps]; Delta Time [sec]; Rate [pps]");
	
  //Get any cuts;
  //TFile *fi=new TFile("cut.root");		   // open file
  TFile * fCut = new TFile("cutsFile.root");		   // open file
  isCutFileOpen = fCut->IsOpen(); 
  numCut = 0 ;
  if( isCutFileOpen ){	  
	cutList = (TObjArray *) fCut->FindObjectAny("cutList");
	numCut = cutList->GetEntries();
	printf("=========== found %d cutG \n", numCut);
	
	cutG = new TCutG();
	graphRateCut = new TGraph * [numCut];
	for(int i = 0; i < numCut ; i++){
		printf(" cut name : %s \n", cutList->At(i)->GetName());
		countFromCut.push_back(0);	
			
		graphRateCut[i] = new TGraph();
		graphRateCut[i]->SetMarkerColor(i+1);	 
		graphRateCut[i]->SetMarkerStyle(20+i);
		graphRateCut[i]->SetMarkerSize(1);
		rateGraph->Add(graphRateCut[i]);
	}
  }
  
  printf("======== number of cuts found : %d \n", numCut);
  cCanvas  = new TCanvas("cCanvas","Running Plots",1250,1000);
  cCanvas->Divide(1,3);cCanvas->cd(2);gPad->Divide(2,1);
  cCanvas->cd(3);gPad->Divide(2,1);
  cCanvas->Modified(); cCanvas->Update();
  StpWatch.Start();
}

void InFlight::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t InFlight::Process(Long64_t entry)
{
  ProcessedEntries++;
  if (ProcessedEntries<NUMSORT) {
    
    if (ProcessedEntries>NumEntries*Frac-1) {
      printf(" %3.0f%% (%llu/%llu k) processed in %6.1f seconds\n",
	     Frac*100,ProcessedEntries/1000,NumEntries/1000,StpWatch.RealTime());
      StpWatch.Start(kFALSE);
      Frac+=0.1;
    }

    b_TAC->GetEntry(entry);
    b_EZERO->GetEntry(entry);
    b_TACTimestamp->GetEntry(entry);
    b_EZEROTimestamp->GetEntry(entry);

    //Do calculations and fill histograms
 
    //EZERO
    //Fill Raw Data
    hExAt->Fill(tac[0],0);
    for (Int_t i=0;i<5;i++) hExAt->Fill(ezero[i],i+1);

    //Make ZEROS
    Float_t temp[5]={0,0,0,0,0};
    for (Int_t i=0;i<4;i++) {
      if (TMath::Abs(ezero[i])>0) {
	temp[i] = (Float_t)(TMath::Abs(ezero[i]));
      } else {
	temp[i]=0;
	ezero[i]=0;
      }
    }
      
    hExDeE->Fill(TMath::Abs(ezero[1]),TMath::Abs(ezero[0]));
    hExDeT->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[0]));
    hExET->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[1]));
    hExDeEtot->Fill(TMath::Abs(ezero[0]+ezero[1]),TMath::Abs(ezero[0]));
    hAtDeE->Fill(TMath::Abs(ezero[3]),TMath::Abs(ezero[2]));
    hAtDeT->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[2]));
    hAtET->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[3]));
    hAtEtotT->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[4]));
    hAtDeEtot->Fill(TMath::Abs(ezero[2]+ezero[3]),TMath::Abs(ezero[2]));
		    
    //calibrated
    temp[4] = temp[3]+temp[2];
    for (Int_t i=0;i<5;i++) {
      if (temp[i]>0) {
	temp[i]
	  =temp[i]*temp[i]*temp[i]*ezero_cal[i][0]
	  +temp[i]*temp[i]*ezero_cal[i][1]
	  +temp[i]*ezero_cal[i][2]
	  +ezero_cal[i][3];
      }
    }
    
    Float_t tempT = (2119.1 - TMath::Abs(tac[0]))*tac_slope+tac_offset+82.5;
    
    hExDeEc->Fill(temp[1],temp[0]);
    hExDeTc->Fill(tempT,temp[0]);
    hExETc->Fill(tempT,temp[1]);
    hExDeEtotc->Fill(temp[1]+temp[0],temp[0]);
    hAtDeEc->Fill(temp[3],temp[2]);
    hAtDeEtotc->Fill(temp[4],temp[2]);
    
	if( isCutFileOpen){
		for( int i = 0 ; i < numCut; i++ ){
			cutG = (TCutG *)cutList->At(i) ;
			if( cutG->IsInside(TMath::Abs(ezero[3]),TMath::Abs(ezero[2]))
			    || cutG->IsInside(TMath::Abs(ezero[1]),TMath::Abs(ezero[0])) ) { //CRH
				countFromCut[i] += 1;
				//printf("count %d : %d \n", i, countFromCut[i]);
				hExDeEgc->Fill(temp[1],temp[0]);
				hExDeTgc->Fill(tempT,temp[0]);
				hExETgc->Fill(tempT,temp[1]);
				hExDeEtotgc->Fill(temp[1]+temp[0],temp[0]);
				hAtDeEgc->Fill(temp[3],temp[2]);
				
				hExDeEg->Fill(TMath::Abs(ezero[1]),TMath::Abs(ezero[0]));
				hExDeTg->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[0]));
				hExETg->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[1]));
				hAtDeEg->Fill(TMath::Abs(ezero[3]),TMath::Abs(ezero[2]));
				hAtDeTg->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[2]));
				hAtETg->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[3]));
				hAtEtotTg->Fill(TMath::Abs(tac[0]),TMath::Abs(ezero[4]));
			}
		}
	}
	
	//Time
	if (TMath::Abs(ezero[0])>50 ){//CRH
	  timeCurrent = (Float_t) ezero_t[0]/1e8;
	} else if (TMath::Abs(ezero[2])>50 ){//CRH
	  timeCurrent = (Float_t) ezero_t[2]/1e8;
	}
	//initial timeZero and timeRef
	if (timeZero==0) {
	  timeZero = timeCurrent;
	  timeRef  = timeCurrent;
	}
	
	timeCurrent = timeCurrent - timeZero;
	Float_t timeDelta = timeCurrent - timeRef;
	
	if (ProcessedEntries>1 && ProcessedEntries%COUNTINTERVAL==0) {      
	  printf("Total Run Time: %10.1f sec, dT : %5.3f sec, Total Evt Rate: %10.0f pps \n",
		 timeCurrent, timeDelta,
		 ProcessedEntries/timeCurrent);
	  if( timeCurrent > 0 ){
	    graphRate->SetPoint(n-1, timeCurrent, ProcessedEntries/timeDelta);
	    if( isCutFileOpen){
	      for( int i = 0 ; i < numCut; i++ ){
		printf("cut%d : %5d, %6.3f pps \n", i+1, countFromCut[i], countFromCut[i]/timeDelta);			 
		graphRateCut[i]->SetPoint(n-1, timeCurrent, countFromCut[i]/timeDelta);
		countFromCut[i] = 0; // reset count for semi-Instantaneous beam rate;
		timeRef = timeCurrent;
	      }
	    }
	    cCanvas->cd(1);
	    rateGraph->Draw("AP");
	    rateGraph->GetXaxis()->SetRangeUser(0, timeCurrent);
	    gPad->Modified(); cCanvas->Modified(); cCanvas->Update();
	    n++;
	  }	
	  cCanvas->cd(2); gPad->cd(1); hAtDeE->Draw("colz");
	  cCanvas->cd(3); gPad->cd(1); hExDeE->Draw("colz");//CRH
	  if( isCutFileOpen){
	    for( int i = 0 ; i < numCut; i++ ){
	      cCanvas->cd(2); gPad->cd(1);	 cutList->At(i) ->Draw("same");
	      cCanvas->cd(3); gPad->cd(1);	 cutList->At(i) ->Draw("same");
	    }
	  }
	  cCanvas->cd(2); gPad->cd(2); hAtDeEtotc->Draw("colz");
	  cCanvas->cd(3); gPad->cd(2); hExDeEtotc->Draw("colz");//CRH
	  gPad->Modified(); cCanvas->Modified(); cCanvas->Update();
	  gSystem->ProcessEvents();
	}
	
   
  }
   return kTRUE;
}

void InFlight::SlaveTerminate()
{

}

void InFlight::Terminate()
{
  cCanvas->cd(1);
  if( isCutFileOpen) {
    for (int i = 0 ; i < numCut ; i++){
      graphRateCut[i]->Fit("pol0");
    }
  }
  /*
  cCanvas->Clear(); cCanvas->Divide(2,2);
  cCanvas->cd(1); hExDeEc->Draw("colz");
  cCanvas->cd(2); hExDeEtotc->Draw("colz");
  cCanvas->cd(3); gPad->SetLogy(); hExDeEtotc->ProjectionY("py",0,2500,"d");
  cCanvas->cd(4); gPad->SetLogy(); hExDeEtotc->ProjectionX("px",0,2500,"d");
  */

  //cCanvas->Clear(); hAtDeEtotc->Draw("colz");
  printf("Total Run Time: %5.1f\n",timeCurrent);

  	if( isCutFileOpen){
		for( int i = 0 ; i < numCut; i++ ){
			cutG = (TCutG *)cutList->At(i) ;
			printf("Total Counts for Cut %d: %4.0f\n",i,cutG->IntegralHist(hExDeE));
		}

	}
  
  if (ProcessedEntries>=NUMSORT)
    printf("Warning: Only Sorted %llu Events\n",NUMSORT);
  // printf("Total time for sort: %3.1f\n",StpWatch.RealTime());
  //printf("Which is a rate of: %3.1f k/s\n",(Float_t)ProcessedEntries/StpWatch.RealTime()/1000.);

  StpWatch.Start(kFALSE);
}
