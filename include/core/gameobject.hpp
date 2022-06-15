#ifndef GAMEOBJ_H_

#define GAMEOBJ_H_

#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

namespace Core
{
    class GameObject;

    class Component
    {
    public:
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Finish() = 0;
    
        inline bool Enabled() { return m_Enabled; }
        inline void SetEnabled(bool enabled) { m_Enabled = enabled; }

        inline std::string Type() { return m_Type; }
        inline GameObject *GetGameObject() { return m_GameObject; }

    protected:

        friend class GameObject;

        bool m_Enabled = true;
        std::string m_Type;
        GameObject *m_GameObject;
    };

    class GameObject
    {
    public:

        GameObject() = default;
        ~GameObject();

        inline bool Active() { return m_Active; }
        inline void SetActive(bool active) { m_Active = active; }

        inline std::string Name() { return m_Name; }
        inline void SetName(std::string name) { m_Name = name; }

        inline void AddComponent(Component *c) { c->m_GameObject = this; m_Components.push_back(c); }
        Component *GetComponent(std::string typeName);

        void Start();
        void Update();
        void Render();
        void Finish();

    private:

        std::vector<Component *> m_Components;
        std::string m_Name;
        bool m_Active = true;
    };

    class IComponentParser
    {
    public:
        virtual Component *Parse(json &data) = 0;
    };
}

#endif
