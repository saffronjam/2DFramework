#pragma once

#include <SFML/Graphics/Color.hpp>

#include "Saffron/Base.h"
#include "Saffron/Core/Enums.h"

namespace Se
{
class FadePane
{
public:
	using FadeFn = std::function<uchar(sf::Time, sf::Time)>;


public:
	FadePane(FadeType type, sf::Time duration, sf::Time delay = sf::Time::Zero, bool startOnCreation = false,
	         sf::Color color = sf::Color::Black);
	FadePane(FadeType type, sf::Time duration, FadeFn alphaFunction, sf::Time delay = sf::Time::Zero,
	         bool startOnCreation = false, sf::Color color = sf::Color::Black);

	void OnUpdate();
	void OnGuiRender() const;

	void Start();
	auto IsActive() const -> bool;

public:
	SubscriberList<void> Began;
	SubscriberList<void> Finished;

private:
	auto DefaultAlphaFunction(sf::Time timer, sf::Time duration) const -> uchar;

private:
	FadeType _type;

	FadeFn _alphaFunction;

	bool _wantFade = false;
	sf::Color _fadeColor;

	sf::Time _timer = sf::Time::Zero;
	const sf::Time _duration;

	sf::Time _delayTimer = sf::Time::Zero;
	const sf::Time _delay;
};
}
