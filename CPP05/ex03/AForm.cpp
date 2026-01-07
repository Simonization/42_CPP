#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("unnamed"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
	std::cout << "AForm default constructor called" << std::endl;
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	std::cout << "AForm parameterized constructor called" << std::endl;
	if (gradeToSign < HIGHEST_GRADE || gradeToExecute < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (gradeToSign > LOWEST_GRADE || gradeToExecute > LOWEST_GRADE)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
	: _name(other._name), _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
	std::cout << "AForm copy constructor called" << std::endl;
}

AForm& AForm::operator=(const AForm& other)
{
	std::cout << "AForm assignment operator called" << std::endl;
	if (this != &other)
		_isSigned = other._isSigned;
	return *this;
}

AForm::~AForm()
{
	std::cout << "AForm destructor called" << std::endl;
}

const std::string& AForm::getName() const
{
	return _name;
}

bool AForm::getIsSigned() const
{
	return _isSigned;
}

int AForm::getGradeToSign() const
{
	return _gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return _gradeToExecute;
}

void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (_isSigned)
		throw FormAlreadySignedException();
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

void AForm::execute(Bureaucrat const& executor) const
{
	if (!_isSigned)
		throw FormNotSignedException();
	if (executor.getGrade() > _gradeToExecute)
		throw GradeTooLowException();
	executeAction();
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "Form grade is too high! (Maximum grade is 1)";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "Form grade is too low! (Minimum grade is 150)";
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return "Form is not signed!";
}

const char* AForm::FormAlreadySignedException::what() const throw()
{
	return "Form is already signed!";
}

std::ostream& operator<<(std::ostream& os, const AForm& f)
{
	os << "Form \"" << f.getName() << "\", signed: " << (f.getIsSigned() ? "yes" : "no")
	   << ", grade to sign: " << f.getGradeToSign()
	   << ", grade to execute: " << f.getGradeToExecute() << ".";
	return os;
}
