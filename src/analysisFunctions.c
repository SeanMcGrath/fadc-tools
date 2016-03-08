#include "fadc.h"

// Detects start/end sample numbers of peak if they exist.
// Threshold is a fraction representing the percent increase that must occur from one sample
// to the next in order for that pair of samples to be counted towards a potential peak detection.
// iterations i the number of successive over-threshold increases that must occur for a peak to be detected.
//
// Returns [0, 0] if no peak is found 
unsigned int * FindPeakWindow(std::vector<unsigned int> * data, double threshold, int iterations)
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
						  iterations++;
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
