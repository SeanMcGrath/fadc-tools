#include "stdlib.h"
#include "argp.h"
#include <fstream>
#include <TFile.h>
#include <TApplication.h>
#include "TWaveScanner.h"
#include "TPeakIntegrator.h"

using namespace std;

// argp configuration
const char *argp_program_version = "fadc 0.1";
const char *argp_program_bug_address = "<srmcgrat@umass.edu>";
static char doc[] =
	"Utility for viewing and extracting the data contained in fADC125 .root files.\n"
	"COMMANDS:\n"
	"	view 		see plots of all the waveforms in the root file.\n"
	"	analyze		print a comma-separated list of pulse integrals\n"
	"			and leading-edge times to standard output.\n"
	"\n"
	"CHANNEL: The number of the desired FADC channel, or 'all' to see all channels.\n"
	"\n"
	"OPTIONS:\n";

static char args_doc[] = "COMMAND CHANNEL ROOT_FILE";

static struct argp_option options[] = {
	{"peakmethod",	'p', "METHOD",	0, "Use METHOD to find the peak in the waveform. METHOD must be one of { average | fractional | constfrac }"},
	{"yrange",	'y', "Y_RANGE",	0, "set Y_RANGE as the maximum Y value of displayed plots."},
	{"outfile",	'o', "OUT_FILE", 0, "Print analysis results to OUT_FILE."},
	{"min-integral",'m', "MIN_INTEGRAL", 0, "Reject waves with integral less than MIN_INTEGRAL"},
	{"rejection-threshold",	'r', "THRESHOLD", 0, "Use THRESHOLD as the peak rejection threshold for the constfrac peak finding method"},
	{"peak-threshold",	't', "THRESHOLD", 0, "Use THRESHOLD as the fractional height threshold for the constfrac peak finding method"},
	{"samples",	's', "SAMPLES", 0, "For the constant fraction method, calculate the sample baseline over the first SAMPLES samples in each waveform"},
	{ 0 }
};

struct arguments
{
	char *command;
	char *rootFile;
	char *outFile;
	int channel;
	int minIntegral;
	int baselineSamples;
	double yrange;
	enum PeakFindingMethod method;
	double threshold;
	double threshold2;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = (struct arguments *)state->input;

	switch (key)
	{
		case 'y':
			arguments->yrange = (double)strtof(arg, NULL);
			break;
		case 'p':
			if (strcmp(arg, "average") == 0) {
				arguments->method = byMean;
			}
			else if (strcmp(arg, "fractional") == 0) {
				arguments->method = byIncreases;
			}
			else if (strcmp(arg, "constfrac") == 0) {
				arguments->method = byConstFraction;
			}
			break;
		case 'o':
			arguments->outFile = arg;
			break;
		case 'm':
			arguments->minIntegral = (int)strtol(arg, NULL, 10);
			break;
		case 'r':
			arguments->threshold = atof(arg);
			break;
		case 't':
			arguments->threshold2 = atof(arg);
			break;
		case 's':
			arguments->baselineSamples = (int)strtol(arg, NULL, 10);
			break;

		case ARGP_KEY_ARG:
			if (state->arg_num >= 3) {
				cout << "Too many arguments." << endl;
				argp_usage(state);
			}
			else if (state->arg_num == 0)
				arguments->command = arg;
			else if (state->arg_num == 1)
				if (strcmp(arg, "all") == 0)
					arguments->channel = -1;
				else
					arguments->channel = (int)strtol(arg, NULL, 10);
			else if (state->arg_num == 2)
				arguments->rootFile = arg;
			break;
		
		case ARGP_KEY_END:
			if (state->arg_num < 3)
				argp_usage(state);
			break;

		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

// Main

TTree * getRawData(char *fileName)
{
	TFile *f = new TFile(fileName);
	TTree *Df125WindowRawData = (TTree*)f->Get("Df125WindowRawData");
	return Df125WindowRawData;
}

int main(int argc, char *argv[])
{
	struct arguments arguments;

	//defaults
	arguments.yrange = 2000.0;
	arguments.command = "";
	arguments.method = byConstFraction;
	arguments.channel = 13;
	arguments.rootFile = "";
	arguments.outFile = 0;
	arguments.minIntegral = 0;
	arguments.threshold = 0.5;
	arguments.threshold2 = 0.05;
	arguments.baselineSamples = 5;
	
	argp_parse(&argp, argc, argv, ARGP_NO_EXIT, 0, &arguments);

	if (strcmp(arguments.command, "view") == 0) {
		TApplication theApp("tapp", &argc, argv);
		TTree *data = getRawData(arguments.rootFile);
		TCanvas *canvas = new TCanvas("c1");
		TWaveScanner scan;
		scan.SetAnalysisChannel(arguments.channel);
		scan.SetYAxisRange(arguments.yrange);
		scan.SetPeakFindingMethod(arguments.method);
		scan.SetPeakThreshold(arguments.threshold);
		scan.SetPeakThreshold2(arguments.threshold2);
		scan.SetPeakIterations(3);
		scan.SetBaselineSamples(arguments.baselineSamples);
		scan.SetCanvas(canvas);
		data->Process(&scan);
	}

	else if (strcmp(arguments.command, "analyze") == 0) {
		streambuf * coutbuf;
		ofstream outFile;
		if (arguments.outFile != 0){
			outFile.open(arguments.outFile);
			coutbuf = cout.rdbuf();
			cout.rdbuf(outFile.rdbuf());
		}
		TTree *data = getRawData(arguments.rootFile);
		TPeakIntegrator integrator;
		integrator.SetAnalysisChannel(arguments.channel);
		integrator.SetPeakFindingMethod(arguments.method);
		integrator.SetMinIntegral(arguments.minIntegral);
		integrator.SetPeakThreshold(arguments.threshold);
		integrator.SetPeakThreshold2(arguments.threshold2);
		integrator.SetPeakIterations(3);
		integrator.SetBaselineSamples(arguments.baselineSamples);
		data->Process(&integrator);
		if (arguments.outFile != 0){
			cout.rdbuf(coutbuf);
		}
	}

	else if (strcmp(arguments.command, "") != 0)
		cout << "unknown command: " << arguments.command << endl;

	return 0;	
}
