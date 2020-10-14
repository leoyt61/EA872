# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(MMA)

#
add_executable(MMA App/main.cpp)

# Especificar onde estao os header files
include_directories(Include/Views)
include_directories(Include/Models/amortecedor)
include_directories(Include/Models/massa)
include_directories(Include/Models/mola)
include_directories(Include/Models/teclado)
include_directories(Include/Models/textura)
include_directories(Include/Controllers)

# Bibliotecas locais (estaticas)
add_library(view Views/view.cpp)
add_library(amortecedor Models/amortecedor/amortecedor.cpp)
add_library(massa Models/massa/massa.cpp)
add_library(mola Models/mola/mola.cpp)
add_library(teclado Models/teclado/teclado.cpp)
add_library(textura Models/textura/textura.cpp)
add_library(sistema Controllers/sistema/sistema.cpp)
target_link_libraries(MMA view amortecedor massa mola teclado textura sistema view)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
target_link_libraries(MMA SDL2)
target_link_libraries(MMA SDL2_image)
