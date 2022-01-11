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
Obstacles and Enemy:
--------------------
In addition to the fire, orces and gates, the king and his entourage will be met with moving ghosts
that will block their way. Each character has three lives, crashing into a ghost will decrease
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
the main starts the game by creating a HomeController object.
the HomeController creates a HomePage object, then in a while loop the controller handles the moves and
clickes on the window of the HomePage:
 ● when the user clickes the "help" button in HomePage, the controller creates a Help object that opens
   a Help window and present info about the characters and how to play the game.
 ● when the user clickes the "exit" button in HomePage, the controller exits the program.
 ● when the user clickes the "start" button in HomePage, the controller closes the window of HomePage
   and creates a Level object.
In a for loop, the Level object starts new levels (NUM_OF_LEVEL times). For each level, it reads
a text file to calculate the size of the board and whether or not the level is time-limited.
Lastly, it creates a BoardController object. Using polymorphism a Board object is built from the
BoardController object.
The Board object reads the map of the level from a text file and prints it [and more info? timer, levelData] 
to the window of the level. The BoardController object handles the moves and clickes on the window of
the board. Since the BoardController uses the members of the Board, it inherates from the Board to have
access to the Board's potected members.
**to be continued: types of GameObjects**
The base characters class is called GameObject, it has two children: MovingObject and StaticObject.
The c-tor of the GameObject class recieves a texture and turns it into a sprite protected member, it also
recieves the initial position of an object.
Classes of moving objects, i.g King and Enemy, inherate from the MovingObject class and use its functions
while still objects, i.g Wall and Gate, inherate from the StaticObject class (which is a virtual class).
The classes of moving objects controles the movment of the object according to the character's abilites.
** to be continued: **
** levelData, help and info **
---------------------------------------------------------------------------------------------------------
------------------------------------------- Adding New Levels -------------------------------------------
---------------------------------------------------------------------------------------------------------
creating a new level:
---------------------
The program reads a level from a text file that includes the following:
1. In the first line, write T if the level is time limited or F otherwise.
2. In the second line, write the time limit of the level (in seconds) if the level is time limited,
   otherwise leave the second line empty.
3. from the third line onward, draw the board of the game. Here is the characters dictionary:
   K - king
   M - mage
   W - warrior
   T - thief
   = - wall
   # - gate
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
----------------------------------
By default, the game has three levels. When adding a new level, update the number of the levels
in the file "Number of levels.txt" in the resources repository.
