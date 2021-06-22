#version 330 core

in vec3 vertex;
in vec3 color;

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

uniform int indexColor;

out vec3 fcolor;

void main() {
    if(indexColor == 3)  fcolor = vec3(0.2, 0.2, 0.2);
    else fcolor = color;
    
    gl_Position = Proj * View * TG * vec4 (vertex, 1.0);
}
