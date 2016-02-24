void integrateMacro(char * fileName){
	gROOT->ProcessLine(".L integrate_peaks.c");
	gROOT->ProcessLine("integrate_peaks scan;");
	TFile *f = new TFile(fileName);
	TTree *t = (TTree*)f; 
	gROOT->ProcessLine("Df125WindowRawData->Process(&scan)");
	f->Close();
}
