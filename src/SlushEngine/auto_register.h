#include <memory>
#include <print>
#include "behavior.h"
#include "core.h"
namespace SlushEngine{
    template <typename T>
    class AutoRegister {
    public:
        struct Registrar {
            Registrar() {
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
