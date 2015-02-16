#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "question.h"

#define BUFFERLENGTH 4048

/**
 * randomize_list(root) - Randomizes a question list, note that this reuses the
 * nodes and therefore the original list will be changed.
 *
 * root   - Root node of the question list
 * returns - A root node to the new randomized list
 */
struct question *q_randomize_list(struct question *root)
{
	if(root==NULL)
		return root;
	srand(time(NULL));

	struct question *newroot = root;
	struct question *current_node = root->next;
	struct question *current_head;
	struct question *next_node;

	int numitems = 1;
	int index;

	newroot->next = NULL;
	while(current_node != NULL){
		next_node = current_node->next;
		index = rand() % ++numitems;
		if(index == 0){
			current_node->next = newroot;
			newroot = current_node;
		} else {
			current_head = newroot;
			int currentindex = 0;
		 	while(++currentindex != index)
				current_head = current_head->next;
			current_node->next = current_head->next;
			current_head->next = current_node;
		}
		current_node = next_node;
	}
	return newroot;
}

/**
 * q_make_struct(line, split) - Create a struct from a line
 *
 * line    - The line data
 * split   - The split character
 * returns - A struct containing the data
 */
struct question *q_make_struct(char *line, char split)
{
	struct question *current;
	current = (struct question*)malloc(sizeof(struct question));
	int ql = 0;
	for(; ql<strlen(line) && line[ql] != split; ql++);
	char *que = (char *)malloc(ql+1);
	memcpy(que, line, ql);
	que[ql] = '\0';

	ql = strlen(line)-ql-1;
	char *ans = (char *)malloc(ql);
	memcpy(ans, line+ql, ql);
	ans[ql] = '\0';

	current->question = que;
	current->answer = ans;
	current->errors = 0;
	current->next = NULL;
	return current;
}

/**
 * q_questions_from_files(files, numfiles) - Read questions from files
 *
 * files    - List of filpaths
 * numfiles - Number of files in the list
 * returns  - List of questions
 */
struct question *q_questions_from_files(char **files, int numfiles, char sep)
{
	struct question *head = NULL;
	struct question *tail = NULL;
	char buf[BUFFERLENGTH];
	FILE* currentfile;
	for(int i = 0; i < numfiles; i++){
		currentfile = fopen(files[i], "r");
		if(currentfile == NULL){
			fprintf(stderr, "Skipping %s...\n", files[i]);
			continue;
		}
		while(fgets(buf, sizeof(buf), currentfile)){
			struct question *q = q_make_struct(buf, sep);
			if(tail == NULL && head == NULL){
				tail = q;
				head = q;
			} else {
				tail->next = q;
				tail = q;
			}
		}
		fclose(currentfile);
	}
	return head;
}
