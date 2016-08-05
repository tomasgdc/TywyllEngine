#ifndef _PLAYER_VIEW_H_
#define _PLAYER_VIEW_H_

//forward declaration
class PathingGraph;

#include "IGameView.h"


/*
	This is AI Player View
*/
class AIPlayerView : public IGameView
{
private:
	std::shared_ptr<PathingGraph> m_pPathingGraph;

protected:
	unsigned int	m_ViewId;
	unsigned int m_PlayerActorId;

public:
	AIPlayerView(std::shared_ptr<PathingGraph> pPathingGraph);
	virtual ~AIPlayerView();

	virtual HRESULT VOnRestore() { return S_OK; }
	virtual void VOnRender(double fTime, float fElapsedTime) {}
	virtual HRESULT VOnLostDevice() { return S_OK; }
	virtual GameViewType VGetType() { return GameView_AI; }
	virtual unsigned int VGetId() const { return m_ViewId; }
	virtual void VOnAttach(unsigned int vid, unsigned int actorId) { m_ViewId = vid; m_PlayerActorId = actorId; }
	virtual LRESULT CALLBACK VOnMsgProc(AppMsg msg) { return 0; }
	virtual void VOnUpdate(unsigned long deltaMs) {}

	std::shared_ptr<PathingGraph> GetPathingGraph(void) const { return m_pPathingGraph; }
};

#endif