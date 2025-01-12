#pragma once

#include <jcv/jc_voronoi.h>
#include <SFML/Graphics.hpp>

#include "Saffron/Base.h"

namespace Se
{
class Voronoi : public sf::Drawable
{
private:
	friend class Polygon;

public:
	class Polygon
	{
	public:
		Polygon(Voronoi& parent, int lineVAIndex, int filledVAIndex, const sf::Vector2f& voronoiPoint,
		        std::vector<sf::Vector2f> points);

		auto operator==(const Polygon& other) const -> bool;

		auto LineVAIndex() const -> int;
		auto FilledVAIndex() const -> int;

		auto Points() const -> const std::vector<sf::Vector2f>&;

		auto FillColor() const -> sf::Color;
		void SetFillColor(sf::Color color);
		void ClearFillColor(sf::Color color);

		auto Neighbors() const -> const std::set<Polygon*>&;
		void AddNeighbor(Polygon* neighbor);

		auto VoronoiPoint() const -> const sf::Vector2f&;
		void SetVoronoiPoint(const sf::Vector2f& voronoiPoint);

		auto ClosestEdge(const sf::Vector2f& position) const -> std::pair<sf::Vector2f, sf::Vector2f>;

	private:
		UUID _uuid;

		Voronoi& _parent;
		int _lineVAIndex;
		int _filledVAIndex;

		sf::Color _fillColor = sf::Color::Transparent;
		std::vector<sf::Vector2f> _points;
		std::set<Polygon*> _neighbors;
		sf::Vector2f _voronoiPoint;
	};

public:
	Voronoi();
	explicit Voronoi(const sf::FloatRect& boundingBox);
	Voronoi(const sf::FloatRect& boundingBox, std::vector<sf::Vector2f> points);
	Voronoi(const sf::FloatRect& boundingBox, int noRandomPoints);
	~Voronoi() override;

	void SetPoints(std::vector<sf::Vector2f> points);
	void SetPoints(int noRandomPoints);
	void SetBoundingBox(const sf::FloatRect& boundingBox);
	void SetOutlineColor(const sf::Color& color);
	void SetFillColor(const Polygon& polygon, sf::Color color);

	void ShowGrid();
	void HideGrid();

	void ShowFilled();
	void HideFilled();

	void Relax(int iterations = 1);

	auto Polygons() const -> const std::vector<Polygon>&;
	auto PolygonAt(const sf::Vector2f& position) -> Polygon&;

	// Manual controls
	void EnableAutomaticGeneration();
	void DisableAutomaticGeneration();

	void ForceGenerate();

private:
	static auto ConvertBoundingBox(const sf::FloatRect& boundingBox) -> jcv_rect;

	void Generate();
	void GeneratePoints(int noPoints);
	void MarkForGeneration();

	void SetupUpdateCallback();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Run::Handle _updateHandle;
	bool _automaticGeneration = true;

	sf::Color _defaultGridColor = sf::Color::Blue;
	std::optional<jcv_diagram> _diagram;
	sf::FloatRect _boundingBox;
	std::vector<sf::Vector2f> _points;

	std::vector<Polygon> _polygons;
	sf::VertexArray _polygonsVA{sf::PrimitiveType::Lines};
	sf::VertexArray _filledPolygonsVA{sf::PrimitiveType::Triangles};
	bool _wantNewPolygonVA = false;

	bool _shouldDrawFilledPolygons = true;
	bool _shouldDrawGrid = true;
};
}
