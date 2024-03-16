#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 ourPos;

uniform float XOffset;

void main() {
  gl_Position = vec4(aPos.x + XOffset, aPos.y, aPos.z, 1.0);
  ourPos = gl_Position;
}
