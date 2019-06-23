# antebellum
a simple rts game, and more
## dependencies: ##
* [GLFW](https://www.glfw.org "GLFW")
* [GLEW](http://glew.sourceforge.net "GLEW")
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h "stb_image")
* [glm](https://github.com/g-truc/glm "glm")
* [imgui](https://github.com/ocornut/imgui "imgui")

## instructions to get something drawn: ##
* create a texture object
```c++
texture yourcooltexture(const char* path);
```
* create a thing object. specifying a count greater than 1 enables rendering with instancing. you do not need to specify an array if your count is 1
```c++
thing yourthing(float width, float height, unsigned int count, glm::vec2 positions[]);
```
* in the game loop:
  * create your model matrix with your position data
  * pass the matrix to the shader multiplying by projection and view matrices
  * bind your texture
  * call your thing's display method
```c++
glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0));
basic.setUmat4f("mvp", proj * view * model);
yourcooltexture.bind();
yourthing.display();
```
_you do not need to create or edit shaders as the default ones created for our program seem to be sufficient_
