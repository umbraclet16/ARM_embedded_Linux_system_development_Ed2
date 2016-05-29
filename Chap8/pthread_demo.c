// pthread_demo.c                                                                          
#include <pthread.h>                                                                       
#include <unistd.h>                                                                        
#include <stdio.h>                                                                         
#include <stdlib.h>                                                                        
                                                                                           
void* mid_thread(void *arg);			// mid线程声明                                           
void* term_thread(void *arg);		// term线程声明                                            
                                                                                           
int main()                                                                                 
{                                                                                          
  pthread_t mid_tid, term_tid;			// 存放线程id                                          
                                                                                           
  if (pthread_create(&mid_tid, NULL, mid_thread, NULL)) {		// 创建mid线程                 
    perror("Create mid thread error!");                                                    
    return 0;                                                                              
  }                                                                                        
                                                                                           
  if (pthread_create(&term_tid, NULL, term_thread, (void*)&mid_thread)) {		// 创建term线程
    perror("Create term thread fail!\n");                                                  
    return 0;                                                                              
  }                                                                                        
                                                                                           
  if (pthread_join(mid_tid, NULL)) {		// 等待mid线程结束                                 
    perror("wait mid thread error!");                                                      
    return 0;                                                                              
  }                                                                                        
                                                                                           
  if (pthread_join(term_tid, NULL)) {		// 等待term线程结束                                
    perror("wait term thread error!");                                                     
    return 0;                                                                              
  }                                                                                        
                                                                                           
  return 0;                                                                                
}                                                                                          
                                                                                           
void* mid_thread(void *arg)				// mid线程定义                                           
{                                                                                          
  int times = 0;                                                                           
  printf("mid thread created!\n");                                                         
  while(1) {							// 不断打印等待的次数，间隔2秒                                   
    printf("waitting term thread %d times!\n", times);                                     
    sleep(2);                                                                              
    times++;                                                                               
  }                                                                                        
}                                                                                          
                                                                                           
void* term_thread(void *arg)			// term线程定义                                          
{                                                                                          
  pthread_t *tid;                                                                          
  printf("term thread created!\n");                                                        
  sleep(2);                                                                                
  if (NULL!=arg) {                                                                         
    tid = (pthread_t*)arg;                                                                 
    pthread_cancel((*tid));				// 如果线程id合法，结束线程                              
  }                                                                                        
}                                                                                          
