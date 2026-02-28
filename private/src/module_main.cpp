#include "base/prerequisites.h"
#include "core/core.h"
#include "android_window.h"

#if defined(ARIEO_PLATFORM_ANDROID)
#include <game-activity/GameActivity.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>

namespace Arieo
{
    GENERATOR_MODULE_ENTRY_FUN()
    ARIEO_DLLEXPORT void ModuleMain()
    {
        Core::Logger::setDefaultLogger("android_window");

        static struct DllLoader
        {
            Base::Instance<AndroidWindowManager> android_window_manager;

            DllLoader()
            {
                
                // Set up android app callback if available
                // if (g_android_app != nullptr)
                // {
                //     android_window_manager.setAndroidApp(g_android_app);
                //     g_android_app->onAppCmd = android_app_cmd_callback;
                // }
                
                Base::Interop::RawRef<Interface::Main::IMainModule> main_module = Core::ModuleManager::getInterface<Interface::Main::IMainModule>();
                if (main_module)
                {
                    android_window_manager->initialize(main_module->getAppHandle());
                    
                    main_module->registerTickable(android_window_manager.queryInterface<Interface::Main::ITickable>());
                }

                Core::ModuleManager::registerInstance<Interface::Window::IWindowManager, AndroidWindowManager>(
                    "android_window_manager", 
                    android_window_manager

                );
                
                Core::Logger::info("Android window module initialized");
            }

            ~DllLoader()
            {
                Core::ModuleManager::unregisterInstance<Interface::Window::IWindowManager, AndroidWindowManager>(
                    android_window_manager
                );
                android_window_manager->finalize();
                Core::Logger::info("Android window module finalized");
            }
        } dll_loader;
    }
}

#endif // ARIEO_PLATFORM_ANDROID




