#pragma once
#include "NetAddress.h"

// 소켓 관련 유틸리티 메소드를 제공 및 각종 소켓 옵션 설정 클래스

class SocketUtils
{
public:
	static LPFN_CONNECTEX		ConnectEx;
	static LPFN_DISCONNECTEX	DisconnectEx;
	static LPFN_ACCEPTEX		AcceptEx;

public:
	// 전역으로 호출해 Init 및 Clear
	static void Init();
	static void Clear();

	static bool BindWindowsFunction(SOCKET _socket, GUID _guid, LPVOID* _fn);
	static SOCKET CreateSocket();

	// 자주 사용하는 기능들 미리 제작
	// https://velog.io/@jyongk/TCP-%EC%86%8C%EC%BC%93-%EC%98%B5%EC%85%98-SOLINGER
	static bool SetLinger(SOCKET _socket, unsigned __int16 _onoff, unsigned __int16 _linger);
	static bool SetReuseAddress(SOCKET _socket, bool _flag);
	static bool SetRecvBufferSize(SOCKET _socket, __int32 _size);
	static bool SetSendBufferSize(SOCKET _socket, __int32 _size);
	// 네이글 알고리즘
	static bool SetTcpNoDelay(SOCKET _socket, bool _flag);
	static bool SetUpdateAcceptSocket(SOCKET _socket, SOCKET _listenSocket);

	static bool Bind(SOCKET& _socket, NetAddress _netAddr);
	static bool BindAnyAddress(SOCKET& _socket, unsigned __int16 _port);
	static bool Listen(SOCKET& _socket, __int32 _backlog = SOMAXCONN);
	static void Close(SOCKET& _socket);
};

// SetSocketOption 랩핑
template<typename T>
static inline bool SetSockOpt(SOCKET _socket, __int32 _level, __int32 _optName, T _optVal)
{
	return SOCKET_ERROR != ::setsockopt(_socket, _level, _optName,
		reinterpret_cast<char*>(&_optVal), sizeof(T));
}