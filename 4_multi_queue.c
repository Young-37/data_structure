#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 30

typedef struct node {
	char data[MAX];
	struct node *link;
} node;

void printQueue(int n, node *head_ptr, node *barrier[]);
int checkOverflow(int s, int n, int *sub_size, int *deQ_num);
int checkUnderflow(int queue_num, int *sub_size, int *deQ_num);
node* enQueue(int n, int queue_num, int *sub_size, node *head_ptr, node *barrier[], node *head_queue[], node *tail_queue[]);
node* deQueue(int n, int queue_num, node *head_ptr, node *barrier[], node *head_queue[], node *tail_queue[]);

int main(int argc, char* argv[])
{
	// exception handling
	if(argc != 3)
	{
		printf("[ERROR] usage: %s n(num of sub-queue) s(maximum size of queue)\n", argv[0]);
		return 1;
	}

	int n = atoi(argv[1]);
	int s = atoi(argv[2]);

	// exception handling
	if(n < 0 || s < 0)
	{
		printf("[ERROR] n and s must be over than 0 (not %d, %d)\n", n, s);
		return 1;
	}

	srand(time(NULL));

	node *head_ptr = NULL;
	node *barrier[n], *head_queue[n], *tail_queue[n];
	for(int i = 0; i < n; i++)
	{
		barrier[i] = NULL; head_queue[i] = NULL; tail_queue[i] = NULL;
	}

	int *sub_size = (int*)malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++)
		sub_size[i] = 0;

	int *deQ_num = (int*)malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++)
		deQ_num[i] = 0;

	for(int i = 0; i < s * 3; i++)
	{
		int queue_num = rand() % n + 1;
		int menu = rand() % 2 + 1;

		printf("\n*** sub queue: %d, menu: %d (1 = enQueue, 2 = deQueue) ***\n", queue_num, menu);
		if(menu == 1)
		{
			// check overflow
			int of = checkOverflow(s, n, sub_size, deQ_num);

			if(of == 1)
				printf("[Overflow error]\n");
			else
			{
				//enQueue
				sub_size[queue_num - 1] += 1;
				head_ptr = enQueue(n, queue_num, sub_size, head_ptr, barrier, head_queue, tail_queue);
				printQueue(n, head_ptr, barrier);
			}
		}
		else if(menu ==2)
		{
			deQ_num[queue_num - 1] += 1;
			// check underflow
			int uf = checkUnderflow(queue_num, sub_size, deQ_num);
			
			if(uf == 1)
			{
				deQ_num[queue_num - 1] -= 1;
				printf("[Underflow error]\n");
			}
			else
			{
				// deQueue
				head_ptr = deQueue(n, queue_num, head_ptr, barrier, head_queue, tail_queue);
				printQueue(n, head_ptr, barrier);
			}
		}
	}

	return 0;
}

void printQueue(int n, node *head_ptr, node *barrier[])
{
	node *temp;
	printf("\n============================ Current Queue ============================\n");
	if(head_ptr != NULL)
	{
		int sub_queue_num, size;
		temp = head_ptr;

		while(temp != NULL)
		{
			sscanf(temp -> data, "queue%d_%d", &sub_queue_num, &size);
			
			for(int i = 0; i < n; i++)
			{
				if(temp == barrier[i] && i < (sub_queue_num - 1))
					printf(" | ");
			}

			if(temp -> link != NULL)
				printf("%s -> ", temp -> data);
			else
				printf("%s ", temp -> data);

			for(int i = 0; i < n; i++)
			{
				if(temp == barrier[i] && i >= (sub_queue_num - 1))
					printf(" | ");
			}
			temp = temp -> link;
		}
	}
	printf("\n\n");

	return;
}

int checkOverflow(int s, int n, int *sub_size, int *deQ_num)
{
	int sum = 0;

	for(int i = 0; i < n; i++)
		sum += (sub_size[i] - deQ_num[i]);

	if(sum >= s)
		// overflow
		return 1;
	else
		return 0;
}

int checkUnderflow(int queue_num, int *sub_size, int *deQ_num)
{
	// underflow
	if(sub_size[queue_num - 1] - deQ_num[queue_num - 1] < 0)
		return 1;
	else
		return 0;
}

node* enQueue(int n, int queue_num, int *sub_size, node *head_ptr, node *barrier[], node *head_queue[], node *tail_queue[])
{
	node *new = (node*)malloc(sizeof(node));

	// create data
	char data[MAX];
	sprintf(data, "queue%d_%d", queue_num, sub_size[queue_num - 1]);
	strcpy(new -> data, data);
	printf("enQueue node: %s\n", new -> data);

	// if sub_queue is NULL
	if(tail_queue[queue_num - 1] == NULL)
	{
		head_queue[queue_num - 1] = new;

		// if queue is NULL
		if(head_ptr == NULL)
		{
			for(int i = 0; i < queue_num - 1; i++)
				barrier[i] = new;

			new -> link = NULL;
		}
		// if only sub_queue is NULL
		else
		{
			// check head_ptr location
			for(int i = 0; i < n; i++)
			{
				if(head_ptr == head_queue[i])
				{
					// head_ptr is trailing
					if(i > queue_num - 1)
					{
						// insert new node before head_ptr
						new -> link = head_ptr;

						// update barrier
						for(int j = 0; j < queue_num - 1; j++)
						{
							if(barrier[j] == head_ptr && tail_queue[j] == NULL)
								barrier[j] = new;
						}
					}

					// head_ptr is preceding
					else
					{
						// insert new node next to previous sub queue's last(tail) node
						node *temp;
						for(int i = queue_num - 2; i >= 0; i--)
						{
							if(tail_queue[i] != NULL)
							{
								temp = tail_queue[i];
								break;
							}
						}
						new -> link = temp -> link;
						temp -> link = new;
					}
					break;
				}
			}
		}
	}
	else
	{
		// connect new node next to tail node
		node *temp = tail_queue[queue_num - 1];
		new -> link = temp -> link;
		temp -> link = new;
	}


	// move barrier (queue_num ~ last)
	for(int i = queue_num; i < n; i++)
	{
		if(barrier[i] == NULL || (barrier[i] == barrier[queue_num - 1] && tail_queue[i] == NULL))
			barrier[i] = new;
		else
			break;
	}

	// move tail and barrier
	tail_queue[queue_num - 1] = new;
	barrier[queue_num - 1] = new;

	// update head_ptr
	for(int i = 0; i < n; i++)
	{
		if(head_queue[i] != NULL)
		{
			head_ptr = head_queue[i];
			break;
		}
	}

	// for debuging
	//for(int i = 0; i < n; i++) 
	//	printf("%d: head: %s, barrier: %s, tail: %s\n", i + 1, head_queue[i] -> data, barrier[i] -> data, tail_queue[i] -> data);

	return head_ptr;
}

node* deQueue(int n, int queue_num, node *head_ptr, node *barrier[], node *head_queue[], node *tail_queue[])
{
	printf("deQueue node: %s\n", head_queue[queue_num - 1] -> data);
	
	if(head_ptr == head_queue[queue_num - 1])
	{
		// only one node
		if((head_queue[queue_num - 1] == tail_queue[queue_num - 1]) && head_queue[queue_num - 1] -> link == NULL)
		{
			head_ptr = NULL;
			head_queue[queue_num - 1] = NULL;
			tail_queue[queue_num - 1] = NULL;
			for(int i = 0; i < n; i++)
				barrier[i] = NULL;
		}
		else
		{		
			// delete node
			head_ptr = head_queue[queue_num - 1] -> link;

			// last node of sub_queue
			if(head_queue[queue_num - 1] == tail_queue[queue_num - 1])
			{
				head_queue[queue_num - 1] = NULL;
				tail_queue[queue_num - 1] = NULL;

				// move barrier
				node *temp;
				for(int i = n - 1; i >= 0; i--)
				{
					if(i == queue_num - 1)
						continue;
					else if(barrier[i] != barrier[queue_num - 1])
						temp = head_queue[i];
					else if(barrier[i] == barrier[queue_num - 1])
						barrier[i] = temp;
				}
				barrier[queue_num - 1] = temp;
			}
			else
				head_queue[queue_num - 1] = head_queue[queue_num - 1] -> link;
		}
	}
	else
	{
		// find delete node's previous node
		node *temp = head_ptr;
		while(temp -> link != head_queue[queue_num - 1])
			temp = temp -> link;

		// delete node
		temp -> link = head_queue[queue_num - 1] -> link;

		// last node of sub_queue
		if(head_queue[queue_num - 1] == tail_queue[queue_num - 1])
		{
			// set head, tail as NULL
			head_queue[queue_num - 1] = NULL; 
			tail_queue[queue_num - 1] = NULL;

			// move barrier
			node *temp;
			for(int i = 0; i < n; i++)
			{
				if(i == queue_num - 1)
					continue;
				else if(barrier[i] != barrier[queue_num - 1])
					temp = barrier[i];
				else if(barrier[i] == barrier[queue_num - 1])
					barrier[i] = temp;
			}
			barrier[queue_num - 1] = temp;
		}
		else
			// update head
			head_queue[queue_num - 1] = head_queue[queue_num - 1] -> link;
	}

	// for debuging
	//for(int i = 0; i < n; i++)
        //        printf("%d: head: %s, barrier: %s, tail: %s\n", i + 1, head_queue[i] -> data, barrier[i] -> data, tail_queue[i] -> data);

	return head_ptr;
}

