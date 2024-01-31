
#include "main.h"
#include "renderer.h"
#include "candleHolder.h"
#include "shader.h"
#include "object3D.h"

void CandleHolder::Init()
{
	AddComponent<Shader>()->Init("shader\\pixelLightingVS.cso", "shader\\pixelLightingPS.cso");
	AddComponent<Object3D>()->Init("asset\\model\\title\\candleholder.obj");
}


void CandleHolder::Update()
{

}