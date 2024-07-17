
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dberror.h"
#include "storage_mgr.h"


int starting_point=0;
FILE *present_pg_ptr;
char  *header_page, *file_pages;
 int yes;
SM_FileHandle *fHandle;
char *processingFile;
  int curBlockPos;
  char *page_Header_1;
  

int start_point()
{
  if(starting_point == 1)
  do
  {
      return RC_OK;
    
  } while (starting_point == 1);
  
  
  
  else
  return -1;



}


void initStorageManager()
{
  if (start_point() != RC_OK)
  {
    starting_point = 1;
    printf("\n\t\t CS525Advance Database Organization \n\n");
    printf("\t\t\nA20502873\t Nirali");
    printf("\t\t\nA20494154\t Venkata");
    printf("\t\t\nA20502100\t Satish\n\n\n");
    
    
  }
  else
    printf(" The initialization of Storage Manager is complete!!!\n");
}









RC createPageFile(char *fileName)
{
  
  FILE *pg_ptr;
  


  pg_ptr = fopen(fileName, "w"); // open the file
  
   if (pg_ptr==0)
    return RC_FILE_NOT_FOUND;

  while (pg_ptr != 0)
  {
    char no_for_pages = fputs("1", pg_ptr);
    char headers= fwrite(header_page, PAGE_SIZE, 1, pg_ptr);
    

    file_pages = (char *)calloc(PAGE_SIZE, sizeof(char)); // data storing
    header_page = (char *)calloc(PAGE_SIZE, sizeof(char)); // utilizing the variable to store information such as total number of pages.
      no_for_pages;
                                   
     
     headers;
   
    
    fwrite(file_pages, PAGE_SIZE, 1, pg_ptr); //write
    
    fclose(pg_ptr);
    free(file_pages);
    free(header_page);
    return RC_OK;
  }
 
}


RC openPageFile(char *fileName, SM_FileHandle *fHandle)
{
  int value=PAGE_SIZE;
  present_pg_ptr = fopen(fileName, "r+"); // open in read mode.

   while(present_pg_ptr == 0) // return file not found for unavaibility of file.
    return RC_FILE_NOT_FOUND;
 
  

  char *page_Header_1;  
 page_Header_1= (char *)calloc(value, sizeof(char)); 
  fgets(page_Header_1,value, present_pg_ptr);
  char *totalPages;
  totalPages = page_Header_1;

  fHandle->fileName = fileName; 
  fHandle->totalNumPages = atoi(totalPages);
  fHandle->curPagePos = 0;
  //file pointer 
  
  fHandle->mgmtInfo = present_pg_ptr;

  free(page_Header_1); 
  return RC_OK;
}


RC closePageFile(SM_FileHandle *fHandle)
{
  while(fclose(present_pg_ptr) == 0) //if present page pointer is null 
  {
    printf("**Page file is ending!**\n");
    return RC_OK;
    if(fclose(present_pg_ptr) != 0) //if present page pointer is not null
    {
       return RC_FILE_NOT_FOUND;
    }
  }
  
  
 
}


int isFilePresent(char *fName)
{
  if (access(fName, F_OK) <= 1)
    return 1;
  else if(access(fName, F_OK) > 1)
  return 0;
}


RC destroyPageFile(char *fileName)
{
  if (present_pg_ptr) 
  {
    fclose(present_pg_ptr);
  }

   
   if (remove(fileName) <= 0) 
    {
      printf("**Destroyed Successfully!** \n");
      return RC_OK;
    }
  return RC_FILE_NOT_FOUND;
}


RC readBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  int check= (pageNum + 1) * PAGE_SIZE; //reading of section 1.
  printf("Reading First Section");
 
 while(pageNum > 0 ) //if page num is > O  then reading of section 2. 
  {
    printf("Reading Second Section");
    return RC_READ_NON_EXISTING_PAGE;
  }
  while(pageNum < (*fHandle).totalNumPages - 1)//  if page num is < total page no-1 then reading of section 2. 
  {
    printf("Reading Second Section");
    return RC_READ_NON_EXISTING_PAGE;
  }
//search for file 
//read the page into memory page 
  if (!fseek(fHandle->mgmtInfo, check, SEEK_SET))
  {
  printf("Reading Third Section");
   
    fread(memPage, sizeof(char), PAGE_SIZE, fHandle->mgmtInfo);
    fHandle->curPagePos = pageNum; // store recent position.

    return RC_OK;
  }
    
else

  printf("Reading Forth Section");
  return RC_READ_NON_EXISTING_PAGE; // return forth section.
}





int getBlockPos(SM_FileHandle *fHandle)
{
  
 return fHandle->curPagePos; //obtain the position of current page.
}



RC readFirstBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
 
 (SM_FileHandle) *fHandle;
 (SM_PageHandle) memPage;
  printf("Read section 1 ");
  if (readBlock(0, fHandle, memPage) == RC_OK) {
  printf("Read section 2");
   
return RC_OK;
  }
   if(readBlock(0, fHandle, memPage) != RC_OK)
      printf("Read section 3");
      return RC_READ_NON_EXISTING_PAGE;
}


 

RC readPreviousBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{

  



    if (readBlock(getBlockPos(fHandle) - 1, fHandle, memPage) != RC_OK)
    {
      return RC_READ_NON_EXISTING_PAGE;
    }
    else
    {
      while(readBlock(getBlockPos(fHandle) - 1, fHandle, memPage) == RC_OK)
       return RC_OK;
    }
   
}



RC readCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  if (readBlock(getBlockPos(fHandle), fHandle, memPage) != RC_OK)
   return RC_READ_NON_EXISTING_PAGE;
   else
   {
    while(readBlock(getBlockPos(fHandle), fHandle, memPage) == RC_OK)
      {
          return RC_OK;
      } 
   }
   
  
}



RC readNextBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  if (readBlock(getBlockPos(fHandle) + 1, fHandle, memPage) != RC_OK)
   
  return RC_READ_NON_EXISTING_PAGE;

  else
  {
     while(readBlock(getBlockPos(fHandle) + 1, fHandle, memPage) == RC_OK)
  {
    return RC_OK;
  }

  }
 
}




RC readLastBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  

  if ((*fHandle).curPagePos != (ftell(fHandle->mgmtInfo) / PAGE_SIZE))
    {
        return RC_READ_NON_EXISTING_PAGE;
    }
  else  
    while ((*fHandle).curPagePos == (ftell(fHandle->mgmtInfo) / PAGE_SIZE))
       {
        return RC_OK;
       }
}



RC writeBlock(int pno, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
  int check1= fHandle->totalNumPages;
  
  int check2= pno + 1;
  while(pno<check1-1)
    {
       return RC_OK;
    }
  
    while(pno > check1 - 1)
    {
      return RC_WRITE_FAILED;
      
    }

    while(pno < 0 )
    {
       return RC_WRITE_FAILED;
    }
      
  
  fseek(fHandle->mgmtInfo, (check2) * PAGE_SIZE, SEEK_SET); 

  
  fwrite(memPage, PAGE_SIZE, 1, fHandle->mgmtInfo); 
 
  fHandle->curPagePos = pno; //store recent position.
  
 return RC_OK;
}

//for getting current blocks
RC writeCurBlock;
RC writeCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) 
{

    if(writeCurBlock != RC_OK) 
     {
        return RC_WRITE_FAILED;
     }
        else
        {
          return writeCurBlock;
        }

}


RC appendEmptyBlock(SM_FileHandle *fHandle)
{
   char *presentFile = fHandle->fileName;
  int everyPage;
   if (fHandle == 0)
    return RC_FILE_HANDLE_NOT_INIT;

 
  if (isFilePresent(presentFile))
  {
    
    
    
    fseek((fopen(presentFile, "r+")), 0, SEEK_END);

    
    
          everyPage=0;
          while(everyPage < PAGE_SIZE)
          {
              fwrite("\0", 1, 1, (fopen(presentFile, "r+")));
              fseek(present_pg_ptr, 0, SEEK_END);
              everyPage++;
          }

    fHandle->totalNumPages = (ftell(fHandle->mgmtInfo ) / PAGE_SIZE);

    return RC_OK;
  }

  return RC_FILE_NOT_FOUND;
}



RC ensureCapacity(int finalpages, SM_FileHandle *fHandle)
{
  
  if (isFilePresent(fHandle->fileName))
  {
     while(fHandle->totalNumPages > finalpages)
    {
      return RC_OK;
    }
   
    while (fHandle->totalNumPages < finalpages)
    {
      
        appendEmptyBlock(fHandle); 
     
    }
   while(fHandle->totalNumPages != finalpages)
   {
     appendEmptyBlock(fHandle); 
   }

  }
  else
  {
     return RC_FILE_NOT_FOUND;
  }
 
  while(fHandle == 0)
{
  return RC_FILE_HANDLE_NOT_INIT;

}


}
