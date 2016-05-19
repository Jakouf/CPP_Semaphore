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
