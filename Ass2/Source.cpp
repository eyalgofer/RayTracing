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
#include "SceneObject.h"
#include "Plane.h"
#include "Ray.h"
#include "Scene.h"
#include "Spher.h"
#include "Spot.h"
#include "Intersection.h"

#define HEIGHT 512
#define WIDTH 512
#define MAX_COLOR 255

using namespace std;

typedef Vector3f Point;

GLfloat infinity = numeric_limits<float>::infinity();
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


void parser(const char* filename) {

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
					lightsData[lightsNum] = (GLfloat*)malloc(sizeof(GLfloat)*10);
					for (int i = 0; i<10 ; i++, temp2++) {
						GLfloat num = (GLfloat)strtof(temp2, &temp2);
						lightsData[lightsNum][i] = num;	
						printf("%f ", lightsData[lightsNum][i]);
					} // asd asdasd
					printf("\n");
					lightsNum++;
				}
				else {	// Ambient or Directional
					printf("reading light num %d: \n", lightsNum);
					lightsData[lightsNum] =  (GLfloat*)malloc(sizeof(GLfloat)*7);
					for (int i = 0; i<6; i++, temp2++) {
						GLfloat num = (GLfloat)strtof(temp2, &temp2); 
						lightsData[lightsNum][i] = num;	
						printf("%f ", lightsData[lightsNum][i]);
					}
					lightsData[lightsNum][6] = 99.0;
					printf("\n");
					lightsNum++;
				}
				break;
			
			case 'p':	// read spher
				printf("reading sphere num %d: \n", sphersNum);
				sphersData[sphersNum] =  (GLfloat*)malloc(sizeof(GLfloat)*14);
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
				planesData[planesNum] = (GLfloat*)malloc(sizeof(GLfloat)*18);
				for (int i = 0; i<18; i++, temp2++) {
					GLfloat num = (GLfloat)strtof(temp2, &temp2);
					planesData[planesNum][i] = num;
					printf("%f ", planesData[planesNum][i]);
				}
				printf("\n");
				planesNum++;
				break;

			default:
		
				break;
		}
	}
	file.close();

}

void buildScene() {
	printf("Building Scene from parsed data \n");
	// construct scene from parsed data 
	for (int i = 0; i < 12; i++)
		printf("%f \n", sceneData[i]);
	scene = new Scene(
		Point(sceneData[0], sceneData[1], sceneData[2]), // center
		Vector3f(sceneData[3], sceneData[4], sceneData[5]), // up vector
		sceneData[6], // w
		sceneData[7], // x
		sceneData[8], // y
		new Ambient(Vector3f(sceneData[9], sceneData[10], sceneData[11])), // light
		camera = new Camera(Point(0, 0, 0)) // cam
		);
	printf("as");
	// add lights to scene
	for (int i = 0; i < lightsNum; i++) {
		if (lightsData[i][6] == 99.0  ) {
			printf("adding directional light");
			scene->addLight(new Directional(Vector3f(lightsData[i][3],lightsData[i][4],lightsData[i][5]), 
				Vector3f(lightsData[i][0], lightsData[i][1], lightsData[i][2])));
		}
		else {
			printf("adding spot lights");
			scene->addLight(new Spot(Vector3f(lightsData[i][3], lightsData[i][4], lightsData[i][5]),
				Vector3f(lightsData[i][0], lightsData[i][1], lightsData[i][2]), Vector3f(lightsData[i][6], lightsData[i][7], lightsData[i][8]),lightsData[i][9]));
		}
	}
	// add sphers to scene 
	for (int i = 0; i < sphersNum; i++) {
		scene->addObject(new Spher(Vector3f(sphersData[i][0], sphersData[i][1], sphersData[i][2]), sphersData[i][3],
			Vector3f(sphersData[i][4], sphersData[i][5], sphersData[i][6]), Vector3f(sphersData[i][7], sphersData[i][8],
			sphersData[i][9]), Vector3f(sphersData[i][10], sphersData[i][11], sphersData[i][12]),(int)sphersData[i][13])
			);
	}

	// add planes to scene
	for (int i = 0; i < planesNum; i++) {
		scene->addObject(new Plane(Vector3f(planesData[i][0], planesData[i][1], planesData[i][2]),
			Vector3f(planesData[i][3], planesData[i][4], planesData[i][5]), planesData[i][6],planesData[i][7],
			Vector3f(planesData[i][8], planesData[i][9], planesData[i][10]), Vector3f(planesData[i][11], planesData[i][12], planesData[i][13]),
			Vector3f(planesData[i][14], planesData[i][15], planesData[i][16]),(int)planesData[i][17])
			);
		
	}
	

}

void constructRayThroughPixel(Ray& ray, Camera* camera, int x, int y) {

	ray.source = camera->center;
	GLfloat R = scene->width / scene->Rx;
	GLfloat left = (x - floor(scene->Rx / 2))*R;
	GLfloat right = (y - floor(scene->Ry / 2))*R;
	Vector3f p = scene->screenCenter + (left*scene->rightVector) + (right*scene->upVector);
	ray.vector = p - ray.source;
	ray.vector.normalize();
}

void setColor(Vector3f& c, GLubyte * R, GLubyte * G, GLubyte * B)
{
	if (c.x>1)c.x = 1;
	if (c.x<0)c.x = 0;

	if (c.y>1)c.y = 1;
	if (c.y<0)c.y = 0;

	if (c.z>1)c.z = 1;
	if (c.z<0)c.z = 0;

	*R = c.x * MAX_COLOR;
	*G = c.y * MAX_COLOR;
	*B = c.z * MAX_COLOR;
}
bool intercepted(Ray& lightRay, Intersection* inter){ // does the intersetion point really has a beam of light hitting it .. -
	Intersection* inters = new Intersection(Vector3f(infinity, infinity, infinity), 0);
	for (int i = 0; i < scene->objects.size(); i++) {
		scene->objects.at(i)->findIntersection(inters, lightRay);
		if (inters->distance > 0 && inters->obj->center != inter->obj->center)
			return true;
	}
	return false;
}

void GetColor(Ray& ray, Intersection* hit, GLubyte* R, GLubyte* G, GLubyte* B) {
	if (hit->obj != NULL && 200) {
		Vector3f RGB = hit->obj->calcAmbientColor(scene, hit);
		
		for (unsigned int i = 0; i < scene->lights.size(); i++) {
			Ray lightRay;
			Light* light = scene->lights.at(i);
			light->constructRayToLight(lightRay, hit);
			if (!intercepted(lightRay, hit)) 
				RGB += light->calcDiffuseSpeculareColor(scene, ray,lightRay, hit);
		}
		setColor(RGB, R, G, B);
	}
	else {
		setColor(Vector3f(0, 0, 0),R,G,B);
	}
}

void RayCast() {
	GLubyte *R = screen, *G = screen + 1, *B = screen + 2;
	Ray ray;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++, R+=3, G+=3,B+=3) {
			*R = 0;
			*G = 0;
			*B = 0;
			constructRayThroughPixel(ray, camera, x, y);
			vector<Intersection*> intersections;
			for (int i = 0; i < scene->objects.size(); i++) {
				Intersection* intersect = new Intersection();
				scene->objects.at(i)->findIntersection(intersect, ray);
				intersections.push_back(intersect);
			}
			Intersection* hit = intersections.at(0);
			for (int i = 1; i < intersections.size(); i++) {
				if (intersections.at(i)->distance < hit->distance)
					hit = intersections.at(i);
			}

			GetColor(ray,hit, R,G,B);

			for (int i = 0; i < intersections.size(); i++){
				delete intersections[i];
			}
			intersections.clear();
		}
	}
	
}

void init(char* fileName) {

	parser(fileName);
	buildScene();
	printf("@@ %f %f %f @@", scene->lights.at(0)->RGB.x , scene->lights.at(0)->RGB.y, scene->lights.at(0)->RGB.z);
 	RayCast();
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
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}