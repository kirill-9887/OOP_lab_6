#ifndef BEAR_H
#define BEAR_H

#include "npc.h"

struct Bear : public NPC
{
    Bear(const std::string &name, int x, int y);
    std::ostream& print(std::ostream &os) const override;

    bool accept(const std::shared_ptr<NPC> &visitor) override;
    bool fight_visit(const std::shared_ptr<Outlow> &other) override;
    bool fight_visit(const std::shared_ptr<Bear> &other) override;
    bool fight_visit(const std::shared_ptr<Werewolf> &other) override;
};

#endif