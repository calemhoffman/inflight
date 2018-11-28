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

char * folderName = "testRF";
Int_t RunNum=2;

void caenSort(){
  
  TString fileName;
  //folderName.Form("testRF");
  fileName.Form("../../data/testRF/DAQ/%s_%d/UNFILTERED/compass_%s_%d.root",folderName,RunNum,folderName,RunNum); 
  TFile * f1 = new TFile(fileName,"READ");
  TTree * tree = (TTree *) f1->FindObjectAny("Data");
  
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
  printf("=================== # of Entries to be Sorted: %u\n", nEntries);

  /**///===================== Pull first n pieces of data into struct
  Int_t blockEvents = 200;
  UShort_t channelT[10000],channel[10000];
  ULong64_t timestampT[10000],timestamp[10000];
  UShort_t boardT[10000],board[10000];
  UShort_t energyT[10000],energy[10000];
  UInt_t flagsT[10000],flags[10000];

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
    if (entryID<40)
      printf(" %d | %d | %d | %15llu\n", entryID, channelT[entryID], energyT[entryID], timestampT[entryID]);
  }

  /**///===================== bubblesort the timestamps
  Int_t * sortIndex;
  sortIndex = new Int_t[blockEvents];
  TMath::BubbleLow(blockEvents,bubbleSortArr1,sortIndex);

  /**///===================== adjust
  for (Int_t entryID=0;entryID<blockEvents;entryID++)
    {
      channel[entryID] = channelT[sortIndex[entryID]];

      if (entryID<40)
	printf(" entryID %d | sortID %d | channelID %d \n",entryID,sortIndex[entryID],channel[entryID]);
    }
    
  newTree->Write();
  int pEntries = newTree->GetEntries();
  printf("-------------- done. gen.root, event: %d\n",  pEntries);
  saveFile->Close();
  
}
