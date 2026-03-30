# Proyectos-raylib-cpp

# 1. Traer la libreria (raylib) en su versión 5.5 en la raiz del proyecto 

git clone --branch 5.5 --depth 1 https://github.com/raysan5/raylib.git



# 2. Crear carpeta de build (solo la primera vez)
  
mkdir build && cd build



# 3. Configurar el proyecto
  
cmake ..



# 4. Compilar (usa todos los núcleos del CPU)
  
cmake --build . -j$(nproc)



# 5. Ejecutar el juego que quieras (tetris, pong, snake o clock) [Tienes que estas dentro de la carpeta build]

snake/snake

pong/pong

tetris/tetris

clock/clock