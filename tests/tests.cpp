#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/outlow.h"
#include "../include/bear.h"
#include "../include/werewolf.h"
#include "../include/npc_factory.h"
#include "../include/text_observer.h"
#include "../include/npc_array_saver.h"
#include "../include/npc.h"
#include "../include/fight_func.h"


TEST(NPCFactoryTest, CreateOutlow) {
    NPC_Factory factory;
    auto npc = factory.createNPC(OutlowType, "Outlow1", 100, 200);
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->get_type(), OutlowType);
    EXPECT_EQ(npc->get_name(), "Outlow1");
    EXPECT_EQ(npc->get_x(), 100);
    EXPECT_EQ(npc->get_y(), 200);
}

TEST(NPCFactoryTest, CreateBear) {
    NPC_Factory factory;
    auto npc = factory.createNPC(BearType, "Bear1", 150, 250);
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->get_type(), BearType);
    EXPECT_EQ(npc->get_name(), "Bear1");
}

TEST(NPCFactoryTest, CreateWerewolf) {
    NPC_Factory factory;
    auto npc = factory.createNPC(WerewolfType, "Werewolf1", 300, 400);
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->get_type(), WerewolfType);
    EXPECT_EQ(npc->get_name(), "Werewolf1");
}

TEST(NPCFactoryTest, InvalidType) {
    NPC_Factory factory;
    auto npc = factory.createNPC(static_cast<NpcType>(99), "Invalid", 0, 0);
    EXPECT_EQ(npc, nullptr);
}


TEST(FightLogicTest, WerewolfVsOutlow) {
    auto werewolf = std::make_shared<Werewolf>("Werewolf1", 0, 0);
    auto outlow = std::make_shared<Outlow>("Outlow1", 0, 0);
    
    EXPECT_TRUE(outlow->accept(werewolf));
    EXPECT_TRUE(outlow->is_lose());
    EXPECT_FALSE(werewolf->is_lose());
}

TEST(FightLogicTest, OutlowVsBear) {
    auto outlow = std::make_shared<Outlow>("Outlow1", 0, 0);
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    
    EXPECT_TRUE(bear->accept(outlow));
    EXPECT_TRUE(bear->is_lose());
    EXPECT_FALSE(outlow->is_lose());
}

TEST(FightLogicTest, BearVsWerewolf) {
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    auto werewolf = std::make_shared<Werewolf>("Werewolf1", 0, 0);
    
    EXPECT_TRUE(werewolf->accept(bear));
    EXPECT_TRUE(werewolf->is_lose());
    EXPECT_FALSE(bear->is_lose());
}

TEST(FightLogicTest, SameTypeNoKill) {
    auto outlow1 = std::make_shared<Outlow>("Outlow1", 0, 0);
    auto outlow2 = std::make_shared<Outlow>("Outlow2", 0, 0);
    
    EXPECT_FALSE(outlow2->accept(outlow1));
    EXPECT_FALSE(outlow2->is_lose());
    EXPECT_FALSE(outlow1->is_lose());
}


TEST(DistanceTest, NPCsAreClose) {
    auto npc1 = std::make_shared<Outlow>("Outlow1", 0, 0);
    auto npc2 = std::make_shared<Bear>("Bear1", 5, 5);
    EXPECT_TRUE(npc1->is_close(npc2, 10));
}

TEST(DistanceTest, NPCsAreFar) {
    auto npc1 = std::make_shared<Outlow>("Outlow1", 0, 0);
    auto npc2 = std::make_shared<Bear>("Bear1", 100, 100);
    EXPECT_FALSE(npc1->is_close(npc2, 10));
}

TEST(DistanceTest, SamePosition) {
    auto npc1 = std::make_shared<Outlow>("Outlow1", 50, 50);
    auto npc2 = std::make_shared<Bear>("Bear1", 50, 50);
    EXPECT_TRUE(npc1->is_close(npc2, 1));
}


TEST(SerializationTest, SaveAndLoad) {
    set_t original_set;
    NPC_Factory factory;
    
    original_set.insert(factory.createNPC(OutlowType, "Outlow1", 100, 200));
    original_set.insert(factory.createNPC(BearType, "Bear1", 150, 250));
    original_set.insert(factory.createNPC(WerewolfType, "Werewolf1", 300, 400));

    save(original_set, "test_save.txt");

    auto loaded_set = load("test_save.txt");

    EXPECT_EQ(original_set.size(), loaded_set.size());

    std::ifstream file("test_save.txt");
    EXPECT_TRUE(file.good());
    file.close();
    
    std::remove("test_save.txt");
}

TEST(SerializationTest, LoadNonExistentFile) {
    auto loaded_set = load("non_existent_file.txt");
    EXPECT_TRUE(loaded_set.empty());
}


TEST(HelperTest, IsAttackerDefender) {
    EXPECT_TRUE(NPC::is_attacker_defender(WerewolfType, OutlowType));
    EXPECT_TRUE(NPC::is_attacker_defender(OutlowType, BearType));
    EXPECT_TRUE(NPC::is_attacker_defender(BearType, WerewolfType));
    
    EXPECT_FALSE(NPC::is_attacker_defender(OutlowType, WerewolfType));
    EXPECT_FALSE(NPC::is_attacker_defender(BearType, OutlowType));
    EXPECT_FALSE(NPC::is_attacker_defender(WerewolfType, BearType));
}


TEST(IntegrationTest, FullFightCycle) {
    NPC_Factory factory;
    set_t npc_set;
    
    npc_set.insert(factory.createNPC(WerewolfType, "Werewolf1", 0, 0));
    npc_set.insert(factory.createNPC(OutlowType, "Outlow1", 1, 1));
    npc_set.insert(factory.createNPC(BearType, "Bear1", 100, 100));
    
    size_t initial_size = npc_set.size();
    
    auto lose_list = fight(npc_set, 10);
    
    EXPECT_EQ(lose_list.size(), 1);
    EXPECT_EQ((*lose_list.begin())->get_type(), OutlowType);
    
    for (auto& d : lose_list) {
        npc_set.erase(d);
    }
    
    EXPECT_EQ(npc_set.size(), initial_size - 1);
}

TEST(IntegrationTest, PrintNPCSet) {
    NPC_Factory factory;
    set_t npc_set;
    
    npc_set.insert(factory.createNPC(OutlowType, "Outlow1", 100, 200));
    npc_set.insert(factory.createNPC(BearType, "Bear1", 150, 250));
    
    std::stringstream ss;
    ss << npc_set;
    
    EXPECT_FALSE(ss.str().empty());
    EXPECT_NE(ss.str().find("Outlow1"), std::string::npos);
    EXPECT_NE(ss.str().find("Bear1"), std::string::npos);
}


TEST(BoundaryTest, NPCAtFieldBoundaries) {
    auto npc = std::make_shared<Outlow>("Outlow1", 500, 500);
    EXPECT_EQ(npc->get_x(), 500);
    EXPECT_EQ(npc->get_y(), 500);
    
    auto npc2 = std::make_shared<Bear>("Bear1", 0, 0);
    EXPECT_EQ(npc2->get_x(), 0);
    EXPECT_EQ(npc2->get_y(), 0);
}

TEST(BoundaryTest, ZeroDistanceFight) {
    auto npc1 = std::make_shared<Werewolf>("Werewolf1", 0, 0);
    auto npc2 = std::make_shared<Outlow>("Outlow1", 0, 0);
    
    EXPECT_TRUE(npc1->is_close(npc2, 0));
}


TEST(NPCStateTest, InitialState) {
    auto npc = std::make_shared<Bear>("Bear1", 100, 200);
    EXPECT_FALSE(npc->is_lose());
    EXPECT_TRUE(npc->is_in_game());
}

TEST(NPCStateTest, SetLose) {
    auto npc = std::make_shared<Bear>("Bear1", 100, 200);
    npc->set_lose();
    
    EXPECT_TRUE(npc->is_lose());
    EXPECT_FALSE(npc->is_in_game());
}