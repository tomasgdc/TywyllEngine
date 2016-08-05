#include <stdafx.h>
#include <TywLib\math\GLXMath.h>

//Game Includes
#include "AIPlayerView.h"
#include "AI\Pathing.h"


AIPlayerView::AIPlayerView(std::shared_ptr<PathingGraph> pPathingGraph): IGameView(), m_pPathingGraph(pPathingGraph)
{

}


AIPlayerView::~AIPlayerView()
{

}