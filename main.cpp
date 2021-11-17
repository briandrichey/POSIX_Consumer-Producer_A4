#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "buffer.h"

int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void display_buffer();

sem_t emptySem, fullSem;
pthread_mutex_t mutex;

buffer_item item;

/*Producer Thread*/
void* producer(void* param) {
	buffer_item prodItem = item;

	while (true) {
		//sleep for random time
		sleep(rand() % 10);
		//generate random number
		prodItem = rand() % 100;

		sem_wait(&emptySem);		//aquire the semaphore


		if (insert_item(prodItem))								//critical section
			std::cout << "error producing item" << '\n';
		else
			std::cout << "producer produced item: " << prodItem << '\n';
			display_buffer();
			std::cout << '\n';

		sem_post(&fullSem);		//release the semaphore

	}
}

/*Consumer Thread*/
void* consumer(void* param) {
	buffer_item item;

	while (true) {
		//sleep for random time
		sleep(rand() % 10);
		//generate random number

		sem_wait(&fullSem);		//aquire the semaphore

		if (remove_item(&item))
			std::cout << "error consuming item" << '\n';			//critical section
		else
			std::cout << "consumer consumed item: " << item << '\n';
			display_buffer();
			std::cout << '\n';

		sem_post(&emptySem);		//release the semaphore
	}
}

int main(int argc, char* argv[]) {
	
	srand(time(NULL));
	
	//  1. Get CLI argv[1] argv[2] argv[3] -> sleep time, number of producers, number of consumers
	
	//--- should probably do error checking on the input ---
	int sleepTime = atoi(argv[1]);
	int producerCount = atoi(argv[2]);
	int consumerCount = atoi(argv[3]);
	
	std::cout << "Step 1 done" << '\n';
	//	2. Init semaphores, mutex, buffers
	sem_init(&emptySem, 0, 0);
	sem_init(&fullSem, 0, BUFFER_SIZE);

	pthread_mutex_init(&mutex, NULL);

	pthread_t producers[producerCount];
	pthread_t consumers[consumerCount];
	
	std::cout << "Step 2 done" << '\n';
	//	3. Create producer threads
	for (int i = 0; i < producerCount; i++) {
		//create producer
		pthread_create(&producers[i], NULL, producer, NULL);		
	}
	std::cout << "Step 3 done" << '\n';
	//	4. Create consumer threads
	for (int i = 0; i < consumerCount; i++) {
		//create consumers
		pthread_create(&consumers[i], NULL, consumer, NULL);		
	}
	std::cout << "Step 4 done" << '\n';
	//	5. Sleep
	sleep(sleepTime);
	std::cout << "Step 5 done" << '\n';
	
	//	6. Exit
	return 0;
}