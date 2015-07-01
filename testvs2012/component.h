#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <string>
#include <vector>
#include <typeinfo>
#include "utility.h"
//#include "entity.h"

class ComponentTypeCounter
{
public:
    static int typeCounter;
};

template <typename T>
class ComponentType : public ComponentTypeCounter
{
public:
    ComponentType()
    {
        //typeIndex = typeCounter++;
    }
    const std::string& Name() const
    {
        static std::string name = typeid(T).name();
        return name;
    }
    int TypeIndex() const
    {
        static int typeIndex = typeCounter++;
        return typeIndex;
    }

    //static std::string name;
    //int typeIndex;
};

template <typename T>
class Component
{
    friend class DataBase;

public:
    Component():
        entityID(-1),
        arrayIndex(-1)
    {

    }
    static const std::string& Name()
    {
        return type.Name();
    }
    static int TypeIndex()
    {
        return type.TypeIndex();
    }
    int EntityID() const
    {
        return entityID;
    }
    int ArrayIndex() const
    {
        return arrayIndex;
    }

private:
    static ComponentType<T> type;
    int entityID; // (UUID)
    int arrayIndex;
};

class RenderComponent : public Component<RenderComponent>
{
public:
    RenderComponent():
        test(1000)
    {
        // ....
    }

    void MakeDefault();
    int test;
};

class VelocityComponent : public Component<VelocityComponent>
{

};

class TransformComponent : public Component<TransformComponent>
{

};

class ParticleComponent : public Component<ParticleComponent>
{

};

class Entity;
template <typename T>
class ComponentMapper
{
public:
    ComponentMapper():
        components(DataBase::GetComponets<T>())
    {

    }
    ComponentMapper<T>& operator=(const ComponentMapper<T>&)
    {
        components = DataBase::GetComponets<T>();
    }
    std::vector<T>& GetComponents()
    {
        return components;
    }
    T& GetComponent(int index)
    {
        return components[index];
    }
    T& GetComponent(const Entity& )//entity)
    {
        // fix include issue then reactivate this
        //return components[entity.ComponentArrayIndex(T::TypeIndex())];
        return components[0];
    }
    size_t Size() const
    {
        return components.size();
    }

    std::vector<T>& components;
};

//class Component
//{
// entity id
// component type (see below)
// component array index, which is conceptually the entity id
//};

//class ComponentType
//{
// place this inside component // a mapping
// 1. string, the type name. which you can deduce the real type (by type info?)
// 2. typeinfo pointer. find this in ctor. (confirm this)
//};

// maybe another name
// is this template class?
//class ComponentMapper
//{
// 1. give associated component type when constructed
// 2. points to DB (the component array)

// use case
// 1. return component
// 2. return component array

// only for retrieval, no add/remove/...etc, which is responsible for DB
//};
//////////////////////////////////////////////////////////////////////////

#endif // COMPONENT_H_
