#ifndef _JOINT_TRANSFORM_H_
#define _JOINT_TRANSFORM_H_


class JointQuat 
{
public:
	glx::quat		 q;
	glx::vec3<float> t;
};

class JointMat 
{
public:
	void					SetRotation(const glx::mat4<float> &m);
	glx::mat4<float>		GetRotation();
	void					SetTranslation(const glx::vec3<float> &t);
	glx::vec3<float>		GetTranslation();

	
	glx::vec3<float> operator * (glx::vec3<float>& v) const;
public:
	float mat[3][4];
};


//multiplication operator
inline glx::vec3<float> JointMat::operator * (glx::vec3<float>& v) const
{
	glx::vec3<float> vec
		(
		mat[0][0] * v.x + mat[1][0] * v.y + mat[2][0] * v.z,
		mat[0][1] * v.x + mat[1][1] * v.y + mat[2][1] * v.z,
		mat[0][2] * v.x + mat[1][2] * v.y + mat[2][2] * v.z);

	//vec.x = vec.x / mat[0][3];
	//vec.y = vec.y / mat[1][3];
	//vec.z = vec.z / mat[2][3];
	return vec;
}


inline void JointMat::SetTranslation(const glx::vec3<float> &t) {
	mat[0][3] = t[0];
	mat[1][3] = t[1];
	mat[2][3] = t[2];
}
#endif
