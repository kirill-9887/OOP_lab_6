#ifndef FIGHT_FUNC_H
#define FIGHT_FUNC_H

#include "./npc.h"

// Внутри цикла вместо кучи условий должно быть:
// success = defender->accept(attacker);

set_t fight(const set_t &npc_set, size_t distance) {
    set_t lose_list;
    for (auto &attacker : npc_set) {
        for (auto &defender : npc_set) {
            if (attacker->is_in_game() && defender->is_in_game()
                && (attacker != defender) && (attacker->is_close(defender, distance)))
            {
                defender->accept(attacker);
                if (!defender->is_in_game()) {
                    lose_list.insert(defender);
                }
            }
        }
    }
    return lose_list;
}

#endif