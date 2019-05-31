#include "Worker.hpp"

#include "Master.hpp"

#include <iostream>

Worker::Worker(int _size, int _rank) : rank(_rank), size(_size)
{
}

Worker::~Worker()
{
}

void Worker::Run() {
  std::cout << "Worker with rank " << this->rank << " out of " << this->size << "\n";

  while (true) {
    if (Master::oi != 0) {
      std::cout << "Killing worker" << std::endl;
      for (auto i = 0; i < 1000; i++) {
        std::cout << i << ' ';
      }
      break;
    }
  }
}