#ifndef SCENE_H_

#define SCENE_H_

#include "core/gameobject.hpp"
#include <vector>
#include <map>
#include <string>

namespace Core
{
    class Scene
    {
    public:

        Scene(const char *jsonFileName, std::map<std::string, IComponentParser*> parsers);
        ~Scene();

        inline std::string Name() { return m_Name; }

        void Start();
        void Update();
        void Render();
        void Finish();

        GameObject *CreateGameObject();
        GameObject *FindGameObject(std::string name);
        GameObject *FindGameObject(int index);

    private:

        std::vector<GameObject *> m_GameObjects;
        std::string m_Name;
    };
}

#endif
