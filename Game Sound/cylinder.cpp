
#include "main.h"
#include "renderer.h"
#include "cylinder.h"
#include "shader.h"
#include "object3D.h"

void Cylinder::Init()
{
	AddComponent<Shader>()->Init("shader\\pixelLightingVS.cso", "shader\\pixelLightingPS.cso");
	AddComponent<Object3D>()->Init("asset\\model\\cylinder.obj");
}


void Cylinder::Update()
{

}