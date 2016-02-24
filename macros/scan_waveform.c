#define scan_waveform_cxx
// The class definition in scan_waveform.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("scan_waveform.C")
// Root > T->Process("scan_waveform.C","some options")
// Root > T->Process("scan_waveform.C+")
//

#include <TH2.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TCanvas.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <iostream>

// Fixed size dimensions of array or collections stored in the TTree if any.

class scan_waveform : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   TCanvas        *c1;

   // Declaration of leaf types
   UInt_t          channelnum;
   UInt_t          eventnum;
   UInt_t          rocid;
   UInt_t          slot;
   UInt_t          channel;
   UInt_t          itrigger;
   vector<unsigned int> *waveform;
   UInt_t          nsamples;
   UInt_t          w_integral;
   UInt_t          w_min;
   UInt_t          w_max;
   UInt_t          w_samp1;
   UInt_t          w_ped;
   Float_t         w_time;
   UChar_t         invalid_samples;
   UChar_t         overflow;

   // List of branches
   TBranch        *b_channelnum;   //!
   TBranch        *b_eventnum;   //!
   TBranch        *b_rocid;   //!
   TBranch        *b_slot;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_itrigger;   //!
   TBranch        *b_waveform;   //!
   TBranch        *b_nsamples;   //!
   TBranch        *b_w_integral;   //!
   TBranch        *b_w_min;   //!
   TBranch        *b_w_max;   //!
   TBranch        *b_w_samp1;   //!
   TBranch        *b_w_ped;   //!
   TBranch        *b_w_time;   //!
   TBranch        *b_invalid_samples;   //!
   TBranch        *b_overflow;   //!

   // Analysis variables
   const int analysisChannel = 13;
   const double yAxisRange = 2000.0;

   // Analysis functions
   unsigned int * FindPeakWindow(vector<unsigned int> * data);

   scan_waveform(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~scan_waveform() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(scan_waveform,0);
};

void scan_waveform::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   waveform = 0;
   // Set branch addresses and branch pointers
   //if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("channelnum", &channelnum, &b_channelnum);
   fChain->SetBranchAddress("eventnum", &eventnum, &b_eventnum);
   fChain->SetBranchAddress("rocid", &rocid, &b_rocid);
   fChain->SetBranchAddress("slot", &slot, &b_slot);
   fChain->SetBranchAddress("channel", &channel, &b_channel);
   fChain->SetBranchAddress("itrigger", &itrigger, &b_itrigger);
   fChain->SetBranchAddress("waveform", &waveform, &b_waveform);
   fChain->SetBranchAddress("nsamples", &nsamples, &b_nsamples);
   fChain->SetBranchAddress("w_integral", &w_integral, &b_w_integral);
   fChain->SetBranchAddress("w_min", &w_min, &b_w_min);
   fChain->SetBranchAddress("w_max", &w_max, &b_w_max);
   fChain->SetBranchAddress("w_samp1", &w_samp1, &b_w_samp1);
   fChain->SetBranchAddress("w_ped", &w_ped, &b_w_ped);
   fChain->SetBranchAddress("w_time", &w_time, &b_w_time);
   fChain->SetBranchAddress("invalid_samples", &invalid_samples, &b_invalid_samples);
   fChain->SetBranchAddress("overflow", &overflow, &b_overflow);
}

Bool_t scan_waveform::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void scan_waveform::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   c1 = new TCanvas("c1");
	c1->Draw();
}

void scan_waveform::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t scan_waveform::Process(Long64_t entry)
{

  GetEntry(entry);
   
   if (channel==analysisChannel) {
		  int Nbins = waveform->size();
		  char title[256];
		  sprintf(title, "Event %d  ROC:%d SLOT:%d CHAN:%d", eventnum, rocid, slot, channel);
		  TH1D *h = new TH1D("Waveform", title, Nbins, 0.0, (double)Nbins);

		  unsigned int *peaks = FindPeakWindow(waveform);
		  unsigned int peakStart = *(peaks);
		  unsigned int peakEnd = *(peaks + 1);

		  unsigned int binValue;
		  wave_integral = 0;

		  for(unsigned int ibin=1; ibin<=Nbins; ibin++) {
			  binValue = waveform->at(ibin-1);
			  h->SetBinContent(ibin, binValue);
			  if (binValue >= peakStart && binValue <= peakEnd) {
				  wave_integral = wave_integral + binValue;
			  }
		  }


		  h->GetYaxis()->SetRangeUser(0.0, yAxisRange);
		  h->Draw();
		  TLine *startLine = new TLine((double)peakStart, 0.0, (double)peakStart, yAxisRange);
		  TLine *endLine = new TLine((double)peakEnd, 0.0, (double)peakEnd, yAxisRange);
		  startLine->Draw();
		  endLine->Draw();
		  c1->Update();

		  cout << "Press Enter to Continue";
		  cin.ignore();

		  delete h;
		  delete startLine;
		  delete endLine;
   }

   return kTRUE;
}

unsigned int * scan_waveform::FindPeakWindow(vector<unsigned int> * data)
{
		  static unsigned int peaks[2] = {0, 0};
		  unsigned int current;
		  unsigned int next;
		  unsigned int iterations;
		  unsigned int valAtPeakStart;
		  double comparison;

		  // find leading edge by checking for successive increases
		  for(unsigned int i=1; i<=data->size() - 2; i++) {
				current = data->at(i);
				next = data->at(i + 1);
				comparison = ((double)next - (double)current) / current;
				if (comparison > .2) {
						  iterations++;
						  if (iterations > 2) {
								peaks[0] = i;
								valAtPeakStart = current;
								break;
						  }
				}
				else {
						  iterations = 0;
				}
		  }

		  if (peaks[0] == 0){
					 // didn't find leading edge, give up
					 return peaks;
		  }

		  // found leading edge, look for where peak value goes below value at peak start
		  for(unsigned int i=peaks[0] + 1; i<=data->size() - 1; i++) {
					 current = data->at(i);
					 if (current < valAtPeakStart){
								peaks[1] = i;
								break;
					 }
		  }

		  return peaks;
}

void scan_waveform::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void scan_waveform::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
