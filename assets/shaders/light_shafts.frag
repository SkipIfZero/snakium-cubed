#version 330

// Structs
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

struct SpotLight {
	vec3 vsPos;
	vec3 vsDir;
	vec3 color;
	float range;
	float softFovRad; // outer
	float sharpFovRad; //inner
	float softAngleCos; // outer
	float sharpAngleCos; // inner
	mat4 lightMatrix;
};

// Input, output and uniforms
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

// Input
in vec2 uvCoord;

// Output
out vec4 outFragColor;

// Uniforms
uniform sampler2D uPositionTexture;
uniform SpotLight uSpotlight;
uniform sampler2DShadow uShadowMapLowRes;

const float shadowSampleWeight = 1.0;
const float lightSampleWeight = 1.0 / shadowSampleWeight;
uniform float uLightShaftExposure = 0.8;
uniform float uLightShaftRange = 5.0;
uniform int uLightShaftSamples = 128;

// Helper functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

float sampleShadowMap(sampler2DShadow shadowMap, vec3 vsSamplePos)
{
	return textureProj(shadowMap, uSpotlight.lightMatrix * vec4(vsSamplePos, 1.0));
}

float calcLightScale(vec3 samplePos, float outerCos, float innerCos)
{
	vec3 toSample = samplePos - uSpotlight.vsPos;
	vec3 toSampleDir = normalize(toSample);
	float lightDist = length(toSample);
	float rangeSquared = uSpotlight.range * uSpotlight.range;
	float lightDistSquared = lightDist * lightDist;
	float attenuation = smoothstep(outerCos, innerCos, dot(toSampleDir, uSpotlight.vsDir));
	return attenuation * max((-1.0 / rangeSquared) * (lightDistSquared - rangeSquared), 0);
}

float lightShaftFactor(sampler2DShadow shadowMap, vec3 vsPos, float outerCos, float innerCos)
{
	vec3 camDir = normalize(vsPos);
	float sampleLength = min(length(vsPos), uLightShaftRange) / float(uLightShaftSamples+1);
	vec3 toNextSamplePos = camDir * sampleLength;

	vec3 currentSamplePos = toNextSamplePos;
	float factor = 0.0;
	for (int i = 0; i < uLightShaftSamples; i++) {
		factor += sampleShadowMap(shadowMap, currentSamplePos) * calcLightScale(currentSamplePos, outerCos, innerCos);
		currentSamplePos += toNextSamplePos;
	}

	factor = (factor * lightSampleWeight) / float(uLightShaftSamples);
	factor *= shadowSampleWeight;
	
	return factor;
}

// Intersection test
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

struct Intersection {
	bool hit;
	vec3 first, second;
};

// length(coneDir) == 0
// length(rayDir) == 0
// cosConeAngle == cos(coneAngle) == cos(coneFov / 2)
Intersection rayVsConeIntersectionTest(vec3 rayPos, vec3 rayDir, vec3 conePos, vec3 coneDir, float cosConeAngle)
{
	// Simplifications
	float cos2 = cosConeAngle * cosConeAngle;
	float dirsDot = dot(coneDir, rayDir);
	vec3 rayToCone = rayPos - conePos;
	float coneDirDotRayToCone = dot(coneDir, rayToCone);

	// Calculations
	// ax² + bx + c = 0
	// x = (-b [+-] sqrt(b¹ - 4ac)) / (2a)
	float a = (dirsDot * dirsDot) - cos2;
	float b = 2.0 * (coneDirDotRayToCone * dirsDot - cos2 * dot(rayToCone, rayDir));
	float c = coneDirDotRayToCone * coneDirDotRayToCone - cos2 * dot(rayToCone, rayToCone);

	// sqrt(b¹ - 4ac)
	// if inner factor is below zero there is no solution, i.e. no hit
	float sqrtInner = b * b - 4 * a * c;
	if (sqrtInner < 0) {
		return Intersection(false, vec3(0), vec3(0));
	}

	// Calculate closest and farthest points
	float sqrtProd = sqrt(sqrtInner);
	float a2 = 2 * a;
	float t1 = (-b - sqrtProd) / a2;
	float t2 = (-b + sqrtProd) / a2;
	vec3 closest = rayPos + t1 * rayDir;
	vec3 farthest = rayPos + t2 * rayDir;

	return Intersection(true, closest, farthest);
}

// Main
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void main()
{
	vec3 vsPos = texture(uPositionTexture, uvCoord).xyz;

	// Ray vs Cone Intersection test parameters
	vec3 camPos = vec3(0);
	vec3 camDir = normalize(vsPos);
	vec3 lightPos = uSpotlight.vsPos;
	vec3 lightDir = uSpotlight.vsDir;
	float lightCosAngle = uSpotlight.softAngleCos;

	// Ray vs Cone intersection test
	Intersection isect = rayVsConeIntersectionTest(camPos, camDir, lightPos, lightDir, lightCosAngle);
	if (!isect.hit) {
		discard;
	}

	float outerCos = uSpotlight.softAngleCos;
	float innerCos = uSpotlight.sharpAngleCos;
	float lightShafts = lightShaftFactor(uShadowMapLowRes, vsPos, outerCos, innerCos);

	vec3 total = uLightShaftExposure * lightShafts * uSpotlight.color;
	outFragColor = vec4(total, 1.0);
}