#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IndexList.h"


/* New node in index List*/
struct Node *newNode(char *linenum,char *word)
{
	/* allocate node */
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	/* put in the data  */
	new_node->linuenum = strdup(linenum);
	new_node->word = strdup(word);
	new_node->next = NULL;

	return new_node;
}
/* Function to print linked list */
void printList(struct Node *head)
{
	struct Node *temp = head;//temp node to iterate list
	while (temp != NULL)//iterate until end of list
	{
		printf("%s appears in lines %s\n", temp->word,temp->linuenum);
		temp = temp->next;
	}
}
/* function to insert a new_node in a list. Note that this
function expects a pointer to head_ref as this can modify the
head of the input linked list (similar to push())*/
void sortedInsert(struct Node** head_ref, struct Node* new_node)
{
	struct Node* current;
	/* Special case for the head end */
	if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
	{
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	else
	{
		/* Locate the node before the point of insertion */
		current = *head_ref;
		while (current->next != NULL &&
			current->next->data < new_node->data)
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}
//checks if node with the word string found in list
struct Node *findNode(struct Node *head,char *word)
{
	struct Node *temp = head;//temp node to iterate list
	while (temp != NULL)//iterate until end of list
	{
		if (strcmp(temp->word, word))
			return temp;//return found node
		temp = temp->next;
	}
	return NULL;//return null if nothing found
}
int checklinenum(char *line, char *num)
{
	char linenum[WORD_LEN];
	linenum[0] = '\0';
	strcat(linenum, " ");
	strcat(linenum, num);
	strcat(linenum, " ");
	if (strstr(line, linenum) != NULL)
		return 0;
	else
		return -1;
}
//finds a node with given word and updates unique line number
void updateNode(struct Node *head, char *linenum, char *word)
{
	struct Node *temp = head;//temp node to iterate list
	char *newlinenum[WORD_LEN];
	while (temp != NULL)//iterate until end of list
	{
		if (strcmp(temp->word, word))
		{
			if (checklinenum(temp->linuenum, linenum) == 0)
			{
				strcat(newlinenum, temp->linuenum);
				strcat(newlinenum, ",");
				strcat(newlinenum, linenum);
				temp->linuenum = strdup(newlinenum);
			}
		}
			
		temp = temp->next;
	}
}

void addNode(struct Node *head,char *linenum, char *word)
{
	struct Node *temp = NULL;
	if (findNode(head, word))
		updateNode(head, linenum, word);
	else
	{
		temp = newNode(linenum, word);
		sortedInsert(head, temp);
	}
}