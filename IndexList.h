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

struct Node *newNode(char *linenum, char *word);
void printList(struct Node *head);
struct Node *findNode(struct Node *head, char *word);
void sortedInsert(struct Node** head, struct Node* new_node);//check why head is **
void updateNode(struct Node *head, char *linenum, char *word);
void addNode(struct Node *head, char *linenum, char *word);
int checklinenum(char *line, char *num);