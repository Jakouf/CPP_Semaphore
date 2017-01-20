//MIT License
//
//  Created by Matthias Uttendorfer on 19/05/16.
//  Copyright © 2016 Matthias Uttendorfer. All rights reserved.
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


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
  std::atomic<long> s_count;
};

namespace dispatch {
  
  auto semaphore_signal(dispatch::semaphore_c& semaphore) -> long
  {
    if (--semaphore.s_count < 0) {
      semaphore.cv.notify_one();
    }
    return semaphore.s_count;
  }
  
  auto semaphore_wait(dispatch::semaphore_c& semaphore) -> void {
    
    std::unique_lock<std::mutex> lk(semaphore.locker);
    semaphore.cv.wait(lk);
  }


}
