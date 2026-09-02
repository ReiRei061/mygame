Markdown
# MyGame 🎮

![C++ Version](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![SFML Version](https://img.shields.io/badge/SFML-2.6.1-green.svg)
![Build System](https://img.shields.io/badge/CMake-3.16%2B-red.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)

Un videojuego de rol/aventura en 2D desarrollado en C++ utilizando **SFML 2.6.1**, con una arquitectura orientada a estados (*State Pattern*), gestión centralizada de recursos, renderizado de mapas y un sistema de almacenamiento persistente.

---

## 🛠️ Características Principales

* **Arquitectura de Estados (`StateManager`):** Navegación fluida entre Menú Principal (`MainMenuState`), Selección de Ranuras (`SelectSlotState`), Dificultad (`SelectDifficultyState`), Pantalla de Pausa (`PauseState`) y Juego (`PlayState`).
* **Sistema de Guardado (`SaveSystem`):** Soporte para 3 ranuras (*slots*) de guardado independientes en formato JSON que persisten el estado del juego, dificultad y progreso.
* **Gestión Centralizada de Recursos:** Módulos optimizados para cargar y proveer audio (`AudioManager`), fuentes (`FontManager`) y texturas (`TextureManager`).
* **Motor de Mapas y Zonas (`MapManager`):** Carga dinámica de mapas y zonas interconectadas por portales de transición.
* **Componentes de Interfaz UI:** Botones interactivos (`Button`) con respuestas a eventos del ratón, efectos hover y colores personalizables.

---

## 💻 Requisitos del Sistema

| Componente | Requisito recomendado |
| :--- | :--- |
| **Sistema Operativo** | Windows 10/11 (64-bit) |
| **Compilador C++** | Compatible con C++17 o superior (MSVC 2022 recomendado) |
| **Construcción** | CMake 3.16+ y Make (opcional) |
| **Bibliotecas Externas** | SFML 2.6.1 incluida localmente en `libs/`<br>`nlohmann/json` (descargada e integrada por CMake vía FetchContent) |

---

## 📂 Estructura del Repositorio

```text
mygame/
├── assets/                 # Recursos multimedia (sprites, mapas, fuentes, audio)
├── include/                # Archivos de cabecera (.hpp)
│   ├── core/               # AudioManager, FontManager, TextureManager, SaveSystem, EventBus
│   ├── entities/           # Clases de entidades del juego
│   ├── states/             # Definición de estados del juego
│   └── ui/                 # Componentes de interfaz (Button)
├── libs/                   # Depósito de librerías locales
│   └── SFML-2.6.1/         # Archivos de la librería SFML 2.6.1
├── src/                    # Código fuente (.cpp)
├── saves/                  # Directorio para archivos JSON de guardado (Slot_1.json, etc.)
├── CMakeLists.txt          # Configuración del sistema de compilación CMake
└── Makefile                # Script de automatización de comandos

⚙️ Instalación, Compilación y Ejecución

1. Clonar el Repositorio

git clone [https://github.com/ReiRei061/mygame.git](https://github.com/ReiRei061/mygame.git)
cd mygame

2. Estructura de Librerías

El proyecto ya incluye SFML 2.6.1 integrado dentro del directorio local libs/SFML-2.6.1/. No requieres instalaciones adicionales ni configurar variables de entorno globales.

3. Configurar y Compilar el Proyecto

Desde la raíz del proyecto, ejecuta en la terminal (PowerShell o CMD):

# Generar los archivos de construcción con CMake
cmake -B build

# Compilar el ejecutable en modo Debug
cmake --build build --config Debug
(También puedes ejecutar make si utilizas dicha herramienta).

Nota: La configuración de CMake copia de forma automática las DLLs necesarias de SFML y los recursos al directorio de salida en build/.

4. Ejecutar el Juego

.\build\Debug\mygame.exe

👥 Créditos
Desarrollado por Reinier Manrique como un proyecto personal de videojuego en C++ utilizando SFML.