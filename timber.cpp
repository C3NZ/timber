// Library imports
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
  // Set the video mode to 1920x1080, the dimension of our screen.
  VideoMode vm(1920, 1080);
  // Create a render window that will render our videomode
  RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

  // Create our texture for loading imgs into the GPU
  Texture backgroundTexture;
  // Create a sprite
  Sprite backgroundSprite;

  // Load the texture from the png file
  backgroundTexture.loadFromFile("graphics/background.png");
  // Associate the sprite to the texture
  backgroundSprite.setTexture(backgroundTexture);
  // Set the sprites position relative to the inside of the window
  backgroundSprite.setPosition(0, 0);

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

    // Draw the background sprite
    window.draw(backgroundSprite);

    // Display everything drawn
    window.display();
  }
  return 0;
}
