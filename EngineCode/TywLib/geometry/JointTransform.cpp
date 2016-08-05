#include <stdafx.h>
#include "math\GLXMath.h"
#include "geometry\JointTransform.h"


//Stores into matrix as row major
void JointMat::SetRotation(const glx::mat4<float> &m) {
	mat[0][0] = m.m[0][0];
	mat[0][1] = m.m[1][0];
	mat[0][2] = m.m[2][0];
	mat[1][0] = m.m[0][1];
	mat[1][1] = m.m[1][1];
	mat[1][2] = m.m[2][1];
	mat[2][0] = m.m[0][2];
	mat[2][1] = m.m[1][2];
	mat[2][2] = m.m[2][2];
}


glx::mat4<float> JointMat::GetRotation() {
	glx::mat4<float> m;
	
	m.m[0][0] = mat[0][0];
	m.m[1][0] = mat[0][1];
	m.m[2][0] = mat[0][2];
	m.m[3][0] = 0.0f;

	m.m[0][1] = mat[1][0];
	m.m[1][1] = mat[1][1];
	m.m[2][1] = mat[1][2];
	m.m[3][1] = 0.0f;

	m.m[0][2] = mat[2][0];
	m.m[1][2] = mat[2][1];
	m.m[2][2] = mat[2][2];
	m.m[3][2] = 0.0f;

	m.m[0][3] = 0.0f;
	m.m[1][3] = 0.0f;
	m.m[2][3] = 0.0f;
	m.m[3][3] = 1.0f;
	return m;
}

glx::vec3<float> JointMat::GetTranslation()
{
	glx::vec3<float> t;
	t[0] = mat[0][3];
	t[1] = mat[1][3];
	t[2] = mat[2][3];
	return t;
}
