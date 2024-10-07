#ifndef LAYER_UTILS_H
#define LAYER_UTILS_H
#include <iostream>
#include <unordered_set>
#include "Node.h"
#include <memory>

class LayerUtils
{
    private:
        std::unordered_set<std::shared_ptr<Node>> visited;
        std::vector<std::shared_ptr<Node>> orderedNodes;

        void buildTopoGraph(std::shared_ptr<Node> root);
    public:
        // In contrast to the backward function on the node,
        // This function recursively calls backward on children nodes
        // While making sure one node is not visited twice.
        void backward(std::shared_ptr<Node> root);
        
};

#endif