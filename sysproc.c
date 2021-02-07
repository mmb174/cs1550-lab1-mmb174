#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


// this will return the number of times the referenced System
// call was invoked by the calee (calling process)
// when passed a valid system call number as an argument
// the above captioned implentation description was paraphrased by me
// from the  CS/COE 1550 Lab 1 instructions provided to me.


//

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0) //figure out what argin does
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


    //moving back here because I don't know what else to do
// this will return the number of times the referenced System
// call was invoked by the calee (calling process)
// when passed a valid system call number as an argument
// the above captioned implentation description was paraphrased by me
// from the  CS/COE 1550 Lab 1 instructions provided to me.
//moving here so it can use syscalls
//this function gets the count and returns it
int sys_getcount(void)
  {
    int n;
    struct proc *curproc = myproc(); //get currect process
    n  = argint(0,&n); //holds the param number
    if((n > 0) && (n < sizeof curproc->syscount)) //if its a syscall valid in range number
    {
      return curproc->syscount[n]; //stores the syscount in count
    } 
    else 
    {
    return -1; //returns number of times sycall was invoked, -1 if invalid syscall
    }
  
  
  }
