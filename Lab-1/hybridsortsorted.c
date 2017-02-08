#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


void swap(int* a, int* b)
{
    	int t = *a;
    	*a = *b;
    	*b = t;
}

void insertionSort(int arr[], int low,int high)
{
	int i, key, j;
	for (i = low+1; i <= high; i++)
	{
		key = arr[i];
		j = i-1;

		while (j >= low && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
	}
}
 
int partition (int arr[], int low, int high)
{
    	int pivot = arr[high];    
    	int j,i = (low - 1);  
 
    	for (j = low; j <= high- 1; j++)
    	{
        	if (arr[j] <= pivot)
        	{
            		i++;  
            		swap(&arr[i], &arr[j]);
        	}
    	}
    	swap(&arr[i + 1], &arr[high]);
    	return (i + 1);
}
 
void quickSort(int arr[], int low, int high, int k)
{
    	if (low < high)
    	{
        	int pi = partition(arr, low, high);
 		
		if(pi-low < k)
			insertionSort(arr, low, pi -1);
		else
        		quickSort(arr, low, pi - 1, k);

		if(high-pi < k)        	
			insertionSort(arr, pi + 1, high);
		else
			quickSort(arr, pi + 1, high, k);
		
    	}	
}

void hybridSort(int *arr, int n)
{
	int i,j,b[100005];
	for(i=0;i<n;i++)
	{
		b[i] = rand()%100000;
	}
	
	qsort(b,n,sizeof(int),cmpfunc);
	
	for(i=1;i<=100;i++)
	{
		for(j=0;j<n;j++)
			arr[j] = b[j];

		time_t begin,end;
			
	     	begin = clock();
		quickSort(arr,0,n-1,i);
	     	end = clock();

	     	printf("%d\t%ld\n",i,end-begin);
  	}
}

int main()
{
	int *arr,n,i;
  	//srand((unsigned int)time(NULL));
	scanf("%d",&n);
  	
	arr = (int *)malloc(n*sizeof(int));
	hybridSort(arr,n);
	return 0;
}
