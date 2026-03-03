cmake_minimum_required(VERSION 3.16) # Qt 6 requiere versiones modernas de CMake

project(RETENEITOR3000 LANGUAGES CXX)

# Habilitar el manejo automático de archivos .ui, .qrc y MOC (headers)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar los paquetes necesarios
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(X11 REQUIRED)
# Nota: Asegúrate de tener instalados los archivos de desarrollo de Sox y Festival
# find_package(Sox REQUIRED)
# find_package(Festival REQUIRED)

# Listar tus archivos fuente
set(RETENEITOR3000_SRCS
    main.cpp
    reteneitor3000.cpp
    reteneitor3000.h
    reteneitor3000.ui
    reteneitor3000.qrc
)

add_executable(reteneitor3000 ${RETENEITOR3000_SRCS})

# Enlazar con las librerías de Qt 6 y X11
target_link_libraries(reteneitor3000 PRIVATE 
    Qt6::Widgets 
    X11::X11
    # Sox::Sox      <-- Ajustar según cómo se llamen los targets de Sox/Festival
    # Festival::Festival
)