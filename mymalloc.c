#include <stdlib.h>
#include<stdio.h>

char memory[25000];

struct block{
    int size;
    int free;
    struct block *next;

};

struct block *freeList=(void *)memory;

void initialize(){
    freeList->size=2500-sizeof(struct block);
    freeList->free=1;
    freeList->next=NULL;
}

void *MyMalloc(size_t noOfBytes){
    struct block *curr;
    void *result;

    if(!(freeList->size)){
        initialize();
        printf("Memory is Initialized");
    }

    curr=freeList;

    while((((curr->size)<noOfBytes)||((curr->free==0))&&curr->next==NULL)){
        curr=curr->next;
    }
    if((curr->size)==noOfBytes){
        curr->free=0;
        result=(void*)(++curr);
        return result;
    }
}

void split(struct block *fitting_slot ,size_t size){

    struct block *new1=(void *)fitting_slot+size+sizeof(struct block);

    new1->size=(fitting_slot->free)-(size+sizeof(struct block));
    new1->free=1;
    new1->next=fitting_slot->next;

    fitting_slot->size=size;
    fitting_slot->free=0;
    fitting_slot->next=new1;
}



void MyFree(void* ptr){
    if(((void*)memory<=ptr)&& (ptr<=(void*)(memory+25000))){
        struct block* curr=ptr;
        --curr;
        curr->free=1;
        merge();
    }
    else{
        printf("Pointer is not a void one");
    }
}

void merge(){
    struct block *curr;
    curr=freeList;

    while(curr->next!=NULL){
        if(curr->free && curr->next->free){
            curr->size+=curr->next->size+sizeof(struct block);
            curr->next=curr->next->next;
        }
        curr=curr->next;
    }
}



int main(){
    int *p=(int *)MyMalloc(100*sizeof(int));
    char *q=(char*)MyMalloc(250*sizeof(char));
    int *r=(int *)MyMalloc(1000*sizeof(int));

    MyFree(p);

//    int *p=(int *)MyMalloc(100*sizeof(int));
//    int *p=(int *)MyMalloc(100*sizeof(int));
//    int *p=(int *)MyMalloc(100*sizeof(int));
//    int *p=(int *)MyMalloc(100*sizeof(int));

}

