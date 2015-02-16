#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "question.h"

bool O_INV = false;
bool O_SHF = false;
bool O_RER = false;
char O_SEP = '\t';
int O_FOR = 0;

void train(char **files, int nf)
{
	printf("Going to train with %i files\n", nf);
	struct question *head = q_questions_from_files(files, nf, O_SEP);
	if(O_SHF)
		head = q_randomize_list(head);

	struct question *cur = head;
	char *question;
	char *answer;
	char *useranswer;
	do {
		question = O_INV ? cur->answer : cur->question;
		answer = O_INV ? cur->question : cur->answer;
		printf("Question: %s\n", question);
		useranswer = readline("?> ");
		printf("%s is equal to\n%s\n", answer, useranswer);
	} while((cur=cur->next) != NULL);
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
	opterr = 0;
	while((c=getopt(argc, argv, "irhes:f:d1l")) != -1)
		switch(c){
			case 'i':
				O_INV = true;
				break;
			case 'r':
				O_SHF = true;
				break;
			case 's':
				O_SEP = optarg[0];
				break;
			case 'f':
				O_FOR = atoi(optarg);
				break;
			case 'e':
				O_RER = true;
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
		fprintf(stderr, "\n\nSpecify at least one file...\n");
		return 2;
	}
	train(argv + optind, argc - optind);
	return 0;
}
