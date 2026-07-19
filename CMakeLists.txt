cmake_minimum_required(VERSION 3.15)

# Nombre de tu proyecto
project(mygame CXX)

# Forzar el estándar moderno de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. DILE A CMAKE DÓNDE DESCOMPRIMISTE SFML
# Asegúrate de que esta ruta coincida exactamente con el lugar donde guardaste SFML
set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")

# 2. Buscar los componentes de SFML que vamos a usar
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# 3. Buscar automáticamente todos los archivos .cpp dentro de la carpeta src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 4. Definir el ejecutable final con el nombre de tu proyecto
add_executable(${PROJECT_NAME} ${SOURCES})

# 5. Indicarle a CMake dónde buscar tus archivos de cabecera (.hpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)

# 6. Enlazar las librerías de SFML con tu juego
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# 7. TRUCO DE WINDOWS: Copiar los archivos .dll automáticamente al compilar
# Esto evita el molesto error de "falta sfml-graphics-2.dll" al ejecutar el juego
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DIR}/../../../bin"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()