#include "../include/bear.h"
#include "../include/werewolf.h"
#include "../include/outlow.h"

Bear::Bear(const std::string &name, int x, int y) : NPC(BearType, name, x, y) {}

std::ostream& Bear::print(std::ostream &os) const {
    return NPC::print(os) << " type: bear";
}

bool Bear::fight_visit(const std::shared_ptr<Outlow> &other) {
    fight_notify(other);
    return false;
}

bool Bear::fight_visit(const std::shared_ptr<Bear> &other) {
    fight_notify(other);
    return false;
}

bool Bear::fight_visit(const std::shared_ptr<Werewolf> &other) {
    other->set_lose();
    fight_notify(other);
    return true;
}

bool Bear::accept(const std::shared_ptr<NPC> &visitor) {
    return visitor->fight_visit(std::static_pointer_cast<Bear>(shared_from_this()));
}