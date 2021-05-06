#include "new_mesh_class.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

typedef struct _vec2
{
    float u, v;
} vec2;

typedef struct _vec3
{
    float x, y, z;
} vec3;

typedef struct _vertex
{
    vec3 position;
    vec2 texture_coordinate;
    vec3 normal;
} vertex;

Mesh::Mesh(const std::string &_mesh_name,
           std::string &_out_texture_source_path)
{
    std::string mesh_source_path = "./res/models/" + _mesh_name + ".obj";
    std::ifstream input_file;
    input_file.open(mesh_source_path);
    if (!input_file)
    {
        std::cerr << "Could not open mesh file at "
                  << mesh_source_path << "!\n";

        std::cin.get();
        exit(-1);
    }

    std::string text;
    std::vector<vec3> pos;
    std::vector<vec2> tex_coord;
    std::vector<vec3> normal;

    std::vector<GLuint> indices;
    std::vector<vertex> vertex_data;

    GLuint index_value = 0;
    unsigned int current = 0;
    std::map<std::string, GLuint> vertex_map;

    while (!input_file.eof())
    {
        input_file >> text;

        if (text == "v")
        {
            float x, y, z;

            input_file >> text;
            x = atof(text.c_str());

            input_file >> text;
            y = atof(text.c_str());

            input_file >> text;
            z = atof(text.c_str());

            pos.push_back({x, y, z});
        }

        if (text == "vt")
        {
            float u, v;

            input_file >> text;
            u = atof(text.c_str());

            input_file >> text;
            v = atof(text.c_str());

            tex_coord.push_back({u, v});
        }

        if (text == "vn")
        {
            float x, y, z;

            input_file >> text;
            x = atof(text.c_str());

            input_file >> text;
            y = atof(text.c_str());

            input_file >> text;
            z = atof(text.c_str());

            normal.push_back({x, y, z});
        }

        if (text == "usemtl")
        {
            input_file >> text;

            _out_texture_source_path = "./res/textures/" + text + ".png";
        }

        if (text == "f")
        {
            for (int i = 0; i < 3; i++) //because there are 3 elements
            {
                input_file >> text;
                text = text + " "; //breaks the stream, otherwise  the last stream push will overflow

                std::string unique_vertex = text;

                //removes "/" from the configuration of v/vt/vn
                for (int i = 0; i < text.length(); i++)
                {
                    if (text[i] == *"/")
                    {
                        text[i] = *" ";
                    }
                }
                std::stringstream ss;

                ss << text;
                unsigned int v = atoi(ss.str().c_str()) - 1; //-1 because 0 is the first index

                ss << text;
                unsigned int vt = atoi(ss.str().c_str()) - 1;

                ss << text;
                unsigned int vn = atoi(ss.str().c_str()) - 1;

                //making a vertex and pushing it to the vertex array
                vertex_data.push_back({pos[v], tex_coord[vt], normal[vn]});

                if (vertex_map.insert(std::make_pair(unique_vertex, index_value)).second == true)
                {
                    indices.push_back(index_value);
                    index_value++;
                }
                else
                {
                    indices.push_back(vertex_map[unique_vertex]);
                }
                current++;
            }
        }
    }

#ifdef MESH_PARSING_DEBUG
    std::cout << "In position vector: " << std::endl;
    for (const auto &i : pos)
    {
        std::cout << i.x << " " << i.y << " " << i.z << std::endl;
    }
    std::cout << std::endl;

    std::cout << "In tex_coord vector: " << std::endl;
    for (const auto &i : tex_coord)
    {
        std::cout << i.u << " " << i.v << std::endl;
    }
    std::cout << std::endl;

    std::cout << "In normal vector: " << std::endl;
    for (const auto &i : normal)
    {
        std::cout << i.x << " " << i.y << " " << i.z << std::endl;
    }
    std::cout << std::endl;

    std::cout << "In indices vector: " << std::endl;
    int count = 0;
    for (const auto &i : indices)
    {
        std::cout << i << " ";
        if ((count + 1) % 3 == 0)
            std::cout << std::endl;
        count++;
    }
    std::cout << std::endl;

    std::cout << "In vertex data vector: " << std::endl;
    for (const auto &i : vertex_data)
    {
        std::cout << i.position.x << " " << i.position.y << " " << i.position.z << ", "
                  << i.texture_coordinate.u << " " << i.texture_coordinate.v << ", "
                  << i.normal.x << " " << i.normal.y << " " << i.normal.z << std::endl;
    }
#endif

    m_vao.Bind();

    GLfloat *f_vertex_data = new GLfloat[vertex_data.size() * 8];
    int i = 0;
    for (const auto &element : vertex_data)
    {
        f_vertex_data[i] = element.position.x;
        i++;
        f_vertex_data[i] = element.position.y;
        i++;
        f_vertex_data[i] = element.position.z;
        i++;
        f_vertex_data[i] = element.texture_coordinate.u;
        i++;
        f_vertex_data[i] = element.texture_coordinate.v;
        i++;
        f_vertex_data[i] = element.normal.x;
        i++;
        f_vertex_data[i] = element.normal.y;
        i++;
        f_vertex_data[i] = element.normal.z;
        i++;
    }

#ifdef MESH_PARSING_DEBUG
    std::cout << "\nIn GLfloat array: " << std::endl;
    for (int i = 0; i < vertex_data.size() * 8; i++)
    {
        std::cout << f_vertex_data[i] << ", ";
        if ((i + 1) % 8 == 0)
            std::cout << std::endl;
    }
#endif

    m_vbo = VBO(f_vertex_data, vertex_data.size() * 8 * sizeof(GLfloat));
    delete[] f_vertex_data;

    GLuint *ui_indices = new GLuint[indices.size()];
    i = 0;
    for (const auto &element : indices)
    {
        ui_indices[i] = element;
        i++;
    }

#ifdef MESH_PARSING_DEBUG
    std::cout << "\nIn ui_indices array: " << std::endl;
    for (int i = 0; i < indices.size(); i++)
    {
        std::cout << ui_indices[i] << " ";
        if ((i + 1) % 3 == 0)
            std::cout << std::endl;
    }
#endif

    m_ebo = EBO(ui_indices, indices.size() * sizeof(GLuint));
    delete[] ui_indices;

    m_vbo.Bind();
    m_ebo.Bind();

    m_vao.LinkAttrib(m_vbo, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void *)(0 * sizeof(GLfloat)));
    m_vao.LinkAttrib(m_vbo, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    m_vao.LinkAttrib(m_vbo, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void *)(5 * sizeof(GLfloat)));

    m_vao.Unbind();
    m_vbo.Unbind();
    m_ebo.Unbind();

    number_of_indices = indices.size();

#ifdef MESH_PARSING_DEBUG
    std::cout << "\n"
              << number_of_indices << std::endl;
#endif
}

void Mesh::bind() const
{
    m_vao.Bind();
    m_vbo.Bind();
    m_ebo.Bind();
}

void Mesh::unbind() const
{
    m_vao.Unbind();
    m_vbo.Unbind();
    m_ebo.Unbind();
}

Mesh::~Mesh()
{
    m_vao.Unbind();
    m_vbo.Unbind();
    m_ebo.Unbind();

    m_vao.Delete();
    m_vbo.Delete();
    m_ebo.Delete();
}