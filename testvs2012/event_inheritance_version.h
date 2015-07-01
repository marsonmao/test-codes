template <typename T>
class StripArgumentType;

template <class ArgumentType, typename ReturnType >
class StripArgumentType<std::function<ReturnType(ArgumentType)>>
{
public:
    typedef ArgumentType Type;
    typedef ReturnType NoMatter;
};

template <typename FunctionType, typename ArgumentBaseType>
void WrapCall(FunctionType f, const ArgumentBaseType& arg) 
{
    f(static_cast<StripArgumentType<FunctionType>::Type>(arg));
}

//
//template <typename R, typename A, typename ABase>
//void WrapCall(std::function<R(A)> f, const ABase& arg) 
//{
//    f(static_cast<A>(arg));
//}

class EventDispatcher
{
public:
    typedef std::function<void(const Event&)> ListenerFunction;

    Connection AddListener(std::string event, ListenerFunction function)
    {
        ConnectionGroup& cg = listeners[event];
        cg.push_back(Group(function));
        return cg.back().connection;
    }

    void RemoveListener(std::string event, Connection connection)
    {
        ConnectionGroup& cg = listeners[event];
        auto it = std::find_if(cg.begin(), cg.end(),
        [=](const Group& g)
        {
            return g.connection == connection;
        });
        assert(it != cg.end());
        cg.erase(it);
    }

    void Dispatch(const Event& e) // template with real type
    {
        auto it = listeners.find(e.Type());
        ConnectionGroup cg = it->second;
        std::for_each(cg.begin(), cg.end(), 
        [&](Group& g)
        {
            g.function(static_cast<decltype(e)>(e));
        });
    }

private:
    struct Group
    {
        Connection connection;
        ListenerFunction function;

        Group(ListenerFunction function): function(function) {}
    };
    typedef std::vector<Group> ConnectionGroup;

    std::map<std::string, ConnectionGroup> listeners;
};

class MouseDispatcher: public EventDispatcher
{
public:
    void MouseOn()
    {
        MouseEvent e("On", 100, 101);
        Dispatch(e);
        MouseEXEvent e1("OnEx", 100, 101, 200);
        Dispatch(e1);
    }

    void MouseSuperOn()
    {
        MouseEXEvent e("OnEx", 100, 101, 200);
        Dispatch(e);
    }

    /*void AddListener(std::string event, EventDispatcher<MouseEvent>::ListenerFunction function)
    {
        m.AddListener(event, function);
    }*/

    /*void AddListener(std::string event, EventDispatcher<MouseEXEvent>::ListenerFunction function)
    {
        mex.AddListener(event, function);
    }*/
};

class Subscriber
{
public:
    void AddListener(EventDispatcher& d, std::string event, EventDispatcher::ListenerFunction function)
    {
        if (connections.find(event) != connections.end())
        {
            return;
        }

        connections[event] = d.AddListener(event, function);
    }

    void RemoveListener(EventDispatcher& d, std::string event)
    {
        auto it = connections.find(event);
        d.RemoveListener(event, it->second);
        connections.erase(it);
    }

private:
    std::map<std::string, Connection> connections;
};


inline void Fun(const MouseEvent&)// e)
{

}

//template <typename EventType>
//inline EventDispatcher::ListenerFunction Bind(std::function<void(const EventType&)> F)
//{
//    //std::function<void(const MouseEvent&)> F = std::bind(&MouseSubscriber::React, this, std::placeholders::_1);
//    return std::bind(WrapCall<decltype(F), Event>, F, std::placeholders::_1);
//}

template <typename Class, typename EventType>
inline EventDispatcher::ListenerFunction Bind(void(Class::*mf)(const EventType&), Class* instance)
{
    std::function<void(const EventType&)> F = std::bind(mf, instance, std::placeholders::_1);
    return std::bind(WrapCall<decltype(F), Event>, F, std::placeholders::_1);
}

class MouseSubscriber: public Subscriber
{
public:
    void React(const MouseEvent& e)
    //void React(const Event& e)
    {
        if (e.Type() != "On")
        {
            assert(0);
            return;
        }
        //const MouseEvent& xe = static_cast<const MouseEvent&>(e);
        std::cout << "x=" << e.x << " " << "y=" << e.y << std::endl;
    }
    void React1(const Event& e)
    {
        if (e.Type() != "OnEx")
        {
            assert(0);
            return;
        }
        const MouseEXEvent& xe = static_cast<const MouseEXEvent&>(e);
        std::cout << "x=" << xe.x << " " << "y=" << xe.y << " " << "z=" << xe.z << std::endl;
    }

    void Init()
    {
    }

    void Register(MouseDispatcher& md)
    {
        //AddListener(md, "On", std::bind(&MouseSubscriber::React, this, std::placeholders::_1));
        //AddListener(md, "On", std::bind(WrapCall<decltype(&MouseSubscriber::React), Event>, &MouseSubscriber::React, this, std::placeholders::_1));
        
        //std::function<void(const MouseEvent&)> F = std::bind(&MouseSubscriber::React, this, std::placeholders::_1);
        //AddListener(md, "On", std::bind(WrapCall<decltype(F), Event>, F, std::placeholders::_1));

        //AddListener(md, "On", Bind<MouseEvent>(std::bind(&MouseSubscriber::React, this, std::placeholders::_1)));

        AddListener(md, "On", Bind(&MouseSubscriber::React, this));
    }
    void Unregister(MouseDispatcher& md)
    {
        RemoveListener(md, "On");
    }
    void RegisterEx(MouseDispatcher& md)
    {
        AddListener(md, "OnEx", std::bind(&MouseSubscriber::React1, this, std::placeholders::_1));
    }
    void UnregisterEx(MouseDispatcher& md)
    {
        RemoveListener(md, "OnEx");
    }
};
