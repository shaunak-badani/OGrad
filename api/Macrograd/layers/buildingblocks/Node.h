#ifndef VALUE_H
#define VALUE_H
#include <vector>
#include <iostream>
#include <functional>
#include <memory>
#include "Mat.h"
#include <unordered_set>

class Node
{
    public:
        std::unordered_set<std::shared_ptr<Node>> previous;
        std::shared_ptr<Mat> data;
        std::shared_ptr<Mat> grad;
        std::function<void(void)> backward;
        Node(std::shared_ptr<Mat> paramData);
        Node(std::shared_ptr<Mat> paramData, std::unordered_set<std::shared_ptr<Node>> previous);

        friend std::shared_ptr<Node> operator+(std::shared_ptr<Node> a, std::shared_ptr<Node> b);
        friend std::shared_ptr<Node> operator-(std::shared_ptr<Node> a, std::shared_ptr<Node> b);
        friend std::shared_ptr<Node> operator*(std::shared_ptr<Node> a, std::shared_ptr<Node> b);
        friend std::shared_ptr<Node> operator/(std::shared_ptr<Node> a, float b);
        
        friend std::shared_ptr<Node> sum(std::shared_ptr<Node> a);
};

#endif