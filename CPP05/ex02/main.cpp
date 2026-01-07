#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(NULL));

	std::cout << "\n===== TEST 1: ShrubberyCreationForm - Success =====" << std::endl;
	try
	{
		Bureaucrat gardener("Gardener", 130);
		ShrubberyCreationForm shrub("home");

		std::cout << gardener << std::endl;
		std::cout << shrub << std::endl;

		gardener.signForm(shrub);
		std::cout << shrub << std::endl;

		gardener.executeForm(shrub);
		std::cout << "Check for home_shrubbery file!" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 2: ShrubberyCreationForm - Grade Too Low to Sign =====" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 150);
		ShrubberyCreationForm shrub("garden");

		std::cout << intern << std::endl;
		std::cout << shrub << std::endl;

		intern.signForm(shrub);
		std::cout << shrub << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 3: ShrubberyCreationForm - Grade Too Low to Execute =====" << std::endl;
	try
	{
		Bureaucrat signer("Signer", 140);
		Bureaucrat executor("Executor", 145);
		ShrubberyCreationForm shrub("office");

		signer.signForm(shrub);
		std::cout << shrub << std::endl;

		executor.executeForm(shrub);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 4: Execute Unsigned Form =====" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("park");

		std::cout << shrub << std::endl;
		boss.executeForm(shrub);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 5: RobotomyRequestForm - Success (50% chance) =====" << std::endl;
	try
	{
		Bureaucrat scientist("Scientist", 40);
		RobotomyRequestForm robotomy("Bender");

		std::cout << scientist << std::endl;
		std::cout << robotomy << std::endl;

		scientist.signForm(robotomy);
		std::cout << robotomy << std::endl;

		scientist.executeForm(robotomy);
		scientist.executeForm(robotomy);
		scientist.executeForm(robotomy);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 6: RobotomyRequestForm - Grade Too Low =====" << std::endl;
	try
	{
		Bureaucrat technician("Technician", 50);
		RobotomyRequestForm robotomy("C-3PO");

		std::cout << technician << std::endl;
		std::cout << robotomy << std::endl;

		technician.signForm(robotomy);
		technician.executeForm(robotomy);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 7: PresidentialPardonForm - Success =====" << std::endl;
	try
	{
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardon("Arthur Dent");

		std::cout << president << std::endl;
		std::cout << pardon << std::endl;

		president.signForm(pardon);
		std::cout << pardon << std::endl;

		president.executeForm(pardon);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 8: PresidentialPardonForm - Grade Too Low =====" << std::endl;
	try
	{
		Bureaucrat clerk("Clerk", 30);
		PresidentialPardonForm pardon("Ford Prefect");

		std::cout << clerk << std::endl;
		std::cout << pardon << std::endl;

		clerk.signForm(pardon);
		clerk.executeForm(pardon);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 9: PresidentialPardonForm - Can Sign But Not Execute =====" << std::endl;
	try
	{
		Bureaucrat minister("Minister", 10);
		PresidentialPardonForm pardon("Zaphod");

		std::cout << minister << std::endl;
		std::cout << pardon << std::endl;

		minister.signForm(pardon);
		std::cout << pardon << std::endl;

		minister.executeForm(pardon);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 10: All Forms with Same Bureaucrat =====" << std::endl;
	try
	{
		Bureaucrat supreme("Supreme Leader", 1);

		ShrubberyCreationForm shrub("palace");
		RobotomyRequestForm robot("Marvin");
		PresidentialPardonForm pardon("Trillian");

		std::cout << supreme << std::endl;

		supreme.signForm(shrub);
		supreme.signForm(robot);
		supreme.signForm(pardon);

		std::cout << "\n--- Executing all forms ---" << std::endl;

		supreme.executeForm(shrub);
		supreme.executeForm(robot);
		supreme.executeForm(pardon);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 11: Form Copy and Assignment =====" << std::endl;
	try
	{
		ShrubberyCreationForm original("backyard");
		Bureaucrat signer("Signer", 100);

		signer.signForm(original);
		std::cout << "Original: " << original << std::endl;

		ShrubberyCreationForm copy(original);
		std::cout << "Copy: " << copy << std::endl;

		ShrubberyCreationForm assigned("temp");
		std::cout << "Before assignment: " << assigned << std::endl;

		assigned = original;
		std::cout << "After assignment: " << assigned << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 12: Direct execute() Call with Exception =====" << std::endl;
	try
	{
		Bureaucrat lowRank("LowRank", 100);
		PresidentialPardonForm pardon("Someone");

		Bureaucrat highRank("HighRank", 1);
		highRank.signForm(pardon);

		pardon.execute(lowRank);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 13: Direct execute() on Unsigned Form =====" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 1);
		RobotomyRequestForm robot("Target");

		robot.execute(boss);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
