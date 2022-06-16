#include "combat/healthpoints.hpp"
#include "raymath.h"

namespace Combat
{
    HealthPoints::HealthPoints(int maxHealth)
    {
        m_MaxHealth = maxHealth;
        m_CurrentHealth = 0;
    }

    void HealthPoints::Hit(int damage)
    {
        m_CurrentHealth -= damage;
        if (m_CurrentHealth < 0)
            m_CurrentHealth = 0;
        if (m_CurrentHealth > m_MaxHealth)
            m_CurrentHealth = m_MaxHealth;
    }

    Core::Component *HealthPointsParser::Parse(json &data)
    {
        json maxHealth = data["maxHealth"];

        return (Core::Component *) new HealthPoints(maxHealth.get<int>());
    }
}
