
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	
    //In.Position.x += In.InstanceId;
	
    In.Position.xyz += Position[In.InstanceId];
	
	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse * Material.Diffuse;

}

