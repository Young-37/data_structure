#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	struct node *left;
	int win;
	int lose;
	struct node *right;
} node;

typedef struct num_node {
	struct num_node *left;
	int num;
	struct num_node *right;
} num_node;

void print_node(node *head, num_node *num_head, node *computer_ptr, int num, int delete_num);
node* create_initial_node(int num, num_node **num_head);
node* user_win(node **head, num_node **num_head, node *computer_ptr, num_node **num_computer_ptr, int *num);
node* user_lose(node **head, num_node **num_head, node *computer_ptr, num_node **num_computer_ptr, int *delete_num);

int main(int argc, char* argv[])
{
	// exception handling
	if(argc != 2)
	{
		printf("[ERROR] usage: %s num_of_nodes\n", argv[0]);
		return 1;
	}

	int num = atoi(argv[1]);
	int delete_num = 0;
	
	if(num <= 0)
	{
		printf("Please enter a number greater than 1 (not %d)\n", num);
		return 0;
	}

	srand(time(NULL));

	node *head = NULL;
	node *computer_ptr = NULL;
	num_node *num_head = NULL;
	num_node *num_computer_ptr = NULL;

	// create initial node
	head = create_initial_node(num, &num_head);
	computer_ptr = head;
	num_computer_ptr = num_head;
	printf("초기 ?�드가 ?�성?�었?�니??n");
	print_node(head, num_head, computer_ptr, num, delete_num);

	// start game
	while(1)
	{
		int user = 0;
		int computer = 0;

		printf("\n?�택?�세??(1. 가?? 2. 바위, 3. �? 4. ?�내�? ? ");
		scanf("%d", &user);

		computer = (rand() % 3) + 1;

		printf("user: %d computer: %d\n", user, computer);

		switch(user)
		{
			case 1:
				if(computer == 1)
				{
					printf("?�용?��? 컴퓨?��? 비겼?�니??\n");
				}
				else if(computer == 2)
				{
					computer_ptr = user_lose(&head, &num_head, computer_ptr, &num_computer_ptr, &delete_num);
					print_node(head, num_head, computer_ptr, num, delete_num);
				}
				else if(computer == 3)
				{
					computer_ptr = user_win(&head, &num_head, computer_ptr, &num_computer_ptr, &num);
					print_node(head, num_head, computer_ptr, num, delete_num);
				}

				break;

			case 2:
				if(computer == 1)
                                {
					computer_ptr = user_win(&head, &num_head, computer_ptr, &num_computer_ptr, &num);
					print_node(head, num_head, computer_ptr, num, delete_num);
                                }
                                else if(computer == 2)
                                {
					printf("?�용?��? 컴퓨?��? 비겼?�니??\n");
                                }
                                else if(computer == 3)
                                {
					computer_ptr = user_lose(&head, &num_head, computer_ptr, &num_computer_ptr, &delete_num);
					print_node(head, num_head, computer_ptr, num, delete_num);
                                }

				break;
			case 3:
				if(computer == 1)
                                {
					computer_ptr = user_lose(&head, &num_head, computer_ptr, &num_computer_ptr, &delete_num);
					print_node(head, num_head, computer_ptr, num, delete_num);
                                }
                                else if(computer == 2)
                                {
					computer_ptr = user_win(&head, &num_head, computer_ptr, &num_computer_ptr, &num);
					print_node(head, num_head, computer_ptr, num, delete_num);
                                }
                                else if(computer == 3)
                                {
					printf("?�용?��? 컴퓨?��? 비겼?�니??\n");
                                }

				break;
			case 4:
				printf("게임??종료?�니??..\n");
				return 0;
			default:
				printf("1부??4까�????�자�??�력?�주?�요!!!\n");
				break;
		}
		if(computer_ptr == NULL)
		{
			printf("?�드??개수가 0???�어 ?�신??졌습?�다.\n게임??종료?�니??..\n");
			break;
		}
	}

	return 0;
}

void print_node(node *head, num_node *num_head, node* computer_ptr, int num, int delete_num)
{
	if(computer_ptr == NULL)
		return;

	node *temp;
	num_node *num_temp;
	temp = head;
	num_temp = num_head;

	printf("�?node 개수: %d\n", num - delete_num);

	printf("<-> ");
	do {
		// if current node
		if(temp == computer_ptr)
			printf("node%d*: win=%d, lose=%d <-> ", num_temp -> num, temp -> win, temp -> lose);
		else
			printf("node%d: win=%d, lose=%d <-> ", num_temp -> num, temp -> win, temp -> lose);
		
		// move temp
		temp = temp -> right;
		num_temp = num_temp -> right;
	}while(temp != head);
	printf("\n");
}

node* create_initial_node(int num, num_node **num_head)
{
	node *head = NULL;
	node *temp = NULL;
	num_node *num_temp = NULL;

        for(int i = 0; i < num; i++)
        {
                node *new = (node*)malloc(sizeof(node));
                new -> win = 0;
                new -> lose = 0;

		num_node *num_new = (num_node*)malloc(sizeof(num_node));
		num_new -> num = i;

                if(head == NULL)
                {
                        new -> left = new;
                        new -> right = new;

			num_new -> left = num_new;
			num_new -> right = num_new;

			// set head pointer
                        head = new;
			*num_head = num_new;

			// move temp
                        temp = new;
			num_temp = num_new;
                }
                else
                {
			// connect node
                        temp -> right = new;
                        new -> left = temp;
                        new -> right = head;
                        head -> left = new;

			// connect num node
			num_temp -> right = num_new;
			num_new -> left = num_temp;
			num_new -> right = *num_head;
			(*num_head) -> left = num_new;

			// move temp
                        temp = new;
			num_temp = num_new;
                }
        }

	return head;
}

node* user_win(node **head, num_node **num_head, node *computer_ptr, num_node **num_computer_ptr, int *num)
{
	printf("\n컴퓨?��? 졌습?�다. ?�른�??�드�??�동?�겠?�니??\n");
	
	// add win point
	computer_ptr -> win += 1;

	if(computer_ptr -> win >= 2)
	{
		// set win point as 0
		computer_ptr -> win = 0;

		node *new1 = (node*)malloc(sizeof(node));
		node *new2 = (node*)malloc(sizeof(node));

		num_node *num_new1 = (num_node*)malloc(sizeof(num_node));
		num_node *num_new2 = (num_node*)malloc(sizeof(num_node));

		new1 -> win = 0; new1 -> lose = 0;
		new2 -> win = 0; new2 -> lose = 0;
		num_new1 -> num = *num; num_new2 -> num = *num + 1;

		// insert left node
		new1 -> left = computer_ptr -> left;
		new1 -> right = computer_ptr;
		computer_ptr -> left -> right = new1;
		computer_ptr -> left = new1;

		// insert left num node
		num_new1 -> left = (*num_computer_ptr) -> left;
		num_new1 -> right = *num_computer_ptr;
		(*num_computer_ptr) -> left -> right = num_new1;
		(*num_computer_ptr) -> left = num_new1;

		// insert rigth node
		new2 -> right = computer_ptr -> right;
		new2 -> left = computer_ptr;
		computer_ptr -> right -> left = new2;
		computer_ptr -> right = new2;

		// insert rigth num node
		num_new2 -> right = (*num_computer_ptr) -> right;
		num_new2 -> left = *num_computer_ptr;
		(*num_computer_ptr) -> right -> left = num_new2;
		(*num_computer_ptr) -> right = num_new2;

		// move head node
		if(computer_ptr == *head)
			*head = new1;
		if(*num_computer_ptr == *num_head)
			*num_head = num_new1;

		*num += 2;
	}

	// move current pointer
	computer_ptr = computer_ptr -> right;
	*num_computer_ptr = (*num_computer_ptr) -> right;

	return computer_ptr;
}

node* user_lose(node **head, num_node **num_head, node *computer_ptr, num_node **num_computer_ptr, int *delete_num)
{
	printf("\n컴퓨?��? ?�겼?�니?? ?�쪽 ?�드�??�동?�겠?�니??\n");

	// add lose point
	computer_ptr -> lose += 1;
	
	if(computer_ptr -> lose >= 2)
	{
		if(computer_ptr == *head)
		{
			// end game
			if(computer_ptr -> left == computer_ptr)
				return NULL;
			else
			{
				// change head
				*head = computer_ptr -> right;
				*num_head = (*num_computer_ptr) -> right;
			}
		}

		// delete node
		computer_ptr -> left -> right = computer_ptr -> right;
		computer_ptr -> right -> left = computer_ptr -> left;

		(*num_computer_ptr) -> left -> right = (*num_computer_ptr) -> right;
		(*num_computer_ptr) -> right -> left = (*num_computer_ptr) -> left;

		*delete_num += 1;
	}

�n#^�����
