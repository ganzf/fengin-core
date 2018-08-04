cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project(fengin-core)

set(FENDER_ROOT ${PROJECT_SOURCE_DIR}/projects/fender)
set(MUTILS_ROOT ${PROJECT_SOURCE_DIR}/projects/mutils)
set(DEMO_ROOT ${PROJECT_SOURCE_DIR}/projects/fender/demo)

execute_process(
        COMMAND git submodule update --remote --init
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

include_directories(include modules/utils)
file(GLOB UTILS modules/utils/*.hpp)
file(GLOB INCLUDE include/*.hpp)
file(GLOB SRC src/*.hpp src/*.cpp)
set(SOURCE_FILES ${INCLUDE} ${SRC} ${UTILS})

if (UNIX)
    add_compile_options(-Wall -Wextra -Werror)
elseif(WIN32)
    set(CMAKE_CXX_FLAGS /std:c++latest)
    #    add_compile_options(/std:c++latest)
endif()
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(fengin-core STATIC ${SOURCE_FILES})
if (UNIX)
    target_link_libraries(fengin-core sfml-system sfml-window sfml-audio sfml-graphics)
endif (UNIX)
if (WIN32)
    #    set(SFML_ROOT ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/)
    #    set(CMAKE_MODULE_PATH
    #			${CMAKE_MODULE_PATH}
    #			${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/cmake/Modules/)
    #	find_package(SFML REQUIRED COMPONENTS system window audio graphics)
    #        message(${SFML_LIBRARIES})
    #	target_link_libraries(fender ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(fengin-core
            ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/lib/sfml-system.lib
            ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/lib/sfml-window.lib
            ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/lib/sfml-audio.lib
            ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/lib/sfml-graphics.lib
            )
endif(WIN32)
target_link_libraries(fengin-core -lstdc++fs)

