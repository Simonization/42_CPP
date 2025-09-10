#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
    std::cout << "\n=== Testing Construction/Destruction Chaining ===" << std::endl;
    {
        std::cout << "\n--- Creating ScavTrap with name ---" << std::endl;
        ScavTrap scav1("SC4V-TP");
        
        std::cout << "\n--- Creating ScavTrap with default constructor ---" << std::endl;
        ScavTrap scav2;
    }
    std::cout << "\n--- Objects go out of scope (destruction in reverse order) ---" << std::endl;

    std::cout << "\n=== Testing Copy Constructors ===" << std::endl;
    {
        ScavTrap original("Original");
        std::cout << "\n--- Copy constructor ---" << std::endl;
        ScavTrap copy(original);
        
        std::cout << "\n--- Copy assignment operator ---" << std::endl;
        ScavTrap assigned;
        assigned = original;
    }

    std::cout << "\n=== Testing ScavTrap Specific Values ===" << std::endl;
    {
        ScavTrap scav("Guardian");
        std::cout << "\nScavTrap stats:" << std::endl;
        std::cout << "Name: " << scav.getName() << std::endl;
        std::cout << "Hit Points: " << scav.getHitPoints() << " (should be 100)" << std::endl;
        std::cout << "Energy Points: " << scav.getEnergyPoints() << " (should be 50)" << std::endl;
        std::cout << "Attack Damage: " << scav.getAttackDamage() << " (should be 20)" << std::endl;
    }

    std::cout << "\n=== Testing ScavTrap Attack (Different Message) ===" << std::endl;
    {
        ScavTrap scav("Warrior");
        ClapTrap clap("Basic");
        
        std::cout << "\n--- ScavTrap attack ---" << std::endl;
        scav.attack("enemy");
        
        std::cout << "\n--- ClapTrap attack (for comparison) ---" << std::endl;
        clap.attack("enemy");
    }

    std::cout << "\n=== Testing Guard Gate Special Ability ===" << std::endl;
    {
        ScavTrap guardian("Gatekeeper");
        guardian.guardGate();
        
        std::cout << "\n--- Testing guard gate when dead ---" << std::endl;
        guardian.takeDamage(100); // Kill the ScavTrap
        guardian.guardGate();
    }

    std::cout << "\n=== Testing Combat Scenario ===" << std::endl;
    {
        ScavTrap attacker("Attacker");
        ScavTrap defender("Defender");
        
        std::cout << "\nInitial state:" << std::endl;
        std::cout << "Attacker - HP: " << attacker.getHitPoints() 
                  << ", Energy: " << attacker.getEnergyPoints() << std::endl;
        std::cout << "Defender - HP: " << defender.getHitPoints() 
                  << ", Energy: " << defender.getEnergyPoints() << std::endl;
        
        std::cout << "\n--- Combat sequence ---" << std::endl;
        attacker.attack("Defender");
        defender.takeDamage(20);
        
        defender.attack("Attacker");
        attacker.takeDamage(20);
        
        defender.beRepaired(10);
        defender.guardGate();
        
        std::cout << "\nFinal state:" << std::endl;
        std::cout << "Attacker - HP: " << attacker.getHitPoints() 
                  << ", Energy: " << attacker.getEnergyPoints() << std::endl;
        std::cout << "Defender - HP: " << defender.getHitPoints() 
                  << ", Energy: " << defender.getEnergyPoints() << std::endl;
    }

    std::cout << "\n=== Testing Energy Depletion ===" << std::endl;
    {
        ScavTrap tired("Tired");
        std::cout << "Initial energy: " << tired.getEnergyPoints() << std::endl;
        
        // Deplete all energy (50 attacks)
        for (int i = 0; i < 51; i++)
        {
            if (i == 49)
                std::cout << "\n--- Last attack with energy ---" << std::endl;
            else if (i == 50)
                std::cout << "\n--- Trying to attack without energy ---" << std::endl;
            
            if (i >= 49)  // Only print the last two attempts
                tired.attack("target");
            else
                tired.attack("target");  // Silent attacks to save output
        }
        
        std::cout << "Final energy: " << tired.getEnergyPoints() << std::endl;
        
        std::cout << "\n--- Trying to repair without energy ---" << std::endl;
        tired.beRepaired(10);
    }

    std::cout << "\n=== Program Ending ===" << std::endl;
    return 0;
}