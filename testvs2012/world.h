#pragma once
#ifndef WORLD_H_
#define WORLD_H_
#include "entity.h"
#include "database.h"
#include "system.h"

class World
{
public:
    World(): 
        entityManager(*this)
    {
        systems.insert(std::make_pair(0, new MovementSystem(entityManager)));
    }
    EntityManager& GetEntityManager()
    {
        return entityManager;
    }
    System* GetSystem() // by what? system index? template? // needed?
    {
        return 0;
    }
    void EnableSystem() // by what? system index? template? // needed?
    {

    }
    void DisableSystem() // by what? system index? template? // needed?
    {

    }
    Entity& CreateEntity()
    {
        return entityManager.CreateEntity();
    }
    void AddEntity(Entity& entity)
    {
        // put into world
        // bind this with CreateEntity()?
    }
    void RemoveEntity(Entity& entity)
    {
        // remove all components
        // remove entity
    }
    Entity& GetEntity(int entityID)
    {
        return entityManager.GetEntity(entityID);
    }
    template <typename T>
    T& AddComponent(Entity& entity)
    {
        T& addedComponent = DataBase::Add<T>(entity);
        // test entity for all systems
        return addedComponent;
    }
    template <typename T>
    void RemoveComponent(Entity& entity)
    {
        DataBase::Remove(entity);
        // test entity for all systems
    }
    void Update()
    {
        // iterate all systems
    }

    EntityManager entityManager;
    std::map<int, System*> systems; // or vector?
};

//// like a game world? or like a MOGA window (so there can be multiple "worlds"?)
//class World
//{
//    private EntityManager em;
//    private ComponentManager cm; // database
//
//    public float delta;
//    // these bags are responsible for some "temp" entities
//    // whense these entities are suitably processed, the bags will be cleared.
//    // not sure if we need these bags.
//    private Bag<Entity> added;
//    private Bag<Entity> changed;
//    private Bag<Entity> deleted;
//    private Bag<Entity> enable;
//    private Bag<Entity> disable;
//
//    private Map<Class<? extends Manager>, Manager> managers;
//    private Bag<Manager> managersBag;
//
//    private Map<Class<?>, EntitySystem> systems;
//    private Bag<EntitySystem> systemsBag;
//
//    // Adds a entity to this world.
//    public void addEntity(Entity e)
//    {
//        added.add(e);
//    }
//        
//    // Ensure all systems are notified of changes to this entity.
//    // If you're adding a component to an entity after it's been
//    // added to the world, then you need to invoke this method.
//    public void changedEntity(Entity e)
//    {
//        changed.add(e);
//    }
//        
//    // Delete the entity from the world.
//    public void deleteEntity(Entity e)
//    {
//        if (!deleted.contains(e)) // so deleted is not cleared?!
//        {
//            deleted.add(e);
//        }
//    }
//
//    // (Re)enable the entity in the world, after it having being disabled.
//    public void enable(Entity e)
//    {
//        enable.add(e);
//    }
//
//    // Disable the entity from being processed. Won't delete it, it will
//    // continue to exist but won't get processed.
//    // what's the purpose of this?
//    public void disable(Entity e)
//    {
//        disable.add(e);
//    }
//
//    // Create and return a new or reused entity instance.
//    // Will NOT add the entity to the world, use World.addEntity(Entity) for that.
//    // should create and add be separated?
//    public Entity createEntity()
//    {
//        return em.createEntityInstance();
//    }
//
//    // Get a entity having the specified id.
//    public Entity getEntity(int entityId)
//    {
//        return em.getEntity(entityId);
//    }
//    /**
//    * Gives you all the systems in this world for possible iteration.
//    */
//    public ImmutableBag<EntitySystem> getSystems() {
//            return systemsBag;
//    }
//
//    /**
//    * Adds a system to this world that will be processed by World.process()
//    */
//    // should be never needed
//    // systems are static information
//    public <T extends EntitySystem> T setSystem(T system) {
//            return setSystem(system, false);
//    }
//
//    /**
//    * Will add a system to this world.
//    */
//    // should be never needed
//    // systems are static information
//    public <T extends EntitySystem> T setSystem(T system, boolean passive) {
//            system.setWorld(this);
//            system.setPassive(passive);
//            systems.put(system.getClass(), system);
//            systemsBag.add(system);
//            return system;
//    }
//        
//    /**
//    * Removed the specified system from the world.
//    */
//    // should be never needed
//    // systems are static information
//    public void deleteSystem(EntitySystem system) {
//            systems.remove(system.getClass());
//            systemsBag.remove(system);
//    }
//        
//    private void notifySystems(Performer performer, Entity e) {
//            for(int i = 0, s=systemsBag.size(); s > i; i++) {
//                    performer.perform(systemsBag.get(i), e);
//            }
//    }
//
//    private void notifyManagers(Performer performer, Entity e) {
//            for(int a = 0; managersBag.size() > a; a++) {
//                    performer.perform(managersBag.get(a), e);
//            }
//    }
//        
//    /**
//    * Retrieve a system for specified system type.
//    */
//    public <T extends EntitySystem> T getSystem(Class<T> type) {
//            return type.cast(systems.get(type));
//    }
//        
//    /**
//    * Performs an action on each entity.
//    */
//    // for add, change, dis/enable, delete actions
//    private void check(Bag<Entity> entities, Performer performer) {
//            if (!entities.isEmpty()) {
//                    for (int i = 0; entities.size() > i; i++) {
//                            Entity e = entities.get(i);
//                            notifyManagers(performer, e);
//                            notifySystems(performer, e);
//                    }
//                    entities.clear();
//            }
//    }
//
//        
//    /**
//    * Process all non-passive systems.
//    */
//    // the Update() function
//    public void process() {
//            check(added, new Performer() {
//                    @Override
//                    public void perform(EntityObserver observer, Entity e) {
//                            observer.added(e);
//                    }
//            });
//                
//            check(changed, new Performer() {
//                    @Override
//                    public void perform(EntityObserver observer, Entity e) {
//                            observer.changed(e);
//                    }
//            });
//                
//            check(disable, new Performer() {
//                    @Override
//                    public void perform(EntityObserver observer, Entity e) {
//                            observer.disabled(e);
//                    }
//            });
//                
//            check(enable, new Performer() {
//                    @Override
//                    public void perform(EntityObserver observer, Entity e) {
//                            observer.enabled(e);
//                    }
//            });
//                
//            check(deleted, new Performer() {
//                    @Override
//                    public void perform(EntityObserver observer, Entity e) {
//                            observer.deleted(e);
//                    }
//            });
//                
//            cm.clean();
//                
//            for(int i = 0; systemsBag.size() > i; i++) {
//                    EntitySystem system = systemsBag.get(i);
//                    if(!system.isPassive()) {
//                            system.process();
//                    }
//            }
//    }
//        
//
//    /**
//    * Retrieves a ComponentMapper instance for fast retrieval of components from entities.
//    */
//    public <T extends Component> ComponentMapper<T> getMapper(Class<T> type) {
//            return ComponentMapper.getFor(type, this);
//    }
//
//    /*
//        * Only used internally to maintain clean code.
//        */
//    private interface Performer {
//            void perform(EntityObserver observer, Entity e);
//    }
//
//    private static class ComponentMapperInitHelper {
//
//            public static void config(Object target, World world) {
//                    try {
//                            Class<?> clazz = target.getClass();
//                            for (Field field : clazz.getDeclaredFields()) {
//                                    Mapper annotation = field.getAnnotation(Mapper.class);
//                                    if (annotation != null && Mapper.class.isAssignableFrom(Mapper.class)) {
//                                            ParameterizedType genericType = (ParameterizedType) field.getGenericType();
//                                            Class componentType = (Class) genericType.getActualTypeArguments()[0];
//
//                                            field.setAccessible(true);
//                                            field.set(target, world.getMapper(componentType));
//                                    }
//                            }
//                    } catch (Exception e) {
//                            throw new RuntimeException("Error while setting component mappers", e);
//                    }
//            }
//
//    }
//};

#endif // WORLD_H_
