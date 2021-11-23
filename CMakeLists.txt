cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME FVGame)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(GLEW_STATIC)

include_directories(src)

link_directories(3rdParty/GLEW/lib)
include_directories(3rdParty/GLEW/include)
link_directories(3rdParty/GLFW/lib)
include_directories(3rdParty/GLFW/include)
include_directories(3rdParty/glm
                    3rdParty/ImGui
                    3rdParty/GLFW/include
                    3rdParty/rapidjson)


if(WIN32)
    set (PROJECT_LIBS mingw32 glew32 opengl32 glu32 Imm32)
else(WIN32)
    set (PROJECT_LIBS gl glew glu)
endif(WIN32)

set (PROJECT_LIBS ${PROJECT_LIBS} glfw3)
link_libraries(${PROJECT_LIBS})

file(GLOB_RECURSE IMGUI_SOURCES
    3rdParty/ImGui/*.cpp 3rdParty/ImGui/*.h)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp src/*.h assets/*)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${IMGUI_SOURCES})

add_subdirectory(3rdParty/VoxelLib/RanokCoreLib RanokCore)
target_link_libraries(${PROJECT_NAME} PRIVATE RanokCore)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                      ${CMAKE_SOURCE_DIR}/3rdParty/GLFW/bin/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/3rdParty/GLEW/bin/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)
