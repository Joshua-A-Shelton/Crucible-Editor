cmake_minimum_required(VERSION 3.24)
project(CrucibleEditor)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#there may be more of these I need to add, but this works on windows at the very least
if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "AMD64" OR ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    set(CRUCIBLE_EDITOR_TRIPLET x64)
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL ARM)
    set(CRUCIBLE_EDITOR_TRIPLET arm)
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL ARM64 OR ${CMAKE_SYSTEM_PROCESSOR} STREQUAL aarch64 OR ${CMAKE_SYSTEM_PROCESSOR} STREQUAL aarch64_be)
    set(CRUCIBLE_EDITOR_TRIPLET arm64)
endif()


#use custom manifest for windows
if( WIN32 )
    set ( CMAKE_SHARED_LINKER_FLAGS /MANIFEST:NO )
endif()

if(UNIX AND NOT APPLE)
    set(CRUCIBLE_EDITOR_PLATFORM linux-${CRUCIBLE_EDITOR_TRIPLET})
elseif(UNIX)
    set(CRUCIBLE_EDITOR_PLATFORM osx)
else()
    set(CRUCIBLE_EDITOR_PLATFORM win-${CRUCIBLE_EDITOR_TRIPLET})
endif()

add_subdirectory(third-party/crucible)

add_executable(CrucibleEditor ${CRUCIBLE_DEAR_IMGUI} src/Program.cpp src/Graphics/Fonts.h src/Editor.cpp src/Editor.h src/Interop/EditorInterop.cpp src/Interop/EditorInterop.h)
target_link_libraries(CrucibleEditor Crucible)
#==============================================================================
# COMPILE SHADERS
#
set(SHADER_SOURCE_DIR src/Graphics/DefaultShaders)
set(SHADER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Graphics/DefaultShaders)

file(GLOB SHADERS
        ${SHADER_SOURCE_DIR}/*.vert
        ${SHADER_SOURCE_DIR}/*.frag
        ${SHADER_SOURCE_DIR}/*.comp)

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



#copy over native dlls managed dll requires
add_custom_target(dotnetruneditor-native
        DEPENDS dotnetruneditor-build
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_BINARY_DIR}/runtimes/${CRUCIBLE_EDITOR_PLATFORM}/native/" "${CMAKE_BINARY_DIR}"
        COMMENT "Copying native DLLs for managed Avalonia DLLs"
        )


ADD_DEPENDENCIES(Crucible dotnetruneditor-build dotnetruneditor-native)

#add custom manifest, required to make avalonia work on windows
if( WIN32 )
add_custom_command(
        TARGET CrucibleEditor
        POST_BUILD
        COMMAND "mt.exe" -manifest "${CMAKE_SOURCE_DIR}\\CrucibleEditor.manifest" -outputresource:"${CMAKE_BINARY_DIR}/CrucibleEditor.exe"
        COMMENT "Adding manifest..."
)
endif()


file(COPY Crucible.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})