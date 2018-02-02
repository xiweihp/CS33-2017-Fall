#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

void *thread(void *vargp);
int calculate(int n);
//pthread_t tid;
//int isLeaf(int number);
//int thread_id = 0;
struct node
{
  int value;
  int label;
};

int main(int argc, char **argv)
{
  if(argc != 2)
    {
      fprintf(stderr, "Wrong number of arguments\n");
      exit(1);
    }

  int N = atoi(argv[1]);

  if(N <= 0)
    {
      fprintf(stderr, "Invalid argument\n");
      exit(1);
    }

  if(N == 1)
    {
      printf("[0]\n");
      exit(0);
    }
  pthread_t tid;
  printf("(0\n");
  struct node root;
  root.value = N;
  root.label = 0;

  pthread_create(&tid, NULL, thread, (void*)&root);
  pthread_join(tid,NULL);

  printf("0)\n");
  return 0;

}


int calculate(int n)
{
  if(n==0)
    return 1;
  else if(n==1)
    return 1;
  else
    return (calculate(n-1) + calculate(n-2) + 1);
}
/*
int isLeaf(int number)
{
if((number==0) || (number==1)
return 1;
else 
return 0;
}*/

void *thread(void *vargp)
{
  struct node* Node = (struct node*)vargp;
  //  int* returnValue = malloc(sizeof(int));
  //*returnValue = 0;
  struct node* leftChild = malloc(sizeof(struct node)*1);
  leftChild->value = Node->value-1;
  leftChild->label = Node->label+1;
  if(Node->value <= 1)
  {
  //    *returnValue = 1;
    printf("[%d]\n",Node->label);
    free(leftChild);
    pthread_exit(NULL);
  }
  else
  {
    if(leftChild->value > 1)
      printf("(%d\n",leftChild->label);

    pthread_t tid;
    pthread_create(&tid,NULL,thread,leftChild);
    pthread_join(tid,NULL);
    if(leftChild->value > 1)
      printf("%d)\n",leftChild->label);
  //    (*(int*)returnValue) ++;
    free(leftChild);
  }
  if(Node->value - 2 >= 0)
  {
    struct node* rightChild = malloc(sizeof(struct node)*1);
    pthread_t tid;
    rightChild->value = Node->value -2;
    rightChild->label = Node->label + 1 + calculate((Node->value)-1);
    if(rightChild->value > 1)
      printf("(%d\n",rightChild->label);
 
    pthread_create(&tid,NULL,thread,rightChild);
    pthread_join(tid,NULL);
    if(rightChild->value > 1)
      printf("%d)\n",rightChild->label);
    free(rightChild);
  }

  return NULL;
}

