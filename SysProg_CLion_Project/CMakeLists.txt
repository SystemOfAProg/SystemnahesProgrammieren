# General Information for CMake (not project specific)
cmake_minimum_required(VERSION 3.13)
project(SystemnahesProgrammieren)
set(CMAKE_CXX_STANDARD 14)

# ================= Preparation =====================

set(BUFFER_DIR  "src/Buffer")
set(SYMTAB_DIR  "src/Symboltable")
set(AUTOMAT_DIR "src/Automat")
set(SCANNER_DIR "src/Scanner")
set(PARSER_DIR  "src/Parser")

# ================= Include Header Files =====================

include_directories(${BUFFER_DIR}/includes)
include_directories(${SYMTAB_DIR}/includes)
include_directories(${AUTOMAT_DIR}/includes)
include_directories(${SCANNER_DIR}/includes)
include_directories(${PARSER_DIR}/includes)

# ================= Declare Source Files =====================

file(GLOB BUFFER_SOURCES  "${BUFFER_DIR}/src/*.cpp")
file(GLOB SYMTAB_SOURCES  "${SYMTAB_DIR}/src/*.cpp")
file(GLOB AUTOMAT_SOURCES "${AUTOMAT_DIR}/src/*.cpp")
file(GLOB SCANNER_SOURCES "${SCANNER_DIR}/src/*.cpp")
file(GLOB PARSER_SOURCES  "${PARSER_DIR}/src/*.cpp")

# ================= Copying assets =====================

configure_file(${PROJECT_SOURCE_DIR}/assets/program_1.txt ${CMAKE_BINARY_DIR}/Scanner/assets/program_1.txt COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/assets/program_1.txt ${CMAKE_BINARY_DIR}/Parser/assets/program_1.txt COPYONLY)

# ================= Create output directories =====================

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Parser/output)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Scanner/output)

# ================= Buffer =====================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Buffer/bin)
file(COPY ${BUFFER_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/Buffer/)
add_executable(TestBuffer ${BUFFER_SOURCES})
add_library(BUFFER_LIB ${BUFFER_SOURCES})

# ================= Symboltable =====================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Symboltable/bin)
add_executable(TestSymboltable ${SYMTAB_SOURCES})
add_library(SYMTAB_LIB ${SYMTAB_SOURCES})

# ================= Automat =====================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Automat/bin)
add_executable(TestAutomat ${AUTOMAT_SOURCES})
add_library(AUTOMAT_LIB ${AUTOMAT_SOURCES})

# ================= Scanner =====================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Scanner/bin)
add_executable(Scanner ${SCANNER_SOURCES})
add_library(SCANNER_LIB ${SCANNER_SOURCES})
target_link_libraries(Scanner BUFFER_LIB SYMTAB_LIB AUTOMAT_LIB)
target_link_libraries(SCANNER_LIB BUFFER_LIB SYMTAB_LIB AUTOMAT_LIB)

# ================= Parser =====================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Parser/bin)
add_executable(Parser ${PARSER_SOURCES})
target_link_libraries(Parser SCANNER_LIB)