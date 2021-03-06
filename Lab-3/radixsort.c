# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

void radix_sort(char **,int,int);

void countSort(char **input, int n, int ind, int k)
{
   	char output[n][k+1];
    	int i, count[100] = {0};
 
    	for (i = 0; i < n; i++)
        	count[input[i][ind]-32]++;
 
	for (i = 1; i < 95; i++)
	        count[i] += count[i - 1];
 
	for (i = n - 1; i >= 0; i--)
    	{
        	strcpy(output[count[input[i][ind]-32] - 1],input[i]);
        	count[input[i][ind]-32]--;
    	}
    	
	for (i = 0; i < n; i++)
	        strcpy(input[i],output[i]);
}

int main()
{
 	char **input;
  	char ch=' ';
  	int n,k,i,j;
  	srand(time(NULL));
  	scanf("%d",&n);
  	scanf("%d",&k);
  	input = (char **)malloc(n*sizeof(char *));
  	for(i=0;i<n;i++)
    	{
      		input[i]=(char *)malloc((k+1)*sizeof(char));
      		for(j=0;j<k;j++)
			input[i][j]=(rand()%95)+32;
      		input[i][k]='\0';
    	}
  	radix_sort(input,n,k);
  	for(i=0;i<n;i++)
    	{
      		printf("%s\n",input[i]);
    	}
  
  	return 0;
}

void radix_sort(char **input,int n,int k)
{
	int ind;
	for (ind = k-1; ind >= 0; ind--)
	        countSort(input, n, ind, k);
}

