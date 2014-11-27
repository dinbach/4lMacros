#include <iostream>
#include <fstream>
#include <vector>
#include "TFile.h"

using namespace std;



// run with:
// root -l DumpCutFlow.C'("../CutFlowInputAllWeights.root","Nominal/pid_160205/CutFlows/incl4e/CutFlow_incl4e")'
// root -l DumpCutFlow.C'("../CutFlowInputAllWeights.root","Nominal/pid_160205/CutFlows/incl4mu/CutFlow_incl4mu")'
// root -l DumpCutFlow.C'("../CutFlowInputAllWeights.root","Nominal/pid_160205/CutFlows/incl2mu2e/CutFlow_incl2mu2e")'
// root -l DumpCutFlow.C'("../CutFlowInputAllWeights.root","Nominal/pid_160205/CutFlows/incl2e2mu/CutFlow_incl2e2mu")'

void DumpCutFlow() {


  std::vector<string> fileVector;
  fileVector.push_back("/Users/kbachas/WORK/4lInclusive/24_11_2014_FFBackground/InputFiles/AnalysisManager.DATA.FFHisto.root");

  std::vector<string> cutFlowName;
  // cutFlowName.push_back("MyTool/CutFlows/QuadSel_4e/CutFlow_QuadSel_4e");
  // cutFlowName.push_back("MyTool/CutFlows/QuadSel_4m/CutFlow_QuadSel_4m");
  // cutFlowName.push_back("MyTool/CutFlows/QuadSel_2e2m/CutFlow_QuadSel_2e2m");
  // cutFlowName.push_back("MyTool/CutFlows/QuadSel_2m2e/CutFlow_QuadSel_2m2e");

  // cutFlowName.push_back("Nominal/CutFlows/incl4e/CutFlow_incl4e");
  // cutFlowName.push_back("Nominal/CutFlows/incl4mu/CutFlow_incl4mu");
  // cutFlowName.push_back("Nominal/CutFlows/incl2e2mu/CutFlow_incl2e2mu");
  // cutFlowName.push_back("Nominal/CutFlows/incl2mu2e/CutFlow_incl2mu2e");
  cutFlowName.push_back("MyTool/CutFlows/EventSelection/CutFlow_EventSelection");

  TH1 *hsum;

  for (unsigned int ifile=0;ifile<fileVector.size();ifile++)
  {
    string currentFile = fileVector[ifile];
    cout << "Opening file : " << currentFile << endl;
    TFile *f1 = TFile::Open(currentFile.c_str());

    if(!f1 ) {
      cout<<"unable to open file"<<endl;
      exit(1);
    }

    for (unsigned int i=0; i<cutFlowName.size() ; i++)
    {
      cout << "Getting Histo : " << cutFlowName[i] << endl;
      TH1F* h1 = (TH1F*) f1->Get(cutFlowName[i].c_str());
      if (!h1) {
        cout << "unable to find histo"<<endl;
        exit(1);
      }

      if (ifile==0)
        hsum = (TH1*)h1->Clone();
      else
        hsum->Add(h1);

      for(int b=1; b<=h1->GetNbinsX(); ++b) {
        Double_t n1=h1->GetBinContent(b);
        Double_t n1err=h1->GetBinError(b);
        cout<< setw(20)<<fixed << h1->GetXaxis()->GetBinLabel(b)<<" "<< setw(10)<<fixed << setprecision(1)<< n1 <<" +- " << setw(5)<< fixed << n1err <<endl;
      }
    }

  }

  cout << "--------------------------------------" << endl;
  cout << "Total Cutflow from all files" << endl;
  for(int b=1; b<=hsum->GetNbinsX(); ++b) {
    Double_t n1=hsum->GetBinContent(b);
    Double_t n1err=hsum->GetBinError(b);
    cout<< setw(20)<<fixed << hsum->GetXaxis()->GetBinLabel(b)<<" "<< setw(10)<<fixed << setprecision(1)<< n1 <<" +- " << setw(5)<< fixed << n1err <<endl;
  }

}