#ifndef MENGER_H
#define MENGER_H

#include <glm/glm.hpp>
#include <vector>

class Menger {
public:
	Menger();
	~Menger();
	void set_nesting_level(int);
	bool is_dirty() const;
	void set_clean();
	void generate_geometry(std::vector<glm::vec4>& obj_vertices,
                           std::vector<glm::uvec3>& obj_faces);
private:
	int nesting_level_ = 0;
	bool dirty_ = false;
    void draw_cube(std::vector<glm::vec4>& obj_vertices,
                      std::vector<glm::uvec3>& obj_faces,
                      glm::vec3 min_vals,
                      glm::vec3 max_vals);
    void gen_geo_recursive(std::vector<glm::vec4>& obj_vertices,
                           std::vector<glm::uvec3>& obj_faces,
                           const int depth,
                           glm::vec3 minvals,
                           glm::vec3 maxvals);
};

#endif
