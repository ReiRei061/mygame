cmake_minimum_required(VERSION 3.15)

# Nombre de tu proyecto
project(mygame CXX)

# Forzar el estándar moderno de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. RUTA DE SFML (Tu versión actual de 64 bits)
set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")

# 2. Buscar los componentes de SFML
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# 3. Buscar archivos fuentes
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 4. Definir el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# 5. Indicar la carpeta de cabeceras (.hpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)

# 6. ENLAZAR CON LOS OBJETIVOS OFICIALES DE SFML
# Usar los objetivos importados remedia los errores de "símbolos sin resolver" en MSVC
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# 7. Copiar los archivos .dll automáticamente al compilar
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DIR}/../../../bin"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()