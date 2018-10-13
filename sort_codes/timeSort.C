#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
char * folderName="pulserTestInflAtscat";
Int_t RunNum=0;

void timeSort(){

  TFile * f1 = new TFile(Form("../../data/%s_0/UNFILTERED/compass_%s_%d.root",folderName,folderName,RunNum), "READ");
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
  printf("=================== # of Entry: %u\n", nEntries);
  
  int countCh = 0;
  int nonPairCount = 0;
  double dTime = TMath::QuietNaN();
  //nEntries = 15;
  for(int i = 0 ; i < nEntries; i++){
    
    //initiallization
    countCh = 0;
    for( int k = 0; k < 10; k++){
      ch[k] = -1;
      ezero_t[k] = 0;
      ezero[k] = TMath::QuietNaN();
    }
    
    for( int k = 0; k < 100; k++){
      e[k]    = TMath::QuietNaN();
      xf[k]   = TMath::QuietNaN();
      xn[k]   = TMath::QuietNaN();
      rdt[k]  = TMath::QuietNaN();
      tac[k]  = TMath::QuietNaN();
      if( k < 32 ) elum[k] = TMath::QuietNaN();
      
      e_t[k]    = TMath::QuietNaN();
      xf_t[k]   = TMath::QuietNaN();
      xn_t[k]   = TMath::QuietNaN();
      rdt_t[k]  = TMath::QuietNaN();
      tac_t[k]  = TMath::QuietNaN();
      if( k < 32 ) elum_t[k] = TMath::QuietNaN();
      
    }
    
    dTime = TMath::QuietNaN();
    tree->GetEntry(i);
    
    //printf("=========== %d | %d, %15llu\n", i, Channel, Timestamp);
    Int_t trigChannel=0;
    for (Int_t k=0;k<2;k++) {
      if (k==1) trigChannel=6;
      if( Channel == trigChannel) {
	countCh ++;
	ch[trigChannel] = 0;
	ezero_t[trigChannel] = Timestamp;
	ezero[trigChannel] = (Float_t)Energy;
	//printf("      0  %d | %d, %15llu\n", i, ch[0], e_t[0]);
      }else{
	continue;
      }
      
      for( int j = i+1 ; j < i + 100; j++){
	tree->GetEntry(j);
	if( Channel != trigChannel+1 ) continue;
	dTime = ((int)Timestamp - (int)ezero_t[trigChannel])/1e8;
	//printf("     (%3d,%3d) ( %15f, %15f )= dTime : %f \n",i,j, Timestamp/1e8, ezero_t[0]/1e8, dTime);
	if( Channel == trigChannel+1 && TMath::Abs(dTime) < 0.01) {
	  countCh ++;
	  ch[trigChannel+1] = 0;
	  ezero_t[trigChannel+1] = Timestamp;
	  ezero[trigChannel+1] = (Float_t)Energy;
	  //printf("      4  %d | %d, %15llu\n", i, ch[1], ezero_t[1]);
	  break;
	}	
      }
    }
    
    if( countCh >= 2 ) {
      //printf("%6d | %d, %d, %15llu, %15llu | %d\n", i, ch[0], ch[1], e_t[0], e_t[1], (int)e_t[0]- (int)e_t[1]);
      newTree->Fill();
    }else{
      nonPairCount ++;
    }
  }
  
  newTree->Write();
  int pEntries = newTree->GetEntries();
  printf("-------------- done. gen.root, event: %d\n",  pEntries);
  printf(" non-Pair count: %d \n", nonPairCount);
  saveFile->Close();
  
}
