#include "../include/tester.hpp"

void testIter() {
    try {
        testIntegerArray();
        testDoubleArray();
        testCharArray();
        testCStyleString();
        testNullptr();
        testZeroSize();
        testEmptyArray();
        testCustomType();
        testExceptionPropagation();
        testLargeArray();
        testMultipleFunctionTypes();

        testOversizedCString();
        testOversizedWithNullTerminator();
        // testOversizedIntArray();        // UB
        // testOversizedCharArray();       // UB
        // testOversizedCustomType();      // UB
    } catch (const std::exception &e) {
        std::cerr << "Unexpected exception in testIter: " << e.what()
                  << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception in testIter" << std::endl;
    }
}
