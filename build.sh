include=-I/usr/local/include
binary=unnamed
source=src/main.c
libs=-L/usr/local/lib
link_opengl=-lGL
link_glfw="-lglfw3 -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp"

gcc $include -o $binary $source $libs $link_opengl $link_glfw

