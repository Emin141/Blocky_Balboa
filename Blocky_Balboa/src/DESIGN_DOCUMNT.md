////////////////////////////////////////////////////////////////
Player
////////////////////////////////////////////////////////////////
Player is a class that has an entity that also has a camera attached to it. Therefore, the player has a model view projection matrix that can be returned and assigned to the global mvp matrix.

////////////////////////////////////////////////////////////////
Entity
////////////////////////////////////////////////////////////////
Entity is a class that has a model, a collision box, physical properties such as position, rotation, maximum velocity, mass (for collisions), intrinsic acceleration (or a LERP for velocity), etc.

The Entity class needs to be have:
    - a draw call
    - a move call
    - a rotation call (possibly able to be done inside the move call)

The draw call of the entity class calls the draw method of the model member.

The move call of the entity class calls the set_world_position method of the model member. It also checks for collision by calling a collision check method of the collision box member. This will be implemented later.

The rotation call of the entity class calls the set_world_rotation method of the model member. No need to check for collision.

////////////////////////////////////////////////////////////////
Model
////////////////////////////////////////////////////////////////
The model class has a Mesh class, a Texture class, and a Shader class. It also has world position and rotation, which are set by the Entity is attached to. The model class needs to have:
    - a draw call
    - a set_world_position call
    - a set_world_rotation call

The draw call binds the texture, the mesh and the shader, then calls the appropriate GL function. It then unbinds all of the mentioned objects. 

The set_world_rotation call just updates a vec3 uniform to the model_matrix uniform in the shader program. The same goes for the set_world_rotation call.

////////////////////////////////////////////////////////////////
Mesh
////////////////////////////////////////////////////////////////
The Mesh class needs to have the VAO, VBO, EBO which it reads from a source file. This is the complex part as the parsing needs to be done in such a way that even if the number of vertices per element are not the same, the number of indices needs to align.
The constructor should also take in an out parameter for the texture path. In the .obj model file (renamed to .wfo in this project), there is a line that states the name of the "material" (read as "texture") used by the .wfo. That out parameter string needs to have "./res/textures/" appeneded to the front and ".png" to the back in order to specify the texture source path properly.
The only parameters that need to exist inside the Mesh are ID of the VAO, VBO, and EBO. All other objects and variables can be stack allocated and scoped to free memory. The Mesh class needs to have a Bind and Unbind method. The Bind method binds the VAO and EBO, and the unbind the opposite.