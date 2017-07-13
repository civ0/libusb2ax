#ifndef GLOBAL_HPP
#define GLOBAL_HPP

template<class... T> void unused(T&& ...)
{
	// do nothiing.
	// used to suppress unused parameter warnings
}

#endif