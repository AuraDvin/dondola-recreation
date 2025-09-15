# Dondola Game Recreation 
This was a 3rd Year High-school project for C++ that I made, find it [here](https://github.com/AuraDvin/Dondola-Game-original).  
I thought the code was generally pretty bad and ugly so I decided to recreate it now with my "more modern" knowledge of C++ but also programming in general 
# Disclamer 
As this is a project for fun and nothing serious   
it's unlikely to be made in a quick manner or with high quality.  
It's only a thing I want to do to see if I've actually improved as a programmer. 
## Requirements
Requires CMake 4, and an internet connection as it fetches SFML from github using FetchContent.  
As this was the reccomended sfml inclusion according to their [github page](https://github.com/SFML/cmake-sfml-project/blob/master/README.md#upgrading-sfml).   
If you know how to compile sfml and then compile the game on top of it, you do you :)
## How to build
All the steps are in `CMakeLists.txt`. But there is also the `build.sh` script you can use to do it automatically.   
```bash
mkdir build
cd build
cmake ..
make
```
and then you can run the game with (still inside the build directoy)
```bash
./dondolagame_recreation 
```
These commands are all in `build.sh` script. Tho I dunno if it works on windows.

# Todo: 
- [x] Game pauses
- [ ] Multiple scenes (front screen, credits, main game, end-game/highscore, settings)
- [ ] HUD 
  - [ ] Health
  - [ ] Enemy count
  - [ ] Timer
  - [ ] Maybe pointer to closest enemy
  - [ ] Pause menu
- [ ] Camera
  - [x] Follows player
  - [ ] Smooth animation for better feel  
- [ ] Player
  - [x] Moves left and right at an angle
  - [ ] Collides with enemes, losing health
  - [x] Better movement (smooth rather than staggering)
  - [ ] ANIMATIONS PLEASE
- [ ] Enemies
  - [ ] Multiple types
  - [ ] Spawning in allowed areas *currently untested*
  - [x] Set direction
  - [x] Deleted when out of bounds/camera view
  - [ ] ANIMATIONS PLEASE
- [ ] Highscore
  - [ ] Save and write scores to a binary file that can be read on game over screen
- [ ] Background
## Movement 
Changed from moving at a fixed rate on update to a velocity/acceleration type so it feels much better, tho haven't added the angle of the actual line for the dondola 
## Enemies 
Originally were just rockets falling from the top, but planning on making them able to spawn on any side and possibly different kind of movement (say go up, turn around and back down) 
## Input 
I am planning on making the game playable with Keyboards and some interaction with the mouse (i. e. buttons for menus) and possibly controller support 
