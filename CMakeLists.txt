#Define clang from homebrew
if (APPLE)
    set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
    set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
endif()

cmake_minimum_required(VERSION 3.16)

# Define the project name and version
project(RayTracing VERSION 1.0 LANGUAGES CXX)

# Set C++17 as the required standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Import openMP
# Find OpenMP as before
find_package(OpenMP)
if(OpenMP_FOUND)
    message(STATUS "Found OpenMP")
    # target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
else()
    message(WARNING "OpenMP not found, setting flags manually")
    # Option 2: Manually specify OpenMP flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/homebrew/opt/libomp/lib -lomp")
endif()

#set to release mode
set(CMAKE_BUILD_TYPE Release)

# Find glm package (make sure glm is installed and available via CMake pkg)
find_package(glm)
if (NOT glm_FOUND)
    message(STATUS "GLM not found. Fetching glm...")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
    )
    FetchContent_MakeAvailable(glm)
endif()

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Add the executable target (assumes main.cpp exists in your project)
add_executable(${PROJECT_NAME} ${SOURCES})

# Link glm to your project
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
if(OpenMP_FOUND)
    message(STATUS "Linking with OpenMP")
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()
