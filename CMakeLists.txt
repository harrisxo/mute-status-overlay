cmake_minimum_required(VERSION 3.10)
project(mute_status_overlay LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output DLL
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(BUILD_SHARED_LIBS ON)

# Plugin source
set(SOURCES mute_status_overlay.cpp)

# Include TeamSpeak SDK headers
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/pluginsdk/include
    ${CMAKE_SOURCE_DIR}/pluginsdk/include/teamspeak
)

# Output name
set(LIBRARY_OUTPUT_NAME mute_status_overlay)

# Build DLL
add_library(${LIBRARY_OUTPUT_NAME} SHARED ${SOURCES})

# Link Windows libraries
if(MSVC)
    target_link_libraries(${LIBRARY_OUTPUT_NAME} PRIVATE comctl32 gdi32 user32 kernel32)
else()
    target_link_libraries(${LIBRARY_OUTPUT_NAME} PRIVATE -lcomctl32 -lgdi32 -luser32 -lkernel32)
endif()

# Set output directory
set_target_properties(${LIBRARY_OUTPUT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
) 