/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef ENGINE_SHARED_GHOST_H
#define ENGINE_SHARED_GHOST_H

#include <engine/shared/protocol.h>
#include "huffman.h"

struct CGhostHeader
{
	unsigned char m_aMarker[8];
	unsigned char m_Version;
	char m_aOwner[MAX_NAME_LENGTH];
	char m_aMap[64];
	unsigned char m_aCrc[4];
	unsigned char m_aNumTicks[4];
	unsigned char m_aTime[4];
};

enum
{
	MAX_ITEM_SIZE = 256,
	NUM_ITEMS_PER_CHUNK = 50,
};

class CGhostItem
{
public:
	char m_aData[MAX_ITEM_SIZE];
	int m_Type;

	CGhostItem() : m_Type(-1) {}
	CGhostItem(int Type) : m_Type(Type) {}
	void Reset() { m_Type = -1; }
};

class CGhostRecorder
{
	class IStorage *m_pStorage;
	class IConsole *m_pConsole;

	IOHANDLE m_File;
	CGhostItem m_LastItem;

	char m_aBuffer[MAX_ITEM_SIZE * NUM_ITEMS_PER_CHUNK];
	char *m_pBufferPos;
	int m_BufferNumItems;

	void ResetBuffer();
	void FlushChunk();

	CHuffman m_Huffman;

public:
	CGhostRecorder();

	void Init(class IConsole *pConsole, class IStorage *pStorage);

	int Start(const char *pFilename, const char *pMap, unsigned MapCrc, const char *pName);
	int Stop(int Ticks, int Time);

	void WriteData(int Type, const char *pData, int Size);
	bool IsRecording() const { return m_File != 0; }
};

class CGhostLoader
{
	class IStorage *m_pStorage;
	class IConsole *m_pConsole;

	IOHANDLE m_File;
	CGhostHeader m_Header;
	CGhostItem m_LastItem;

	char m_aBuffer[MAX_ITEM_SIZE * NUM_ITEMS_PER_CHUNK];
	char *m_pBufferPos;
	int m_BufferNumItems;
	int m_BufferCurItem;
	int m_BufferPrevItem;

	void ResetBuffer();
	int ReadChunk(int *pType);

	CHuffman m_Huffman;

public:
	CGhostLoader();

	void Init(class IConsole *pConsole, class IStorage *pStorage);

	int Load(const char *pFilename, const char *pMap);
	void Close();
	const CGhostHeader *GetHeader() const { return &m_Header; }

	bool ReadNextType(int *pType);
	bool ReadData(int Type, char *pData, int Size);

	bool GetGhostInfo(const char *pFilename, CGhostHeader *pGhostHeader) const;

	static int GetTime(const CGhostHeader *pH) { return (pH->m_aTime[0] << 24) | (pH->m_aTime[1] << 16) | (pH->m_aTime[2] << 8) | (pH->m_aTime[3]);  };
	static int GetTicks(const CGhostHeader *pH) { return (pH->m_aNumTicks[0] << 24) | (pH->m_aNumTicks[1] << 16) | (pH->m_aNumTicks[2] << 8) | (pH->m_aNumTicks[3]); };
	static unsigned GetMapCrc(const CGhostHeader *pH) { return (pH->m_aCrc[0] << 24) | (pH->m_aCrc[1] << 16) | (pH->m_aCrc[2] << 8) | (pH->m_aCrc[3]); };
};

#endif