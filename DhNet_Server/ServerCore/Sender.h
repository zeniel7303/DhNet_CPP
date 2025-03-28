#pragma once
#include "SendPool.h"
#include "PacketHeader.h"

//패킷 전송시 사용
//SendPool에서 패킷 전송 할당받아 사용 후 반납.

class Sender
{
private:
	DataChunk*			m_tempChunk;
	int					m_index;
	unsigned short		m_count;

	static SendPool		m_sendPool;

public:
	Sender();
	~Sender();

	static int Init(unsigned short _sendCount);

	template<typename T>
	static shared_ptr<Sender> Alloc();
	int DeAlloc();

	void SetSendDataChunk(DataChunk* _chunk, int _chunkIndex, unsigned short _chunkCount);

	template<typename T>
	T* GetWritePointer();
	void* GetSendPointer();
	unsigned short GetSendSize();
};

template<typename T>
inline shared_ptr<Sender> Sender::Alloc()
{
	int size = sizeof(T);

	ASSERT_CRASH(size >= sizeof(PacketHeader));

	auto shared = m_sendPool.Alloc(size);

	if (shared == nullptr) return nullptr;

	(reinterpret_cast<PacketHeader*>(shared->m_tempChunk))->m_dataSize = size;

	return shared;
}

template<typename T>
inline T* Sender::GetWritePointer()
{
	auto ptr = reinterpret_cast<char*>(m_tempChunk);

	return reinterpret_cast<T*>(ptr);
}
