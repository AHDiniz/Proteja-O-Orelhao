#include "combat/damager.hpp"
#include "combat/healthpoints.hpp"

namespace Combat
{
    Damager::Damager(int damage)
    {
        m_Damage = damage;
        m_Type = "Damager";
    }

    void Damager::Start()
    {
        Physics::Collider *col = m_GameObject->GetComponent<Physics::Collider>();

        Physics::CollisionEvent event = [this](Physics::Collider *other) { this->OnCollision(other); };
    }

    void Damager::OnCollision(Physics::Collider *other)
    {
        Core::GameObject *otherGO = other->GetGameObject();
        HealthPoints *hp = otherGO->GetComponent<HealthPoints>();

        if (hp != nullptr)
        {
            hp->Hit(m_Damage);
        }
    }

    Core::Component *DamagerParser::Parse(json &data)
    {
        json damage = data["damage"];

        return (Core::Component *) new Damager(damage.get<int>());
    }
}
