#pragma once
#include "Config.hpp"
#include "GrayscalePlotter.hpp"
#include "Plotter.hpp"
#include <memory>

namespace plotter
{

class PlotterFactory
{
public:
	static std::unique_ptr<Plotter> CreatePlotter(const PlotterConfig& config)
	{
		if (config.plotter_type == "grayscale")
		{
			return std::make_unique<GrayscalePlotter>(config.width, config.height, config.background_char, config.palette);
		}
		else
		{
			return std::make_unique<Plotter>(config.width, config.height, config.background_char);
		}
	}
};

} // namespace plotter