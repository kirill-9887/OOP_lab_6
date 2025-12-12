#include "../include/outlow.h"
#include "../include/bear.h"
#include "../include/werewolf.h"

Outlow::Outlow(const std::string &name, int x, int y) : NPC(OutlowType, name, x, y) {}

std::ostream& Outlow::print(std::ostream &os) const {
    return NPC::print(os) << " type: outlow";
}

bool Outlow::fight_visit(const std::shared_ptr<Outlow> &other) {
    fight_notify(other);
    return false;
}

bool Outlow::fight_visit(const std::shared_ptr<Bear> &other) {
    other->set_lose();
    fight_notify(other);
    return true;
}

bool Outlow::fight_visit(const std::shared_ptr<Werewolf> &other) {
    fight_notify(other);
    return false;
}

bool Outlow::accept(const std::shared_ptr<NPC> &visitor) {
    return visitor->fight_visit(std::static_pointer_cast<Outlow>(shared_from_this()));
}