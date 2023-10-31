#version 440 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 fragColour;

void main() {

	fragColour = aCol;
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0f);
}