/*
 * mm_alloc.c
 *
 * Stub implementations of the mm_* routines. Remove this comment and provide
 * a summary of your allocator's design here.
 */

#include "mm_alloc.h"
#include<sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
/* Your final implementation should comment out this macro. */
#define MM_USE_STUBS
#define block_size sizeof(s_block_ptr)
s_block_ptr last=NULL;
//start=(void*)sbrk(0);
void* mm_malloc(size_t size)
{
  
    void* breakPoint=sbrk(size);
    struct rlimit *resourceLimit=breakPoint;
    if(resourceLimit!=(void*)-1)
    {
      if (getrlimit(size,breakPoint)==0)
	{
	  
	  last=extend_heap(last,size);
	  return breakPoint;
	        
	}
      else 
	{
	  
	  printf("Couldn't get limit.\n");
	}
      
   
    }
  else
    {
      return NULL;
    }
  
  /*  #ifdef MM_USE_STUBS
    return calloc(1, size);
#else
#error Not implemented.
#endif*/
}

void* mm_realloc(void* ptr, size_t size)
{
  mm_free(ptr);
  return mm_malloc(size);
	  
  /*#ifdef MM_USE_STUBS
    return realloc(ptr, size);
#else
#error Not implemented.
#endif*/
}

void mm_free(void* ptr)
{
  s_block_ptr block=get_block(ptr);
  s_block_ptr block2=get_block(sbrk(0));
  if ( block>block2)
    {
      //printf("true %d %d.\n", block->prev, block2->prev);
      block->free=1;
    }
}
s_block_ptr get_block(void *p)
{
  /// printf("hi.\n");
  if (last==NULL)
    {
      printf("it is definetly not there.\n");
    }
  else
    {
  char *tmp;
  tmp=p;
  return(p=tmp -=block_size);
    }
}
s_block_ptr extend_heap(s_block_ptr last1,size_t size)
{
  s_block_ptr block=sbrk(0);
  if (sbrk(block_size+size)!=(void*)-1)
    {
      
      block->size=size;
      block->prev=last1;
      block->ptr=block->data;
      block->next=NULL;
      block->free=0;
      if (last1==NULL)
	{
	  last=block;
	}
      else if (last1->next==NULL)
	{
	 
	  last1->next=block;
	 
	}
      //printf("success\n");
      return block;
    }
    else
      {
	return NULL;
      }
}
