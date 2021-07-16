#pragma once

namespace Utilities
{
	[[nodiscard("We want to use the contents of the file we loaded")]]
		std::string LoadCompleteFile(std::string& filename);

	[[nodiscard("We want to use the contents of the file we loaded")]]
		std::string LoadCompleteFileFromData(std::string& filename);

	[[nodiscard("We want to use the contents of the file we loaded")]]
		std::string LoadCompleteFileFromData(std::string&& filename);

	[[nodiscard("We want to use the contents of the file we loaded")]]
		std::string LoadShaderFromData(std::string& filename);
};

