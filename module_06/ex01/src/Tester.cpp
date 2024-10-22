/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Tester.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:34:02 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 14:50:59 by lvan-gef      ########   odam.nl         */
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
    static_assert(!std::is_destructible<Serializer>::value,
                  "Serializer should not be destructible");

    // Test 2: Verify serialization and deserialization
    Data original = {"John Doe", 30, nullptr};
    Data *originalPtr = &original;

    uintptr_t serialized = Serializer::serialize(originalPtr);
    Data *deserialized = Serializer::deserialize(serialized);

    assert(deserialized == originalPtr);
    assert(deserialized->name == "John Doe");
    assert(deserialized->age == 30);
    assert(deserialized->next == nullptr);

    // Test 3: Verify with a chain of Data structs
    Data second = {"Jane Doe", 28, nullptr};
    original.next = &second;

    uintptr_t serializedChain = Serializer::serialize(originalPtr);
    Data *deserializedChain = Serializer::deserialize(serializedChain);

    assert(deserializedChain == originalPtr);
    assert(deserializedChain->name == "John Doe");
    assert(deserializedChain->age == 30);
    assert(deserializedChain->next == &second);
    assert(deserializedChain->next->name == "Jane Doe");
    assert(deserializedChain->next->age == 28);
    assert(deserializedChain->next->next == nullptr);

    // Test 4: Convert from nullptr (Should throw)
    Data *nullPtr = nullptr;
    try {
        Serializer::serialize(nullPtr);
        assert(false && "serialize: should throw on nullptr");
    } catch (const std::invalid_argument &e) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "serialize: throw wrong type of exception");
    }

    // Test 5: convert from null addr (Should throw)
    uintptr_t null_addr = 0;
    try {
        Serializer::deserialize(null_addr); // Points to null
        assert(false && "deserialize: should throw on 0");
    } catch (const std::invalid_argument &e) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "deserialize: throw wrong type of exception");
    }

    std::cout << "All tests passed successfully!" << '\n';
}
