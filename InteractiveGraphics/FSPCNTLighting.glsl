#version 400
in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragPosition;
in vec2 fragTexCoord;

out vec4 color;

uniform float materialAmbientIntensity;
uniform float materialSpecularIntensity;
uniform float materialShininess;

uniform vec3 globalLightPosition;
uniform vec3 globalLightColor;
uniform float globalLightIntensity;

uniform int numberOfLights;
uniform vec3 localLightPosition[10];
uniform vec3 localLightColor[10];
uniform float localLightIntensity[10];
uniform float localLightAttenuationCoefficient[10];

uniform sampler2D tex;
uniform vec3 viewPosition;

vec4 calculateDiffuse(vec3 lightDir, vec3 unitNormal, float lightIntensity, vec3 lightColor);

void main()
{
   vec3 toGlobalLightDir = normalize(globalLightPosition - fragPosition);
   vec4 globalDiffuse = calculateDiffuse(
      toGlobalLightDir, fragNormal, globalLightIntensity, globalLightColor);

   vec3 viewDir = normalize(viewPosition - fragPosition);
   vec4 totalLocalDiffuse;
   vec3 toLocalLightDir;
   vec4 localDiffuse;
   float distanceToLight;
   float attenuation;
   vec4 totalSpecular;
   for(int i = 0; i < numberOfLights; i++){
      toLocalLightDir = normalize(localLightPosition[i] - fragPosition);
      localDiffuse = calculateDiffuse(
         toLocalLightDir, fragNormal, localLightIntensity[i], localLightColor[i]);
      distanceToLight = length(localLightPosition[i] - fragPosition);
      attenuation = 1.0 / (1.0 + localLightAttenuationCoefficient[i] * pow(distanceToLight, 2));
      totalLocalDiffuse += (attenuation * localDiffuse);
      if(materialShininess > 0.0f){
         vec3 reflectDir = reflect(-toLocalLightDir, fragNormal);
         float angIncidence = max(dot(viewDir, reflectDir), 0.0f);
         float spec = pow(angIncidence, materialShininess);
         totalSpecular += materialSpecularIntensity * spec 
            * localLightIntensity[i] * vec4(localLightColor[i], 1.0f); 
      }
   }

   vec4 texFragColor = texture(tex, fragTexCoord) * fragColor;
   vec4 ambientColor = materialAmbientIntensity * vec4(1.0f, 1.0f, 1.0f, 1.0f);
   color = (ambientColor + globalDiffuse + totalLocalDiffuse + totalSpecular) * texFragColor;
   // Gamma correction
   float gamma = 1.0/2.2;
   color.r = pow(color.r, gamma);
   color.g = pow(color.g, gamma);
   color.b = pow(color.b, gamma);
}

vec4 calculateDiffuse(vec3 lightDir, vec3 unitNormal, float lightIntensity, vec3 lightColor)
{
   float cosAngIncidence = dot(unitNormal, lightDir);
   cosAngIncidence = clamp(cosAngIncidence, 0.0f, 1.0f);
   return cosAngIncidence * lightIntensity * vec4(lightColor, 1.0f);
}
