cmake_minimum_required(VERSION 3.24)

project(
    block
    VERSION "1.30.0"
    DESCRIPTION "Source rebuild of BLOCK v1.30 (KENTA, 2000) on SDL3"
    LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# static C/C++ runtime, so block.exe runs without the Visual C++ redistributable
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.8
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SDL3)

# compile assets/ into the executable so it needs nothing but the optional wave/ folder
set(embedded_sources)
foreach(asset IN ITEMS sprites.bmp stages.txt)
    string(MAKE_C_IDENTIFIER "${asset}" symbol)
    set(input ${CMAKE_SOURCE_DIR}/assets/${asset})
    set(output ${CMAKE_BINARY_DIR}/embedded/${symbol}.cpp)
    add_custom_command(
        OUTPUT ${output}
        COMMAND ${CMAKE_COMMAND} -DINPUT=${input} -DOUTPUT=${output} -DNAME=${symbol}
                -P ${CMAKE_SOURCE_DIR}/cmake/embed.cmake
        DEPENDS ${input} ${CMAKE_SOURCE_DIR}/cmake/embed.cmake
        COMMENT "Embedding ${asset}")
    list(APPEND embedded_sources ${output})
endforeach()

add_executable(block WIN32
    src/audio.cpp
    src/game.cpp
    src/gfx.cpp
    src/main.cpp
    src/physics.cpp
    src/save.cpp
    src/screens.cpp
    src/stages.cpp
    src/voxels.cpp
    src/windows.cpp
    ${embedded_sources}
)
if(WIN32)
    target_sources(block PRIVATE src/block.rc)
endif()
target_include_directories(block PRIVATE src)
target_compile_features(block PRIVATE cxx_std_23)
target_link_libraries(block PRIVATE SDL3::SDL3-static)
if(MSVC)
    target_compile_options(block PRIVATE /W4 /utf-8)
endif()

# the original game plays user-supplied wav files from wave/ next to the exe
add_custom_command(TARGET block POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/wave $<TARGET_FILE_DIR:block>/wave)

# release zip: cmake --build build --config Release --target package
install(TARGETS block RUNTIME DESTINATION .)
install(DIRECTORY wave/ DESTINATION wave FILES_MATCHING PATTERN "*.wav")
install(FILES README.md LICENSE DESTINATION .)
set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_FILE_NAME "BLOCK-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}-win64")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY ON)
include(CPack)
