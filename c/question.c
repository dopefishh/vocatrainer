#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct question {
	char *question;
	char *answer;
	unsigned int errors;
	struct question *next;
};

struct question *randomize_list(struct question *root)
{
	/* If the list is length 0 return the list */
	if(root==NULL)
		return root;
	srand(time(NULL));

	/* Initialize the newroot as the original root */
	struct question *newroot = root;
	/* The current node will be initialized with the next node in the
	 * original list 
	 */
	struct question *current_node = root->next;
	struct question *current_head;
	struct question *next_node;

	/* Detach the child of the new root for safe insertion later */
	newroot->next = NULL;
	int numitems = 1;
	int index;

	/* While we have nodes left in the original list */
	while(current_node != NULL){
		/* Save the next node for later use */
		next_node = current_node->next;
		/* Generate the index of insertion */
		index = rand() % ++numitems;
		/* When the index is 0 insert in front and reinitialize root
		 * with the current node
		 */
		if(index == 0){
			current_node->next = newroot;
			newroot = current_node;
		/* If we don't insert up front we walk through the list and
		 * when we have encountered the index we assign the
		 * parent->next to current and current->next to the original
		 * parent->next
		 */
		} else {
			current_head = newroot;
			int currentindex = 0;
		 	while(++currentindex != index)
				current_head = current_head->next;
			current_node->next = current_head->next;
			current_head->next = current_node;
		}
		/* Next current node will be the original next node */
		current_node = next_node;
	}
	return newroot;
}

struct question *make_struct(char *line, char split)
{
	struct question *current;
	current = (struct question*)malloc(sizeof(struct question));
	int ql = 0;
	for(; ql<strlen(line) && line[ql] != split; ql++);
	char *que = (char *)malloc(ql+1);
	memcpy(que, line, ql);
	que[ql] = '\0';

	ql = strlen(line)-ql-1;
	char *ans = (char *)malloc(ql+1);
	memcpy(ans, line+ql, ql);
	ans[ql] = '\0';

	current->question = que;
	current->answer = ans;
	current->errors = 0;
	return current;
}
