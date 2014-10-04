{

  vector<string> plots;
  plots.push_back("pt_centralmu_FF");
  // plots.push_back("pt_forwmu_FF");
  // plots.push_back("pt_calomu_FF");
  // plots.push_back("pt_centralel_FF");

  vector<string> plots2D;
  plots2D.push_back("pt_eta_centralmu_FF");
  // plots2D.push_back("pt_eta_calomu_FF");
  // plots2D.push_back("pt_eta_forwmu_FF");
  // plots2D.push_back("pt_eta_centralel_FF");

  // TFile *f = new TFile("../OutputFiles/hists_FF_data.root","READ");
  TFile *f = new TFile("/afs/cern.ch/user/k/kbachas/SFRAME/ElectroweakBosons/AnalysisFourLeptons/hists_FF_data_28_9.root","READ");
  //   KEY: TH1F eta_centralmu_FF;1
  //   KEY: TH1F eta_forwmu_FF;1
  //   KEY: TH1F eta_calomu_FF;1
  //   KEY: TH1F eta_centralel_FF;1

  for (unsigned int j=0;j<plots.size();j++)
  {
    cout << "Extracting numbers for " << plots[j] << endl;
    TH1F* h = (TH1F*)f.Get(plots[j].c_str());

    for (unsigned int i=1;i<=h->GetNbinsX();i++)
    {
      cout << "Bin ["<< h->GetXaxis()->GetBinLowEdge(i)<<","<<h->GetXaxis()->GetBinUpEdge(i) <<"] : " << h->GetBinContent(i) << " +/- " <<  h->GetBinError(i) << endl;
    }
  }

  for (unsigned int j=0;j<plots2D.size();j++)
  {
    cout << "Extracting numbers for " << plots2D[j] << endl;
    TH2F* h2d = (TH2F*)f.Get(plots2D[j].c_str());

    for (unsigned int i=1;i<=h2d->GetNbinsX();i++)
    {
      for (unsigned int k=1;k<=h2d->GetNbinsY();k++)
      {
        cout << "BinX ["<< h2d->GetXaxis()->GetBinLowEdge(i)<<","<<h2d->GetXaxis()->GetBinUpEdge(i) <<"] - BinY ["<< h2d->GetYaxis()->GetBinLowEdge(k)<<","<<h2d->GetYaxis()->GetBinUpEdge(k)<< "] : " << h2d->GetBinContent(i,k) << " +/- " <<  h2d->GetBinError(i,k) << endl;
      }
    }
  }

}