#include "GamePCH.h"
#include "Utilities.h"
#include <string>
using namespace std;

bool Utils::CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string str = lua_tostring(L, -1);
		cout << "Error: " << str << " -- LUA failed a check with value: " << r << endl;
		return false;
	}
	return true;
}
