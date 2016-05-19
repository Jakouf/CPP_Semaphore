//
//  main.cpp
//  CppSemaphore
//
//  Created by Matthias Uttendorfer on 19/05/16.
//  Copyright © 2016 Matthias Uttendorfer. All rights reserved.
//

#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include "cppSemaphore.hpp"

class asyncClass {
public:
  asyncClass() {
    
  }
  
  std::function<void()> callback;
  
  auto asyncMethod() -> void {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    callback();

  }
};

asyncClass foo;

int main(int argc, const char * argv[]) {
  
  long count = 3;
    printf("\n\n\n semaphore create \n\n\n");
  dispatch::semaphore_c sem(count);
  
  std::thread asyncWorker(&asyncClass::asyncMethod , &foo);
  
  std::mutex mutex;
  
  foo.callback = [&] {
    while (count >= 0) {
      dispatch::semaphore_signal(sem);
      mutex.lock();
      std::cout << "signal " << count << std::endl;
      count--;
      mutex.unlock();

    }
  };
  
  printf("\n\n\n semaphore wait \n\n\n");
  dispatch::semaphore_wait(sem);
  asyncWorker.join();
  printf("\n\n\n back on main !!!");
  
}
