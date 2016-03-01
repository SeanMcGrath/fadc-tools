void TWaveScannerMacro(char * fileName, short channel=1, double yAxisRange=2000.0, bool autoY=false){
	TFile *f = new TFile(fileName);
	TTree *t = (TTree*)f; 
	TWaveScanner scan;
	scan->SetAnalysisChannel(channel);
	scan->SetYAxisRange(yAxisRange);
	scan->SetAutoYAxis(autoY);
	Df125WindowRawData->Process(&scan);
	f->Close();
}
