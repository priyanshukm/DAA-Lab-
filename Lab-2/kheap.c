# include <stdio.h>
# include <stdlib.h>

int check_MAX_heap(int *,int,int);
void build_MAX_heap(int *,int, int);
int extract_MAX(int *,int, int);
void insert(int *,int,int,int);
void change(int *,int,int,int,int);

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void restoreDown(int arr[], int len, int index, int k)
{
	int child[k+1],i;

	while (1)
	{
		for (i=1; i<=k; i++)
			child[i] = ((k*index + i) < len) ? (k*index + i) : -1;

		int max_child = -1, max_child_index ;

		for (i=1; i<=k; i++)
		{
			if (child[i] != -1 && arr[child[i]] > max_child)
			{
				max_child_index = child[i];
				max_child = arr[child[i]];
			}
		}

		if (max_child == -1)
			break;

		if (arr[index] < arr[max_child_index])
			swap(&arr[index], &arr[max_child_index]);

		index = max_child_index;
	}
}

void restoreUp(int arr[], int index, int k)
{
	int parent = (index-1)/k;

	while (parent>=0)
	{
		if (arr[index] > arr[parent])
		{
			swap(&arr[index], &arr[parent]);
			index = parent;
			parent = (index -1)/k;
		}

		else
			break;
	}
}

void print(int arr[],int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("\n");
}

int main()
{
	char ch=' ';
  	int *arr,n,k,i,new;
  	scanf("%d",&k);
  	scanf("%d",&n);
  	arr = (int *)malloc(2*n*sizeof(int));
  	for(i=0;i<n;i++)
    	{
      		scanf("%d",&arr[i]);
    	}
  	if(!check_MAX_heap(arr,n,k))
    		build_MAX_heap(arr,n,k);
	printf("Heap : \n");
	print(arr,n);
  	do
    	{
      		while(getchar()!='\n');
      		ch=getchar();
      		switch(ch)
		{
			case 'i':
	  			scanf("%d",&new);
	  			insert(arr,n,k,new);
	  			n++;
				printf("Heap : \n");
				print(arr,n);
	  			break;
			case 'd':
	  			printf("Max element : %d\n",extract_MAX(arr,n,k));
	  			n--;
				printf("Heap : \n");
				print(arr,n);
	  			break;
			case 'c':
	  			scanf("%d",&i);
	  			scanf("%d",&new);
	  			change(arr,n,k,i,new);
				printf("Heap : \n");
				print(arr,n);
	  			break;
			
		}
    	}while(ch!='q');
  	return 0;
}

int check_MAX_heap(int arr[],int n,int k)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=k*i+1;j<=k*i+k && (j<n);j++)
		{
			if(arr[j] > arr[i])
				return 0;
		}
	}
	return 1;
}

void build_MAX_heap(int arr[],int n,int k)
{
	int i;
	for (i= (n-1)/k; i>=0; i--)
		restoreDown(arr, n, i, k);
}

void insert(int arr[], int n, int k, int new)
{
	arr[n] = new;
	restoreUp(arr, n, k);
}

int extract_MAX(int arr[],int n,int k)
{
	int max = arr[0];

	arr[0] = arr[n-1];
	restoreDown(arr, n-1, 0, k);

	return max;
}

void change(int arr[],int n,int k,int i,int new)
{
	arr[i] = new;
	restoreDown(arr, n, i, k);
	restoreUp(arr, i, k);
}

