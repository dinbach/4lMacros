{
  // string outdir = "";
  // string inputdir = "";
  string outdir = "../OutputPlots/";
  string inputdir = "../OutputFiles/";
  gROOT->ProcessLine("#include <vector>");
  gROOT->ProcessLine("#include <string>");
  gROOT->ProcessLine(".x doAtlasStyle.C");

  TFile *f[3];
  f[0] = TFile::Open((inputdir+"hists_FF_data.root").c_str());
  TH1::AddDirectory(kTRUE);
  f[1] = TFile::Open((inputdir+"hists_FF_ZplusJets.root").c_str());
  TH1::AddDirectory(kTRUE);
  f[2] = TFile::Open((inputdir+"hists_FF_SherpaZplusJets.root").c_str());
  TH1::AddDirectory(kTRUE);

  string elrecotype[1] = {"central"};
  string murecotype[3] = {"central","forw","calo"};
  int netypes = sizeof( elrecotype)/sizeof(elrecotype[0]);
  int nmutypes = sizeof( murecotype)/sizeof(murecotype[0]);

  const int nFiles=3; //data +mc1 +mc2
  TH1F *pt_mu_FF[3][nFiles];
  TH1F *eta_mu_FF[3][nFiles];
  TH1F *pt_el_FF[1][nFiles];
  TH1F *eta_el_FF[1][nFiles];

  TH2F *pt_eta_el_FF[3][nFiles];
  TH2F *pt_eta_mu_FF[3][nFiles];

  for (int ifile=0;ifile<nFiles;ifile++) {
    for (int i=0;i<nmutypes;i++) {
      pt_mu_FF[i][ifile] = (TH1F*) (f[ifile]->Get(Form("pt_%smu_FF",murecotype[i].c_str())))->Clone(Form("pt_%smu_FF_DATA",murecotype[i].c_str()));
      pt_mu_FF[i][ifile]->SetYTitle("fake factor");
      eta_mu_FF[i][ifile] = (TH1F*) (f[ifile]->Get(Form("eta_%smu_FF",murecotype[i].c_str())))->Clone(Form("eta_%smu_FF_DATA",murecotype[i].c_str()));
      eta_mu_FF[i][ifile]->SetYTitle("fake factor");

    }
    for (int i=0;i<netypes;i++) {
      pt_el_FF[i][ifile] = (TH1F*) (f[ifile]->Get(Form("pt_%sel_FF",elrecotype[i].c_str())))->Clone(Form("pt_%sel_FF_DATA",elrecotype[i].c_str()));
      pt_el_FF[i][ifile]->SetYTitle("fake factor");
      eta_el_FF[i][ifile] = (TH1F*) (f[ifile]->Get(Form("eta_%sel_FF",elrecotype[i].c_str())))->Clone(Form("eta_%sel_FF_DATA",elrecotype[i].c_str()));
      eta_el_FF[i][ifile]->SetYTitle("fake factor");
    }
  }

  for (int i=0;i<nmutypes;i++)
  {
    pt_eta_mu_FF[i][0] = (TH2F*) (f[0]->Get(Form("pt_eta_%smu_FF",murecotype[i].c_str())))->Clone(Form("pt_eta_%smu_FF_DATA",murecotype[i].c_str()));
    pt_eta_mu_FF[i][0]->SetYTitle("fake factor");
  }

  for (int i=0;i<netypes;i++) {
    pt_eta_el_FF[i][0] = (TH2F*) (f[0]->Get(Form("pt_eta_%sel_FF",elrecotype[i].c_str())))->Clone(Form("pt_eta_%sel_FF_DATA",elrecotype[i].c_str()));
    pt_eta_el_FF[i][0]->SetYTitle("fake factor");
  }


  const Int_t NRGBs = 5;
  const Int_t NCont = 255;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  gStyle->SetOptStat(0);



  TCanvas c2("c2","c2");
  TLatex t1; t1.SetNDC();
  t1.SetTextColor(1);
  t1.SetTextSize(0.04);

  pt_eta_mu_FF[0][0]->Draw("colz");
  pt_eta_mu_FF[0][0]->GetXaxis()->SetRangeUser(6,200);
  pt_eta_mu_FF[0][0]->GetYaxis()->SetRangeUser(0,2.7);
  pt_eta_mu_FF[0][0]->GetXaxis()->SetTitle("p_{T}");
  pt_eta_mu_FF[0][0]->GetYaxis()->SetTitle("#eta");
  pt_eta_mu_FF[0][0]->GetZaxis()->SetRangeUser(0.0,0.5);
  t1.DrawLatex(0.4,0.94,"central muon fake factor");
  c2.SaveAs((outdir+"ff_mu_pteta_central.pdf").c_str());

  pt_eta_mu_FF[1][0]->Draw("colz");
  pt_eta_mu_FF[1][0]->GetXaxis()->SetRangeUser(6,200);
  pt_eta_mu_FF[1][0]->GetYaxis()->SetRangeUser(2.5,2.7);
  pt_eta_mu_FF[1][0]->GetXaxis()->SetTitle("p_{T}");
  pt_eta_mu_FF[1][0]->GetYaxis()->SetTitle("#eta");
  pt_eta_mu_FF[1][0]->GetZaxis()->SetRangeUser(0.0,3.0);
  t1.DrawLatex(0.4,0.94,"fwd muon fake factor");
  c2.SaveAs((outdir+"ff_mu_pteta_fwd.pdf").c_str());

  pt_eta_mu_FF[2][0]->Draw("colz");
  pt_eta_mu_FF[2][0]->GetXaxis()->SetRangeUser(15,200);
  pt_eta_mu_FF[2][0]->GetYaxis()->SetRangeUser(0.0,0.1);
  pt_eta_mu_FF[2][0]->GetXaxis()->SetTitle("p_{T}");
  pt_eta_mu_FF[2][0]->GetYaxis()->SetTitle("#eta");
  pt_eta_mu_FF[2][0]->GetZaxis()->SetRangeUser(0.0,0.15);
  t1.DrawLatex(0.4,0.94,"calo muon fake factor");
  c2.SaveAs((outdir+"ff_mu_pteta_calo.pdf").c_str());

  pt_eta_el_FF[0][0]->Draw("colz");
  pt_eta_el_FF[0][0]->GetXaxis()->SetRangeUser(7,200);
  pt_eta_el_FF[0][0]->GetYaxis()->SetRangeUser(0,2.47);
  pt_eta_el_FF[0][0]->GetXaxis()->SetTitle("p_{T}");
  pt_eta_el_FF[0][0]->GetYaxis()->SetTitle("#eta");
  pt_eta_el_FF[0][0]->GetZaxis()->SetRangeUser(0.0,0.1);
  t1.DrawLatex(0.4,0.94,"central electron fake factor");
  c2.SaveAs((outdir+"ff_el_pteta.pdf").c_str());


  TCanvas c1("c1","c1");
  TLegend *leg = new TLegend(0.2,0.77,0.8,0.92);
  leg->SetShadowColor(0);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  TLatex t; t.SetNDC(); t.SetTextColor(1);

  //////////////muon eta
  //DATA
  //--------central
  eta_mu_FF[0][0]->GetXaxis()->SetRangeUser(0,2.7);
  eta_mu_FF[0][0]->GetYaxis()->SetRangeUser(0,3);
  eta_mu_FF[0][0]->SetXTitle("#eta");
  eta_mu_FF[0][0]->DrawCopy("e");


  //--------forward
  if (nmutypes>1) {
    // eta_mu_FF[1][0]->SetLineColor(kRed+1);
    // eta_mu_FF[1][0]->SetMarkerColor(kRed+1);
    eta_mu_FF[1][0]->SetMarkerStyle(21);
    eta_mu_FF[1][0]->DrawCopy("esame");
    //--------calo
    if (nmutypes>2) {
      //eta_mu_FF[2][0]->SetLineColor(kRed+1);
      //eta_mu_FF[2][0]->SetMarkerColor(kRed+1);
      eta_mu_FF[2][0]->SetMarkerStyle(22);
      eta_mu_FF[2][0]->DrawCopy("esame");
    }
  }
  //MC
  for (int itype=0;itype<nmutypes;itype++) { //central,forw,calo
    for (int imc=1;imc<=2;imc++) {   //sherpa, powheg
      eta_mu_FF[itype][imc]->SetMarkerSize(0);
      eta_mu_FF[itype][imc]->SetLineColor( ((imc==1)? kBlue : kRed) );
      if (itype==2)
       eta_mu_FF[itype][imc]->SetLineStyle(kDashed);
      // eta_mu_FF[itype][imc]->DrawCopy("histesame");
      eta_mu_FF[itype][imc]->DrawCopy("esame");
    }
  }
  for (int i=0;i<nmutypes;i++) eta_mu_FF[i][0]->DrawCopy("esame"); //redraw data point

  leg->AddEntry(eta_mu_FF[0][0],"data","l");
  leg->AddEntry(eta_mu_FF[0][1],"simulation (Alpgen Z+jets)","l");
  leg->AddEntry(eta_mu_FF[0][2],"simulation (Sherpa Z+jets)","l");
  leg->Draw();
  t.DrawLatex(0.45,0.96,"central and forward muons");
  c1.SaveAs((outdir+"ff_mu_eta.pdf").c_str());

  /////////////muon pt
  //central - DATA
  pt_mu_FF[0][0]->GetYaxis()->SetRangeUser(0,0.5);
  pt_mu_FF[0][0]->SetXTitle("p_{T} [GeV]");
  pt_mu_FF[0][0]->DrawCopy("e");
  //central - MC
  for (int imc=1;imc<=2;imc++) {   //sherpa, powheg
    pt_mu_FF[0][imc]->SetMarkerSize(0);
    pt_mu_FF[0][imc]->SetLineColor( ((imc==1)? kBlue : kRed) );
    // pt_mu_FF[0][imc]->DrawCopy("histesame");
    pt_mu_FF[0][imc]->DrawCopy("esame");
  }
  pt_mu_FF[0][0]->DrawCopy("esame");
  t.DrawLatex(0.45,0.96,"central muons");
  leg->Draw();
  c1.SaveAs((outdir+"ff_mu_pt.pdf").c_str());

  //forward - DATA
  if (nmutypes>1) {
    pt_mu_FF[1][0]->GetYaxis()->SetRangeUser(0,18);
    pt_mu_FF[1][0]->SetXTitle("p_{T} [GeV]");
    pt_mu_FF[1][0]->DrawCopy("e");
    //forward - MC
    for (int imc=1;imc<=2;imc++) {   //sherpa, powheg
      pt_mu_FF[1][imc]->SetMarkerSize(0);
      pt_mu_FF[1][imc]->SetLineColor( ((imc==1)? kBlue : kRed) );
      // pt_mu_FF[1][imc]->DrawCopy("histesame");
      pt_mu_FF[1][imc]->DrawCopy("esame");
    }
    pt_mu_FF[1][0]->DrawCopy("esame");
    t.DrawLatex(0.45,0.96,"forward muons");
    leg->Draw();
    c1.SaveAs((outdir+"ff_forwmu_pt.pdf").c_str());
  }

  //calo - DATA
  if (nmutypes>2) {
    pt_mu_FF[2][0]->GetYaxis()->SetRangeUser(0,1.0);
    pt_mu_FF[2][0]->SetXTitle("p_{T} [GeV]");
    pt_mu_FF[2][0]->DrawCopy("e");
    //calo - MC
    for (int imc=1;imc<=2;imc++) {   //sherpa, powheg
      pt_mu_FF[2][imc]->SetMarkerSize(0);
      pt_mu_FF[2][imc]->SetLineColor( ((imc==1)? kBlue : kRed) );
      pt_mu_FF[2][imc]->DrawCopy("esame");
    }
    pt_mu_FF[2][0]->DrawCopy("esame");
    t.DrawLatex(0.45,0.96,"calo muons");
    leg->Draw();
    c1.SaveAs((outdir+"ff_calomu_pt.pdf").c_str());
  }

  //////////electron eta
  //DATA
  //----central
  eta_el_FF[0][0]->GetYaxis()->SetRangeUser(0,0.3);
  eta_el_FF[0][0]->SetXTitle("#eta");
  eta_el_FF[0][0]->DrawCopy("e");

    //MC
    for (int imc=1;imc<=2;imc++) {   //sherpa, powheg
      eta_el_FF[0][imc]->SetMarkerSize(0);
      eta_el_FF[0][imc]->SetLineColor( ((imc==1)? kBlue : kRed) );
      eta_el_FF[0][imc]->DrawCopy("histesame");
    }
    eta_el_FF[0][0]->DrawCopy("esame");

    leg->Draw();
    t.DrawLatex(0.4,0.96,"central electrons");
    c1.SaveAs((outdir+"ff_el_eta.pdf").c_str());

  /////////////electron pt
  //DATA
  //----central
  pt_el_FF[0][0]->GetYaxis()->SetRangeUser(0,0.12);
  pt_el_FF[0][0]->SetXTitle("p_{T} [GeV]");
  pt_el_FF[0][0]->DrawCopy("e");
  //MC
  for (int imc=1;imc<=2;imc++) {   //sherpa, powheg
    pt_el_FF[0][imc]->SetMarkerSize(0);
    pt_el_FF[0][imc]->SetLineColor(((imc==1)? kBlue : kRed));
    pt_el_FF[0][imc]->DrawCopy("histesame");
  }
  pt_el_FF[0][0]->DrawCopy("esame");
  leg->Draw();
  t.DrawLatex(0.45,0.96,"central electrons");
  c1.SaveAs((outdir+"ff_el_pt.pdf").c_str());

}
