
#include "common.hlsl"



void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp; //matrix型の変数wvpを定義する

	//wvp = ワールド変換行列×ビュー変換行列
    wvp = mul(World, View);
	//wvp = wvp × プロジェクション変換行列
    wvp = mul(wvp, Projection);

	//入力された頂点座標を変換して出力先へ代入する
    Out.Position = mul(In.Position, wvp);

	//頂点の法線をワールド行列で変換する
    float4 worldNormal, normal;

    normal = float4(In.Normal.xyz, 0.0f);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    Out.Normal = worldNormal;

    Out.Diffuse = In.Diffuse;

	//頂点カラーはそのままコピー
	//Out.Diffuse = In.Diffuse;
	
    Out.WorldPosition = mul(In.Position, World);
	
		//入力されたUV座標を出力先へ代入する
    Out.TexCoord = In.TexCoord;
	
    matrix lightwvp;
    lightwvp = mul(World, Light.View);
    lightwvp = mul(lightwvp, Light.Projection);
    Out.ShadowPosition = mul(In.Position, lightwvp);

    for (int i = 0; i < 6;i++)
    {
        matrix pointlightwvp;
        pointlightwvp = mul(World, PointLight.View[i]);
        pointlightwvp = mul(pointlightwvp, PointLight.Projection);
        Out.PointShadowPosition[i] = mul(In.Position, pointlightwvp);
    }
    
    matrix spotlightwvp;
    spotlightwvp = mul(World, SpotLight.View);
    spotlightwvp = mul(spotlightwvp, SpotLight.Projection);
    Out.SpotShadowPosition = mul(In.Position, spotlightwvp);
}
