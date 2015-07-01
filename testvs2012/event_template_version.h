template <typename EventType>
class EventDispatcher
{
public:
    typedef std::function<void(const EventType&)> ListenerFunction;

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

    void Dispatch(const EventType& e)
    {
        auto it = listeners.find(e.Type());
        ConnectionGroup cg = it->second;
        std::for_each(cg.begin(), cg.end(), 
        [&](Group& g)
        {
            g.function(e);
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

class MouseDispatcher
    //: public EventDispatcher<MouseEvent>
    //, public EventDispatcher<MouseEXEvent>
{
public:
    void MouseOn()
    {
        MouseEvent e("On", 100, 101);
        //EventDispatcher<MouseEvent>::Dispatch(e);
        m.Dispatch(e);
        MouseEXEvent e1("On", 100, 101, 200);
        mex.Dispatch(e1);
    }

    void MouseSuperOn()
    {
        MouseEXEvent e("On", 100, 101, 200);
        //EventDispatcher<MouseEXEvent>::Dispatch(e);
        mex.Dispatch(e);
    }

    /*void AddListener(std::string event, EventDispatcher<MouseEvent>::ListenerFunction function)
    {
        m.AddListener(event, function);
    }*/

    /*void AddListener(std::string event, EventDispatcher<MouseEXEvent>::ListenerFunction function)
    {
        mex.AddListener(event, function);
    }*/

    EventDispatcher<MouseEvent> m;
    EventDispatcher<MouseEXEvent> mex;
};

template <typename Dispatcher>
class Subscriber
{
public:
    void AddListener(Dispatcher& d, std::string event, typename Dispatcher::ListenerFunction function)
    {
        if (connections.find(event) != connections.end())
        {
            return;
        }

        connections[event] = d.AddListener(event, function);
    }

    void RemoveListener(Dispatcher& d, std::string event)
    {
        auto it = connections.find(event);
        d.RemoveListener(event, it->second);
        connections.erase(it);
    }

private:
    std::map<std::string, Connection> connections;
};

class MouseSubscriber
    //: public Subscriber<EventDispatcher<MouseEvent>>
{
public:
    void React(const MouseEvent& e)
    {
        if (e.Type() != "On")
        {
            assert(0);
            return;
        }
        std::cout << "x=" << e.x << " " << "y=" << e.y << std::endl;
    }
    void React1(const MouseEXEvent& e)
    {
        if (e.Type() != "On")
        {
            assert(0);
            return;
        }
        std::cout << "x=" << e.x << " " << "y=" << e.y << " " << "z=" << e.z << std::endl;
    }

    void Init()
    {
    }

    void Register(MouseDispatcher& md)
    {
        sm.AddListener(md.m, "On", std::bind(&MouseSubscriber::React, this, std::placeholders::_1));
    }
    void Unregister(MouseDispatcher& md)
    {
        sm.RemoveListener(md.m, "On");
    }
    void RegisterEx(MouseDispatcher& md)
    {
        smex.AddListener(md.mex, "On", std::bind(&MouseSubscriber::React1, this, std::placeholders::_1));
    }
    void UnregisterEx(MouseDispatcher& md)
    {
        smex.RemoveListener(md.mex, "On");
    }

    Subscriber<EventDispatcher<MouseEvent>> sm;
    Subscriber<EventDispatcher<MouseEXEvent>> smex;
};
