#include "core/gameobject.hpp"

namespace Core
{
    GameObject::~GameObject()
    {
        for (Component *c : m_Components)
        {
            delete c;
        }
    }

    void GameObject::Start()
    {
        for (Component *c : m_Components)
        {
            c->Start();
        }
    }

    void GameObject::Update()
    {
        for (Component *c : m_Components)
        {
            if (c->Enabled())
            {
                c->Update();
            }
        }
    }

    void GameObject::Render()
    {
        for (Component *c : m_Components)
        {
            if (c->Enabled())
            {
                c->Render();
            }
        }
    }

    void GameObject::Finish()
    {
        for (Component *c : m_Components)
        {
            c->Finish();
        }
    }
}
