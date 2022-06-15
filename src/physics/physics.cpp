#include "physics/physics.hpp"
#include "raymath.h"

namespace Physics
{
    void Collider::OnCollision(Collider *other)
    {
        for (std::function<void(Collider*)> event : m_OnColEvents)
        {
            event(other);
        }
    }

    Rigidbody::Rigidbody(float mass, float staticFriction, float dynamicFriction, float restituition)
    {
        m_Mass = mass;
        m_StaticFriction = staticFriction;
        m_DynamicFriction = dynamicFriction;
        m_Restituition = restituition;

        m_Velocity.x = 0;
        m_Velocity.y = 0;

        m_Force.x = 0;
        m_Force.y = 0;
    }

    void Rigidbody::ApplyForce(Vector2 force)
    {
        m_Force.x += force.x;
        m_Force.y += force.y;
    }

    Core::Component *RigidbodyParser::Parse(json &data)
    {
        json mass = data["mass"];
        json staticFriction = data["staticFriction"];
        json dynamicFriction = data["dynamicFriction"];
        json restituition = data["restituition"];

        return (Core::Component *) new Rigidbody(
            mass.get<float>(),
            staticFriction.get<float>(),
            dynamicFriction.get<float>(),
            restituition.get<float>()
        );
    }

    CircleCollider::CircleCollider(float radius, bool isTrigger)
    {
        m_Radius = radius;
        m_IsTrigger = isTrigger;
        m_ColType = CIRCLE;
    }

    CollisionPoints CircleCollider::Test(Collider *other)
    {
        CollisionPoints points = {0};

        return points;
    }

    Core::Component *CircleColliderParser::Parse(json &data)
    {
        json radius = data["radius"];
        json isTrigger = data["isTrigger"];

        return (Core::Component*) new CircleCollider(
            radius.get<float>(),
            isTrigger.get<bool>()
        );
    }

    RectangleCollider::RectangleCollider(Vector2 dimensions, bool isTrigger)
    {
        m_Dimensions = dimensions;
        m_IsTrigger = isTrigger;
        m_ColType = RECT;
    }

    CollisionPoints RectangleCollider::Test(Collider *other)
    {
        CollisionPoints points = {0};

        return points;
    }

    Core::Component *RectangleColliderParser::Parse(json &data)
    {
        json dimensions = data["dimensions"];
        json width = dimensions["width"];
        json height = dimensions["height"];
        json isTrigger = data["isTrigger"];

        Vector2 dim;
        dim.x = width.get<float>();
        dim.y = height.get<float>();

        return (Core::Component*) new RectangleCollider(dim, isTrigger.get<bool>());
    }

    void CollisionSolver::Update()
    {
        m_Collisions.clear();
        m_Triggers.clear();

        for (Collider *a : m_Colliders)
        {
            for (Collider *b : m_Colliders)
            {
                if (a == b)
                    break;
                
                CollisionPoints points = a->Test(b);
                Collision c;
                c.a = a;
                c.b = b;
                c.points = points;

                if (points.collision)
                {
                    if (a->IsTrigger() || b->IsTrigger())
                    {
                        m_Triggers.push_back(c);
                    }
                    else
                    {
                        m_Collisions.push_back(c);
                    }
                }
            }
        }
    }

    void CollisionSolver::SolveCollisions()
    {
        for (IResponse *s : m_Responses)
        {
            s->Solve(m_Collisions);
        }
    }

    void CollisionSolver::CallCollisionEvents()
    {
        for (Collision c : m_Collisions)
        {
            c.a->OnCollision(c.b);
            c.b->OnCollision(c.a);
        }

        for (Collision c : m_Triggers)
        {
            c.a->OnCollision(c.b);
            c.b->OnCollision(c.a);
        }
    }

    void DynamicsSolver::Update(float dt)
    {
        for (Rigidbody *body : m_Bodies)
        {
            Vector2 vel = Vector2Add(body->Velocity(), Vector2Scale(body->Force(), dt / body->Mass()));
            body->SetVelocity(vel);
            
            Core::Transform2D *t =
                static_cast<Core::Transform2D *>(body->GetGameObject()->GetComponent("Transform2D"));
            
            Vector2 pos = Vector2Add(t->Position(), Vector2Scale(vel, dt));
            t->SetPosition(pos);

            body->ApplyForce(Vector2Zero());
        }
    }

    CollisionPoints TestCircleRect(CircleCollider *sphere, RectangleCollider *rect)
    {
        
    }

    CollisionPoints TestCircleCircle(CircleCollider *a, CircleCollider *b)
    {
        CollisionPoints points;

        Core::GameObject *ag = a->GetGameObject();
        Core::GameObject *bg = b->GetGameObject();

        Core::Transform2D *at = static_cast<Core::Transform2D*>(ag->GetComponent("Transform2D"));
        Core::Transform2D *bt = static_cast<Core::Transform2D*>(bg->GetComponent("Transform2D"));

        Vector2 dist = Vector2Subtract(bt->Position(), at->Position());

        points.normal = Vector2Normalize(dist);
        points.depth = Vector2Length(dist);
        
        points.a = Vector2Add(at->Position(), Vector2Scale(points.normal, -a->Radius()));
        points.b = Vector2Add(bt->Position(), Vector2Scale(points.normal, b->Radius()));
        
        points.collision = points.depth - a->Radius() >= b->Radius();

        return points;
    }

    CollisionPoints TestRectRect(RectangleCollider *a, RectangleCollider *b)
    {

    }
}
