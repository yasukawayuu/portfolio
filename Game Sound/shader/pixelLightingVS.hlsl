
#include "common.hlsl"



void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp; //matrix�^�̕ϐ�wvp���`����

	//wvp = ���[���h�ϊ��s��~�r���[�ϊ��s��
    wvp = mul(World, View);
	//wvp = wvp �~ �v���W�F�N�V�����ϊ��s��
    wvp = mul(wvp, Projection);

	//���͂��ꂽ���_���W��ϊ����ďo�͐�֑������
    Out.Position = mul(In.Position, wvp);

	//���_�̖@�������[���h�s��ŕϊ�����
    float4 worldNormal, normal;

    normal = float4(In.Normal.xyz, 0.0f);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    Out.Normal = worldNormal;

    Out.Diffuse = In.Diffuse;

	//���_�J���[�͂��̂܂܃R�s�[
	//Out.Diffuse = In.Diffuse;
	
    Out.WorldPosition = mul(In.Position, World);
	
		//���͂��ꂽUV���W���o�͐�֑������
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
