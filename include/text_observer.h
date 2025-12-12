#ifndef TEXT_OBSERVER_H
#define TEXT_OBSERVER_H

#include "./npc.h"

class TextObserver : public IFightObserver {

private:
    TextObserver(){};

public:
    TextObserver(const TextObserver&) = delete;
    TextObserver(TextObserver&&) noexcept = delete;
    TextObserver& operator=(const TextObserver&) = delete;
    TextObserver& operator=(TextObserver&&) noexcept = delete;

    static std::shared_ptr<IFightObserver> get();

    void on_fight(
        const std::shared_ptr<NPC> &attacker,
        const std::shared_ptr<NPC> &defender
    ) override;
};

#endif