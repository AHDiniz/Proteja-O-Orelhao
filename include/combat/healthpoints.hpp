#ifndef HEALTH_POINTS_H_

#define HEALTH_POINTS_H_

#include "core/gameobject.hpp"

namespace Combat
{
    class HealthPoints : public Core::Component
    {
    public:

        HealthPoints(int maxHealth);
        ~HealthPoints() = default;

        void Start() override {}
        void Update() override {}
        void Render() override {}
        void Finish() override {}

        inline int MaxHealth() { return m_MaxHealth; }
        inline int CurrentHealth() { return m_CurrentHealth; }

        void Hit(int damage);

    private:

        int m_MaxHealth, m_CurrentHealth;
    };

    class HealthPointsParser : public Core::IComponentParser
    {
    public:
        Core::Component *Parse(json &data) override;
    };
}

#endif
