#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct node{
	char *key;
	struct node *left;
	struct node *right;
} node;

void clearBuffer(void);
node* insertNode(node *head, char *string);
node* searchNode(node *head, char *string);
node* searchParentNode(node *head, char *string);
node* searchMaxNode(node *head);
node* searchMinNode(node *head);
node* deleteNode(node *head, char *string);
void inOrderPrintTree(node* head, int level);
void printTree(node* head, int level);

node *tree_head = NULL;

int main(int argc, char* argv[])
{
	while(1)
	{
		char *menu = malloc(sizeof(char) * MAX);
		char *string = malloc(sizeof(char) * MAX);

		printf("\n> ");
		scanf("%s", &menu[0]);
		if(strcmp(menu, "QUIT") == 0)
		{
			free(menu);	free(string);
			printf("exit program...\n");
			return 0;
		}
		else
		{
			scanf("%s", &string[0]);
			if(strcmp(menu, "INSERT") == 0)
			{
				node *temp = insertNode(tree_head, string);
				if(temp == NULL)
					printf("[ERROR] %s is already exist!\n", string);
				else
					tree_head = temp;
			}
			else if(strcmp(menu, "SEARCH") == 0)
			{
				node *temp = searchNode(tree_head, string);
				if(temp == NULL)
					printf("%s does NOT EXIST!\n", string);
				else
					printf("%s EXISTS!\n", string);
			}
			else if(strcmp(menu, "DELETE") == 0)
			{
				if(tree_head == NULL)
					printf("Tree is NULL! \n");
				else
				{
					if(strcmp(tree_head -> key, string) == 0)
					{
						if(tree_head -> left == NULL && tree_head -> right == NULL)
							tree_head = NULL;
						else
							deleteNode(tree_head, string);
					}
					else
					{
						node *temp = deleteNode(tree_head, string);
					}
				}
			}
			else
				printf("POSSIBLE MENU -> INSERT [KEY] | SEARCH [KEY] | DELETE [KEY] | QUIT\n");
		}
		clearBuffer();
		
		printf("============= CURRENT TREE =============\n");
		if(tree_head != NULL)
			inOrderPrintTree(tree_head, 0);
	}

	return 0;
}

void clearBuffer(void) 
{
	while(getchar() != '\n');
}

node* insertNode(node *head, char *string)
{
	node *temp = head;
	node *parent = NULL;
	
	while(temp != NULL) 
	{
		if(strcmp(string, temp -> key) == 0) return NULL;

		parent = temp;
		if(strcmp(string, temp -> key) < 0)
			temp = temp -> left;
		else
			temp = temp -> right;
	}

	node *new = (node*)malloc(sizeof(node));
	new -> key = string;
	new -> left = NULL;
	new -> right = NULL;

	if(head == NULL)
		head = new;
	else if(strcmp(string, parent -> key) < 0)
		parent -> left = new;
	else
		parent -> right = new;

	return head;
}

node* searchNode(node *head, char *string)
{
	node *temp = head;

	if(temp == NULL)
		return NULL;
	if(strcmp(string, temp -> key) == 0)
		return temp;
	if(strcmp(string, temp -> key) < 0)
		return searchNode(temp -> left, string);
	else
		return searchNode(temp -> right, string);
}

node* searchParentNode(node *head, char *string)
{
	node *temp = head;

	if(temp == NULL)
		return NULL;
	if(temp -> left != NULL)
	{
		if(strcmp(string, temp -> left -> key) == 0)
			return temp;
	}
	if(temp -> right != NULL)
	{
		if(strcmp(string, temp -> right -> key) == 0)
			return temp;
	}
	if(strcmp(string, temp -> key) < 0)
		return searchParentNode(temp -> left, string);
	else
		return searchParentNode(temp -> right, string);
}

node* searchMaxNode(node *head)
{
	node *temp = head;

	if(temp == NULL)
		return NULL;

	if(temp -> right != NULL)
		searchMaxNode(temp -> right);
	else
		return temp;
}

node* searchMinNode(node *head)
{
	node *temp = head;

	if(temp == NULL)
		return NULL;

	if(temp -> left != NULL)
		searchMinNode(temp -> left);
	else
		return temp;
}

node* deleteNode(node *head, char *string)
{
	node *temp = searchNode(head, string);
	if(temp == NULL)
		return NULL;

	node *parent = searchParentNode(tree_head, string);
	
	if(temp -> left == NULL && temp -> right == NULL)
	{
		if(parent != NULL)
		{
			if(parent -> left == temp)
				parent -> left = NULL;
			else
				parent -> right = NULL;
		}
	}
	else if(temp -> left == NULL || temp -> right == NULL)
	{
		if(temp -> left != NULL)
		{
			if(parent != NULL)
			{
				if(parent -> left == temp)
					parent -> left = temp -> left;
				else
					parent -> right = temp -> left;
			}
		}
		else
		{
			if(parent != NULL)
			{
				if(parent -> left == temp)
					parent -> left = temp -> right;
				else
					parent -> right = temp -> right;
			}
		}
	}
	else if(temp -> left != NULL && temp -> right != NULL)
	{
		node *q;
		if(temp -> left == NULL)
		{
			q = searchMinNode(temp -> right);
			deleteNode(temp -> right, q -> key);
			temp -> key = q -> key;
		}
		else
		{
			q = searchMaxNode(temp -> left);
			deleteNode(temp -> left, q -> key);
			temp -> key = q -> key;
		}
	}

}

void inOrderPrintTree(node* head, int level)
{
    if(head == NULL)
        return;

    inOrderPrintTree(head -> right, level + 1);

    printTree(head, level);

    inOrderPrintTree(head -> left, level + 1);
}

void printTree(node* head, int level)
{
	for(int i = 0; i < level;i++)
		printf("___");
	printf("|%s", head -> key);

	// for debugging
	/*if(head -> left != NULL)
		printf("left: %s", head -> left -> key);
	if(head -> right != NULL)
		printf(" right: %s", head -> right -> key);
	*/

	printf("\n");
}
