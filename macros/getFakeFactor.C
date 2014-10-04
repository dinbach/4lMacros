#include <TH2F.h>
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <iostream>
using namespace std;
#include <string>
#include <sstream>
#include <TROOT.h>
#include <TSystem.h>

string elrecotype[1] = {"central"};
string murecotype[3] = {"central","forw","calo"};
string cut="";

TH2F *pt_eta_mu_l[3];
TH2F *pt_eta_mu_j[3];
TH1F *pt_mu_l[3];
TH1F *pt_mu_j[3];
TH1F *eta_mu_l[3];
TH1F *eta_mu_j[3];

TH2F *pt_eta_el_l[1];
TH2F *pt_eta_el_j[1];
TH1F *pt_el_l[1];
TH1F *pt_el_j[1];
TH1F *eta_el_l[1];
TH1F *eta_el_j[1];

TH1F* divideHists(TH1F *h1, TH1F *h2,string title);
TH2F* divideHists(TH2F *h1, TH2F *h2,string title);
void  doBinOptimization(TH1F *h_L, TH1F *h_J,string type);
void  doBinOptimization(TH2F *h_L, TH2F *h_J,string type);

string inputdir = "../InputFiles/";
string outputdir = "../OutputFiles/";
string outputPlotsdir = "../OutputPlots/";

void doLJDivision(string inputfname,string outputfname,string mcfname="");

void getFakeFactor()
{

  //add ZZ and WZ MC -- needed to subtract from data
  gSystem->Exec(("hadd -f "+outputdir+"AnalysisManager.mc12_8TeV.hists.Dibosons.root "+inputdir+"AnalysisManager.MC.FFHisto.WZSherpa.root "+inputdir+"AnalysisManager.MC.FFHisto.ZZ.root "+inputdir+"AnalysisManager.MC.FFHisto.ggH125p5_gg_ZZ.root").c_str());
  gSystem->Exec(("hadd -f "+outputdir+"AnalysisManager.mc12_8TeV.hists.ZjetsAlpgenAll.root "+inputdir+"AnalysisManager.MC.FFHisto.Zjets.root "+inputdir+"AnalysisManager.MC.FFHisto.Zbb_3l.root "+inputdir+"AnalysisManager.MC.FFHisto.Zbb_4l.root ").c_str());

  //data, subtracting contribution from dibosons with mc
  doLJDivision(inputdir+"AnalysisManager.DATA.FFHisto_2lFilter.root",outputdir+"hists_FF_data.root",outputdir+"AnalysisManager.mc12_8TeV.hists.Dibosons.root");

  //mc for Z+jets, sherpa
  doLJDivision(inputdir+"AnalysisManager.MC.FFHisto.ZjetsSherpa.root",outputdir+"hists_FF_SherpaZplusJets.root");

  //mc for Z+jets, alpgen
  doLJDivision(inputdir+"AnalysisManager.MC.FFHisto.Zjets.root",outputdir+"hists_FF_ZplusJets.root");

}


void doLJDivision(string inputfname,string outputfname,string mcfname)
{
  TFile *f;
  TFile *f2;
  TH1F *h1;
  TH2F *h2;

  bool doOpt = false;
  string version="";
  string solution = "";

  cout << "Starting..." << endl;
  // bool doOpt = true;
  // string version="_binn2";
  /////////////// retrieve histograms from data
  f = TFile::Open(inputfname.c_str());
  TH1::AddDirectory(kFALSE);
  for (int i=0;i<3;i++) {
    cout << solution << endl;
    pt_eta_mu_l[i] = (TH2F*) (f->Get(Form("MyTool/mu%s_L/pt_eta_%s%s_mu%s_L%s",solution.c_str(),murecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())))->Clone(Form("pt_eta_%smu_l_DATA",murecotype[i].c_str()));
    pt_eta_mu_j[i] = (TH2F*) (f->Get(Form("MyTool/mu%s_J/pt_eta_%s%s_mu%s_J%s",solution.c_str(),murecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())))->Clone(Form("pt_eta_%smu_j_DATA",murecotype[i].c_str()));
    pt_mu_l[i] = (TH1F*) (f->Get(Form("MyTool/mu%s_L/pt_%s%s_mu%s_L%s",solution.c_str(),murecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())))->Clone(Form("pt_%smu_l_DATA",murecotype[i].c_str()));
    pt_mu_j[i] = (TH1F*) (f->Get(Form("MyTool/mu%s_J/pt_%s%s_mu%s_J%s",solution.c_str(),murecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())))->Clone(Form("pt_%smu_j_DATA",murecotype[i].c_str()));
    eta_mu_l[i] = (TH1F*) (f->Get(Form("MyTool/mu%s_L/eta_%s_mu%s_L%s",solution.c_str(),murecotype[i].c_str(),solution.c_str(),cut.c_str())))->Clone(Form("eta_%smu_l_DATA",murecotype[i].c_str()));
    eta_mu_j[i] = (TH1F*) (f->Get(Form("MyTool/mu%s_J/eta_%s_mu%s_J%s",solution.c_str(),murecotype[i].c_str(),solution.c_str(),cut.c_str())))->Clone(Form("eta_%smu_j_DATA",murecotype[i].c_str()));
  }
  cout << "Histos read..." << endl;
  for (int i=0;i<1;i++) {
    pt_eta_el_l[i] = (TH2F*) (f->Get(Form("MyTool/e%s_L/pt_eta_%s%s_e%s_L%s",solution.c_str(),elrecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())))->Clone(Form("pt_eta_%sel_l_DATA",elrecotype[i].c_str()));
    pt_eta_el_j[i] = (TH2F*) (f->Get(Form("MyTool/e%s_J/pt_eta_%s%s_e%s_J%s",solution.c_str(),elrecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())))->Clone(Form("pt_eta_%sel_j_DATA",elrecotype[i].c_str()));
    pt_el_l[i] = (TH1F*) (f->Get(Form("MyTool/e%s_L/pt_%s%s_e%s_L%s",solution.c_str(),elrecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())))->Clone(Form("pt_%sel_l_DATA",elrecotype[i].c_str()));
    pt_el_j[i] = (TH1F*) (f->Get(Form("MyTool/e%s_J/pt_%s%s_e%s_J%s",solution.c_str(),elrecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())))->Clone(Form("pt_%sel_j_DATA",elrecotype[i].c_str()));

    eta_el_l[i] = (TH1F*) (f->Get(Form("MyTool/e%s_L/eta_%s_e%s_L%s",solution.c_str(),elrecotype[i].c_str(),solution.c_str(),cut.c_str())))->Clone(Form("eta_%sel_l_DATA",elrecotype[i].c_str()));
    eta_el_j[i] = (TH1F*) (f->Get(Form("MyTool/e%s_J/eta_%s_e%s_J%s",solution.c_str(),elrecotype[i].c_str(),solution.c_str(),cut.c_str())))->Clone(Form("eta_%sel_j_DATA",elrecotype[i].c_str()));

  }
  f->Close();

  if (mcfname!="") {
    f = TFile::Open(mcfname.c_str());
    TH1::AddDirectory(kFALSE);

    for (int i=0;i<3;i++) {
      pt_eta_mu_l[i]->Add((TH2F*)f->Get(Form("MyTool/mu%s_L/pt_eta_%s%s_mu%s_L%s",solution.c_str(),murecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())),-1);
      pt_eta_mu_j[i]->Add((TH2F*)f->Get(Form("MyTool/mu%s_J/pt_eta_%s%s_mu%s_J%s",solution.c_str(),murecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())),-1);
      pt_mu_l[i]->Add((TH1F*)f->Get(Form("MyTool/mu%s_L/pt_%s%s_mu%s_L%s",solution.c_str(),murecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())),-1);
      pt_mu_j[i]->Add((TH1F*)f->Get(Form("MyTool/mu%s_J/pt_%s%s_mu%s_J%s",solution.c_str(),murecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())),-1);
      eta_mu_l[i]->Add((TH1F*)f->Get(Form("MyTool/mu%s_L/eta_%s_mu%s_L%s",solution.c_str(),murecotype[i].c_str(),solution.c_str(),cut.c_str())),-1);
      eta_mu_j[i]->Add((TH1F*)f->Get(Form("MyTool/mu%s_J/eta_%s_mu%s_J%s",solution.c_str(),murecotype[i].c_str(),solution.c_str(),cut.c_str())),-1);
    }
    for (int i=0;i<1;i++) {
      pt_eta_el_l[i]->Add((TH2F*)f->Get(Form("MyTool/e%s_L/pt_eta_%s%s_e%s_L%s",solution.c_str(),elrecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())),-1);
      pt_eta_el_j[i]->Add((TH2F*)f->Get(Form("MyTool/e%s_J/pt_eta_%s%s_e%s_J%s",solution.c_str(),elrecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())),-1);
      pt_el_l[i]->Add((TH1F*)f->Get(Form("MyTool/e%s_L/pt_%s%s_e%s_L%s",solution.c_str(),elrecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())),-1);
      pt_el_j[i]->Add((TH1F*)f->Get(Form("MyTool/e%s_J/pt_%s%s_e%s_J%s",solution.c_str(),elrecotype[i].c_str(),version.c_str(),solution.c_str(),cut.c_str())),-1);
      eta_el_l[i]->Add((TH1F*)f->Get(Form("MyTool/e%s_L/eta_%s_e%s_L%s",solution.c_str(),elrecotype[i].c_str(),solution.c_str(),cut.c_str())),-1);
      eta_el_j[i]->Add((TH1F*)f->Get(Form("MyTool/e%s_J/eta_%s_e%s_J%s",solution.c_str(),elrecotype[i].c_str(),solution.c_str(),cut.c_str())),-1);
    }
    f->Close();
  }

  TFile* fout = TFile::Open(outputfname.c_str(),"RECREATE");
  TH1::AddDirectory(kTRUE);

  TH2F *pt_eta_mu_FF[3];
  TH2F *pt_eta_el_FF[2];

  TH1F *pt_mu_FF[3];
  TH1F *pt_el_FF[2];

  TH1F *eta_mu_FF[3];
  TH1F *eta_el_FF[2];

  //+original
  // Double_t etaBins_el[]={0,0.2,0.7,1.2,1.52,1.9,2.3,2.4,2.47};
  // Double_t etaBins_mu[]={0,0.1,0.3,0.7,1.1,1.3,1.7,2.3,2.5,2.7};
  // Double_t ptBins_el[]={7,10,15,20,30,40,50,60,80,100,300};
  // Double_t ptBins_mu[]={6,8,10,15,20,30,40,50,60,80,100,300};
  //-

  // for central  and forwd muons
  // Double_t ptBins_mu[6]={6,15,20,25,30,300};
  // for calo muons
  // {15,25,40,55,200};
  //for electrons
  // {7,10,15,30,60,80,300};

  for (int i=0;i<3;i++) {

    if (doOpt){
      // pt_eta_mu_l[i]->RebinY(10);
      // pt_eta_mu_j[i]->RebinY(10);

      if (i==0){
        doBinOptimization(pt_mu_l[i],pt_mu_j[i],"mu_central");
        // doBinOptimization(pt_eta_mu_l[i],pt_eta_mu_j[i],"mu_central");
      }
      else if (i==1){
       doBinOptimization(pt_mu_l[i],pt_mu_j[i],"mu_fwd");
       // doBinOptimization(pt_eta_mu_l[i],pt_eta_mu_j[i],"mu_fwd");
     }
     else if (i==2){
       doBinOptimization(pt_mu_l[i],pt_mu_j[i],"mu_calo");
       // doBinOptimization(pt_eta_mu_l[i],pt_eta_mu_j[i],"mu_calo");
     }
   }

   // if (i==1){
   //  Double_t ptBins_mu[3]={6,25,200};
   //  TH1F *new_pt_mu_l = (TH1F*)pt_mu_l[i]->Rebin(2,"new_pt_mu_l",ptBins_mu);
   //  TH1F *new_pt_mu_j = (TH1F*)pt_mu_j[i]->Rebin(2,"new_pt_mu_j",ptBins_mu);
   //  pt_mu_FF[i] = divideHists(new_pt_mu_l,new_pt_mu_j,Form("pt_%smu_FF",murecotype[i].c_str()));
   // }
   // else
    pt_mu_FF[i] = divideHists(pt_mu_l[i],pt_mu_j[i],Form("pt_%smu_FF",murecotype[i].c_str()));

    pt_eta_mu_FF[i] = divideHists(pt_eta_mu_l[i],pt_eta_mu_j[i],Form("pt_eta_%smu_FF",murecotype[i].c_str()));
    eta_mu_FF[i] = divideHists(eta_mu_l[i],eta_mu_j[i],Form("eta_%smu_FF",murecotype[i].c_str()));
  }

  for (int i=0;i<1;i++) {
    if (doOpt) {
      doBinOptimization(pt_el_l[i],pt_el_j[i],"el_central");
      // doBinOptimization(pt_eta_el_l[i],pt_eta_el_j[i],"el_central");
    }

    pt_eta_el_FF[i] = divideHists(pt_eta_el_l[i],pt_eta_el_j[i],Form("pt_eta_%sel_FF",elrecotype[i].c_str()));
    pt_el_FF[i] = divideHists(pt_el_l[i],pt_el_j[i],Form("pt_%sel_FF",elrecotype[i].c_str()));
    eta_el_FF[i] = divideHists(eta_el_l[i],eta_el_j[i],Form("eta_%sel_FF",elrecotype[i].c_str()));
  }
  fout->Write();
  fout->Close();
}

void  doBinOptimization(TH1F *h_L, TH1F *h_J,string type)
{

  vector< vector<Double_t> > ptBins;
  TH1F *pt_FF;
  vector<Double_t> bin_temp;

  // for (int ischeme=0;ischeme<=3;ischeme++)
  // {
  //   bin_temp.clear();
  //   if (type=="mu_central")
  //   {
  //     // for central  and forwd muons
  //     // {6,15,20,25,30,300};
  //     if (ischeme==0)
  //     {
  //        bin_temp.push_back(6);
  //        bin_temp.push_back(15);
  //        bin_temp.push_back(25);
  //        bin_temp.push_back(35);
  //        bin_temp.push_back(200);
  //     }
  //     else if (ischeme==1)
  //     {
  //       bin_temp.push_back(6);
  //       bin_temp.push_back(20);
  //       bin_temp.push_back(30);
  //       bin_temp.push_back(200);
  //     }
  //     else if (ischeme==2)
  //     {
  //       bin_temp.push_back(6);
  //       bin_temp.push_back(15);
  //       bin_temp.push_back(30);
  //       bin_temp.push_back(200);
  //     }
  //     else if (ischeme==3)
  //     {
  //       bin_temp.push_back(6);
  //       bin_temp.push_back(15);
  //       bin_temp.push_back(30);
  //       bin_temp.push_back(80);
  //       bin_temp.push_back(200);
  //     }
  //   }
  //   else if (type=="mu_fwd")
  //   {
  //     if (ischeme==0){
  //       bin_temp.push_back(6);
  //       bin_temp.push_back(15);
  //       bin_temp.push_back(30);
  //       bin_temp.push_back(200);
  //     }
  //     if (ischeme==1){
  //       bin_temp.push_back(6);
  //       bin_temp.push_back(20);
  //       bin_temp.push_back(30);
  //       bin_temp.push_back(200);
  //     }
  //     if (ischeme==2){
  //       bin_temp.push_back(6);
  //       bin_temp.push_back(20);
  //       bin_temp.push_back(30);
  //       bin_temp.push_back(80);
  //       bin_temp.push_back(200);
  //     }
  //     if (ischeme==3){
  //       bin_temp.push_back(6);
  //       bin_temp.push_back(30);
  //       bin_temp.push_back(60);
  //       bin_temp.push_back(200);
  //     }

  //   }
  //   else if (type=="mu_calo")
  //   {
  //     // for calo muons
  //     // {15,25,40,55,200};
  //     if (ischeme==0){
  //       bin_temp.push_back(15);
  //       bin_temp.push_back(25);
  //       bin_temp.push_back(55);
  //       bin_temp.push_back(200);
  //     }
  //     else if (ischeme==1){
  //       bin_temp.push_back(15);
  //       bin_temp.push_back(30);
  //       bin_temp.push_back(55);
  //       bin_temp.push_back(200);
  //     }
  //     else if (ischeme==2){
  //       bin_temp.push_back(15);
  //       bin_temp.push_back(30);
  //       bin_temp.push_back(60);
  //       bin_temp.push_back(200);
  //     }
  //     else if (ischeme==3){
  //       bin_temp.push_back(15);
  //       bin_temp.push_back(25);
  //       bin_temp.push_back(80);
  //       bin_temp.push_back(200);
  //     }


  //   }
  //   else if (type=="el_central")
  //   {
  //     // for electrons
  //     // {7,10,15,30,60,80,300};
  //    if (ischeme==0)
  //    {
  //     bin_temp.push_back(7);
  //     bin_temp.push_back(15);
  //     bin_temp.push_back(25);
  //     bin_temp.push_back(35);
  //     bin_temp.push_back(200);
  //   }
  //   else if (ischeme==1)
  //   {
  //    bin_temp.push_back(7);
  //    bin_temp.push_back(20);
  //    bin_temp.push_back(30);
  //    bin_temp.push_back(200);
  //  }
  //  else if (ischeme==2)
  //  {
  //    bin_temp.push_back(7);
  //    bin_temp.push_back(15);
  //    bin_temp.push_back(30);
  //    bin_temp.push_back(200);
  //  }
  //  else if (ischeme==3)
  //  {
  //    bin_temp.push_back(7);
  //    bin_temp.push_back(15);
  //    bin_temp.push_back(30);
  //    bin_temp.push_back(80);
  //    bin_temp.push_back(200);
  //  }
  //   }

  //   ptBins.push_back(bin_temp);
  // }

  for (int ischeme=0;ischeme<=10;ischeme++)
  {
    bin_temp.clear();
    if (type=="mu_central")
    {
     bin_temp.push_back(6);
     bin_temp.push_back(20);
     bin_temp.push_back(30+ischeme);
     bin_temp.push_back(200);
   }
   else if (type=="mu_fwd")
   {
    bin_temp.push_back(6);
    bin_temp.push_back(25);
    bin_temp.push_back(35+ischeme);
    bin_temp.push_back(200);
  }
  else if (type=="mu_calo")
  {
    bin_temp.push_back(15);
    bin_temp.push_back(35);
    bin_temp.push_back(55+ischeme);
    bin_temp.push_back(200);
  }
  else if (type=="el_central")
  {
   bin_temp.push_back(7);
   bin_temp.push_back(20);
   bin_temp.push_back(30+ischeme);
   bin_temp.push_back(200);
 }

 ptBins.push_back(bin_temp);
  }


  TMultiGraph * mg = new TMultiGraph("mg","mg");
  std::vector<TGraph*> graphVector;
  std::vector<string> binString;

    for (int ischeme=0; ischeme<ptBins.size(); ischeme++)
    {
      std::vector<Double_t> significance;
      std::vector<Double_t> binLowEdge;

      TH1F *h_pt_l = (TH1F*)h_L->Rebin(ptBins[ischeme].size()-1,"h_pt_l",&(ptBins[ischeme][0]));
      TH1F *h_pt_j = (TH1F*)h_J->Rebin(ptBins[ischeme].size()-1,"h_pt_j",&(ptBins[ischeme][0]));

      pt_FF = divideHists(h_pt_l,h_pt_j,Form("pt_%smu_FF",type.c_str()));

      // cout << "FF for type : " << type << endl;

      string binningString_temp="";

      for (int ibin=1;ibin<=pt_FF->GetNbinsX(); ibin++)
      {
        double binErr = pt_FF->GetBinError(ibin);
        if (binErr == 0 ) binErr =1;
        double sig = pt_FF->GetBinContent(ibin)/binErr;
        // cout << "Bin ["<< pt_FF->GetXaxis()->GetBinLowEdge(ibin)<<","<<pt_FF->GetXaxis()->GetBinUpEdge(ibin) <<"] : " << pt_FF->GetBinContent(ibin) << " +/- " << binErr << " sig: "<< sig  << endl;
        significance.push_back(sig);
        binLowEdge.push_back(pt_FF->GetXaxis()->GetBinLowEdge(ibin));

        stringstream textEvents;
        if (ibin==pt_FF->GetNbinsX())
          textEvents  << pt_FF->GetXaxis()->GetBinLowEdge(ibin);
        else
          textEvents  << pt_FF->GetXaxis()->GetBinLowEdge(ibin)<<",";

        binningString_temp += textEvents.str();
      }

      graphVector.push_back(new TGraph( ptBins[ischeme].size()-1, &(binLowEdge[0]), &(significance[0]) ) );
      binString.push_back(binningString_temp);
  }

  TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
  for (int ig=0;ig<graphVector.size(); ig++)
  {
    graphVector[ig]->SetMarkerStyle(ig+2);
    graphVector[ig]->SetMarkerColor(ig+2);
    graphVector[ig]->SetMarkerSize(1.3);

    // graphVector[ig]->SetLineColor(ig+2);
    mg->Add(graphVector[ig],"p");

    leg->AddEntry(graphVector[ig],binString[ig].c_str(),"p");
  }
  TCanvas canVas;
  canVas.cd();
  mg->Draw("ap");
  mg->SetTitle(type.c_str());
  mg->GetXaxis()->SetTitle("p_{T} bin lower edge [GeV]");
  mg->GetYaxis()->SetTitle("Fake Factor Significance");
  leg->Draw();

  canVas.SaveAs((outputPlotsdir+"Optimization1D_"+type+".pdf").c_str());
}

void  doBinOptimization(TH2F *h_L, TH2F *h_J,string type)
{

  TH2F *pt_FF;
  vector<int> bin_temp;

  for (int ischeme=0;ischeme<=1;ischeme++)
  {
    bin_temp.push_back(10+ischeme*10);
  }

  std::vector<TH2*> graphVector;
  std::vector<string> binString;

    for (int ischeme=0; ischeme<bin_temp.size(); ischeme++)
    {
      std::vector<Double_t> significance;
      std::vector<Double_t>  xbinLowEdge;
      std::vector<Double_t>  ybinLowEdge;

      TH2F *h_pt_l = (TH2F*)h_L->RebinX(bin_temp[ischeme],"h_pt_l");
      TH2F *h_pt_j = (TH2F*)h_J->RebinX(bin_temp[ischeme],"h_pt_j");

      pt_FF = divideHists(h_pt_l,h_pt_j,Form("pt_%smu_FF",type.c_str()));
      TH2 *h_temp = (TH2*)pt_FF->Clone();
      cout << "FF for type : " << type << endl;

      string binningString_temp="";
      for (int ibin=1;ibin<=pt_FF->GetNbinsX(); ibin++)
      {
        xbinLowEdge.push_back(pt_FF->GetXaxis()->GetBinLowEdge(ibin));

        stringstream textEvents;
        if (ibin==pt_FF->GetNbinsX())
          textEvents  << pt_FF->GetXaxis()->GetBinLowEdge(ibin);
        else
          textEvents  << pt_FF->GetXaxis()->GetBinLowEdge(ibin)<<",";

        binningString_temp += textEvents.str();
      }
      for (int ybin=1;ybin<=pt_FF->GetNbinsY(); ybin++)
      {
        ybinLowEdge.push_back(pt_FF->GetYaxis()->GetBinLowEdge(ybin));
      }


      for (int ibin=1;ibin<=pt_FF->GetNbinsX(); ibin++)
      {
        for (int ybin=1;ybin<=pt_FF->GetNbinsY(); ybin++)
        {
          double binErr = pt_FF->GetBinError(ibin,ybin);
          if (binErr == 0 ) binErr =1;
          double sig = pt_FF->GetBinContent(ibin,ybin)/binErr;
          // cout << "Bin x["<< pt_FF->GetXaxis()->GetBinLowEdge(ibin)<<","<<pt_FF->GetXaxis()->GetBinUpEdge(ibin) <<"] - Bin y["<<pt_FF->GetYaxis()->GetBinLowEdge(ybin)<<","<<pt_FF->GetYaxis()->GetBinUpEdge(ybin)<<"] "   << pt_FF->GetBinContent(ibin,ybin) << " +/- " << binErr << " sig: "<< sig  << endl;
          significance.push_back(sig);

          h_temp->SetBinContent(ibin,ybin,sig);
          h_temp->SetBinError(ibin,ybin,0);
      }
    }
    graphVector.push_back(h_temp);
    binString.push_back(binningString_temp);
  }


  for (int ig=0;ig<graphVector.size(); ig++)
  {
    TLegend leg = TLegend(0.7,0.3,0.9,0.5);
    TCanvas canVas;

    graphVector[ig]->Draw("colztext");
    graphVector[ig]->SetStats(0);
    graphVector[ig]->GetXaxis()->SetRangeUser(0.0,100);
    graphVector[ig]->GetXaxis()->SetTitle("p_{T}");
    graphVector[ig]->GetYaxis()->SetTitle("#eta");

    leg.AddEntry(graphVector[ig],binString[ig].c_str(),"lp");
    leg.Draw();

    stringstream variation;
    variation  << ig;
    canVas.SaveAs((outputPlotsdir+"Optimization2D_"+type+"_"+variation.str()+".pdf").c_str());
  }

}


TH1F* divideHists(TH1F *h1, TH1F *h2,string title)
{
  TH1F *h = (TH1F*) h1->Clone(title.c_str());
  for (int i=1;i<=h2->GetNbinsX();i++) {
    double f=0,fErr=0;
    double l = h1->GetBinContent(i);
    double j = h2->GetBinContent(i);
    double lErr = h1->GetBinError(i);
    double jErr = h2->GetBinError(i);

    if (j>0) {
      f=l/j;
      if (l>0) {
       fErr = f*sqrt( pow(lErr/l,2)+pow(jErr/j,2) );
      }
    }
    if (f<0) {
      // cout << "Fake rate negative for " << title << ". Setting to 0"<< endl;
      f=0;
    }
    h->SetBinContent(i,f);
    h->SetBinError(i,fErr);
  }
  return h;
}
TH2F* divideHists(TH2F *h1, TH2F *h2,string title)
{
  TH2F *h = (TH2F*) h1->Clone(title.c_str());
  for (int i=1;i<=h2->GetNbinsX();i++) {
    for (int j=1;j<=h2->GetNbinsY();j++) {
      double f=0,fErr=0;

      double L = h1->GetBinContent(i,j);
      double J = h2->GetBinContent(i,j);
      double LErr = h1->GetBinError(i,j);
      double JErr = h2->GetBinError(i,j);




      if (J>0) {
        // cout << "Bin ["<<i<<","<<j<<"] = " << L << " "<< J << " = " << L/J << endl;
       f=L/J;
       if (L>0) {
         fErr = f*sqrt( pow(LErr/L,2)+pow(JErr/J,2) );
       }
     }
     if (f<0) {
       // cout << "Fake rate negative for " << title << ". Setting to 0"<< endl;
       f=0.0000000001;
     }
     if (f==0) f=0.00000000001;
     h->SetBinContent(i,j,f);
     h->SetBinError(i,j,fErr);
   }
 }
  return h;
}
