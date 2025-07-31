#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>
#include <cstring>

int main(int argc, char *argv[]) {
  /* Initialize the Run Copy of Disk */
  Disk disk_run;
  // create objects for the relation catalog and attribute catalog
  RecBuffer relCatBuffer(RELCAT_BLOCK);
  RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

  HeadInfo relCatHeader;
  HeadInfo attrCatHeader;

  // load the headers of both the blocks into relCatHeader and attrCatHeader.
  // (we will implement these functions later)
  relCatBuffer.getHeader(&relCatHeader);
  // attrCatBuffer.getHeader(&attrCatHeader);
  
  int i,j,k,currAttrCatBlock;
  for (i=0;i<relCatHeader.numEntries;i++) {
    currAttrCatBlock = ATTRCAT_BLOCK; 
    Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

    relCatBuffer.getRecord(relCatRecord, i);

    printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);
    for(k=0;k<DISK_BLOCKS;k++){
      if(currAttrCatBlock <= 4 || currAttrCatBlock >=DISK_BLOCKS){
        break;
      }
      printf("  * Visting Block No. %d\n",currAttrCatBlock);
      attrCatBuffer = RecBuffer(currAttrCatBlock);
      attrCatBuffer.getHeader(&attrCatHeader);

      for (int j=0;j<attrCatHeader.numEntries;j++) {
          // declare attrCatRecord and load the attribute catalog entry into it
          Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
          attrCatBuffer.getRecord(attrCatRecord,j);
          if (std::strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal,relCatRecord[RELCAT_REL_NAME_INDEX].sVal)==0) {
            const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
            printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
          }
      }

      //find the rblock
      currAttrCatBlock = attrCatHeader.rblock; 
    }
    printf("\n");
  }
  return 0;
}
