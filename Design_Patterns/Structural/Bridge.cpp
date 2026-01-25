//Bridge design pattern example in C++
/* ****************************************************************************************
 * Bridge Design Pattern (Structural Pattern)
 *
 * Intent:
 * --------
 * The Bridge pattern decouples an abstraction from its implementation so that the two
 * can vary independently. It is used to separate a class's interface from its implementation,
 * allowing both to evolve separately without affecting each other.
 * Problem Solved:
 * ----------------
 * - Tight coupling between abstraction and implementation.
 * - Difficulty in extending both abstraction and implementation independently.
 * Solution:
 * ----------
 * - Define an abstraction interface and an implementation interface.
 * - Create concrete implementations of the implementation interface.
 * - Create refined abstractions that use the implementation interface.
 * Example Mapping in this program:
 * --------------------------------
 * - Abstraction         : Shape
 * - Refined Abstraction : Circle, Square
 * - Implementor        : DrawingAPI       */

#include <iostream>