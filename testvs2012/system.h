#pragma once
#ifndef SYSTEM_H_
#define SYSTEM_H_
#include "component.h"
#include "assert.h"

class System
{
public:
    virtual void ProcessEntity(const Entity& entity) = 0;

    System(EntityManager& em): 
        enabled(true),
        entityManager(em)
    {

    }
    bool IsEnabled()
    {
        return enabled;
    }
    void Enable()
    {
        enabled = true;
    }
    void Disable()
    {
        enabled = false;
    }
    bool Matching(const Entity& entity)
    {
        (entity.ComponentTypes() & componentTypes) == componentTypes;
    }
    bool TryToInsert(const Entity& entity)
    {
        if (!Matching(entity))
        {
            return false;
        }

        entityIDs.push_back(entity.ID());
        return true;
    }
    bool TryToLeave(const Entity& entity)
    {
        if (Matching(entity))
        {
            return false;
        }

        //entityIDs.erase(entity.ID());
        return true;
    }
    void Update()
    {
        for (int i = 0, size = entityIDs.size(); i < size; ++i)
        {
            ProcessEntity(entityManager.GetEntity(entityIDs[i]));
        }
    }

    bool enabled;
    std::bitset<32> componentTypes;
    std::vector<int> entityIDs;
    EntityManager& entityManager;
};

// then you can make an array of systems, iterate all of them
// and if any, or all, of the systems is/are disabled, then you can skip its update()

class MovementSystem : public System
{
public:
    MovementSystem(EntityManager& em): System(em)
    {
        componentTypes.set(TransformComponent::TypeIndex());
        componentTypes.set(VelocityComponent::TypeIndex());
    }
    virtual void ProcessEntity(const Entity& entity)
    {
        TransformComponent& transform = transforms.GetComponent(entity);
        VelocityComponent& velocity = velocitys.GetComponent(entity);
    }

    ComponentMapper<TransformComponent> transforms;
    ComponentMapper<VelocityComponent> velocitys;
};

class RenderSystem : public System
{
public:
    RenderSystem(EntityManager& em): System(em)
    {
        componentTypes.set(TransformComponent::TypeIndex());
    }
    virtual void ProcessEntity(const Entity& entity)
    {
        
    }

    ComponentMapper<TransformComponent> transforms;
};

//class System
//{
//    private final int systemIndex; // == system ID, feed this into entity's system-bits
//    
//    protected World* world;
//    private Bag<Entity*> actives;
//    private Aspect aspect; // == class definition? or typeinfo?
//    private BitSet allSet;
//    private BitSet exclusionSet;
//    private BitSet oneSet;
//
//    private boolean passive; // what for?
//    private boolean dummy; // what for?
//};

#endif // SYSTEM_H_
