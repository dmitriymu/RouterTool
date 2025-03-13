cmake_minimum_required(VERSION 3.10)
project(RoCom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# Force static linking and point to wx-config if needed
# ------------------------------------------------------------------------------
set(wxWidgets_USE_STATIC ON)
set(wxWidgets_ROOT_DIR "/usr/local")
set(wxWidgets_CONFIG_EXECUTABLE "/usr/local/bin/wx-config")

# ------------------------------------------------------------------------------
# Find wxWidgets
# ------------------------------------------------------------------------------
find_package(wxWidgets REQUIRED COMPONENTS core base net adv)
include(${wxWidgets_USE_FILE})

# ------------------------------------------------------------------------------
# Find libssh (via pkg-config)
# ------------------------------------------------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(SSH REQUIRED libssh)

# Include dirs for libssh
include_directories(${SSH_INCLUDE_DIRS})
link_directories(${SSH_LIBRARY_DIRS})

# ------------------------------------------------------------------------------
# Project Includes
# ------------------------------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/include)

# ------------------------------------------------------------------------------
# Add Executable and Source Files
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME}
    src/App.cpp
    src/SSHFrame.cpp
    src/CommandFrame.cpp
    src/NotesFrame.cpp
    src/MacGeneratorFrame.cpp
    src/MacVendor.cpp
)

# ------------------------------------------------------------------------------
# Link Libraries
# ------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} 
    ${wxWidgets_LIBRARIES}
    ${SSH_LIBRARIES}
)