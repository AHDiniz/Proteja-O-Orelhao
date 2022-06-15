#pragma once

#include "core/gameobject.hpp"
#include "core/transform2D.hpp"
#include <functional>

namespace Physics
{
    using CollisionEvent = std::function<void(Collider*)>;

    struct CollisionPoints
    {
        Vector2 a, b;
        Vector2 normal;
        float depth;
        bool collision;
    };

    enum ColliderType
    {
        CIRCLE,
        RECT
    };

    class Collider : public Core::Component
    {
    public:
        virtual CollisionPoints Test(Collider *other) = 0;

        void Start() override {}
        void Update() override {}
        void Render() override {}
        void Finish() override {}
        
        inline void AddCollisionEvent(CollisionEvent &event) { m_OnColEvents.push_back(event); }
        void OnCollision(Collider *other);

        inline ColliderType ColType() { return m_ColType; }
        inline bool IsTrigger() { return m_IsTrigger; }
    
    protected:
        ColliderType m_ColType;
        bool m_IsTrigger;

        std::vector<CollisionEvent> m_OnColEvents;
    };

    struct Collision
    {
        Collider *a, *b;
        CollisionPoints points;
    };

    class Rigidbody : public Core::Component
    {
    public:

        Rigidbody(float mass, float staticFriction, float dynamicFriction, float restituition);
        ~Rigidbody() = default;

        inline float Mass() { return m_Mass; }
        inline void SetMass(float mass) { m_Mass = mass; }

        inline Vector2 Force() { return m_Force; }

        inline Vector2 Velocity() { return m_Velocity; }
        inline void SetVelocity(Vector2 velocity) { m_Velocity = velocity; }

        inline float StaticFriction() { return m_StaticFriction; }
        inline void SetStaticFriction(float staticFriction) { m_StaticFriction = staticFriction; }

        inline float DynamicFriction() { return m_DynamicFriction; }
        inline void SetDynamicFriction(float dynamicFriction) { m_DynamicFriction = dynamicFriction; }

        inline float Restituition() { return m_Restituition; }
        inline void SetRestituition(float restituition) { m_Restituition = restituition; }

        void ApplyForce(Vector2 force);

        void Start() override {}
        void Update() override {}
        void Render() override {}
        void Finish() override {}

    private:

        float m_Mass;
        Vector2 m_Force;
        Vector2 m_Velocity;

        float m_StaticFriction, m_DynamicFriction;
        float m_Restituition;
    };

    class RigidbodyParser : public Core::IComponentParser
    {
    public:
        Core::Component *Parse(json &data) override;
    };

    class IResponse
    {
    public:
        virtual void Solve(std::vector<Collision> &collisions) = 0;
    };

    class CollisionSolver
    {
    public:
        inline void AddCollider(Collider *col) { m_Colliders.push_back(col); }
        inline void AddResponse(IResponse *response) { m_Responses.push_back(response); }

        void Update();

    private:

        void SolveCollisions();
        void CallCollisionEvents();

        std::vector<Collider*> m_Colliders;
        std::vector<Collision> m_Collisions;
        std::vector<Collision> m_Triggers;
        std::vector<IResponse*> m_Responses;
    };

    class DynamicsSolver
    {
    public:
        inline void AddRigidbody(Rigidbody *body) { m_Bodies.push_back(body); }

        void Update(float dt);

    private:
        
        std::vector<Rigidbody*> m_Bodies;
    };

    class CircleCollider : public Collider
    {
    public:

        CircleCollider(float radius, bool isTrigger);
        ~CircleCollider() = default;

        CollisionPoints Test(Collider *other) override;

        inline float Radius() { return m_Radius; }

    private:

        float m_Radius;
    };

    class CircleColliderParser : public Core::IComponentParser
    {
    public:
        Core::Component *Parse(json &data) override;
    };

    class RectangleCollider : public Collider
    {
    public:

        RectangleCollider(Vector2 dimensions, bool isTrigger);
        ~RectangleCollider() = default;

        CollisionPoints Test(Collider *other) override;

    private:

        Vector2 m_Dimensions;
    };

    class RectangleColliderParser : public Core::IComponentParser
    {
    public:
        Core::Component *Parse(json &data) override;
    };

    CollisionPoints TestCircleRect(CircleCollider *sphere, RectangleCollider *rect);
    CollisionPoints TestCircleCircle(CircleCollider *a, CircleCollider *b);
    CollisionPoints TestRectRect(RectangleCollider *a, RectangleCollider *b);
}
