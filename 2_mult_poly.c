#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 100

typedef struct Node {
	int coef;
	int expo;
	struct Node *link;
} node;

typedef struct headNode {
	struct headNode *nextHead;
	struct Node *link;
} headNode;

headNode* multPoly(headNode *startPoly);
void printPoly(headNode *startPoly);
void printResult(headNode *result);

int main(int argc, char* argv[])
{
	char buffer[MAX];

	// enter polynomial
	printf("? ");
	scanf("%s", buffer);

	// declare start of polynomial and handler
	headNode *startPoly = (headNode*)malloc(sizeof(headNode));
	headNode *newHead = (headNode*)malloc(sizeof(headNode));
	headNode *currentHead = startPoly;
	headNode *lastHead = startPoly;
	headNode *priorityHead = startPoly;

	//read formula
	int i = 0;
	int openedBracket = 0;

	bool open = false;
	bool close = false;

	while(buffer[i] != '\0')
	{
		switch(buffer[i])
		{
			case '(':
			{
				// create headNode
				headNode *newHead = (headNode*)malloc(sizeof(headNode));

				//create node handler
				node *currentNode = NULL;

				i++;
				char temp[10] = {0, };
				int j = 0;

				// read polynomial
				while(buffer[i] != ')')
				{
					// check bracket
					if(buffer[i] == '*' || buffer[i] == '\0')
					{
						printf("[ERROR] Formula is invalid!!! (Please check the bracket.)\n");
						return 1;
					}

					// save term (?˜ë‚˜?????€??
					temp[j++] = buffer[i];

					// save coef value and expo value
					if(buffer[i + 1] == '+' || buffer[i + 1] == '-' || buffer[i + 1] == ')')
					{
						int coef = 0;
						int expo = 0;

						if(strstr(temp, "x^") != NULL)
						{
							// read coef
							char *ptr = strtok(temp, "x");
							if(ptr[0] != '+' && ptr[0] != '-' && isdigit(ptr[0]) == 0)
                                                        {
                                                                printf("[ERROR] Formula is invalid!!! (\"%c\" is not available.) Please check your formular\n", ptr[0]);
                                                                return 1;
                                                        }
							coef = atoi(ptr);

							// read expo
							ptr = strtok(NULL, "^");
							if(ptr[0] != '+' && ptr[0] != '-' && isdigit(ptr[0]) == 0)
                                                        {
                                                                printf("[ERROR] Formula is invalid!!! (\"%c\" is not available.) Please check your formular\n", ptr[0]);
                                                                return 1;
                                                        }
							expo = atoi(ptr);
						}
						// constant term (?ìˆ˜??
						else
						{
							if(temp[0] != '+' && temp[0] != '-' && isdigit(temp[0]) == 0)
							{
								printf("[ERROR] Formula is invalid!!! (\"%c\" is not available.) Please check your formular\n", temp[0]);
								return 1;
							}
							coef = atoi(temp);
							expo = 0;
						}
						//printf("coef: %d, expo: %d\n", coef, expo);
						
						//create new node
						node *new = (node*)malloc(sizeof(node));
						new -> coef = coef;
						new -> expo = expo;
						new -> link = NULL;
						
						// first node
						if(newHead -> link == NULL)
						{
							newHead -> link = new;
							currentNode = new;
						}
						// not first node
						else
						{
							currentNode -> link = new;
							currentNode = new;
						}

						// initialization
                                                memset(temp, '\0', 10);
                                                j = 0;
					}
					i++;
				}

				currentHead = newHead;

				// consider priority
				if(open = true && openedBracket > 0)
				{
					if(openedBracket < 0)
					{
						printf("[ERROR] Formula is invalid!!! (Please check the bracket.)\n");
						return 1;
					}

					if(openedBracket == 1)
					{
						// move currentHead next to priorityHead
						currentHead -> nextHead = priorityHead -> nextHead;
						priorityHead -> nextHead = currentHead;
						priorityHead = currentHead;

						// update lastHead
						if(currentHead -> nextHead == NULL)
                                                                lastHead = currentHead;
					}
					else
					{
						if(priorityHead == startPoly)
						{
							// move currentHead next to startPoly (currentHead == 1st Head)
							currentHead -> nextHead = priorityHead -> nextHead;
							priorityHead -> nextHead = currentHead;
							priorityHead = currentHead;

							// update lastHead
							if(currentHead -> nextHead == NULL)
								lastHead = currentHead;
						}
						else
						{
							if(buffer[i + 1] != '}')
							{
								// find previousHead of priorityHead
								headNode *temp = startPoly;
								while(temp -> nextHead != priorityHead)
									temp = temp -> nextHead;
	
								// move currentHead next to previousHead
								currentHead -> nextHead = temp -> nextHead;
								temp -> nextHead = currentHead;
								priorityHead = currentHead;

								// update lastHead
								if(currentHead -> nextHead == NULL)
                                                                	lastHead = currentHead;
							}
							else
							{
								// move currentHead next to priorityHead
								currentHead -> nextHead = priorityHead -> nextHead;
                                                        	priorityHead -> nextHead = currentHead;
                                                        	priorityHead = currentHead;

								// update lastHead
								if(currentHead -> nextHead == NULL)
                                                                	lastHead = currentHead;
							}
						}
					}

					//openedBracket++;
					open = false;
				}
				else
				{
					lastHead -> nextHead = currentHead;
                                	lastHead = currentHead;
				}

				//printPoly(startPoly);
				break;
			}

			case ')':
				i++;
				break;

			case '{':
				open = true;
				openedBracket++;
				i++;
				break;

			case '}':
			// consider priority
			{
				close = true;
				openedBracket--;
				
				if(openedBracket < 0)
				{
					printf("[ERROR] Formula is invalid!!! (Please check the bracket.)\n");
                			return 1;
				}
				else if(openedBracket > 0 && buffer[i + 1] != '}')
				{
					if(priorityHead != currentHead)
					{
						// find previousHead of currentHead
						headNode *preHead = startPoly;
                                                while(preHead -> nextHead != currentHead)
							preHead = preHead -> nextHead;

						// move currentHead next to priorityHead
						currentHead -> nextHead = priorityHead -> nextHead;
                                                priorityHead -> nextHead = currentHead;
                                                priorityHead = currentHead;
						
						// set previousHead as lastHead
						preHead -> nextHead = NULL;
						lastHead = preHead;
					}
					priorityHead = currentHead;
				}

				//printPoly(startPoly);

				close = false;
				i++;
				break;
			}

			case '*':
				i++;
				break;

			// exception handling
			default:
				printf("[ERROR] Formula is invalid!!! (\"%c\" is not available.) Please check your formular.\n", buffer[i]);
				return 1;
		}
	}

	if(openedBracket > 0 || open == true || close == true)
	{
		printf("[ERROR] Formula is invalid!!! (Please check the bracket.)\n");
                return 1;
	}

	lastHead -> nextHead = NULL;

	// print poly
	printPoly(startPoly);

	// multiply poly
	headNode *result = (headNode*)malloc(sizeof(headNode));
	result = multPoly(startPoly);

	//print result
	if(result != NULL)
		printResult(result);

	free(startPoly);
	free(result);

	return 0;
}

headNode* multPoly(headNode *startPoly)
{
	// multiply poly
	headNode *result = (headNode*)malloc(sizeof(headNode));

        headNode *head1, *head2;
        node *poly1, *poly2;

        head1 = startPoly -> nextHead;
        head2 = head1 -> nextHead;

	// only 1 poly
        if(head2 == NULL)
        {
                printResult(head1);
		return NULL;
        }
        else
        {
                // head2
                while(head2 != NULL)
                {
                        headNode *preResult = (headNode*)malloc(sizeof(headNode));
                        node *currentResult;
                        poly1 = head1 -> link;
                        // poly1
                        while(poly1 != NULL)
                        {
                                // poly2
                                poly2 = head2 -> link;
                                while(poly2 != NULL)
                                {
                                        node *new = (node*)malloc(sizeof(node));
                                        new -> coef = (poly1 -> coef) * (poly2 -> coef);
                                        new -> expo = (poly1 -> expo) + (poly2 -> expo);

                                        if(preResult -> link == NULL)
                                        {
                                                preResult -> link = new;
                                                currentResult = new;
                                        }
                                        else
                                        {
                                                currentResult -> link = new;
                                                currentResult = new;
 					}

                                        poly2 = poly2 -> link;
                                }
                                poly1 = poly1 -> link;
                        }

                        // organize result
                        node *temp1, *temp2, *pre;
                        temp1 = preResult -> link;
                        while(temp1 != NULL)
                        {
                                temp2 = temp1 -> link;
                                pre = temp1;
                                while(temp2 != NULL)
                                {
                                        if((temp1 -> expo) == (temp2 -> expo))
                                        {
                                                temp1 -> coef = (temp1 -> coef) + (temp2 -> coef);
                                                pre -> link = temp2 -> link;
                                        }
                                        else
                                                pre = pre -> link;
                                        temp2 = temp2 -> link;
                                }
                                temp1 = temp1 -> link;
                        }

			// print interim result
                        //printResult(preResult);

			result = preResult;
                        head1 = preResult;
                        head2 = head2 -> nextHead;
		}
	}
	return result;
}

void printPoly(headNode *startPoly)
{
	// show startPoly linked list
	int i = 1;
	headNode *head;
	node *temp;
	head = startPoly -> nextHead;

	while(head != NULL)
	{
		printf("\nPoly %d : ", i);
		temp = head -> link;
		while(temp != NULL)
		{
			if(temp -> coef < 0)
				printf("%dx^%d", temp -> coef, temp -> expo);
			else if(temp -> coef > 0)
				printf("+%dx^%d", temp -> coef, temp -> expo);
			temp = temp -> link;
		}
		head = head -> nextHead;
		i++;
	}
	printf("\n");
}

void printResult(headNode *result)
{
	//print result
	headNode *head;
	node *temp;

	head = result;
	temp = head -> link;
	printf("\nResult\n");
	while(temp != NULL)
	{
		if(temp -> coef < 0)
			printf("%dx^%d", temp -> coef, temp -> expo);
		else if(temp -> coef > 0)
			printf("+%dx^%d", temp -> coef, temp -> expo);
		temp = temp -> link;
	}
	printf("\n");

