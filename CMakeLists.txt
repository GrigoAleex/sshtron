cmake_minimum_required(VERSION 3.16)
project(sshtron C)

# C standard + warnings cross-platform
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Default build type to Release if not set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# Nice warnings per compiler
if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

# --- Sources (ce există deja în repo)
set(SSH_TRON_SOURCES
  main.c
  src/connection.c
  src/cli.c
)

add_executable(sshtron ${SSH_TRON_SOURCES})

target_include_directories(sshtron PRIVATE src)

# Windows specific (dacă ai nevoie de ws2_32; poți comenta dacă nu-l folosești)
if(WIN32)
  target_link_libraries(sshtron PRIVATE ws2_32)
  target_compile_definitions(sshtron PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# --- POSIX vs Windows input (termios vs conio)
# Sugestie: în cod folosește #ifdef _WIN32 pentru conio.h, altfel termios.h
# Nu e nevoie de setări speciale aici; doar ensurează te că header-urile sunt guarded.

# --- OPȚIONAL: pregătit pentru Firebase (când adaugi fișierele)
# option(ENABLE_FIREBASE "Build with Firebase REST (libcurl)" OFF)
# if(ENABLE_FIREBASE)
#   find_package(CURL REQUIRED)
#   target_sources(sshtron PRIVATE src/config.c src/firebase.c)
#   target_include_directories(sshtron PRIVATE ${CURL_INCLUDE_DIRS})
#   target_link_libraries(sshtron PRIVATE ${CURL_LIBRARIES})
#   target_compile_definitions(sshtron PRIVATE SSH_TRON_WITH_FIREBASE=1)
# endif()

# --- Install target (user-friendly)
# Pe Windows: cmake --install build --prefix "%LOCALAPPDATA%/Programs/sshtron"
# Pe Linux/macOS: cmake --install build --prefix "$HOME/.local"
install(TARGETS sshtron
  RUNTIME DESTINATION bin
)
