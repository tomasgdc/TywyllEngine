#ifndef _ENGINE_PHYSICS_DEBUG_DRAWER_H_
#define _ENGINE_PHYSICS_DEBUG_DRAWER_H_

class TYWPHYSICS_API PhysicsDebugDrawer
{
public:
	virtual void DrawContactPoint();
	virtual void ReportWarnings();
	virtual void SetDebugMode();
	virtual int  GetDebugMode();
	virtual void DrawLine();
};

#endif