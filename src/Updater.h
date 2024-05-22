
#pragma once
#include "Node.h"
#include "Adafruit_NeoPixel.h"


/**
 * @class Updater
 * @brief A class that can take many nodes and 1 strip and update all their values at once.
 */
class Updater {
private:
    Node** nodes;               ///< An array of Node pointers representing the nodes to be updated.
    int nodeCount;              ///< The number of nodes in the array.
    Adafruit_NeoPixel* strip;   ///< A pointer to the strip object.

public:
    /**
     * @brief Default constructor for the Updater class.
     * Initializes the nodes array and nodeCount to default values, and strip to nullptr.
     */
    Updater() {
        nodes = nullptr;
        nodeCount = 0;
        strip = nullptr;
    }

    /**
     * @brief Destructor for the Updater class.
     * Deletes the nodes array.
     */
    ~Updater() {
        delete[] nodes;
    }

    /**
     * @brief Adds a node to the array of nodes.
     * @param node A pointer to the Node object to be added.
     */
    void addNode(Node* node) {
        Node** newNodes = new Node*[nodeCount + 1];
        for (int i = 0; i < nodeCount; i++) {
            newNodes[i] = nodes[i];
        }
        newNodes[nodeCount] = node;
        delete[] nodes;
        nodes = newNodes;
        nodeCount++;
    }

    /**
     * @brief Sets the strip object.
     * @param strip A pointer to the Adafruit_NeoPixel object representing the strip.
     */
    void setStrip(Adafruit_NeoPixel* strip) {
        this->strip = strip;
    }

    /**
     * @brief Updates the values of all the nodes and pushes the strip buffer to display.
     */
    void update_Components() {
        for (int i = 0; i < nodeCount; i++) {
            nodes[i]->update_nodeValue();
        }
        if (strip != nullptr) {
            strip->show();
        }
    }
};