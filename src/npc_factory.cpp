#include "../include/npc_factory.h"

std::shared_ptr<NPC> NPC_Factory::createNPC(NpcType type, const std::string &name, int x, int y) {
    std::shared_ptr<NPC> result;
    switch (type) {
        case OutlowType:
            result = std::make_shared<Outlow>(name, x, y);
            break;
        case BearType:
            result = std::make_shared<Bear>(name, x, y);
            break;
        case WerewolfType:
            result = std::make_shared<Werewolf>(name, x, y);
            break;
        default:
            break;
    }
    if (result) {
        result->subscribe(TextObserver::get());
        result->subscribe(LogTextObserver::get());
    }
    return result;
}

std::shared_ptr<NPC> NPC_Factory::createNPC(std::istream &is) {
    std::shared_ptr<NPC> result;
    int type;
    std::string name;
    int x;
    int y;
    if (is >> type
        && is >> name
        && is >> x
        && is >> y
    ) {
        result = createNPC(static_cast<NpcType>(type), name, x, y);
    } else {
        std::cerr << "Unexpected NPC type: " << type << std::endl;
    }
    return result;
}