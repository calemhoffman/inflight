void infl20_scale1011()
{
//=========Macro generated from canvas: cc/cc
//=========  (Fri May 14 10:27:31 2021) by ROOT version 6.22/06
   TCanvas *cc = new TCanvas("cc", "cc",0,53,800,848);
   gStyle->SetOptFit(1);
   cc->ToggleEventStatus();
   cc->ToggleToolTips();
   cc->Range(0,0,1,1);
   cc->SetFillColor(0);
   cc->SetBorderMode(0);
   cc->SetBorderSize(2);
   cc->SetGridx();
   cc->SetGridy();
   cc->SetTickx(1);
   cc->SetTicky(1);
   cc->SetFrameFillColor(10);
   cc->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: cc_1
   TPad *cc_1 = new TPad("cc_1", "cc_1",0.01,0.51,0.99,0.99);
   cc_1->Draw();
   cc_1->cd();
   cc_1->Range(0,0,1,1);
   cc_1->SetFillColor(0);
   cc_1->SetBorderMode(0);
   cc_1->SetBorderSize(2);
   cc_1->SetGridx();
   cc_1->SetGridy();
   cc_1->SetTickx(1);
   cc_1->SetTicky(1);
   cc_1->SetFrameFillColor(10);
   cc_1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: cc_1_1
   TPad *cc_1_1 = new TPad("cc_1_1", "cc_1_1",0.01,0.01,0.49,0.99);
   cc_1_1->Draw();
   cc_1_1->cd();
   cc_1_1->Range(0,0,1,1);
   cc_1_1->SetFillColor(0);
   cc_1_1->SetBorderMode(0);
   cc_1_1->SetBorderSize(2);
   cc_1_1->SetLogz();
   cc_1_1->SetGridx();
   cc_1_1->SetGridy();
   cc_1_1->SetTickx(1);
   cc_1_1->SetTicky(1);
   cc_1_1->SetFrameFillColor(10);
   cc_1_1->SetFrameBorderMode(0);
   
   TH2F *hdEtotE = new TH2F("hdEtotE","cross: Scale 101.1",1000,360,480,1000,80,160);
   hdEtotE->SetMinimum(1);
   hdEtotE->SetStats(0);
   hdEtotE->GetXaxis()->SetTitle(" Total E [MeV]");
   hdEtotE->GetXaxis()->SetLabelSize(0.04);
   hdEtotE->GetXaxis()->SetTitleSize(0.04);
   hdEtotE->GetXaxis()->SetTitleOffset(1);
   hdEtotE->GetYaxis()->SetTitle(" DE [MeV]");
   hdEtotE->GetYaxis()->SetLabelSize(0.04);
   hdEtotE->GetYaxis()->SetTitleSize(0.04);
   hdEtotE->GetYaxis()->SetTitleOffset(1);
   hdEtotE->GetZaxis()->SetLabelSize(0.04);
   hdEtotE->GetZaxis()->SetTitleSize(0.04);
   hdEtotE->GetZaxis()->SetTitleOffset(1);
   hdEtotE->Draw("colz");
   cc_1_1->Modified();
   cc_1->cd();
  
// ------------>Primitives in pad: cc_1_2
   TPad *cc_1_2 = new TPad("cc_1_2", "cc_1_2",0.51,0.01,0.99,0.99);
   cc_1_2->Draw();
   cc_1_2->cd();
   cc_1_2->Range(0,0,1,1);
   cc_1_2->SetFillColor(0);
   cc_1_2->SetBorderMode(0);
   cc_1_2->SetBorderSize(2);
   cc_1_2->SetGridx();
   cc_1_2->SetGridy();
   cc_1_2->SetTickx(1);
   cc_1_2->SetTicky(1);
   cc_1_2->SetFrameFillColor(10);
   cc_1_2->SetFrameBorderMode(0);
   
   TH2F *hdEtotEg__1 = new TH2F("hdEtotEg__1","gated cross: Scale 101.1",1000,360,480,1000,80,160);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   hdEtotEg__1->SetMarkerColor(ci);
   hdEtotEg__1->GetXaxis()->SetTitle(" Total E [MeV]");
   hdEtotEg__1->GetXaxis()->SetLabelSize(0.04);
   hdEtotEg__1->GetXaxis()->SetTitleSize(0.04);
   hdEtotEg__1->GetXaxis()->SetTitleOffset(1);
   hdEtotEg__1->GetYaxis()->SetTitle(" DE [MeV]");
   hdEtotEg__1->GetYaxis()->SetLabelSize(0.04);
   hdEtotEg__1->GetYaxis()->SetTitleSize(0.04);
   hdEtotEg__1->GetYaxis()->SetTitleOffset(1);
   hdEtotEg__1->GetZaxis()->SetLabelSize(0.04);
   hdEtotEg__1->GetZaxis()->SetTitleSize(0.04);
   hdEtotEg__1->GetZaxis()->SetTitleOffset(1);
   hdEtotEg__1->Draw("");
   cc_1_2->Modified();
   cc_1->cd();
   cc_1->Modified();
   cc->cd();
  
// ------------>Primitives in pad: cc_2
   TPad *cc_2 = new TPad("cc_2", "cc_2",0.01,0.01,0.99,0.49);
   cc_2->Draw();
   cc_2->cd();
   cc_2->Range(0,0,1,1);
   cc_2->SetFillColor(0);
   cc_2->SetBorderMode(0);
   cc_2->SetBorderSize(2);
   cc_2->SetGridx();
   cc_2->SetGridy();
   cc_2->SetTickx(1);
   cc_2->SetTicky(1);
   cc_2->SetFrameFillColor(10);
   cc_2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: cc_2_1
   TPad *cc_2_1 = new TPad("cc_2_1", "cc_2_1",0.01,0.01,0.49,0.99);
   cc_2_1->Draw();
   cc_2_1->cd();
   cc_2_1->Range(0,0,1,1);
   cc_2_1->SetFillColor(0);
   cc_2_1->SetBorderMode(0);
   cc_2_1->SetBorderSize(2);
   cc_2_1->SetLogz();
   cc_2_1->SetGridx();
   cc_2_1->SetGridy();
   cc_2_1->SetTickx(1);
   cc_2_1->SetTicky(1);
   cc_2_1->SetFrameFillColor(10);
   cc_2_1->SetFrameBorderMode(0);
   
   TH2F *hdEdT = new TH2F("hdEdT","cross: Scale 101.1",50,380,430,1000,80,160);
   hdEdT->SetMinimum(1);
   hdEdT->SetStats(0);
   hdEdT->GetXaxis()->SetTitle(" TOF [ns]");
   hdEdT->GetXaxis()->SetLabelSize(0.04);
   hdEdT->GetXaxis()->SetTitleSize(0.04);
   hdEdT->GetXaxis()->SetTitleOffset(1);
   hdEdT->GetYaxis()->SetTitle(" DE [MeV]");
   hdEdT->GetYaxis()->SetLabelSize(0.04);
   hdEdT->GetYaxis()->SetTitleSize(0.04);
   hdEdT->GetYaxis()->SetTitleOffset(1);
   hdEdT->GetZaxis()->SetLabelSize(0.04);
   hdEdT->GetZaxis()->SetTitleSize(0.04);
   hdEdT->GetZaxis()->SetTitleOffset(1);
   hdEdT->Draw("colz");
   cc_2_1->Modified();
   cc_2->cd();
  
// ------------>Primitives in pad: cc_2_2
   TPad *cc_2_2 = new TPad("cc_2_2", "cc_2_2",0.51,0.01,0.99,0.99);
   cc_2_2->Draw();
   cc_2_2->cd();
   cc_2_2->Range(0,0,1,1);
   cc_2_2->SetFillColor(0);
   cc_2_2->SetBorderMode(0);
   cc_2_2->SetBorderSize(2);
   cc_2_2->SetGridx();
   cc_2_2->SetGridy();
   cc_2_2->SetTickx(1);
   cc_2_2->SetTicky(1);
   cc_2_2->SetFrameFillColor(10);
   cc_2_2->SetFrameBorderMode(0);
   
   TH2F *hdEdTg__2 = new TH2F("hdEdTg__2","gated cross: Scale 101.1",50,380,430,1000,80,160);

   ci = TColor::GetColor("#ff0000");
   hdEdTg__2->SetMarkerColor(ci);
   hdEdTg__2->GetXaxis()->SetTitle(" TOF [ns]");
   hdEdTg__2->GetXaxis()->SetLabelSize(0.04);
   hdEdTg__2->GetXaxis()->SetTitleSize(0.04);
   hdEdTg__2->GetXaxis()->SetTitleOffset(1);
   hdEdTg__2->GetYaxis()->SetTitle(" DE [MeV]");
   hdEdTg__2->GetYaxis()->SetLabelSize(0.04);
   hdEdTg__2->GetYaxis()->SetTitleSize(0.04);
   hdEdTg__2->GetYaxis()->SetTitleOffset(1);
   hdEdTg__2->GetZaxis()->SetLabelSize(0.04);
   hdEdTg__2->GetZaxis()->SetTitleSize(0.04);
   hdEdTg__2->GetZaxis()->SetTitleOffset(1);
   hdEdTg__2->Draw("");
   cc_2_2->Modified();
   cc_2->cd();
   cc_2->Modified();
   cc->cd();
   cc->Modified();
   cc->cd();
   cc->SetSelected(cc);
   cc->ToggleToolBar();
}
