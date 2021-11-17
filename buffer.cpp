#include "buffer.h"

//buffer needs to be circular 
buffer_item buffer[BUFFER_SIZE];

int fpos = -1; 
int rpos = -1;

int insert_item(buffer_item item) { 
/*
	* insert
	* return 0 if success
	* return -1 if fail
	*/
	  if ((fpos == 0 && rpos == BUFFER_SIZE-1) ||
            (rpos == (fpos-1)%(BUFFER_SIZE-1)))
    {
        std::cout<<"Buffer is Full"<<std::endl;
        return -1;
    }
 
    else if (fpos == -1) /* Insert First Element */
    {
        fpos = rpos = 0;
        buffer[rpos] = item;
    }
 
    else if (rpos == BUFFER_SIZE-1 && fpos != 0)
    {
        rpos = 0;
        buffer[rpos] = item;
    }
 
    else
    {
        rpos++;
        buffer[rpos] = item;
    }
	return 0;
}

int remove_item(buffer_item *item) {
	/*remove item
	* return 0 if success
	* return -1 if  fail 
	*/
	 if (fpos == -1)
    {
        std::cout<<"Buffer is Empty"<<std::endl;
        return -1;
    }
 
    *item = buffer[fpos];
    buffer[fpos] = -1;
    if (fpos == rpos)
    {
        fpos = -1;
        rpos = -1;
    }
    else if (fpos == BUFFER_SIZE-1)
        fpos = 0;
    else
        fpos++;
 
    
	return 0;
}

void display_buffer()
{
    if (fpos == -1)
    {
        std::cout<<"Buffer is Empty"<<std::endl;
        return;
    }
    std::cout<<"The current content of the buffer is [";
    if (rpos >= fpos)
    {
        for (int i = fpos; i <= rpos; i++)
            std::cout<<buffer[i]<<",";
    }
    else
    {
        for (int i = fpos; i < BUFFER_SIZE; i++)
            std::cout<<buffer[i]<<",";
 
        for (int i = 0; i <= rpos; i++)
            std::cout<<buffer[i]<<",";
    }
	std::cout<<"]"<<std::endl;
}