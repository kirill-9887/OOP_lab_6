#include "../include/log_text_observer.h"

std::shared_ptr<IFightObserver> LogTextObserver::get() {
    static LogTextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
}

void LogTextObserver::on_fight(const std::shared_ptr<NPC> &attacker, const std::shared_ptr<NPC> &defender) {
    if (!defender->is_in_game() || !attacker->is_in_game()) {
        std::ofstream fs(filename, std::ios::app);
        if (!defender->is_in_game()) {
            fs << *attacker << " DEFEATED " << *defender << std::endl;
        }
        if (!attacker->is_in_game()) {
            fs << *defender << " DEFEATED " << *attacker << std::endl;
        }
        fs.flush();
        fs.close();
    }
}