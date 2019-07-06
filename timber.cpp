// Library imports
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
  // Set the video mode to 1920x1080, the dimension of our screen.
  VideoMode vm(1920, 1080);
  // Create a render window that will render our videomode
  RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

  // Create our texture for loading imgs into the GPU
  // Add the tree texture
  // Bee texture
  // Create sprites for both the background and the tree.

  // Load the background texture and load it's sprite on screen
  Texture backgroundTexture;
  Sprite backgroundSprite;
  backgroundTexture.loadFromFile("graphics/background.png");
  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setPosition(0, 0);

  // Create the tree texture and load it's sprite on screen
  Texture treeTexture;
  Sprite treeSprite;
  treeTexture.loadFromFile("graphics/tree.png");
  treeSprite.setTexture(treeTexture);
  treeSprite.setPosition(810, 0);
  // Set the initial positions for the sprites
  // relative to the window.

  Texture beeTexture;
  Sprite beeSprite;
  beeTexture.loadFromFile("graphics/bee.png");
  beeSprite.setTexture(beeTexture);
  beeSprite.setPosition(0, 800);

  // Bee variables
  bool beeActive = false;
  float beeSpeed = 0.0f;

  Texture cloudTexture;
  cloudTexture.loadFromFile("graphics/cloud.png");

  Sprite cloudSprite1;
  Sprite cloudSprite2;
  Sprite cloudSprite3;

  cloudSprite1.setTexture(cloudTexture);
  cloudSprite2.setTexture(cloudTexture);
  cloudSprite3.setTexture(cloudTexture);

  cloudSprite1.setPosition(0, 0);
  cloudSprite2.setPosition(0, 250);
  cloudSprite3.setPosition(0, 500);

  float cloud1Speed = 0.0f;
  float cloud2Speed = 0.0f;
  float cloud3Speed = 0.0f;

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

    // Draw the clouds
    window.draw(cloudSprite1);
    window.draw(cloudSprite2);
    window.draw(cloudSprite3);

    // Draw the trees
    window.draw(treeSprite);

    // Draw the bee
    window.draw(beeSprite);
    // Display everything drawn
    window.display();
  }
  return 0;
}
