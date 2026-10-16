cmake_minimum_required(VERSION 3.24)

# std::format in Apple's libc++ needs macOS 13.3
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.3" CACHE STRING "Minimum macOS version")

project(
    block
    VERSION "1.4.0"
    DESCRIPTION "Source rebuild of BLOCK (KENTA, 2000) on SDL3"
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
foreach(asset IN ITEMS sprites.bmp stages.txt icon.bmp)
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

file(GLOB wave_files CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/wave/*.wav)

add_executable(block WIN32 MACOSX_BUNDLE
    src/audio.cpp
    src/game.cpp
    src/gfx.cpp
    src/main.cpp
    src/physics.cpp
    src/save.cpp
    src/screens.cpp
    src/settings.cpp
    src/stages.cpp
    src/voxels.cpp
    src/windows.cpp
    ${embedded_sources}
)
target_include_directories(block PRIVATE src)
target_compile_features(block PRIVATE cxx_std_23)
target_link_libraries(block PRIVATE SDL3::SDL3-static)
if(MSVC)
    target_compile_options(block PRIVATE /W4 /utf-8)
else()
    target_compile_options(block PRIVATE -Wall -Wextra)
endif()

if(WIN32)
    target_sources(block PRIVATE src/block.rc)
endif()

if(APPLE)
    # BLOCK.app, with the sounds in Contents/Resources/wave (SDL_GetBasePath points there)
    target_sources(block PRIVATE ${wave_files})
    set_source_files_properties(${wave_files} PROPERTIES MACOSX_PACKAGE_LOCATION Resources/wave)
    set_target_properties(block PROPERTIES
        OUTPUT_NAME BLOCK
        MACOSX_BUNDLE_BUNDLE_NAME BLOCK
        MACOSX_BUNDLE_GUI_IDENTIFIER jp.kenta.block
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
else()
    # the original game plays its wav files from wave/ next to the executable
    add_custom_command(TARGET block POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/wave $<TARGET_FILE_DIR:block>/wave)
endif()

# release package: cmake --build build --config Release --target package
if(APPLE)
    install(TARGETS block BUNDLE DESTINATION .)
    set(package_platform macos)
else()
    install(TARGETS block RUNTIME DESTINATION .)
    install(FILES ${wave_files} DESTINATION wave)
    if(WIN32)
        set(package_platform win64)
    else()
        set(package_platform linux-${CMAKE_SYSTEM_PROCESSOR})
    endif()
endif()
install(FILES README.md LICENSE DESTINATION .)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CPACK_GENERATOR TGZ)
else()
    set(CPACK_GENERATOR ZIP)
endif()
set(CPACK_PACKAGE_FILE_NAME "BLOCK-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}-${package_platform}")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY ON)
include(CPack)
