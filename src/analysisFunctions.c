#include "analysisFunctions.h"

int mean(std::vector<unsigned int> * vec)
{
	int total = 0;
	for (int i=0; i<vec->size(); i++) {
		total += vec->at(i);
	}

	return total / vec->size();
}

unsigned int peakMax(std::vector<unsigned int> * vec){

	unsigned int max = 0;
	unsigned int current;
	for (int i = 0; i < vec->size(); i++){
		current = vec->at(i);
		if (current > max) {
			max = current;
		}
	}

	return max;
}

unsigned int * FindPeakByMean(std::vector<unsigned int> * data)
{
	static unsigned int peaks[2] = {0, 0};
	unsigned int avg = mean(data);
	int i;
	int reduced;

	for (i=0; i<data->size(); i++)
	{
		reduced = (int)data->at(i) - avg;
		if (reduced > 0) {
			peaks[0] = i;
			break;
		}
	}

	i += 5;

	for (i; i<data->size(); i++)
	{
		reduced = (int)data->at(i) - avg;
		if (reduced < 0) {
			peaks[1] = i;
			break;
		}
	}
	
	return peaks;
}

// Detects start/end sample numbers of peak if they exist.
// Threshold is a fraction representing the percent increase that must occur from one sample
// to the next in order for that pair of samples to be counted towards a potential peak detection.
// iterations i the number of successive over-threshold increases that must occur for a peak to be detected.
//
// Returns [0, 0] if no peak is found 
unsigned int * FindPeakByIncreases(std::vector<unsigned int> * data, double threshold, int iterations)
{
		  static unsigned int peaks[2] = {0, 0};
		  unsigned int current;
		  unsigned int next;
		  unsigned int iters;
		  unsigned int valAtPeakStart;
		  unsigned int i;
		  double comparison;

		  // find leading edge by checking for successive increases
		  for(i=1; i<=data->size() - 2; i++) {
				current = data->at(i);
				next = data->at(i + 1);
				comparison = ((double)next - (double)current) / current;
				if (comparison > threshold) {
						  iters++;
						  if (iters > iterations) {
								peaks[0] = i;
								valAtPeakStart = current;
								break;
						  }
				}
				else {
						  iters = 0;
				}
		  }

		  if (peaks[0] == 0){
					 // didn't find leading edge, give up
					 return peaks;
		  }

		  // found leading edge, look for where peak value goes below value at peak start
		  for(i=peaks[0] + 1; i<=data->size() - 1; i++) {
					 current = data->at(i);
					 if (current < valAtPeakStart){
								break;
					 }
		  }

		  peaks[1] = i;
		  return peaks;
}

// Detects start/end of peak by continuous fraction method.
// finds wave baseline by averaging over first 20 samples,
// then finds when wave goes above/below (baseline + peak_max*threshold)
unsigned int * FindPeakByConstantFraction(std::vector<unsigned int> * data, double threshold)
{
	unsigned int peaks[2] = {0, 0};
	unsigned int current;
	double comparison;
	std::vector<unsigned int> subvec = std::vector<unsigned int>(data->begin(), data->begin() + 19);
	unsigned int avg = mean(&subvec);
	unsigned int max = peakMax(data);
	if ((max - avg) < (avg*threshold))
		return peaks;

	double thresholdVal = avg + max*threshold;
	unsigned int i;

	// find peak start
	for (i=20; i < data->size(); i++) {
		current = data->at(i);
		if (current > thresholdVal) {
			peaks[0] = i;
			break;
		}
	}

	// find peak end
	if (peaks[0] != 0) {

		for (i; i < data->size(); i++) {
			current = data->at(i);
			if (current < thresholdVal) {
				peaks[1] = i;
				break;
			}
		}

		// no peak end found, set peak end to last value in wave
		if (peaks[1] == 0) {
			peaks[1] = i;
		}

	}

	return peaks;

}

unsigned int * FindPeak(
		std::vector<unsigned int> * data,
		enum PeakFindingMethod method,
		struct PeakFindingOptions options)
{
	unsigned int * peaks;

	switch (method) 
	{
            case byIncreases:
                peaks = FindPeakByIncreases(data, options.threshold, options.iterations);
                break;
            case byMean:
                peaks = FindPeakByMean(data);
                break;
	    case byConstFraction:
		peaks = FindPeakByConstantFraction(data, options.threshold);
		break;
            case none:
		unsigned int temp[2] = {0, 0};
		peaks = &temp[0];
                break;
	}

	return peaks;
}
