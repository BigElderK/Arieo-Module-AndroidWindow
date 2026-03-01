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
            AndroidWindowManager android_window_manager_instance;
            Base::Interop::SharedRef<Interface::Window::IWindowManager> window_manager = Base::Interop::makePersistentShared<Interface::Window::IWindowManager>(android_window_manager_instance);

            DllLoader()
            {
                // Set up android app callback if available
                // if (g_android_app != nullptr)
                // {
                //     android_window_manager_instance.setAndroidApp(g_android_app);
                //     g_android_app->onAppCmd = android_app_cmd_callback;
                // }

                Base::Interop::SharedRef<Interface::Main::IMainModule> main_module = Core::ModuleManager::getInterface<Interface::Main::IMainModule>();
                if (main_module)
                {
                    android_window_manager_instance.initialize(main_module->getAppHandle());

                    main_module->registerTickable(window_manager);
                }

                Core::ModuleManager::registerInterface<Interface::Window::IWindowManager>(
                    "android_window_manager",
                    window_manager
                );

                Core::Logger::info("Android window module initialized");
            }

            ~DllLoader()
            {
                Core::ModuleManager::unregisterInterface<Interface::Window::IWindowManager>(
                    window_manager
                );
                android_window_manager_instance.finalize();
                Core::Logger::info("Android window module finalized");
            }
        } dll_loader;
    }
}

#endif // ARIEO_PLATFORM_ANDROID




