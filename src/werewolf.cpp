#include "../include/werewolf.h"
#include "../include/outlow.h"
#include "../include/bear.h"

Werewolf::Werewolf(const std::string &name, int x, int y) : NPC(WerewolfType, name, x, y) {}

std::ostream& Werewolf::print(std::ostream &os) const {
    return NPC::print(os) << " type: werewolf";
}

bool Werewolf::fight_visit(const std::shared_ptr<Outlow> &other) {
    other->set_lose();
    fight_notify(other);
    return true;
}

bool Werewolf::fight_visit(const std::shared_ptr<Bear> &other) {
    fight_notify(other);
    return false;
}

bool Werewolf::fight_visit(const std::shared_ptr<Werewolf> &other) {
    fight_notify(other);
    return false;
}

bool Werewolf::accept(const std::shared_ptr<NPC> &visitor) {
    return visitor->fight_visit(std::static_pointer_cast<Werewolf>(shared_from_this()));
}