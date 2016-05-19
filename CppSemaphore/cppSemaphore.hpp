//
//  cppSemaphore.hpp
//  CppSemaphore
//
//  Created by Matthias Uttendorfer on 19/05/16.
//  Copyright © 2016 Matthias Uttendorfer. All rights reserved.
//

#include <stdio.h>
#include <cstdint>
#include <mutex>
#include <condition_variable>



namespace dispatch
{
  class semaphore_c;
}

class dispatch::semaphore_c
{
public:
  semaphore_c(long s) {
    s_count = s;
  }
  
  std::condition_variable cv;
  std::mutex locker;
  long s_count;
};

namespace dispatch {
  
  auto semaphore_signal(dispatch::semaphore_c& semaphore) -> long
  {
    semaphore.s_count--;
    
    if (semaphore.s_count < 0) {
      semaphore.cv.notify_one();
    }
    return semaphore.s_count;
  }
  
  auto semaphore_wait(dispatch::semaphore_c& semaphore) -> void {
    
    std::unique_lock<std::mutex> lk(semaphore.locker);
    semaphore.cv.wait(lk);
  }


}