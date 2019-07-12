// Import SFML graphics
#include <SFML/Graphics.hpp>
// Import string streams
#include <sstream>

using namespace sf;

// The function prototype
void updateBranches(int seed);

// The number of branches our tree will have
const int NUM_BRANCHES = 6;

// All of our branches held within a sprite array
Sprite branches[NUM_BRANCHES];

// Sides that the player or branch is on
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main() {

  // Seed the random number generator
  srand((int)time(0));

  // Set the video mode to 1920x1080, the dimension of our screen.
  VideoMode vm(1920, 1080);
  // Create a render window that will render our videomode
  RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

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

  // Setup the bee texture and load it's sprite on screen.
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

  // Setup the time bar to let the player know how much time is left.
  RectangleShape timeBar;
  float timeBarStartWidth = 400;
  float timeBarHeight = 80;
  timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
  timeBar.setFillColor(Color::Red);
  timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

  // Setup the remaining time
  Time gameTimeTotal;
  float timeRemaining = 6.0f;
  float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

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

  Texture branchTexture;
  branchTexture.loadFromFile("graphics/branch.png");

  // Initialize the branches
  for (int i = 0; i < NUM_BRANCHES; i++) {
    branches[i].setTexture(branchTexture);
    branches[i].setPosition(-2000, -2000);
    // Sets the branches origin to dead center, for
    // rotatating it without changing it's position.
    branches[i].setOrigin(220, 20);
  }

  // Setup the player texture and sprites.
  Texture playerTexture;
  Sprite playerSprite;
  playerTexture.loadFromFile("graphics/player.png");
  playerSprite.setTexture(playerTexture);
  playerSprite.setPosition(580, 720);

  // The side in which the player starts on.
  side playerSide = side::LEFT;

  Texture ripTexture;
  Sprite ripSprite;
  ripTexture.loadFromFile("graphics/rip.png");
  ripSprite.setTexture(ripTexture);
  ripSprite.setPosition(600, 860);

  Texture axeTexture;
  Sprite axeSprite;
  axeTexture.loadFromFile("graphics/axe.png");
  axeSprite.setTexture(axeTexture);
  axeSprite.setPosition(700, 830);

  const float AXE_POSITION_LEFT = 700;
  const float AXE_POSITION_RIGHT = 1075;

  Texture logTexture;
  Sprite logSprite;
  logTexture.loadFromFile("graphics/log.png");
  logSprite.setTexture(logTexture);
  logSprite.setPosition(810, 720);

  bool logActive = false;
  float logSpeedX = 1000;
  float logSpeedY = -1500;

  while (window.isOpen()) {
    /*
     * Handle player input
     */

    // Checking to see if the user clicks on the escape key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

    // Handle pausing and unpausing the game.
    if (Keyboard::isKeyPressed(Keyboard::Return)) {
      paused = !paused;

      // Reset the score and the time remaining when the user pauses
      score = 0;
      timeRemaining = 5;
    }

    /*
     * Update the scene
     */

    // Game must be unpaused in order to issue updates
    if (!paused) {

      Time dt = clock.restart();

      // Update the time bar that shows the player how much time is left.
      timeRemaining -= dt.asSeconds();
      float newBarWidth = timeBarWidthPerSecond * timeRemaining;
      timeBar.setSize(Vector2f(newBarWidth, timeBarHeight));

      if (timeRemaining <= 0.0f) {
        paused = true;

        messageText.setString("Out of time!!");

        // Grab the Rectangle bounding box of the text and compute the new
        // origins.
        FloatRect messageRect = messageText.getLocalBounds();
        float xOrigin = messageRect.left + messageRect.width / 2.0f;
        float yOrigin = messageRect.top + messageRect.height / 2.0f;

        // Update the origin and position of the text
        messageText.setOrigin(xOrigin, yOrigin);
        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
      }

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

    // Iterate through the branches and update them.
    for (int i = 0; i < NUM_BRANCHES; i++) {
      float height = i * 150;
      if (branchPositions[i] == side::LEFT) {
        branches[i].setPosition(610, height);
        branches[i].setRotation(180);
      } else if (branchPositions[i] == side::RIGHT) {
        branches[i].setPosition(1330, height);
        branches[i].setRotation(0);
      } else {
        branches[i].setPosition(3000, height);
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

    // Draw the branches for the treea
    for (int i = 0; i < NUM_BRANCHES; i++) {
      window.draw(branches[i]);
    }

    // Draw the trees
    window.draw(treeSprite);

    // Draw the player
    window.draw(playerSprite);

    // Draw the axe
    window.draw(axeSprite);

    // Draw the log sprite
    window.draw(logSprite);

    // draw the rip sprite
    window.draw(ripSprite);

    // Draw the bee
    window.draw(beeSprite);

    // Draw the score
    window.draw(scoreText);

    window.draw(timeBar);

    // If the game is paused, draw the pause message
    if (paused) {
      window.draw(messageText);
    }

    // Display everything drawn
    window.display();
  }
  return 0;
}

void updateBranches(int seed) {
  /*
   *   Update the branches accordingly
   */

  // Move all the branches down one place
  for (int i = NUM_BRANCHES - 1; i > 0; i--) {
    branchPositions[i] = branchPositions[i - 1];
  }

  // Seed our random number generator and generate a random number
  srand((int)time(0) + seed);
  int randomNum = (rand() % 5);

  // Choose the position of the highest branch
  switch (randomNum) {
  case 0:
    branchPositions[0] = side::LEFT;
    break;
  case 1:
    branchPositions[0] = side::RIGHT;
    break;
  default:
    branchPositions[0] = side::NONE;
    break;
  }
}
