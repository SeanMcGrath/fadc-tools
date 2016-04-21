#include "TWaveScanner.h"
#include "analysisFunctions.h"
#include <TLine.h>

ClassImp(TWaveScanner);

void TWaveScanner::Init(TTree *tree)
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

Bool_t TWaveScanner::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TWaveScanner::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   c1->Draw();
}

void TWaveScanner::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t TWaveScanner::Process(Long64_t entry)
{

  GetEntry(entry);
   
   if (channel==analysisChannel || analysisChannel < 0) {
		  int Nbins = waveform->size();
		  char title[256];
		  sprintf(title, "Event %d  ROC:%d SLOT:%d CHAN:%d", eventnum, rocid, slot, channel);
		  TH1D *h = new TH1D("Waveform", title, Nbins, 0.0, (double)Nbins);

		  unsigned int *peaks = FindPeak(waveform, peakMethod, peakOptions);

		  unsigned int peakStart = *(peaks);
		  unsigned int peakEnd = *(peaks + 1);

		  unsigned int binValue;

		  for(unsigned int ibin=1; ibin<=Nbins; ibin++) {
			  binValue = waveform->at(ibin-1);
			  h->SetBinContent(ibin, binValue);
		  }


		  h->GetYaxis()->SetRangeUser(0.0, yAxisRange);
		  h->Draw();
		  TLine *startLine = new TLine((double)peakStart, 0.0, (double)peakStart, yAxisRange);
		  TLine *endLine = new TLine((double)peakEnd, 0.0, (double)peakEnd, yAxisRange);
		  startLine->Draw();
		  endLine->Draw();
		  c1->Update();

		  std::cout << "Press Enter to Continue";
		  std::cin.ignore();

		  delete h;
		  delete startLine;
		  delete endLine;
   }

   return kTRUE;
}

void TWaveScanner::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void TWaveScanner::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
