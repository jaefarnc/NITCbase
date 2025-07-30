#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>

int main(int argc, char *argv[]) {
  /* Initialize the Run Copy of Disk */
  Disk disk_run;
  // StaticBuffer buffer;
  // OpenRelTable cache;

  // unsigned char buffer[BLOCK_SIZE];
  // Disk::readBlock(buffer, 7000);
  // char message[]="hello";
  // memcpy(buffer+20,message,6);
  // Disk::writeBlock(buffer,7000);
  //
  // unsigned char buffer2[BLOCK_SIZE];
  // char message2[6];
  // Disk::readBlock(buffer2,7000);
  // memcpy(message2,buffer2+20,6);
  //
  // std::cout << message2;
  //return FrontendInterface::handleFrontend(argc, argv);
  unsigned char buffer[BLOCK_SIZE];
  int i,j,k;
  for(i=0;i<4;i++){
    Disk::readBlock(buffer,i);
    for(j=0;j<BLOCK_SIZE;j++){
      k = i*BLOCK_SIZE+j;
      std::cout<<"Block Number "<<k<<" has "<<static_cast<int>(buffer[j])<<std::endl;
    }
  }
  return 0;
}
