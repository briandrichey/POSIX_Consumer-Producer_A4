#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "buffer.h"

int insert_item(buffer_item item);
int remove_item(buffer_item* item);
sem_t emptySem, fullSem;
pthread_mutex_t mutex;

/*Producer Thread*/
void* producer(void* param) {
	buffer_item item;

	while (true) {
		//sleep for random time
		sleep(rand() % 10);
		//generate random number
		item = rand() % 10000000;;

		sem_wait(sem);		//aquire the semaphore

		if (insert_item(item))								//critical section
			std::cout << "report error condition" << '\n';
		else
			std::cout << "producer produced item: " << item << '\n';

		sem_post(sem);		//release the semaphore

	}
}

/*Consumer Thread*/
void* consumer(void* param) {
	buffer_item item;

	while (true) {
		//sleep for random time
		sleep(rand() % 10);
		//generate random number
		item = rand() % 10000000;

		sem_wait(sem);		//aquire the semaphore

		if (remove_item(&item))
			std::cout << "report error condition" << '\n';			//critical section
		else
			std::cout << "consumer consumed item: " << item << '\n';

		sem_post(sem);		//release the semaphore
	}
}

int main(int argc, char* argv[]) {
	
	srand(time(NULL));
	
	//  1. Get CLI argv[1] argv[2] argv[3] -> sleep time, number of producers, number of consumers

	//--- should probably do error checking on the input ---
	int sleepTime = atoi(argv[1]);
	int producerCount = atoi(argv[2]);
	int consumerCount = atoi(argv[3]);
	
	//	2. Init semaphores, mutex, buffers
	sem_init(&emptySem, 0, 0);
	sem_init(&fullSem, 0, 0);
	

	pthread_mutex_init(&mutex, NULL);

	pthread_t producers[producerCount];
	pthread_t consumers[consumerCount];
	
    
	//	3. Create producer threads
	for (int i = 0; i < producerCount; i++) {
		//create producer
		pthread_create(&producers, NULL, producer, NULL);		
	}

	//	4. Create consumer threads
	for (int i = 0; i < consumerCount; i++) {
		//create consumers
		pthread_create(&consumers, NULL, consumer, NULL);		
	}
	//	5. Sleep
	sleep(sleepTime);
	
	//	6. Exit
	return 0;
}