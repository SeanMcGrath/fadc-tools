#include "fadc.h"
#include "stdlib.h"
#include "argp.h"

using namespace std;

// argp configuration
const char *argp_program_version = "fadc 0.1";
const char *argp_program_bug_address = "<srmcgrat@umass.edu>";
static char doc[] =
	"Utility for viewing and extracting the data contained in fADC125 .root files.\n"
	"COMMANDS:\n"
	"	view 		see plots of all the waveforms in the root file.\n"
	"	integrate	print a comma-separated list of pulse integrals\n"
	"			and leading-edge times to standard out.\n"
	"\n"
	"OPTIONS:\n";

static char args_doc[] = "COMMAND CHANNEL ROOT_FILE";

static struct argp_option options[] = {
	{"yrange",	'y', "Y_RANGE", OPTION_ARG_OPTIONAL, "set Y_RANGE as the maximum Y value of displayed plots."},
	{ 0 }
};

struct arguments
{
	char *command;
	int channel;
	char *rootFile;
	double yrange;
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

		case ARGP_KEY_ARG:
			if (state->arg_num >= 3)
				argp_usage(state);
			else if (state->arg_num == 0)
				arguments->command = arg;
			else if (state->arg_num == 1)
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

TFile *f;

TTree * getRawData(char *fileName)
{
	f = new TFile(fileName);
	TTree *Df125WindowRawData = (TTree*)f->Get("Df125WindowRawData");
	return Df125WindowRawData;
}

void clean() { delete f; }

int main(int argc, char *argv[])
{
	struct arguments arguments;

	//defaults
	arguments.yrange = 2000.0;
	arguments.command = "";
	
	argp_parse(&argp, argc, argv, ARGP_NO_EXIT, 0, &arguments);

	if (strcmp(arguments.command, "view") == 0) {
		TTree *data = getRawData(arguments.rootFile);
		TWaveScanner scan;
		scan.SetAnalysisChannel(arguments.channel);
		scan.SetYAxisRange(arguments.yrange);
		data->Process(&scan);
	}
	else if (strcmp(arguments.command, "integrate") == 0) {
		TTree *data = getRawData(arguments.rootFile);
		TPeakIntegrator integrator;
		integrator.SetAnalysisChannel(arguments.channel);
		data->Process(&integrator);
	}
	else if (strcmp(arguments.command, "") != 0)
		cout << "unknown command: " << arguments.command << endl;
	return 0;	
}
