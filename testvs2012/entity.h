#pragma once
#ifndef ENTITY_H_
#define ENTITY_H_
#include <bitset>
#include "component.h"

class Entity;
class EntityManager;
class World;

struct Indexes
{
    Indexes(
        int tidx, 
        int aidx): 
        typeIndex(tidx),
        arrayIndex(aidx)
    {

    }
    int typeIndex;
    int arrayIndex;
};

class Entity
{
public:
    Entity(
        int newID,
        World& newWorld,
        EntityManager& newManager):
        id(newID),
        world(newWorld),
        manager(newManager)
    {

    }
    int ID() const
    {
        return id;
    }
    const std::bitset<32>& ComponentTypes() const
    {
        return componentTypes;
    }
    const std::vector<Indexes>& ComponentIndexes() const
    {
        return componentIndexes;
    }
    int ComponentArrayIndex(int componentTypeIndex) const
    {
        for (int i = 0, size = componentIndexes.size(); i < size; ++i)
        {
            Indexes indexes = componentIndexes[i];
            if (indexes.typeIndex == componentTypeIndex)
            {
                return indexes.arrayIndex;
            }
        }
        return -1;
    }
    template<typename T>
    void AddComponent(const Component<T>& newComponent)
    {
        componentIndexes.push_back(Indexes(
            newComponent::TypeIndex(), 
            newComponent.ArrayIndex()));
    }
    template<typename T>
    void RemoveComponent(const Component<T>& newComponent)
    {
        // find by type index, then swap-popback it
    }

    // UUID uuid; // need another uuid for reflection system
    int id;
    std::bitset<32> componentTypes;
    std::vector<Indexes> componentIndexes;
    World& world;
    EntityManager& manager;

private:
    Entity& operator=(const Entity&) {}
};

class EntityManager
{
public:
    EntityManager(
        World& newWorld):
        world(newWorld),
        dummy(-1, newWorld, *this)
    {

    }
    Entity& CreateEntity()
    {
        Entity* e = new Entity(GenerateID(), world, *this);
        entitys.push_back(e);
        return (*e);
    }
    int GenerateID()
    {
        // generate unique id (UUID)
        return 0;
    }
    void DestroyEntity(int)// id)//(UUID)
    {
        // find by id, then delete it
    }
    Entity& GetEntity(int)// id)//(UUID)
    {
        // find by id, or return dummy
        return dummy;
    }

    std::vector<Entity*> entitys;
    World& world;
    Entity dummy;
};

//class Entity
//{
//    UUID uuid;
//    int id; // is this array index? or merge with uuid?
//    std::bitset<32> componentBits;
//    std::bitset<32> systemBits; // ??
//
//    World world;
//    EntityManager entityManager;
//    ComponentManager componentManager; // the Database
//
//    void reset()
//    {
//        systemBits.clear();
//        componentBits.clear();
//        uuid = UUID.randomUUID();
//    }
//
//    Entity* addComponent(Component* component) // or reference? (return and paramter)
//    {
//        // get type => get type info?
//        addComponent(component, ComponentType.getTypeFor(component.getClass()));
//        return this;
//    }
//
//    Entity* addComponent(Component* component, ComponentType type) // if type is known
//    {
//        componentManager.addComponent(this, type, component);
//        return this;
//    }
//
//    Entity* addComponent(const std::string& typeName)
//    {
//        // use existing typeinfo class
//        /*Component* newComponent = hive::CreateObjectByName<Component>(typeName);
//        _AddComponent(newComponent);
//        return newComponent;*/
//        return this;
//    }
//
//    Entity* removeComponent(Component component)
//    {
//        removeComponent(component.getClass());
//        return this;
//    }
//
//    Entity* removeComponent(ComponentType type) // if type is known
//    {
//        componentManager.removeComponent(this, type);
//        return this;
//    }
//
//    Entity removeComponent(Class<? extends Component> type) // by real type (class)?
//    {
//        removeComponent(ComponentType.getTypeFor(type));
//        return this;
//    }
//
//    Entity* removeComponent(const std::string& typeName)
//    {
//        // use existing typeinfo class
//        return this;
//    }
//
//    boolean isActive() // what's this for?
//    {
//        return entityManager.isActive(id);
//    }
//
//    boolean isEnabled() // what's this for?
//    {
//        return entityManager.isEnabled(id);
//    }
//
//    Component* getComponent(ComponentType type) // should not need this
//    {
//        return componentManager.getComponent(this, type);
//    }
//
//    /**
//         * Slower retrieval of components from this entity. Minimize usage of this,
//         * but is fine to use e.g. when creating new entities and setting data in
//         * components.
//    */ // I dont think so...should give data to component first, and then add it to the entity
//    <T extends Component> T getComponent(Class<T> type)
//    {
//        return type.cast(getComponent(ComponentType.getTypeFor(type)));
//    }
//
//    Bag<Component> getComponents(Bag<Component> fillBag)
//    {
//        return componentManager.getComponentsFor(this, fillBag);
//    }
//
//    void addToWorld() // ok = =
//    {
//        world.addEntity(this);
//    }
//
//    void changedInWorld() // update after component change
//    {
//        world.changedEntity(this);
//    }
//
//    void deleteFromWorld() // opposite of add to world
//    {
//        world.deleteEntity(this);
//    }
//};

//// create, destroy entity
//class EntityManager
//{
//    // are there multiple managers? NO, and YES
//    // entity manager and world is one-to-one relationship
//    // but there can be multiple worlds.
//
//    // entities that are belonged to this manager
//    Bag<Entity> entities;
//    // what?
//    BitSet disabled;
//    // any use?
//    int active;
//    long added;
//    long created;
//    long deleted;
//    // ??
//    IdentifierPool identifierPool;
//
//    Entity* createEntityInstance() // protected? why?
//    {
//        Entity* e = new Entity(world, identifierPool.checkOut());
//        created++;
//        return e;
//    }
//
//    //@Override
//    void added(Entity e)
//    {
//        active++;
//        added++;
//        entities.set(e.getId(), e);
//    }
//
//    //@Override
//    void enabled(Entity e)
//    {
//        disabled.clear(e.getId());
//    }
//
//    //@Override
//    void disabled(Entity e)
//    {
//        disabled.set(e.getId());
//    }
//
//    //@Override
//    void deleted(Entity e)
//    {
//        entities.set(e.getId(), null);
//        disabled.clear(e.getId());
//        identifierPool.checkIn(e.getId());
//
//        active--;
//        deleted++;
//    }
//
//    /*
//    * Used only internally to generate distinct ids for entities and reuse them.
//    */
//    //private 
//    class IdentifierPool
//    {
//        Bag<Integer> ids;
//        int nextAvailableId;
//
//        IdentifierPool()
//        {
//            ids = new Bag<Integer>();
//        }
//
//        int checkOut()
//        {
//            if(ids.size() > 0)
//            {
//                return ids.removeLast();
//            }
//            return nextAvailableId++;
//        }
//
//        void checkIn(int id)
//        {
//            ids.add(id);
//        }
//    };
//};

//class EntityObserver // just an interface for (entity) systems
//{
//    // i think we dont need this
//};

#endif // ENTITY_H_
