#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

int HashTable[SIZE];

void initHashTable()
{
    for(int i=0;i<SIZE;i++)
    {
        HashTable[i]=-1;
    }
}

int hash1(int key)
{
    return key%SIZE;
}

int hash2(int key)
{
    return 7-(key%7);  // used in double hashing
}

// linear probing
void linearprobing(int key)
{
    int index=hash1(key);
    while(HashTable[index]!=-1)
    {
        index=(index+1)%SIZE;
    }
    HashTable[index]=key;
}

// quadratic probing
void quadraticprobing(int key)
{
    int index=hash1(key);
    int i=1;
    while(HashTable[index]!=-1)
    {
        index=(hash1(key)+i*i)%SIZE;
        i++;
    }
    HashTable[index]=key;
}

// double hashing
void doubleHashing(int key)
{
    int index = hash1(key);
    int step = hash2(key);
    while(HashTable[index] != -1)
    {
        index = (index + step) % SIZE;
    }
    HashTable[index] = key;
}

void displayHashTable()
{
    for(int i=0;i<SIZE;i++)
    {
        if(HashTable[i]==-1)
            printf("%d:Empty\n",i);
        else
            printf("%d:%d\n",i,HashTable[i]);
    }
}

// separate chaining
struct Node{
    int data;
    struct Node*next;
};
struct Node*Chain[SIZE];

// initialize chaining table
void initChain()
{
    for(int i=0;i<SIZE;i++)
        Chain[i]=NULL;    
}

// insert separate chaining
void separateChaining(int key)
{
    int index=hash1(key);
    struct Node*newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->data=key;
    newNode->next=Chain[index];
    Chain[index]=newNode;
}

void displayChain()
{
    for(int i=0;i<SIZE;i++)
    {
        printf("%d:",i);
        struct Node*temp=Chain[i];
        while(temp!=NULL)
        {
            printf("%d->",temp->data);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}

int main()
{
    int ch,key,n;
    printf("Hashing collision resolution techniques\n");
    printf("1. linear\n");
    printf("2. quadratic\n");
    printf("3. double\n");
    printf("4. separate chaining\n");
    printf("Enter your choice:\n");
    scanf("%d",&ch);
    printf("Enter number of elements:\n");
    scanf("%d", &n);

    switch(ch)
    {
        case 1:
            initHashTable();
            printf("Enter elements:\n");
            for(int i=0;i<n;i++)
            {
                scanf("%d",&key);
                linearprobing(key);
            }
            displayHashTable();
            break;

        case 2:
            initHashTable();
            printf("Enter elements:\n");
            for(int i=0;i<n;i++)
            {
                scanf("%d",&key);
                quadraticprobing(key);
            }
            displayHashTable();
            break;

        case 3:
            initHashTable();
            printf("Enter elements:\n");
            for(int i=0;i<n;i++)
            {
                scanf("%d",&key);
                doubleHashing(key);
            }
            displayHashTable();
            break;

        case 4:
            initChain();   // ? fixed
            printf("Enter elements:\n");
            for(int i=0;i<n;i++)
            {
                scanf("%d",&key);
                separateChaining(key);   // ? fixed spelling
            }
            displayChain();
            break;

        default:
            printf("Invalid choice\n");
    }
    return 0;
}
