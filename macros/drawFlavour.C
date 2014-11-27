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
#include <vector>
#include <map>
#include <TColor.h>
#include "TRint.h"
#include "TStyle.h"
#include "TLatex.h"
#include "THStack.h"


void drawFlavour();

string elrecotype = "central";
string murecotype[3] = {"central","forw","calo"};

// string BaseWorkDir = "/Users/kbachas/WORK/4lInclusive/FF_12_11/";
string BaseWorkDir = "/Users/kbachas/WORK/4lInclusive/24_11_2014_FFBackground/";

string inputdir    = BaseWorkDir+"InputFiles/";
string outputdir   = BaseWorkDir+"OutputFiles/";
string outputPlotsdir = BaseWorkDir+"Plots/";

string binScheme     = "";
// MyTool_plus1bin
// MyTool_down5gev
// MyTool_up5gev
// MyTool_newbinning
string controlSample = "";
// string controlSample = "_ttbarcs";
int getColor(string channel);

void drawFlavour()
{
  cout << std::setprecision(3);
  cout << std::fixed;

  cout << "-*************************************************************************************************************-" << endl;

  map<string,TH1F*> type_mu_l;
  map<string,TH1F*> type_mu_j;
  map<string,TH1F*> type_forwmu_l;
  map<string,TH1F*> type_forwmu_j;
  map<string,TH1F*> type_el_l;
  map<string,TH1F*> type_el_j;

  map<string,TFile*> fileMap;
  // fileMap["DATA"]       = new TFile((inputdir+"AnalysisManager.DATA.FFHisto.root").c_str());
  // fileMap["WZ"]         = new TFile((inputdir+"AnalysisManager.MC.FFHisto.WZ.root").c_str());
  // fileMap["qqZZ"]       = new TFile((inputdir+"AnalysisManager.MC.FFHisto.ZZ.root").c_str());
  // fileMap["ggZZ"]       = new TFile((inputdir+"AnalysisManager.MC.FFHisto.ggH125p5_gg_ZZ.root").c_str());

  fileMap["DPI"]        = new TFile((inputdir+"AnalysisManager.MC.FFHisto.DPI.root").c_str());
  fileMap["VVV"]        = new TFile((inputdir+"AnalysisManager.MC.FFHisto.Triboson.root").c_str());
  fileMap["Alpgen_Zbb"]        = new TFile((inputdir+"AnalysisManager.MC.FFHisto.Zbb.root").c_str());
  fileMap["Zg"]         = new TFile((inputdir+"AnalysisManager.MC.FFHisto.Zgamma.root").c_str());
  fileMap["Alpgen_ZjetsLF"]    = new TFile((inputdir+"AnalysisManager.MC.FFHisto.Zjets.root").c_str());
  // fileMap["ZjetsSherpa"]= new TFile((inputdir+"AnalysisManager.MC.FFHisto.ZjetsSherpa.root").c_str());
  fileMap["tZ"]         = new TFile((inputdir+"AnalysisManager.MC.FFHisto.tZ.root").c_str());
  fileMap["ttbar"]      = new TFile((inputdir+"AnalysisManager.MC.FFHisto.ttbar.root").c_str());
  fileMap["ttbarW"]     = new TFile((inputdir+"AnalysisManager.MC.FFHisto.ttbarWj.root").c_str());
  fileMap["ttbarZ"]     = new TFile((inputdir+"AnalysisManager.MC.FFHisto.ttbarZj.root").c_str());

  map<string,TFile*>::iterator ifile = fileMap.begin();
  THStack hs_muL("hs_muL","");
  THStack hs_muJ("hs_muL","");
  THStack hs_forwmuL("hs_forwmuL","");
  THStack hs_forwmuJ("hs_forwmuL","");
  THStack hs_eL("hs_eL","");
  THStack hs_eJ("hs_eL","");

  TLegend *leg = new TLegend(0.85,0.9,0.7,0.7);
    leg->SetShadowColor(0);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetLineWidth(0);
    TCanvas c1("c1","c1");
    TLatex t; t.SetNDC(); t.SetTextColor(1);
    t.SetTextSize(0.04);

  for ( ; ifile!=fileMap.end(); ++ifile)
  {
    string channel = ifile->first;
    TFile *ftmp    = ifile->second;

    cout << "Getting channel " << channel << "  from file " << ftmp->GetName() << endl;

    type_mu_l[channel] = (TH1F*) ftmp->Get(("MyTool"+binScheme+"/mu_L"+controlSample+"/type_central_mu_L"+controlSample).c_str());
    type_mu_j[channel] = (TH1F*) ftmp->Get(("MyTool"+binScheme+"/mu_J"+controlSample+"/type_central_mu_J"+controlSample).c_str());

    type_forwmu_l[channel] = (TH1F*) ftmp->Get(("MyTool"+binScheme+"/mu_L"+controlSample+"/type_forw_mu_L"+controlSample).c_str());
    type_forwmu_j[channel] = (TH1F*) ftmp->Get(("MyTool"+binScheme+"/mu_J"+controlSample+"/type_forw_mu_J"+controlSample).c_str());

    type_el_l[channel] = (TH1F*) ftmp->Get(("MyTool"+binScheme+"/e_L"+controlSample+"/type_central_e_L"+controlSample).c_str());
    type_el_j[channel] = (TH1F*) ftmp->Get(("MyTool"+binScheme+"/e_J"+controlSample+"/type_central_e_J"+controlSample).c_str());

// Undefined=0,Signal=2,Fromb=3,Conversion=4,Hadron=5

    type_mu_l[channel]->SetFillColor(getColor(channel));
    type_mu_l[channel]->GetXaxis()->SetBinLabel(1,"Unknown");
    type_mu_l[channel]->GetXaxis()->SetBinLabel(3,"Signal");
    type_mu_l[channel]->GetXaxis()->SetBinLabel(4,"HeavyF");
    type_mu_l[channel]->GetXaxis()->SetBinLabel(5,"Conversion");
    type_mu_l[channel]->GetXaxis()->SetBinLabel(6,"LightF");
    leg->AddEntry(type_mu_l[channel],channel.c_str(),"F");
    hs_muL.Add(type_mu_l[channel]);

    type_mu_j[channel]->SetFillColor(getColor(channel));
    type_mu_j[channel]->GetXaxis()->SetBinLabel(1,"Unknown");
    type_mu_j[channel]->GetXaxis()->SetBinLabel(3,"Signal");
    type_mu_j[channel]->GetXaxis()->SetBinLabel(4,"HeavyF");
    type_mu_j[channel]->GetXaxis()->SetBinLabel(5,"Conversion");
    type_mu_j[channel]->GetXaxis()->SetBinLabel(6,"LightF");
    hs_muJ.Add(type_mu_j[channel]);

    type_forwmu_l[channel]->SetFillColor(getColor(channel));
    type_forwmu_l[channel]->GetXaxis()->SetBinLabel(1,"Unknown");
    type_forwmu_l[channel]->GetXaxis()->SetBinLabel(3,"Signal");
    type_forwmu_l[channel]->GetXaxis()->SetBinLabel(4,"HeavyF");
    type_forwmu_l[channel]->GetXaxis()->SetBinLabel(5,"Conversion");
    type_forwmu_l[channel]->GetXaxis()->SetBinLabel(6,"LightF");
    hs_forwmuL.Add(type_forwmu_l[channel]);

    type_forwmu_j[channel]->SetFillColor(getColor(channel));
    type_forwmu_j[channel]->GetXaxis()->SetBinLabel(1,"Unknown");
    type_forwmu_j[channel]->GetXaxis()->SetBinLabel(3,"Signal");
    type_forwmu_j[channel]->GetXaxis()->SetBinLabel(4,"HeavyF");
    type_forwmu_j[channel]->GetXaxis()->SetBinLabel(5,"Conversion");
    type_forwmu_j[channel]->GetXaxis()->SetBinLabel(6,"LightF");
    hs_forwmuJ.Add(type_forwmu_j[channel]);


    type_el_l[channel]->SetFillColor(getColor(channel));
    type_el_l[channel]->GetXaxis()->SetBinLabel(1,"Unknown");
    type_el_l[channel]->GetXaxis()->SetBinLabel(3,"Signal");
    type_el_l[channel]->GetXaxis()->SetBinLabel(4,"HeavyF");
    type_el_l[channel]->GetXaxis()->SetBinLabel(5,"Conversion");
    type_el_l[channel]->GetXaxis()->SetBinLabel(6,"LightF");
    hs_eL.Add(type_el_l[channel]);

    type_el_j[channel]->SetFillColor(getColor(channel));
    type_el_j[channel]->GetXaxis()->SetBinLabel(1,"Unknown");
    type_el_j[channel]->GetXaxis()->SetBinLabel(3,"Signal");
    type_el_j[channel]->GetXaxis()->SetBinLabel(4,"HeavyF");
    type_el_j[channel]->GetXaxis()->SetBinLabel(5,"Conversion");
    type_el_j[channel]->GetXaxis()->SetBinLabel(6,"LightF");
    hs_eJ.Add(type_el_j[channel]);


  // Signal=0,Fromb=1,Conversion=2,Hadron=3,Undefined=5,Unknown=-1
  }


  hs_muL.Draw("FHIST");
  hs_muL.SetMaximum(hs_muL.GetMaximum() *1.2);
  leg->Draw();
  t.DrawLatex(0.45,0.96,"central L muons");
  c1.SaveAs((outputPlotsdir+"type_muL.pdf").c_str());
  c1.Clear();

  hs_muJ.Draw("FHIST");
  hs_muJ.SetMaximum(hs_muJ.GetMaximum() *1.2);
  leg->Draw();
  t.DrawLatex(0.45,0.96,"central J muons");
  c1.SaveAs((outputPlotsdir+"type_muJ.pdf").c_str());
  c1.Clear();

  hs_forwmuL.Draw("FHIST");
  hs_forwmuL.SetMaximum(hs_forwmuL.GetMaximum() *1.2);
  leg->Draw();
  t.DrawLatex(0.45,0.96,"forw L muons");
  c1.SaveAs((outputPlotsdir+"type_forwmuL.pdf").c_str());
  c1.Clear();


  hs_forwmuJ.Draw("FHIST");
  hs_forwmuJ.SetMaximum(hs_forwmuJ.GetMaximum() *1.2);
  leg->Draw();
  t.DrawLatex(0.45,0.96,"forw J muons");
  c1.SaveAs((outputPlotsdir+"type_forwmuJ.pdf").c_str());
  c1.Clear();


  hs_eL.Draw("FHIST");
  hs_eL.SetMaximum(hs_eL.GetMaximum() *1.2);

  leg->Draw();
  t.DrawLatex(0.45,0.96,"L electrons");
  c1.SaveAs((outputPlotsdir+"type_eL.pdf").c_str());
  c1.Clear();


  hs_eJ.Draw("FHIST");
  hs_eJ.SetMaximum(hs_eJ.GetMaximum() *1.2);
  leg->Draw();
  t.DrawLatex(0.45,0.96,"J electrons");
  c1.SaveAs((outputPlotsdir+"type_eJ.pdf").c_str());
  c1.Clear();





}
int getColor(string channel)
{
  if(channel=="DPI") return kRed+3;
  else if(channel=="VVV") return kYellow;
  else if(channel=="Alpgen_Zbb") return kGreen+1;
  else if(channel=="Zg") return kBlue;
  else if(channel=="Alpgen_ZjetsLF") return kGreen;
  else if(channel=="ZjetsSherpa") return kGreen;
  else if(channel=="tZ") return kOrange+3;
  else if(channel=="ttbar") return  kOrange;
  else if(channel=="ttbarW") return kOrange+1;
  else if(channel=="ttbarZ") return kOrange+1;

  return 4;
}
//