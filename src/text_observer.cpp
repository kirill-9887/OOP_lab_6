#include "../include/text_observer.h"

std::shared_ptr<IFightObserver> TextObserver::get() {
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
}

void TextObserver::on_fight(const std::shared_ptr<NPC> &attacker, const std::shared_ptr<NPC> &defender) {
    if (!defender->is_in_game()) {
        std::cout << *attacker << " DEFEATED " << *defender << std::endl;
    }
    if (!attacker->is_in_game()) {
        std::cout << *defender << " DEFEATED " << *attacker << std::endl;
    }
}