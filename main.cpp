#include "./include/npc.h"
#include "./include/outlow.h"
#include "./include/bear.h"
#include "./include/werewolf.h"
#include "./include/npc_factory.h"
#include "./include/text_observer.h"
#include "./include/npc_array_saver.h"
#include "./include/fight_func.h"

const int FIELD_SIZE{501};
const int START_DIST{20};
const int DIST_STEP{10};

int main() {
    srand(time(NULL));

    NPC_Factory npc_factory;
    set_t npc_set;

    std::cout << "Generating ..." << std::endl;
    const int NPC_count = 100;
    for (size_t i = 0; i < NPC_count; ++i) {
        npc_set.insert(npc_factory.createNPC(NpcType(std::rand() % NPC_TYPES_COUNT + 1),
                                                 "",
                                                 std::rand() % FIELD_SIZE,
                                                 std::rand() % FIELD_SIZE));
    }
    
    std::cout << "Saving ..." << std::endl;
    save(npc_set, "npc.txt");

    std::cout << "Loading ..." << std::endl;
    npc_set = load("npc.txt");

    std::cout << "Fighting ..." << std::endl
              << npc_set;

    for (size_t dist = START_DIST; (dist <= FIELD_SIZE) && !npc_set.empty(); dist += DIST_STEP) {
        auto lose_list = fight(npc_set, dist);
        for (auto &d : lose_list) {
            npc_set.erase(d);
        }
        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << dist << std::endl
                  << "defeated: " << lose_list.size() << std::endl
                  << std::endl << std::endl;
    }
    std::cout << "Remaining:" << std::endl;
    for (const auto &npc : npc_set) {
        std::cout << *npc << std::endl;
    }
    return 0;
}