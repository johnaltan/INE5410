#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <malloc.h>

#define VECT_SIZE
#define BUCKETS
#define THREADS

typedef struct {
	int size, minValue, maxValue;
	int *bucket;
} bucket_t;

int usedBucket;
bucket_t *arrayBuckets;

pthread_mutex_t usedBucketMutex;

void bubbleSort(int, int);
void *sortIt(void *);

int main(int argc, char **argv) {
	pthread_t *myThreads;
	int i, *vector;
	
	vector = (int *)malloc(sizeof(int) * VECT_SIZE);
	arrayBuckets = (arrayBuckets *)calloc(sizeof(bucket_t), BUCKETS);
	
	srand(666);
	for (i = 0; i < VECT_SIZE; i++) vector[i] = rand() % VECT_SIZE;
	
	int quantMod = VECT_SIZE % BUCKETS - 1;
	int quantDiv = VECT_SIZE / BUCKETS;
	arrayBuckets[0].minValue = 0;
	arrayBuckets[0].maxValue = quantDiv + (quantMod-- > 0)?1:0;
    arrayBuckets[0].bucket = (int *)malloc(sizeof(int) * VECT_SIZE);
	for (i = 1; i < BUCKETS; i++) {
        arrayBuckets[i].minValue = arrayBuckets[i - 1].maxValue + 1;
        arrayBuckets[i].maxValue = arrayBuckets[i].minValue + quantDiv + (quantMod-- > 0)?1:0;
	}
	
	for (i = 0; i < VECT_SIZE; i++) {
        int j;
		for (j = 0; j < BUCKET; j++) {
            if ((vector[i] >= arrayBuckets[j].minValue) && (vector[i] <= arrayBuckets[j].maxValue)) {
                arrayBuckets[j].num[arrayBuckets[j].size++] = vector[i];
                break;
            }
        }
    }
    
    //realloc arrayBuckets.bucket and delete empty buckets
    
	
	pthread_mutex_init(&usedBucketMutex, NULL);
	myThreads = (pthread_t *)malloc(sizeof(pthread_t) * THREADS);
	for (i = 0; i < THREADS; i++)	
		pthread_init(&myThreads[i], NULL, sortIt, NULL);
	for (i = 0; i < THREADS; i++)
		pthread_join(myThreads[i],NULL);
	pthread_mutex_destroy(&usedBucketMutex);
    
    // free used memory
}

void *sortIt(void *arg) {
	int bucketIndex;
	while (true) {
		pthread_mutex_lock(usedBucketMutex);
		bucketIndex = usedBucket++;
		pthread_mutex_unlock(usedBucketMutex);
		if (bucketIndex >= BUCKETS) {
			break;
		}
		else if (arrayBuckets[bucketIndex].size == 0) {
            continue;
        }
		bubbleSort(arrayBuckets[bucketIndex].bucket, arrayBuckets[bucketIndex].size);
	}
	return NULL;
}

void bubbleSort(int *buf, int size) {
	int aux;
	for(int i=tamanho-1; i >= 1; i--)
		for( int j=0; j < i ; j++)
			if(vetor[j]>vetor[j+1]) {
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
}
