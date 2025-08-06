#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
int main(int argc, char *argv[]) {
  /* Initialize the Run Copy of Disk */
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;
  // // create objects for the relation catalog and attribute catalog
  // RecBuffer relCatBuffer(RELCAT_BLOCK);
  // RecBuffer attrCatBuffer(ATTRCAT_BLOCK);
  //
  // HeadInfo relCatHeader;
  // HeadInfo attrCatHeader;
  //
  // // load the headers of both the blocks into relCatHeader and attrCatHeader.
  // // (we will implement these functions later)
  // relCatBuffer.getHeader(&relCatHeader);
  // // attrCatBuffer.getHeader(&attrCatHeader);
  //
  // int i,j,k,currAttrCatBlock;
  //
  //
  // //UPDATE ATTRIBUTE NAME -----------------------------------------
  // for (i=0;i<relCatHeader.numEntries;i++) {
  //   currAttrCatBlock = ATTRCAT_BLOCK; 
  //   Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog
  //
  //   relCatBuffer.getRecord(relCatRecord, i);
  //
  //   //printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);
  //   if(std::strcmp(relCatRecord[RELCAT_REL_NAME_INDEX].sVal,"Student")!=0)continue;
  //
  //   for(k=0;k<DISK_BLOCKS;k++){
  //     if(currAttrCatBlock <= 4 || currAttrCatBlock >=DISK_BLOCKS){
  //       break;
  //     }
  //     //printf("  * Visting Block No. %d\n",currAttrCatBlock);
  //     attrCatBuffer = RecBuffer(currAttrCatBlock);
  //     attrCatBuffer.getHeader(&attrCatHeader);
  //
  //     for (int j=0;j<attrCatHeader.numEntries;j++) {
  //         // declare attrCatRecord and load the attribute catalog entry into it
  //         Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  //         attrCatBuffer.getRecord(attrCatRecord,j);
  //         if (std::strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal,relCatRecord[RELCAT_REL_NAME_INDEX].sVal)==0) {
  //             if(std::strcmp(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal,"Class")==0){
  //               strcpy(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal,"Batch");
  //               attrCatBuffer.setRecord(attrCatRecord, j);
  //             }
  //         }
  //     }
  //
  //     //find the rblock
  //     currAttrCatBlock = attrCatHeader.rblock; 
  //   }
  //   printf("\n");
  // }
  //
  //
  // //PRINT ---------------------------------------------------
  // for (i=0;i<relCatHeader.numEntries;i++) {
  //   currAttrCatBlock = ATTRCAT_BLOCK; 
  //   Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog
  //
  //   relCatBuffer.getRecord(relCatRecord, i);
  //
  //   printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);
  //   for(k=0;k<DISK_BLOCKS;k++){
  //     if(currAttrCatBlock <= 4 || currAttrCatBlock >=DISK_BLOCKS){
  //       break;
  //     }
  //     printf("  * Visting Block No. %d\n",currAttrCatBlock);
  //     attrCatBuffer = RecBuffer(currAttrCatBlock);
  //     attrCatBuffer.getHeader(&attrCatHeader);
  //
  //     for (int j=0;j<attrCatHeader.numEntries;j++) {
  //         // declare attrCatRecord and load the attribute catalog entry into it
  //         Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  //         attrCatBuffer.getRecord(attrCatRecord,j);
  //         if (std::strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal,relCatRecord[RELCAT_REL_NAME_INDEX].sVal)==0) {
  //           const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
  //           printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
  //         }
  //     }
  //
  //     //find the rblock
  //     currAttrCatBlock = attrCatHeader.rblock; 
  //   }
  //   printf("\n");
  // }
  
  /*-------------------------------*/ 
  /*  for i= 0 and i =1 ( i.e RELCAT_RID and ATTRCAT_RELID)
   *    get the relation catalog entry using RelCacheTable::getRelCatEntry()
   *    printf("Relation: %s\n",relname);
   *
   *    for j = 0 to numAttrs of the relation - 1 
   *      get the attribute catalog entry for (rel-id i, attribte offset j) in attrCatEntry using AttrCacheTable::getAttrCatEntry()
   *
   *      pritn("  %s: %s\n", attrName, attrType);
  */ 
  for(int i =0;i<3;i++){
    //i = 0,1 means RELCAT_RELID and ATTRCAT_RELID
    RelCatEntry relCatEntry;
    RelCatEntry* relCatBuf = &relCatEntry;
    RelCacheTable::getRelCatEntry(i,relCatBuf);
    printf("Relation: %s\n", relCatBuf->relName);
    for(int j = 0; j < relCatBuf->numAttrs;j++){
      AttrCatEntry attrCatEntry;
      AttrCatEntry* attrCatBuf = &attrCatEntry;
      AttrCacheTable::getAttrCatEntry(i,j,attrCatBuf);
      const char *attrType = attrCatBuf->attrType == NUMBER ? "NUM" : "STR";
      printf("  %s: %s\n", attrCatBuf->attrName, attrType);
    }
  }
  return 0;

}
