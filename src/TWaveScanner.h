#define TWaveScanner_cxx
// The class definition in TWaveScanner.h has been generated automatically
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
// Root > T->Process("TWaveScanner.C")
// Root > T->Process("TWaveScanner.C","some options")
// Root > T->Process("TWaveScanner.C+")
//

#include <TH2.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TCanvas.h>
#include <TLine.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <iostream>

// Fixed size dimensions of array or collections stored in the TTree if any.

class TWaveScanner : public TSelector {
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
   const int analysisChannel = 13;
   const double yAxisRange = 2000.0;

   TWaveScanner(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~TWaveScanner() { }
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

   // Analysis functions
   virtual unsigned int * FindPeakWindow(std::vector<unsigned int> * data);

   ClassDef(TWaveScanner,1);
};
