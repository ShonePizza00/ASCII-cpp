#include "Config.hpp"
#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include "json.h"

namespace plotter {

	PlotterConfig Config::LoadFromFile(const std::string& filename) {
		std::ifstream input(filename);
		if (!input) {
			throw std::runtime_error("Cannot open config file: " + filename);
		}
		return LoadFromString(input);
	}

	PlotterConfig Config::LoadFromString(std::istream& json_str) {
		const json::Document doc = json::Load(json_str);
		const auto& root = doc.GetRoot().AsMap();
		PlotterConfig config = DefaultConfig();

		auto width_it = root.find("width");
		if (width_it == root.end()) {
			throw std::invalid_argument("Missing field in the config: width");
		}
		config.width = width_it->second.AsInt();
		
		auto height_it = root.find("height");
		if (height_it == root.end()) {
			throw std::invalid_argument("Missing field in the config: height");
		}
		config.height = height_it->second.AsInt();

		auto background_it = root.find("background_char");
		if (background_it == root.end()) {
			throw std::invalid_argument("Missing field in the config: background char");
		}
		const std::string& background_str = background_it->second.AsString();
		if (background_str.empty()) {
			throw std::invalid_argument("Field cannot be empty: background char");
		}
		config.background_char = background_str[0];

		auto plotter_type_it = root.find("plotter_type");
		if (plotter_type_it == root.end()) {
			throw std::invalid_argument("Missing field in the config: plotter_type");
		}
		config.plotter_type = plotter_type_it->second.AsString();

		auto palette_it = root.find("palette");
		if (palette_it != root.end()) {
			config.palette = ParsePalette(palette_it->second.AsString());
		}

		if (!ValidateConfig(config)) {
			throw std::invalid_argument("Invalid config");
		}
		return config;
	}

	bool Config::ValidateConfig(const PlotterConfig& config) {
		if (config.width <= 0) {
			return false;
		}
		if (config.height <= 0) {
			return false;
		}
		if (config.plotter_type != "basic" && config.plotter_type != "grayscale") {
			return false;
		}
		return true;
	}

	PlotterConfig Config::DefaultConfig() {
		PlotterConfig ret;
		ret.width = 60;
		ret.height = 30;
		ret.background_char = '.';
		ret.palette = { ' ', '.', ':', '-', '=', '+', '*', '#', '%', '@' };
		ret.plotter_type = "basic";
		return ret;
	}

	PlotterConfig Config::GetDefaultConfig() {
		return DefaultConfig();
	}

	std::vector<char> Config::ParsePalette(const std::string& palette_str) {
		std::vector<char> palette(palette_str.begin(), palette_str.end());
		return palette;
	}

} // namespace plotter