
uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower;
varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;

 void main(void)
 {
 vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
 vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);
 vec4 diffMatColor = texture2D(u_texture, v_texcoord);
 vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz);
 vec3 lightVect = normalize(v_position.xyz - u_lightPosition.xyz);
 vec3 reflectLight = normalize(reflect(lightVect, v_normal));
 float len = length(v_position.xyz - eyePosition.xyz);
 float specularFactor = 10.0;
 float ambientFactor = 0.1;
 vec4 diffColor = diffMatColor * u_lightPower * dot(v_normal, -lightVect) / (1.0 + 0.25 * len*len);
 resultColor += diffColor;
     gl_FragColor = resultColor;
 }
