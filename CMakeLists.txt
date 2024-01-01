cmake_minimum_required(VERSION 3.24)
project(CrucibleEditor)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

list(APPEND CRUCIBLE_DEAR_IMGUI third-party/dear-imgui/imgui.cpp)
list(APPEND CRUCIBLE_DEAR_IMGUI third-party/dear-imgui/imgui_demo.cpp)
list(APPEND CRUCIBLE_DEAR_IMGUI third-party/dear-imgui/imgui_draw.cpp)
list(APPEND CRUCIBLE_DEAR_IMGUI third-party/dear-imgui/imgui_tables.cpp)
list(APPEND CRUCIBLE_DEAR_IMGUI third-party/dear-imgui/imgui_widgets.cpp)
list(APPEND CRUCIBLE_DEAR_IMGUI third-party/dear-imgui/backends/imgui_impl_sdl2.cpp)

add_subdirectory(third-party/crucible)

add_executable(CrucibleEditor ${CRUCIBLE_DEAR_IMGUI} src/Program.cpp src/Graphics/DearImGUI/imgui_impl_slag.cpp src/Graphics/DearImGUI/imgui_impl_slag.h src/Graphics/Fonts.h src/Controls/MenuBar.cpp src/Controls/MenuBar.h src/Controls/Control.h src/Graphics/DearImGUI/ImGuiInterop.cpp src/Graphics/DearImGUI/ImGuiInterop.h src/Editor.cpp src/Editor.h)
target_include_directories(CrucibleEditor PRIVATE third-party/dear-imgui)
target_link_libraries(CrucibleEditor Crucible)
#==============================================================================
# COMPILE SHADERS
#
set(SHADER_SOURCE_DIR src/Graphics/DefaultShaders)
set(SHADER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Graphics/DefaultShaders)

file(GLOB SHADERS
        ${SHADER_SOURCE_DIR}/*.vert
        ${SHADER_SOURCE_DIR}/*.frag)

add_custom_command(
        COMMAND
        ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
        OUTPUT ${SHADER_BINARY_DIR}
        COMMENT "Creating ${SHADER_BINARY_DIR}"
)

foreach(source IN LISTS SHADERS)
    get_filename_component(FILENAME ${source} NAME)
    add_custom_command(
            COMMAND
            glslc
            #      -MD -MF ${SHADER_BINARY_DIR}/${FILENAME}.d
            -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
            ${source}
            OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
            DEPENDS ${source} ${SHADER_BINARY_DIR}
            COMMENT "Compiling ${FILENAME}"
    )
    list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
endforeach()

add_custom_target(shaders ALL DEPENDS ${SPV_SHADERS})

add_dependencies(CrucibleEditor shaders)



if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CRUCIBLE_EDITOR_BUILD_TYPE "Debug")
else()
    set(CRUCIBLE_EDITOR_BUILD_TYPE "Release")
endif()

#==============================================================================
#Compile dotnet
#
file(GLOB_RECURSE DOTNETEDITOR CONFIGURE_DEPENDS dotnet/CrucibleEditor/*.cs)
add_custom_target(dotnetruneditor-build
        DEPENDS ${DOTNETEDITOR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dotnet/CrucibleEditor/Crucible-Editor
        COMMAND dotnet publish -c ${CRUCIBLE_EDITOR_BUILD_TYPE} -o ${CMAKE_BINARY_DIR}
        COMMENT "Building .net editor addon")
ADD_DEPENDENCIES(Crucible dotnetruneditor-build)




file(COPY Crucible.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
