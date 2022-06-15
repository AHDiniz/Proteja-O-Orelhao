#include "core/scene.hpp"
#include "json.hpp"
#include "raylib.h"
#include <cstdio>

using json = nlohmann::json;

namespace Core
{
    Scene::Scene(const char *jsonFileName, std::map<std::string, IComponentParser*> parsers)
    {
        const char *data = LoadFileText(jsonFileName);
        json sceneJson = json::parse(data);

        m_Name = sceneJson["name"].get<std::string>();
        json objsJson = sceneJson["gameObjects"];

        for (json objJson : objsJson)
        {
            json name = objJson["name"];
            json components = objJson["components"];

            GameObject *go = new GameObject();
            for (json comp : components)
            {
                json t = comp["type"];
                std::string type = t.get<std::string>();
                json dataJson = comp["data"];
                
                Component *c = parsers[type]->Parse(dataJson);

                go->AddComponent(c);
            }

            m_GameObjects.push_back(go);
        }
    }

    GameObject *Scene::CreateGameObject()
    {
        GameObject *go = new GameObject();
        m_GameObjects.push_back(go);
        return go;
    }

    GameObject *Scene::FindGameObject(std::string name)
    {
        for (GameObject *go : m_GameObjects)
        {
            if (go->Name() == name)
            {
                return go;
            }
        }
        return nullptr;
    }

    GameObject *Scene::FindGameObject(int index)
    {
        return m_GameObjects[index];
    }

    Scene::~Scene()
    {
        for (GameObject *go : m_GameObjects)
        {
            delete go;
        }
    }

    void Scene::Start()
    {
        for (GameObject *go : m_GameObjects)
        {
            go->Start();
        }
    }

    void Scene::Update()
    {
        for (GameObject *go : m_GameObjects)
        {
            if (go->Active())
            {
                go->Update();
            }
        }
    }

    void Scene::Render()
    {
        for (GameObject *go : m_GameObjects)
        {
            if (go->Active())
            {
                go->Render();
            }
        }
    }

    void Scene::Finish()
    {
        for (GameObject *go : m_GameObjects)
        {
            go->Finish();
        }
    }
}
