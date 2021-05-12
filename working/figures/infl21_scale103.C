void infl21_scale103()
{
//=========Macro generated from canvas: cc/cc
//=========  (Fri May  7 20:48:34 2021) by ROOT version 6.22/06
   TCanvas *cc = new TCanvas("cc", "cc",0,53,800,847);
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
   cc_1->SetLogz();
   cc_1->SetGridx();
   cc_1->SetGridy();
   cc_1->SetTickx(1);
   cc_1->SetTicky(1);
   cc_1->SetFrameFillColor(10);
   cc_1->SetFrameBorderMode(0);
   
   TH2F *hdEtotE = new TH2F("hdEtotE","cross: Scale 10.3",1000,0,40000,1000,0,10000);
   hdEtotE->SetBinContent(0,450);
   hdEtotE->SetBinContent(2,1635);
   hdEtotE->SetBinContent(3,9131);
   hdEtotE->SetBinContent(4,2431);
   hdEtotE->SetBinContent(5,12);
   hdEtotE->SetBinContent(16,4040);
   hdEtotE->SetMinimum(1);
   hdEtotE->SetEntries(17699);
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
   cc_2->SetLogy();
   cc_2->SetGridx();
   cc_2->SetGridy();
   cc_2->SetTickx(1);
   cc_2->SetTicky(1);
   cc_2->SetFrameFillColor(10);
   cc_2->SetFrameBorderMode(0);
   
   TH1F *htotEg__1 = new TH1F("htotEg__1","cross: Scale 10.3",1000,0,40000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   htotEg__1->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   htotEg__1->SetLineColor(ci);
   htotEg__1->GetXaxis()->SetTitle(" Total E [MeV]");
   htotEg__1->GetXaxis()->SetLabelSize(0.04);
   htotEg__1->GetXaxis()->SetTitleSize(0.04);
   htotEg__1->GetXaxis()->SetTitleOffset(1);
   htotEg__1->GetYaxis()->SetLabelSize(0.04);
   htotEg__1->GetYaxis()->SetTitleSize(0.04);
   htotEg__1->GetYaxis()->SetTitleOffset(1);
   htotEg__1->GetZaxis()->SetLabelSize(0.04);
   htotEg__1->GetZaxis()->SetTitleSize(0.04);
   htotEg__1->GetZaxis()->SetTitleOffset(1);
   htotEg__1->Draw("");
   
   TH1F *htotE__2 = new TH1F("htotE__2","cross: Scale 10.3",1000,0,40000);
   htotE__2->SetBinContent(0,450);
   htotE__2->SetBinContent(2,1635);
   htotE__2->SetBinContent(3,9131);
   htotE__2->SetBinContent(4,2431);
   htotE__2->SetBinContent(5,12);
   htotE__2->SetBinContent(16,4040);
   htotE__2->SetEntries(17699);
   htotE__2->GetXaxis()->SetTitle(" Total E [MeV]");
   htotE__2->GetXaxis()->SetLabelSize(0.04);
   htotE__2->GetXaxis()->SetTitleSize(0.04);
   htotE__2->GetXaxis()->SetTitleOffset(1);
   htotE__2->GetYaxis()->SetLabelSize(0.04);
   htotE__2->GetYaxis()->SetTitleSize(0.04);
   htotE__2->GetYaxis()->SetTitleOffset(1);
   htotE__2->GetZaxis()->SetLabelSize(0.04);
   htotE__2->GetZaxis()->SetTitleSize(0.04);
   htotE__2->GetZaxis()->SetTitleOffset(1);
   htotE__2->Draw("same");
   cc_2->Modified();
   cc->cd();
   cc->Modified();
   cc->cd();
   cc->SetSelected(cc);
   cc->ToggleToolBar();
}
