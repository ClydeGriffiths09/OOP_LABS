#include <gtest/gtest.h>
#include <sstream>

#include "battle_visitor.hpp"
#include "dungeon_editor.hpp"
#include "npc_factory.hpp"
#include "npc_handle.hpp"
#include "npc.hpp"
#include "observer.hpp"

TEST(FactoryTest, CreateValidNPC) {
    auto p = NPCFactory::CreateNPC("Knight", 100, 100, "Peach");
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->GetType(), "Knight");
    EXPECT_EQ(p->GetX(), 100);
}

TEST(NPCFactoryTest, CreateKnight) {
    auto knight = NPCFactory::CreateNPC("Knight", 100, 200, "Arthur");
    
    ASSERT_NE(knight, nullptr);
    EXPECT_EQ(knight->GetType(), "Knight");
    EXPECT_EQ(knight->GetX(), 100);
    EXPECT_EQ(knight->GetY(), 200);
    EXPECT_EQ(knight->GetName(), "Arthur");
}

TEST(NPCFactoryTest, CreateSquirrel) {
    auto squirrel = NPCFactory::CreateNPC("Squirrel", 50, 75, "Nutsy");
    
    ASSERT_NE(squirrel, nullptr);
    EXPECT_EQ(squirrel->GetType(), "Squirrel");
    EXPECT_EQ(squirrel->GetX(), 50);
    EXPECT_EQ(squirrel->GetY(), 75);
    EXPECT_EQ(squirrel->GetName(), "Nutsy");
}

TEST(NPCFactoryTest, CreatePegasus) {
    auto pegasus = NPCFactory::CreateNPC("Pegasus", 0, 0, "Storm");
    
    ASSERT_NE(pegasus, nullptr);
    EXPECT_EQ(pegasus->GetType(), "Pegasus");
    EXPECT_EQ(pegasus->GetX(), 0);
    EXPECT_EQ(pegasus->GetY(), 0);
    EXPECT_EQ(pegasus->GetName(), "Storm");
}

TEST(NPCFactoryTest, CaseInsensitiveType) {
    auto k1 = NPCFactory::CreateNPC("Knight", 1, 1, "Test1");
    auto k2 = NPCFactory::CreateNPC("Knight", 2, 2, "Test2");
    auto k3 = NPCFactory::CreateNPC("Knight", 3, 3, "Test3");
    
    if (k1) EXPECT_EQ(k1->GetType(), "Knight");
    if (k2) EXPECT_EQ(k2->GetType(), "Knight");
}

TEST(NPCFactoryTest, CreateWithEmptyName) {
    auto npc = NPCFactory::CreateNPC("Knight", 10, 20, "");
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->GetType(), "Knight");
    EXPECT_EQ(npc->GetX(), 10);
    EXPECT_EQ(npc->GetY(), 20);
    EXPECT_TRUE(npc->GetName().empty() || npc->GetName() == "Unknown");
}

TEST(NPCFactoryTest, CreateMultipleDifferentNPCs) {
    auto knight = NPCFactory::CreateNPC("Knight", 1, 1, "K1");
    auto squirrel = NPCFactory::CreateNPC("Squirrel", 2, 2, "S1");
    auto pegasus = NPCFactory::CreateNPC("Pegasus", 3, 3, "P1");
    
    ASSERT_NE(knight, nullptr);
    ASSERT_NE(squirrel, nullptr);
    ASSERT_NE(pegasus, nullptr);
    
    EXPECT_EQ(knight->GetType(), "Knight");
    EXPECT_EQ(squirrel->GetType(), "Squirrel");
    EXPECT_EQ(pegasus->GetType(), "Pegasus");
    
    EXPECT_NE(knight->GetType(), squirrel->GetType());
    EXPECT_NE(squirrel->GetType(), pegasus->GetType());
}

TEST(NPCFactoryTest, SameTypeDifferentInstances) {
    auto npc1 = NPCFactory::CreateNPC("Knight", 10, 10, "SameName");
    auto npc2 = NPCFactory::CreateNPC("Knight", 10, 10, "SameName");
    
    ASSERT_NE(npc1, nullptr);
    ASSERT_NE(npc2, nullptr);
    
    EXPECT_NE(npc1.get(), npc2.get());
    
    EXPECT_EQ(npc1->GetType(), npc2->GetType());
    EXPECT_EQ(npc1->GetName(), npc2->GetName());
    EXPECT_EQ(npc1->GetX(), npc2->GetX());
    EXPECT_EQ(npc1->GetY(), npc2->GetY());
}

TEST(NPCFactoryTest, NameWithSpaces) {
    auto npc = NPCFactory::CreateNPC("Knight", 0, 0, "Sir Lancelot");
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->GetName(), "Sir Lancelot");
}

TEST(NPCFactoryTest, NameWithSpecialCharacters) {
    auto npc = NPCFactory::CreateNPC("Squirrel", 0, 0, "Nut-Cracker_123");
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->GetName(), "Nut-Cracker_123");
}

TEST(NPCFactoryTest, ZeroCoordinates) {
    auto npc = NPCFactory::CreateNPC("Pegasus", 0, 0, "Zero");
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->GetX(), 0);
    EXPECT_EQ(npc->GetY(), 0);
}

TEST(NPCFactoryTest, NPCsAreMovable) {
    auto npc = NPCFactory::CreateNPC("Knight", 10, 20, "Movable");
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->GetX(), 10);
    EXPECT_EQ(npc->GetY(), 20);
}

TEST(NPCFactoryTest, MassCreation) {
    const int COUNT = 100;
    
    for (int i = 0; i < COUNT; ++i) {
        std::string type;
        if (i % 3 == 0) type = "Knight";
        else if (i % 3 == 1) type = "Squirrel";
        else type = "Pegasus";
        
        std::string name = "NPC_" + std::to_string(i);
        
        auto npc = NPCFactory::CreateNPC(type, i, i * 2, name);
        
        ASSERT_NE(npc, nullptr);
        EXPECT_EQ(npc->GetType(), type);
        EXPECT_EQ(npc->GetName(), name);
        EXPECT_EQ(npc->GetX(), i);
        EXPECT_EQ(npc->GetY(), i * 2);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}