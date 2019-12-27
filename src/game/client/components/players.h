/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_CLIENT_COMPONENTS_PLAYERS_H
#define GAME_CLIENT_COMPONENTS_PLAYERS_H
#include <game/client/component.h>

class CPlayers : public CComponent
{
	friend class CGhost;

	CTeeRenderInfo m_aRenderInfo[MAX_CLIENTS];
	void RenderPlayer(
		const CNetObj_Character *pPrevChar,
		const CNetObj_Character *pPlayerChar,
		const CNetObj_PlayerInfo *pInfo,
		const CTeeRenderInfo *pRenderInfo,
		int ClientID,
		float Intra = 0.f
	);
	void RenderHook(
		const CNetObj_Character *pPrevChar,
		const CNetObj_Character *pPlayerChar,
		const CTeeRenderInfo *pRenderInfo,
		int ClientID,
		float Intra = 0.f
	);

public:
	virtual void OnRender();
};

#endif
