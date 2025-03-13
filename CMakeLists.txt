cmake_minimum_required(VERSION 3.10)
project(RoCom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# Force static linking for wxWidgets
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
# Define paths to static libraries
# ------------------------------------------------------------------------------
set(SSH_STATIC_LIB "/usr/local/lib/libssh.a" CACHE FILEPATH "Path to static libssh")
set(CRYPTO_STATIC_LIB "/opt/homebrew/opt/openssl@3/lib/libcrypto.a" CACHE FILEPATH "Path to static libcrypto")
set(SSL_STATIC_LIB "/opt/homebrew/opt/openssl@3/lib/libssl.a" CACHE FILEPATH "Path to static libssl")

# Verify existence
if(NOT EXISTS ${SSH_STATIC_LIB})
    message(FATAL_ERROR "Could not find static libssh.a at ${SSH_STATIC_LIB}")
endif()

if(NOT EXISTS ${CRYPTO_STATIC_LIB})
    message(FATAL_ERROR "Could not find static libcrypto.a at ${CRYPTO_STATIC_LIB}")
endif()

if(NOT EXISTS ${SSL_STATIC_LIB})
    message(FATAL_ERROR "Could not find static libssl.a at ${SSL_STATIC_LIB}")
endif()

# ------------------------------------------------------------------------------
# Include Paths
# ------------------------------------------------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/include "/usr/local/include" "/opt/homebrew/include")
link_directories("/usr/local/lib" "/opt/homebrew/lib")

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
    ${SSH_STATIC_LIB}
    ${CRYPTO_STATIC_LIB}
    ${SSL_STATIC_LIB}
    -lgssapi_krb5
    -lz
)