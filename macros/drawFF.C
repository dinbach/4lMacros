#include <TH2F.h>
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <TROOT.h>
#include <TSystem.h>
#include <vector>
#include <map>
#include <TColor.h>
#include "TRint.h"
#include "TStyle.h"
#include "TLatex.h"

using namespace std;
int getLineColor(string channel);
void drawFF();


// string BaseWorkDir = "/Users/kbachas/WORK/4lInclusive/FF_12_11/";
string BaseWorkDir = "/Users/kbachas/WORK/4lInclusive/24_11_2014_FFBackground/";

string inputdir = BaseWorkDir+"OutputFiles/";
string outdir   = BaseWorkDir+"Plots/";

string binScheme = "_down5gev";
// string binScheme     = "_less1";
// string controlSample = "";
string controlSample = "_ttbarcs";

map<string,TFile*> fileMap;

map<string,TH2F*> pt_eta_centralmu_FF;
map<string,TH2F*> pt_eta_forwmu_FF;
map<string,TH2F*> pt_eta_calomu_FF;
map<string,TH2F*> pt_eta_centralel_FF;

map<string,TH1F*> pt_centralmu_FF;
map<string,TH1F*> pt_forwmu_FF;
map<string,TH1F*> pt_calomu_FF;
map<string,TH1F*> pt_centralel_FF;

map<string,TH1F*> eta_centralmu_FF;
map<string,TH1F*> eta_forwmu_FF;
map<string,TH1F*> eta_calomu_FF;
map<string,TH1F*> eta_centralel_FF;


const Int_t NRGBs = 5;
const Int_t NCont = 255;


Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };

void drawFF()
{
  gROOT->ProcessLine(".x doAtlasStyle.C");
  gStyle->SetPaintTextFormat("4.2f");

  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  gStyle->SetOptStat(0);

  fileMap["DATA"]          = new TFile((inputdir+"hists_FF_data"+binScheme+controlSample+".root").c_str());
  // fileMap["ZjetsSherpa"]   = new TFile((inputdir+"hists_FF_ZjetsSherpa"+binScheme+controlSample+".root").c_str());
  // fileMap["ZjetsAlpgenHF"] = new TFile((inputdir+"hists_FF_ZjetsAlpgen_HF"+binScheme+controlSample+".root").c_str());
  // fileMap["ZjetsAlpgenLF"] = new TFile((inputdir+"hists_FF_ZjetsAlpgen_LF"+binScheme+controlSample+".root").c_str());
  // fileMap["Zjets"]       = TFile::Open((inputdir+"hists_FF_Zjets_HFLF"+binScheme+controlSample+".root").c_str()) ;
  // fileMap["ttbar"]       = new TFile((inputdir+"hists_FF_ttbar"+binScheme+controlSample+".root").c_str(),"READ");
  // fileMap["TEST"]        = TFile::Open( (inputdir+"hists_FF_TEST"+binScheme+controlSample+".root").c_str());

  cout << std::setprecision(2);
  cout << std::fixed;

  map<string,TFile*>::iterator ifile = fileMap.begin();
  for ( ; ifile!=fileMap.end(); ++ifile)
  {
    string channel = ifile->first;
    TFile *ftmp    = ifile->second;

    cout << "Getting channel " << channel << "  from file " << ftmp->GetName() << endl;
    pt_eta_centralmu_FF[channel] = (TH2F*) ftmp->Get("pt_eta_centralmu_FF")->Clone(("pt_eta_centralmu_FF"+channel).c_str());
    pt_eta_forwmu_FF[channel]    = (TH2F*) ftmp->Get("pt_eta_forwmu_FF")->Clone(("pt_eta_forwmu_FF"+channel).c_str());
    pt_eta_calomu_FF[channel]    = (TH2F*) ftmp->Get("pt_eta_calomu_FF")->Clone(("pt_eta_calomu_FF"+channel).c_str());
    pt_eta_centralel_FF[channel] = (TH2F*) ftmp->Get("pt_eta_centralel_FF")->Clone(("pt_eta_centralel_FF_"+channel).c_str());

    pt_centralmu_FF[channel] = (TH1F*) (ftmp->Get("pt_centralmu_FF"))->Clone(("pt_centralmu_FF"+channel).c_str());
    pt_forwmu_FF[channel]    = (TH1F*) (ftmp->Get("pt_forwmu_FF"))   ->Clone(("pt_forwmu_FF"+channel).c_str());
    pt_calomu_FF[channel]    = (TH1F*) (ftmp->Get("pt_calomu_FF"))   ->Clone(("pt_calomu_FF"+channel).c_str());
    pt_centralel_FF[channel] = (TH1F*) (ftmp->Get("pt_centralel_FF"))->Clone(("pt_centralel_FF"+channel).c_str());

    eta_centralmu_FF[channel] = (TH1F*) (ftmp->Get("eta_centralmu_FF"))->Clone(("eta_centralmu_FF"+channel).c_str());
    eta_forwmu_FF[channel]    = (TH1F*) (ftmp->Get("eta_forwmu_FF"))   ->Clone(("eta_forwmu_FF"+channel).c_str());
    eta_calomu_FF[channel]    = (TH1F*) (ftmp->Get("eta_calomu_FF"))   ->Clone(("eta_calomu_FF"+channel).c_str());
    eta_centralel_FF[channel] = (TH1F*) (ftmp->Get("eta_centralel_FF"))->Clone(("eta_centralel_FF"+channel).c_str());
  }


  TCanvas c1("c1","c1");
  TLatex t1; t1.SetNDC();
  t1.SetTextColor(1);
  t1.SetTextSize(0.04);

  map<string,TH2F*>::iterator iplot = pt_eta_centralmu_FF.begin();
  for ( ; iplot!=pt_eta_centralmu_FF.end();iplot++)
  {
    string channel = iplot->first;
    cout << "Plotting channel : " << channel << endl;
    pt_eta_centralmu_FF[channel]->SetMarkerSize(0.9);
    pt_eta_centralmu_FF[channel]->Draw("colztexte");
    pt_eta_centralmu_FF[channel]->GetXaxis()->SetRangeUser(6,200);
    pt_eta_centralmu_FF[channel]->GetYaxis()->SetRangeUser(0,2.5);
    pt_eta_centralmu_FF[channel]->GetXaxis()->SetTitle("p_{T}");
    pt_eta_centralmu_FF[channel]->GetYaxis()->SetTitle("#eta");
    pt_eta_centralmu_FF[channel]->GetZaxis()->SetRangeUser(0.0,0.5);
    pt_eta_centralmu_FF[channel]->GetZaxis()->SetLabelSize(0.03);
    t1.DrawLatex(0.4,0.96,"central muon fake factor");
    c1.SaveAs((outdir+"ff_mu_pteta_central"+binScheme+controlSample+"_"+channel+".pdf").c_str());
    c1.Clear();

    // pt_eta_forwmu_FF[channel]->SetMarkerSize(0.8);
    // pt_eta_forwmu_FF[channel]->Draw("colztexte");
    // pt_eta_forwmu_FF[channel]->GetXaxis()->SetRangeUser(6,200);
    // pt_eta_forwmu_FF[channel]->GetYaxis()->SetRangeUser(2.5,2.7);
    // pt_eta_forwmu_FF[channel]->GetXaxis()->SetTitle("p_{T}");
    // pt_eta_forwmu_FF[channel]->GetYaxis()->SetTitle("#eta");
    // pt_eta_forwmu_FF[channel]->GetZaxis()->SetRangeUser(0.0,3.0);
    // t1.DrawLatex(0.4,0.94,"fwd muon fake factor");
    // c1.SaveAs((outdir+"ff_mu_pteta_fwd"+binScheme+controlSample+"_"+channel+".pdf").c_str());
    // c1.Clear();

    // pt_eta_calomu_FF[channel]->SetMarkerSize(0.8);
    // pt_eta_calomu_FF[channel]->Draw("colztexte");
    // pt_eta_calomu_FF[channel]->GetXaxis()->SetRangeUser(15,200);
    // pt_eta_calomu_FF[channel]->GetYaxis()->SetRangeUser(0.0,0.1);
    // pt_eta_calomu_FF[channel]->GetXaxis()->SetTitle("p_{T}");
    // pt_eta_calomu_FF[channel]->GetYaxis()->SetTitle("#eta");
    // pt_eta_calomu_FF[channel]->GetZaxis()->SetRangeUser(0.0,0.15);
    // t1.DrawLatex(0.4,0.94,"calo muon fake factor");
    // c1.SaveAs((outdir+"ff_mu_pteta_calo"+binScheme+controlSample+"_"+channel+".pdf").c_str());
    // c1.Clear();

    pt_eta_centralel_FF[channel]->SetMarkerSize(0.9);
    pt_eta_centralel_FF[channel]->Draw("colztexte");
    pt_eta_centralel_FF[channel]->GetXaxis()->SetRangeUser(7,200);
    pt_eta_centralel_FF[channel]->GetYaxis()->SetRangeUser(0,2.47);
    pt_eta_centralel_FF[channel]->GetXaxis()->SetTitle("p_{T}");
    pt_eta_centralel_FF[channel]->GetYaxis()->SetTitle("#eta");
    Double_t zup =0.2;
    if (channel=="ZjetsAlpgenHF") zup = 0.7;
    // if (controlSample=="_ttbarcs") zup = 0.27;
    pt_eta_centralel_FF[channel]->GetZaxis()->SetRangeUser(0.0,zup);
    pt_eta_centralel_FF[channel]->GetZaxis()->SetLabelSize(0.03);
    t1.DrawLatex(0.4,0.96,"central electron fake factor");
    c1.SaveAs((outdir+"ff_el_pteta"+binScheme+controlSample+"_"+channel+".pdf").c_str());
    c1.Clear();
  }

  //-------------------------------------------------------------------------------------------------
  TCanvas c2("c2","c2");
  TLegend *leg = new TLegend(0.2,0.77,0.8,0.92);
  leg->SetShadowColor(0);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  TLatex t; t.SetNDC(); t.SetTextColor(1);
  t.SetTextSize(0.04);


  ///***********************  eta central muon  ***************************///
  cout << "- Plotting Muon Eta FF" << endl;
  bool isFirst = true;
  map<string,TH1F*>::iterator iplot_eta = eta_centralmu_FF.begin();
  for ( ; iplot_eta!=eta_centralmu_FF.end();iplot_eta++)
  {
    string channel = iplot_eta->first;
    cout << " Muon Eta FF for channel " << channel << endl;
    if (isFirst)
    {
      eta_centralmu_FF[channel]->GetXaxis()->SetRangeUser(0,2.7);
      eta_centralmu_FF[channel]->GetYaxis()->SetRangeUser(0,2);
      eta_centralmu_FF[channel]->SetXTitle("#eta");
      eta_centralmu_FF[channel]->DrawCopy("e");

      isFirst=false;
    }
    else
    {
      if (channel !="DATA"){
        eta_centralmu_FF[channel]->SetMarkerSize(0);
        eta_centralmu_FF[channel]->SetLineColor(getLineColor(channel));

      }
      eta_centralmu_FF[channel]->SetMarkerStyle(21);
      eta_centralmu_FF[channel]->DrawCopy("esame");
    }

    leg->AddEntry(eta_centralmu_FF[channel],channel.c_str(),"l");

  }

  leg->Draw();
  t.DrawLatex(0.45,0.96,"central muons");
  c2.SaveAs((outdir+"ff_mu_eta"+binScheme+controlSample+".pdf").c_str());


  c2.Clear();
  leg->Clear();
  ///***********************  pt muon  ***************************///
  isFirst = true;
  map<string,TH1F*>::iterator iplot_pt = pt_centralmu_FF.begin();
  for ( ; iplot_pt!=pt_centralmu_FF.end();iplot_pt++)
  {
    string channel = iplot_pt->first;
    if (isFirst)
    {
      pt_centralmu_FF[channel]->GetYaxis()->SetRangeUser(0,1);
      pt_centralmu_FF[channel]->SetXTitle("p_{T} [GeV]");
      pt_centralmu_FF[channel]->DrawCopy("e");
      isFirst=false;
    }
    else
    {
      if (channel !="DATA"){
        pt_centralmu_FF[channel]->SetMarkerSize(0);
        pt_centralmu_FF[channel]->SetLineColor(getLineColor(channel));
      }
      pt_centralmu_FF[channel]->SetMarkerStyle(21);
      pt_centralmu_FF[channel]->DrawCopy("esame");
    }

    leg->AddEntry(pt_centralmu_FF[channel],channel.c_str(),"l");

  }

  leg->Draw();
  t.DrawLatex(0.45,0.96,"central muons");
  c2.SaveAs((outdir+"ff_mu_pt"+binScheme+controlSample+".pdf").c_str());

  ///***********************  pt Fwd muon  ***************************///
  c2.Clear();
  leg->Clear();
  isFirst = true;
  iplot_pt = pt_forwmu_FF.begin();
  for ( ; iplot_pt!=pt_forwmu_FF.end();iplot_pt++)
  {
    string channel = iplot_pt->first;
    if (isFirst)
    {
      double yup = 4;
      if (controlSample=="_ttbarcs") yup = 2;
      pt_forwmu_FF[channel]->GetYaxis()->SetRangeUser(0,yup);
      pt_forwmu_FF[channel]->SetXTitle("p_{T} [GeV]");
      pt_forwmu_FF[channel]->DrawCopy("e");
      isFirst=false;
    }
    else
    {
      if (channel !="DATA"){
        pt_forwmu_FF[channel]->SetMarkerSize(0);
        pt_forwmu_FF[channel]->SetLineColor(getLineColor(channel));
      }
      pt_forwmu_FF[channel]->SetMarkerStyle(21);
      pt_forwmu_FF[channel]->DrawCopy("esame");
    }

    leg->AddEntry(pt_forwmu_FF[channel],channel.c_str(),"l");

  }

  leg->Draw();
  t.DrawLatex(0.45,0.96,"fowrward muons");
  c2.SaveAs((outdir+"ff_forwmu_pt"+binScheme+controlSample+".pdf").c_str());

  ///***********************  pt Calo muon  ***************************///
  c2.Clear();
  leg->Clear();
  isFirst = true;
  iplot_pt = pt_calomu_FF.begin();
  for ( ; iplot_pt!=pt_calomu_FF.end();iplot_pt++)
  {
    string channel = iplot_pt->first;
    if (isFirst)
    {
      double yup = 0.4;
      if (controlSample=="_ttbarcs") yup = 1.4;
      pt_calomu_FF[channel]->GetYaxis()->SetRangeUser(0,yup);
      pt_calomu_FF[channel]->SetXTitle("p_{T} [GeV]");
      pt_calomu_FF[channel]->DrawCopy("e");
      isFirst=false;
    }
    else
    {
      if (channel !="DATA"){
        pt_calomu_FF[channel]->SetMarkerSize(0);
        pt_calomu_FF[channel]->SetLineColor(getLineColor(channel));
      }
      pt_calomu_FF[channel]->SetMarkerStyle(21);
      pt_calomu_FF[channel]->DrawCopy("esame");
    }

    leg->AddEntry(pt_calomu_FF[channel],channel.c_str(),"l");

  }

  leg->Draw();
  t.DrawLatex(0.45,0.96,"calo muons");
  c2.SaveAs((outdir+"ff_calomu_pt"+binScheme+controlSample+".pdf").c_str());


  c2.Clear();
  leg->Clear();
  ///***********************  eta electron  ***************************///
  isFirst = true;
  iplot_eta = eta_centralel_FF.begin();
  for ( ; iplot_eta!=eta_centralel_FF.end();iplot_eta++)
  {
    string channel = iplot_eta->first;
    if (isFirst)
    {
      eta_centralel_FF[channel]->GetXaxis()->SetRangeUser(0,2.47);
      eta_centralel_FF[channel]->GetYaxis()->SetRangeUser(0,0.25);
      eta_centralel_FF[channel]->SetXTitle("#eta");
      eta_centralel_FF[channel]->DrawCopy("e");
      isFirst=false;
    }
    else
    {
      if (channel !="DATA"){
        eta_centralel_FF[channel]->SetMarkerSize(0);
        eta_centralel_FF[channel]->SetLineColor(getLineColor(channel));
      }
      eta_centralel_FF[channel]->SetMarkerStyle(21);
      eta_centralel_FF[channel]->DrawCopy("esame");
    }

    leg->AddEntry(eta_centralel_FF[channel],channel.c_str(),"l");

  }

  eta_centralel_FF["DATA"]->DrawCopy("esame"); //redraw data point

  leg->Draw();
  t.DrawLatex(0.45,0.96,"central electrons");
  c2.SaveAs((outdir+"ff_el_eta"+binScheme+controlSample+".pdf").c_str());


  c2.Clear();
  leg->Clear();
  ///***********************  pt electron  ***************************///
  isFirst = true;
  iplot_pt = pt_centralel_FF.begin();
  for ( ; iplot_pt!=pt_centralel_FF.end();iplot_pt++)
  {
    string channel = iplot_pt->first;
    if (isFirst)
    {
      double yup = 0.8;
      if (controlSample=="_ttbarcs") yup = 0.6;
      pt_centralel_FF[channel]->GetYaxis()->SetRangeUser(0,yup);
      pt_centralel_FF[channel]->SetXTitle("p_{T} [GeV]");
      pt_centralel_FF[channel]->DrawCopy("e");
      isFirst=false;
    }
    else
    {
      if (channel !="DATA"){
        pt_centralel_FF[channel]->SetMarkerSize(0);
        pt_centralel_FF[channel]->SetLineColor(getLineColor(channel));
      }
      pt_centralel_FF[channel]->SetMarkerStyle(21);
      pt_centralel_FF[channel]->DrawCopy("esame");
    }

    leg->AddEntry(pt_centralel_FF[channel],channel.c_str(),"l");

  }

  // pt_centralel_FF["DATA"]->DrawCopy("esame"); //redraw data point

  leg->Draw();
  t.DrawLatex(0.45,0.96,"central electrons");
  c2.SaveAs((outdir+"ff_el_pt"+binScheme+controlSample+".pdf").c_str());

 }

int getLineColor(string channel)
{
  if (channel=="DATA") return kBlack;
  else if (channel=="ZjetsSherpa") return kRed;
  else if (channel=="Zjets") return 4;
  else if (channel=="ZjetsAlpgenHF") return kBlue;
  else if (channel=="ZjetsAlpgenLF") return kGreen;
  else if (channel=="TEST") return 3;

  return 4;
}
