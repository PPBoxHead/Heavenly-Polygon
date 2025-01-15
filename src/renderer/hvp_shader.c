#include "hvp_shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/console_logger.h"


// Allocates MoonStation shader into memory and creates a shader with a <shader_id> of index <0>.
HVP_Shader* HVP_shader_init() {
    HVP_Shader* shader = (HVP_Shader*)malloc(sizeof(HVP_Shader));
    if (shader)
    {
        shader->ID = 0; // Initial value, will be updated later
    }
    return shader;
}
// Frees the MoonStation shader specified at <shader_id> from memory.
void HVP_shader_destroy(HVP_Shader* shader_id) {
    if (shader_id)
        glDeleteProgram(shader_id->ID);
        free(shader_id);
}
// Sets the specified <shader_id> as the active shader.
HVP_Shader* HVP_shader_use(HVP_Shader* shader_id) {
    glUseProgram(shader_id->ID);
    return shader_id;
}
// Compiles the <shader_id> using the <vertex_source> and <fragment_source>
void HVP_shader_compile(HVP_Shader* shader_id, const char* vertex_source, const char* fragment_source) {
    if (!shader_id || !vertex_source || !fragment_source) {
        console_print(C_ERROR, "Invalid parameters to HVP_shader_compile");
        return;
    }

    // create and compile a vertex shader from the vertex source
    GLuint vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    _shader_check_compile_error(vertex_shader, "VERTEX");

    // create and compile a fragment shader from the fragment source
    GLuint fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);
    _shader_check_compile_error(fragment_shader, "FRAGMENT");

    // create the shader program
    shader_id->ID = glCreateProgram();
    glAttachShader(shader_id->ID, vertex_shader);
    glAttachShader(shader_id->ID, fragment_shader);
    glLinkProgram(shader_id->ID);
    _shader_check_compile_error(shader_id->ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

// Set a floating point value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
void HVP_shader_set_float(const HVP_Shader* shader_id, const char* uniform_name, float value) {
    glUniform1f(glGetUniformLocation(shader_id->ID, uniform_name), value);
}
// Set a interger value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
void HVP_shader_set_int(const HVP_Shader* shader_id, const char* uniform_name, int value) {
    glUniform1i(glGetUniformLocation(shader_id->ID, uniform_name), value);
}
// Set a bool value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
void HVP_shader_set_bool(const HVP_Shader* shader_id, const char* uniform_name, bool value) {
    glUniform1i(glGetUniformLocation(shader_id->ID, uniform_name), (int)value);
}

// Set a Vector2 value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
// This uses an approximation when you set Vector2 <x> and <y> values as independent values.
void HVP_shader_set_vector2_f(const HVP_Shader* shader_id, const char* uniform_name, float x, float y) {
    glUniform2f(glGetUniformLocation(shader_id->ID, uniform_name), x, y);
}
// Set a Vector2 value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
// This uses an approximation when you set Vector2 <x> and <y> values as a <cglm> Vector2 struct.
void HVP_shader_set_vector2_v(const HVP_Shader* shader_id, const char* uniform_name, vec2* value) {
    glUniform2fv(glGetUniformLocation(shader_id->ID, uniform_name), 1, (float*)value);
}

// Set a Vector3 value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
// This uses an approximation when you set Vector3 <x>,<y> and <z> values as independent values.
void HVP_shader_set_vector3_f(const HVP_Shader* shader_id, const char* uniform_name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(shader_id->ID, uniform_name), x, y, z);
}
// Set a Vector3 value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
// This uses an approximation when you set Vector3 <x>,<y> and <z> values as a <cglm> Vector3 struct.
void HVP_shader_set_vector3_v(const HVP_Shader* shader_id, const char* uniform_name, vec3* value) {
    glUniform3fv(glGetUniformLocation(shader_id->ID, uniform_name), 1, (float*)value);
}

// Set a Vector4 value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
// This uses an approximation when you set Vector4 <x>,<y>,<z> and <w> values as independent values.
void HVP_shader_set_vector4_f(const HVP_Shader* shader_id, const char* uniform_name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(shader_id->ID, uniform_name), x, y, z, w);
}
// Set a Vector4 value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
// This uses an approximation when you set Vector3 <x>,<y>,<z> and <w> values as a <cglm> Vector4 struct.
void HVP_shader_set_vector4_v(const HVP_Shader* shader_id, const char* uniform_name, vec4* value) {
    glUniform4fv(glGetUniformLocation(shader_id->ID, uniform_name), 1, (float*)value);
}

// Set a Matrix value to the shader specified by <shader_id> and pointing to the specified <uniform_name> in the shader.
// This uses an approximation when you set Matrix values as a <cglm> Matrix struct.
void HVP_shader_set_matrix4(const HVP_Shader* shader_id, const char* uniform_name, mat4* value) {
    glUniformMatrix4fv(glGetUniformLocation(shader_id->ID, uniform_name), 1, GL_FALSE, (float*)value);
}

// Check for and report errors that occur during the compilation or linking of a shader.
// First checks if the <type> of the <object> (shader or program) passed to it is "PROGRAM" or not.
// If it is not a "PROGRAM", the function assumes it's a shader object (like a vertex, fragment, or geometry shader).
void _shader_check_compile_error(GLuint object, const char* type) {
    int success;
    char info_log[1024];

    if (strcmp(type, "PROGRAM") != 0)
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, sizeof(info_log), NULL, info_log);
            console_print(C_ERROR, "Compile-time error, Type: %s %s", type, info_log);
        }
    }
    else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, sizeof(info_log), NULL, info_log);
            console_print(C_ERROR, "Link-time error, Type: %s %s", type, info_log);
        }
    }
}
