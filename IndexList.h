#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERR	1
#define SUCCESS 0
#define WORD_LEN 100

/* Link list node */
struct Node
{
	char *linuenum;//list of lines that has given word
	char *word;//word in index
	struct Node* next;//pointer to next Node
};