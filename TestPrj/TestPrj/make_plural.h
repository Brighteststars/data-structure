#ifndef MAKE_PLURAL_H
#define MAKE_PLURAL_H
#include <string>

std::string make_plural(size_t sz, const std::string &word, const std::string &ending)
{
	return sz > 1 ? word + ending : word;
}

#endif
