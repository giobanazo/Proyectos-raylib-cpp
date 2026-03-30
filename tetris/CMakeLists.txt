add_executable(tetris main.cpp blocks.cpp block.cpp colors.cpp game.cpp grid.cpp position.cpp)
target_link_libraries(tetris raylib)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})