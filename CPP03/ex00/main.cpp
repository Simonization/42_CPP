#include "ClapTrap.hpp"

int main()
{
    std::cout << "\n=== TEST 1: Constructor and Destructor ===" << std::endl;
    {
        ClapTrap clap1("Robot1");
        ClapTrap clap2;
    }

    std::cout << "\n=== TEST 2: Attack with 0 damage ===" << std::endl;
    {
        ClapTrap attacker("Attacker");
        attacker.attack("Target");
    }

    std::cout << "\n=== TEST 3: Take Damage ===" << std::endl;
    {
        ClapTrap victim("Victim");
        victim.takeDamage(3);
        victim.takeDamage(5);
        victim.takeDamage(5);
        victim.takeDamage(1);
    }

    std::cout << "\n=== TEST 4: Repair ===" << std::endl;
    {
        ClapTrap healer("Healer");
        healer.takeDamage(5);
        healer.beRepaired(3);
        healer.beRepaired(2);
    }

    std::cout << "\n=== TEST 5: Energy Points Depletion ===" << std::endl;
    {
        ClapTrap energyTest("EnergyDrain");
        
        for (int i = 0; i < 12; i++)
        {
            std::cout << "Action " << i + 1 << ": ";
            if (i % 2 == 0)
                energyTest.attack("Dummy");
            else
                energyTest.beRepaired(1);
        }
    }

    std::cout << "\n=== TEST 6: Copy Constructor and Assignment ===" << std::endl;
    {
        ClapTrap original("Original");
        original.takeDamage(3);
        
        ClapTrap copy(original);
        ClapTrap assigned("ToBeReplaced");
        assigned = original;
        
        copy.attack("Target1");
        assigned.attack("Target2");
    }

    std::cout << "\n=== TEST 7: No Actions When Destroyed ===" << std::endl;
    {
        ClapTrap destroyed("Destroyed");
        destroyed.takeDamage(10);
        destroyed.attack("Target");
        destroyed.beRepaired(5);
    }

    std::cout << "\n=== TEST 8: Combined Actions ===" << std::endl;
    {
        ClapTrap warrior("Warrior");
        
        warrior.attack("Enemy1");
        warrior.takeDamage(2);
        warrior.beRepaired(1);
        warrior.attack("Enemy2");
        warrior.takeDamage(3);
        warrior.beRepaired(2);
        
        for (int i = 0; i < 5; i++)
        {
            warrior.attack("Enemy3");
        }
    }

    std::cout << "\n=== End of Tests ===" << std::endl;
    
    return 0;
}
