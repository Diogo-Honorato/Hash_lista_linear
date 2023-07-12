#include<stdio.h>
#include<stdlib.h>
#define    TAM 21

typedef struct Cell
{
    int item;
    struct Cell *next;
}Cell;

typedef struct
{
    Cell *first;
    int full;
}HashTable;


void StartHash(HashTable *hash)
{
    for(int i = 0; i < TAM; i++)
    {
        hash[i].first = NULL;
    }
    
    hash->full = 0;
}

int FunctionHash(int key)
{
    return key %  TAM;
}

int InsertHash(HashTable *hash,int key)
{
    int index = FunctionHash(key);
    
    Cell *newcell = (Cell*)malloc(sizeof(Cell));
    newcell->next = NULL;
    newcell->item = key;
    
    if(hash[index].first == NULL)
    {
        hash[index].first = newcell;
    }
    else
    {
        newcell->next = hash[index].first;
        hash[index].first = newcell;
    }
    
    hash->full++;
}

int *RemovedHash(HashTable *hash,int key)
{
    int index = FunctionHash(key);
    
    if(hash[index].first == NULL)
    {
        printf("\n\nKey not in the hash table to removed: %d\n\n",key);
        return NULL;
    }
    
    Cell *aux = hash[index].first;
    Cell *temp = aux;
    
    if(aux->item == key)
    {
        hash[index].first = hash[index].first->next;
        
        free(aux);
        
        hash->full--;
        printf("\n\nKey removed: %d\nIndex: %d\n\n",key,index);
    }
    else
    {
        while(aux != NULL && aux->item != key)
        {
            temp = aux;
            aux = aux->next;
        }
        
        if(aux)
        {
            temp->next = aux->next;
            free(aux);
            hash->full--;
            printf("\n\nKey removed: %d\nIndex: %d\n\n",key,index);
        }
        else
        {
            printf("\n\nKey not in the hash table to removed: %d\n\n",key);
            return NULL;
        }
    }
}

int *SearchHash(HashTable *hash,int key)
{
    int index = FunctionHash(key);

    if(hash[index].first == NULL)
    {
        printf("\n\nKey not in the hash table: %d\n\n",key);
        return NULL;
    }

    Cell *aux = hash[index].first;

    while (aux != NULL && aux->item != key )
    {
        aux = aux->next;
    }

    if(aux)
    {
        printf("\n\nKey was found: %d\nIndex: %d\n\n",key,index);
    }
    else
    {
       printf("\n\nKey not found: %d\n",key);
    }
    
    return 0;
}

int PrintHash(HashTable *hash)
{
    Cell *aux;
    for(int i = 0; i < TAM; i++)
    {
        aux = hash[i].first;

        printf("[%d] : ",i);

        while(aux != NULL)
        {
            printf("(%d)->", aux->item); 
            aux = aux->next;
        }
        printf("\n");
    }
}

int main()
{
    
    HashTable hash[TAM];
    int list[] = {39,89,70,33,110,50,56,90,10,80};
    int size = sizeof(list) / sizeof(int);

    StartHash(hash);

    for (int i = 0; i < size; i++)
    {
       InsertHash(hash, list[i]);
    }
    
    PrintHash(hash);
    SearchHash(hash,90);
    RemovedHash(hash,89);
    PrintHash(hash);
}