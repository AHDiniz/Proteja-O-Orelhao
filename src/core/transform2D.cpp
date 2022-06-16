#include "core/transform2D.hpp"

namespace Core
{
    Transform2D::Transform2D()
    {
        m_Position.x = .0f;
        m_Position.y = .0f;
        m_Rotation = .0f;
    }

    Transform2D::Transform2D(Vector2 position, float rotation)
    {
        m_Position.x = position.x;
        m_Position.y = position.y;
        m_Rotation = rotation;
    }

    Component *Transform2DParser::Parse(json &data)
    {
        json position = data["position"];
        json rotation = data["rotation"];
        json x = position["x"];
        json y = position["y"];

        Vector2 pos;
        pos.x = x.get<float>();
        pos.y = y.get<float>();
        Transform2D *t = new Transform2D(pos, rotation.get<float>());

        return (Component *)t;
    }
}
