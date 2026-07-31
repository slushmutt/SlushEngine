#include <raylib.h>
#include <SlushEngine/export.hpp>
namespace SlushEngine {
    class SLUSH_EXPORT Input {
        public:
            static Vector2 AsVector2Composite(KeyboardKey up, KeyboardKey down, KeyboardKey left, KeyboardKey right); 
        private:
    };

}
