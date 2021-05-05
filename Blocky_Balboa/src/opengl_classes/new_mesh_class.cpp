#include "new_mesh_class.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

typedef struct _vec2
{
    float u, v;
} vec2;

typedef struct _vec3
{
    float x, y, z;
} vec3;

typedef vec3 vertex_position;
typedef vec2 vertex_texture_coordinate;
//add a normal coordinate too

typedef struct _vertex
{
    vertex_position position;
    vertex_texture_coordinate texture_coordinate;
} vertex;

Mesh::Mesh(const std::string &_mesh_source_path,
           std::string &_out_texture_source_path)
{
    std::ifstream input_file;
    input_file.open(_mesh_source_path);
    if (!input_file)
    {
        std::cerr << "Could not open mesh file at "
                  << _mesh_source_path << "!\n";

        std::cin.get();
        exit(-1);
    }

    std::string text;
    std::vector<vec3> pos;
    std::vector<vec2> tex_coord;
    std::vector<vec3> normal; //unimplemented

    std::vector<GLuint> indices;
    std::vector<vertex> vertex_data;

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

        ////////////////////////////////////////////////////////////////
        //Vertex normals not supported yet
        ////////////////////////////////////////////////////////////////

        // if (text == "vn")
        // {
        //     float x, y, z;

        //     input_file >> text;
        //     x = atof(text.c_str());

        //     input_file >> text;
        //     y = atof(text.c_str());

        //     input_file >> text;
        //     z = atof(text.c_str());

        //     normal.push_back({x, y, z});
        // }

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

                //removes "/" from the configuration of v/vt/vn
                for (int i = 0; i < text.length(); i++)
                {
                    if (text[i] == *"/")
                    {
                        text[i] = *" ";
                    }
                }
                std::stringstream ss;
                std::string value;

                //parsing the v value in f
                ss << text;
                ss >> value;

                //passing the v value to uint and to the index array
                unsigned int v = atoi(value.c_str()) - 1; //-1 because 0 is the first index
                indices.push_back(v);

                ss << text;
                ss >> value;
                unsigned int vt = atoi(value.c_str()) - 1;

                //unimplemented
                //ss << text;
                //ss >> value;
                //unsigned int vn = atoi(value.c_str()) - 1;

                //making a vertex and pushing it to the vertex array
                vertex_data.push_back({pos[v], tex_coord[vt]});
            }
        }
    }

#ifdef MESH_PARSING_DEBUG
    for (auto i : pos)
    {
        std::cout << i.x << " " << i.y << " " << i.z << std::endl;
    }
    std::cout << std::endl;
    for (auto i : tex_coord)
    {
        std::cout << i.u << " " << i.v << std::endl;
    }
    std::cout << std::endl;
    int count = 0;
    for (auto i : indices)
    {
        std::cout << i << " ";
        if ((count + 1) % 3 == 0)
            std::cout << std::endl;
        count++;
    }
    std::cout << std::endl;

    for (auto i : vertex_data)
    {
        std::cout << i.position.x << " " << i.position.y << " " << i.position.z
                  << ", " << i.texture_coordinate.u << " " << i.texture_coordinate.v << std::endl;
    }
#endif

    m_vao.Bind();

    GLfloat *f_vertex_data = new GLfloat[vertex_data.size() * 5];
    int i = 0;
    for (auto element : vertex_data)
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
    }

#ifdef MESH_PARSING_DEBUG
    for (int i = 0; i < vertex_data.size() * 5; i++)
    {
        std::cout << f_vertex_data[i] << " ";
        if ((i + 1) % 5 == 0)
            std::cout << std::endl;
    }
#endif

    m_vbo = VBO(f_vertex_data, 5 * vertex_data.size() * sizeof(float));
    delete[] f_vertex_data;

    GLuint *ui_indices = new GLuint[indices.size()];
    i = 0;
    for (auto element : indices)
    {
        ui_indices[i] = element;
        i++;
    }

#ifdef MESH_PARSING_DEBUG
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

    m_vao.LinkAttrib(m_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);
    m_vao.LinkAttrib(m_vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    m_vao.Unbind();
    m_vbo.Unbind();
    m_ebo.Unbind();

    number_of_indices = indices.size();
    std::cout << number_of_indices << std::endl;
}

void Mesh::bind() const
{
    m_vao.Bind();
    //m_vbo.Bind();
    m_ebo.Bind();
}

void Mesh::unbind() const
{
    m_vao.Unbind();
    //m_vbo.Unbind();
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