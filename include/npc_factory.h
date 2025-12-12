#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include "./npc.h"
#include "./bear.h"
#include "./outlow.h"
#include "./werewolf.h"
#include "./text_observer.h"
#include "./log_text_observer.h"

struct NPC_Factory final {
public:
    NPC_Factory() = default;
    std::shared_ptr<NPC> createNPC(NpcType type, const std::string &name, int x, int y);
    std::shared_ptr<NPC> createNPC(std::istream &is);
};

#endif