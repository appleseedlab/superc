#include<stdio.h>
#include<stdlib.h>

struct dnode {
  int val;
  struct dnode *next;
};

#ifdef CONFIG_FEATURE_LS_RECURSIVE
void dfree(struct dnode **arr)
{
  struct dnode *cur, *next;

  if (arr == NULL)
    return;

  cur = arr[0]; // is no longer the head
  while (cur != NULL) {
    next = cur->next;
    free(cur);
    cur = next;
  }
}
#endif

void showdirs(struct dnode **arr)
{
  for (int i = 0; i < 5; ++i) {
    printf("\n%d", arr[i]->val);
  }

  #ifdef CONFIG_FEATURE_LS_RECURSIVE
  dfree(arr); //ERROR
  #endif
}

#ifdef CONFIG_FEATURE_LS_SORTFILES
void sort(int **arr, int size)
{
  int **temp;
  int i, j;

  if (arr == NULL || size < 1)
    return;

  for(i=0;i<size;i++) {
    for(j=i;j<size;j++) {
      if(*arr[i] > *arr[j]) {
        temp=*arr[i];
        *arr[i]=*arr[j];
        *arr[j]=temp;
      }
    }
  }
}
#endif

int main(int argc, char **argv)
{
  struct dnode *curr, *head;
  const int size = 5;
  struct dnode *arr[size];

  for (int i = 0; i < size; i++) {
    curr = (struct dnode *) malloc(sizeof(struct dnode));
    curr->val = rand() % 10;
    curr->next = head;
    head = curr;
    arr[(size-1)-i] = curr;
  }

  if (rand() % 2) {
    #ifdef CONFIG_FEATURE_LS_SORTFILES
    sort(arr, size);
    #endif
    showdirs(arr);
  }
  return 0;
}
