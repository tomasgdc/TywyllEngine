#include <stdafx.h>
#include <TywLib\math\GLXMath.h>

//Renderer Includes
#include "Model.h"


bool Plane::Inside(const glx::vec3<float> &point) const
{
	// Inside the plane is defined as the direction the normal is facing
	float result;// = D3DXPlaneDotCoord(this, &point);
	return (result >= 0.0f);
}

bool Plane::Inside(const glx::vec3<float> &point, const float radius) const
{
	float fDistance;	// calculate our distances to each of the planes

						// find the distance to this plane
	fDistance;// = D3DXPlaneDotCoord(this, &point);

	// if this distance is < -radius, we are outside
	return (fDistance >= -radius);
}
