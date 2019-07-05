// Library imports
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
  // Set the video mode to 1920x1080, the dimension of our screen.
  VideoMode vm(1920, 1080);
  // Create a render window that will render our videomode
  RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
  return 0;
}
