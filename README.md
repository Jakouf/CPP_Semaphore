# CPP_Semaphore
This project implements a semaphore type platform independent in C++. Highly influenced by lib dispatch 

### Example:

  A sample application can be found in sample.cpp. 
  
### Usage:
  
  ```C++
  
  dispatch::semaphore_c(long s)
  
  ```
  
  creates a new semaphore. the parameter s indicates how many signals you have to invoke 
  until you unblock the blocked thread.
  
  
  You can block the current thread by calling:
  
  ```C++
  
  dispatch::semaphore_wait(dispatch::semaphore semaphore)
  
  ```
  
  To invoke a signal on the semaphore call:
  
  ```C++
  
  dispatch::semaphore_signal(dispatch::semaphore_c& semaphore)
  
  ```
  
