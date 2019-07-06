// Library imports
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {

  // Seed the random number generator
  srand((int)time(0));

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

  // Create the cloud texture
  Texture cloudTexture;
  cloudTexture.loadFromFile("graphics/cloud.png");

  // Create the cloud sprites, set them to all be of one texture
  // and then set their positions
  Sprite cloudSprite1;
  Sprite cloudSprite2;
  Sprite cloudSprite3;
  cloudSprite1.setTexture(cloudTexture);
  cloudSprite2.setTexture(cloudTexture);
  cloudSprite3.setTexture(cloudTexture);
  cloudSprite1.setPosition(0, 0);
  cloudSprite2.setPosition(0, 250);
  cloudSprite3.setPosition(0, 500);

  // Cloud properties
  bool cloud1Active = false;
  bool cloud2Active = false;
  bool cloud3Active = false;
  float cloud1Speed = 0.0f;
  float cloud2Speed = 0.0f;
  float cloud3Speed = 0.0f;

  Clock clock;

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
    Time dt = clock.restart();

    if (!beeActive) {
      // Seed the random number generator and then
      // generate the bees speed
      srand((int)time(0));
      beeSpeed = (rand() % 200) + 200;

      // Seed the random number generator again and then seed the bees height
      srand((int)time(0) * 10);
      float height = (rand() % 500) + 500;
      beeSprite.setPosition(2000, height);
      beeActive = true;
    } else {
      // Calculate the newX of the bee
      float newX = beeSprite.getPosition().x - (beeSpeed * dt.asSeconds());
      beeSprite.setPosition(newX, beeSprite.getPosition().y);

      // If the bee has made it to the other side of the screen,
      // the bee needs to be reset.
      if (beeSprite.getPosition().x < -100) {
        beeActive = false;
      }
    }

    if (!cloud1Active) {
      // Obtain and set the clouds horizontal speed
      srand((int)time(0) * 10);
      cloud1Speed = (rand() % 200);

      // Obtain and set the clouds height
      srand((int)time(0) * 10);
      float height = (rand() % 150);
      cloudSprite1.setPosition(-200, height);
      cloud1Active = true;
    } else {
      float newX =
          cloudSprite1.getPosition().x + (cloud1Speed * dt.asSeconds());

      cloudSprite1.setPosition(newX, cloudSprite1.getPosition().y);

      if (cloudSprite1.getPosition().x > 1920) {
        cloud1Active = false;
      }
    }
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
