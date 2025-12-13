#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <fstream>
#include <set>
#include <math.h>
#include <mutex>
#include <string>

struct NPC;
struct Outlow;
struct Bear;
struct Werewolf;

using set_t = std::set<std::shared_ptr<NPC>>;

const int NPC_TYPES_COUNT = 3;
enum NpcType {
    Unknown = 0,
    OutlowType = 1,
    BearType = 2,
    WerewolfType = 3
};

struct IFightObserver {
    virtual void on_fight(
        const std::shared_ptr<NPC> &attacker,
        const std::shared_ptr<NPC> &defender
    ) = 0;
};

struct NPC : public std::enable_shared_from_this<NPC>
{
private:
    NpcType type;
    std::string name{"null"};
    int x{0};
    int y{0};
    bool lose{false};
    std::vector<std::shared_ptr<IFightObserver>> observers;

public:
    NPC(NpcType t, const std::string &name, int _x, int _y);

    NpcType get_type() const;
    std::string get_name() const;

    bool is_lose() const;
    bool is_in_game() const;
    void set_lose();

    void subscribe(const std::shared_ptr<IFightObserver> &observer);
    void detach(const std::shared_ptr<IFightObserver> &observer);
    void fight_notify(const std::shared_ptr<NPC> &defender);
    
    virtual bool is_close(const std::shared_ptr<NPC> &defender, size_t distance) const;

    virtual bool accept(const std::shared_ptr<NPC> &visitor) = 0;
    virtual bool fight_visit(const std::shared_ptr<Outlow> &other) = 0;
    virtual bool fight_visit(const std::shared_ptr<Bear> &other) = 0;
    virtual bool fight_visit(const std::shared_ptr<Werewolf> &other) = 0;

    virtual std::ostream& print(std::ostream &os) const;

    virtual void save(std::ostream &os) const;

    friend std::ostream &operator<<(std::ostream &os, const NPC &npc);

    int get_x() const;
    int get_y() const;

    static bool is_attacker_defender(NpcType attacker_type, NpcType defender_type);
};

#endif