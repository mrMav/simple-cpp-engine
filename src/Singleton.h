// As seen in game programming gems volume 1;

#include <cassert>

namespace Engine
{
    template <typename T>
    class Singleton
    {
        static T* _Singleton;

    public:

        Singleton()
        {
            assert(!_Singleton);
            int offset = (uintptr_t)(T*)1 - (uintptr_t)(Singleton <T>*)(T*)1;
            _Singleton = (T*)((uintptr_t)this + offset);
        }
        
        ~Singleton()
        {
            assert(_Singleton);
            _Singleton = nullptr;
        }

        static T& GetSingleton()
        {
            assert(_Singleton);
            return *_Singleton;
        }

        static T* GetSingletonPtr()
        {
            return _Singleton;
        }
        
    };

    template <typename T> T* Singleton <T>::_Singleton = nullptr;
}
