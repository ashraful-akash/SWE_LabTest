#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <gtest/gtest.h>
using namespace std;
class WindowsWindow : public Window {
public: 
    void render() const override {
        cout << "Rendering Windows Window\n";
    }
};
class WindowsScrollbar : public Scrollbar {
public:
    void render() const override {
        cout << "Rendering Windows Scrollbar\n";
    }
};
class LinuxWindow : public Window {
public: 
    void render() const override {
        cout << "Rendering Linux Window\n";
    }
};
class LinuxScrollbar : public Scrollbar {
public:
    void render() const override {
        cout << "Rendering Linux Scrollbar\n";
    }
};
class Window{
public:
    virtual void render() const = 0;
    virtual ~Window() = default;
};
class Scrollbar {
public:
    virtual void render() const = 0;
    virtual ~Scrollbar() = default;
};
class GUIFactory {
public:
    virtual Window* createWindow() const = 0;
    virtual Scrollbar* createScrollbar() const = 0;
    virtual ~GUIFactory() = default;
};
class WindowsFactory : public GUIFactory {
public: 
    Window* createWindow() const override {
        return new WindowsWindow();
    }
    Scrollbar* createScrollbar() const override {
        return new WindowsScrollbar();
    }
};
class LinuxFactory : public GUIFactory {
public:
    Window* createWindow() const override {
        return new LinuxWindow();
    }
    Scrollbar* createScrollbar() const override {
        return new LinuxScrollbar();
    }
};
void renderUI(const GUIFactory& factory) {
    Window* window = factory.createWindow();
    Scrollbar* scrollbar = factory.createScrollbar();
    window->render();
    scrollbar->render();
    delete window;
    delete scrollbar;
}
int main() {
    WindowsFactory windowsFactory;
    LinuxFactory linuxFactory;
    cout << "Windows UI:\n";
    renderUI(windowsFactory);
    cout << "\nLinux UI:\n";
    renderUI(linuxFactory);
    return 0;
}
TEST(WindowsFactoryTest, RenderTest) {
    WindowsFactory factory;
    Window* window = factory.createWindow();
    Scrollbar* scrollbar = factory.createScrollbar();
    testing::internal::CaptureStdout();
    window->render();
    scrollbar->render();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Rendering Windows Window\nRendering Windows Scrollbar\n");
    delete window;
    delete scrollbar;
}
TEST(LinuxFactoryTest, RenderTest) {
    LinuxFactory factory;
    Window* window = factory.createWindow();
    Scrollbar* scrollbar = factory.createScrollbar();
    testing::internal::CaptureStdout();
    window->render();
    scrollbar->render();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Rendering Linux Window\nRendering Linux Scrollbar\n");
    delete window;
    delete scrollbar;
}
