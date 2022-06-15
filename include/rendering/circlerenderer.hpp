#ifndef CIRCLE_RENDERER_H_

#define CIRCLE_RENDERER_H_

#include "core/gameobject.hpp"
#include "raylib.h"
#include "json.hpp"
#include "core/transform2D.hpp"

namespace Rendering
{
    class CircleRenderer : public Core::Component
    {
    public:

        CircleRenderer(float radius, Color color);
        ~CircleRenderer() = default;

        void Start() override;
        void Update() override;
        void Render() override;
        void Finish() override;
    
    private:

        float m_Radius;
        Color m_Color;
        Core::Transform2D *m_Transform;
    };

    class CircleRendererParser : public Core::IComponentParser
    {
    public:
        Core::Component *Parse(json &data) override;
    };
}

#endif
