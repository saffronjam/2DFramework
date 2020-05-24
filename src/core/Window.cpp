#include "Window.h"

sf::RenderWindow *Window::m_sfWindow = nullptr;
std::string Window::m_title("Unnamed window");
sf::VideoMode Window::m_videomode;
sf::Uint32 Window::m_style;
sf::Vector2i Window::m_nonFullscreenPosition;
bool Window::m_fullscreen;

Window::~Window()
{
    delete m_sfWindow;
    m_sfWindow = nullptr;
}

void Window::Create(const std::string &title, int width, int height)
{
    m_videomode = sf::VideoMode(width, height);
    m_style = sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close;

    m_sfWindow = new sf::RenderWindow(m_videomode, title, m_style, sf::ContextSettings());
    SetTitle(title);
    PositionCenter();
}

void Window::Draw(const sf::Drawable &drawable, sf::RenderStates renderStates)
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    m_sfWindow->draw(drawable, renderStates);
}

void Window::Clear()
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    m_sfWindow->clear();
}

void Window::Present() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    m_sfWindow->display();
}

void Window::PositionCenter() noexcept
{
    sf::VideoMode max = sf::VideoMode::getDesktopMode();
    sf::Vector2i halfSize = sf::Vector2i(m_sfWindow->getSize().x / 2u, m_sfWindow->getSize().y / 2u);
    m_sfWindow->setPosition(sf::Vector2i(max.width, max.height) / 2 - halfSize);
}

sf::RenderWindow *Window::GetSFWindow() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    return m_sfWindow;
}

sf::Vector2i Window::GetPosition() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    return m_sfWindow->getPosition();
}

sf::Vector2u Window::GetSize() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    return m_sfWindow->getSize();
}

int Window::GetWidth() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    return GetSize().x;
}

int Window::GetHeight() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    return GetSize().y;
}

const std::string &Window::GetTitle() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    return m_title;
}

sf::View Window::GetCurrentView() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    return m_sfWindow->getView();
}

sf::View Window::GetDefaultView() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    return m_sfWindow->getDefaultView();
}

sf::IntRect Window::GetScreenRect() noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    return sf::IntRect(0, 0, GetWidth(), GetHeight());
}

void Window::SetPosition(const sf::Vector2i &pos) noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    m_sfWindow->setPosition(pos);
}

void Window::SetSize(const sf::Vector2u &size) noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    m_sfWindow->setSize(size);
}

void Window::SetTitle(const std::string &title) noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    m_sfWindow->setTitle(title);
}

void Window::SetIcon(const std::string &icon) noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    sf::Image image;
    image.loadFromFile(icon);
    m_sfWindow->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

void Window::SetFullscreen(bool toggle) noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    if (toggle && !m_fullscreen)
    {
        m_fullscreen = true;
        m_videomode.width = GetSize().x;
        m_videomode.height = GetSize().y;
        m_nonFullscreenPosition = GetPosition();
        m_sfWindow->create(sf::VideoMode::getFullscreenModes()[0], GetTitle(), sf::Style::Fullscreen);
    }
    else if (!toggle && m_fullscreen)
    {
        m_fullscreen = false;
        m_sfWindow->create(m_videomode, GetTitle(), m_style);
        SetPosition(m_nonFullscreenPosition);
    }
}

void Window::SetVSync(bool toggle) noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    m_sfWindow->setVerticalSyncEnabled(toggle);
}

void Window::SetView(const sf::View &view) noexcept
{
    assert("Attempted to handle the window without creating it" && m_sfWindow);
    m_sfWindow->setView(view);
}

Window::Exception::Exception(int line, const char *file, const char *errorString) noexcept
    : VeException(line, file),
      errorString(errorString)
{
}

const char *Window::Exception::what() const noexcept
{
    std::ostringstream oss;
    oss << "[Type] " << GetType() << std::endl
        << "[Description] " << GetErrorString() << std::endl
        << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char *Window::Exception::GetType() const noexcept
{
    return "V-2DEngine Window Exception";
}

const char *Window::Exception::GetErrorString() const noexcept
{
    return errorString.c_str();
}