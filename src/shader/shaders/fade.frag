#version 330 core

uniform float time;

out vec4 finalColor;

void main() {
	finalColor = vec4(0, 0, 0, time);
}
