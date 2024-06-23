#include "KIRenderLayer.hpp"

void KIRenderLayer::addToLayer(std::function<void()> renderLambda)
{
    renderLambdas.push_back(renderLambda);
}

void KIRenderLayer::render()
{
    for (auto& renderLambda : renderLambdas)
    {
        renderLambda();
    }    
}

void KIRenderLayer::clear()
{
    renderLambdas.clear();
}