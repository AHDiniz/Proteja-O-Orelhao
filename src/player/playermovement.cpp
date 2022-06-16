#include "player/playermovement.hpp"

namespace Player
{
    PlayerMovement::PlayerMovement(float walkSpeed)
    {
        m_WalkSpeed = walkSpeed;
        m_Type = "PlayerMovement";
    }

    Core::Component *PlayerMovementParser::Parse(json &data)
    {
        float walkSpeed = data["walkSpeed"].get<float>();

        return (Core::Component *) new PlayerMovement(walkSpeed);
    }

    void PlayerMovement::Start()
    {
        m_Transform = static_cast<Core::Transform2D*>(m_GameObject->GetComponent<Core::Transform2D>());
    }

    void PlayerMovement::Update()
    {
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            Vector2 pos = m_Transform->Position();
            pos.y -= m_WalkSpeed * GetFrameTime();
            m_Transform->SetPosition(pos);
        }
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            Vector2 pos = m_Transform->Position();
            pos.y += m_WalkSpeed * GetFrameTime();
            m_Transform->SetPosition(pos);
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            Vector2 pos = m_Transform->Position();
            pos.x -= m_WalkSpeed * GetFrameTime();
            m_Transform->SetPosition(pos);
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            Vector2 pos = m_Transform->Position();
            pos.x += m_WalkSpeed * GetFrameTime();
            m_Transform->SetPosition(pos);
        }
    }

    void PlayerMovement::Render() {}

    void PlayerMovement::Finish() {}
}
