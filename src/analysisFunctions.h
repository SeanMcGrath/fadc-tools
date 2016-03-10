#ifndef analysisFunctions_cxx
#define analysisFunctions_cxx
#include <vector>

enum PeakFindingMethod
{
	byIncreases,
	byMean,
	none
};

// Analysis functions
int mean(std::vector<unsigned int> * vec);
unsigned int * FindPeakByMean(std::vector<unsigned int> * data);
unsigned int * FindPeakByIncreases(std::vector<unsigned int> * data, double threshold, int iterations);

#endif
