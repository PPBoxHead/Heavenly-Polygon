#ifndef HVP_SHADER_H
#define HVP_SHADER_H

#include <stdbool.h>

#include <glad/glad.h>
//#include <raymath.h>
#include <cglm/cglm.h>


// Shader object struct
typedef struct {
    GLuint ID;
} HVP_Shader;

HVP_Shader* HVP_shader_init();
void HVP_shader_destroy(HVP_Shader* shader_id);
HVP_Shader* HVP_shader_use(const HVP_Shader* shader_id);
void HVP_shader_compile(HVP_Shader* shader_id, const char* vertex_source, const char* fragment_source);

void HVP_shader_set_float(const HVP_Shader* shader_id, const char* uniform_name, float value);
void HVP_shader_set_int(const HVP_Shader* shader_id, const char* uniform_name, int value);
void HVP_shader_set_bool(const HVP_Shader* shader_id, const char* uniform_name, bool value);

void HVP_shader_set_vector2_f(const HVP_Shader* shader_id, const char* uniform_name, float x, float y);
void HVP_shader_set_vector2_v(const HVP_Shader* shader_id, const char* uniform_name, vec2* value);

void HVP_shader_set_vector3_f(const HVP_Shader* shader_id, const char* uniform_name, float x, float y, float z);
void HVP_shader_set_vector3_v(const HVP_Shader* shader_id, const char* uniform_name, vec3* value);

void HVP_shader_set_vector4_f(const HVP_Shader* shader_id, const char* uniform_name, float x, float y, float z, float w);
void HVP_shader_set_vector4_v(const HVP_Shader* shader_id, const char* uniform_name, vec4* value);

void HVP_shader_set_matrix4(const HVP_Shader* shader_id, const char* uniform_name, mat4* value);

// private
void _shader_check_compile_error(GLuint object, const char* type);


#endif // !HVP_SHADER_H

