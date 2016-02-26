void TWaveScannerMacro(char * fileName){
	TFile *f = new TFile(fileName);
	TTree *t = (TTree*)f; 
	TWaveScanner scan;
	Df125WindowRawData->Process(&scan);
	f->Close();
}
