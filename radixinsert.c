# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

void radix_sort(char **,int,int);

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

void insertion_sort(char **input, int n, int pos,int k)
{
	char temp[k+1];
	int i, j;
	for (i = 0; i < n; i++) {
		j = i;
		while (j > 0 && input[j-1][pos] > input[j][pos]) {
			strcpy(temp,input[j-1]);
			strcpy(input[j-1],input[j]);
			strcpy(input[j],temp);
			j = j - 1;
		}
	}
}

void radix_sort(char **input,int n,int k)
{
	int i;
	for (i = k-1; i>=0; i--)
		insertion_sort(input, n, i, k);
}


