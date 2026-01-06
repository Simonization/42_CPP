#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

const Intern::FormType Intern::_formTypes[] = {
	{"shrubbery creation", &Intern::createShrubbery},
	{"robotomy request", &Intern::createRobotomy},
	{"presidential pardon", &Intern::createPresidential}
};

const int Intern::_numFormTypes = sizeof(Intern::_formTypes) / sizeof(Intern::_formTypes[0]);

Intern::Intern()
{
}

Intern::Intern(const Intern& src)
{
	(void)src;
}

Intern& Intern::operator=(const Intern& other)
{
	(void)other;
	return *this;
}

Intern::~Intern()
{
}

AForm* Intern::createShrubbery(const std::string& target)
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomy(const std::string& target)
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidential(const std::string& target)
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target)
{
	for (int i = 0; i < _numFormTypes; i++)
	{
		if (_formTypes[i].name == formName)
		{
			AForm* form = _formTypes[i].creator(target);
			std::cout << "Intern creates " << form->getName() << std::endl;
			return form;
		}
	}
	std::cout << "Error: Form \"" << formName << "\" does not exist" << std::endl;
	throw FormNotFoundException();
}

const char* Intern::FormNotFoundException::what() const throw()
{
	return "Form not found";
}
