#include "rendering/circlerenderer.hpp"

namespace Rendering
{
    CircleRenderer::CircleRenderer(float radius, Color color)
    {
        m_Color = color;
        m_Radius = radius;
        m_Transform = nullptr;
    }

    void CircleRenderer::Start()
    {
        Core::Component *c = m_GameObject->GetComponent<Core::Transform2D>();
        m_Transform = static_cast<Core::Transform2D *>(c);
    }

    void CircleRenderer::Update()
    {

    }

    void CircleRenderer::Render()
    {
        DrawCircleV(m_Transform->Position(), m_Radius, m_Color);
    }

    void CircleRenderer::Finish()
    {

    }

    Core::Component *CircleRendererParser::Parse(json &data)
    {
        float radius = data["radius"].get<float>();
        json color = data["color"];
        Color c;
        c.r = color["r"].get<float>();
        c.g = color["g"].get<float>();
        c.b = color["b"].get<float>();
        c.a = color["a"].get<float>();

        return (Core::Component *) new CircleRenderer(radius, c);
    }
}
