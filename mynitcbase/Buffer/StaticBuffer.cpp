#include "StaticBuffer.h"

//declarations for this class can be found at "StaticBuffer.h"


unsigned char StaticBuffer::blocks[BUFFER_CAPACITY][BLOCK_SIZE];
struct BufferMetaInfo StaticBuffer::metainfo[BUFFER_CAPACITY];

StaticBuffer::StaticBuffer(){
  //initialize all blocks as free
  for(int bufferIndex=0;bufferIndex<BUFFER_CAPACITY;bufferIndex++){
    metainfo[bufferIndex].free = true;
  }
}

/*
At this stage, we are not writing back from the buffer to the disk since we are not modifying the buffer. So, we will define an empty destructor for now. In subsequent stages, we will implement the write-back functionality here.
*/
StaticBuffer::~StaticBuffer(){}

int StaticBuffer::getFreeBuffer(int blockNum){
  if(blockNum<0 || blockNum > DISK_BLOCKS){
    return E_OUTOFBOUND;
  }
  int allocatedBuffer=E_OUTOFBOUND;

  //iterate through all the blocks in the StaticBuffer 
  // find the first free block in the buffer (check metainfo)
  // assign allocatedBuffer = index of the free block 
  for(int bufferIndex=0;bufferIndex<BUFFER_CAPACITY;bufferIndex++){
    if(metainfo[bufferIndex].free==true){
      allocatedBuffer=bufferIndex;
      break;
    }
  }
  //if no buffer is free, we should do a swap, but no for now return the error
  if(allocatedBuffer == E_OUTOFBOUND) return E_OUTOFBOUND;

  metainfo[allocatedBuffer].free = false;
  metainfo[allocatedBuffer].blockNum = blockNum;
  
  return allocatedBuffer;
}

/*Get the buffer index where a particular block is stored or E_BLOCKNOTINBUFFER otherwise 
 */ 
int StaticBuffer::getBufferNum(int blockNum){
  // Check if blockNum is valid ( between zero and DISK_BLOCKS )
  // and return E_OUTOFBOUND if not valid. 
  if(blockNum<0 || blockNum > DISK_BLOCKS){
    return E_OUTOFBOUND;
  }
  //find and return the bufferIndex which corresponds to blockNum( check metainfo)
  for(int bufferIndex=0;bufferIndex<BUFFER_CAPACITY;bufferIndex++){
    if(metainfo[bufferIndex].free==true)continue;
    if(metainfo[bufferIndex].blockNum != blockNum)continue;
    return bufferIndex;
  }
  //if block is not in the buffer 
  return E_BLOCKNOTINBUFFER;
}
