#ifndef INTERN_HPP
# define INTERN_HPP

#include <string>
#include "AForm.hpp"

class Intern
{
private:
	typedef AForm* (*FormCreator)(const std::string& target);

	struct FormType
	{
		std::string name;
		FormCreator creator;
	};

	static AForm* createShrubbery(const std::string& target);
	static AForm* createRobotomy(const std::string& target);
	static AForm* createPresidential(const std::string& target);

	static const FormType _formTypes[];
	static const int _numFormTypes;

public:
	Intern();
	Intern(const Intern& src);
	Intern& operator=(const Intern& other);
	~Intern();

	AForm* makeForm(const std::string& formName, const std::string& target);

	class FormNotFoundException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

#endif
