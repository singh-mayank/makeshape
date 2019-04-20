// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"

#include <igl/opengl/glfw/Viewer.h>

/*
int main(int argc, char *argv[])
{
  // Inline mesh of a cube
  const Eigen::MatrixXd V= (Eigen::MatrixXd(8,3)<<
    0.0,0.0,0.0,
    0.0,0.0,1.0,
    0.0,1.0,0.0,
    0.0,1.0,1.0,
    1.0,0.0,0.0,
    1.0,0.0,1.0,
    1.0,1.0,0.0,
    1.0,1.0,1.0).finished();
  const Eigen::MatrixXi F = (Eigen::MatrixXi(12,3)<<
    1,7,5,
    1,3,7,
    1,4,3,
    1,2,4,
    3,8,7,
    3,4,8,
    5,7,8,
    5,8,6,
    1,5,6,
    1,6,2,
    2,6,8,
    2,8,4).finished().array()-1;

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_face_based(true);
  viewer.launch();
}
*/

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
    viewer.data().set_mesh(application.vertices(), application.faces());
    viewer.data().set_face_based(true);
    viewer.launch();

}
