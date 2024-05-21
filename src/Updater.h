
#pragma once
#include "Node.h"


class Updater {
private:
    Node** nodes;
    int nodeCount;

public:
    Updater() {
        nodes = nullptr;
        nodeCount = 0;
    }

    ~Updater() {
        delete[] nodes;
    }

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

    void update_Components() {
        for (int i = 0; i < nodeCount; i++) {
            nodes[i]->update_nodeValue();
        }
    }
};