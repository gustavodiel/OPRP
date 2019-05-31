#pragma once

class Worker
{
protected:
  int size, rank;
public:
  Worker(int, int);
  ~Worker();

  void Run();
};
