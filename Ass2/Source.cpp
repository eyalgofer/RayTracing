#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "glut.h"
#include "Vector3f.h"
#include "Ambient.h"
#include "Camera.h"
#include "Directional.h"
#include "Light.h"
#include "Plane.h"
#include "Ray.h"
#include "Scene.h"
#include "SceneObject.h"
#include "Spher.h"
#include "Spot.h"



#define HEIGHT 512
#define WIDTH 512


using namespace std;
typedef Vector3f Point;


GLubyte *screen = new GLubyte[WIDTH*HEIGHT *3]; // RGB
GLuint Screentex = 0;

GLfloat sceneData[12];
GLfloat * lightsData[5];
GLfloat * planesData[5];
GLfloat * sphersData[5];
int lightsNum = 0;
int planesNum = 0;
int sphersNum = 0;

Scene* scene;
Camera* camera;


void parser(const char * filename) {

	
	ifstream file(filename);
	string bufferedLine;
	while (!file.eof()) {

		getline(file, bufferedLine);
		string temp = bufferedLine.substr(6); // leave out name of object and space 
		const char* temp1 = temp.c_str();	// prepare for float tokens
		char * temp2 = (char*)temp1;	// no const 
		switch (bufferedLine[1]) {
		case 'c':   // read scene
			printf("Reading Scene: \n");
			for (int i = 0; i<12; i++, temp2++) {
				GLfloat num = (GLfloat)strtof(temp2, &temp2); // take first token and put the rest in temp2
				sceneData[i] = num;	// put float num in scene data structure 
				printf("%f ", num);
			}
			printf("\n");
			break;
		case 'i':	// read light
			
			if (bufferedLine.length() > 30 ) { // case spot light
				printf("reading spotlight num %d: \n", lightsNum);
				lightsData[lightsNum] = new GLfloat(10);
				for (int i = 0; i<10 ; i++, temp2++) {
					GLfloat num = (GLfloat)strtof(temp2, &temp2);
					lightsData[lightsNum][i] = num;	
					printf("%f ", lightsData[lightsNum][i]);
				}
				printf("\n");
				lightsNum++;
			}
			else {	// Ambient or Directional
				printf("reading light num %d: \n", lightsNum);
				lightsData[lightsNum] = new GLfloat(6);
				for (int i = 0; i<6; i++, temp2++) {
					GLfloat num = (GLfloat)strtof(temp2, &temp2); 
					lightsData[lightsNum][i] = num;	
					printf("%f ", lightsData[lightsNum][i]);
				}
				printf("\n");
				lightsNum++;
			}
			break;
			
		case 'p':	// read spher
			printf("reading sphere num %d: \n", sphersNum);
			sphersData[sphersNum] = new GLfloat(14);
			for (int i = 0; i<14; i++, temp2++) {
				GLfloat num = (GLfloat)strtof(temp2, &temp2);
				sphersData[sphersNum][i] = num;
				printf("%f ", sphersData[sphersNum][i]);
			}
			printf("\n");
			sphersNum++;
			break;
		case 'l':	// read plane
			printf("reading plane num %d: \n", planesNum);
			planesData[planesNum] = new GLfloat(6);
			for (int i = 0; i<6; i++, temp2++) {
				GLfloat num = (GLfloat)strtof(temp2, &temp2);
				planesData[planesNum][i] = num;
				printf("%f ", planesData[planesNum][i]);
			}
			printf("\n");
			planesNum++;
			break;
		}
	}
	file.close();

}

void buildScene() {
	printf("Building Scene from parsed data \n");
	// construct scene from parsed data 
	scene = new Scene(
		Point(sceneData[0], sceneData[1], sceneData[2]),
		Vector3f(sceneData[3],sceneData[4],sceneData[5]),
		(int)sceneData[6],
		(int)sceneData[7],
		(int)sceneData[8],
		new Ambient(Vector3f(sceneData[9], sceneData[10], sceneData[11])),
		camera
		);

	// add lights to scene
	for (int i = 0; i < lightsNum; i++) {
		if (lightsData[i][6] == 0) {
			printf("print this for directional light man ");
		}
		else {

		}
	}

	// add planes to scene
	for (int i = 0; i < planesNum; i++) {

	}

	// add sphers to scene 
	for (int i = 0; i < sphersNum; i++) {

	}

}


/*

void constructRayThroughPixel(Ray* ray, Camera* camera, int i, int j) {

}


Image RayCast(Camera camera, Scene scene, int width, int height) {
	Image image = new Image(width, height); 
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Ray ray = ConstructRayThroughPixel(camera, i, j);
			Intersection hit = FindIntersection(ray, scene); 
			image[i][j] = GetColor(hit);
		}
	}
	return image;
}

Intersection FindIntersection(Ray ray, Scene scene)
{
	min_t = infinity min_primitive = NULL
		For each primitive in scene{
		t = Intersect(ray, primitive);
	if (t < min_t) then
		min_primitive = primitive
		min_t = t }
}
return Intersection(min_t, min_primitive)
}

RGB GetColor(Scene scene, Ray in_ray, Point hit) {
	// Ambient and Emission calculations
	RGB color = calcEmissionColor(scene) + calcAmbientColor(scene);
	// Diffuse & Specular calculations
	for (int i = 0; i < getNumLights(scene); i++) {
		Light light = getLight(i, scene);
		color += calcDiffuseColor(scene, hit, light) +
	}
	return color;
}

*/
void init(char* fileName) {

	parser(fileName);
	//buildScene();

	
	glEnable(GL_TEXTURE_2D);
	glOrtho(-1.0, 1.0, -1.0, 1.0, 2.0, -2.0);
	glGenTextures(1, &Screentex);
	glBindTexture(GL_TEXTURE_2D, Screentex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, screen);
	
}

	
void mydisplay() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	glViewport(0, 0, WIDTH, HEIGHT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, Screentex);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); //adapt texture to shape
	glVertex3f(-1.0, -1.0f, 1.0);

	glTexCoord2f(1, 0);  //adapt texture to shape
	glVertex3f(1.0, -1.0f, 1.0);

	glTexCoord2f(1, 1);//adapt texture to shape
	glVertex3f(1.0, 1.0f, 1.0);

	glTexCoord2f(0, 1);//adapt texture to shape
	glVertex3f(-1.0, 1.0f, 1.0);
	glEnd();
	glFlush();

}



int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Scene");
	init(argv[1]);
	printf("why ?? ");
	glutDisplayFunc(mydisplay);
	glutMainLoop();


}