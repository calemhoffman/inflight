{
//========= Macro generated from object: cut_test/cut_test
//========= by ROOT version6.22/06
   
   TCutG *cutg = new TCutG("cut_test",6);
   cutg->SetVarX("etotcal");
   cutg->SetVarY("decal");
   cutg->SetTitle("cut_test");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,409.939,137.5);
   cutg->SetPoint(1,409.46,122.446);
   cutg->SetPoint(2,429.12,122.446);
   cutg->SetPoint(3,429.12,139.651);
   cutg->SetPoint(4,409.46,139.651);
   cutg->SetPoint(5,409.939,137.5);
   cutg->Draw("");
}
