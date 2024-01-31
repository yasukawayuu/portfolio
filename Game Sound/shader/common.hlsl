


cbuffer WorldBuffer : register(b0)
{
    matrix World;
}
cbuffer ViewBuffer : register(b1)
{
    matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}




struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    bool TextureEnable;
    float2 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}




struct LIGHT
{
    bool Enable;
    bool3 Dummy;
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
	
    matrix View;
    matrix Projection;
};


cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
}

struct POINTLIGHT
{
    float4 Position;
    float4 Attenuation;
    float4 Color;
    matrix View[6];
    matrix Projection;
};

cbuffer PointLightBuffer : register(b8)
{
    POINTLIGHT PointLight;
}

struct SPOTLIGHT
{
    float4 Position;
    float4 Attenuation;
    float4 Direction;
    float4 Color;
    matrix View;
    matrix Projection;
};

cbuffer SpotLightBuffer : register(b9)
{
    SPOTLIGHT SpotLight;
}


cbuffer CameraBuffer : register(b5) //コンスタントバッファ4番とする
{
    float4 CameraPosition; //ライト構造体
}

struct PARAMETER
{
    float4 hp;
    float4 lostColor;
    float4 baseColor;
    float4 diffColor;
};

cbuffer ParamBuffer : register(b6)
{
    PARAMETER param;
}

cbuffer FogBuffer : register(b7) //コンスタントバッファ7番とする
{
    float4 FogP; //xはfog_start yはfog_end zはfog_height
    float4 FogC;
    float4 FogGC;
}

struct VS_IN
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
    uint InstanceId : SV_InstanceID;
};


struct PS_IN
{
    float4 Position : SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
	
    float4 ShadowPosition : POSITION1;
    float4 PointShadowPosition[6] : POSITION2;
    float4 SpotShadowPosition : POSITION8;
};

StructuredBuffer<float3> Position : register(t2);

