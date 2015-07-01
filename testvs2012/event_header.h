class Event
{
public:
    Event(const std::string& type): type(type) {}
    const std::string& Type() const { return type; }

private:
    std::string type;
};

class Connection
{
public:
    Connection()
        : uuid(GetUUID())
    {

    }
    bool operator== (const Connection& connection) const
    {
        return uuid == connection.uuid;
    }

private:
    static int GetUUID()
    {
        static int counter = 0;
        if (counter == 0xFFFF)
        {
            counter = 0;
        }
        return ++counter;
    }
    int uuid;
};

class MouseEvent : public Event
{
public:
    MouseEvent(const std::string& type, int x, int y)
        : Event(type)
        , x(x)
        , y(y)
    {

    }

public:
    int x;
    int y;
};

class MouseEXEvent : public Event
{
public:
    MouseEXEvent(const std::string& type, int x, int y, int z)
        : Event(type)
        , x(x)
        , y(y)
        , z(z)
    {

    }

public:
    int x;
    int y;
    int z;
};
