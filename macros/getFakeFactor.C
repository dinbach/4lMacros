#include <TH2F.h>
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <iostream>
#include <iomanip>
using namespace std;
#include <string>
#include <sstream>
#include <TROOT.h>
#include <TSystem.h>

void doLJDivision(string inputfname,string outputfname,string mcfname="");
void getFakeFactor();
TH1F* divideHists(TH1F *h1, TH1F *h2,string title);
TH2F* divideHists(TH2F *h1, TH2F *h2,string title);


string elrecotype = "central";
string murecotype[3] = {"central","forw","calo"};

// string BaseWorkDir = "/Users/kbachas/WORK/4lInclusive/FF_12_11/";
string BaseWorkDir = "/Users/kbachas/WORK/4lInclusive/24_11_2014_FFBackground/";
string inputdir    = BaseWorkDir+"InputFiles/";
string outputdir   = BaseWorkDir+"OutputFiles/";
string outputPlotsdir = BaseWorkDir+"Plots/";

string binScheme     = "_down5gev";
// _plus1bin
// _down5gev
// _up5gev
// _newbinning
// _Mz20_Zjcs
// _Mz10_Zjcs
// _pt20_Zjcs
// _pt25_Zjcs
// _pt25_ttbarcs
// _pt15_ttbarcs
// _MET60_ttbarcs
// _MET40_ttbarcs
// string controlSample = "";
string controlSample = "_ttbarcs";


void getFakeFactor()
{
  //add ZZ and WZ MC -- needed to subtract from data
  // gSystem->Exec(("hadd -f "+inputdir+"AnalysisManager.MC.FFHisto.Dibosons.root "+inputdir+"AnalysisManager.MC.FFHisto.WZ.root "+inputdir+"AnalysisManager.MC.FFHisto.ZZ.root "+inputdir+"AnalysisManager.MC.FFHisto.ggH125p5_gg_ZZ.root").c_str());
  // gSystem->Exec(("hadd -f "+inputdir+"AnalysisManager.MC.FFHisto.ZjetsAlpgen_HFLF.root "+inputdir+"AnalysisManager.MC.FFHisto.Zjets.root "+inputdir+"AnalysisManager.MC.FFHisto.Zbb.root ").c_str());

  //data, subtracting contribution from dibosons with mc
  // doLJDivision(inputdir+"AnalysisManager.DATA.FFHisto.root",outputdir+"hists_FF_data",inputdir+"AnalysisManager.MC.FFHisto.Dibosons.root");
  doLJDivision(inputdir+"AnalysisManager.DATA.FFHisto.root",outputdir+"hists_FF_data");

  //mc for Z+jets, sherpa
  // doLJDivision(inputdir+"AnalysisManager.MC.FFHisto.ZjetsSherpa.root",outputdir+"hists_FF_ZjetsSherpa");

  // doLJDivision(inputdir+"AnalysisManager.MC.FFHisto.Zjets.root",outputdir+"hists_FF_ZjetsAlpgen_LF");

  // doLJDivision(inputdir+"AnalysisManager.MC.FFHisto.Zbb.root",outputdir+"hists_FF_ZjetsAlpgen_HF");

  // doLJDivision(inputdir+"AnalysisManager.MC.FFHisto.ttbar.root",outputdir+"hists_FF_ttbar");

  // doLJDivision(inputdir+"AnalysisManager.MC.FFHisto.ZjetsAlpgen_HFLF.root",outputdir+"hists_FF_Zjets_HFLF");
  // doLJDivision(inputdir+"AnalysisManager.MC.FFHisto.TEST.root",outputdir+"hists_FF_TEST");

}


void doLJDivision(string inputfname,string outputfname,string mcfname)
{
  cout << std::setprecision(3);
  cout << std::fixed;

  cout << "-*************************************************************************************************************-" << endl;
  cout << "- Doing FF of : " << inputfname << endl;
  cout << "binScheme     : " << binScheme << endl;
  cout << "controlCS     : " << controlSample << endl;
  cout << "-*************************************************************************************************************-" << endl;


  TH2F *pt_eta_mu_l[3];
  TH2F *pt_eta_mu_j[3];
  TH1F *pt_mu_l[3];
  TH1F *pt_mu_j[3];
  TH1F *eta_mu_l[3];
  TH1F *eta_mu_j[3];

  TH2F *pt_eta_el_l;
  TH2F *pt_eta_el_j;
  TH1F *pt_el_l;
  TH1F *pt_el_j;
  TH1F *eta_el_l;
  TH1F *eta_el_j;

  /////////////// retrieve histograms from data
  TFile *f = new TFile(inputfname.c_str(),"READ");
  // TH1::AddDirectory(kFALSE);

  for (int i=0;i<3;i++) {

    string mutype = murecotype[i];
    pt_eta_mu_l[i] = (TH2F*) (f->Get(("MyTool"+binScheme+"/mu_L"+controlSample+"/pt_eta_"+mutype+"_mu_L"+controlSample).c_str() ) )->Clone(("pt_eta_mu_l"+mutype).c_str());
    pt_eta_mu_j[i] = (TH2F*) (f->Get(("MyTool"+binScheme+"/mu_J"+controlSample+"/pt_eta_"+mutype+"_mu_J"+controlSample).c_str() ) )->Clone(("pt_eta_mu_j"+mutype).c_str());
    pt_mu_l[i]     = (TH1F*) (f->Get(("MyTool"+binScheme+"/mu_L"+controlSample+"/pt_"+mutype+"_mu_L"+controlSample).c_str() ) )->Clone(("pt_mu_l"+mutype).c_str());
    pt_mu_j[i]     = (TH1F*) (f->Get(("MyTool"+binScheme+"/mu_J"+controlSample+"/pt_"+mutype+"_mu_J"+controlSample).c_str() ) )->Clone(("pt_mu_j"+mutype).c_str());
    eta_mu_l[i]    = (TH1F*) (f->Get(("MyTool"+binScheme+"/mu_L"+controlSample+"/eta_"+mutype+"_mu_L"+controlSample).c_str() ) )->Clone(("eta_mu_l"+mutype).c_str());
    eta_mu_j[i]    = (TH1F*) (f->Get(("MyTool"+binScheme+"/mu_J"+controlSample+"/eta_"+mutype+"_mu_J"+controlSample).c_str() ) )->Clone(("eta_mu_j"+mutype).c_str());
  }

  pt_eta_el_l       = (TH2F*) (f->Get(("MyTool"+binScheme+"/e_L"+controlSample+"/pt_eta_"+elrecotype+"_e_L"+controlSample).c_str() ) )->Clone();
  pt_eta_el_j       = (TH2F*) (f->Get(("MyTool"+binScheme+"/e_J"+controlSample+"/pt_eta_"+elrecotype+"_e_J"+controlSample).c_str() ) )->Clone();
  pt_el_l           = (TH1F*) (f->Get(("MyTool"+binScheme+"/e_L"+controlSample+"/pt_"+elrecotype+"_e_L"+controlSample).c_str() ) )->Clone();
  pt_el_j           = (TH1F*) (f->Get(("MyTool"+binScheme+"/e_J"+controlSample+"/pt_"+elrecotype+"_e_J"+controlSample).c_str() ) )->Clone();
  eta_el_l          = (TH1F*) (f->Get(("MyTool"+binScheme+"/e_L"+controlSample+"/eta_"+elrecotype+"_e_L"+controlSample).c_str() ) )->Clone();
  eta_el_j          = (TH1F*) (f->Get(("MyTool"+binScheme+"/e_J"+controlSample+"/eta_"+elrecotype+"_e_J"+controlSample).c_str() ) )->Clone();

  // f->Close();

  if (mcfname!="") {
    cout << "- Subtracting "<< mcfname << " from " << inputfname << endl;
      TFile *f2 = new TFile(mcfname.c_str(),"READ");
    // TH1::AddDirectory(kFALSE);

    for (int i=0;i<3;i++) {
      string mutype = murecotype[i];

      pt_eta_mu_l[i]->Add((TH2F*)f2->Get(("MyTool"+binScheme+"/mu_L"+controlSample+"/pt_eta_"+mutype+"_mu_L"+controlSample).c_str()),-1);
      pt_eta_mu_j[i]->Add((TH2F*)f2->Get(("MyTool"+binScheme+"/mu_J"+controlSample+"/pt_eta_"+mutype+"_mu_J"+controlSample).c_str()),-1);
      pt_mu_l[i]    ->Add((TH1F*)f2->Get(("MyTool"+binScheme+"/mu_L"+controlSample+"/pt_"+mutype+"_mu_L"+controlSample).c_str()),-1);
      pt_mu_j[i]    ->Add((TH1F*)f2->Get(("MyTool"+binScheme+"/mu_J"+controlSample+"/pt_"+mutype+"_mu_J"+controlSample).c_str()),-1);
      eta_mu_l[i]   ->Add((TH1F*)f2->Get(("MyTool"+binScheme+"/mu_L"+controlSample+"/eta_"+mutype+"_mu_L"+controlSample).c_str()),-1);
      eta_mu_j[i]   ->Add((TH1F*)f2->Get(("MyTool"+binScheme+"/mu_J"+controlSample+"/eta_"+mutype+"_mu_J"+controlSample).c_str()),-1);
    }

     pt_eta_el_l->Add((TH2F*)f2->Get(("MyTool"+binScheme+"/e_L"+controlSample+"/pt_eta_"+elrecotype+"_e_L"+controlSample).c_str()),-1);
     pt_eta_el_j->Add((TH2F*)f2->Get(("MyTool"+binScheme+"/e_J"+controlSample+"/pt_eta_"+elrecotype+"_e_J"+controlSample).c_str()),-1);
     pt_el_l    ->Add((TH1F*)f2->Get(("MyTool"+binScheme+"/e_L"+controlSample+"/pt_"+elrecotype+"_e_L"+controlSample).c_str()),-1);
     pt_el_j    ->Add((TH1F*)f2->Get(("MyTool"+binScheme+"/e_J"+controlSample+"/pt_"+elrecotype+"_e_J"+controlSample).c_str()),-1);
     eta_el_l   ->Add((TH1F*)f2->Get(("MyTool"+binScheme+"/e_L"+controlSample+"/eta_"+elrecotype+"_e_L"+controlSample).c_str()),-1);
     eta_el_j   ->Add((TH1F*)f2->Get(("MyTool"+binScheme+"/e_J"+controlSample+"/eta_"+elrecotype+"_e_J"+controlSample).c_str()),-1);

    // f2->Close();
     delete f2;
     f2=0;
  }

  cout << "- Opening file " << outputfname+binScheme+controlSample+".root" << " to store histograms" << endl;
  TFile* fout = new TFile((outputfname+binScheme+controlSample+".root").c_str(),"RECREATE");
  // TH1::AddDirectory(kTRUE);

  TH2F *pt_eta_mu_FF[3];
  TH2F *pt_eta_el_FF;

  TH1F *pt_mu_FF[3];
  TH1F *pt_el_FF;

  TH1F *eta_mu_FF[3];
  TH1F *eta_el_FF;

  //+original - used for presentation of 29-9-2014
  // central el  = 7,15,25,40,200
  // central mu  = 6,15,25,40,200
  // fwd mu      = 6,15,25,200
  // calo mu     = 15,25,40,60,200
  //-

  for (int i=0;i<3;i++) {
   // Bin [6,15] : 1.29006 +/- 0.0673906
   // Bin [15,25] : 0.945139 +/- 0.161233
   // Bin [25,200] : 1.25679 +/- 0.340029

    pt_eta_mu_FF[i] = divideHists(pt_eta_mu_l[i],pt_eta_mu_j[i],Form("pt_eta_%smu_FF",murecotype[i].c_str()));
    pt_mu_FF[i]     = divideHists(pt_mu_l[i],pt_mu_j[i],Form("pt_%smu_FF",murecotype[i].c_str()));
    eta_mu_FF[i]    = divideHists(eta_mu_l[i],eta_mu_j[i],Form("eta_%smu_FF",murecotype[i].c_str()));
  }

    pt_eta_el_FF = divideHists(pt_eta_el_l,pt_eta_el_j,Form("pt_eta_%sel_FF",elrecotype.c_str()));
    pt_el_FF     = divideHists(pt_el_l,pt_el_j,Form("pt_%sel_FF",elrecotype.c_str()));
    eta_el_FF    = divideHists(eta_el_l,eta_el_j,Form("eta_%sel_FF",elrecotype.c_str()));

  fout->Write();
  fout->Close();

  delete fout;
  fout=0;
  delete f;
  f=0;

}


TH1F* divideHists(TH1F *h1, TH1F *h2,string title)
{
  TH1F *h = (TH1F*) h1->Clone(title.c_str());
  cout << "\n - Computing FF of histograms: " << h1->GetName() << " / " << h2->GetName() <<endl;

  for (int i=1;i<=h2->GetNbinsX();i++) {
    double f=0,fErr=0;
    double l = h1->GetBinContent(i);
    double j = h2->GetBinContent(i);
    double lErr = h1->GetBinError(i);
    double jErr = h2->GetBinError(i);

    if (j>0) {
      f=l/j;
      if (l>0) fErr = f*sqrt( pow(lErr/l,2)+pow(jErr/j,2) );
    }
    if (f<0) f=0;

    cout <<  " Bin "<< " ["<< h2->GetBinLowEdge(i)<< ","<< h2->GetBinLowEdge(i) + h2->GetBinWidth(i) <<"]";
    cout << setw(5)<< right<<"=";
    cout <<setw(10) << f  << " +/- "<< fErr << endl;
    // cout << setw(10) << l << " "<<setw(10) << j << setw(10) <<" = " <<setw(10) << f  << " +/- "<< fErr << endl;
    h->SetBinContent(i,f);
    h->SetBinError(i,fErr);
  }
  return h;
}

TH2F* divideHists(TH2F *h1, TH2F *h2,string title)
{
  TH2F *h = (TH2F*) h1->Clone(title.c_str());
  cout << "\n - Computing FF of histograms: " << h1->GetName() << " / " << h2->GetName() <<endl;
  for (int i=1;i<=h2->GetNbinsX();i++) {
    for (int j=1;j<=h2->GetNbinsY();j++) {
      double f=0,fErr=0;

      double L = h1->GetBinContent(i,j);
      double J = h2->GetBinContent(i,j);
      double LErr = h1->GetBinError(i,j);
      double JErr = h2->GetBinError(i,j);

      if (J>0)
      {
        f=L/J;
        if (L>0) fErr = f*sqrt( pow(LErr/L,2)+pow(JErr/J,2) );
      }

      if (f<0)f=0.0000000001;
      if (f==0) f=0.00000000001;
      cout << " Bin ["<<i<<","<<j<<"]    = " << setw(10) << L << " "<< setw(10) << J <<setw(10) << " = " <<setw(10) << f << " +/- "<< fErr << endl;

     h->SetBinContent(i,j,f);
     h->SetBinError(i,j,fErr);
   }
 }
  return h;
}
//