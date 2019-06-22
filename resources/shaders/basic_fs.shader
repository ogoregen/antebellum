
#version 330 core

out vec4 FragColor;
in vec2 t_coord;

uniform sampler2D oursampler;

void main(){

	FragColor = texture(oursampler, t_coord);
}
