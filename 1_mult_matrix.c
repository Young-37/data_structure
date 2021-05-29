#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	int data;
	struct Node *link;
}node;

node* create_matrix(node *M, int i, int j);
node* matrix_product(node *M, node *N, node *L, int i, int j, int k);
void print_matrix(node *M, int i, int j);

int main(int argc, char* argv[])
{
	// exception handling
	if(argc != 4)
	{
		printf("[ERROR] usage: %s M_number_of_rows M_number_of_columns(N_number_of_rows) N_number_of_columns\n", argv[0]);
		return 0;
	}

	srand(time(NULL));

	// define size
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int c = atoi(argv[3]);

	// declare matrix	
	node *M = (node*)malloc(sizeof(node) * (a * b));
        node *N = (node*)malloc(sizeof(node) * (b * c));
        node *L = (node*)malloc(sizeof(node) * (a * c));
	
	// create matrix
	M = create_matrix(M, a, b);
	N = create_matrix(N, b, c);

	// print matrix (M, N)
	printf("M\n");
	print_matrix(M, a, b);

	printf("\nN\n");
	print_matrix(N, b, c);

	// matrix product
	L = matrix_product(M, N, L, a, b, c);

	// print result
	printf("\nL (M X N)\n");
	print_matrix(L, a, c);

	free(M);
	free(N);
	free(L);

	return 0;
}

node* create_matrix(node *M, int i, int j)
{
	int x = 0;
        node *temp = M;

        for(x = 0; x < i * j; x++)
        {
                temp -> data = (rand() % 10000) + 1;
                temp -> link = M + (x + 1);
                //printf("%d\n", temp -> data);

                temp = temp -> link;
        }

	return M;
}

void print_matrix(node *M, int i, int j)
{
	int x, y;
	node *temp = M;
	
	for(x = 0; x < i; x++)
	{
		for(y = 0; y < j; y++)
		{
			printf("%d(addr: %p) ", temp -> data, &(temp -> data));
			temp = temp -> link;
		}
		printf("\n");
	}

	return;
}

node* matrix_product(node *M, node *N, node *L, int i, int j, int k)
{
	int x, y, z;
	int sum;

	for(x = 0; x < i; x++)
	{
		for(y = 0; y < k; y++)
		{
			sum = 0;
			for(z = 0; z < j; z++)
			{

				sum += ((M + (x * j + z)) -> data) * ((N + (z * k + y)) -> data);
				//printf("M: %d N: %d sum: %d\n", ((M + (x * j + z)) -> data), ((N + (z * k + y)) -> data), sum);
			}
			(L + (x * k + y)) -> data = sum;
		}
	}

	// connect linked list (L)
	node *temp = L;

	for(x = 0; x < i * k; x++)
	{
		temp -> link = L + (x + 1);

                temp = temp -> link;
	}

	return L;
}

