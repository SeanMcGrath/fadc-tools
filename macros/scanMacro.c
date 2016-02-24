void scanMacro(char * fileName){
	gROOT->ProcessLine(".L scan_waveform.c");
	gROOT->ProcessLine("scan_waveform scan;");
	TFile *f = new TFile(fileName);
	TTree *t = (TTree*)f; 
	gROOT->ProcessLine("Df125WindowRawData->Process(&scan)");
	f->Close();
}
