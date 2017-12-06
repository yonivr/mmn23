/**
MMN 23 Yoni rivkin
this program reads a file , find which line has each word in file and document

workflow:
1.read file line by line
2.normalize line by turning all non alpanumeric chars to space and set all char to lowercase
3.sperate each word
4.push word to proper location in file by finding the first word smaller and putting it after it in linked list


**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "IndexList.h"
#define _CRT_SECURE_NO_WARNINGS
#define LINE_LEN 1000


int startLineIndex(int argc, char *argv[]);//V
int getFile(char *s, struct Node* head);//VX
int initIndex(char *s);
char *normalLine(char *s);//V
int readLine(char *s,int lineNum,struct Node** head);

int main(int argc,char *argv[])
{
	startLineIndex(argc, argv);
}
/*
validate input file 
populate index
print index
*/
int startLineIndex(int argc, char *argv[])
{
	int res = 0;/*check if getFile Worked*/
	struct Node* head = NULL;/*init indexList*/

	if (argc == 2)/*case two arguments supplied*/
	{
		res = getFile(argv[1], head) == ERR;/*populate index*/
		if (res == ERR)/*case cant open file*/
			printf("Eror opening file");
		else
			/*	printList(head);*/ printf("");
	}
	else if (argc > 2)/*too many arguments*/
		printf("Too many arguments supplied.\n");
	else/*too few arguments*/
		printf("One argument expected.\n");

	return SUCCESS;
}
/*get file content and ite,rate line by line*/
int getFile(char *s, struct Node* head)
{
	FILE *ptr_file;/*pointer to file*/
	char buf[1000];/*current line*/
	int lineNum = 0;//line index
	
	ptr_file = fopen(s, "r");/*attempt to open the file s*/
	if (!ptr_file)/*In case you can't open file return error*/
		return ERR;
	/*Create an empy index file*/
	if (initIndex(s)==SUCCESS)
	{
		/*iterate the file until end of file line by line*/
		while (fgets(buf, LINE_LEN, ptr_file) != NULL)
		{
			lineNum++;
			readLine(normalLine(buf),lineNum,&head);//index each normalized line
		}
		printf("\n");
	}
	else
	{
		printf("can't initate index\n");
		fclose(ptr_file);/*close file*/
		return ERR;
	}
	
	fclose(ptr_file);/*close file*/
	return SUCCESS;
}
/*create an empty index file*/
int initIndex(char *s)
{
	char indexName[LINE_LEN];//file name to create
	char index[] = ".index";/*index extention name*/
	FILE *fp;
	int i,j=0;
	/*initate index name*/
	for (i = 0; i < (int)strlen(s); i++)
		indexName[i] = s[i];
	for (j=0; j < (int)strlen(index); j++)
	{
		indexName[i] = index[j];
		i++;
	}
	indexName[i] = '\0';
	printf("%s\n", indexName);
	fp = fopen(indexName, "ab+");/*create file with new extention*/
	if (!fp)/*return error in case file coluldnt be created*/
		return ERR;
	fclose(fp);/*close file*/
	return SUCCESS;
}
/*replace non alphanumeric letters to seperators by space*/
char *normalLine(char *s)
{
	static char res[WORD_LEN];// line to return
	memset(res, '\0', sizeof(res));
	strcpy(res, s);//copy current line to temp string
	for (char *p = res; *p; p++)//iterate the string and replace non alphanumeric with space
	{
		if (!isdigit(*p) && !isalpha(*p))
			*p = ' ';
		if (isalpha(*p))
			*p = tolower(*p);
	}
	return res;
}
/*iterate line and add words to index*/
int readLine(char *s,int lineNum,struct Node** head)
{
	const char seperator[2] = " ";
	char *word;
	//char linenumString[5];
	/*seperate line to words*/
//	printf("%s\n", s);
	word = strtok(s, seperator);
	while (word != NULL) {
		/*Add word to index in case doest exist or update line number*/
		printf("%s\n",word);
	//	addNode(&head, _itoa(lineNum,linenumString,10), word);
		word = strtok(NULL, s);
	}
	return SUCCESS;
}

