#ifndef QUESTION_FILE
#define QUESTION_FILE

struct question {
	char *question;
	char *answer;
	unsigned int errors;
	struct question *next;
};

struct question *make_struct(char *line, char split);
struct question *randomize_list(struct question *root);

#endif
