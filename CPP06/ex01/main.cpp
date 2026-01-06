/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main(void)
{
	std::cout << "=== Serialization Test ===" << std::endl;
	std::cout << std::endl;

	// Create and initialize Data object
	Data data;
	data.id = 42;
	data.name = "test_data";
	data.value = 3.14159;

	std::cout << "Original Data object:" << std::endl;
	std::cout << "  Address: " << &data << std::endl;
	std::cout << "  id:      " << data.id << std::endl;
	std::cout << "  name:    " << data.name << std::endl;
	std::cout << "  value:   " << data.value << std::endl;
	std::cout << std::endl;

	// Serialize: convert pointer to uintptr_t
	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "Serialized value (uintptr_t): " << raw << std::endl;
	std::cout << std::endl;

	// Deserialize: convert uintptr_t back to pointer
	Data* ptr = Serializer::deserialize(raw);

	std::cout << "Deserialized pointer:" << std::endl;
	std::cout << "  Address: " << ptr << std::endl;
	std::cout << "  id:      " << ptr->id << std::endl;
	std::cout << "  name:    " << ptr->name << std::endl;
	std::cout << "  value:   " << ptr->value << std::endl;
	std::cout << std::endl;

	// Verify the pointers are equal
	std::cout << "=== Verification ===" << std::endl;
	if (ptr == &data)
		std::cout << "SUCCESS: Deserialized pointer equals original pointer!" << std::endl;
	else
		std::cout << "FAILURE: Pointers do not match!" << std::endl;

	// Verify data is accessible and correct through deserialized pointer
	if (ptr->id == 42 && ptr->name == "test_data" && ptr->value == 3.14159)
		std::cout << "SUCCESS: Data members are correct through deserialized pointer!" << std::endl;
	else
		std::cout << "FAILURE: Data members do not match!" << std::endl;

	std::cout << std::endl;

	// Additional test: modify through deserialized pointer
	std::cout << "=== Modification Test ===" << std::endl;
	ptr->id = 100;
	ptr->name = "modified";
	std::cout << "Modified data through deserialized pointer:" << std::endl;
	std::cout << "  Original data.id:   " << data.id << std::endl;
	std::cout << "  Original data.name: " << data.name << std::endl;

	if (data.id == 100 && data.name == "modified")
		std::cout << "SUCCESS: Modification through deserialized pointer affects original!" << std::endl;
	else
		std::cout << "FAILURE: Modification did not affect original!" << std::endl;

	return 0;
}
