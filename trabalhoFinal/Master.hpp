#pragma once

#include "Worker.hpp"

class Master : public Worker
{
private:
  /* Data */
public:
  Master(int, int);
  ~Master();

  void Run();

  void SigHandler(int);

  static int oi;

  static int IsMaster(int rank) { return rank == 0; }
};
