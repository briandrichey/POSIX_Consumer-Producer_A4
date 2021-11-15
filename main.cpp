#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

int insert_item(buffer_item item);
int remove_item(buffer_item* item);


void* producer(void* param) {
	buffer_item item;

	while (true) {
		//sleep for random time
		//sleep(...);
		//generate random number
		item = rand();
		if (insert_item(item))
			std::cout << "report error condition" << '\n';
		else
			std::cout << "producer produced item: " << item << '\n';
	}
}

void* consumer(void* param) {
	buffer_item item;

	while (true) {
		//sleep for random time
		//sleep(...);
		//generate random number
		item = rand();
		if (remove_item(&item))
			std::cout << "report error condition" << '\n';
		else
			std::cout << "consumer consumed item: " << item << '\n';
	}
}

int main(int argc, char* argv[]) {
	//  1. Get CLI argv[1] argv[2] argv[3] -> sleep time, number of producers, number of consumers

	//--- should probably do error checking on the input ---
	int sleepTime = atoi(argv[1]);
	int producerCount = atoi(argv[2]);
	int consumerCount = atoi(argv[3]);
	
	//	2. Init buffers
	pthread_t producers[producerCount];
	pthread_t consumers[consumerCount];
	
    
	//	3. Create producer threads
	for (int i = 0; i < producerCount; i++) {
		//create producer
		//pthread_create()
	}

	//	4. Create consumer threads
	for (int i = 0; i < consumerCount; i++) {
		//create consumers
		//pthread_create()
	}
	//	5. Sleep
	//sleep(sleepTime);
	
	//	6. Exit
	return 0;
}