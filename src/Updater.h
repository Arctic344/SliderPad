
#pragma once
#include "Node.h"
#include "Adafruit_NeoPixel.h"


class Updater {
private:
    Node** nodes;
    int nodeCount;
    Adafruit_NeoPixel* strip;

public:
    Updater() {
        nodes = nullptr;
        nodeCount = 0;
        strip = nullptr;
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
    void setStrip(Adafruit_NeoPixel* strip) {
        this->strip = strip;
    }
    void update_Components() {
        for (int i = 0; i < nodeCount; i++) {
            nodes[i]->update_nodeValue();
        }
        if (strip != nullptr) {
            strip->show();
        }
    }
};