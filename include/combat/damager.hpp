#ifndef DAMAGER_H_

#define DAMAGER_H_

#include "core/gameobject.hpp"
#include "physics/physics.hpp"

namespace Combat
{
    class Damager : public Core::Component
    {
    public:

        Damager(int damage);

        void Start() override;
        void Update() override {}
        void Render() override {}
        void Finish() override {}

        inline int Damage() { return m_Damage; }

    private:

        void OnCollision(Physics::Collider *other);

        int m_Damage;
    };

    class DamagerParser : public Core::IComponentParser
    {
    public:
        Core::Component *Parse(json &data) override;
    };
}

#endif
