#ifndef PLAYER_MOVEMENT_H_

#define PLAYER_MOVEMENT_H_

#include "core/gameobject.hpp"
#include "core/transform2D.hpp"
#include "json.hpp"

namespace Player
{
    class PlayerMovement : public Core::Component
    {
    public:

        PlayerMovement(float walkSpeed);

        void Start() override;
        void Update() override;
        void Render() override;
        void Finish() override;

    private:

        float m_WalkSpeed;
        Core::Transform2D *m_Transform;
    };

    class PlayerMovementParser : public Core::IComponentParser
    {
    public:
        Core::Component *Parse(json &data) override;
    };
}

#endif
