#include <string>
#include "../opengl_classes/vao_class.h"
#include "../opengl_classes/vbo_class.h"
#include "../opengl_classes/ebo_class.h"

class Mesh
{
public:
    Mesh() = delete;
    Mesh(const Mesh &other) = delete;
    Mesh(Mesh &&other) = delete;

    Mesh(const std::string &_mesh_name,
         std::string &_out_texture_source_path);

    ~Mesh();

    void bind() const;
    void unbind() const;

    GLuint number_of_indices;

private:
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};

