#ifndef CRUCIBLEEDITOR_IMGUIINTEROP_H
#define CRUCIBLEEDITOR_IMGUIINTEROP_H

#include "imgui.h"

namespace crucible
{

    class ImGuiInterop
    {
    public:
        static void registerInteropFunctions(ImFont* title, ImFont* body);
    };

} // crucible

#endif //CRUCIBLEEDITOR_IMGUIINTEROP_H
