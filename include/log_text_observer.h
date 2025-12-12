#ifndef LOG_TEXT_OBSERVER_H
#define LOG_TEXT_OBSERVER_H

#include "./npc.h"

class LogTextObserver : public IFightObserver {

private:
    LogTextObserver(){};
    const std::string filename = "log.txt";

public:
    LogTextObserver(const LogTextObserver&) = delete;
    LogTextObserver(LogTextObserver&&) noexcept = delete;
    LogTextObserver& operator=(const LogTextObserver&) = delete;
    LogTextObserver& operator=(LogTextObserver&&) noexcept = delete;
    
    static std::shared_ptr<IFightObserver> get();

    void on_fight(
        const std::shared_ptr<NPC> &attacker,
        const std::shared_ptr<NPC> &defender
    ) override;
};

#endif