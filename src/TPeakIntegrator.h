#ifndef TPeakIntegrator_cxx
#define TPeakIntegrator_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TChain.h>
#include <TSelector.h>
#include "analysisFunctions.h"

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <iostream>

class TPeakIntegrator : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   UInt_t          channelnum;
   UInt_t          eventnum;
   UInt_t          rocid;
   UInt_t          slot;
   UInt_t          channel;
   UInt_t          itrigger;
   std::vector<unsigned int> *waveform;
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
   mutable int analysisChannel;
   mutable double yAxisRange;
   mutable enum PeakFindingMethod peakMethod;
   mutable int minIntegral; // integral must > this value to appear in output
   struct PeakFindingOptions peakOptions;
   std::vector<unsigned int> * integrals;
   std::vector<unsigned int> * leading_edge_times;

   TPeakIntegrator(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~TPeakIntegrator() { }
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
   virtual void    SetAnalysisChannel(int channel) { analysisChannel = channel; }
   virtual void    SetPeakFindingMethod(enum PeakFindingMethod method) { peakMethod = method; }
   virtual void    SetMinIntegral(int min) { 
	   if(min > 0)
		   minIntegral = min;
	   else
		   minIntegral = 0;
   }
   virtual void    SetPeakThreshold(double threshold){
	   if (threshold > 0)
		   peakOptions.threshold = threshold;
	   else
		   peakOptions.threshold = 0;
   }
   virtual void    SetPeakIterations(int iterations){
	   if (iterations > 0)
		   peakOptions.iterations = iterations;
	   else
		   peakOptions.iterations = 1;
   }

   ClassDef(TPeakIntegrator,1);
};
#endif
