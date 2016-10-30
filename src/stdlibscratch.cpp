#include <string>
#include <fmt/format.h>


int main(int argc, char const* argv[])
{
	fmt::print(stdout, "Don't {}!", "panic");
	
	return 0;
}

