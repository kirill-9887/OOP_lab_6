#include "../include/npc.h"

std::vector<std::pair<enum NpcType, enum NpcType>> ATTACK_DEFENDER_PAIRS = {
    { OutlowType, BearType },
    { BearType, WerewolfType },
    { WerewolfType, OutlowType }
};

std::string gen_name() {
    static int n = 0;
    int x = n;
    ++n;
    return "npc_" + std::to_string(x);
}

NPC::NPC(NpcType t, const std::string &_name, int _x, int _y) : type(t), name(_name.empty() ? gen_name() : _name), x(_x), y(_y) {}

NpcType NPC::get_type() const {
    return type;
}

std::string NPC::get_name() const {
    return name;
}

bool NPC::is_lose() const {
    return lose;
}

bool NPC::is_in_game() const {
    return !lose;
}

void NPC::set_lose() {
    lose = true;
}

void NPC::subscribe(const std::shared_ptr<IFightObserver> &observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> &defender) {
    for (auto &o : observers) {
        o->on_fight(shared_from_this(), defender);
    }
}

bool NPC::is_close(const std::shared_ptr<NPC> &defender, size_t distance) const {
    bool res = (std::pow(x - defender->x, 2) + std::pow(y - defender->y, 2)) <= std::pow(distance, 2);
    return res;
}

void NPC::save(std::ostream &os) const {
    os << type << std::endl;
    os << name << std::endl;
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream& NPC::print(std::ostream &os) const {
    os << "NPC " << name << " { x:" << x << ", y:" << y << " } in_game: " << !lose;
    return os;
}

std::ostream &operator<<(std::ostream &os, const NPC &npc){
    return npc.print(os);
}

int NPC::get_x() const {
    return x;
}

int NPC::get_y() const {
    return y;
}

bool NPC::is_attacker_defender(NpcType attacker_type, NpcType defender_type) {
    for (const auto &pair : ATTACK_DEFENDER_PAIRS) {
        if (attacker_type == pair.first && defender_type == pair.second) {
            return true;
        }
    }
    return false;
}