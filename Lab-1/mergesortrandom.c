#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
 
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
void mergeSort(int arr[], int l, int r, int k)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
 
        if(m-l < k)
        	insertionSort(arr,l,m);
        else
        	mergeSort(arr, l, m, k);

        if(r-m < k)
        	insertionSort(arr,m+1,r);
        else
        	mergeSort(arr, m+1, r, k);
 
        merge(arr, l, m, r);
    }
}

void hybridSort(int *arr, int n)
{
	int i,j,b[100005];
	for(i=0;i<n;i++)
	{
		b[i] = rand()%100000;
	}
	
	for(i=1;i<=100;i++)
	{
		for(j=0;j<n;j++)
			arr[j] = b[j];

		time_t begin,end;
			
	    begin = clock();
		mergeSort(arr,0,n-1,i);
	    end = clock();

	    printf("%d\t%ld\n",i,end-begin);
  	}
}

int main()
{
	int *arr,n,i;
  	//srand((unsigned int)time(NULL));
	scanf("%d",&n);
  	
	arr = (int *)malloc((n+10)*sizeof(int));
	hybridSort(arr,n);
	return 0;
}
