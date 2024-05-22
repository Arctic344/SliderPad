#pragma once
#include <Arduino.h>


/**
 * @brief The base class for a node in a data structure.
 * 
 * The `Node` class provides a base implementation for a node in a data structure.
 * It contains a virtual function `update_nodeValue()` which can be overridden by derived classes.
 */
class Node {
public:
    /**
     * @brief Updates the value of the node.
     * 
     * This function is virtual and can be overridden by derived classes to update the value of the node.
     */
    virtual void update_nodeValue() {
        return;
    }
};