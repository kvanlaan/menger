#include "menger.h"

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
//    obj_vertices.push_back(std::vector<glm::vec4>(0.0, 0.0, 0.0, 0));
//    obj_vertices.push_back(std::vector<glm::vec4>(0.0, 0.0, 1.0, 0));
//    obj_vertices.push_back(std::vector<glm::vec4>(0.0, 1.0, 1.0, 0));
//    obj_vertices.push_back(std::vector<glm::vec4>(1.0, 1.0, 1.0, 0));
//    obj_vertices.push_back(std::vector<glm::vec4>(1.0, 1.0, 0.0, 0));
//    obj_vertices.push_back(std::vector<glm::vec4>(1.0, 0.0, 0.0, 0));
//    obj_vertices.push_back(std::vector<glm::vec4>(1.0, 1.0, 0.0, 0));
//    obj_vertices.push_back(std::vector<glm::vec4>(1.0, 0.0, 0.0, 0));
//    obj_faces.push_back();


}

