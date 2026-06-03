#pragma once
#include <filesystem>

namespace plotter
{

class DemoRunner
{
public:
	static void RunAllDemos();

	static void DemoBasicPlotter();
	static void DemoGrayscalePlotter();
	static void DemoAdvancedGrayscalePlotter();
	static void DemoFromConfig();
	static void DemoAdvancedShapes();
	static void DemoFilters();
	static void DemoCustomPalettes();
	static void CompareFillAlgorithms();

private:
	static void EnsureDemoDirectory();
	static std::filesystem::path GetDemoPath(const std::string& filename);
};

} // namespace plotter