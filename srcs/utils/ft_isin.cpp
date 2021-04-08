#include <string>

bool    ft_isin(const char &c, const std::string &str) {
	std::string::const_iterator it, ite = str.end();

	for (it = str.begin(); it != ite; ++it)
		if (*it == c)
			return (true);
	return (false);
}
