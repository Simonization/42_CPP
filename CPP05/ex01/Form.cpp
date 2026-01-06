#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("unnamed"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
    std::cout << "Form default constructor called" << std::endl;
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
    std::cout << "Form parameterized constructor called" << std::endl;
    if (gradeToSign < HIGHEST_GRADE || gradeToExecute < HIGHEST_GRADE)
        throw GradeTooHighException();
    if (gradeToSign > LOWEST_GRADE || gradeToExecute > LOWEST_GRADE)
        throw GradeTooLowException();
}

Form::Form(const Form& other)
    : _name(other._name), _isSigned(other._isSigned),
      _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
    std::cout << "Form copy constructor called" << std::endl;
}

Form& Form::operator=(const Form& other)
{
    std::cout << "Form assignment operator called" << std::endl;
    if (this != &other)
        _isSigned = other._isSigned;
    return *this;
}

Form::~Form()
{
    std::cout << "Form destructor called" << std::endl;
}

const std::string& Form::getName() const
{
    return _name;
}

bool Form::getIsSigned() const
{
    return _isSigned;
}

int Form::getGradeToSign() const
{
    return _gradeToSign;
}

int Form::getGradeToExecute() const
{
    return _gradeToExecute;
}

void Form::beSigned(const Bureaucrat& bureaucrat)
{
    if (_isSigned)
        throw FormAlreadySignedException();
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
    return "Form grade is too high! (Maximum grade is 1)";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Form grade is too low! (Minimum grade is 150)";
}

const char* Form::FormAlreadySignedException::what() const throw()
{
    return "Form is already signed!";
}

std::ostream& operator<<(std::ostream& os, const Form& f)
{
    os << "Form \"" << f.getName() << "\", signed: " << (f.getIsSigned() ? "yes" : "no")
       << ", grade to sign: " << f.getGradeToSign()
       << ", grade to execute: " << f.getGradeToExecute() << ".";
    return os;
}
