#ifndef _RAY_CAST_H_
#define _RAY_CAST_H_

class Intersection
{
public:
	FLOAT m_fDist;                  // distance from ray origin to intersection
	DWORD m_dwFace;					// the face index of the intersection
	FLOAT m_fBary1, m_fBary2;		// Barycentric coordinates of the intersection
	FLOAT m_tu, m_tv;               // texture coords of intersection
	unsigned int m_actorId;				// Which actor was intersected if there was one
	glx::vec3<float> m_worldLoc;				// world location of intersection
	glx::vec3<float> m_actorLoc;				// actor local coordinates of intersection
	glx::vec3<float> m_normal;					// normal of intersection

	bool const operator <(Intersection const &other) { return m_fDist < other.m_fDist; }
};

template <class T>
void InitIntersection(Intersection &intersection, DWORD faceIndex, FLOAT dist, FLOAT u, FLOAT v, unsigned int actorId, WORD* pIndices, T* pVertices, const glx::mat4<float> &matWorld);


typedef std::vector<Intersection> IntersectionArray;

class CDXUTSDKMesh;

class RayCast
{
protected:
	//LPDIRECT3DVERTEXBUFFER9     m_pVB;

public:
	//RayCast(Point point, DWORD maxIntersections = 16);

	DWORD m_MaxIntersections;
	DWORD m_NumIntersections;
	bool m_bUseD3DXIntersect;      // Whether to use D3DXIntersect
	bool m_bAllHits;			// Whether to just get the first "hit" or all "hits"
	//Point m_Point;

//	D3DXVECTOR3 m_vPickRayDir;
//	D3DXVECTOR3 m_vPickRayOrig;

	IntersectionArray m_IntersectionArray;

	/*
	HRESULT Pick(Scene *pScene, ActorId actorId, ID3DXMesh *pMesh);
	HRESULT Pick(Scene *pScene, ActorId actorId, CDXUTSDKMesh *pMesh);

	HRESULT Pick(Scene *pScene, ActorId actorId, LPDIRECT3DVERTEXBUFFER9 pVerts, LPDIRECT3DINDEXBUFFER9 pIndices, DWORD numPolys);
	HRESULT Pick(Scene *pScene, ActorId actorId, LPDIRECT3DVERTEXBUFFER9 pVerts, DWORD numPolys);
	*/

	void Sort();
};

#endif