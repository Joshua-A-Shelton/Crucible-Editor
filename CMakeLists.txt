cmake_minimum_required(VERSION 3.29)
project(CrucibleEditor)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
fetchcontent_declare(
        Crucible
        GIT_REPOSITORY https://github.com/Joshua-A-Shelton/Crucible.git
        GIT_TAG origin/master
        GIT_SHALLOW TRUE
        OVERRIDE_FIND_PACKAGE
)
fetchcontent_makeavailable(Crucible)

add_executable(CrucibleEditor
        src/Main.cpp
        src/Editor.cpp
        src/Editor.h
        src/dear-imgui/imconfig.h
        src/dear-imgui/imgui.cpp
        src/dear-imgui/imgui.h
        src/dear-imgui/imgui_demo.cpp
        src/dear-imgui/imgui_draw.cpp
        src/dear-imgui/imgui_impl_sdl3.cpp
        src/dear-imgui/imgui_impl_sdl3.h
        src/dear-imgui/imgui_impl_slag.cpp
        src/dear-imgui/imgui_impl_slag.h
        src/dear-imgui/imgui_internal.h
        src/dear-imgui/imgui_tables.cpp
        src/dear-imgui/imgui_widgets.cpp
        src/dear-imgui/imstb_rectpack.h
        src/dear-imgui/imstb_textedit.h
        src/dear-imgui/imstb_truetype.h
)

target_link_libraries(CrucibleEditor PUBLIC Crucible)
#copy icon to build file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/crucible.png ${CMAKE_BINARY_DIR}/crucible.png COPYONLY)
