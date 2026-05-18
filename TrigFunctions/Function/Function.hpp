#pragma once

#include <deque>
#include "constants.h"

enum FunctionType
{
  Vertical,
  Horizontal
};

class Function
{
public:
  Function(FunctionType, int origin);
  std::deque<int> GetPoints()    const;
  int             GetOrigin()    const;
  FunctionType GetFunctionType() const;
  void Update(int newY);
private:
  FunctionType type;
  int origin;
  std::deque<int> points;
};