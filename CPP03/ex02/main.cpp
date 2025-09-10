#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
    std::cout << "\n=== Testing Construction/Destruction Chaining ===" << std::endl;
    {
        std::cout << "\n--- Creating FragTrap with name ---" << std::endl;
        FragTrap frag1("FR4G-TP");
        
        std::cout << "\n--- Creating FragTrap with default constructor ---" << std::endl;
        FragTrap frag2;
    }
    std::cout << "\n--- Objects go out of scope (destruction in reverse order) ---" << std::endl;

    std::cout << "\n=== Testing Copy Constructors ===" << std::endl;
    {
        FragTrap original("Original");
        std::cout << "\n--- Copy constructor ---" << std::endl;
        FragTrap copy(original);
        
        std::cout << "\n--- Copy assignment operator ---" << std::endl;
        FragTrap assigned;
        assigned = original;
    }

    std::cout << "\n=== Testing FragTrap Specific Values ===" << std::endl;
    {
        FragTrap frag("Demolisher");
        std::cout << "\nFragTrap stats:" << std::endl;
        std::cout << "Name: " << frag.getName() << std::endl;
        std::cout << "Hit Points: " << frag.getHitPoints() << " (should be 100)" << std::endl;
        std::cout << "Energy Points: " << frag.getEnergyPoints() << " (should be 100)" << std::endl;
        std::cout << "Attack Damage: " << frag.getAttackDamage() << " (should be 30)" << std::endl;
    }

    std::cout << "\n=== Testing High Fives Special Ability ===" << std::endl;
    {
        FragTrap friendly("BuddyBot");
        friendly.highFivesGuys();
        
        std::cout << "\n--- Testing high fives when dead ---" << std::endl;
        friendly.takeDamage(100); // Kill the FragTrap
        friendly.highFivesGuys();
    }

    std::cout << "\n=== Comparing All Three Classes ===" << std::endl;
    {
        ClapTrap clap("Basic");
        ScavTrap scav("Guardian");
        FragTrap frag("Smasher");
        
        std::cout << "\n--- Stats Comparison ---" << std::endl;
        std::cout << "ClapTrap - HP: " << clap.getHitPoints() 
                  << ", Energy: " << clap.getEnergyPoints() 
                  << ", Attack: " << clap.getAttackDamage() << std::endl;
        std::cout << "ScavTrap - HP: " << scav.getHitPoints() 
                  << ", Energy: " << scav.getEnergyPoints() 
                  << ", Attack: " << scav.getAttackDamage() << std::endl;
        std::cout << "FragTrap - HP: " << frag.getHitPoints() 
                  << ", Energy: " << frag.getEnergyPoints() 
                  << ", Attack: " << frag.getAttackDamage() << std::endl;
        
        std::cout << "\n--- Special Abilities ---" << std::endl;
        scav.guardGate();
        frag.highFivesGuys();
    }

    std::cout << "\n=== Testing Combat Scenario ===" << std::endl;
    {
        FragTrap attacker("Heavy");
        FragTrap defender("Tank");
        
        std::cout << "\nInitial state:" << std::endl;
        std::cout << "Heavy - HP: " << attacker.getHitPoints() 
                  << ", Energy: " << attacker.getEnergyPoints() << std::endl;
        std::cout << "Tank - HP: " << defender.getHitPoints() 
                  << ", Energy: " << defender.getEnergyPoints() << std::endl;
        
        std::cout << "\n--- Combat sequence ---" << std::endl;
        attacker.attack("Tank");
        defender.takeDamage(30);
        
        defender.attack("Heavy");
        attacker.takeDamage(30);
        
        defender.beRepaired(15);
        defender.highFivesGuys();
        
        std::cout << "\nFinal state:" << std::endl;
        std::cout << "Heavy - HP: " << attacker.getHitPoints() 
                  << ", Energy: " << attacker.getEnergyPoints() << std::endl;
        std::cout << "Tank - HP: " << defender.getHitPoints() 
                  << ", Energy: " << defender.getEnergyPoints() << std::endl;
    }

    std::cout << "\n=== Testing Energy Depletion ===" << std::endl;
    {
        FragTrap energetic("Energizer");
        std::cout << "Initial energy: " << energetic.getEnergyPoints() << std::endl;
        
        // FragTrap has 100 energy points
        std::cout << "\n--- Using energy for attacks and repairs ---" << std::endl;
        for (int i = 0; i < 101; i++)
        {
            if (i == 99)
                std::cout << "\n--- Last action with energy ---" << std::endl;
            else if (i == 100)
                std::cout << "\n--- Trying to act without energy ---" << std::endl;
            
            if (i >= 99)  // Only print the last two attempts
            {
                if (i % 2 == 0)
                    energetic.attack("target");
                else
                    energetic.beRepaired(5);
            }
            else
            {
                // Silent actions to save output
                if (i % 2 == 0)
                    energetic.attack("target");
                else
                    energetic.beRepaired(5);
            }
        }
        
        std::cout << "Final energy: " << energetic.getEnergyPoints() << std::endl;
    }

    std::cout << "\n=== Testing Multiple Kills ===" << std::endl;
    {
        FragTrap immortal("Phoenix");
        
        std::cout << "Starting HP: " << immortal.getHitPoints() << std::endl;
        
        std::cout << "\n--- First death ---" << std::endl;
        immortal.takeDamage(150);  // Overkill
        
        std::cout << "\n--- Trying to act while dead ---" << std::endl;
        immortal.attack("ghost");
        immortal.beRepaired(50);
        immortal.highFivesGuys();
        
        std::cout << "\n--- Taking more damage while dead ---" << std::endl;
        immortal.takeDamage(50);
    }

    std::cout << "\n=== Program Ending ===" << std::endl;
    return 0;
}