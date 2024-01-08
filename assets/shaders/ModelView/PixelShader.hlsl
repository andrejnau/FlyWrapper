struct VS_OUTPUT
{
    float4 pos       : SV_POSITION;
    float3 fragPos   : POSITION;
    float3 normal    : NORMAL;
    float3 tangent   : TANGENT;
    float2 texCoord  : TEXCOORD;
};

cbuffer ConstantBuf
{
    uint32_t texture_index;
    uint32_t sampler_index;
};

Texture2D albedoMap[] : register(t, space8);
SamplerState g_sampler[] : register(s, space9);

float4 getTexture(Texture2D _texture, SamplerState _sample, float2 _tex_coord, bool _need_gamma = false)
{
    float4 _color = _texture.Sample(_sample, _tex_coord);
    if (_need_gamma)
        _color = float4(pow(abs(_color.rgb), 2.2), _color.a);
    return _color;
}

float4 LinearTosRGBA(float3 color)
{
    return float4(pow(abs(color), 1 / 2.2), 1.0);
}

float4 main(VS_OUTPUT input) : SV_TARGET
{
    return LinearTosRGBA(getTexture(albedoMap[texture_index], g_sampler[sampler_index], input.texCoord, true).rgb);
}
