#include "Master.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int Master::oi = 0;

Master::Master(int size, int rank) : Worker(size, rank)
{

}

Master::~Master()
{

}

void Master::SigHandler(int s) {
  std::cout << "Got " << s << std::endl;
}

void Master::Run() {
  std::cout << "Master with rank " << this->rank << " out of " << this->size << "\n";

  while (true) {

    if (Master::oi != 0) {
      std::cout << "Saving..." << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << "Saved!" << std::endl;
      break;
    }
  }
}