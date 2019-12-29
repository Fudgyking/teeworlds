/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_COLLISION_H
#define GAME_COLLISION_H

#include <base/vmath.h>

class CCollision
{
	class CTile *m_pTiles;
	class CTile *m_pTilesEx;
	class CTile *m_pTele;
	class CTile *m_pSpeedupForce;
	class CTile *m_pSpeedupAngle;
	int m_Width;
	int m_Height;
	class CLayers *m_pLayers;

	vec2 *m_pTeleporter;
	bool m_MainTiles;
	bool m_StopTiles;

	void InitTeleporter();

	bool IsTile(int x, int y, int Flag=COLFLAG_SOLID) const;
	int GetTile(int x, int y) const;

	bool IsRaceTile(int TilePos, int Mask);

public:
	enum
	{
		COLFLAG_SOLID=1,
		COLFLAG_DEATH=2,
		COLFLAG_NOHOOK=4,

		RACECHECK_TILES_MAIN=1,
		RACECHECK_TILES_STOP=2,
		RACECHECK_TELE=4,
		RACECHECK_SPEEDUP=8,
	};

	CCollision();
	virtual ~CCollision();
	void Init(class CLayers *pLayers);
	bool CheckPoint(float x, float y, int Flag=COLFLAG_SOLID) const { return IsTile(round_to_int(x), round_to_int(y), Flag); }
	bool CheckPoint(vec2 Pos, int Flag=COLFLAG_SOLID) const { return CheckPoint(Pos.x, Pos.y, Flag); }
	int GetCollisionAt(float x, float y) const { return GetTile(round_to_int(x), round_to_int(y)); }
	int GetWidth() const { return m_Width; };
	int GetHeight() const { return m_Height; };
	int IntersectLine(vec2 Pos0, vec2 Pos1, vec2 *pOutCollision, vec2 *pOutBeforeCollision) const;
	void MovePoint(vec2 *pInoutPos, vec2 *pInoutVel, float Elasticity, int *pBounces) const;
	void MoveBox(vec2 *pInoutPos, vec2 *pInoutVel, vec2 Size, float Elasticity, bool *pDeath=0) const;
	bool TestBox(vec2 Pos, vec2 Size, int Flag=COLFLAG_SOLID) const;

	// race
	int GetTilePos(vec2 Pos);
	int GetTilePosLayer(const class CMapItemLayerTilemap *pLayer, int TilePos);
	vec2 GetPos(int TilePos);

	bool CheckIndexEx(vec2 Pos, int Index) { return CheckIndexEx(GetTilePos(Pos), Index); }
	bool CheckIndexEx(int TilePos, int Index);
	int CheckIndexExRange(int TilePos, int MinIndex, int MaxIndex);

	int CheckRaceTile(vec2 PrevPos, vec2 Pos, int Mask);

	int CheckCheckpoint(int TilePos);
	int CheckSpeedup(int TilePos);
	void GetSpeedup(int SpeedupPos, vec2 *Dir, int *Force);
	int CheckTeleport(int TilePos);
	vec2 GetTeleportDestination(int Number);
};

#endif
