# General Information for CMake (not project specific)
cmake_minimum_required(VERSION 3.13)
project(SystemnahesProgrammieren)
set(CMAKE_CXX_STANDARD 14)

# Preparing the Build:
# - Define Variables for subdirectories with seperate projects (set)
# - Define where to find header files for each project (include_directories)
# Actual Build:
# - Define subdir for binaries of each component (set(CMAKE_RUNTIME...))
# - Copy assets next to binary folder (file(COPY...))
# - Create Executable with collected source files (add_executable)

set(BUFFER_DIR "Buffer")
set(SYMTAB_DIR "Symboltable")

include_directories(${BUFFER_DIR}/includes)
include_directories(${SYMTAB_DIR}/includes)

file(GLOB BUFFER_SOURCES "${BUFFER_DIR}/src/*.cpp")
file(GLOB SYMTAB_SOURCES "${SYMTAB_DIR}/src/*.cpp")

# ================= Buffer =====================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Buffer/bin)
file(COPY ${BUFFER_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/Buffer/)
add_executable(TestBuffer ${BUFFER_SOURCES})

# ================= Symboltable =====================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Symboltable/bin)
add_executable(TestSymboltable ${SYMTAB_SOURCES})
