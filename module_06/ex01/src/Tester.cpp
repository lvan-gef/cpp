/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Tester.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:34:02 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/14 20:34:06 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Tester.hpp"

void test_serializer() {
    // Test 1: Verify that Serializer cannot be instantiated
    static_assert(!std::is_default_constructible<Serializer>::value,
                  "Serializer should not be default constructible");
    static_assert(!std::is_copy_constructible<Serializer>::value,
                  "Serializer should not be copy constructible");
    static_assert(!std::is_move_constructible<Serializer>::value,
                  "Serializer should not be move constructible");
    static_assert(!std::is_copy_assignable<Serializer>::value,
                  "Serializer should not be copy assignable");
    static_assert(!std::is_move_assignable<Serializer>::value,
                  "Serializer should not be move assignable");

    // Test 2: Verify serialization and deserialization
    Data original = {"John Doe", 30, nullptr};
    Data *originalPtr = &original;

    // Serialize
    uintptr_t serialized = Serializer::serialize(originalPtr);

    // Deserialize
    Data *deserialized = Serializer::deserialize(serialized);

    // Check if the deserialized pointer is the same as the original
    assert(deserialized == originalPtr);
    assert(deserialized->name == "John Doe");
    assert(deserialized->age == 30);
    assert(deserialized->next == nullptr);

    // Test 3: Verify with nullptr
    Data *nullPtr = nullptr;
    uintptr_t serializedNull = Serializer::serialize(nullPtr);
    Data *deserializedNull = Serializer::deserialize(serializedNull);
    assert(deserializedNull == nullptr);

    // Test 4: Verify with a chain of Data structs
    Data second = {"Jane Doe", 28, nullptr};
    original.next = &second;

    uintptr_t serializedChain = Serializer::serialize(originalPtr);
    Data *deserializedChain = Serializer::deserialize(serializedChain);

    assert(deserializedChain == originalPtr);
    assert(deserializedChain->next == &second);
    assert(deserializedChain->next->name == "Jane Doe");
    assert(deserializedChain->next->age == 28);
    assert(deserializedChain->next->next == nullptr);

    std::cout << "All tests passed successfully!" << std::endl;
}
