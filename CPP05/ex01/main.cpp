#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
    std::cout << "\n===== TEST 1: Valid Form Creation =====" << std::endl;
    try
    {
        Form taxForm("Tax Declaration", 50, 25);
        std::cout << taxForm << std::endl;

        Form permit("Building Permit", 1, 1);
        std::cout << permit << std::endl;

        Form request("Simple Request", 150, 150);
        std::cout << request << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 2: Invalid Form (Grade Too High) =====" << std::endl;
    try
    {
        Form invalid("Invalid Form", 0, 50);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 3: Invalid Form (Grade Too Low) =====" << std::endl;
    try
    {
        Form invalid("Invalid Form", 50, 151);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 4: Successful Form Signing =====" << std::endl;
    try
    {
        Bureaucrat boss("Boss", 1);
        Form contract("Employment Contract", 50, 25);

        std::cout << boss << std::endl;
        std::cout << contract << std::endl;

        boss.signForm(contract);
        std::cout << contract << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 5: Failed Form Signing (Grade Too Low) =====" << std::endl;
    try
    {
        Bureaucrat intern("Intern", 150);
        Form topSecret("Top Secret Document", 1, 1);

        std::cout << intern << std::endl;
        std::cout << topSecret << std::endl;

        intern.signForm(topSecret);
        std::cout << topSecret << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 6: Edge Case - Exact Grade Match =====" << std::endl;
    try
    {
        Bureaucrat clerk("Clerk", 50);
        Form permit("Permit", 50, 25);

        std::cout << clerk << std::endl;
        std::cout << permit << std::endl;

        clerk.signForm(permit);
        std::cout << permit << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 7: Edge Case - One Grade Too Low =====" << std::endl;
    try
    {
        Bureaucrat clerk("Clerk", 51);
        Form permit("Permit", 50, 25);

        std::cout << clerk << std::endl;
        std::cout << permit << std::endl;

        clerk.signForm(permit);
        std::cout << permit << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 8: Multiple Bureaucrats, One Form =====" << std::endl;
    try
    {
        Bureaucrat low("LowRank", 100);
        Bureaucrat mid("MidRank", 50);
        Bureaucrat high("HighRank", 10);
        Form report("Annual Report", 50, 30);

        std::cout << report << std::endl;

        low.signForm(report);
        std::cout << report << std::endl;

        mid.signForm(report);
        std::cout << report << std::endl;

        high.signForm(report);
        std::cout << report << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 9: Form Copy and Assignment =====" << std::endl;
    try
    {
        Form original("Original Form", 30, 20);
        std::cout << "Original: " << original << std::endl;

        Bureaucrat signer("Signer", 25);
        signer.signForm(original);
        std::cout << "After signing: " << original << std::endl;

        Form copy(original);
        std::cout << "Copy: " << copy << std::endl;

        Form assigned("Temp", 100, 100);
        std::cout << "Before assignment: " << assigned << std::endl;

        assigned = original;
        std::cout << "After assignment: " << assigned << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 10: Using beSigned Directly =====" << std::endl;
    try
    {
        Bureaucrat admin("Admin", 5);
        Form license("License Application", 10, 5);

        std::cout << license << std::endl;
        license.beSigned(admin);
        std::cout << "After beSigned: " << license << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n===== TEST 11: beSigned Throws Exception =====" << std::endl;
    try
    {
        Bureaucrat lowGrade("LowGrade", 100);
        Form highReq("High Requirement", 10, 5);

        std::cout << highReq << std::endl;
        highReq.beSigned(lowGrade);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
