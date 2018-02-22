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

    obj_vertices.push_back(glm::vec4(x_min, y_min, z_min, 1.0f)); //0
    obj_vertices.push_back(glm::vec4(x_min, y_min, z_max, 1.0f)); //1
    obj_vertices.push_back(glm::vec4(x_min, y_max, z_max, 1.0f)); //2
    obj_vertices.push_back(glm::vec4(x_min, y_max, z_min, 1.0f)); //3
    obj_vertices.push_back(glm::vec4(x_max, y_max, z_max, 1.0f)); //4
    obj_vertices.push_back(glm::vec4(x_max, y_max, z_min, 1.0f)); //5
    obj_vertices.push_back(glm::vec4(x_max, y_min, z_min, 1.0f)); //6
    obj_vertices.push_back(glm::vec4(x_max, y_min, z_max, 1.0f)); //7

    //parallel to zmin
    obj_faces.push_back(num_vertices + glm::uvec3(0, 6, 3));
    obj_faces.push_back(num_vertices + glm::uvec3(6, 5, 0));
    //parallel to zmax
    obj_faces.push_back(num_vertices + glm::uvec3(1, 7, 2));
    obj_faces.push_back(num_vertices + glm::uvec3(7, 4, 2));

    //parallel to xmin
    obj_faces.push_back(num_vertices + glm::uvec3(0, 1, 3));
    obj_faces.push_back(num_vertices + glm::uvec3(1, 2, 3));
    //parallel to xmax
    obj_faces.push_back(num_vertices + glm::uvec3(6, 7, 5));
    obj_faces.push_back(num_vertices + glm::uvec3(7, 4, 5));

    //parallel to ymin
    obj_faces.push_back(num_vertices + glm::uvec3(0, 6, 1));
    obj_faces.push_back(num_vertices + glm::uvec3(6, 7, 0));
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
        const auto y_min = minvals[1];
        const auto y_max = maxvals[1];
        const auto z_min = minvals[2];
        const auto z_max = maxvals[2];

        //it's a cube, so these diffs should all
        //be the same lol
        auto third = (x_max - x_min)/3;

        auto x = x_min;
        while(x < x_max)
        {
            auto y = y_min;
            while(y < y_max)
            {
                auto z = z_min;
                while(z < z_max)
                {
                    bool empty = ((x == x_min + third && y == y_min && z == z_min + third) ||
                                (x == x_min + third && y == y_min + third && z == z_min) ||
                                (x == x_min + third && y == y_min + third && z == z_min + third) ||
                                (x == x_min && y == y_min + third && z == z_min + third) ||
                                (x == x_min + third && y == y_min + third && z == z_min + 2 * third) ||
                                (x == x_min + 2 * third && y == y_min + third && z == z_min + third) ||
                                (x == x_min + third && y == y_min + 2*third && z == z_min + third));

                    if(!empty)
                    {
                        gen_geo_recursive(obj_vertices, obj_faces,
                                          depth + 1,
                                          glm::vec3(x, y, z),
                                          glm::vec3(x+third,
                                                    y+third,
                                                    z+third));
                    }
                    z += third;
                }
                y += third;
            }
            x += third;
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

