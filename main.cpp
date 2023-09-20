//#####################################################################
// Main
// Dartmouth COSC 77/177 Computer Graphics, starter code
// Contact: Bo Zhu (bo.zhu@dartmouth.edu)
//#####################################################################
#include <iostream>
#include <random>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "Common.h"
#include "Driver.h"
#include "OpenGLMesh.h"
#include "OpenGLCommon.h"
#include "OpenGLWindow.h"
#include "OpenGLViewer.h"
#include "OpenGLMarkerObjects.h"
#include "TinyObjLoader.h"

#ifndef __Main_cpp__
#define __Main_cpp__

#ifdef __APPLE__
#define CLOCKS_PER_SEC 100000
#endif

class FinalProjectDriver : public Driver, public OpenGLViewer
{using Base=Driver;
	std::vector<OpenGLTriangleMesh*> mesh_object_array;						////mesh objects, every object you put in this array will be rendered.
	clock_t startTime;

public:
	virtual void Initialize()
	{
		draw_bk=false;						////turn off the default background and use the customized one
		draw_axes=false;						////if you don't like the axes, turn them off!
		startTime=clock();
		OpenGLViewer::Initialize();
	}

	void Add_Shaders()
	{
		////format: vertex shader name, fragment shader name, shader name
		OpenGLShaderLibrary::Instance()->Add_Shader_From_File("background.vert","background.frag","background");

		////SHADOW TODO: uncomment next three lines to import shadow shaders
		//OpenGLShaderLibrary::Instance()->Add_Shader_From_File("object_1_shadow.vert","object_1_shadow.frag","object_1_shadow");	
		//OpenGLShaderLibrary::Instance()->Add_Shader_From_File("object_2_shadow.vert","object_2_shadow.frag","object_2_shadow");	
		//OpenGLShaderLibrary::Instance()->Add_Shader_From_File("object_3_shadow.vert","object_3_shadow.frag","object_3_shadow");	

		////SHADOW TODO: comment out next three lines
		OpenGLShaderLibrary::Instance()->Add_Shader_From_File("object_1.vert","object_1.frag","object_1");	
		OpenGLShaderLibrary::Instance()->Add_Shader_From_File("object_2.vert","object_2.frag","object_2");	
		OpenGLShaderLibrary::Instance()->Add_Shader_From_File("object_3.vert","object_3.frag","object_3");	
	}

	void Add_Textures()
	{
		////format: image name, texture name
		OpenGLTextureLibrary::Instance()->Add_Texture_From_File("earth_albedo.png", "object_1_albedo");		
		OpenGLTextureLibrary::Instance()->Add_Texture_From_File("earth_normal.png", "object_1_normal");
		OpenGLTextureLibrary::Instance()->Add_Texture_From_File("bark.jpg", "object_2_albedo");		
		OpenGLTextureLibrary::Instance()->Add_Texture_From_File("bark_normal.png", "object_2_normal");
		OpenGLTextureLibrary::Instance()->Add_Texture_From_File("brown.jpg", "object_3_albedo");		
		OpenGLTextureLibrary::Instance()->Add_Texture_From_File("bark_normal.png", "object_3_normal");

	}

	void Add_Background()
	{
		OpenGLBackground* opengl_background=Add_Interactive_Object<OpenGLBackground>();
		opengl_background->shader_name="background";
		opengl_background->Initialize();
	}

	////this is an example of adding a mesh object read from obj file
	int Add_Object_1()
	{
		/* Bunny Mesh */
		// auto mesh_obj=Add_Interactive_Object<OpenGLTriangleMesh>();
		// ////read mesh file
		// std::string obj_file_name="bunny.obj";
		// Array<std::shared_ptr<TriangleMesh<3> > > meshes;
		// Obj::Read_From_Obj_File_Discrete_Triangles(obj_file_name,meshes);
		// mesh_obj->mesh=*meshes[0];
		// ////This is an example showing how to access and modify the values of vertices on the CPU end.
		// //std::vector<Vector3>& vertices=mesh_obj->mesh.Vertices();
		// //int vn=(int)vertices.size();
		// //for(int i=0;i<vn;i++){
		// //	vertices[i]+=Vector3(1.,0.,0.);
		// //}
		// ////This is an example of creating a 4x4 matrix for GLSL shaders. Notice that the matrix is column-major (instead of row-major!)
		// ////The code for passing the matrix to the shader is in OpenGLMesh.h
		// mesh_obj->model_matrix=
		// 	glm::mat4(1.f,0.f,0.f,0.f,		////column 0
		// 			  0.f,1.f,0.f,0.f,		////column 1
		// 			  0.f,0.f,1.f,0.f,		////column 2
		// 			  0.f,1.f,0.f,1.f);		////column 3	////set the translation in the last column
		// ////set up shader
		// //mesh_obj->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("object_1_shadow"));//Shadow TODO: uncomment this line and comment next line to use shadow shader
		// mesh_obj->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("object_1"));
		// ////set up texture
		// mesh_obj->Add_Texture("tex_albedo", OpenGLTextureLibrary::Get_Texture("object_1_albedo"));
		// mesh_obj->Add_Texture("tex_normal", OpenGLTextureLibrary::Get_Texture("object_1_normal"));
		// Set_Polygon_Mode(mesh_obj,PolygonMode::Fill);
		// Set_Shading_Mode(mesh_obj,ShadingMode::Texture);//SHADOW TODO: set Shading Mode to Shadow
		// ////initialize
		// mesh_obj->Set_Data_Refreshed();
		// mesh_obj->Initialize();	
		// mesh_object_array.push_back(mesh_obj);
		// return (int)mesh_object_array.size()-1;

		/* Sphere Mesh */
		auto mesh_obj=Add_Interactive_Object<OpenGLTriangleMesh>();
		real radius=1.;
		Initialize_Sphere_Mesh(radius,&mesh_obj->mesh,500);		////add a sphere with radius=1000. if the obj file name is not specified
		////set up shader
		//mesh_obj->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("object_2_shadow"));//Shadow TODO: uncomment this line and comment next line to use shadow shader
		mesh_obj->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("object_1"));
		////set up texture
		mesh_obj->Add_Texture("tex_albedo", OpenGLTextureLibrary::Get_Texture("object_1_albedo"));
		mesh_obj->Add_Texture("tex_normal", OpenGLTextureLibrary::Get_Texture("object_1_normal"));
		Set_Polygon_Mode(mesh_obj,PolygonMode::Fill);
		Set_Shading_Mode(mesh_obj,ShadingMode::Texture);//SHADOW TODO: Set Shading Mode to Shadow
		////initialize
		mesh_obj->Set_Data_Refreshed();
		mesh_obj->Initialize();	
		mesh_object_array.push_back(mesh_obj);
		return (int)mesh_object_array.size()-1;
	}

	////this is an example of adding a spherical mesh object generated analytically
	int Add_Object_2()
	{
		/* Tree Mesh */
		real segment_len = 2;							// how long a segment is; height of a cylinder
		real radius = .3;								// cylinder radius
		float theta = 30. * (3.14159265 / 180);			// angle by which to rotate orientation when traversing L-System statement
		int num_sides = 128;							// number of sides of a cylinder

		auto mesh_obj=Add_Interactive_Object<OpenGLTriangleMesh>();

		TriangleMesh<3>* tri_mesh = &mesh_obj->mesh;
		
		////build tree
		/* Tree defined by an L-System statement (composed of instructions of forward (f), left/right turns (-/+), and branching off ([])) */
		Build_Tree(*tri_mesh, segment_len, radius, theta, num_sides);

		////set up shader
		mesh_obj->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("object_2"));

		////set up texture
		mesh_obj->Add_Texture("tex_albedo", OpenGLTextureLibrary::Get_Texture("object_2_albedo"));
		mesh_obj->Add_Texture("tex_normal", OpenGLTextureLibrary::Get_Texture("object_2_normal"));

		Set_Polygon_Mode(mesh_obj,PolygonMode::Fill);
		Set_Shading_Mode(mesh_obj,ShadingMode::Texture);
		Set_Color(mesh_obj,OpenGLColor(.3f,.3f,.3f,1.f));

		////initialize
		mesh_obj->Set_Data_Refreshed();
		mesh_obj->Initialize();	
		mesh_object_array.push_back(mesh_obj);
		return (int)mesh_object_array.size()-1;
	}

	std::string Generate_Statement(const int num_iterations, const std::string initial, std::unordered_map<char, std::string> rules) {
		std::string statement = initial;

		// iterate num_iterations times
		for (int i=0; i<num_iterations; ++i) {
			std::string next_statement = "";	// recursive statement that we desire

			// iterate over current statement to generate next statement
			for (int c=0; c<statement.length(); ++c) {
				if (rules.find(statement[c]) != rules.end()) {
					next_statement += rules[statement[c]];
				}
				else {
					next_statement += statement[c];
				}
			}
			statement = next_statement;	// update current statement to be next statement
		}
		return statement;
	}

	void Build_Tree(TriangleMesh<3>& tri_mesh, const real segment_len, const real radius, const float theta, const int sides) {
		std::vector<Vector3>& vertices = tri_mesh.Vertices();
		std::vector<Vector3i>& elements = tri_mesh.Elements();
		std::vector<Vector3>& normals = tri_mesh.Normals();
		std::cout<<"Load tri_mesh, #vtx: "<<vertices.size()<<", #ele: "<<elements.size()<<std::endl;

		// endpoints of a line segment
		Vector3 x1 = Vector3(0., -10, 0.);
		Vector3 x2 = x1;

		// temporary vertices used for stack
		Vector3 x1_temp = x1;
		Vector3 x2_temp = x2;

		// vector used to move forward; y is up according to initial render orientation
		Vector3 forward = Vector3(0., segment_len, 0.);

		Vector3 adaptive_radius = Vector3(radius, radius, radius);

		// stack used for branching; stores two endpoints of segment before branching as well as forward vector from before branching
		std::stack<std::vector<Vector3>> s;

		////generate L-System statement
		int num_iterations = 4;
		std::string initial = "F";
		std::unordered_map<char, std::string> rules;
		rules['F'] = "FF-[-F+F+F]+[+F-F-F]";
		// rules['F'] = "F+[F-F[+F+F]]+F-[F+F]";
		rules['X'] = "F[+X][-X]FX";
		
		std::string statement = Generate_Statement(num_iterations, initial, rules);
		std::cout<<"Statement after "<<num_iterations<<" iterations: "<<statement<<std::endl;

		// //go through statement 1 letter at a time
		for (int c=0; c<statement.length(); ++c) {
			// if the character is F, we move forward by segment_len
			if (statement[c] == 'F') {
				x2 += forward;

				forward *= .9;

				// now that we have two endpoints, we can create a cylinder
				Build_Cylinder(x1, x2, sides, adaptive_radius[0], vertices, elements, normals);

				adaptive_radius *= .9;
				
				// set temp values
				x1_temp = x1;
				x2_temp = x2;

				// after creating cylinder, update x1
				x1 = x2;
			}
			// if the character is -, we turn left by some angle
			else if (statement[c] == '-') {
				Matrix3 rot_m = Generate_Rotation_Matrix(theta, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX);
				forward = rot_m * forward;
			}
			// if the character is +, we turn right by some angle
			else if (statement[c] == '+') {
				Matrix3 rot_m = Generate_Rotation_Matrix(-1 * theta, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX);
				forward = rot_m * forward;
			}
			// if the character is [, branch off (use a stack)
			else if (statement[c] == '[') {
				// we need to add the two endpoints, our forward vector, and our adaptive radius to the stack
				std::vector<Vector3> branch = {x1, x2, forward, adaptive_radius};
				s.push(branch);
			}
			// if the character is ], end branch (pop off stack)
			else if (statement[c] == ']') {
				// pop off the stack to return to where the branch began
				if (s.empty()) {
					std::cout<<"Unexpectedly popped. Aborting..."<<std::endl;
					return;
				}

				std::vector<Vector3> branch = s.top();
				s.pop();
				x1 = branch[0];
				x2 = branch[1];
				forward = branch[2];
				adaptive_radius = branch[3];
			}
			// else we have an unknown/invalid character
			else {
				// std::cout<<"Invalid instruction: '"<<statement[c]<<"'. Aborting..."<<std::endl;
				;
			}
		}
		std::cout<<"Tree built, #vtx: "<<vertices.size()<<", #ele: "<<elements.size()<<std::endl;
	}

	void Build_Cylinder(const Vector3 x1, const Vector3 x2, const int sides, const real radius, std::vector<Vector3>& vertices, std::vector<Vector3i>& elements, std::vector<Vector3>& normals) {
		float taper_weight = 1.;	// determines the radius of the top cylinder face, allowing for the cylinder to become thinner/fatter as you go up in height
		Vector3 segment_dir = x2 - x1;
		Vector3 face_plane_v_bottom = segment_dir.cross(Vector3(1.,0.,0.)).normalized() * radius;	// used to generate vertices about x1,x2 segment
		Vector3 face_plane_v_top = segment_dir.cross(Vector3(1.,0.,0.)).normalized() * radius * taper_weight;
		// std::cout<<"(x,y,z) of face_plane_v for segment ("<<segment_dir[0]<<","<<segment_dir[1]<<","<<segment_dir[2]<<"): ("<<face_plane_v[0]<<","<<face_plane_v[1]<<","<<face_plane_v[2]<<")"<<std::endl;

		float phi = 360./sides;	// determines the angle by which to rotate about the face center at x1 or x2

		int vert_size = vertices.size();
		int elmt_size = elements.size();

		// add new vertices
		for (int i=0; i<sides; ++i) {
			// obtain rotation matrix:
			float ax = segment_dir[0];
			float ay = segment_dir[1];
			float az = segment_dir[2];

			float rot_angle = phi * i;

			Matrix3 rot_m = Generate_Rotation_Matrix(rot_angle, ax, ay, az);

			Vector3 v_bottom_face = rot_m * face_plane_v_bottom + x1;
			Vector3 v_top_face = rot_m * face_plane_v_top + x2;
		
			vertices.push_back(v_bottom_face);
			vertices.push_back(v_top_face);

			normals.push_back(face_plane_v_bottom);
			normals.push_back(face_plane_v_bottom);
		}

		// add new triangle elements
		for (int i=0; i<2*sides; i+=2) {
			// wraparound case where last vertices connect with first vertices
			if (i == sides * 2 - 2) {
				int idx = i + vert_size;

				Vector3i triangle1 = Vector3i(idx, idx + 1, (idx + 2) % sides + vert_size);
				Vector3i triangle2 = Vector3i((idx + 2) % sides + vert_size + 1, idx + 1, (idx + 2) % sides + vert_size);

				elements.push_back(triangle1);
				elements.push_back(triangle2);
			}
			else {
				int idx = i + vert_size;
				
				Vector3i triangle1 = Vector3i(idx, idx + 1, idx + 2);
				Vector3i triangle2 = Vector3i(idx + 3, idx + 1, idx + 2);

				elements.push_back(triangle1);
				elements.push_back(triangle2);
			}
		}
	}

	Matrix3 Generate_Rotation_Matrix(const float rot_angle, const float ax, const float ay, const float az) {
		/*
			Rotation Matrix about some axis A = [ax, ay, az]:
				[[cos(theta) + (1 - cos(theta))*ax^2      ax*ay*(1 - cos(theta)) - az*sin(theta)   	ax*az*(1 - cos(theta)) + ay*sin(theta)]
				 [ay*ax*(1 - cos(theta)) + az*sin(theta)  cos(theta) + (1 - cos(theta))*ay^2      	ay*az*(1 - cos(theta)) - ax*sin(theta)]
				 [az*ax*(1 - cos(theta)) - ay*sin(theta)  az*ay*(1 - cos(theta)) + ax*sin(theta)   	cos(theta) + (1 - cos(theta))*az^2]]

				theta is rotation angle; ax,ay,az are components of rotation axis (i.e. segment)
		*/
		Matrix3 rot_m;
		rot_m.col(0) = Vector3(cos(rot_angle) + (1 - cos(rot_angle))*ax*ax, ax*ay*(1 - cos(rot_angle)) - az*sin(rot_angle), ax*az*(1 - cos(rot_angle)) + ay*sin(rot_angle));
		rot_m.col(1) = Vector3(ay*ax*(1 - cos(rot_angle)) + az*sin(rot_angle), cos(rot_angle) + (1 - cos(rot_angle))*ay*ay, ay*az*(1 - cos(rot_angle)) - ax*sin(rot_angle));
		rot_m.col(2) = Vector3(az*ax*(1 - cos(rot_angle)) - ay*sin(rot_angle), az*ay*(1 - cos(rot_angle)) + ax*sin(rot_angle), cos(rot_angle) + (1 - cos(rot_angle))*az*az);

		return rot_m;
	}

	////this is an example of adding an object with manually created triangles and vertex attributes
	int Add_Object_3()
	{
		auto mesh_obj=Add_Interactive_Object<OpenGLTriangleMesh>();
		auto& mesh=mesh_obj->mesh;

		////vertex position
		std::vector<Vector3> triangle_vertices={Vector3(-1000,-10,-1000),Vector3(1000,-10,-1000),Vector3(-1000,-10,1000),Vector3(1000,-10,1000)};
		std::vector<Vector3>& vertices=mesh_obj->mesh.Vertices();
		vertices=triangle_vertices;
			
		////vertex color
		std::vector<Vector4f>& vtx_color=mesh_obj->vtx_color;
		vtx_color={Vector4f(1.f,0.f,0.f,1.f),Vector4f(0.f,1.f,0.f,1.f),Vector4f(0.f,0.f,1.f,1.f),Vector4f(1.f,1.f,0.f,1.f)};

		////vertex normal
		std::vector<Vector3>& vtx_normal=mesh_obj->vtx_normal;
		vtx_normal={Vector3(0.,1.,0.),Vector3(0.,1.,0.),Vector3(0.,1.,0.),Vector3(0.,1.,0.)};

		////vertex uv
		std::vector<Vector2>& uv=mesh_obj->mesh.Uvs();
		uv={Vector2(0.,0.),Vector2(1.,0.),Vector2(0.,1.),Vector2(1.,1.)};

		////mesh elements
		std::vector<Vector3i>& elements=mesh_obj->mesh.Elements();
		elements={Vector3i(0,1,3),Vector3i(0,3,2)};

		////set up shader
		//mesh_obj->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("object_3_shadow"));//Shadow TODO: uncomment this line and comment next line to use shadow shader
		mesh_obj->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("object_3"));
		
		////set up texture
		mesh_obj->Add_Texture("tex_albedo", OpenGLTextureLibrary::Get_Texture("object_3_albedo"));
		mesh_obj->Add_Texture("tex_normal", OpenGLTextureLibrary::Get_Texture("object_3_normal"));
		Set_Polygon_Mode(mesh_obj,PolygonMode::Fill);
		Set_Shading_Mode(mesh_obj,ShadingMode::Texture);//SHADOW TODO: Set Shading Mode to Shadow

		////initialize
		mesh_obj->Set_Data_Refreshed();
		mesh_obj->Initialize();	
		mesh_object_array.push_back(mesh_obj);
		return (int)mesh_object_array.size()-1;
	}

	//// Use this function to set up lighting only if you are using Shadow mode
	void Init_Lighting() {
		auto dir_light = OpenGLUbos::Add_Directional_Light(glm::vec3(-1.f, -1.f, -1.f));//Light direction
		dir_light->dif = glm::vec4(.9,.8,.7, 1.0);//diffuse reflection color
		dir_light->Set_Shadow();////SHADOW TODO: turn on the shadow by uncommenting this line, currenly our base code only supports shadow for one light

		//This is an example to add a second directional light
		//auto dir_light_2 = OpenGLUbos::Add_Directional_Light(glm::vec3(1.,1.,1.));//the parameter is light direction
		//dir_light_2->dif = glm::vec4(.9,.9,.9,1.0);
		//dir_light_2->spec = glm::vec4(.2,.2,.2,1.0);

		//This is an example to add a point light
		//auto point_light = OpenGLUbos::Add_Point_Light(glm::vec3(1.,1.,1.));//the parameter is the position of point light
		//point_light->dif = glm::vec4(.9,.8,.7, 1.0);

		//This is an example to add a spot light
		//auto spot_light = OpenGLUbos::Add_Spot_Light(glm::vec3(1.,1.,1.),glm::vec3(1.,1.,1.));//first param: position, second param: direction
		//spot_light->dif = glm::vec4(.9,.8,.7, 1.0);

		OpenGLUbos::Set_Ambient(glm::vec4(.01f, .01f, .02f, 1.f));
		OpenGLUbos::Update_Lights_Ubo();	
	}

	virtual void Initialize_Data()
	{
		Add_Shaders();
		Add_Textures();

		Add_Background();
		// Add_Object_1();
		Add_Object_2();
		Add_Object_3();

		Init_Lighting(); ////SHADOW TODO: uncomment this line
	}

	////Goto next frame 
	virtual void Toggle_Next_Frame()
	{
		for (auto& mesh_obj : mesh_object_array) {
			mesh_obj->setTime(GLfloat(clock() - startTime) / CLOCKS_PER_SEC);
		}
		OpenGLViewer::Toggle_Next_Frame();
	}

	virtual void Run()
	{
		OpenGLViewer::Run();
	}
};

int main(int argc,char* argv[])
{
	FinalProjectDriver driver;
	driver.Initialize();
	driver.Run();	
}

#endif