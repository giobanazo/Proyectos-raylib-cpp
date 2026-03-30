# Proyectos-raylib-cpp

# 1. Crear carpeta de build (solo la primera vez)
  
  mkdir build && cd build



# 2. Configurar el proyecto
  
  cmake ..



# 3. Compilar (usa todos los núcleos del CPU)
  
  cmake --build . -j$(nproc)



# 4. Ejecutar el juego que quieras (tetris, pong, snake o clock) [Tienes que estas dentro de la carpeta build]

  snake/snake

  pong/pong

  tetris/tetris

  clock/clock