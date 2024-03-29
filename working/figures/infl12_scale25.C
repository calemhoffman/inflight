void infl12_scale25()
{
//=========Macro generated from canvas: cc/cc
//=========  (Mon Apr 26 11:31:46 2021) by ROOT version 6.22/06
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
   cc_1->SetLogz();
   cc_1->SetGridx();
   cc_1->SetGridy();
   cc_1->SetTickx(1);
   cc_1->SetTicky(1);
   cc_1->SetFrameFillColor(10);
   cc_1->SetFrameBorderMode(0);
   
   TH2F *hdEtotE = new TH2F("hdEtotE","exit: Scale 25",1000,3000,16000,1000,0,2000);
   hdEtotE->SetBinContent(1270,1);
   hdEtotE->SetBinContent(1298,1);
   hdEtotE->SetBinContent(1383,1);
   hdEtotE->SetBinContent(1478,1);
   hdEtotE->SetBinContent(1547,1);
   hdEtotE->SetBinContent(2003,226);
   hdEtotE->SetBinContent(567131,1);
   hdEtotE->SetBinContent(661319,1);
   hdEtotE->SetBinContent(691379,1);
   hdEtotE->SetBinContent(722441,1);
   hdEtotE->SetBinContent(748493,1);
   hdEtotE->SetBinContent(750497,1);
   hdEtotE->SetBinContent(757511,1);
   hdEtotE->SetBinContent(763523,1);
   hdEtotE->SetBinContent(768533,1);
   hdEtotE->SetBinContent(795587,1);
   hdEtotE->SetBinContent(818633,1);
   hdEtotE->SetBinContent(847691,1);
   hdEtotE->SetBinContent(850697,1);
   hdEtotE->SetBinContent(852701,1);
   hdEtotE->SetBinContent(855707,1);
   hdEtotE->SetBinContent(857711,1);
   hdEtotE->SetBinContent(864725,2);
   hdEtotE->SetBinContent(865727,1);
   hdEtotE->SetBinContent(869735,1);
   hdEtotE->SetBinContent(874745,2);
   hdEtotE->SetBinContent(879755,1);
   hdEtotE->SetBinContent(902801,1);
   hdEtotE->SetBinContent(905807,1);
   hdEtotE->SetBinContent(908813,1);
   hdEtotE->SetBinContent(917832,1);
   hdEtotE->SetBinContent(919835,2);
   hdEtotE->SetBinContent(921839,1);
   hdEtotE->SetBinContent(929855,1);
   hdEtotE->SetBinContent(939875,1);
   hdEtotE->SetBinContent(940877,2);
   hdEtotE->SetBinContent(943883,1);
   hdEtotE->SetBinContent(946889,1);
   hdEtotE->SetBinContent(952901,1);
   hdEtotE->SetBinContent(953903,1);
   hdEtotE->SetBinContent(954905,1);
   hdEtotE->SetBinContent(956909,3);
   hdEtotE->SetBinContent(957911,1);
   hdEtotE->SetBinContent(962921,1);
   hdEtotE->SetBinContent(965927,1);
   hdEtotE->SetBinContent(968933,1);
   hdEtotE->SetBinContent(969935,1);
   hdEtotE->SetBinContent(972941,1);
   hdEtotE->SetBinContent(976949,1);
   hdEtotE->SetBinContent(978953,1);
   hdEtotE->SetBinContent(981959,1);
   hdEtotE->SetBinContent(982961,1);
   hdEtotE->SetBinContent(984965,1);
   hdEtotE->SetBinContent(985967,1);
   hdEtotE->SetBinContent(987971,1);
   hdEtotE->SetBinContent(990978,1);
   hdEtotE->SetBinContent(991979,2);
   hdEtotE->SetBinContent(997991,1);
   hdEtotE->SetBinContent(998993,1);
   hdEtotE->SetBinContent(999995,2);
   hdEtotE->SetBinContent(1003002,29);
   hdEtotE->SetBinContent(1003009,1);
   hdEtotE->SetBinContent(1003011,2);
   hdEtotE->SetBinContent(1003025,1);
   hdEtotE->SetBinContent(1003034,1);
   hdEtotE->SetBinContent(1003040,1);
   hdEtotE->SetBinContent(1003053,2);
   hdEtotE->SetBinContent(1003061,1);
   hdEtotE->SetBinContent(1003062,1);
   hdEtotE->SetBinContent(1003064,1);
   hdEtotE->SetBinContent(1003083,1);
   hdEtotE->SetBinContent(1003095,1);
   hdEtotE->SetBinContent(1003101,1);
   hdEtotE->SetBinContent(1003115,1);
   hdEtotE->SetBinContent(1003132,1);
   hdEtotE->SetBinContent(1003139,1);
   hdEtotE->SetBinContent(1003157,1);
   hdEtotE->SetBinContent(1003163,1);
   hdEtotE->SetBinContent(1003196,1);
   hdEtotE->SetBinContent(1003263,1);
   hdEtotE->SetBinContent(1003266,1);
   hdEtotE->SetBinContent(1003319,1);
   hdEtotE->SetBinContent(1003388,1);
   hdEtotE->SetBinContent(1003402,19);
   hdEtotE->SetBinContent(1003458,1);
   hdEtotE->SetBinContent(1003610,1);
   hdEtotE->SetBinContent(1003648,1);
   hdEtotE->SetBinContent(1003700,2);
   hdEtotE->SetBinContent(1003964,1);
   hdEtotE->SetBinContent(1003972,1);
   hdEtotE->SetBinContent(1004003,1472);
   hdEtotE->SetMinimum(1);
   hdEtotE->SetEntries(1844);
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
   
   TH1F *htotEg__1 = new TH1F("htotEg__1","exit: Scale 25",1000,3000,16000);
   htotEg__1->SetBinContent(0,31);
   htotEg__1->SetBinContent(7,1);
   htotEg__1->SetBinContent(9,2);
   htotEg__1->SetBinContent(23,1);
   htotEg__1->SetBinContent(32,1);
   htotEg__1->SetBinContent(38,1);
   htotEg__1->SetBinContent(51,2);
   htotEg__1->SetBinContent(59,1);
   htotEg__1->SetBinContent(60,1);
   htotEg__1->SetBinContent(62,1);
   htotEg__1->SetBinContent(81,1);
   htotEg__1->SetBinContent(93,1);
   htotEg__1->SetBinContent(99,1);
   htotEg__1->SetBinContent(113,1);
   htotEg__1->SetBinContent(130,1);
   htotEg__1->SetBinContent(137,1);
   htotEg__1->SetBinContent(155,1);
   htotEg__1->SetBinContent(161,1);
   htotEg__1->SetBinContent(194,1);
   htotEg__1->SetBinContent(261,1);
   htotEg__1->SetBinContent(264,1);
   htotEg__1->SetBinContent(317,1);
   htotEg__1->SetBinContent(386,1);
   htotEg__1->SetBinContent(400,19);
   htotEg__1->SetBinContent(456,1);
   htotEg__1->SetBinContent(608,1);
   htotEg__1->SetBinContent(646,1);
   htotEg__1->SetBinContent(698,2);
   htotEg__1->SetBinContent(962,1);
   htotEg__1->SetBinContent(970,1);
   htotEg__1->SetBinContent(1001,1532);
   htotEg__1->SetEntries(1613);

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
   
   TH1F *htotE__2 = new TH1F("htotE__2","exit: Scale 25",1000,3000,16000);
   htotE__2->SetBinContent(0,31);
   htotE__2->SetBinContent(7,1);
   htotE__2->SetBinContent(9,2);
   htotE__2->SetBinContent(23,1);
   htotE__2->SetBinContent(32,1);
   htotE__2->SetBinContent(38,1);
   htotE__2->SetBinContent(51,2);
   htotE__2->SetBinContent(59,1);
   htotE__2->SetBinContent(60,1);
   htotE__2->SetBinContent(62,1);
   htotE__2->SetBinContent(81,1);
   htotE__2->SetBinContent(93,1);
   htotE__2->SetBinContent(99,1);
   htotE__2->SetBinContent(113,1);
   htotE__2->SetBinContent(130,1);
   htotE__2->SetBinContent(137,1);
   htotE__2->SetBinContent(155,1);
   htotE__2->SetBinContent(161,1);
   htotE__2->SetBinContent(194,1);
   htotE__2->SetBinContent(261,1);
   htotE__2->SetBinContent(264,1);
   htotE__2->SetBinContent(268,1);
   htotE__2->SetBinContent(296,1);
   htotE__2->SetBinContent(317,1);
   htotE__2->SetBinContent(381,1);
   htotE__2->SetBinContent(386,1);
   htotE__2->SetBinContent(400,19);
   htotE__2->SetBinContent(456,1);
   htotE__2->SetBinContent(476,1);
   htotE__2->SetBinContent(545,1);
   htotE__2->SetBinContent(608,1);
   htotE__2->SetBinContent(646,1);
   htotE__2->SetBinContent(698,2);
   htotE__2->SetBinContent(962,1);
   htotE__2->SetBinContent(970,1);
   htotE__2->SetBinContent(1001,1758);
   htotE__2->SetEntries(1844);
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
