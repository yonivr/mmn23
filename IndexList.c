#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IndexList.h"


/* New node in index List*/
struct Node *newNode(char *linenum, char *word)
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
function expects a pointer to head as this can modify the
head of the input linked list (similar to push())*/
void sortedInsert(struct Node** head, struct Node* new_node)
{
	struct Node* current;
	/* Special case for the head end */
	if (*head == NULL || (strcmp((*head)->word, new_node->word) >= 0))//case new_node is before head put new_node as head
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		/* Locate the node before the point of insertion */
		current = *head;
		while (current->next != NULL &&
			(strcmp(current->next->word, new_node->word) < 0))//check if new_node is after word after current
		{
			current = current->next;
		}//insert new_node
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
//check if line number exists in line
int checklinenum(char *line, char *num)
{
	//create line number in same format
	for (char *p = strtok(line, ","); p != NULL; p = strtok(NULL, ","))//iterate line until num is found
	{
		if (strstr(p, num))
		{
			return 0;
		}
	}
		return -1;
}
//finds a node with given word and updates unique line number
void updateNode(struct Node *head, char *linenum, char *word)
{
	struct Node *temp = head;//temp node to iterate list
	char *newlinenum[WORD_LEN];
	while (temp != NULL)//iterate until end of list
	{
		if (strcmp(temp->word, word))//check if word is in the list
		{
			if (checklinenum(temp->linuenum, linenum) == 0)//line number is not in line num list add it
			{
				strcat(newlinenum, temp->linuenum);
				strcat(newlinenum, ",");
				strcat(newlinenum, linenum);
				temp->linuenum = strdup(newlinenum);
			}
		}
		temp = temp->next;//go to the next node 
	}
}
/*
input:
head - start of list
linenum - number of line
word - word in text
purpose:
In case word exists in list starting with head update the linenum or insert word to list if it doesnt exit
*/
void addNode(struct Node *head,char *linenum, char *word)
{
	struct Node *temp = NULL;
	if (findNode(head, word))//check if word is in list
		updateNode(head, linenum, word);//update line number in list
	else
	{//case word doesnt exist add node in proper location
		temp = newNode(linenum, word);
		sortedInsert(head, temp);
	}
}