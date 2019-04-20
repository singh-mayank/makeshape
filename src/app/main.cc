// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"
#include <igl/opengl/glfw/Viewer.h>

//
// Loads a mesh, and registers a set of callbacks
// 
int main(int argc, char *argv[])
{
    App application;

    if (argc < 2) {
        application.load_cube();
    } else {
        if(!application.load_mesh(std::string(argv[1]))) {
            printf("Failed at loading file: [ %s ]. Aborting.\n", argv[1]);
            return 1;
        }
    }

    // Viewer
    igl::opengl::glfw::Viewer viewer;
    
    // GUI
    igl::opengl::glfw::imgui::ImGuiMenu menu;
    viewer.plugins.push_back(&menu);

    auto mousepress_callback_ptr = std::bind(&App::mousepress_callback, &application,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);
    viewer.callback_mouse_down = mousepress_callback_ptr;

    auto custom_menu_callback_ptr = std::bind(&App::custom_menu_callback, &application,
            &viewer,
            &menu);
    menu.callback_draw_custom_window = custom_menu_callback_ptr;

    // Mesh data
    viewer.data().set_mesh(application.const_mesh().const_vertices(), 
                           application.const_mesh().const_faces());
    viewer.data().set_face_based(true);
    viewer.launch();

}
