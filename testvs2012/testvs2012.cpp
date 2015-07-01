#include "stdafx.h"
#pragma warning(disable : 4100 4189 4244 4127 4101)
#pragma warning(disable : 4512) // '=' can't be generated
#include <map>
#include <iostream>
#include <vector>
#include <memory>
#include <scoped_allocator>
#include <typeinfo>
#include <type_traits>
#include "database.h"
#include "world.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <functional>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <ctime>
#include <iterator>

#include "test_specialize_float.h"
#include "Debug.h"

void function1(int* pint)
{
    *pint = 10;
}

template <typename T>
class mapper
{
public:
    static T something;
    T somethingelse;
};

template <typename T>
T mapper<T>::something;
//

auto xxaa = 4;

#define ToString(x) #x

//template<class T, class... U>
//std::unique_ptr<T> make_unique(U&&... u)
//{
//    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
//}

class TA
{
public:
    TA(int a, int b, bool c) {}
};
class TB
{
public:
    TB(std::string abc, int def) {}
};
//template <typename... T>
//void testsomething(T&&... t)
//{
//    T obj(std::forward<T>(t)...));
//    std::cout << "a" << std::endl;
//}
template <typename T, typename P1>
void make(P1 p1)
{
    T obj(p1);
    std::cout << "a2" << std::endl;
}
template <typename T, typename P1, typename P2>
void make(P1 p1, P2 p2)
{
    T obj(p1, p2);
    std::cout << "a3" << std::endl;
}
template <typename T, typename P1, typename P2, typename P3>
void make(P1 p1, P2 p2, P3 p3)
{
    T obj(p1, p2, p3);
    std::cout << "a4" << std::endl;
}

//template <typename T>
//std::string ComponentType<T>::name = ToString(T);

int ComponentTypeCounter::typeCounter = 0;

template <typename T>
ComponentType<T> Component<T>::type;

class ForStatic
{
public:
    ForStatic()
    {
        aa = 1024;
        std::cout << "a" << std::endl;
    }
    int aa;
};

void ActivateForStatic()
{
    static ForStatic forstatic;
    forstatic.aa = 2024;
}

template <typename Tp>
class SimpleAllocator
{
public:
    typedef Tp value_type;
    typedef Tp* pointer;

    template <typename U>
    struct rebind
    {
        typedef SimpleAllocator<U> other;
    };

    SimpleAllocator() {}
    template <typename U>
    SimpleAllocator(const SimpleAllocator<U>& other) {}

    Tp* allocate(std::size_t n)
    {
        Tp* t = (Tp*) malloc(n * sizeof(Tp));
        std::cout
                << "used my_allocator to allocate at address "
                << t << " (+) size = "
                << n
                << std::endl;
        return t;
    }
    void deallocate(Tp* p, std::size_t n)
    {
        if (p)
        {
            free(p);
            std::cout
                    << "used my_allocator to deallocate at address "
                    << p << " (-) size = "
                    << n
                    << std::endl;
        }
    }

    void construct(pointer p, const Tp& val)
    {
        std::cout
                << "construct address"
                << p
                << " for value = "
                //<< val
                << std::endl;

        new((Tp*) p) Tp(val);
    }
    void destroy(pointer p)
    {
        std::cout
                << "destruct address"
                << p
                << std::endl;

        p->~Tp();
    }
};

#if 0
template<typename T>
class MyAllocator
{
public :
    //    typedefs

    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public :
    //    convert an allocator<T> to allocator<U>

    template<typename U>
    struct rebind
    {
        typedef MyAllocator<U> other;
    };

public :
    inline explicit MyAllocator() {}
    inline ~MyAllocator() {}
    inline explicit MyAllocator(MyAllocator const&) {}
    template<typename U>
    inline explicit MyAllocator(MyAllocator<U> const&) {}

    //    address

    inline pointer address(reference r)
    {
        return &r;
    }
    inline const_pointer address(const_reference r)
    {
        return &r;
    }

    //    memory allocation

    inline pointer allocate(size_type cnt,
                            typename std::allocator<void>::const_pointer = 0)
    {
        std::cout << "Trying to allocate " << cnt << " objects in memory" << std::endl;
        pointer new_memory = reinterpret_cast<pointer>(::operator new(cnt * sizeof(T)));
        std::cout << "Allocated " << cnt << " objects in memory at location:" << new_memory << std::endl;
        return new_memory;
    }
    inline void deallocate(pointer p, size_type n)
    {
        ::operator delete(p);
        std::cout << "Deleted " << n << " objects from memory" << std::endl;
    }
    //    size
    inline size_type max_size() const
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    //    construction/destruction

    inline void construct(pointer p, const T& t)
    {
        std::cout << "Constructing at memory location:" << p << std::endl;
        new(p) T(t);
    }
    inline void destroy(pointer p)
    {
        std::cout << "Destroying object at memory location:" << p << std::endl;
        p->~T();
    }

    inline bool operator==(MyAllocator const&)
    {
        return true;
    }
    inline bool operator!=(MyAllocator const& a)
    {
        return !operator==(a);
    }

    //typedef integral_constant<bool, true> true_type;
    //typedef integral_constant<bool, false> false_type;
    //typedef false_type propagate_on_container_copy_assignment;
    //typedef false_type propagate_on_container_move_assignment;
    //typedef false_type propagate_on_container_swap;

    MyAllocator<T> select_on_container_copy_construction() const
    {
        // return this allocator
        return (*this);
    }
};    //    end of class MyAllocator
#else
template<typename T>
class MyAllocator
{
public :
    //    typedefs

    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public :
    //    convert an allocator<T> to allocator<U>

    template<typename U>
    struct rebind
    {
        typedef MyAllocator<U> other;
    };

public :
    MyAllocator() {}

    template<typename U>
    MyAllocator(MyAllocator<U> const&) {}

    //    address

    pointer address(reference r)
    {
        return &r;
    }
    const_pointer address(const_reference r)
    {
        return &r;
    }

    //    memory allocation

    pointer allocate(size_type cnt,
                     typename std::allocator<void>::const_pointer = 0)
    {
        std::cout << "Trying to allocate " << cnt << " objects in memory" << std::endl;
        pointer new_memory = reinterpret_cast<pointer>(::operator new(cnt * sizeof(T)));
        std::cout << "Allocated " << cnt << " objects in memory at location:" << new_memory << std::endl;
        return new_memory;
    }
    void deallocate(pointer p, size_type n)
    {
        ::operator delete(p);
        std::cout << "Deleted " << n << " objects from memory" << std::endl;
    }
    //    size
    size_type max_size() const
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    //    construction/destruction

    void construct(pointer p, const T& t)
    {
        std::cout << "Constructing at memory location:" << p << std::endl;
        new(p) T(t);
    }
    void destroy(pointer p)
    {
        std::cout << "Destroying object at memory location:" << p << std::endl;
        p->~T();
    }

    bool operator==(MyAllocator const&)
    {
        return true;
    }
    bool operator!=(MyAllocator const& a)
    {
        return !operator==(a);
    }
};    //    end of class MyAllocator
#endif

struct ABD
{
    ABD(int newoops): oops(newoops)
    {
        std::cout << "ABD c address = " << this << " value = " << oops << std::endl;
    }
    ~ABD()
    {
        std::cout << "ABD D address = " << this << " value = " << oops << std::endl;
    }
    int oops;
};

//template<typename T>
//using MyIntVec = std::vector<T>;

template <typename T>
class MyVector
{
public:
    typedef typename std::vector<T>::iterator Iterator;

    void PushBack(const T& val)
    {
        underneath.push_back(val);
    }

    Iterator Begin()
    {
        return underneath.begin();
    }

    Iterator End()
    {
        return underneath.end();
    }

private:
    std::vector<T> underneath;
};

template<class T>
struct my_is_ptr
{
    enum { value = 0 };
};

template<class T>
struct my_is_ptr<T*>
{
    enum { value = 1 };
};

class uuuu
{
public:
    int getaa()
    {
        return aa;
    }
    int aa;
    int ba;
    int ca;
};

template <typename T>
void tryfunction(void* mem)
{
    T* ptr = reinterpret_cast<T*>(mem);
    std::cout << "a" << std::endl;
}

template <typename T>
struct tembase
{
    int tembase_g;
    void DO()
    {
        tryfunction<T>(static_cast<T*>(this));
    }
};

struct temderi : public tembase<temderi>
{
    int temderi_g;
};

template <typename T>
class schauen
{
public:
    schauen(): inited(false)
    {}

    virtual void DoIt() {}
    void Execute()
    {
        if (!inited)
        {
            std::cout << typeid(T).name() << std::endl;
            DoIt();
            inited = true;
        }
    }

    bool inited;
};

class aufgabe : public schauen<aufgabe>
{
public:
    aufgabe() {};

    virtual void DoIt()
    {
        std::cout << "aufgabe dodo" << std::endl;
    }
};

enum TestEnum
{
    ABC = 0,
    DEF = 1,
    ZZZ = 999,
};
template <typename T, TestEnum U, bool F = true>
class lesen
{
public:
    lesen(): ghi(U)
    {
    }

    static void calcoffset()
    {
        //static int offset = &(lesen::rrr) - &(lesen::abc);
        //int offset2= &(rrr) - &(abc);
        //dodo();
        std::cout << (&lesen::rrr) << std::endl;
        std::cout << "omg" << std::endl;
    }

    void dodo()
    {
        if (F)
        {
            //F = false;
        }
        abc++;
        std::cout << "omg" << std::endl;
    }

    int abc;
    int rrr;
    T def;
    TestEnum ghi;
};

class hoeren
{
public:
    hoeren()
    {
    }

    static void dodo()
    {
        //int offset = (&hoeren::xx) - (&hoeren::yy);

        std::cout << (&(((hoeren*)0)->*(&hoeren::xx))) << std::endl;
        std::cout << (&(((hoeren*)0)->*(&hoeren::yy))) << std::endl;
        //std::cout << (&hoeren::yy) << std::endl;
        std::cout << "omg" << std::endl;
    }

private:
    int xx;
    int yy;

};

void functionneedvoid(void* wow)
{
    if (1)
    {
        static int ggg = 1000;
    }
    std::cout << wow << std::endl;
}

struct HvBitset
{
    typedef std::bitset<32> rt;
};

struct podabc
{
    int a;
    int b;
};
void podabcde(const podabc& ok)
{
    std::cout << "a" << std::endl;
}

template <typename T>
class asbase
{
public:
    int a;
    void print()
    {
        std::cout << typeid(T).name() << std::endl;
    }
};
template <typename T>
class rrenderComponent : public asbase<rrenderComponent<T>>
{
    int abcd;
    T efgj;
};
template <typename T>
class Component123 : public asbase<T>
{

};

template <typename T>
class systembase
{
public:
    virtual void oninsert()
    {

    }
    virtual void onremove()
    {

    }
    void print()
    {
        baseint = 1234;
        std::cout << typeid(T).name() << "->base" << std::endl;
    }
    int baseint;
};

template <typename T>
class lightsystem : public systembase<lightsystem<T>>
{
public:
    virtual void oninsert()
    {
        baseint = 9999;
        std::cout << typeid(T).name() << "lightsystem" << std::endl;
    }
    virtual void onremove()
    {
        std::cout << typeid(T).name() << "lightsystem" << std::endl;
    }
};

template <>
void lightsystem<int>::oninsert()
{
    baseint = 5678;
    std::cout << "100_lightsystem" << std::endl;
};

template <>
void lightsystem<float>::oninsert()
{
    baseint = 9876;
    std::cout << "1.0f_lightsystem" << std::endl;
};

template <typename T, bool b1, bool b2>
class factoryuserr
{
public:
    void test()
    {
        std::cout << "1" << std::endl;
    }
    void test1()
    {
        std::cout << "100" << std::endl;
    }
};

template<>
void factoryuserr<int, true, true>::test()
{
    std::cout << "2" << std::endl;
}

template <typename T, bool B>
class Entitee
{
public:
    Entitee()
    {}

    void Do()
    {
        dosomething<B>();
    }

    template <bool b>
    void dosomething()
    {
        std::cout << "boolean" << std::endl;
    }

    template <>
    void dosomething<true>()
    {
        T::Krkr();
        std::cout << "cccccccccccccccc" << std::endl;
    }
};

class Aantitee : public Entitee<Aantitee, true>
{
public:
    static void Krkr()
    {
        std::cout << "krkr" << std::endl;
    }
};
class Bentitee : public Entitee<Bentitee, false>
{
public:
    void lar()
    {
        std::cout << "lar" << std::endl;
    }

};

template
<
    typename T,
    bool usingTypeFields = false,
    bool usingAutoRegister = false,
    /*
        if isDerivedClass == true, Super should be T's base
    */
    bool isDerivedClass = false,
    typename Super = T
    >
class FactoryUser
{
public:
    //static TypeInfo& StaticTypeInfo()
    static double StaticTypeInfo()
    {
        static double instance = 100;//CreateTypeInfo<T>(T::ClassName());
        static bool inited = false;
        if (!inited)
        {
            TestAutoRegister<usingAutoRegister>(instance);
            TestInheritance<isDerivedClass>(instance);
            TestFieldAdding<usingTypeFields>(instance);
            inited = true;
        }
        return instance;
    }

    template<bool enable>
    static void TestAutoRegister(double instance)//TypeInfo& instance) {}
    {

    }
    template<>
    static void TestAutoRegister<true>(double instance)//(TypeInfo& instance) { instance.EnableAutoRegisterInstance(); }
    {
        std::cout << "TestAutoRegister" << std::endl;
    }

    template<bool enable>
    static void TestInheritance(double instance)//TypeInfo& instance) {}
    {

    }
    template<>
    static void TestInheritance<true>(double instance)//TypeInfo& instance) { instance.Inherit(Super::StaticTypeInfo()); }
    {
        std::cout << "TestInheritance" << std::endl;
    }

    template<bool enable>
    static void TestFieldAdding(double instance)//TypeInfo& instance)
    {}
    template<>
    static void TestFieldAdding<true>(double instance)//TypeInfo& instance)
    {
        static std::vector<int> fields;
        T::AddFields(fields);
        //instance.SetTypeFields(fields);
        instance = 200;
        std::cout << "TestFieldAdding" << std::endl;
    }
};

class Wentity : public FactoryUser<Wentity, false, true>
{
public:
    void DoDo()
    {
        StaticTypeInfo();
    }
};

class VCom
{
public:
    VCom(): a(-1) {}
    VCom(int na): a(na) {}
    int a;
};
class VSOBase
{
public:
    virtual void Do(VCom* v) = 0;
};
class VComManager
{
public:
    VComManager()
    {
        vs.resize(10);
        for (size_t i = 0; i < 10; ++i)
        {
            vs[i] = int(i);
        }
    }
    void Accept(VSOBase* vb)
    {
        for (VCom& v : vs)
        {
            vb->Do(&v);
        }
    }
    std::vector<VCom> vs;
};
class VSO : public VSOBase
{
public:
    VSO(): sum(0) {}
    void Do(VCom* v) override
    {
        sum += v->a;
    }

    int sum;
};

class testparam
{
public:
    testparam(int abc): abc(abc)
    {

    }
    int abc;
};

void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int g(int n1)
{
    return n1;
}

struct Foo
{
    Foo(int num): num_(num), data(10) {}
    Foo(): num_(1), data(10) {}

    void print_add(int i) //const
    {
        std::cout << num_ + i << '\n';
    }
    void print_sum(int n1, int n2)
    {
        std::cout << n1 + n2 << '\n';
    }

    int num_;
    int data;// = 10;
};



void print_num(int i)
{
    std::cout << i << '\n';
}

struct PrintNum
{
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};

class Com1
{
public:
    int abcd;
    void print()
    {
        abcd = 1234;
        std::cout << abcd << std::endl;
    }
};
class Com2
{
public:
    int efghi;
    double jkl;
    void print()
    {
        efghi = 321;
        std::cout << efghi << std::endl;
        jkl = 11;
        std::cout << jkl << std::endl;
    }
};
class Com3
{
public:
    float mnop[2];
    std::string qrst;
    void print()
    {
        mnop[0] = 99.0f;
        mnop[1] = 100.0f;
        std::cout << mnop[0] << " " << mnop[1] << std::endl;
    }
};
class ComDatabase
{
public:

    template <typename T>
    void add()
    {
        T com;
        get<T>().push_back(com);
        com.print();
    }

    template <typename T>
    std::vector<T>& get()
    {
        static std::vector<T> coms;
        return coms;
    }
};

class roar
{
public:
    int j;
};
template<typename T>
class rsystem
{
public:
    T abc;
};
class roar;
void dorsys(rsystem<roar>* obj)
{
    std::cout << obj->abc.j << std::endl;
}


class tryrealcont
{
public:
    template <typename T>
    void getstatic()
    {
        static int stadt = 1234;
        ++stadt;
        static T another;
        another += 1;
    }

    void wtf()
    {
        static int gee = 55;
        ++gee;
    }

    int az;
};

struct indexcombo
{
    indexcombo(int aa, int bb, int& cc):
        a(aa), b(bb), c(cc)
    {

    }
    indexcombo(const indexcombo& rhs):
        a(rhs.a), b(rhs.b), c(rhs.c)
    {

    }
    int a;
    int b;
    int& c;
};

class combat
{
public:
    /*void operator= (const combat& rhs)
    {
        abc = rhs.abc;
    }*/

    int abc;
};
class dcombat1 : public combat
{
public:
    int def;

};
class dcombat2 : public combat
{
public:
    void operator= (const dcombat2& rhs)
    {
        //combat::operator=(rhs);
        gg = rhs.gg;
        kk = 100;
        ll = 101;
    }

    int gg;
    int kk;
    int ll;

};

#include "event_header.h"
//#include "event_template_version.h"
#include "event_inheritance_version.h"

class AA
{

};

class BB : public AA
{

};

void FB(const BB& b)
{
    std::cout << "abcd" << std::endl;
}

using std::placeholders::_1;


class vdtor
{
public:
    virtual ~vdtor() = 0;
    void dodo()
    {
        std::cout << abc << std::endl;
    }

    int abc;
};

vdtor::~vdtor()
{

}

class conder : public vdtor
{
public:
    conder(): gg(123) {}
    int gg;
};

std::vector<int> foreachthing(std::function<void(int&)> f)
{
    std::vector<int> ints(10, 12);
    // 10­Ó12
    std::for_each(ints.begin(), ints.end(), f);
    return ints;
}

void magicsetter(void* val)
{
    decltype(val) a = static_cast<decltype(val)*>(val);
    std::cout << a << std::endl;
}

class Testobj
{
public:
    Testobj(int val)
        : ptr(new int(val))
    {

    }

    ~Testobj()
    {
        delete ptr;
    }

    Testobj(Testobj&& other)
        : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    void operator= (Testobj&& other)
    {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    int* get()
    {
        return ptr;
    }

private:
    Testobj(const Testobj& other)
    {

    }
    void operator= (const Testobj& other)
    {

    }
    int* ptr;
};

enum class Color
{
    RED,
    GREEN,
    BLUE
};
enum class Feelings
{
    EXCITED,
    MOODY,
    BLUE
};

class base1
{
public:
    void do0()
    {
        std::cout << "a0==" << b0 << std::endl;
    }
    void do1()
    {
        std::cout << "a1==" << b1 << std::endl;
    }
    base1(): b0(0), b1(1) {}
    base1(const base1& rhs)
    {
        b0 = 11;
        b1 = 12;
    }
    int b0;
    int b1;
};
class base2
{
public:
    void do2()
    {
        std::cout << "a2==" << b2 << std::endl;
    }
    int b2;
};
class base3
{
public:
    void do3()
    {
        std::cout << "a3==" << b3 << std::endl;
    }
    int b3;
};
class super123
    : public base1
    , public base2
    , public base3
{
public:
    super123()
    {
        b0 = 5;
        b1 = 10;
        b2 = 20;
        b3 = 30;
    }
    //super123(const super123& rhs)
    //    //: base1(rhs)
    //{
    //    b0 = 7;
    //}
    void do123()
    {
        std::cout << "a123" << std::endl;
    }
    int a123;
};

class ebase
{
public:
    ebase()
    {
        std::cout << "ebase ctor" << std::endl;
    }
    /*virtual*/ ~ebase()
    {
        std::cout << "ebase dtor" << abc << std::endl;
    }

    int abc;
};

class ederive1 : public ebase
{
public:
    ederive1()
    {
        std::cout << "ederive 1 ctor" << std::endl;
    }
    ~ederive1()
    {
        std::cout << "ederive 1 dtor" << def << std::endl;
    }

    int def;
};

class ederive2 : public ederive1
{
public:
    ederive2()
    {
        std::cout << "ederive 2 ctor" << std::endl;
    }
    ~ederive2()
    {
        std::cout << "ederive 2 dtor" << jkl << std::endl;
    }

    int jkl;
};

class test99
{
public:
    test99(int a)
        : a(a)
    {

    }
    test99(const test99& r)
        : a(r.a)
    {

    }
    /*void operator=(const test99& r)
    {
        a = r.a;
    }
    void operator=(test99&& r)
    {
        a = r.a;
        r.a = -1;
    }*/
    void operator=(test99 r)
    {
        a = r.a;
        r.a = -1;
    }
    test99(test99&& r)
    {
        a = r.a;
    }
    ~test99()
    {

    }

    int a;
};

class test100 : public test99
{
public:
    test100(int a)
        : test99(a)
    {

    }
    /*test100(test100&& r)
        : test99(std::move(r))
    {

    }*/
};

class trytemplate
{
public:
    template <template<typename, typename> class V, typename U, typename A>
    trytemplate(const V<U, A>& p)
    {
        std::cout << p[0] << " " << p.size() << std::endl;
    }

    template <typename T>
    trytemplate(const T& p)
    {
        std::cout << p << std::endl;
    }

    template <typename T, typename X>
    trytemplate(const T& p, X)
    {
        X* ptr = new X();
        std::cout << p << std::endl;
        delete ptr;
    }
};

template <typename T>
void Fun()
{
    T a = T();
    std::cout << a << std::endl;
}

template <>
void Fun<int>()
{
    std::cout << "GGGG" << std::endl;
}

//template <typename U>
//void Fun<std::vector<U>>() // <-- fail
//{
//    std::vector<U> v;
//    std::cout << v.size() << std::endl;
//}

template <typename T>
class TClass
{
public:
    TClass()
    {

    }
    ~TClass()
    {

    }
    void do1()
    {
        std::cout << "1234" << std::endl;
    }
    template <typename T>
    void do2();
    /*{
        std::cout<<"12345"<<std::endl;
    }*/
};

template <typename T>
template <typename U>
void TClass<T>::do2()
{
    std::cout << "12345" << std::endl;
}

template <>
template <>
void TClass<float>::do2<float>()
{
    std::cout << "12345" << std::endl;
}

class ComponentBase1
{
public:
    ComponentBase1()
    {

    }

    virtual int GetTypeIndex() const = 0;
};
class SystemBase1
{
public:
    SystemBase1(int sss)
        : sss(sss)
    {

    }
    int sss;

    virtual int GetTypeIndex() const = 0;
};

//template <typename Base, typename PType, typename CounterProvider>
//class Counter : public Base
//{
//public:
//    Counter(PType& p): Base(p) {}
//
//protected:
//    static int typeIndexCounter;
//};

template
<
    typename T,
    typename Base,
    typename CounterProvider,
    typename PType = float
    >
class Bridge : public Base
{
public:
    Bridge(PType& p): Base(p) {}
    Bridge(): Base() {}
    virtual ~Bridge() {}

    virtual int GetTypeIndex() const
    {
        return TypeIndex();
    }

    static int TypeIndex()
    {
        static int typeIndex = CounterProvider::Instance().GetIndex<T>();
        return typeIndex;
    }
};

template <typename C>
class CounterProvider
{
public:
    template <typename T>
    int GetIndex()
    {
        auto it = typeIndexes.find(typeid(T));
        if (it != typeIndexes.end())
        {
            return it->second;
        }
        else
        {
            typeIndexes.insert(std::make_pair(std::type_index(typeid(T)), indexCounter++));
            return (indexCounter - 1);
        }
    }

protected:
    CounterProvider()
        : indexCounter(0)
    {

    }

    std::map<std::type_index, int> typeIndexes;
    int indexCounter;
};

class /*dllexport*/ ComponentCounterProvider : public CounterProvider<ComponentCounterProvider>
{
public:
    static ComponentCounterProvider& Instance()
    {
        static ComponentCounterProvider instance;
        return instance;
    }
private:
    ComponentCounterProvider() {}
};
class /*dllexport*/ SystemCounterProvider : public CounterProvider<SystemCounterProvider>
{
public:
    static SystemCounterProvider& Instance()
    {
        static SystemCounterProvider instance;
        return instance;
    }
private:
    SystemCounterProvider() {}
};

class Component001 : public Bridge<Component001, ComponentBase1, ComponentCounterProvider>
{
public:

};
class Component002 : public Bridge<Component002, ComponentBase1, ComponentCounterProvider>
{
public:

};
class Component003 : public Bridge<Component003, ComponentBase1, ComponentCounterProvider>
{
public:

};

class System001 : public Bridge<System001, SystemBase1, SystemCounterProvider, int>
{
public:
    System001(int& gg): Bridge(gg) {}
};
class System002 : public Bridge<System002, SystemBase1, SystemCounterProvider, int>
{
public:
    System002(int& gg): Bridge(gg) {}
};
class System003 : public Bridge<System003, SystemBase1, SystemCounterProvider, int>
{
public:
    System003(int& gg): Bridge(gg) {}
};

template <typename T, bool TF = false>
class TestTemplateParam
{
public:
    TestTemplateParam()
    {
        doo<TF>();
    }

    template <bool b>
    void doo()
    {

        std::cout << "default" << std::endl;
    }
    template <>
    void doo<true>()
    {
        T::something();
        std::cout << "true" << std::endl;
    }

};
class forsomething
{
public:
    static void something()
    {
        std::cout << "yayyy" << std::endl;
    }

    forsomething()
    {

    }
    ~forsomething()
    {

    }
};

template <typename T>
void ttt01(T t)
{
    std::cout << t << std::endl;
}
template <typename T>
void ttt01(T& t)
{
    std::cout << t << std::endl;
}
template <typename T>
void ttt01(T* t)
{
    std::cout << *t << std::endl;
}

void acceptvoid(void* p)
{

}

template <typename T>
void Delete(T*& p)
{
    if (p == nullptr)
    {
        return;
    }
    p->~T();
    acceptvoid(p);
    delete p;
    p = nullptr;
}

template
<
    typename Return,
    typename Input
    >
std::vector<Return> Transform(const std::vector<Input>& inputs)
{
    std::vector<Return> result(inputs.size());
    //std::transform(inputs.begin(), inputs.end(), result.begin(), f);
    return result;
}

//typedef std::vector<> MyVector;

template <typename T>
struct HvVector
{
    typedef std::vector<T> rt;
};

template <typename T>
void wc(typename HvVector<T>::rt p)
{

}

class LetYouDo
{
public:

    template <typename T>
    LetYouDo(std::string s, T* p1)
    {
        std::cout << "1.1" << std::endl;
    }
    template <typename T>
    LetYouDo(std::string s, T* p1, T* p2)
    {
        std::cout << "1.2" << std::endl;
    }

    template<typename CLASS, typename TYPE>
    LetYouDo(const std::string& name, typename HvVector<TYPE>::rt(CLASS::*field), TYPE* p)
    {
        std::cout << "4" << std::endl;
    }

    template<typename CLASS, typename TYPE>
    LetYouDo(const std::string& name, TYPE(CLASS::*field))
    {
        std::cout << "3" << std::endl;
    }

    void Init()
    {
        m[0] = 1;
    }
    void* GetKey() const
    {
        auto it = m.find(0);
        auto p = it->first;
        auto pp = &it->first;
        return const_cast<void*>(reinterpret_cast<const void*>(&it->first));
    }

    std::map<int, int> m;

};

//template <typename T>
//void wc(std::vector<T> p)
//{
//
//}

class Victim
{
public:
    int m1;
    HvVector<int>::rt m2;
};

class STbase
{
public:
    static void yay()
    {

        return;
    }

};
class STDerive : public STbase
{
public:
    STDerive(int a = 0): a(a) {}

    static void grr()
    {

        return;
    }
    void some()
    {
        this;
        std::cout << "a" << std::endl;
    }
    void do1(STDerive* p)
    {
        if (m.find(this) == m.end())
        {
            std::cout << "a" << std::endl;
        }
        p->a = 123;
        std::cout << "a" << std::endl;
    }

    int a;
    std::map<STDerive*, STDerive*> m;
};

class ABCD
{
public:
    int a1()
    {
        //return a;
        return 0;
    }
    int a;
};

//uint FindKeyIndexAtTime(const Entity& entity, float time)
//{
//    std::vector<KeyType>& keyArr = GetCurrentKeyArray( entity );
//
//    uint lens = keyArr.Size();
//    for( uint i=0; i<lens; ++i )
//    {
//        float diff = fabs(time - keyArr[i].GetTime()); // will fabs affect performance badly?
//        if ( diff < FLT_EPSILON)
//            return i;
//    }
//
//    return ETimelineErrorCode::KEY_NOT_FOUND;
//
//
//}
//uint FindKeyIndexAtTime(const Entity& entity, float time)
//{
//    std::vector<KeyType>& keyArr = GetCurrentKeyArray( entity );
//
//    auto it = std::find_if(keyArr.begin(), keyArr.end(),
//    [=](const KeyType& k)
//    {
//        return fabs(time - k.GetTime()) < FLT_EPSILON;
//    });
//
//    return (it-keyArr.begin());
//}
//
//
//
//
//bool HasKeyIndexAtTime(const Entity& entity, float time)
//{
//    auto it = std::find_if(keyArr.begin(), keyArr.end(),
//    [=](const KeyType& k)
//    {
//        return fabs(time - k.GetTime()) < FLT_EPSILON;
//    });
//
//    return it != keyArr.end();
//}

class classA
{

};
class classB
{

};
class absClass
{
public:
    // ...
    // instead of templating the absClass fun method, define the different
    // overloads that are going to be used:
    virtual void fun(classA a) = 0;
    virtual void fun(classB b) = 0;
};

class impClass : public absClass
{
public:
    // ...
    template <typename T>
    void fun(T t)
    {
        /* whatever */
    }

    // declaration
    void fun(classA a)
    {

    }
    void fun(classB b)
    {

    }
};

template
void impClass::fun<classA>(classA t);

template
void impClass::fun<classB>(classB t);

void eatchar(char c)
{
    const char* cc = &c;
    std::string s(cc);
}

class wtfref
{
public:
    int ww;
    virtual ~wtfref()
    {
        std::cout << "1" << std::endl;
    }
    void do1()
    {
        ww = 10;
    }
};
class wtfref2
{
public:
    int ww2;
    virtual ~wtfref2()
    {
        std::cout << "2" << std::endl;
    }
};
class whoa : public wtfref, public wtfref2
{
public:
    int wwaa;
    virtual ~whoa()
    {
        std::cout << "100" << std::endl;
    }
};

namespace detail
{
/*template<typename T1, typename T2>
std::ostream& print_elem(std::ostream &out, std::pair<T1, T2> const &mp)
{
    return (out << "(" << mp.first << ", " << mp.second << ")");
}
template<typename T>
std::ostream& print_elem(std::ostream &out, T const &elem)
{
    return (out << elem);
}*/

template<typename T>
auto print_elem(T it) -> typename T::value_type
{
    return *it;
}
template<typename T1, typename T2>
auto print_elem(std::pair<T1, T2> it) -> typename std::pair<T1, T2>::second_type
{
    return it->second;
}
}

//template<typename T>
//struct extract
//{
//    static auto ppp(const T& t) -> T
//    {
//        return t;
//    }
//};
//template<typename T1, typename T2>
//struct extract<std::pair<T1, T2>>
//{
//    static auto ppp(const std::pair<T1, T2>& r) -> T2
//    {
//        return r.second;
//    }
//};
namespace extract
{
template <typename T1, typename T2>
const T2& e(const std::pair<T1, T2>& r)
{
    return r.second;
}

template <typename T>
const T& e(const T& r)
{
    return r;
}
}

template<typename Iterator>
void print(Iterator begin, Iterator end)
{
    while (begin != end)
    {
        std::cout << extract::e(*begin) << std::endl;
        ++begin;
    }
}

struct noncbutm
{
    noncbutm() {}
    noncbutm(noncbutm&&) {}
    void operator=(noncbutm&&) {}

private:
    noncbutm(noncbutm&) {}
    void operator=(noncbutm&) {}
};

class MEEBO
{
public:
    MEEBO()
    //: enabled(true)
    //, var(1234)
    {

    }
    bool enabled;
    int var;
};

class FOOFOO
{
public:
    void foo(int foo)
    {
        foo_ = foo;
    }
    int foo()
    {
        return foo_;
    }
    int foo_;
};

class RGBB
{
public:
    RGBB(int r, int g, int b)
    {
        colors[0] = r;
        colors[1] = g;
        colors[2] = b;
    }

    int operator[](int index)
    {
        // you can check index is not exceeding 2, if you want
        return colors[index];
    }

    int getColor(int index)
    {
        // you can check index is not exceeding 2, if you want
        return colors[index];
    }

private:
    int colors[3];
};

class NonCopyable
{
protected:
    NonCopyable() {}
    ~NonCopyable() {}

private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator= (const NonCopyable&);
};

class CopyMe : NonCopyable
{
public:
    CopyMe() {}
    int cm;

private:
    //CopyMe(const CopyMe&){}
};

class BaseToCopy
{
public:
    BaseToCopy()
    {

    }
    ~BaseToCopy()
    {

    }
    BaseToCopy(const BaseToCopy& btc)
    {
        a = btc.a;
    }
    BaseToCopy(BaseToCopy&& btc)
    {
        a = btc.a;
    }
    void operator=(const BaseToCopy& btc)
    {
        a = btc.a;
    }
    void operator=(BaseToCopy&& btc)
    {
        a = btc.a;
    }
    int a;
    virtual void do1() = 0;
};
class DeriveToCopy : public BaseToCopy
{
public:
    DeriveToCopy(int b) : b(b)
    {

    }
    ~DeriveToCopy()
    {

    }
    DeriveToCopy(const DeriveToCopy& dtc) : BaseToCopy(dtc)
    {
        b = dtc.b;
    }
    DeriveToCopy(DeriveToCopy&& dtc) : BaseToCopy(std::move(dtc))
    {
        b = dtc.b;
    }
    void operator=(const DeriveToCopy& dtc)
    {
        BaseToCopy::operator=(dtc);
        b = dtc.b;
    }
    void operator=(DeriveToCopy&& dtc)
    {
        BaseToCopy::operator=(dtc);
        b = dtc.b;
    }
    //void operator=(DeriveToCopy dtc)
    //{
    //    BaseToCopy::operator=(dtc);
    //    b = dtc.b;
    //}
    int b;
    void do1() override {}
};
class Simple
{
public:
    Simple(int i) : i(i) {}
    int i;
};

void matrixSum(float** pOutSum, float** pMatrixA, float** pMatrixB, int iDim1, int iDim2)
{
    for (int i = 0; i < iDim1; i++)
    {
        for (int j = 0; j < iDim2; j++)
        {
            pOutSum[i][j] = pMatrixA[i][j] + pMatrixB[i][j];
        }
    }
}

void goodMatrixSum(float* pOutSum, float* pMatrixA, float* pMatrixB, int iDim1, int iDim2)
{
    for (int i = 0; i < iDim1; i++)
    {
        float* result = (pOutSum + i * iDim1);
        float* rowA = (pMatrixA + i * iDim1);
        float* rowB = (pMatrixB + i * iDim1);
        for (int j = 0; j < iDim2; j++)
        {
            result[j] = rowA[j] + rowB[j];
            std::cout << i << " " << j << std::endl;
        }
    }
}

void arraySum(float* pOutSum, float* pMatrixA, int iDim2)
{
    for (int j = 0; j < iDim2; j++)
    {
        pOutSum[j] = pMatrixA[j]++;
    }
}

void boom(void)
{
    float matrixA[4][4] =
    {
        {1.0f, 1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f, 1.0f}
    };
    float matrixB[4][4] =
    {
        {2.0f, 2.0f, 2.0f, 2.0f},
        {2.0f, 2.0f, 2.0f, 2.0f},
        {2.0f, 2.0f, 2.0f, 2.0f},
        {2.0f, 2.0f, 2.0f, 2.0f}
    };
    float matrixC[4][4];
    //matrixSum((float**)matrixC, (float**)matrixA, (float**)matrixB, 4, 4);
    goodMatrixSum(matrixC[0], matrixA[0], matrixB[0], 4, 4);

    float arrayA[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float arrayC[4];
    arraySum(arrayC, arrayA, 4);
}

class Something1 //: public NonCopyable
{
public:
    Something1(int& r): s(1122), r(r) {}

    int s;
    int& r;
};

//#define ABC1
#define ABC2

template <typename T>
class CRTPP
{
public:
    CRTPP()
    {
        f = std::bind(&CRTPP::Gay, this);
    }

    virtual void Gay()
    {
        std::cout << "12345" << std::endl;
    }
    void Do()
    {
        f();
    }
    std::function<void()> f;
};

class HelloCR : public CRTPP<HelloCR>
{
public:
    void Gay() override
    {
        std::cout << "Gay" << std::endl;

    }
};

void DOVECTOR(std::vector<int>& v)
{
    std::cout << v.size() << std::endl;
}
void DOVECTOR(std::vector<bool>& v)
{
    std::cout << v.size() << std::endl;
}
void DOVECTOR(std::vector<float>& v)
{
    std::cout << v.size() << std::endl;
}
template <typename T>
class EffectCommand
{
public:
    EffectCommand() {}

    void Yay()
    {
        std::vector<T> v;
        DOVECTOR(v);
    }
};

template <typename T>
class AAAAA
{
public:
    int currPlayKeyIdx; // self
    T* currKeyValue; // self
};

template <>
class AAAAA<float>
{
public:
    double haha;
};

struct Info
{
    int a;
    int b;
    double c;
    double d;
    int e;
};

struct CompareInfo
{
    bool operator()(const Info& lhs, const Info& rhs) const
    {
        return (lhs.a < rhs.a) && (lhs.b < rhs.b);
    }
};

typedef std::pair<int, int> Pairs;

Info MakeInfo(Pairs p)
{
    Info i = {p.first, p.second, 0, 0, 0};
    return i;
}

template <typename T>
class Ptr
{
public:
    Ptr(T* p): p_(p) {}
    T* p_;
};

template <typename T>
void TheHeck(T& p)
{
    p += 1;
    std::cout << p << std::endl;
}

void TheHeck(int& p)
{
    std::cout << "theeeeeeeeeee" << p << std::endl;
}

template<class T>
T foo2(T t, typename std::enable_if<std::is_reference<T>::value>::type* = 0)
{
    std::cout << "kiwi" << t << std::endl;
    return t;
}

void fooo(int z)
{
    ++z;
}

class HHH
{
public:
    HHH() {}
    int a;
    static HHH b;
    //virtual void dooo() = 0;
};
HHH HHH::b;

class HHH1
{
public:
    HHH1()
    {
        init();
    }
    void init()
    {
        dooo();
    }
    virtual void dooo() = 0;
};
class HHHD : public HHH1
{
public:
    virtual void dooo()
    {
        std::cout << "1" << std::endl;
    }
    int a;
};

template <typename T1, typename T2>
class A
{
public:
    A(T1 a1, T2 a2): a1(a1), a2(a2) {}

    T1 a1;
    T2 a2;
};

using namespace std;
class myclass
{
public:
    //_load_event_handler
    typedef std::function<void()> Function;
    vector<Function> _handler_one;
    vector<Function> _handler_two;
    vector<Function> _handler_three;

    void register_for_load_event(Function fun)
    {
        this->_handler_three.push_back(fun);
    }

    void register_for_dowork_event(Function fun)
    {
        this->_handler_one.push_back(fun);
    }
    void register_for_end_event(Function fun)
    {
        this->_handler_two.push_back(fun);
    }
    void run(char** fileNames)
    {
        for (int i = 0; i < _handler_one.size(); i++)
        {
            _handler_one[i]();
        }


        for (int i = 0; i < _handler_two.size(); i++)
        {
            _handler_two[i]();
        }


        for (int i = 0; i < _handler_three.size(); i++)
        {
            _handler_three[i]();
        }
    }


};

class myclass_2
{
public:
    myclass* ptrmyclass;
    void load(void)
    {
        cout << "load function start" << endl;

        //some code here
    }
    myclass_2(myclass* _ptrmyclass)
    {
        ptrmyclass = _ptrmyclass;
        ptrmyclass->register_for_load_event(bind(&myclass_2::load, this));

    }
    void foo(vector<string> vect)
    {
        cout << "is stop word called" << endl;
    }
};

class B1
{
public:
    void bo1()
    {
        cout << "bo1" << endl;
    }
    int b1;
};
class B2
{
public:
    void bo2()
    {
        cout << "bo2" << endl;
    }
    int b2;
};
class D1
    : private B1
    , private B2
{
public:
    D1() {}
    int d1;
    void do1()
    {
        bo1();
        bo2();
    }
};

//template <typename T, typename Predicate, typename Operation>
//void ForHierarchy(T entity, Predicate pred, Operation op)
//{
//    if (pred(entity))
//    {
//        op(entity);
//    }
//}
//template <typename T, typename Predicate, typename Operation>
//void ForHierarchy(const T& entity, Predicate pred, Operation op)
//{
//    if (pred(entity))
//    {
//        op(entity);
//    }
//}
template <typename T, typename Predicate, typename Operation>
void ForHierarchy(T& entity, Predicate pred, Operation op)
{
    //ForHierarchy(const_cast<const T&>(entity), pred, op);
    if (pred(entity))
    {
        op(entity);
    }
}

//template <typename T, typename Predicate, typename Operation>
//void ForHierarchy(T&& entity, Predicate pred, Operation op)
//{
//    if (pred(std::forward<T>(entity)))
//    {
//        op(std::forward<T>(entity));
//    }
//
//    // and blah
//}

//template <typename Predicate, typename Operation>
//void ForHierarchy(int& entity, Predicate pred, Operation op)
//{
//    ForHierarchy(const_cast<const int&>(entity), pred, op);
//    /*if (pred(entity))
//    {
//        op(entity);
//    }*/
//}

class MyEntity
{
public:
    MyEntity(int e): e(e) {}
    int e;
};

template <typename T>
void HV_DeleteAndSetNull(T*& instance)
{
    delete instance;
    instance = nullptr;
}

#include "some_header.h"

void Hahahabb::do123()
{

}

void Hahahabb::do234()
{

}

//////////////////////////////////////////////////////////////////////////

class SomeShitBase
{
public:
    int a;
};

template <typename T, typename Base>
class MemoryBase : public Base
{
public:
    static void chain()
    {
        cout << "ID=" << T::ID << endl;
    }
    virtual void vchain()
    {
        cout << "ID=" << T::ID << endl;
    }
    void get()
    {
        cout << this << endl;
        cout << static_cast<T*>(this) << endl;
        cout << (void*)(static_cast<T*>(this)) << endl;
        cout << "ID=" << T::ID << endl;

        void* mem = this;
        cout << mem << endl;
    }
    virtual void vget()
    {
        cout << this << endl;
        cout << static_cast<T*>(this) << endl;
        cout << static_cast<MemoryBase*>(this) << endl;

        void* mem = this;
        cout << mem << endl;
    }
    int b;
};

class IInterface
{
public:
    virtual void imp() = 0;
};

//class MemoryDerive : public MemoryBase<MemoryDerive>, public SomeShitBase
//class MemoryDerive : public SomeShitBase, public MemoryBase<MemoryDerive>
class MemoryDerive : public MemoryBase<MemoryDerive, SomeShitBase>
{
public:
    enum Const
    {
        ID = 1,
    };
    virtual void vtest()
    {

    }
    void test()
    {
        get();
        //vget();
        cout << this << endl;
        cout << static_cast<MemoryBase*>(this) << endl;
        cout << static_cast<SomeShitBase*>(this) << endl;

        cout << "1" << endl;
    }
};

class MemoryDerive2 : public MemoryBase<MemoryDerive2, MemoryDerive>
{
public:
    enum Const
    {
        ID = 2,
    };
    int mdd;
};

//////////////////////////////////////////////////////////////////////////

template <typename T>
class Has_PostImport
{
private:
    typedef char Yes;
    typedef long No;

    struct Fallback
    {
        int member;
    };
    struct Derived : T, Fallback { };

    template <typename U>
    static Yes& test(decltype(U::PostImport)*);
    template <typename U>
    static No& test(U*);

public:
    static const bool value = sizeof(test<Derived>(nullptr)) == sizeof(Yes);
};
class TestPostImport
{
public:
    void PostImport() {}
    enum Const
    {
        VERSION = 1,
    };
};
class TestPostImport2
{
public:
    void ha() {}
};

//////////////////////////////////////////////////////////////////////////

template<class T>
auto serialize_imp(T& obj, int) -> decltype(&T::PostImport, void())
{
    obj.PostImport();
}

template<class T>
void serialize_imp(T& obj, long)
{

}

template<class T>
//auto serialize(T& obj) -> decltype(serialize_imp(obj, 0), void())
void serialize(T& obj)
{
    serialize_imp(obj, 0);
}

//////////////////////////////////////////////////////////////////////////

//template<class T>
//void serialize_imp2(T& obj, decltype(T::VERSION)* ptr)
//{
//    obj.PostImport();
//}
//
//template<class T>
//void serialize_imp2(T& obj, bool* ptr)
//{
//
//}

//template<class T>
//auto serialize2(T& obj) -> decltype(serialize_imp2(obj, 0), void())
//{
//    serialize_imp2(obj, 0);
//}

class NewColor
{
public:
    NewColor(float r, float g, float b)
        : r(r), g(g), b(b)
    {
    }
    NewColor(const NewColor& color = NewColor::White)
        : r(color.r), g(color.g), b(color.b)
    {
    }

    static const NewColor White;
    static const NewColor Black;
    static const NewColor Red;
    static const float R;

    float r;
    float g;
    float b;
};

const float NewColor::R = 10.0f;
const NewColor NewColor::White = NewColor(1,1,1);
const NewColor NewColor::Black = NewColor(0,0,0);

void PrintXX(const NewColor& color = NewColor::Black)
{
    std::cout << color.r << color.g << color.b << endl;
}

//////////////////////////////////////////////////////////////////////////

/*********************************************

    whoa!

 *********************************************/
int _tmain(int argc, _TCHAR* argv[])
{
    {

    }
    {
        NewColor nc;
        std::cout << nc.r << nc.g << nc.b << endl;

        NewColor nc2(NewColor::Black);
        cout << nc2.r << nc2.g << nc2.b << endl;

        PrintXX();

        cout << "1";
    }

    {
        //using namespace DebugNamespace;
        //Debug.Ha();
    }

    {
        std::map<int, int> m;
        m[0] = 1;
        auto it = m.find(0);
        it->second = 2;
        cout << "1" << endl;
    }
    {
        DeriveToCopy hd(7);
        BaseToCopy* ph1 = &hd;
        DeriveToCopy* phd = static_cast<DeriveToCopy*>(ph1);
        phd->a = 12345;
        cout << "1" << endl;
    }
    {
        TestPostImport tpi;
        serialize(tpi);
        //serialize_imp2(tpi, nullptr);
        TestPostImport2 tpi2;
        serialize(tpi2);
        //serialize_imp2(tpi2, 0);
    }
    {
        cout << Has_PostImport<TestPostImport>::value << endl;
        cout << Has_PostImport<TestPostImport2>::value << endl;
    }
    {
        //MemoryDerive md;
        //md.test();

        MemoryDerive2 md2;
        md2.get();
        MemoryDerive* pmd1 = static_cast<MemoryDerive*>(&md2);
        pmd1->get();

        //SomeShitBase* psb1 = static_cast<MemoryDerive*>(&md2);
        //psb1->a;

        md2.vchain();
        pmd1->vchain();
        cout << "1" << endl;
    }
    {
        Hahahabb v;
        v.do123();
    }
    {
        int* p = new int(1234);
        HV_DeleteAndSetNull(p);
        cout << "1" << endl;
    }
    {
        char c[12] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};

        std::string s1;
        s1.resize(12);
        char* tos1 = const_cast<char*>(s1.c_str());
        memcpy(tos1, c, 12);

        auto p = reinterpret_cast<const int*>(s1.c_str());
        int i1 = p[0];
        int i2 = p[1];
        int i3 = p[2];

        std::string s2 = s1;
        p = reinterpret_cast<const int*>(s2.c_str());
        i1 = p[0];
        i2 = p[1];
        i3 = p[2];

        cout << "1" << endl;
    }
    {
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        cout << v[0] << " " << &v[0] << endl;
        cout << v[1] << " " << &v[1] << endl;
        cout << "---" << endl;
        auto it = lower_bound(v.begin(), v.end(), 2);

        std::vector<int>::const_iterator itc = v.begin();
        itc = v.end();
        bool isEnd = (it == v.end());
        bool isBegin = (it == v.begin());
        int lb = (*it);
        itc = it;

        v.insert(it, 10);

        for (int i = 0; i < 2; ++i)
        {
            cout << v[i] << " " << &v[i] << endl;
            v.push_back(5);
            v.push_back(5);
            v.push_back(5);
        }

        cout << "1" << endl;
    }
    {
        MyEntity a = 1234;
        MyEntity& ra = a;
        const MyEntity& cra = a;
        auto pred = [](const MyEntity & i)
        {
            return true;
        };
        auto cop = [](const MyEntity & i)
        {
            cout << i.e << endl;
        };
        auto op = [](MyEntity & i)
        {
            ++i.e;
            cout << i.e << endl;
        };
        ForHierarchy(ra, pred, op);
        ForHierarchy(ra, pred, cop);
        ForHierarchy(cra, pred, cop);
        //ForHierarchy(cra, pred, op);
        cout << "1" << endl;
    }
    {
        D1 d1;
        d1.do1();
        //d1.bo1();
        cout << "1" << endl;
    }
    {
        myclass m1;
        myclass_2 m2(&m1);
        m2.load();
        cout << "1" << endl;
    }
    {
        int v1 = 10;
        double v2 = 20.0;
        //auto a = A(v1, v2);
    }
    {
        HHHD d;
        HHH1* h = &d;
        h->dooo();
        std::cout << "1" << std::endl;
    }
    {
        std::vector<int> v(5, 99);
        v[0] = 1;
        v[1] = 0;
        for (auto i : v)
        {
            if (i == 0)
            {
                v.push_back(1234);
            }
        }
        std::cout << "1" << std::endl;

        HHH h;
        HHH::b.a = 123;

        int x = 100;
        TheHeck(x);
        float y = 1.0f;
        TheHeck(y);
        int& z = x;
        //foo2(x);
        fooo(z);
        //foo2(z);

        std::cout << "1" << std::endl;
    }
    {
        std::string str = "aaaabbb";
        unsigned char arr[3];
        //std::copy(str.begin(), str.begin()+4, std::begin(arr));//cause secure error (build error...)
        std::cout << "1" << std::endl;
    }
    {
        const int i = 0;
        //Ptr ptr(&i);
        //Ptr
    }
    {
        /*typedef std::map<int, int> Sample;
        typedef std::map<int, Sample> Sample2;
        Sample m1;
        m1[0] = 999;
        m1[1] = 999;
        m1[2] = 999;
        Sample2 m2;
        m2[0] = m1;
        std::cout << "1" << std::endl;*/

        typedef std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> Inner;
        typedef std::map<int, Inner, std::less<int>, MyAllocator<std::pair<const int, Inner>>> Outer;
        Inner m_inner;
        Outer m_outer;
        m_inner[0] = 1234;
        m_inner[1] = 1234;
        m_inner[2] = 1234;
        //m_outer.insert(std::make_pair(0, m_inner));
        m_outer[1] = m_inner;
        //m_outer[2] = m_inner;
        std::cout << "1" << std::endl;
    }
    {
        Hahaha<float> a;
        Hahaha<bool> b;
        std::vector<Hahaha<float>> va(10);
        std::vector<Hahaha<bool>> vb(10);
        std::cout << va[0].jkl << std::endl;
        std::cout << vb[0].abcd << std::endl;
        std::cout << "1" << std::endl;
    }
    {
        std::set<Info, CompareInfo> infos;
        Info info1 = {1, 1, 1, 1, 1};
        infos.insert(info1);
        Info info2 = {2, 2, 2, 2, 2};
        infos.insert(info2);
        Pairs p(1, 1);

        auto it0 = infos.find(MakeInfo(p));
        if (it0 != infos.end())
        {
            std::cout << "1" << std::endl;
        }
        std::cout << "1" << std::endl;

        auto it = std::find_if(infos.begin(), infos.end(),
                               [ = ](const Info & info)
        {
            return (info.a == p.first) && (info.b == p.second);
        });

        if (it != infos.end())
        {
            std::cout << "1" << std::endl;
        }
        std::cout << "1" << std::endl;
    }
    {
        AAAAA<int> a1;
        AAAAA<float> a2;
        AAAAA<double> a3;
        a1.currPlayKeyIdx = 10;
        a2.haha = 123.0f;
        //a2.
    }
    {
        int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int* it = std::remove_if(std::begin(array), std::end(array),
                                 [](int e)
        {
            return (e >= 5) && (e <= 8);
        });
        /*std::transform(it, std::end(array), it,
        [](int e) -> int
        {
        return -1;
        });*/ // ----> cause error in Debug mode

        std::cout << "1" << std::endl;
    }
    {
        std::vector<std::string> myvector;
        myvector.push_back("value");
        myvector.push_back("value");
        myvector.push_back("empty");
        myvector.push_back("value");
        myvector.push_back("value");
        myvector.push_back("empty");
        myvector.push_back("empty");
        auto it = std::remove_if(myvector.begin(), myvector.end(),
                                 [](const std::string & string)
        {
            return (string == "empty");
        });
        myvector.erase(it, myvector.end());
        std::cout << "1" << std::endl;
    }
    {
        EffectCommand<int> ec1;
        ec1.Yay();
        //EffectCommand<double> ec2;
        //ec2.Yay();
        std::vector<bool> v(10);
        DOVECTOR(v);
        std::vector<int> v1(10);
        DOVECTOR(v1);

        HelloCR h;
        h.Do();
        std::cout << "1" << std::endl;
    }
    {
        bool result = false;

        std::vector<int> children(10, 1);
        std::for_each(children.begin(), children.end(), [&](int i)
        {
            result &= i;
            std::cout << &result << std::endl;
        });

        std::cout << result << std::endl;
    }
    {
        std::vector<int> v(10);
        v[0] = 10;
        int k = 1;
        v[k] = 20;
    }
    {
#if defined ABC1
        std::cout << "ABC1" << std::endl;
#elif defined ABC2
        std::cout << "ABC2" << std::endl;
#else
        std::cout << "ABC3" << std::endl;
#endif
    }
    {
        int r = 999;
        Something1 s(r);


        std::cout << "1" << std::endl;
    }
    {
        int k;
        int* j = new int;

        boom();
        std::cout << "1" << std::endl;
    }
    {
        std::vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        for (int i : v)
        {
            if (i == 2)
            {
                v.erase(v.begin() + i);
            }
            else
            {
                std::cout << i;
            }
        }
        std::cout << "1" << std::endl;
    }
    {
        std::vector<std::string> names;
        names.push_back("Jeremy");
        names.push_back("James");
        names.push_back("Richard");

        std::copy(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, " "));
    }
    {
        /*std::vector<int> ds; ds.reserve(4);
        ds.push_back( int(1));
        ds.push_back( int(2));
        ds.push_back( int(3));
        auto it = std::find_if(ds.begin(), ds.end(), [](int d){d == 2;});
        if (it != ds.end())
        {
        int dd = (*it);
        dd = 4;
        }*/

        std::cout << "1" << std::endl;
    }
    {
        std::vector<DeriveToCopy*> ds;
        ds.reserve(4);
        ds.push_back(new DeriveToCopy(1));
        ds.push_back(new DeriveToCopy(2));
        ds.push_back(new DeriveToCopy(3));
        //auto it = ds.begin();
        auto f = [](DeriveToCopy * d)
        {
            return d->b == 2;
        };
        auto it = std::find_if(ds.begin(), ds.end(), f);
        if (it != ds.end())
        {
            DeriveToCopy* dd = (*it);
            dd->b = 4;
        }

        std::cout << "1" << std::endl;
    }
    {
        //DeriveToCopy d1; d1.b = 1234;
        //DeriveToCopy d2; d2.b = 5678;
        //d2 = d1;
        std::vector<DeriveToCopy> ds;
        ds.reserve(4);
        ds.emplace_back(123);
        ds.emplace_back(456);
        ds.emplace_back(789);
        ds.erase(std::remove_if(ds.begin(), ds.end(), [](DeriveToCopy & d)
        {
            return d.b == 456;
        }));

        std::cout << "1" << std::endl;
    }
    {
        CopyMe c1;
        c1.cm = 12345;
        //CopyMe c2(c1);

        RGBB o(1, 2, 3);
        int g = o[1];

        std::cout << "1" << std::endl;
    }

    {
        MEEBO m;
        std::cout << m.enabled << std::endl;
        //m.var++;
        std::cout << m.var << std::endl;

        std::vector<noncbutm> v(10);
        /*v.push_back(noncbutm());
        v.push_back(noncbutm());
        v.push_back(noncbutm());
        for (auto& e : v)
        {

        }*/
        v.clear();
    }
    {
        //std::pair<int, int>::second_type;
        std::vector<int> v(3, 1);
        std::map<int, int> m;
        m[0] = 10;
        m[1] = 11;
        m[2] = 12;
        print(v.begin(), v.end());
        print(m.begin(), m.end());
        std::cout << "a" << std::endl;
    }
    {
        {
            /*std::vector<wtfref*> v1;
            v1.push_back(new whoa);
            v1.push_back(new whoa);
            v1.push_back(new whoa);
            std::for_each(v1.begin(), v1.end(), [](wtfref* p) { delete p; });
            v1.clear();
            std::cout << "a" << std::endl;*/
            std::vector<int> v;
            v.push_back(0);
            v.push_back(1);
            v.push_back(2);
            v.push_back(3);
            v.push_back(4);
            srand(time(NULL));
            int a = rand() % 5;
            auto it = v.begin() + a;
            v.erase(it);
            std::cout << "a" << std::endl;
        }
        whoa* w = new whoa();
        {
            std::vector<std::shared_ptr<wtfref>> v1;
            std::vector<std::shared_ptr<wtfref2>> v2;

            {
                std::shared_ptr<whoa> pw(w);
                v1.push_back(std::shared_ptr<wtfref>(pw));
                v2.push_back(std::shared_ptr<wtfref2>(pw));
            }

            v1.clear();
            v2.clear();
            //std::shared_ptr<wtfref> p1(w);
            //std::shared_ptr<wtfref2> p2(w);

        }
        std::cout << "a" << std::endl;
    }
    {
        int a = 123;
        {
            std::shared_ptr<int> p(&a);
            // crash when leave
        }
        std::cout << "a" << std::endl;
    }
    {
        char c = 'c';
        //const char* cc = &c;
        std::string s(1, c);
        char& rc = c;
        rc = 'd';
        //*rc = 'e';
        wtfref w;
        w.ww = 10;
        //(*w.ww) = 20;

        s = typeid(std::vector<int>).name();

        impClass o;
        classA a;
        o.fun(a);
        o.fun<classA>(a);

        std::cout << "a" << std::endl;
    }
    {
        eatchar('a');

        std::unordered_map<std::string, unsigned int> dico;
        dico["a"] = 1;
        dico["b"] = 1;
        dico["c"] = 1;
        std::string str("abcd");
        std::for_each(str.begin(), str.end(), [&](char l)
        {
            {
                char c = 'a';
                const char* cc = &c;
                std::string s(cc);
            }
            const char* cc = &l;
            //std::string ss(cc);
            if (dico.count(cc) == 0)
            {
                std::cout << "1" << std::endl;
            }
        });

        std::cout << "a" << std::endl;
    }
    {
        std::map<int, int> L;
        //L.insert({1,1});
        std::map<int, STDerive> m;
        //m.insert({0,STDerive(1)});

        STDerive::yay();
        STDerive d;
        d.some();
        d.do1(&d);
        std::vector<int> ad;
        for (int i = 0; i < 5000; ++i)
        {
            ad.push_back(1);
        }
        ad.push_back(1);
        ad.push_back(1);
        ad.clear();

        std::cout << "a" << std::endl;
    }
    {
        int* p1 = new int(123);
        LetYouDo oo1("abc", p1);
        //LetYouDo oo2("abc", p1, p1);
        oo1.Init();
        void* vp1 = oo1.GetKey();

        /*Victim v;
        v.m1 = 10;
        v.m2.push_back(10);
        LetYouDo o1("o1", &Victim::m1);
        LetYouDo o2("o2", &Victim::m2, static_cast<int*>(0));*/

        std::cout << "a" << std::endl;
    }
    {
        HvVector<int>::rt v0;
        v0.push_back(1);
        auto it = v0.begin();
        (*it) = 2;
        //wc(v0);
        /*std::vector<int> vvv;
        wc(vvv);
        HvVector<int>::rt v2;
        wc(v2);*/

        std::cout << "a" << std::endl;
    }
    {
        std::vector<float> v(10);

        //std::vector<int> vv = Transform(v);

        std::cout << "a" << std::endl;
    }
    {
        int* p = nullptr;
        if (p)
        {
            std::cout << "a" << std::endl;
        }
        if (!p)
        {
            std::cout << "a" << std::endl;
        }
        std::cout << "a" << std::endl;
    }
    {
        int* p = new int(123);
        Delete(p);
        forsomething* fff = new forsomething();
        Delete(fff);

        std::cout << "a" << std::endl;
    }
    {
        std::vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        auto it = std::lower_bound(v.begin(), v.end(), 4);
        bool b = it == v.end();
        int offset = it - v.begin();

        std::cout << "a" << std::endl;
    }
    {
        int a = 10;
        //ttt01(static_cast<const int&>(a));

        std::cout << "a" << std::endl;
    }
    {
        TestTemplateParam<int, false> o1;
        TestTemplateParam<forsomething, true> o2;

        std::cout << "a" << std::endl;
    }
    {
        Component001 c1;
        Component002 c2;
        Component003 c3;
        int k = 99;
        System001 s1(k);
        System002 s2(k);
        System003 s3(k);
        std::cout << c1.GetTypeIndex() << std::endl;
        std::cout << c2.GetTypeIndex() << std::endl;
        std::cout << c3.GetTypeIndex() << std::endl;
        std::cout << s1.GetTypeIndex() << std::endl;
        std::cout << s2.GetTypeIndex() << std::endl;
        std::cout << s3.GetTypeIndex() << std::endl;
        std::cout << Component001::TypeIndex() << std::endl;
        std::cout << Component002::TypeIndex() << std::endl;
        std::cout << Component003::TypeIndex() << std::endl;
        std::cout << System001::TypeIndex() << std::endl;
        std::cout << System002::TypeIndex() << std::endl;
        std::cout << System003::TypeIndex() << std::endl;

        std::cout << "a" << std::endl;
    }
    {
        //std::set<const type_info*> m;
        std::map<std::type_index, int> m;

        TClass<int> o;
        TClass<float> p;

        m.insert(std::make_pair(std::type_index(typeid(int)), 0));
        m.insert(std::make_pair(std::type_index(typeid(float)), 0));
        m.insert(std::make_pair(std::type_index(typeid(double)), 0));
        m.insert(std::make_pair(std::type_index(typeid(TClass<int>)), 0));
        m.insert(std::make_pair(std::type_index(typeid(TClass<float>)), 0));
        //m.insert(&typeid(int));
        //m.insert(&typeid(float));
        //m.insert(&typeid(double));

        auto it = m.find(typeid(TClass<float>));
        if (it != m.end())
        {
            std::cout << "a" << std::endl;
        }

        std::cout << "a" << std::endl;
    }
    {
        TClass<int> o;
        o.do1();
        o.do2<float>();
        TClass<float> p;
        p.do1();
        p.do2<float>();

        std::cout << "a" << std::endl;
    }
    {
        Fun<float>();
        Fun<int>();
        //Fun<std::vector<double>>();

        std::cout << "a" << std::endl;
    }
    {
        int p1 = 123;
        double p2 = 444.444;
        std::vector<float> v1(1, 123.0f);

        //trytemplate o1(p1);
        trytemplate o2(v1);

        trytemplate o3(p1, double());

        std::cout << "a" << std::endl;
    }
    {
        std::vector<test99> v;
        //test99 o; o.a = 1234;

        v.emplace_back(1);
        v.emplace_back(2);
        v.emplace_back(3);
        v.emplace_back(4);
        v.emplace_back(5);
        v.emplace_back(6);
        //v.push_back(test99(2));
        //v.push_back(test99(3));
        //v.push_back(test99(4));
        //v.push_back(test99(5));
        //v.push_back(test99(6));
        //v.push_back(o);
        //v.push_back(o);
        //v.push_back(o);
        //v.push_back(o);
        //v.push_back(o);
        //v.push_back(o);
        v[2].a = 7;
        auto it = std::remove_if(v.begin(), v.end(), [](test99 & t)
        {
            return t.a == 7;
        });
        v.erase(it);

        std::cout << "a" << std::endl;
    }
    {
        {
            ederive2 o;
            o.abc = 1;
            o.def = 2;
            o.jkl = 3;
        }
        ederive2* p2 = new ederive2;
        delete p2;
        ebase* pb = new ederive2;
        delete pb;
        std::cout << "a" << std::endl;
    }
    {
        super123 o;
        o.do2();
        base3* pb1 = &o;
        pb1->do3();
        //reinterpret_cast<base1*>(pb1)->do1();
        super123 p(o);
        p.do1();

        std::cout << "a" << std::endl;
    }
    {
        //Testobj o;
        std::vector<Testobj> v;
        v.push_back(Testobj(10));
        v.push_back(Testobj(20));
        v.push_back(Testobj(30));
        auto it = std::find_if(v.begin(), v.end(),
                               [](Testobj & o)
        {
            return *(o.get()) == 10;
        });
        v.erase(it);

        std::cout << "a" << std::endl;
    }
    {
        std::vector<int> v;
        auto it = v.end();
        if (it == v.end())
        {
            std::cout << "a" << std::endl;
        }
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        auto it2 = v.begin();

        if (it == v.end())
        {
            std::cout << "a" << std::endl;
        }
        else
        {
            std::cout << "a" << std::endl;
        }

        std::cout << "a" << std::endl;
    }
    {
        int a = 123;
        double b = 123.321;
        magicsetter(&a);
        magicsetter(&b);
        std::cout << "a" << std::endl;
    }
    {
        std::vector<int> a1 = foreachthing(
                                  [](int& a)
        {
            ++a;
        }
        // 10­Ó13
                              );

        std::vector<int> a2 = foreachthing([](int& a)
        {
            --a;
        });
        // 10­Ó11

        std::cout << "a" << std::endl;
    }
    {
        conder o;
        o.dodo();
        /*std::function<void(const AA&)> f = std::bind(FB, _1);
        BB bb;
        f(bb);
        std::cout << "a" << std::endl;*/
        std::cout << "a" << std::endl;
    }
    {
        MouseSubscriber ms;
        MouseDispatcher md;
        ms.Register(md);
        ms.RegisterEx(md);
        md.MouseOn();
        ms.Unregister(md);
        md.MouseOn();

        /*typedef std::function<void(const MouseEvent&)> Fun;
        typedef std::shared_ptr<Fun> FunP;
        MouseSubscriber ms;
        auto f = std::bind(&MouseSubscriber::React, &ms, std::placeholders::_1);
        FunP p1(new Fun(f));
        FunP p2(new Fun(f));
        std::cout << (p1==p2) << std::endl;*/

        std::cout << "a" << std::endl;
    }
    {
        dcombat1 d11;
        d11.abc = 1;
        d11.def = 100;
        dcombat1 d12;
        d12.abc = 2;
        d12.def = 200;
        dcombat2 d21;
        d21.abc = 3;
        d21.gg = 123;
        dcombat2 d22;
        d22.abc = 4;
        d22.gg = 321;
        d12 = d11;
        d22 = d21;

        std::cout << "a" << std::endl;
    }
    {
        int orz = 1234;
        indexcombo obj(1, 2, orz);
        std::vector<indexcombo> vic;
        vic.push_back(obj);
        vic.push_back(obj);
        vic[0].c = 321;

        std::cout << "a" << std::endl;
        /*indexcombo c1 = {1,100};
        indexcombo c2 = {2,100};
        indexcombo c3 = {3,100};
        std::vector<indexcombo> vic;
        vic.push_back(c1);
        vic.push_back(c2);
        vic.push_back(c3);
        auto it = std::lower_bound(vic.begin(), vic.end(), 2,
        [=](indexcombo& cb1, int val)
        {
        return cb1.a < val;
        });

        std::cout << (*it).a << std::endl;
        std::cout << "a" << std::endl;*/
    }
    {
        tryrealcont a1;
        a1.az = 1;
        tryrealcont a2;
        a2.az = 3;
        a1.getstatic<float>();
        a2.getstatic<float>();
        a1.wtf();
        a2.wtf();

        std::cout << "a" << std::endl;
    }
    {
        rsystem<roar> obj;
        dorsys(&obj);
    }
    {
        ComDatabase db;
        std::map<int, std::function<void()>> funcs;

        funcs[0] = std::bind(&ComDatabase::add<Com1>, db);
        funcs[1] = std::bind(&ComDatabase::add<Com2>, db);
        funcs[2] = std::bind(&ComDatabase::add<Com3>, db);

        funcs[0]();
        funcs[1]();
        funcs[2]();

        std::cout << "a" << std::endl;
    }
    {
        // store a free function
        std::function<void(int)> f_display = print_num;
        f_display(-9);

        // store a lambda
        std::function<void()> f_display_42 = []()
        {
            print_num(42);
        };
        f_display_42();

        // store the result of a call to std::bind
        std::function<void()> f_display_31337 = std::bind(print_num, 31337);
        f_display_31337();

        // store a call to a member function
        //std::function<void(const Foo&, int)> f_add_display = &Foo::print_add; // why error?
        /*const*/ Foo foo(314159);
        //f_add_display(foo, 1);

        // store a call to a member function and object
        using std::placeholders::_1;
        using std::placeholders::_2;
        std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
        f_add_display2(2);

        std::function<void(Foo&, int)> f_add_display3 = std::bind(&Foo::print_add, _1, _2);
        f_add_display3(foo, 1);

        // store a call to a function object
        std::function<void(int)> f_display_obj = PrintNum();
        f_display_obj(18);
    }
    {
        using namespace std::placeholders;  // for _1, _2, _3...

        // demonstrates argument reordering and pass-by-reference
        int n = 7;
        // (_1 and _2 are from std::placeholders, and represent future
        // arguments that will be passed to f1)
        auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);
        n = 10;
        f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused

        // nested bind subexpressions share the placeholders
        auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
        f2(10, 11, 12);

        // common use case: binding a RNG with a distribution
        std::default_random_engine e;
        std::uniform_int_distribution<> d(0, 10);
        std::function<int()> rnd = std::bind(d, e);
        for (int n = 0; n < 10; ++n)
        {
            std::cout << rnd() << ' ';
        }
        std::cout << '\n';

        // bind to a member function
        Foo foo;
        auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
        f3(5);

        // bind to member data
        auto f4 = std::bind(&Foo::data, _1);
        std::cout << f4(foo) << '\n';
    }
    {
        testparam obj(1234);

        VComManager vcm;
        VSO o;
        vcm.Accept(&o);


        std::cout << "a" << std::endl;
    }
    {
        Aantitee a;
        Bentitee b;
        a.Do();
        b.Do();

        Wentity e;
        e.DoDo();

        std::cout << "a" << std::endl;
    }
    {
        int* pint = new int(1234);
        {
            std::unique_ptr<int> upint1(pint);
            std::unique_ptr<int> upint2 = std::move(upint1);
            upint2.release();
        }
        delete pint;
    }
    {
        int* pint = new int(1234);

        {
            {
                std::shared_ptr<int> spint1(pint);
                //spint1.reset(pint);

                {
                    std::shared_ptr<int> spint2(pint);
                    //spint2.reset(pint);
                }

                int usecount = spint1.use_count();
            }

            std::cout << "a" << std::endl;

            //usecount = spint2.use_count();
            //b/ool isuniq = spint2.unique();

            /*int* nullpint = NULL;
            spint1.reset(nullpint);
            if (spint1)
            {
            std::cout << *spint1 << std::endl;
            }
            else
            {
            std::cout << "a" << std::endl;
            }

            usecount = spint2.use_count();
            isuniq = spint2.unique();

            spint2.reset(nullpint);*/
        }
        delete pint;

        std::cout << "a" << std::endl;
    }
    {
        std::vector<int> vvv(10, 10);
        vvv[0] = 0;
        vvv[1] = 2;
        vvv[2] = 4;
        vvv[3] = 6;
        auto it0 = std::lower_bound(vvv.begin(), vvv.end(), 5);
        int offset0 = it0 - vvv.begin();
        vvv.insert(it0, 5);
        auto itz = vvv.begin() + offset0;

        auto it1 = vvv.begin();
        auto it2 = vvv.begin() + 5;
        int offset = it2 - it1;
        std::cout << "a" << std::endl;
    }
    {
        lightsystem<int>   ls1;
        lightsystem<float> ls2;
        lightsystem<bool>  ls3;
        ls1.oninsert();
        ls1.onremove();
        ls1.print();
        ls2.oninsert();
        ls2.onremove();
        ls3.oninsert();
        ls3.onremove();

        factoryuserr<int, true, true> f1;
        factoryuserr<char, true, true> f2;
        f1.test();
        f1.test1();
        f2.test();
        f1.test1();

        std::cout << "a" << std::endl;
    }
    {
        rrenderComponent<int> hhh;
        hhh.print();
        std::cout << "a" << std::endl;
    }
    {
        enum testbit
        {
            AAA = 0x1,
            BBB = 0x2,
            CCC = 0x4,
        };
        int bit = AAA & BBB & CCC;
        if (bit & AAA)
        {
            std::cout << "a" << std::endl;
        }
        if (bit & BBB)
        {
            std::cout << "b" << std::endl;
        }
        if (bit & CCC)
        {
            std::cout << "c" << std::endl;
        }
        std::cout << "omg" << std::endl;
    }
    {
        lesen<int, ZZZ> oh;
        //int offset = &(lesen<int, ZZZ>::def) - &(lesen<int, ZZZ>::abc);
        lesen<int, ZZZ>::calcoffset();
        oh.dodo();

        hoeren ooo;
        ooo.dodo();
        std::cout << "omg" << std::endl;
    }
    {
        HvBitset::rt abc;
        abc.set(1);
        std::cout << "omg" << std::endl;
    }
    {
        int yo = 1234;
        /*const*/ int* pyo = &yo;
        //functionneedvoid(const_cast<void*>(pyo)); // cant
        functionneedvoid(pyo);
        std::cout << "omg" << std::endl;
    }
    {
        lesen<float, ZZZ> a;
        std::cout << "omg" << std::endl;
    }
    {
        aufgabe a;
        a.Execute();
        a.Execute();
        a.Execute();
        std::cout << "omg" << std::endl;
    }
    {
        std::vector<int> findlower;
        findlower.push_back(0);
        findlower.push_back(2);
        findlower.push_back(4);
        findlower.push_back(6);
        findlower.push_back(8);
        std::vector<int>::iterator it =
            std::lower_bound(findlower.begin(), findlower.end(), 5);
        int offset = it - findlower.begin();
        findlower.insert(it, 5);
        std::cout << "omg" << std::endl;
    }
    {
        struct seevec
        {
            seevec(int aa): abc(aa) {}
            int abc;

        private:
            seevec() {}
        };
        std::vector<seevec> vaa;
        vaa.reserve(20);
        std::cout << "omg" << std::endl;
    }
    {
        temderi abc;
        abc.DO();
    }
    {
        std::vector<uuuu> vuuuu;
        uuuu local;
        local.aa = 0;
        vuuuu.push_back(local);
        local.aa = 1;
        vuuuu.push_back(local);
        local.aa = 2;
        vuuuu.push_back(local);
        std::vector<uuuu>::iterator it =
            std::find_if(vuuuu.begin(), vuuuu.end(),
                         [&](const uuuu & a)
        {
            return (a.aa == 1);
        }
                        );
        if (it != vuuuu.end())
        {
            std::cout << "omg" << std::endl;
        }
        std::for_each(vuuuu.begin(), vuuuu.end(),
                      [&](uuuu & a)
        {
            int offset = (&a) - (&vuuuu.front());
            a.aa = offset;
            std::cout << a.aa << std::endl;
        });
        std::cout << "a" << std::endl;
    }
    {
        bool isit = std::is_pointer<int*>::value;
        bool ismy = false;
        ismy = my_is_ptr<int>::value;
        ismy = my_is_ptr<int*>::value;
        ismy = my_is_ptr<int**>::value;
        if (my_is_ptr<int*>::value)
        {
            std::cout << "omg" << std::endl;
        }
        std::cout << "a" << std::endl;
    }
    {
        MyVector<int> myvecint;
        myvecint.PushBack(0);
        myvecint.PushBack(1);
        myvecint.PushBack(2);
        myvecint.PushBack(3);
        myvecint.PushBack(4);
        MyVector<int>::Iterator it = std::find(myvecint.Begin(), myvecint.End(), 1);
        if (it != myvecint.End())
        {
            std::cout << *it << std::endl;
        }
        else
        {
            std::cout << "your ass" << std::endl;
        }

        std::cout << "a" << std::endl;
    }
    //ActivateForStatic();
    {
        std::vector<ABD, SimpleAllocator<ABD>> vall;
        vall.reserve(100);
        vall.push_back(1);
        vall.push_back(2);
        vall.clear();
        vall.push_back(3);

        std::map<int, int, std::less<int>, SimpleAllocator<int>> mall;
        mall.insert(std::make_pair(0, 1));
        mall.insert(std::make_pair(1, 1));
        mall.insert(std::make_pair(2, 1));
        mall.find(0);
        mall.erase(1);
        mall.clear();

        std::cout << "a" << std::endl;
    }
    {
        make<TA>(10, 20, false);
        make<TB>("sob", 101);
    }
    {
        World world;
        Entity& entity = world.CreateEntity();
        RenderComponent& c1 = world.AddComponent<RenderComponent>(entity);
        TransformComponent& c2 = world.AddComponent<TransformComponent>(entity);
        VelocityComponent& c3 = world.AddComponent<VelocityComponent>(entity);
        //ParticleComponent& c4 = world.AddComponent<ParticleComponent>(entity);
        RenderComponent& c5 = world.AddComponent<RenderComponent>(entity);
        std::string abc = c1.Name();
        std::cout << typeid(RenderComponent).name() << std::endl;
        std::cout << c1.TypeIndex() << std::endl;
        std::cout << c2.TypeIndex() << std::endl;
        std::cout << c3.TypeIndex() << std::endl;
        // std::cout << c4.TypeIndex() << std::endl;
        std::cout << c5.TypeIndex() << std::endl;

        std::cout << "a" << std::endl;
    }
    {
        mapper<int> yoyoyo1;
        yoyoyo1.something = 1234;
        mapper<int> yoyoyo2;
        std::cout << yoyoyo2.something << std::endl;
        mapper<float>::something = 4444;
        std::cout << mapper<float>::something << std::endl;
        std::cout << &(mapper<int>::something) << std::endl;
        std::cout << &(mapper<double>::something) << std::endl;
        std::cout << "a" << std::endl;
    }
    {
        std::map<int, int> gg;
        gg.insert(std::make_pair(0, 1));
        gg.insert(std::make_pair(1, 1));
        gg.insert(std::make_pair(2, 1));

        ((*((std::_Tree_val<std::_Tree_simple_types<std::pair<int const , int>>>*)(&(*((std::_Tree_alloc<0, std::_Tree_base_types<std::pair<int const , int>, std::allocator<std::pair<int const , int>>>>*)(&(*((std::_Tree_buy<std::pair<int const , int>, std::allocator<std::pair<int const , int>>>*)(&(*((std::_Tree_comp<0, std::_Tmap_traits<int, int, std::less<int>, std::allocator<std::pair<int const , int>>, 0>>*)(&(*((std::_Tree<std::_Tmap_traits<int, int, std::less<int>, std::allocator<std::pair<int const , int>>, 0>>*)((&(gg)))))))))))))))))._Myhead)->_Parent;
        std::cout << "a" << std::endl;
    }
    {
        int abc[4] = {1, 2, 3, 4};
        memset(abc, 0xFF, 4);

        std::cout << "a" << std::endl;
    }
    {
        //int a = 20;
        int* pa = NULL;
        *pa = 10;
        function1(pa);
        std::cout << "a" << std::endl;
    }

    return 0;
}

