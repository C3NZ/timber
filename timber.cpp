// Import SFML graphics
#include <SFML/Graphics.hpp>
// Import string streams
#include <sstream>

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

  // Variable for keeping track of the time.
  Clock clock;

  // Keeping track of whether the game is running or not.
  bool paused = true;

  int score = 0;

  Text messageText;
  Text scoreText;

  // Create our font
  Font font;
  font.loadFromFile("fonts/ARCADECLASSIC.TTF");

  // Set the font resource to the font that we're using.
  messageText.setFont(font);
  scoreText.setFont(font);

  // Set the initial string values of both pieces of text.
  messageText.setString("Press enter to start!");
  scoreText.setString("Score = 0");

  // Set the font size of both pieces of text.
  messageText.setCharacterSize(75);
  scoreText.setCharacterSize(100);

  // Set the color of both pieces of text.
  messageText.setFillColor(Color::White);
  scoreText.setFillColor(Color::White);

  FloatRect textRect = messageText.getLocalBounds();

  // Set the texts origin to be the center of the text
  float textX = textRect.left + textRect.width / 2.0f;
  float textY = textRect.top + textRect.height / 2.0f;
  messageText.setOrigin(textX, textY);

  // Set the position to be the middle of the screen.
  messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

  scoreText.setPosition(20, 20);
  while (window.isOpen()) {
    /*
     * Handle player input
     */

    // Checking to see if the user clicks on the escape key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

    // Handle unpausing the game.
    if (Keyboard::isKeyPressed(Keyboard::Return)) {
      paused = false;
    }

    /*
     * Update the scene
     */

    // Game must be unpaused in order to issue updates
    if (!paused) {

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
        // Obtain and set the 1st clouds horizontal speed
        srand((int)time(0) * 10);
        cloud1Speed = (rand() % 200);

        // Obtain and set the 1st clouds height
        srand((int)time(0) * 10);
        float height = (rand() % 150);
        cloudSprite1.setPosition(-200, height);
        cloud1Active = true;
      } else {
        // Update the position of the cloud based on it's speed
        float newX =
            cloudSprite1.getPosition().x + (cloud1Speed * dt.asSeconds());

        cloudSprite1.setPosition(newX, cloudSprite1.getPosition().y);

        // reset the first cloud
        if (cloudSprite1.getPosition().x > 1920) {
          cloud1Active = false;
        }
      }

      if (!cloud2Active) {
        // Obtain and set the speed of the 2nd cloud sprite
        srand((int)time(0) * 20);
        cloud2Speed = (rand() % 200);

        // Obtain and set the height of the 2nd cloud sprite
        srand((int)time(0) * 20);
        float height = (rand() % 300) - 150;
        cloudSprite2.setPosition(-200, height);
        cloud2Active = true;
      } else {
        // Update the position of the cloud based on it's speed
        float newX =
            cloudSprite2.getPosition().x + (cloud2Speed * dt.asSeconds());

        cloudSprite2.setPosition(newX, cloudSprite2.getPosition().y);

        // Reset the second cloud
        if (cloudSprite2.getPosition().x > 1920) {
          cloud2Active = false;
        }
      }

      if (!cloud3Active) {
        // Obtain and set the speed of the 3rd cloud sprite
        srand((int)time(0) * 30);
        cloud3Speed = (rand() % 200);

        // Obtain and set the height of the 3rd cloud sprite
        srand((int)time(0) * 30);
        float height = (rand() % 450) - 150;
        cloudSprite3.setPosition(-200, height);
        cloud3Active = true;
      } else {
        // Update the position of the cloud based on it's speed
        float newX =
            cloudSprite3.getPosition().x + (cloud3Speed * dt.asSeconds());

        cloudSprite3.setPosition(newX, cloudSprite3.getPosition().y);

        // reset the third cloud
        if (cloudSprite3.getPosition().x > 1920) {
          cloud3Active = false;
        }
      }
    }

    // Update the score
    std::stringstream ss;
    ss << "Score = " << score;
    scoreText.setString(ss.str());
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
