em++ -std=c++17 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG -lidbfs.js main.cpp Game.cpp GameOver.cpp Highscore.cpp Menu.cpp Tetris.cpp -o ..\webasm\pge.html --preload-file .\assets