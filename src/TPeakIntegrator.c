#include "TPeakIntegrator.h"
#include "analysisFunctions.h"

#define MAX_CHANNEL 256

ClassImp(TPeakIntegrator);
void TPeakIntegrator::Init(TTree *tree)
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
    integrals = new std::vector<unsigned int>[MAX_CHANNEL];
    leading_edge_times = new std::vector<unsigned int>[MAX_CHANNEL];

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

Bool_t TPeakIntegrator::Notify()
{
// The Notify() function is called when a new file is opened. This
// can be either for a new TTree in a TChain or when when a new TTree
// is started when using PROOF. It is normally not necessary to make changes
// to the generated code, but the routine can be extended by the
// user if needed. The return value is currently not used.

    return kTRUE;
}

void TPeakIntegrator::Begin(TTree * /*tree*/)
{
// The Begin() function is called at the start of the query.
// When running with PROOF Begin() is only called on the client.
// The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

void TPeakIntegrator::SlaveBegin(TTree * /*tree*/)
{
// The SlaveBegin() function is called after the Begin() function.
// When running with PROOF SlaveBegin() is called on each slave server.
// The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();

}

Bool_t TPeakIntegrator::Process(Long64_t entry)
{

    GetEntry(entry);

    if (channel==analysisChannel || analysisChannel < 0) {
        int Nbins = waveform->size();

        unsigned int *peaks = FindPeak(waveform, peakMethod, peakOptions);

        unsigned int peakStart = *(peaks);
        unsigned int peakEnd = *(peaks + 1);

	// No Peak
        if (peakStart == 0 && peakEnd == 0)
            return kTRUE;

	// Peak starts, but doesn't end
        if (peakEnd >= Nbins)
            peakEnd = Nbins - 1;

        unsigned int binValue;
        unsigned int wave_integral = 0;

        for(unsigned int ibin=peakStart; ibin<=peakEnd; ibin++) {
            try {
                binValue = waveform->at(ibin);
                wave_integral = wave_integral + binValue;
            }
            catch (...) {
                std::cout << ibin;
            }

        }

// Peak found
        if (wave_integral > minIntegral){
            integrals[channel].push_back(wave_integral);
            leading_edge_times[channel].push_back(peakStart);
        }
    }  

    return kTRUE;
}


void TPeakIntegrator::SlaveTerminate()
{
// The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.

}

void TPeakIntegrator::Terminate()
{
// The Terminate() function is the last function to be called during
// a query. It always runs on the client, it can be used to present
// the results graphically or save the results to file.

    // do printing
    std::vector<unsigned int> chan_integrals;
    std::vector<unsigned int> chan_times;
    for(int j = 0; j < MAX_CHANNEL; j++){
        chan_integrals = integrals[j];
        chan_times = leading_edge_times[j]; 
    
        if (!chan_integrals.empty()){
            std::cout << "Channel " << j << std::endl;
            std::cout << "Wave integral, Wave Leading Edge" << std::endl;
            for(int k = 0; k < chan_integrals.size(); k++){
                std::cout << chan_integrals.at(k) << "," << chan_times.at(k) << std::endl;
            }
            std::cout << std::endl;
        }


    }
}
