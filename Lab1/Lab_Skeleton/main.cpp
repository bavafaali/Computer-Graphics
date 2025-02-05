#include <iostream>
#include <fstream>
#include <sstream>

// GLEW
#define GLEW_STATIC	    
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "camera.h" //algebra is included in camera.h
#include "shaders.h"
#include "mesh.h"

Camera cam = {{30, 0, 40}, {0, 30, 0}, 80, 1, 10000}; // Setup the global camera parameters
ProjectionMode projMode = PERSPECTIVE;
int screen_width = 1024;
int screen_height = 768;

Mesh *meshList = NULL; // Global pointer to linked list of triangle meshes

GLuint shprg; // Shader program id
// Create a GLFWwindow object that we can use for GLFW's functions
GLFWwindow *window;
// Global transform matrices
// V is the view transform
// P is the projection transform
// PV = P * V is the combined view-projection transform
Matrix V, W, M, P, PV;

std::string LoadShaderFromFile(const std::string& filename)
{
    std::string result = "";
    std::string line = "";
    std::ifstream myFile(filename.c_str());
    
    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            result += line + '\n';
        }
        myFile.close();
    } else {
        printf("error \n");
    }
    
    return result;
}

bool compileShader(const char **shader_src, GLenum shader_type, GLuint *shader_handle)
{
	GLint isCompiled = GL_FALSE;
	*shader_handle = glCreateShader(shader_type);
	glShaderSource(*shader_handle, 1, shader_src, NULL);
	glCompileShader(*shader_handle);
	glGetShaderiv(*shader_handle, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(*shader_handle, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
//		std::vector<GLchar> errorLog(maxLength);
//		glGetShaderInfoLog(*shader_handle, maxLength, &maxLength, &errorLog[0]);
//		for (auto &&c : errorLog)
//		{
//			std::cerr << c;
//		}
//		std::cerr << "\n";

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(*shader_handle); // Don't leak the shader.
        return;
	}

	if (!isCompiled)
	{
		fprintf(stderr, "Error in vertex shader!\n");
		return false;
	}
	else
		fprintf(stdin, "Vertex shader compiled successfully!\n");
	return true;
}

void prepareShaderProgram(const char **vs_src, const char **fs_src)
{
	GLint isCompiled = GL_FALSE;

	shprg = glCreateProgram();
	GLuint vs, fs;
	if (compileShader(vs_src, GL_VERTEX_SHADER, &vs) &&
		compileShader(fs_src, GL_FRAGMENT_SHADER, &fs))
	{
		glAttachShader(shprg, vs);
		glAttachShader(shprg, fs);
		glLinkProgram(shprg);
		GLint isLinked = GL_FALSE;
		glGetProgramiv(shprg, GL_LINK_STATUS, &isLinked);
		if (!isLinked)
			printf("Link error in shader program!\n");
		else
			printf("Shader program linked successfully!\n");
	}
	else
		fprintf(stderr, "There were errors during shader compilation\n");
}

void prepareMesh(Mesh *mesh)
{
	int sizeVerts = mesh->nv * 3 * sizeof(float);
	int sizeCols = mesh->nv * 3 * sizeof(float);
	int sizeTris = mesh->nt * 3 * sizeof(int);

	// For storage of state and other buffer objects needed for vertex specification
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	// Allocate VBO and load mesh data (vertices and normals)
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeVerts + sizeCols, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVerts, (void *)mesh->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeVerts, sizeCols, (void *)mesh->vnorms);

	// Allocate index buffer and load mesh indices
	glGenBuffers(1, &mesh->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeTris, (void *)mesh->triangles, GL_STATIC_DRAW);

	// Define the format of the vertex data
	GLint vPos = glGetAttribLocation(shprg, "vPos");
	glEnableVertexAttribArray(vPos);
	glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Define the format of the vertex data
	GLint vNorm = glGetAttribLocation(shprg, "vNorm");
	glEnableVertexAttribArray(vNorm);
	glVertexAttribPointer(vNorm, 3, GL_FLOAT, GL_FALSE, 0, (void *)(mesh->nv * 3 * sizeof(float)));

	glBindVertexArray(0);
}

void renderMesh(Mesh *mesh)
{

	// Assignment 1: Apply the transforms from local mesh coordinates to world coordinates here
	// Combine it with the viewing transform that is passed to the shader below
    W = ModelTranform(mesh->scale, mesh->rotate, mesh->translate);
    M = MatMatMul(V, W);
    // This finds the combined view-projection matrix
    PV = MatMatMul(P, M);
    
	// Pass the viewing transform to the shader
	GLint loc_PV = glGetUniformLocation(shprg, "PV");
	glUniformMatrix4fv(loc_PV, 1, GL_FALSE, PV.e);

	// Select current resources
	glBindVertexArray(mesh->vao);

	// To accomplish wireframe rendering (can be removed to get filled triangles)
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    
	// Draw all triangles
	glDrawElements(GL_TRIANGLES, mesh->nt * 3, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

//void changeSize(int w, int h) {
//    screen_width = w;
//    screen_height = h;
//    glViewport(0, 0, screen_width, screen_height);
//
//}

void display(void)
{
	Mesh *mesh;

    // Clear the colorbuffer
	//glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	TODO: Assignment 1: The implementation of View- and ProjectionMatrix in camera.cpp
	returns hardcoded matrices. Your assignment is to fix them.
	*/
	V = ViewMatrix(cam);

	P = ProjectionMatrix(cam, screen_width, screen_height, projMode);

	// Select the shader program to be used during rendering
	glUseProgram(shprg);

	// Render all meshes in the scene
	mesh = meshList;

	while (mesh != NULL)
	{
		renderMesh(mesh);
		mesh = mesh->next;
	}

	glFlush();
}

void init(void)
{
	// Compile and link the given shader program (vertex shader and fragment shader)
	prepareShaderProgram(vs_n2c_src, fs_ci_src);

	// Setup OpenGL buffers for rendering of the meshes
	Mesh *mesh = meshList;
	while (mesh != NULL)
	{
		prepareMesh(mesh);
		mesh = mesh->next;
	}
}
// Include data for some triangle meshes (hard coded in struct variables)
#include "./models/mesh_bunny.h"
#include "./models/mesh_cow.h"
#include "./models/mesh_cube.h"
#include "./models/mesh_frog.h"
#include "./models/mesh_knot.h"
#include "./models/mesh_sphere.h"
#include "./models/mesh_teapot.h"
#include "./models/mesh_triceratops.h"
static void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	// Terminate early if it is not a keypress
	if (action == GLFW_RELEASE)
		return;

	switch (key)
	{
	case GLFW_KEY_ESCAPE:
	case GLFW_KEY_Q:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
            
    case GLFW_KEY_P:
    {
        if (projMode == PERSPECTIVE)
            projMode = ORTHOGONAL;
        else
            projMode = PERSPECTIVE;
        break;
    }
            
    //position
    case GLFW_KEY_X:
    {
        if(mods & GLFW_MOD_SHIFT)
            cam.position.x += 0.5f;
        else
            cam.position.x -= 0.5f;
        
        break;
        
    }
    case GLFW_KEY_Y:
    {
        if(mods & GLFW_MOD_SHIFT)
            cam.position.y += 0.5f;
        else
            cam.position.y -= 0.5f;
        break;
    }
    case GLFW_KEY_Z:
    {
        if(mods & GLFW_MOD_SHIFT)
            cam.position.z += 0.5f;
        else
            cam.position.z -= 0.5f;
        break;
    }
    //rotation
    case GLFW_KEY_I:
    {
        if(mods & GLFW_MOD_SHIFT)
            cam.rotation.x += 0.5f;
        else
            cam.rotation.x -= 0.5f;
        break;
    }
    case GLFW_KEY_J:
    {
        if(mods & GLFW_MOD_SHIFT)
            cam.rotation.y += 0.5f;
        else
            cam.rotation.y -= 0.5f;
        break;
    }
    case GLFW_KEY_K:
    {
        if(mods & GLFW_MOD_SHIFT)
            cam.rotation.z += 0.5f;
        else
            cam.rotation.z -= 0.5f;
        break;
    }
    
    // model interaction
    case GLFW_KEY_1:
    {
        if (mods & GLFW_MOD_SHIFT)
        {
            meshList->translate.x += 0.5;
            //meshList->rotate.x += 0.5;
            //meshList->scale.x += 0.5;
        } else
        {
            meshList->translate.x -= 0.5;
            //meshList->rotate.x -= 0.5;
            //meshList->scale.x -= 0.5;
        }
        break;
    }
    case GLFW_KEY_2:
    {
        if (mods & GLFW_MOD_SHIFT)
        {
            meshList->translate.y += 0.5;
            //meshList->rotate.y += 0.5;
            //meshList->scale.y += 0.5;
        } else
        {
            meshList->translate.y -= 0.5;
            //meshList->rotate.y -= 0.5;
            //meshList->scale.y -= 0.5;
        }
        break;
    }
    case GLFW_KEY_3:
    {
        if (mods & GLFW_MOD_SHIFT)
        {
            meshList->translate.z += 0.5;
            //meshList->rotate.z += 0.5;
            //meshList->scale.z += 0.5;
        } else
        {
            meshList->translate.z -= 0.5;
            //meshList->rotate.z -= 0.5;
            //meshList->scale.z -= 0.5;
        }
        break;
    }
            
    case GLFW_KEY_TAB:
    {
        if (action == GLFW_PRESS)
            if(meshList->next != NULL)
                meshList = meshList->next;
        break;
    }
	default:
		break;
	}
}

void Setup_GLFW()
{
	// Init GLFW
	glfwInit();
	glfwSetErrorCallback(error_callback);
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

int CreateGLFWWindow(GLFWwindow **window, GLint width, GLint height)
{
	*window = glfwCreateWindow(width, height, "DVA338 Lab Program", nullptr, nullptr);
	if (nullptr == *window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}
	glfwSetKeyCallback(*window, key_callback);

	glfwMakeContextCurrent(*window);
	return 0;
}

void constructScene(Mesh **meshList)
{
    // COW transforms
    Vector cowTrans = {10, 0, 0};
    Vector cowRotate = {0, 90, 0};
    Vector cowScale = {1, 1, 1};
    
    Vector cowTrans2 = {0, 30, -40};
    Vector cowRotate2 = {0, 0, 0};
    Vector cowScale2 = {3, 1, 1};
    
    // TRICERATOPS transforms
    Vector triTrans = {-25, 0, 0};
    Vector triRotate = {60, 0, 0};
    Vector triScale = {1, 1, 1};
    
//    insertModel(meshList, cow.nov, cow.verts, cow.nof, cow.faces, cowTrans, cowRotate, cowScale, 20.0);
//    insertModel(meshList, cow.nov, cow.verts, cow.nof, cow.faces, cowTrans2, cowRotate2, cowScale2, 20.0);
//    insertModel(meshList, triceratops.nov, triceratops.verts, triceratops.nof, triceratops.faces, triTrans, triRotate, triScale, 3.0);
    //insertModel(&meshList, bunny.nov, bunny.verts, bunny.nof, bunny.faces, 60.0);
    //insertModel(&meshList, cube.nov, cube.verts, cube.nof, cube.faces, 5.0);
    //insertModel(&meshList, frog.nov, frog.verts, frog.nof, frog.faces, 2.5);
    insertModel(meshList, knot.nov, knot.verts, knot.nof, knot.faces, cowRotate2, cowRotate2, triScale, 1.0);
//    insertModel(meshList, sphere.nov, sphere.verts, sphere.nof, sphere.faces, cowRotate2, cowRotate2, cowScale, 12.0);
    //insertModel(&meshList, teapot.nov, teapot.verts, teapot.nof, teapot.faces, 3.0);
}

void MainLoop()
{
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed,
		// mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render

		// Draw OpenGL
		display();

		glfwSwapBuffers(window);
	}
}

// The MAIN function, from here we start the application and run the game loop
int main()
{
	Setup_GLFW();
	if (EXIT_FAILURE == CreateGLFWWindow(&window, screen_width, screen_height))
	{
		return EXIT_FAILURE;
	}

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	fprintf(stdout, "GLEW version: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "OpenGL version: %s\n", (const char *)glGetString(GL_VERSION));

	int screenWidth, screenHeight;
	// Define the viewport dimensions
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);

	constructScene(&meshList);

	init();
	MainLoop();

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return EXIT_SUCCESS;
}
