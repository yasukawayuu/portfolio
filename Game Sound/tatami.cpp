
#include "main.h"
#include "renderer.h"
#include "tatami.h"
#include "shader.h"
#include "object3D.h"

void Tatami::Init()
{
	AddComponent<Shader>()->Init("shader\\pixelLightingVS.cso", "shader\\pixelLightingPS.cso");
	AddComponent<Object3D>()->Init("asset\\model\\title\\tatami.obj");
}


void Tatami::Update()
{

}