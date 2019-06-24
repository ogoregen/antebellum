# antebellum
a simple rts game, currently under developement
## dependencies: ##
* [GLFW](https://www.glfw.org "GLFW")
* [GLEW](http://glew.sourceforge.net "GLEW")
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h "stb_image")
* [stb_perlin](https://github.com/nothings/stb/blob/master/stb_perlin.h "stb_perlin")
* [glm](https://github.com/g-truc/glm "glm")
* [imgui](https://github.com/ocornut/imgui "imgui")

## instructions to get something drawn: ##
* create a texture object
```c++
texture yourcooltexture(const char* path);
```
* create a thing object
```c++
thing yourthing(float width, float height);
```
specifying count enables rendering with instancing. you do not need to specify an array or count if you want to draw one object at a time
```c++
thing yourthing(float width, float height, unsigned int count, glm::vec2 positions[]);
```
* in the game loop:
  * create a model matrix with your position data
  * pass the matrix to the shader multiplying by projection, scale and view matrices
  * bind your texture
  * call your thing's display method
```c++
glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0));
basic.setUmat4f("mvp", proj * view * model * scale);
yourcooltexture.bind();
yourthing.display();
```
_you do not need to create or edit shaders as the default ones created for our program are sufficient_

# #

#### download full vs project including libraries [here](http://catheart.xyz/antebellum.rar "source"). (don't forget to update source codes) ####
#### collaborator: [@perought](https://github.com/perought "perought") ####
feel free to let us know about anything about the project
