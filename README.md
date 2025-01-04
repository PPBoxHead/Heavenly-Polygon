
# Heavenly Polygon

Heavenly Polygon it's a project meant to be a 3D framework (maybe a Fantasy Console in the future) using C and OpenGL 3.3, evocating the PS1 aesthetics with a main focus on 3D rendering rather than 2D rendering (at least at the moment I'm writing this).

It intended to use premake5 as build system, but at the moment the focus is on use with Visual Studio 2022 in Windows platforms.


## Features

Note that at the moment of writing this (05/012/2024) may not all the features could be implemented yet.

- 3D retro-style rendering (need to see if use Z-Buffer or use Ordering Tables for depth testing)
- Vertex jittering, texture affine mapping and per-vertex lighting
- 3 types of 3D shading:
    - `HVPGPU_MODEL_SHADING_UNSHADED` <--- unshaded model
    - `HVPGPU_MODEL_SHADING_FLAT` <--- flat shading
    - `HVPGPU_MODEL_SHADING_GOURAUD` <--- gouraud shading using vertex shading
- 4 types of 3D blending:
    - `HVPGPU_BLEND_OPAQUE` <--- blend models opaque
    - `HVPGPU_BLEND_ADD` <--- blend models in a additive manner
    - `HVPGPU_BLEND_SUB` <--- blend models in a substractive manner
    - `HVPGPU_BLEND_ALPHA` <--- support alpha in models textures and so (need to confirm yet)


## Dependencies

Heavenly Polygon often relies on the use of single-header or static libraries. I did it like this due to how simple it is to setup and add the kind of libraries which will be listered right here:

- [ ] C (emedded in Lua?)
- [x] OpenGL 3.3 (3D and 2D graphics) <-- GLAD
- [ ] OpenAL (audio)
- [x] GLFW (window and input handler)
- [x] cglm (math library)
- [x] cgltf (glTF/glb loader)
- [ ] free_type (font loader)
- [x] stb_image (image loading)
