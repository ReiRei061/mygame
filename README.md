# MyGame 🎮

Un videojuego de rol/aventura en 2D desarrollado en **C++** utilizando **SFML 2.6.1**, con una arquitectura orientada a estados (*State Pattern*), gestión centralizada de recursos, renderizado de mapas y un sistema de almacenamiento persistente.

---

## 🛠️ Características Principales

* **Arquitectura de Estados (`StateManager`):** Navegación fluida entre Menú Principal (`MainMenuState`), Selección de Ranuras (`SelectSlotState`), Dificultad (`SelectDifficultyState`), Pantalla de Pausa (`PauseState`) y Juego (`PlayState`).
* **Sistema de Guardado (`SaveSystem`):** Soporte para 3 ranuras (*slots*) de guardado independientes en formato JSON que persisten el estado del juego, dificultad y progreso.
* **Gestión Centralizada de Recursos:** Módulos optimizados para cargar y proveer audio (`AudioManager`), fuentes (`FontManager`) y texturas (`TextureManager`).
* **Motor de Mapas y Zonas (`MapManager`):** Carga dinámica de mapas y zonas interconectadas por portales de transición.
* **Componentes de Interfaz UI:** Botones interactivos (`Button`) con respuestas a eventos del ratón, efectos hover y colores personalizables.

---

## 💻 Requisitos del Sistema

* **Sistema Operativo:** Windows 10/11 (64-bit).
* **Compilador C++:** Compatible con C++17 o superior (MSVC 2022 recommended).
* **Herramientas de Construcción:** CMake 3.16+ y Make (opcional).
* **Librerías Externas:**
  * **SFML 2.6.1** (64-bit) instalada en `C:\SFML-2.6.1`.
  * **nlohmann/json** (descargada e integrada automáticamente por CMake vía `FetchContent`).

---

## 📂 Estructura del Repositorio (`https://github.com/ReiRei061/mygame.git`)

```text
mygame/
├── assets/                 # Recursos multimedia (sprites, mapas, fuentes, audio)
├── include/                # Archivos de cabecera (.hpp)
│   ├── core/               # AudioManager, FontManager, TextureManager, SaveSystem, EventBus
│   ├── entities/           # Clases de entidades del juego
│   ├── states/             # Definición de estados del juego
│   └── ui/                 # Componentes de interfaz (Button)
├── src/                    # Código fuente (.cpp)
├── saves/                  # Directorio para archivos JSON de guardado (Slot_1.json, etc.)
├── CMakeLists.txt          # Configuración del sistema de compilación CMake
└── Makefile                # Script de automatización de comandos

⚙️ Instalación, Compilación y Ejecución

1. Verificación de SFML
Asegúrate de que la librería SFML 2.6.1 de 64 bits esté ubicada exactamente en la raíz de tu disco C: con la siguiente estructura:

Plaintext
C:\SFML-2.6.1\
├── bin/       # Contiene las DLLs (sfml-graphics-2.dll, sfml-window-2.dll, etc.)
├── include/   # Cabeceras (.hpp)
└── lib/       # Archivos de biblioteca (.lib) y cmake/SFML

2. Clonar el Repositorio
PowerShell
git clone [https://github.com/ReiRei061/mygame.git](https://github.com/ReiRei061/mygame.git)
cd mygame

3. Configurar y Compilar el Proyecto
Desde la raíz del proyecto, ejecuta en la terminal (PowerShell o CMD):

PowerShell
# Generar los archivos de construcción con CMake
cmake -B build

# Compilar el ejecutable en modo Debug
cmake --build build --config Debug
(También puedes ejecutar simplemente make si utilizas la herramienta Make).

4. Despliegue de DLLs (Paso Obligatorio)
Para que el ejecutable funcione sin fallos de bibliotecas faltantes, copia los archivos .dll de SFML al directorio de salida del ejecutable:

Ve a C:\SFML-2.6.1\bin\ y copia todos los archivos .dll.

Pégalos dentro de la carpeta build\Debug\ (o dentro de build\ según tu generador de CMake).

5. Ejecutar el Juego

.\build\Debug\mygame.exe

👥 Créditos
Desarrollado por Reinier Manrique como un proyecto personal de videojuego en C++ utilizando SFML.
