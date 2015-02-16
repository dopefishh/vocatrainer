#ifndef QUESTION_FILE
#define QUESTION_FILE

/**
 * struct question - Structure for holding questions
 *
 * question - Question string
 * answer   - Answer string
 * errors   - Number of errors made
 * next     - Pointer to the next question, when tail this is NULL
 */
struct question {
	char *question;
	char *answer;
	unsigned int errors;
	struct question *next;
};

int q_difference(char *answer1, char *answer2);
struct question *q_randomize_list(struct question *root);
struct question *q_make_struct(char *line, char split);
struct question *q_questions_from_files(char **files, int nf, char separator);

#endif
