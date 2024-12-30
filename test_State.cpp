#include "State.h"
#include <cassert>
#include <iostream>

void testInitialization() {
    State state(5);

    for (int i = 0; i < 5; ++i) {
        assert(state.getLevel(i) == -1);  // Niveles inicializados en -1
        assert(state.getPointer(i) == 0);  // Punteros inicializados en 0
    }

    std::cout << "testInitialization passed.\n";
}

void testResetLevels() {
    State state(5);

    for (int i = 0; i < 5; ++i) {
        state.setLevel(i, i);
    }

    state.resetLevels();

    for (int i = 0; i < 5; ++i) {
        assert(state.getLevel(i) == -1);  // Niveles reseteados a -1
    }

    std::cout << "testResetLevels passed.\n";
}

void testResetPointers() {
    State state(5);

    for (int i = 0; i < 5; ++i) {
        state.incrementPointer(i);  // Incrementar puntero una vez
    }

    state.resetPointers();

    for (int i = 0; i < 5; ++i) {
        assert(state.getPointer(i) == 0);  // Punteros reseteados a 0
    }

    std::cout << "testResetPointers passed.\n";
}

void testSetAndGetLevel() {
    State state(5);

    for (int i = 0; i < 5; ++i) {
        state.setLevel(i, i * 2);
    }

    for (int i = 0; i < 5; ++i) {
        assert(state.getLevel(i) == i * 2);  // Verificar niveles correctamente asignados
    }

    std::cout << "testSetAndGetLevel passed.\n";
}

void testPointerOperations() {
    State state(5);

    for (int i = 0; i < 5; ++i) {
        assert(state.getPointer(i) == 0);  // Puntero inicial es 0
        state.incrementPointer(i);        // Incrementar puntero
        assert(state.getPointer(i) == 1); // Verificar incremento
    }

    std::cout << "testPointerOperations passed.\n";
}

int main() {
    testInitialization();
    testResetLevels();
    testResetPointers();
    testSetAndGetLevel();
    testPointerOperations();

    std::cout << "All State tests passed successfully.\n";
    return 0;
}
