// Copyright MakeShape. 2019, All rights reserved.

#include "mesh.hh"

#include <igl/opengl/glfw/Viewer.h>
#include <igl/unproject_onto_mesh.h>

#include <igl/bounding_box_diagonal.h>

#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <imgui/imgui.h>

#include <igl/png/writePNG.h>
#include <igl/png/readPNG.h>

#pragma once

namespace app {

class App {

    App(const App& app);
    App& operator=(const App& other);

  public:
    App(){}

    bool mousepress_callback(igl::opengl::glfw::Viewer& viewer, int x, int y);
    void custom_menu_callback(igl::opengl::glfw::Viewer* viewer,
                              igl::opengl::glfw::imgui::ImGuiMenu *menu );

    void load_cube();
    bool load_mesh(const std::string&& filename);
  
    mesh::Mesh& mesh() { return m; }
    const mesh::Mesh& const_mesh() const { return m; }

  private:
    mesh::Mesh m;

};

} // namespace app
