#ifndef NPC_ARRAY_SAVER
#define NPC_ARRAY_SAVER

#include "./npc.h"
#include "./npc_factory.h"

void save(const set_t &array, const std::string &filename);

set_t load(const std::string &filename);

std::ostream &operator<<(std::ostream &os, const set_t &array);

#endif