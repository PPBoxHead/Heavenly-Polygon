#ifndef HVP_MESH_H
#define HVP_MESH_H

#include <glad/glad.h>

#include "hvp_vertex.h"


// Heavenly Polygon Mesh Data
typedef struct {
	// Private member variables
	HVP_Vertex* m_vertices;

	GLuint* m_indices;
	size_t m_vertex_count;
	size_t m_index_count;

	// Public member variables
	char* mesh_name;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
} HVP_Mesh;



#endif // !HVP_MESH_H
