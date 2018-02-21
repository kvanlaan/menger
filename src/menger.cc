#include "menger.h"
#include "glm/gtc/matrix_transform.hpp"

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

// FIXME generate Menger sponge geometry
/**
You will want to write a function which, given a list of existing vertices
(in homogeneous coordinates) and triangle indices, appends the vertices and
triangles necessary to draw a cube with diametrically-opposite corners at
arbitrary locations (minx, miny, minz) and (maxx, maxy, maxz). This will entail
appending the eight cube vertices, and enough triangles to draw all six faces
of the cube.
 */
void
Menger::generate_geometry(std::vector<glm::vec4>& obj_vertices,
                          std::vector<glm::uvec3>& obj_faces) const
{
    /*Start with a single cube
    for i = 0 to L do
        for each cube do
            Subdivide cube into 27 subcubes of one third the side length
            Delete the 7 inner subcubes
        end for
     end for*/
    /*
     * Need to add 5 sides, or 11 more triangles (we're missing one on this side)
     * -one side is rotated 90 deg on the x axis, then translated left
     * -one side is rotated 90 deg on the x axis, then translated right
     * -one side is rotated 90 deg on the y axis, then translated up
     * -one side is rotated 90 deg on the y axis, then translated down
     * -one side is translated on the z axis by the height of the triangle
     * trangles can share vertices, which is what the obj_faces/indices means
     * i'm tired
     * */
//    glm::mat4 mat = glm::translate(glm::mat4(), glm::vec3(10.0f, 10.0f, 10.0f));
//    auto mat = glm::rotate(glm::mat4(), 90.f,  glm::vec3(1.0f, 0.0f, 0.0f));
//    obj_vertices[0] = mat * obj_vertices[0];
//    obj_vertices[1] = mat * obj_vertices[1];
//    obj_vertices[2] = mat * obj_vertices[2];
//    obj_faces[0] = mat*obj_faces[0];
    obj_vertices.push_back(glm::vec4(5.0f, 0.5f, -0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(1, 3, 2));

}

