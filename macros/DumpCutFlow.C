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
  // fileVector.push_back("../YieldFiles_BothZ1Z2Fake/AnalysisManager.Yields_MC.Zjets.root");
  // fileVector.push_back("../YieldFiles_BothZ1Z2Fake/AnalysisManager.Yields_MC.ZZ.root");
  // fileVector.push_back("../YieldFiles_BothZ1Z2Fake/AnalysisManager.Yields_MC.gg_ZZ.root");
  // fileVector.push_back("../YieldFiles_BothZ1Z2Fake/AnalysisManager.Yields_MC.Zbb_3l.root");
  // fileVector.push_back("../InputFiles/badFF/AnalysisManager.Yields_MC.ttbarZj.root");
  // fileVector.push_back("../InputFiles/badFF/AnalysisManager.Yields_MC.ZjetsSherpa.root");
  fileVector.push_back("../InputFiles/AnalysisManager.DATA.FFHisto_Egamma_2lFilter.root");

  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodA.root");
  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodB.root");
  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodC.root");
  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodD.root");
  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodE.root");
  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodG.root");
  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodH.root");
  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodI.root");
  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodJ.root");
  // fileVector.push_back("../AnalysisManager.DATA.EgammaPeriodL.root");

  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodA.root");
  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodB.root");
  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodC.root");
  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodD.root");
  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodE.root");
  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodG.root");
  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodH.root");
  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodI.root");
  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodJ.root");
  // fileVector.push_back("../AnalysisManager.DATA.MuonsPeriodL.root");


  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_A.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_B.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_C.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_D.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_E.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_G.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_H.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_I.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_J.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataEgamma_L.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_A.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_B.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_C.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_D.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_E.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_G.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_H.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_I.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_J.root");
  // fileVector.push_back("root://eosatlas//eos/atlas/user/k/kbachas/FourLeptonFiles_MiniNT_24_7_V2/dataMuons_L.root");

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