#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

const uint SHM_TABLE_SIZE = 64;

struct {
  struct spinlock lock;
  struct shm_page {
    uint id;
    char *frame;
    int refcnt;
  } shm_pages[SHM_TABLE_SIZE];
} shm_table;

void shminit() {
  int i;
  initlock(&(shm_table.lock), "SHM lock");
  acquire(&(shm_table.lock));
  for (i = 0; i< SHM_TABLE_SIZE; i++) {
    shm_table.shm_pages[i].id =0;
    shm_table.shm_pages[i].frame =0;
    shm_table.shm_pages[i].refcnt =0;
  }
  release(&(shm_table.lock));
}

int shm_open(int id, char **pointer) {

//you write this
	acquire(&(shm_table.lock));
	for(i = 0; i < SHM_TABLE_SIZE; ++i){
	   if(shm_table.shm_pages[i].id == id){
	      mappages(myproc()->pg_dir, PGROUNDUP(myproc()->sz), PGSIZE, V2P(shm_table.shm_pages[i].frame), PTE_W|PTE_u);
	      shm_table.shm_pages[i].refcnt += 1;
	      *pointer = (char *)PGROUNDUP(myproc()->sz);
	      myproc()->sz += PGSIZE;
	      release(&(shm_table.lock));
	      return 0;
	   }
	}
	
	for(i = 0; i < SHM_TABLE_SIZE; ++i){
	   if(shm_table.shm_pages[i].id == 0){
	      shm_table.shm_pages[i].id = id;
	      shm_table.shm_pages[i].frame = kmalloc(PGSIZE, );
	      shm_table.shm_pages[i].refcnt = 1;
	   }
	}

	release(&(shm_table.lock));





	return 0; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
//you write this too!
	return 0; //added to remove compiler warning -- you should decide what to return
}
