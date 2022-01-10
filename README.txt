---------------------------------------------------------------------------------------------------------
------------------------------------- OOP1 Project - Save The King --------------------------------------
---------------------------------------------------------------------------------------------------------
------------------------------------------- Students and IDs -------------------------------------------- 
-------- Samah Rajabi (student number: 211558556) & Saja Abu Maizar (student number: 208072371) ---------
---------------------------------------------------------------------------------------------------------
----------------------------------------  General Description  ------------------------------------------
---------------------------------------------------------------------------------------------------------
About the game:
--------------
In the game, the player must bring the king to his throne -chair-.
The problem is that the king is limited in his abilities and can only move on empty tiles on the board.
Thus, The king is accompanied by his entourage that will clear the way for him and help him reach his
goal.
There are four characters that the player has control over:
 ● The King: he can walk on empty tiles, or keys tiles (but he can't take them),
   he can also travel through teleport cells. Lastly, he can sit on the throne.
 ● The Mage: his special ability is to put out fire (by walking over fire tiles).
   He can walk on empty tiles, fire tiles, and key tiles.
   Finally, he can stand on teleport cells but can't travel through them.
 ● The Warrior: his special ability is to fight the orcs (by walking over orcs tiles).
   He can walk on empty tiles, orcs tiles and keys tiles. He can also use teleport cells.
 ● The Thief: his special ability is to take a key (keys appear on the board whenever the warrior
   kills an orc) and open a gate with it. Finally, He can use teleport cells.
   Note that the thief can carry only one key at a time.
In addition to the fire, orces and gates, the king and his entourage will be met with moving goasts
that will block their way.
In the game there are three types of gifts:
1. Increase time gift: gives the player extra five seconds. All the characters can collect the gift by walking on it.
2. Decrease time gift: decreases five seconds from the timer. All the characters can collect the gift by walking on it.
3. Kill enemy gift: Kills all the goests of the level. All the characters can collect the gift by walking on it.
The player wins the level when the king reaches his throne.
How to play:
-----------
To move between the four characters, press the p key on the keyboard. The default character is the king,
(king --press p--> mage --press p--> warrior --press p--> thief --press p--> king again)
To move a character, press the arrows' keys on the keyboard.
In the game, some of the levels are limited by time so the king must reach his throne befor the time
is up, otherwise the player will have to restart the level.*
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
---------------------------------------------------------------------------------------------------------
** additional notes: how to add a new level, what to write to the text file of the level. **
