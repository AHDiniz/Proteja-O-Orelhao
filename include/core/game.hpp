#pragma once

#include <vector>
#include <string>

namespace Core
{
    class Scene;

    class Game
    {
    public:

        static Game *Instance();
        ~Game() = default;

        inline Scene *CurrentScene() { return m_CurrentScene; }
        inline void AddScene(Scene *scene) { m_Scenes.push_back(scene); }

        void Start();
        void Update();
        void Render();
        void Finish();

        void GoToScene(std::string name);

    private:

        Game() = default;
        
        Scene *m_CurrentScene;
        std::vector<Scene*> m_Scenes;
    };
}
