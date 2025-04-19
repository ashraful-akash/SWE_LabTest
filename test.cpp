#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "pch.h"

using namespace std;

class Window {
public:
    virtual void render() const = 0;
    virtual ~Window() = default;
};

class Scrollbar {
public:
    virtual void render() const = 0;
    virtual ~Scrollbar() = default;
};

class WindowsWindow : public Window {
public:
    void render() const override {
        cout << "Rendering Windows Window\n" << std::flush;
    }
};

class WindowsScrollbar : public Scrollbar {
public:
    void render() const override {
        cout << "Rendering Windows Scrollbar\n" << std::flush;
    }
};

class LinuxWindow : public Window {
public:
    void render() const override {
        cout << "Rendering Linux Window\n" << std::flush;
    }
};

class LinuxScrollbar : public Scrollbar {
public:
    void render() const override {
        cout << "Rendering Linux Scrollbar\n" << std::flush;
    }
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

// Google Test Cases
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
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Rendering Linux Window\nRendering Linux Scrollbar\n");

    delete window;
    delete scrollbar;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
