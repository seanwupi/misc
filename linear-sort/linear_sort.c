#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

char str[1000];
int num[100];
pthread_t id[100];
pthread_mutex_t mutex[100];
int n;

void sort(int i) {
  int j;
  for (j=0; j<n; ++j) {
    if (num[j] < num[i]) {
      pthread_mutex_lock(&mutex[j]);
      pthread_mutex_unlock(&mutex[j]);
    }
  }
  printf("%d ", num[i]);
  pthread_mutex_unlock(&mutex[i]);
}

int main() {
  char *p;
  int i;
  fgets(str, sizeof(str), stdin);
  p = strtok(str, " ");
  do {
    pthread_mutex_init(&mutex[n], 0);
    pthread_mutex_lock(&mutex[n]);
    num[n++] = atoi(p);
  } while (p = strtok(0, " "));
  for (i=0; i<n; ++i) 
    pthread_create(&id[i], 0, sort, i);
  for (i=0; i<n; ++i) 
    pthread_join(id[i], 0);
  for (i=0; i<n; ++i) 
    pthread_mutex_destroy(&mutex[i]);
  puts("");
}
