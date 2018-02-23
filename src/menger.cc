#include "menger.h"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

namespace {
	const int kMinLevel = 0;
	const int kMaxLevel = 4;
};

Menger::Menger()
{
	// Add additional initialization if you like
}

Menger::~Menger()
{
}

void
Menger::set_nesting_level(int level)
{
	nesting_level_ = level;
	dirty_ = true;
}

bool
Menger::is_dirty() const
{
	return dirty_;
}

void
Menger::set_clean()
{
	dirty_ = false;
}

void Menger::draw_cube(std::vector<glm::vec4>& obj_vertices,
                  std::vector<glm::uvec3>& obj_faces,
                  glm::vec3 min_vals,
                  glm::vec3 max_vals)
{
    const auto x_min = min_vals[0];
    const auto x_max = max_vals[0];
    const auto y_min = min_vals[1];
    const auto y_max = max_vals[1];
    const auto z_min = min_vals[2];
    const auto z_max = max_vals[2];

    //skip all previous vertices
    const auto num_vertices = (!obj_vertices.empty()) ?
                glm::uvec3(obj_vertices.size(),
                                   obj_vertices.size(),
                                   obj_vertices.size()) : (glm::uvec3(0, 0, 0));

    //push back the vertices of the cube
    obj_vertices.push_back(glm::vec4(x_min, y_min, z_min, 1.0f)); //0
    obj_vertices.push_back(glm::vec4(x_min, y_min, z_max, 1.0f)); //1
    obj_vertices.push_back(glm::vec4(x_min, y_max, z_max, 1.0f)); //2
    obj_vertices.push_back(glm::vec4(x_min, y_max, z_min, 1.0f)); //3
    obj_vertices.push_back(glm::vec4(x_max, y_max, z_max, 1.0f)); //4
    obj_vertices.push_back(glm::vec4(x_max, y_max, z_min, 1.0f)); //5
    obj_vertices.push_back(glm::vec4(x_max, y_min, z_min, 1.0f)); //6
    obj_vertices.push_back(glm::vec4(x_max, y_min, z_max, 1.0f)); //7

    //push back the triangles that make up the faces of the cube
    //parallel to zmin
    obj_faces.push_back(num_vertices + glm::uvec3(0, 6, 3));
    obj_faces.push_back(num_vertices + glm::uvec3(6, 5, 3));
    //parallel to zmax
    obj_faces.push_back(num_vertices + glm::uvec3(1, 7, 2));
    obj_faces.push_back(num_vertices + glm::uvec3(7, 4, 2));

    //parallel to xmin
    obj_faces.push_back(num_vertices + glm::uvec3(0, 3, 1));
    obj_faces.push_back(num_vertices + glm::uvec3(3, 2, 1));
    //parallel to xmax
    obj_faces.push_back(num_vertices + glm::uvec3(7, 6, 5));
    obj_faces.push_back(num_vertices + glm::uvec3(5, 4, 7));

    //parallel to ymin
    obj_faces.push_back(num_vertices + glm::uvec3(0, 6, 1));
    obj_faces.push_back(num_vertices + glm::uvec3(6, 7, 1));
    //parallel to ymax
    obj_faces.push_back(num_vertices + glm::uvec3(3, 5, 2));
    obj_faces.push_back(num_vertices + glm::uvec3(5, 4, 2));

}

void Menger::gen_geo_recursive(std::vector<glm::vec4>& obj_vertices,
                       std::vector<glm::uvec3>& obj_faces,
                       const int depth,
                       glm::vec3 minvals,
                       glm::vec3 maxvals)
{
    if(depth >= nesting_level_)
    {
        draw_cube(obj_vertices, obj_faces,
                  minvals, maxvals);
    }
    else
    {
        const auto x_min = minvals[0];
        const auto x_max = maxvals[0];

        //it's a cube, so these diffs should all
        //be the same lol
        auto third = (x_max - x_min)/3.f;

        for(int x = 0; x < 3; ++ x)
        {
            for(int y = 0; y < 3; ++ y)
            {
                for(int z = 0; z < 3; ++ z)
                {
                    bool empty = ((x == 1 && y == 0 && z == 1) ||
                                  (x == 1 && y == 1 && z == 0) ||
                                  (x == 1 && y == 1 && z == 1) ||
                                  (x == 0 && y == 1 && z == 1) ||
                                  (x == 1 && y == 1 && z == 2) ||
                                  (x == 2 && y == 1 && z == 1) ||
                                  (x == 1 && y == 2 && z == 1));
                    if(!empty)
                    {
                        glm::vec3 min_vec = minvals + (glm::vec3(x, y, z) * third);
                        glm::vec3 max_vec = minvals + (glm::vec3(x, y, z) * third)
                                + (glm::vec3(1.f, 1.f, 1.f) * third);
                        gen_geo_recursive(obj_vertices, obj_faces,
                                          depth + 1,
                                          glm::vec3(min_vec),
                                          glm::vec3(max_vec));
                    }
                }
            }
        }
    }
}

void
Menger::generate_geometry(std::vector<glm::vec4>& obj_vertices,
                          std::vector<glm::uvec3>& obj_faces)
{
    gen_geo_recursive(obj_vertices, obj_faces, 0,
                      glm::vec3(-.5f, -.5f, -.5f),
                      glm::vec3(.5f, .5f, .5f));
}

