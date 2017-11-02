include=-I/usr/local/include
libs=-L/usr/local/lib
binary=unnamed
source="src/init.c src/shader.c src/loader.c src/glfw_callbacks.c src/main.c"
link_opengl=-lGL
link_glfw="-lglfw3 -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp"
link_glew=-lGLEW

gcc $source -o $binary $include $libs \
  -Wl,-Bstatic $link_glew \
  -Wl,-Bdynamic $link_opengl $link_glfw

