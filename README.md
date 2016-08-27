OpenDK
======

Open source engine re-implementation of Dungeon Keeper (1997).

Development
-----------

 - C++
 - Linux (Debian)
 - SFML (2.1), GLEW (1,13), GLM (0.9.7.5), OpenGL (3.1)

Installing dependencies
-----------------------

    apt-get install libsfml-dev  # SFML - Simple Fast Media Library (2.1)
    apt-get install libglew-dev  # GLEW - OpenGL Extension Wrangler (1.13)
    apt-get install libglm-dev   # GLM  - OpenGL Mathematics (0.9.7.5)

Building
--------

	./build.sh

Camera Controls
---------------

 - `↑` `←` `↓` `→`: move camera
 - `W` `A` `S` `D`: move camera
 - `CTRL` + `↑` / `↓`: zoom in/out
 - `CTRL` + `←` / `→`: rotate view
