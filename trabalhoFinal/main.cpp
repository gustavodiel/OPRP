#include <iostream>

#define _XOPEN_SOURCE 700
#include <signal.h>
#undef _XOPEN_SOURCE

#include <stdlib.h>
#include <unistd.h>

#include <omp.h>
#include <mpi.h>

#include "Master.hpp"
#include "Worker.hpp"

int rank = 0;
int size = 0;

static Master* master;

void SetupSigAbort();
void SignalHandler(int);

int main(int argc, char** argv) {

  {
    struct sigaction sa;
    sa.sa_handler = SignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGKILL, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
  }

  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (Master::IsMaster(rank)) {
      master = new Master(size, rank);

      master->Run();
  } else {
      auto worker = new Worker(size, rank);
      worker->Run();
  }

  MPI_Finalize();
  return 0;
}

void SignalHandler(int signal) {
  std::cout << "Got " << signal << std::endl;

  Master::oi = 10;
}