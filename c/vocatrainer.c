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

struct question *train(struct question *head)
{
	if(head==NULL)
		return head;
	struct question *redo_head = NULL;
	struct question *redo_tail = NULL;
	struct question *cur = head;
	struct question *next = head->next;
	char *question;
	char *answer;
	do {
		next = cur->next;
		question = O_INV ? cur->answer : cur->question;
		answer = O_INV ? cur->question : cur->answer;
		printf("Question: %s\n", question);
		if(q_difference(answer, readline("?> ")) > O_FOR){
			if(redo_head == NULL && redo_tail == NULL){
				redo_head = cur;
				redo_tail = cur;
				redo_tail->next = NULL;
			} else {
				redo_tail->next = cur;
				cur->next = NULL;
				redo_tail = cur;
			}
			printf("Incorrect! It should be %s\n", answer);
		} else {
			printf("Correct!\n");
		}
		cur = next;
	} while(cur != NULL);
	return redo_head;
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
	struct question *q = q_questions_from_files(argv+optind, argc-optind, O_SEP);
	do {
		q = train(O_SHF ? q_randomize_list(q) : q);
	} while(q != NULL && O_RER);
	return 0;
}
