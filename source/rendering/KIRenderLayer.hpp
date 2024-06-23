#pragma once

#include <functional>
#include <vector>

class KIRenderLayer
{
public:
    KIRenderLayer() = default;
    void addToLayer(std::function<void()> renderLambda);
    void render();
    void clear();

private:
    std::vector<std::function<void()>> renderLambdas;
};