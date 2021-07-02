#pragma once

namespace Utilities
{
	[[nodiscard("We want to use the contents of the file we loaded")]] 
		FrameworkAPI char* LoadCompleteFile(const char* filename, long* length = nullptr);
	[[nodiscard("We want to use the contents of the file we loaded")]]
		FrameworkAPI char* LoadCompleteFileFromData(const char* filename, long* length = nullptr);
};

