#include <fstream>
#include <nlohmann//json.hpp>
#include "returnFromJson.h"

using json = nlohmann::json;

std::vector<Vec2> returnValueFromJson(const std::string path, std::string mode) {
	std::ifstream file(path);

	std::vector<Vec2> coordinates;

	if (!file.is_open()) return coordinates;

	json root;
	
	file >> root;

	for (auto& value : root[mode]) {
		Vec2 buf;

		buf.x = value["x"].get<float>();
		buf.y = value["y"].get<float>();

		coordinates.push_back(buf);
	}

	return coordinates;
}
