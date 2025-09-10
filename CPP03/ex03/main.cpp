#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main()
{
    std::cout << "\n=== Testing Construction/Destruction Chaining ===" << std::endl;
    {
        std::cout << "\n--- Creating DiamondTrap with name ---" << std::endl;
        DiamondTrap diamond1("DI4MOND");
        
        std::cout << "\n--- Creating DiamondTrap with default constructor ---" << std::endl;
        DiamondTrap diamond2;
    }
    std::cout << "\n--- Objects go out of scope (destruction in reverse order) ---" << std::endl;

    std::cout << "\n=== Testing Copy Constructors ===" << std::endl;
    {
        DiamondTrap original("Original");
        std::cout << "\n--- Copy constructor ---" << std::endl;
        DiamondTrap copy(original);
        
        std::cout << "\n--- Copy assignment operator ---" << std::endl;
        DiamondTrap assigned;
        assigned = original;
    }

    std::cout << "\n=== Testing DiamondTrap Specific Values ===" << std::endl;
    {
        DiamondTrap diamond("Hybrid");
        std::cout << "\nDiamondTrap stats:" << std::endl;
        std::cout << "Name: " << diamond.getName() << std::endl;
        std::cout << "Hit Points: " << diamond.getHitPoints() << " (should be 100 from FragTrap)" << std::endl;
        std::cout << "Energy Points: " << diamond.getEnergyPoints() << " (should be 50 from ScavTrap)" << std::endl;
        std::cout << "Attack Damage: " << diamond.getAttackDamage() << " (should be 30 from FragTrap)" << std::endl;
    }

    std::cout << "\n=== Testing WhoAmI Special Ability ===" << std::endl;
    {
        DiamondTrap identity("Crystal");
        identity.whoAmI();
        
        std::cout << "\n--- Testing whoAmI when dead ---" << std::endl;
        identity.takeDamage(100); // Kill the DiamondTrap
        identity.whoAmI();
    }

    std::cout << "\n=== Testing Attack (Should use ScavTrap's) ===" << std::endl;
    {
        DiamondTrap attacker("Striker");
        ScavTrap scav("Guardian");
        
        std::cout << "\n--- DiamondTrap attack (using ScavTrap's attack) ---" << std::endl;
        attacker.attack("enemy");
        
        std::cout << "\n--- ScavTrap attack for comparison ---" << std::endl;
        scav.attack("enemy");
    }

    std::cout << "\n=== Testing All Inherited Abilities ===" << std::endl;
    {
        DiamondTrap superBot("UltraBot");
        
        std::cout << "\n--- Testing inherited ScavTrap ability ---" << std::endl;
        superBot.guardGate();
        
        std::cout << "\n--- Testing inherited FragTrap ability ---" << std::endl;
        superBot.highFivesGuys();
        
        std::cout << "\n--- Testing DiamondTrap's own ability ---" << std::endl;
        superBot.whoAmI();
    }

    std::cout << "\n=== Testing Combat Scenario ===" << std::endl;
    {
        DiamondTrap warrior("Warrior");
        DiamondTrap defender("Defender");
        
        std::cout << "\nInitial state:" << std::endl;
        std::cout << "Warrior - HP: " << warrior.getHitPoints() 
                  << ", Energy: " << warrior.getEnergyPoints() << std::endl;
        std::cout << "Defender - HP: " << defender.getHitPoints() 
                  << ", Energy: " << defender.getEnergyPoints() << std::endl;
        
        std::cout << "\n--- Combat sequence ---" << std::endl;
        warrior.attack("Defender");
        defender.takeDamage(20); // ScavTrap's attack damage
        
        defender.attack("Warrior");
        warrior.takeDamage(20);
        
        warrior.beRepaired(10);
        warrior.whoAmI();
        warrior.guardGate();
        defender.highFivesGuys();
        
        std::cout << "\nFinal state:" << std::endl;
        std::cout << "Warrior - HP: " << warrior.getHitPoints() 
                  << ", Energy: " << warrior.getEnergyPoints() << std::endl;
        std::cout << "Defender - HP: " << defender.getHitPoints() 
                  << ", Energy: " << defender.getEnergyPoints() << std::endl;
    }

    std::cout << "\n=== Testing Energy Depletion ===" << std::endl;
    {
        DiamondTrap energetic("PowerCell");
        std::cout << "Initial energy: " << energetic.getEnergyPoints() << std::endl;
        
        // DiamondTrap has 50 energy points (from ScavTrap)
        std::cout << "\n--- Using energy for actions ---" << std::endl;
        for (int i = 0; i < 51; i++)
        {
            if (i == 49)
                std::cout << "\n--- Last action with energy ---" << std::endl;
            else if (i == 50)
                std::cout << "\n--- Trying to act without energy ---" << std::endl;
            
            if (i >= 49)  // Only print the last two attempts
            {
                if (i % 3 == 0)
                    energetic.attack("target");
                else if (i % 3 == 1)
                    energetic.beRepaired(5);
                else
                    energetic.whoAmI();
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

    std::cout << "\n=== Testing Complete Hierarchy ===" << std::endl;
    {
        std::cout << "\n--- Creating one of each type ---" << std::endl;
        ClapTrap clap("Clappy");
        ScavTrap scav("Scavvy");
        FragTrap frag("Fraggy");
        DiamondTrap diamond("Diamondy");
        
        std::cout << "\n--- Stats comparison ---" << std::endl;
        std::cout << "ClapTrap  - HP: " << clap.getHitPoints() 
                  << ", EP: " << clap.getEnergyPoints() 
                  << ", AD: " << clap.getAttackDamage() << std::endl;
        std::cout << "ScavTrap  - HP: " << scav.getHitPoints() 
                  << ", EP: " << scav.getEnergyPoints() 
                  << ", AD: " << scav.getAttackDamage() << std::endl;
        std::cout << "FragTrap  - HP: " << frag.getHitPoints() 
                  << ", EP: " << frag.getEnergyPoints() 
                  << ", AD: " << frag.getAttackDamage() << std::endl;
        std::cout << "DiamondTrap - HP: " << diamond.getHitPoints() 
                  << ", EP: " << diamond.getEnergyPoints() 
                  << ", AD: " << diamond.getAttackDamage() << std::endl;
    }

    std::cout << "\n=== Program Ending ===" << std::endl;
    return 0;
}