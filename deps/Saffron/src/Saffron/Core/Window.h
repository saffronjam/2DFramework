#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Saffron/Base.h"
#include "Saffron/Core/TextAlign.h"
#include "Saffron/Libraries/GenUtils.h"
#include "Saffron/Interface/IException.h"

namespace Se
{
class Window
{
	friend class Camera;

public:
	Window(const std::string& title, int width, int height);
	~Window() = default;
	Window(const Window&) = delete;
	auto operator=(const Window&) -> Window& = delete;

	void Draw(const sf::Drawable& drawable, sf::RenderStates renderStates = sf::RenderStates::Default);
	void DrawText(const sf::Text& text, TextAlign align = TextAlign::Left,
	              sf::RenderStates renderStates = sf::RenderStates::Default);
	void DrawPoint(const sf::Vector2f& position, sf::Color color = sf::Color::Red, float radius = 3.0f);
	void DrawRect(const sf::FloatRect& rect, sf::Color fillColor = sf::Color::Red, bool outlined = false,
	              sf::Color outlineColor = sf::Color::Black);
	void DrawLine(const sf::Vector2f& first, const sf::Vector2f& second, sf::Color color = sf::Color::Red);

	void Clear();
	void Display();

	void HandleBufferedEvents();
	void SetEventCallback(Function<void(const sf::Event&)> fn);

	void PositionCenter();

	auto GetNativeWindow() -> sf::RenderWindow&;
	auto GetNativeWindow() const -> const sf::RenderWindow&;

	auto GetPosition() const -> sf::Vector2i;
	auto GetSize() const -> sf::Vector2u;
	auto GetWidth() const -> int;
	auto GetHeight() const -> int;
	auto GetTitle() const -> const std::string&;
	auto GetScreenRect() const -> sf::IntRect;

	auto IsFullscreen() const -> bool { return _fullscreen; }

	void SetPosition(const sf::Vector2i& pos);
	void SetSize(const sf::Vector2u& size);
	void SetTitle(const std::string& title);
	void SetIcon(const std::string& icon);
	void SetFullscreen(bool toggle);
	void SetVSync(bool toggle);

private:
	void Render(const sf::Drawable& drawable, sf::RenderStates renderStates = sf::RenderStates::Default);

private:
	// Used after exiting fullscreen
	sf::VideoMode _videomode;
	std::string _title;
	sf::Uint32 _style;
	sf::RenderWindow _nativeWindow;
	// Used after exiting fullscreen
	sf::Vector2i _nonFullscreenPosition;

	bool _fullscreen;

	Optional<Function<void(const sf::Event&)>> _eventCallback;

public:
	class Exception : public IException
	{
	public:
		Exception(int line, const char* file, const char* errorString);
		auto what() const noexcept -> const char* override;
		auto GetType() const -> const char* override;
		auto GetErrorString() const -> const char*;

	private:
		std::string errorString;
	};
};
}
