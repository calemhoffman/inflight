#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TSpectrum.h>
#include <TGraph.h>
#include <fstream>
#include <TProof.h>
#include <TString.h>
#include <string>
#include <TLine.h>

#define toPrint 5
Int_t setBlockEventNumber = 500000;
Double_t deltaTimestampConstant=0.3; //in microseconds
//^^^^^^---- coincidence window, if > then new event..

TString folderName("exit_oct31");
Int_t RunNum=9; //Change for each new run!!!
//TString folderName;
//Int_t RunNum;

TH1D * hDeltaTime;
TH1I * hEventMultiplicity;

void barbasol(Int_t runNumberInput=0){
//int barbasol(int argc, char *argv[]){
//sscanf(argv[1],"%s",&folderName);
//sscanf(argv[2],"%d",&RunNum);
  
  if (runNumberInput!=0) RunNum=runNumberInput;
  
  TString fileName;
  //folderName.Form("testRF");
  fileName.Form("~/Desktop/infl3/exit/DAQ/%s_%d/UNFILTERED/compass_%s_%d.root",folderName.Data(),RunNum,folderName.Data(),RunNum); 
  TFile * f1 = new TFile(fileName,"READ");
  TTree * tree = (TTree *) f1->FindObjectAny("Data");

  hDeltaTime = new TH1D("hDeltaTime","Time Differences Between Data; Delta Time [u-seconds]",
			1000,0,5);
  hEventMultiplicity = new TH1I("hEventMultiplicity","Multiplicity for each event; Mult",
				20,0,20);
  
  UShort_t Channel;
  ULong64_t Timestamp;
  UShort_t Board;
  UShort_t Energy;
  UInt_t Flags;
  
  tree->SetBranchAddress("Channel", &Channel);
  tree->SetBranchAddress("Timestamp", &Timestamp);
  tree->SetBranchAddress("Board", &Board);
  tree->SetBranchAddress("Energy", &Energy);
  tree->SetBranchAddress("Flags", &Flags);
  
  //======= make new tree
  TFile * saveFile = new TFile("gen.root", "recreate");
  TTree * newTree = new TTree("gen_tree", "PSD Tree");

  int ch[10];
  ULong64_t ezero_t[10];
  float ezero[10];
  
  newTree->Branch("ch", ch, "ch[10]/I");
  newTree->Branch("ezero",     ezero, "EZERO[10]/F");
  newTree->Branch("ezero_t", ezero_t, "EZEROTimestamp[10]/l");
  
  //dummy branch for Monitor.C
  float e[100], xf[100], xn[100], rdt[100], tac[100], elum[32];
  ULong64_t e_t[100], xf_t[100], xn_t[100], rdt_t[100], tac_t[100], elum_t[100];
  
  newTree->Branch("e",           e,"Energy[100]/F");
  newTree->Branch("e_t",       e_t,"EnergyTimestamp[100]/l");
  newTree->Branch("xf",         xf,"XF[100]/F");
  newTree->Branch("xf_t",     xf_t,"XFTimestamp[100]/l");
  newTree->Branch("xn",         xn,"XN[100]/F");
  newTree->Branch("xn_t",     xn_t,"XNTimestamp[100]/l"); 
  newTree->Branch("rdt",       rdt,"RDT[100]/F");
  newTree->Branch("rdt_t",   rdt_t,"RDTTimestamp[100]/l"); 
  newTree->Branch("tac",       tac,"TAC[100]/F");
  newTree->Branch("tac_t",   tac_t,"TACTimestamp[100]/l"); 
  newTree->Branch("elum",     elum,"ELUM[32]/F");
  newTree->Branch("elum_t", elum_t,"ELUMTimestamp[32]/l"); 
  
  //============ Processing 
  int nEntries = tree->GetEntries();
  if (nEntries < setBlockEventNumber) setBlockEventNumber = nEntries;
  printf("======= File processed = %s_%i\n",folderName.Data(),RunNum);
  printf("=================== # of Entries Avail: %d | and to be Sorted: %u\n", nEntries, setBlockEventNumber);

  /**///===================== Pull first n pieces of data into struct
  Int_t blockEvents = setBlockEventNumber;
  UShort_t channelT[setBlockEventNumber],channel[setBlockEventNumber];
  ULong64_t timestampT[setBlockEventNumber],timestamp[setBlockEventNumber];
  UShort_t boardT[setBlockEventNumber],board[setBlockEventNumber];
  UShort_t energyT[setBlockEventNumber],energy[setBlockEventNumber];
  UInt_t flagsT[setBlockEventNumber],flags[setBlockEventNumber];

  Double_t *bubbleSortArr1;
  bubbleSortArr1 = new Double_t[blockEvents];

  for (Int_t entryID=0;entryID<blockEvents;entryID++) {
    tree->GetEntry(entryID);
    channelT[entryID] = Channel;
    timestampT[entryID] = Timestamp;
    bubbleSortArr1[entryID] = (Double_t)Timestamp/1e12;
    boardT[entryID] = Board;
    energyT[entryID] = Energy;
    flagsT[entryID] = Flags;
    if (entryID<toPrint)
      printf(" %d | %d | %d | %15llu\n", entryID, channelT[entryID], energyT[entryID], timestampT[entryID]);
  }

  /**///===================== bubblesort the timestamps
  Int_t * sortIndex;
  sortIndex = new Int_t[blockEvents];
  TMath::BubbleLow(blockEvents,bubbleSortArr1,sortIndex);

  /**///===================== map based on bubble sort
  for (Int_t entryID=0;entryID<blockEvents;entryID++)
    {
      channel[entryID] = channelT[sortIndex[entryID]];
      timestamp[entryID] = timestampT[sortIndex[entryID]];
      board[entryID] = boardT[sortIndex[entryID]];
      energy[entryID] = energyT[sortIndex[entryID]];
      flags[entryID] = flagsT[sortIndex[entryID]];

      if (entryID<toPrint)
	printf(" entryID %d | sortID %d | channelID %d | ts %12llu | energy %d\n",entryID,sortIndex[entryID],channel[entryID],timestamp[entryID],energy[entryID]);
    }

  /**///===================== scan, make event, and TTree
  Double_t deltaTime=TMath::QuietNaN();
  Int_t eventMultCounter=0;
  
  for (Int_t entryID=1;entryID<blockEvents;entryID++)
    {
      deltaTime = double(timestamp[entryID]-timestamp[entryID-1]);
      hDeltaTime->Fill(deltaTime/1e6);
      eventMultCounter++;
      if (entryID<toPrint)
	printf(" entryID %d-%d | deltaTime/1e6 %2.10f \n",entryID,entryID-1,deltaTime/1e6);
      
      if (deltaTime/1e6>deltaTimestampConstant) { //fill the ttree w/ data
	newTree->Fill();
	hEventMultiplicity->Fill(eventMultCounter);
	//zero out ttree params and dt for safety
	for (Int_t cleanID=0;cleanID<10;cleanID++) {
	  ezero[cleanID]=TMath::QuietNaN();
	  ezero_t[cleanID]=TMath::QuietNaN();
	  deltaTime = TMath::QuietNaN();
	}
	eventMultCounter=0;
      }
      //Always pass current entry to ttree arrays
	ezero[channel[entryID]] = energy[entryID];
	ezero_t[channel[entryID]] = timestamp[entryID];
    }
  TCanvas *cc = new TCanvas("cc","cc",1000,500);
  cc->Clear();cc->Divide(1,2);
  cc->cd(1);
  gPad->SetLogy(1);
  hDeltaTime->SetMinimum(1); hDeltaTime->Draw();
  cc->Update();
  TLine *l=new TLine(deltaTimestampConstant,0,deltaTimestampConstant,hDeltaTime->GetMaximum());
  l->SetLineColor(kBlue);
  l->Draw();
  cc->cd(2);
  hEventMultiplicity->Draw();
  cc->Update();
 
  
  newTree->Write();
  hDeltaTime->Write();
  deltaTime = double(timestamp[blockEvents-1]-timestamp[1])/1e12;
  printf("============== run length: %5.2f seconds\n", deltaTime);
  int pEntries = newTree->GetEntries();
  printf("-------------- done. gen.root, event: %d\n",  pEntries);
  printf("======= File processed = %s_%i\n",folderName.Data(),RunNum);
  saveFile->Close();

  TChain * chain = new TChain("gen_tree");
  chain->Add("gen.root");
  chain->Process("../sort_codes/InFlight.C++");
  printf("======= File processed = %s_%i\n",folderName.Data(),RunNum);
}
