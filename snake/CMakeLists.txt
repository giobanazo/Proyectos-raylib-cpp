add_executable(snake main.cpp)
target_link_libraries(snake raylib)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})