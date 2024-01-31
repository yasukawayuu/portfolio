
#include "common.hlsl"


#define OFFSET_NUM 25.0f

Texture2D g_Texture : register(t0);
Texture2D g_TextureDepthShadow : register(t1);
Texture2D g_TextureDepthPointShadow1 : register(t2);
Texture2D g_TextureDepthPointShadow2 : register(t3);
Texture2D g_TextureDepthPointShadow3 : register(t4);
Texture2D g_TextureDepthPointShadow4 : register(t5);
Texture2D g_TextureDepthPointShadow5 : register(t6);
Texture2D g_TextureDepthPointShadow6 : register(t7);
Texture2D g_TextureDepthSpotShadow : register(t8);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	////法線を正規化して格納する
    
    float4 normal = normalize(In.Normal);
    
    if (Material.TextureEnable)
    {
        //テクスチャから色をサンプリングする
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    }
    else
    {
        outDiffuse = In.Diffuse;
    }
    
    //ランバート
    //float light = -dot(Light.Direction.xyz, In.Normal.xyz);
    //light = saturate(light);
    
    //float4 lighting;
    //lighting = In.Diffuse * Material.Diffuse * light * Light.Diffuse;
    //lighting += In.Diffuse * Material.Ambient * Light.Ambient;
    //lighting += Material.Emission;
    //lighting.a = In.Diffuse.a * Material.Diffuse.a;
      
    //outDiffuse.rgb *= lighting;
    
    //In.ShadowPosition.xyz /= In.ShadowPosition.w;
    //In.ShadowPosition.x = In.ShadowPosition.x * 0.5f + 0.5f;
    //In.ShadowPosition.y = -In.ShadowPosition.y * 0.5f + 0.5f;
    
    //float Depth = g_TextureDepthShadow.Sample(g_SamplerState, In.ShadowPosition.xy);
    
    //if (Depth < In.ShadowPosition.z - 0.001f)
    //{
    //    outDiffuse.rgb *= 0.1f;
    //}
    
    
    
    //スポットライト
    float3 spotDir = In.WorldPosition.xyz - SpotLight.Position.xyz;
    float spotlen = length(spotDir);
    spotDir = normalize(spotDir);
    
    float spotFactor = -dot(SpotLight.Direction.xyz, spotDir);
    spotFactor = saturate(spotFactor);
    
    float4 spotlighting;
    spotlighting = In.Diffuse * Material.Diffuse * spotFactor;
    spotlighting += In.Diffuse * Material.Ambient;
    spotlighting += Material.Emission;
    spotlighting.a = In.Diffuse.a * Material.Diffuse.a;
    
    
    float spotcolA = saturate(1.0f /
            (SpotLight.Attenuation.x +
             SpotLight.Attenuation.y * spotlen +
             SpotLight.Attenuation.z * (spotlen * spotlen)));
 
    
    outDiffuse.rgb *= spotlighting.xyz * spotcolA;
    
    In.SpotShadowPosition.xyz /= In.SpotShadowPosition.w;
    In.SpotShadowPosition.x = In.SpotShadowPosition.x * 0.5f + 0.5f;
    In.SpotShadowPosition.y = -In.SpotShadowPosition.y * 0.5f + 0.5f;
    
    float spotDepth = g_TextureDepthSpotShadow.Sample(g_SamplerState, In.SpotShadowPosition.xy);
    
    if (spotDepth < In.SpotShadowPosition.z - 0.001f)
    {
        float distance = 1.0f - saturate((spotlen - 0.1f) / (20.0f - 0.1f));
        float shadowIntensity = 1.0f - distance;
        outDiffuse.rgb *= shadowIntensity;
    }
  
    
    
    //ポイントライト

    float3 pointDir = In.WorldPosition.xyz - PointLight.Position.xyz;
    float pointLen = length(pointDir);
    pointDir = normalize(pointDir);
    
    float colD = -dot(pointDir, normal.xyz);
    colD = saturate(colD);
    
    float4 pointlighting;
    pointlighting = In.Diffuse * Material.Diffuse * colD;
    pointlighting += In.Diffuse * Material.Ambient;
    pointlighting += Material.Emission;
    pointlighting.a = In.Diffuse.a * Material.Diffuse.a;
    
    float colA = saturate(1.0f /
            (PointLight.Attenuation.x +
             PointLight.Attenuation.y * pointLen +
             PointLight.Attenuation.z * (pointLen * pointLen)));
  
    float3 pointLightColor = PointLight.Color.rgb;
        
    float3 col = pointLightColor * (colA * pointlighting.xyz);
        
    outDiffuse.rgb += col;
        
    
    
    for (int i = 0; i < 6; i++)
    {
        In.PointShadowPosition[i].xyz /= In.PointShadowPosition[i].w;
        In.PointShadowPosition[i].x = In.PointShadowPosition[i].x * 0.5f + 0.5f;
        In.PointShadowPosition[i].y = -In.PointShadowPosition[i].y * 0.5f + 0.5f;
    }
  
    float depth[6];
    
    depth[0] = g_TextureDepthPointShadow1.Sample(g_SamplerState, In.PointShadowPosition[0].xy);
    depth[1] = g_TextureDepthPointShadow2.Sample(g_SamplerState, In.PointShadowPosition[1].xy);
    depth[2] = g_TextureDepthPointShadow3.Sample(g_SamplerState, In.PointShadowPosition[2].xy);
    depth[3] = g_TextureDepthPointShadow4.Sample(g_SamplerState, In.PointShadowPosition[3].xy);
    depth[4] = g_TextureDepthPointShadow5.Sample(g_SamplerState, In.PointShadowPosition[4].xy);
    depth[5] = g_TextureDepthPointShadow6.Sample(g_SamplerState, In.PointShadowPosition[5].xy);
    
    
    
    if (depth[0] < In.PointShadowPosition[0].z - 0.001f && depth[1] < In.PointShadowPosition[1].z - 0.001f ||
        depth[2] < In.PointShadowPosition[2].z - 0.001f && depth[3] < In.PointShadowPosition[3].z - 0.001f ||
        depth[4] < In.PointShadowPosition[4].z - 0.001f && depth[5] < In.PointShadowPosition[5].z - 0.001f)
    {

        float distance = 1.0f - saturate((pointLen - 0.1f) / (10.0f - 0.1f));
        float shadowIntensity = 1.0f - distance;
        //if(len < 10.0f)
        outDiffuse.rgb *= shadowIntensity;
    
    }
    
    outDiffuse.a = In.Diffuse.a;

    
	//ブリンフォン鏡面反射
    //float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    //eyev = normalize(eyev);
    //float3 halfv = eyev + Light.Direction.xyz;
    //halfv = normalize(halfv);

    //float specular = -dot(halfv, In.Normal.xyz);
    //saturate(specular);
    //specular = pow(specular, 30);
    //outDiffuse.rgb = saturate(outDiffuse.rgb + specular);
}
