#pragma once
#include "../../DhNet_Server/DhNet_Protocol/PacketList.h"
#include "../../DhNet_Server/ServerCore/PacketHandler.h"

bool RecvTestPacket(PacketHeader* _header, std::shared_ptr<Session>& _session)
{
	auto temp = reinterpret_cast<TestPacket*>(_header);

	std::cout << "OnRecv Len " << temp->m_dataSize << " / " << temp->m_test << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(1));

	auto sender = Sender::Alloc<TestPacket>();
	auto packet = sender->GetWritePointer<TestPacket>();
	packet->Init(PacketEnum::Test, sizeof(TestPacket));
	strcpy_s(packet->m_test, "Test(Client)");

	_session->Send(sender);

	return true;
}