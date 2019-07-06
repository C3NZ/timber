// Library imports
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
  // Set the video mode to 1920x1080, the dimension of our screen.
  VideoMode vm(1920, 1080);
  // Create a render window that will render our videomode
  RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

  // The main while loop
  while (window.isOpen()) {
    /*
     * Handle player input
     */

    // Checking to see if the user clicks on the escape key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

    /*
     * Update the scene
     */

    /*
     * Draw the scene
     */
    // Clear the display
    window.clear();
    window.clear();
    // Display everything drawn
    window.display();
  }
  return 0;
}
