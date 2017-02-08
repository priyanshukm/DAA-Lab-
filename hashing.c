#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stat{
	int item;
  	int lenLong;
  	float avgComp;
  	float stdDev;
};

struct node{
	int data;
	struct node *next;
}*hash[1100];

struct stat hash_ETH(char **,int);
struct stat hash_cpp(char **,int);
struct stat hash_cc1(char **,int);

struct node *create(int val)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp -> data = val;
	temp -> next = NULL;
	return temp;
}

void insert(int pos,int index)
{
	struct node * ptr = hash[pos],*bptr = hash[pos];
	while(ptr != NULL)
	{
		bptr = ptr;
		ptr = ptr->next;		
	}
	bptr->next = create(index);
}

int findComp(int pos,int index)
{
	int count = 1;
	struct node * ptr = hash[pos];
	while(ptr!= NULL && ptr->data != index)
	{
		count++;
		ptr = ptr->next;		
	}
	return count;
}

int main()
{
  	char **input;
  	struct stat hash_stat;
  	int n,k,i,j;
  	srand(time(NULL));
  	n=1632;
  	k=5;
  	input = (char **)malloc(n*sizeof(char *));
  	for(i=0;i<n;i++)
    	{
      		input[i]=(char *)malloc((k+1)*sizeof(char));
      		for(j=0;j<k;j++)
			input[i][j]=(rand()%95)+32;
      		input[i][k]='\0';
    	}
  	printf("ETH\n");
  	for(i=1040;i<=1050;i++)
    	{
      		hash_stat = hash_ETH(input,i);
      		printf("%d,%f,%f\n",i,hash_stat.avgComp,hash_stat.stdDev);
    	}
  	printf("GNU-cc1\n");
  	for(i=1040;i<=1050;i++)
    	{
      		hash_stat = hash_cc1(input,i);
      		printf("%d,%f,%f\n",i,hash_stat.avgComp,hash_stat.stdDev);
    	}
  	printf("GNU-cpp\n");
  	for(i=1040;i<=1050;i++)
    	{
      		hash_stat = hash_cpp(input,i);
      		printf("%d,%f,%f\n",i,hash_stat.avgComp,hash_stat.stdDev);
    	}
  
  	return 0;
}

struct stat hash_ETH(char **input,int tablesize)
{
  	struct stat hash_stat;
	int i,j,H[1635];
	float tot[1635],totComp = 0; 
	for(i=0;i<1100;i++)
	{
		hash[i] = create(i);		
	}	
	hash_stat.item = 0;
	for(i = 0; i < 1632; i++)
	{
		int h[8];
		h[0] = 1;
		for(j = 1; j <=5; j++)
		{
			h[j] = (input[i][j-1])*((h[j-1]%257)+1);	
		}
		H[i] = h[5]%tablesize;
		insert(H[i],i);
		hash_stat.item++;
		tot[i] = findComp(H[i],i);
		totComp = totComp + tot[i];
	}
	hash_stat.avgComp = (totComp/(hash_stat.item));	
	hash_stat.stdDev = 0;
	for(i = 0; i < 1632; i++)
	{
		float x = tot[i]-hash_stat.avgComp;
		hash_stat.stdDev += (x*x);
	}
	hash_stat.stdDev /= (hash_stat.item);
  	return hash_stat;
}

struct stat hash_cpp(char **input,int tablesize)
{
	struct stat hash_stat;
  	int i,j,H[1635];
	float tot[1635],totComp = 0;
	for(i=0;i<1100;i++)
	{
		hash[i] = create(i);		
	}	
	hash_stat.item = 0;
	for(i = 0; i < 1632; i++)
	{
		int h[8];
		h[0] = 0;
		for(j = 1; j <=5; j++)
		{
			h[j] = 4*h[j-1] + (input[i][j-1]);	
		}
		H[i] = (h[5]&((unsigned int)(~(1<<31))))%tablesize;
		insert(H[i],i);
		hash_stat.item++;
		tot[i] = findComp(H[i],i);
		totComp = totComp + tot[i];
	}
	hash_stat.avgComp = (totComp/(hash_stat.item));	
	hash_stat.stdDev = 0;
	for(i = 0; i < 1632; i++)
	{
		float x = tot[i]-hash_stat.avgComp;
		hash_stat.stdDev += (x*x);
	}
	hash_stat.stdDev /= (hash_stat.item);
  	return hash_stat;
}

struct stat hash_cc1(char **input,int tablesize)
{
  	struct stat hash_stat;
  	int i,j,H[1635];
	float tot[1635],totComp = 0;
	hash_stat.item = 0;
	for(i=0;i<1100;i++)
	{
		hash[i] = create(i);		
	}	
	for(i = 0; i < 1632; i++)
	{
		int h[8];
		h[0] = 5;
		for(j = 1; j <=5; j++)
		{
			h[j] = (613*h[j-1]) - 1 + (input[i][j-1]);	
		}
		H[i] = (h[5]&((unsigned int)(~(3<<30))))%tablesize;
		insert(H[i],i);
		hash_stat.item++;
		tot[i] = findComp(H[i],i);
		totComp = totComp + tot[i];
	}
	hash_stat.avgComp = (totComp/(hash_stat.item));	
	hash_stat.stdDev = 0;
	for(i = 0; i < 1632; i++)
	{
		float x = tot[i]-hash_stat.avgComp;
		hash_stat.stdDev += (x*x);
	}
	hash_stat.stdDev /= (hash_stat.item);
  	return hash_stat;
}

