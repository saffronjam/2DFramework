#include "PingModule.h"

#include "INetMgr.h"

PingModule::PingModule(INetMgr *ioHelper)
    : INetModule(ioHelper)
{
}

void PingModule::HandlePacket(AreYouAlive, const ParsedPacket &packet)
{
    log_info("Someone asked me if I'm alive, of course I am...");
    m_ioHelper->SendEmpty<TCP>(IAmAlive, packet.connection);
}

void PingModule::HandlePacket(IAmAlive, const ParsedPacket &packet)
{
    log_info("They said they are alive...this time...");
}