#include <SlushEngine/export.hpp>
#include <SlushEngine/core.h>

namespace SlushEngine{
    template <typename T>
    class SLUSH_EXPORT AutoRegister {
    public:
        struct Registrar {
            Registrar(){
                SlushEngine::Core::active_behaviors.push_back(new T());
            }
        };

        static Registrar registrar;

        void ForceInstantiation() {
            (void)registrar; 
        }

    };

    template <typename T>
    typename AutoRegister<T>::Registrar AutoRegister<T>::registrar;
}
