#pragma once
#include "interface/window/window.h"

#if defined(ARIEO_PLATFORM_ANDROID)
#include <android/native_window.h>
#include <android/native_activity.h>
#include <unordered_set>
#include <game-activity/native_app_glue/android_native_app_glue.h>
namespace Arieo
{
    class AndroidWindow final
        : public Interface::Window::IWindow
    {
    public:
        AndroidWindow(Interface::Window::IWindowManager* window_manager, android_app* android_app)
            : m_window_manager(window_manager), m_android_app(android_app)
        {
        }

        std::uint64_t getWindowHandle() override
        {
            return reinterpret_cast<std::uint64_t>(m_android_app->window);
        }

        Base::Math::Rect<std::uint32_t> getWindowRect() override
        {
            if (m_android_app->window == nullptr) {
                return Base::Math::Rect<std::uint32_t>(0, 0, 0, 0);
            }

            int32_t width = ANativeWindow_getWidth(m_android_app->window);
            int32_t height = ANativeWindow_getHeight(m_android_app->window);
            
            // Android windows typically start at 0,0 and span full screen
            return Base::Math::Rect<std::uint32_t>(0, 0, width, height);
        }
        
        Base::Math::Vector<std::uint32_t, 2> getFramebufferSize() override
        {
            if (m_android_app->window == nullptr) {
                return Base::Math::Vector<std::uint32_t, 2>(0, 0);
            }

            int32_t width = ANativeWindow_getWidth(m_android_app->window);
            int32_t height = ANativeWindow_getHeight(m_android_app->window);
            return Base::Math::Vector<std::uint32_t, 2>(width, height);
        }
        
        bool isClosed() override
        {
            return m_android_app->window == nullptr;
        }

        Interface::Window::IWindowManager* getWindowManager() override
        {
            return m_window_manager;
        }
        
        Base::StringID getWindowPlatform() override
        {
            return Base::MakeStringID("android");
        }

    private:
        android_app* m_android_app;
        friend class AndroidWindowManager;
        Interface::Window::IWindowManager* m_window_manager;
    };

    class AndroidWindowManager final
        : public Interface::Window::IWindowManager
    {
    protected:
        android_app* m_android_app;
        AndroidWindow* m_android_main_window = nullptr;
    public:
        void initialize(void* app);
        void finalize();

        void* getDisplay() override;

        Interface::Window::IWindow* createWindow(std::uint16_t pos_x, std::uint16_t pos_y, std::uint16_t width, std::uint16_t height) override;
        void destroyWindow(Interface::Window::IWindow*) override;

        Interface::Window::IWindow* getMainWindow() override;

        void onInitialize() override;
        void onTick() override;
        void onDeinitialize() override;

        // Android-specific methods
        ANativeWindow* getCurrentNativeWindow() const;
        
        // Handle Android app lifecycle events
        void handleAppCmd(int32_t cmd);
    };
}

#endif // ARIEO_PLATFORM_ANDROID