#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ll long long int
struct node 
{
   	int data;
    	struct node *lchild;
    	struct node *rchild;
	struct node *parent;
}*root;
int pos[10005];

void printGivenLevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1)
    {
        printGivenLevel(root->lchild, level-1);
        printGivenLevel(root->rchild, level-1);
    }
}

int height(struct node* node)
{
    if (node==NULL)
        return 0;
    else
    {
        int lheight = height(node->lchild);
        int rheight = height(node->rchild);
 
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

void printLevelOrder(struct node* root)
{
    int h = height(root);
    int i;
    for (i=1; i<=h; i++)
        printGivenLevel(root, i);
}

struct node *GetNode(int x)
{
    	struct node *temp=(struct node *)malloc(sizeof(struct node));
        	temp->data=x;
    	temp->lchild=NULL;
    	temp->rchild=NULL;
    	return temp;    
}

void printPreorder(struct node* node)
{
     if (node == NULL)
          return;
 
     printf("%d ", node->data);  
     printPreorder(node->lchild);  
     printPreorder(node->rchild);
}

void insert(int x,int size)
{
	struct node *rroot = root;
	int i;
	if(root==NULL)
	{
        root = GetNode(x);
		return ;
	}	
	for(i = size-2;i>=0;i--)
	{
		//printf("i : %d pos[i] : %d\n",i,pos[i]);
		if(pos[i] == 1)
		{	
			if(i == 0)
			{
				if(root->rchild==NULL)
        				root->rchild = GetNode(x);
				(root->rchild)->parent = root;
			}
			root = root->rchild;
		}	
		else
		{
			if(i == 0)
			{
				if(root->lchild == NULL)
        				root->lchild = GetNode(x);
				(root->lchild)->parent = root;
			}
			root = root->lchild;
		}
	}
	//printf("root data :%d\n",root->data);
	while(root->parent != NULL)
	{
		if(root -> data  > root->parent->data)
		{
			int temp = root->data;
			root->data = root->parent->data;
			root->parent->data = temp;
			//printf("swapped: %d %d\n",root->parent->data,root->data);
			root = root->parent;
		}
		else
		{
			break;
		}	
	}
	root = rroot;
}

int main()
{
    root = NULL;
    ll n,i,x,size,num;
    scanf("%lld",&n);
    	
	for(i=1;i<=n;i++)
    {
       	scanf("%lld",&x);
		num = i;
		size = 0;
		while(num!=0)
		{
			pos[size] = (num%2);
			num/= 2;
			size++;
		}
		//printf("%lld\n",size);
       	insert(x,size);
    }
    printLevelOrder(root);
    return 0;
}

