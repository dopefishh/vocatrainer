#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

#define BUFFERLENGTH 4048

struct question {
	char *question;
	char *answer;
	unsigned int errors;
	struct question *next;
};

void train(char **files, int numfiles)
{
	printf("Going to train with %i files", numfiles);
	struct question *root;
	char buf[BUFFERLENGTH];
	FILE* currentfile;
	for(int i = 0; i < numfiles; i++){
		currentfile = fopen(files[i], "r");
		if(currentfile == NULL){
			fprintf(stderr, "Can't read "%s", skipping...\n",
				files[i]);
			continue;
		}
		while(fgets(buf, sizeof(buf), currentfile)){
			printf("Read: %s", buf);
		}
		fclose(currentfile);
	}
}

void print_usage(char *arg0, FILE *stream)
{
	fprintf(stream, "Usage:\n"
		"\t%s [options] file1 [file2 [file3 ... [filen]]]\n\n"
		"Options:\n"
		"\t-e     Reask questions that you had wrong in the end.\n"
		"\t-f NUM Forgiveness threshhold.\n"
		"\t-h     Show this help.\n"
		"\t-i     Inverse the question and answer, default: false.\n"
		"\t-r     Randomize the questions, default: false.\n"
		"\t-s SEP Custom separator, default: tab.\n", arg0);
}

void print_usage_malformed(char *arg0, char optopt)
{
	print_usage(arg0, stderr);
	if(optopt == 'f' || optopt == 's')
		fprintf(stderr, "\n\n-%c requires an argument.\n", optopt);
	else
		fprintf(stderr, "Unknown option -%c.\n\n", optopt);
}

int main(int argc, char **argv)
{
	int c;
	bool debug = false;
	bool reversed = false;
	bool shuffle = false;
	bool redo_errs = false;
	char *separator = "\t";
	int forgiveness = 0;
	
	opterr = 0;
	while((c=getopt(argc, argv, "irhes:f:d1l")) != -1)
		switch(c){
			case 'i':
				reversed = true;
				break;
			case 'r':
				shuffle = true;
				break;
			case 's':
				separator = optarg;
				break;
			case 'd':
				debug = true;
				break;
			case 'f':
				forgiveness = atoi(optarg);
				break;
			case 'e':
				redo_errs = true;
				break;
			case 'h':
				print_usage(argv[0], stdout);
				return 0;
			case '?':
				print_usage_malformed(argv[0], optopt);
				return 2;
			default:
				return -1;
		}

	if(argc == optind){
		print_usage(argv[0], stderr);
		fprintf(stderr,
			"\n\nYou have to specify at least one file...\n");
		return 2;
	}

	train(argv + optind, argc - optind);
	return 0;
}
