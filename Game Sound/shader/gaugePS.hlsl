
#include "common.hlsl"

static const float pi = 3.1415926535f;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	outDiffuse = float4(0.0f,0.0f,0.0f,1.0f);

	float gauge = In.TexCoord * param.hp.y;
	outDiffuse.rgb += param.lostColor.rgb * step(param.hp.x, gauge);
	outDiffuse.rgb += param.baseColor.rgb * (1.0f - step(param.hp.x, gauge));//float2 uv = In.TexCoord - 0.5f;
	//outDiffuse.rgb += param.diffColor.rgb * (1.0f - step(param.hp.z, gauge)) * step(param.hp.x, gauge);
	//float angle = atan2(uv.x, uv.y);
	//angle += pi;
		
	//
	////UV値からピクセルへのスケール変換を行う
	//float gauge = frac(angle * 0.5f / pi) * param.hp.y;
	////HPゲージのグレー部分を作成する
	//outDiffuse.rgb += param.lostColor.rgb * step(param.hp.z, gauge);
	//outDiffuse.rgb += param.baseColor.rgb * (1.0f - step(param.hp.x, gauge));
	//outDiffuse.rgb += param.diffColor.rgb * (1.0f - step(param.hp.z, gauge)) * step(param.hp.x, gauge);

	//float dist = length(uv) / 0.5f;
	//outDiffuse.a = (1.0f - step(1.0f, dist)) * step(0.3f, dist);
}
