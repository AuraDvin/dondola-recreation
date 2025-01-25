# Dondola Game Recreation 
This was a 3rd Year High-school project for C++ that I made. 
I thought the code was generally pretty bad and ugly so I decided to recreate it now with my "more modern" knowledge of C++ but also programming in general 
# Disclamer 
As this is a project for fun and nothing serious it's unlikely to be made in a quick manner or with high quality. It's only a thing I want to do to see if I've actually improved as a programmer. 
## Requirements
This uses SFML 3.0.0 with MINGW (gcc 14.2.0) for Windows. Make sure it's the exact version since otherwise SFML gets really mad.
Maybe I'll also make a version for linux/unix (TBD). 
## How to build 
This time the project is written in CLion instead of Visual Studio. So hopefully no issues there, just open the project and build.
I am thinking of adding files that will allow building with VSC or just no IDE too.
All the steps are in `CMakeLists.txt`, for VSC I could make settings, tasks and launch files too that do the same thing. 
And possibly just some kind of script that can build the project with just one click... tho I'll think about it.
# Todo: 
- [ ] Camera
  - [x] Follows player
  - [ ] Smooth animation for better feel  
- [ ] Player
  - [x] Moves left and right at an angle
  - [ ] Avoids enemies
  - [x] Better movement (smooth rather than staggering)
- [ ] Enemies
  - [ ] Multiple types?
  - [ ] Spawning in allowed areas *currently untested*
  - [x] Set direction
  - [ ] Deleted when out of bounds/camera view
- [ ] Highscore
  - [ ] Save and write scores to a binary file that can be read on game over screen
## Movement 
Changed from moving at a fixed rate on update to a velocity/acceleration type so it feels much better, tho haven't added the angle of the actual line for the dondola 
## Enemies 
Originally were just rockets falling from the top, but planning on making them able to spawn on any side and possibly different kind of movement (say go up, turn around and back down) 
## Input 
I am planning on making the game playable with Keyboards and some interaction with the mouse (i. e. buttons for menus) and possibly controller support 
