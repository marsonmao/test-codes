#pragma once
#ifndef DATABASE_H_
#define DATABASE_H_
#include <vector>
#include <map>
#include "entity.h"

class IContainer
{
public:
    virtual void Remove(Entity& entity) = 0;
    static int containerIndex; // == uid
};

template<typename T>
class Container : public IContainer
{
public:
    Container()
    {
        ++containerIndex; // currently useless
    }
    virtual void Remove(Entity& entity)
    {
        for (int i = 0, size = components.size(); i < size; ++i)
        {
            if (components[i].EntityID() == entity.ID())
            {
                // swap(i, last)
                // adjust last's arrayIndex
                // pop_back
                return;
            }
        }
    }
    std::vector<T>& GetComponets()
    {
        return components;
    }
    int Index() const
    {
        return containerIndex;
    }

    std::vector<T> components;
};

class DataBase
{
public:
    template <typename T>
    static std::vector<T>& GetComponets()
    {
        static Container<T> container;
        static bool firstTime = true;
        if (firstTime)
        {
            datas.insert(std::make_pair(T::Name(), &container));
            firstTime = false;
        }
        return container.GetComponets();
    }

    template <typename T>
    static void Add(T com)
    {
        GetComponets<T>().push_back(com);
    }

    template <typename T>
    static void Remove(T com)
    {
        GetComponets<T>().erase(com.ArrayIndex());
        // use copy-last-one instead of erase
        // dont forget to adjust array index
    }

    static void Add(const std::string& )//comName)
    {
        // add a default one?
    }

    template <typename T>
    static T& Add(Entity& entity)
    {
        T newComponent;
        newComponent.entityID = entity.ID();
        newComponent.arrayIndex = GetComponets<T>().size();
        GetComponets<T>().push_back(newComponent);
        return GetComponets<T>().back();
    }

    template <typename T, typename P1>
    static T& Add(Entity& entity, P1 p1)
    {
        T newComponent(p1);
        newComponent.entityID = entity.ID();
        newComponent.arrayIndex = GetComponets<T>().size();
        GetComponets<T>().push_back(newComponent);
        return GetComponets<T>().back();
    }

    template <typename T>
    static void Remove(Entity& entity)
    {
        // find by entity ID in GetComponets<T>()
        //std::find(GetComponets<T>().begin(), GetComponets<T>().end(), entity.ID());

        // if there is that component, remove it
        // use copy-last-one instead of erase
        // dont forget to adjust array index
    }

    // low performance, reconsider this
    // design a method to find corresponding containers only
    static void RemoveComponets(Entity& entity)
    {
        DataMap::iterator it1 = datas.begin();
        DataMap::iterator it2 = datas.end();
        for (; it1 != it2; ++it1)
        {
            IContainer* container = it1->second;
            container->Remove(entity);
        }
    }

    typedef std::map<std::string, IContainer*> DataMap; // map key seems useless
    // OR ? //static std::map<int, IContainer*> datas; // use Container.Index();
    static DataMap datas;
};

//class Database // the ComponentManager
//{
// row: map
// column: array

// row: key = string (type name), value = array
// column: components.

// methods:
// 1. add componet(s) for entity
// 2. remove componet(s) for entity
// 3. modify --> seems no need

// reponsible, or can be used to perform serialize/deserialize
// (should not be responsible)
// (so who is in charge of de/serialize? world?)
//};

#endif // DATABASE_H_
