Main is the starting point, which creates the screen stack and render window. Main game states are stored in the screen stack, such as GameScreen or MainMenuScreen. Each screen is sent the window to enable the screen to draw objects. The program is locked to that screen state until another screen state is selected or -1 is returned.

The current version of the program only uses the GameScreen to test the engine. GameScreen creates a Level object. Sfml events (such as keyboard presses and mouse clicks) are processed. GameScreen will loop, updating and drawing all of the game objects.

Level defines the area where all game objects will be stored and position. The level also generates Planet objects using the poisson disk sampling algorithm.