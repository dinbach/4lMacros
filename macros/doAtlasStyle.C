{
  gROOT->ProcessLine("#include \"AtlasStyle.C\"");
  gROOT->ProcessLine("#include \"AtlasUtils.C\"");
  TStyle* atlasStyle = AtlasStyle();
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
  gStyle->SetPalette(1,0);
}
