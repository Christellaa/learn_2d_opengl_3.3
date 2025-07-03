cmake_minimum_required(VERSION 3.12)
project(learn_2d_opengl_3.3)

set(CMAKE_CXX_STANDARD 17)

# Ajoute GLFW depuis le sous-dossier
add_subdirectory(libs/glfw)

# Trouver OpenGL (système)
find_package(OpenGL REQUIRED)

# Ajoute l'exécutable
add_executable(2dtest
	src/main.cpp
	src/glad.c
	src/Shader.cpp
)

# Dossier où se trouvent glad/ et KHR/
target_include_directories(2dtest PRIVATE include)

# Lien avec GLFW et OpenGL
target_link_libraries(2dtest PRIVATE glfw OpenGL::GL)

file(GLOB SHADERS "${CMAKE_SOURCE_DIR}/shaders/*")
file(COPY ${SHADERS} DESTINATION ${CMAKE_BINARY_DIR}/shaders)

file(GLOB TEXTURES "${CMAKE_SOURCE_DIR}/textures/*")
file(COPY ${TEXTURES} DESTINATION ${CMAKE_BINARY_DIR}/textures)
