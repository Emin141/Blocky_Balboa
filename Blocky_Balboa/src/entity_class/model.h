#if 0
#include "../opengl_classes/mesh_class.h"
#include "../opengl_classes/texture_class.h"
#include "../opengl_classes/shader_class.h"
#include "../cece_math/cece_vector3.h"
#include "../cece_math/cece_e_angle.h"

class Model
{
public:
    Model() = delete;
    Model(const Model &other) = delete;
    Model(Model &&other) = delete;

    Model(
        const std::string &_mesh_path,
        const std::string &_vertex_shader_path,
        const std::string &_fragment_shader_path,
        const cece::Vector3 &_world_position = {0.0f, 0.0f, 0.0f},
        const cece::EAngle &_world_orientation = {0.0f, 0.0f, 0.0f});

    ~Model();

    void draw() const;
    void set_world_position(
        const cece::Vector3 &_world_position = {0.0f, 0.0f, 0.0f},
        const cece::EAngle &_world_orientation = {0.0f, 0.0f, 0.0f}) const;

private:
    Mesh *m_mesh;
    Texture *m_texture;
    //NormalMap* m_normal_map;
    Shader *m_shader;

    cece::Vector3 m_world_position;
    cece::EAngle m_wolrd_orientation;
};

Model::Model(
    const std::string &_mesh_path,
    const std::string &_vertex_shader_path,
    const std::string &_fragment_shader_path,
    const cece::Vector3 &_world_position,
    const cece::EAngle &_world_orientation)
{
    m_mesh = new Mesh(_mesh_path);
    m_texture = nullptr;
    m_shader = new Shader(_vertex_shader_path, _fragment_shader_path);
    m_world_position = _world_position;
    m_wolrd_orientation = _world_orientation;
}

Model::~Model()
{
    delete m_mesh;
    delete m_texture;
    delete m_shader;
}
#endif