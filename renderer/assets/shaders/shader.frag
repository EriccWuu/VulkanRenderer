#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 inTexcoord;
layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D Sampler;

layout(push_constant) uniform PC {
    vec3 color;
} pc;

void main() {
    // outColor = vec4(pc.color, 1.0);
    outColor = texture(Sampler, inTexcoord);
}