varying highp vec2 qt_TexCoord0;
uniform sampler2D tex_y;
uniform sampler2D tex_u;
uniform sampler2D tex_v;

void main(void)
{
    vec3 yuv;
    vec3 rgb;
    yuv.x=texture2D(tex_y,qt_TexCoord0).r;
    yuv.y=texture2D(tex_u,qt_TexCoord0).r-0.5;
    yuv.z=texture2D(tex_v,qt_TexCoord0).r-0.5;
    rgb=mat3(1,1,1,0,-0.39465,2.03211,1.13983,-0.58060,0)*yuv;
    gl_FragColor = vec4(rgb,1);
}
