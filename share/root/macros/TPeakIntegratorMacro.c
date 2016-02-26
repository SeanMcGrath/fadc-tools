void TPeakIntegratorMacro(char * fileName){
	TFile *f = new TFile(fileName);
	TTree *t = (TTree*)f; 
	TPeakIntegrator integrator;
	Df125WindowRawData->Process(&integrator);
	f->Close();
}
