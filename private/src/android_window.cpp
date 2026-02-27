#include "base/prerequisites.h"
#include "core/core.h"
#include "android_window.h"

#if defined(ARIEO_PLATFORM_ANDROID)
#include <android/log.h>
#include <game-activity/GameActivity.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>

namespace Arieo
{
    void AndroidWindowManager::initialize(void* app)
    {
        m_android_app = reinterpret_cast<android_app*>(app);
        if (app != nullptr)
        {
            Core::Logger::info("AndroidWindowManager: Initialized with android_app: {}", 
                              reinterpret_cast<std::uint64_t>(app));
        }
    }

    void AndroidWindowManager::finalize()
    {
        // Clean up all windows
        if(m_android_main_window)
        {
            destroyWindow(m_android_main_window);
            m_android_main_window = nullptr;
        }
        
        m_android_app = nullptr;
    }

    void* AndroidWindowManager::getDisplay()
    {
        // Android doesn't have a traditional display handle like X11
        // Return the native activity instead, which serves as the context
        return m_android_app->window;
    }

    Base::Interop<Interface::Window::IWindow> AndroidWindowManager::createWindow(std::uint16_t pos_x, std::uint16_t pos_y, std::uint16_t width, std::uint16_t height)
    {
        // On Android, we can't really create arbitrary windows like on desktop
        // We work with the single native window provided by the Android system
        Core::Logger::error("AndroidWindowManager::getMainWindow() not implemented, using getMainWindow instead");
        return nullptr;
    }

    Base::Interop<Interface::Window::IWindow> AndroidWindowManager::getMainWindow()
    {
        if(m_android_main_window == nullptr)
        {
            if (m_android_app == nullptr)
            {
                Core::Logger::error("Cannot create Android window: No android_app available");
                return nullptr;
            }
            
            ANativeWindow* native_window = m_android_app->window;
            if (native_window == nullptr)
            {
                Core::Logger::error("Cannot create Android window: No native window available");
                return nullptr;
            }

            // Create our wrapper around the native window
            m_android_main_window = Base::Interop<Interface::Window::IWindow>::createAs<AndroidWindow>(m_android_app);
            Core::Logger::info("Created Android window with native window handle: {}", 
                              reinterpret_cast<std::uint64_t>(m_android_app->window));
        }
        
        return m_android_main_window;
    }

    void AndroidWindowManager::destroyWindow(Base::Interop<Interface::Window::IWindow> window)
    {
        if(window != m_android_main_window)
        {
            Core::Logger::error("Attempted to destroy a non-AndroidWindow with AndroidWindowManager");
            return;
        }
        Core::Logger::warn("Destroying AndroidWindow. Note: The underlying native window is managed by the Android system. Actually do nothing now.");
        // android_window.destroyAs<AndroidWindow>();
    }

    void AndroidWindowManager::onInitialize()
    {
        Core::Logger::info("AndroidWindowManager initialized");
    }

    void AndroidWindowManager::onTick()
    {
        // On Android, window events are handled via the native app glue
        // We don't need to poll for events like on desktop platforms
    }

    void AndroidWindowManager::onDeinitialize()
    {
        Core::Logger::info("AndroidWindowManager deinitialized");
    }
}

#endif // ARIEO_PLATFORM_ANDROID