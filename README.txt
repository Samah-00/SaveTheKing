---------------------------------------------------------------------------------------------------------
------------------------------------- OOP1 Project - Save The King --------------------------------------
---------------------------------------------------------------------------------------------------------
------------------------------------------- Students and IDs -------------------------------------------- 
-------- Samah Rajabi (student number: 211558556) & Saja Abu Maizar (student number: 208072371) ---------
---------------------------------------------------------------------------------------------------------
----------------------------------------  General Description  ------------------------------------------
---------------------------------------------------------------------------------------------------------
About the game:-
----------------
In the game, the player must bring the king to his throne -castle-.
The problem is that the king is limited in his abilities and can only move on empty tiles on the board.
Thus, The king is accompanied by his entourage that will clear the way for him and help him reach his
goal.
Characters:
-----------
The player has control over four characters:
 ● The King: he can walk on clear way and keys (but he can't take them),
   he can also travel through teleport cells. Lastly, he can enter his castle.
 ● The Mage: his special ability is to put out fire (by walking over them).
   He can walk on clear way, fire and keys.
   Finally, he can stand on teleport cells but can't travel through them.
 ● The Warrior: his special ability is to fight orcs (by walking over them).
   He can walk on clear ways, orcs and keys. He can also use teleport cells.
 ● The Thief: his special ability is to take a key and open a gate with it
   (keys appear on the board whenever the warrior kills an orc). Finally, He can use teleport cells.
   Note that the thief can carry only one key at a time.
Enemy and Obstacles:
--------------------
In addition to the fire, orces and gates, the king and his entourage will be met with moving ghosts
that will block their way. Each character has three lives, colliding with a ghost will decrease
a life from the character.
Presents:
---------
In the game there are five types of gifts:
1. Increase time gift: gives the player extra five seconds. All the characters can collect the gift by
   walking on it.
2. Decrease time gift: decreases five seconds from the timer. All the characters can collect the gift by
   walking on it.
3. Kill enemy gift: Kills all the goests of the level. All the characters can collect the gift by 
   walking on it.
4. Speed up gift: increases the speed of the enemy.
5. Healing kit gift: increases by one the number of the lives of the character that collects it.
Winning and Losing:
-------------------
The player wins the level when the king reaches his castle.
If one of the four characters runs out of lives or if the time is up, the player loses and replays
the level.
How to play:
------------
To move between the four characters, press the p key on the keyboard. The default character is the king,
(king --press p--> mage --press p--> warrior --press p--> thief --press p--> king again)
To move a character, press the arrows' keys on the keyboard.
---------------------------------------------------------------------------------------------------------
------------------------------------------------- Design ------------------------------------------------
---------------------------------------------------------------------------------------------------------
Home Page:
----------
The main starts the game by creating a HomeController object.
the HomeController creates a HomePage object that creates a background and buttons in the window.
Then in a while loop the homeController handles the moves and clickes on the HomePage window:
 ● when the user clickes the "help" button in HomePage, the controller creates a HelpController object
   that opens a Help window and present info about the characters and how to play the game.
 ● when the user clickes the "exit" button in HomePage, the controller exits the program.
 ● when the user clickes the "start" button in HomePage, the controller closes the window of HomePage
   and creates a Level object.
Levels and Board:
-----------------
In a for loop, the Level object starts new levels (NUM_OF_LEVELS times). For each level, it reads
a text file to calculate the size of the board and whether or not the level is time-limited.
Lastly, it creates a BoardController object. Using polymorphism a Board object is built from the
BoardController object.
The  Board object reads the map of the level from a text file and saves it in a vector.
The BoardController prints the board to the game window and handles the moves and procedure of the game.
It also creates a levelData object when it starts a level, the levelData object updates the info about
the current level such as the character that's moving, the timer and more.
Since the BoardController uses the members of the Board, it inherates from the Board to have
access to the Board's potected members.
Game Objects:
-------------
The base characters class is called GameObject, it has two children: MovingObject and StaticObject.
The c-tor of the GameObject class recieves a texture and turns it into a sprite protected member, it also
recieves the initial position of an object.
Classes of moving objects, i.g King and Enemy, inherate from the MovingObject class and use its functions
while still objects, i.g Wall and Gate, inherate from the StaticObject class (which is a virtual class).
The classes of moving objects handle the movments of the object according to the character's abilites.
---------------------------------------------------------------------------------------------------------
------------------------------------------- Adding New Levels -------------------------------------------
---------------------------------------------------------------------------------------------------------
creating a new level:
---------------------
The program reads a level from a text file that includes the following:
1. In the first line of the text file, write T if the level is time limited or F otherwise.
2. In the second line, write the time limit of the level (in seconds) if the level is time limited,
   otherwise leave the second line empty.
3. from the third line onward, draw the board of the game. Here is the characters dictionary:
   K - king
   M - mage
   W - warrior
   T - thief
   = - wall
   # - gate
   X - teleport cell [note that the program connects every consecutive pair of Xs together]
   @ - king's castle [chair]
   * - fire
   ! - orc
   ^ - ghost [dwarf]
   + - increase time present
   - - decrease time present
   / - kill all ghosts present
   $ - healing kit present
   S - speed up ghosts present
Naming a level file:
--------------------
The name of the level's file should be the number of the level, i.g: "1.txt" is the 1st level.
changing the number of levels:
------------------------------
By default, the game has three levels. When adding a new level, update the number of the levels
in the file "Number of levels.txt" in the resources repository.
---------------------------------------------------------------------------------------------------------
--------------------------------------------- List of Files ---------------------------------------------
---------------------------------------------------------------------------------------------------------
Source files:-
--------------
 ● main.cpp: gets the dimentions of the home page from the background image and starts the game by 
   creating a controller.
 ● HomePage.cpp: Opens a home page window, it contains functions that handle the clicks on its buttons.
 ● Controller.cpp: Handles the events of the HomePage window by calling for the relevent function when
   clicking on one of the three buttons in the window: Play, Help or Exit.
 ● Help.cpp: contains a c-tor and helper functions which initialize the sound, text, images and button
   of the help window.
 ● HelpController.cpp: handles the events of the help window and opens info windows to show more
   information about a character.
 ● Level.cpp: optains the number of levels, runs the level in a for loop, for each level: it reads
   whether its time-bounded or not and its size then creates a board controller for it. 
 ● Board.cpp: reads the level's board, creates an object for each character on the board and saves
   the objects in a vector of vectors of unique  pointers to GameObjects.
 ● Boardontroller.cpp: opens a window for the level and handles the events on it, draws the game's board,
   creates and calls for levelData to update the level's info, shows the result of the level at the end
   of it, recieves data from the character's move functions and updates the board in accordance.
 ● levelData.cpp: for each level, a levelData object is created to initialize, update and draw the data
   of the level under the board on the window. 
 ● MovingObject.cpp: decides the direction of the moving objects according to the keyboard's keys,
   it also returns a direction or a position of a movung object.
 ● Enemy.cpp: creates an enemy object, moves it and updates its direction.
 ● King.cpp: creats a king, handles his moves and changes his image according to his movement direction.
 ● Mage.cpp: creats a mage, handles his moves and changes his image according to his movement direction.
 ● Warrior.cpp: creats a warrior, handles his moves and changes his image according to his move direction.
 ● Thief.cpp: creats a thief, handles his moves and changes his image according to his movement direction.
Headers:-
---------
 ● GameObject.h: contains a c-tor that recieves a texture, and two flaots which it saves as the sprite
   image and the position of the object.
 ● StaticObject.h: uses the GameObject class.
 ● Fire.h: creates a fire object using the c-tor of StaticObjects, draws fire on the window and can return
   the image when needed.
 ● Gate.h: creates a gate object using the c-tor of StaticObjects, draws a gate on the window and can
   return the image when needed.
 ● TeleportCell.h: creates a gate object using the c-tor of StaticObjects, draws a TeleportCell on 
   the window and can return the image when needed.
 ● UnlockedGate.h: creates an opened gate object using the c-tor of StaticObjects, draws an opened gate
   on the window and can return the image when needed.
 ● Wall.h: creates a wall object using the c-tor of StaticObjects, draws a wall on the window and can
   return the image when needed.
 ● Key.h: creates a key object using the c-tor of StaticObjects, draws a key on the window and can
   return the image when needed.
 ● Orc.h: creates a orc object using the c-tor of StaticObjects, draws an orc on the window and can
   return the image when needed.
 ● chair.h: creates a king's chair [a castle in our game] using the c-tor of StaticObjects, draws 
   a chair on the window and can return the image when needed.
 ● Present.h: creates a present object using the c-tor of StaticObjects, draws a present on the window
   and can return the image when needed.
 ● DecreaseTimePresent.h: creates a decrease time present using the Present c-tor, draws  a present on
   the window and can return the image when needed.
 ● IncreaseTimePresent.h: creates an increase time present using the Present c-tor, draws  a present on
   the window and can return the image when needed.
 ● executeEnemyPresent.h: creates a "kill all enemy" present using the Present c-tor, draws  a present on
   the window and can return the image when needed.
 ● HealingKitPresent.h: creates a healing kit present using the Present c-tor, draws  a present on
   the window and can return the image when needed.
 ● SpeedUpPresent.h: creates a "speed enemy up" present using the Present c-tor, draws  a present on
   the window and can return the image when needed.
 ● More headers contains the classes, functions and enums that are used in the sources files.
Resources:
----------
Files of images, text or sound that are used in the game.
---------------------------------------------------------------------------------------------------------
-------------------------------------------- Data Structures --------------------------------------------
---------------------------------------------------------------------------------------------------------
Classes:
--------
All the game objects and controllers have classes of thier own. Some classes inherate from others:
Base Classes: Board, Help, GameObject.
Derived Classes: BoardController, HelpController, StaticObject, MovingObject.
Classes Derived from StaticObject: Present, Wall, Gate, etc...
Classes Derived from MovingObject: Enemy, King, Mage, etc...
Classes Derived from Present: HealingKitPresent, DecreaseTimePresent, etc...
Vectors:
--------
The board of each level is saved in a vector of vectors of unique  pointers to GameObjects. We also
used vectors to save smaller data such as the vector of moving enemies.
---------------------------------------------------------------------------------------------------------
------------------------------------------ Noteable Algorithms ------------------------------------------
---------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------
---------------------------------------------- Known Bugs -----------------------------------------------
---------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------
------------------------------------------- Additional Notes --------------------------------------------
---------------------------------------------------------------------------------------------------------
