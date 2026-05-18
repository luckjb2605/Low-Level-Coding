#include "Function/Function.hpp"

Function::Function(FunctionType type, int origin)
  : type(type), origin(origin)
{}
std::deque<int> Function::GetPoints()    const { return points; }
int Function::GetOrigin()                const { return origin; }
FunctionType Function::GetFunctionType() const { return   type; }
void Function::Update(int newY)
{
  if (points.size() >= FUNCTION_POINTS)
  {
    points.pop_back();
  }

  points.push_front(newY);
}