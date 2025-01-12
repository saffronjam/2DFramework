#pragma once

#include "Saffron/Lighting/Light.h"

namespace Se
{
class PointLight : public Light
{
public:
	using Ptr = std::shared_ptr<PointLight>;

public:
	static auto Create(const sf::Vector2f& position, float radius,
	                   sf::Color color = sf::Color::White) -> PointLight::Ptr;
};
}
