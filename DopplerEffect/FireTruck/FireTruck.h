#include <raylib.h>

class FireTruck
{
public:
  FireTruck();
  void Draw();
private:
  int x, y;
  Texture2D sprite;
};