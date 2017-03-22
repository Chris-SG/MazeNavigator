#pragma once

template<typename T, int width, int height>

class Grid2D
{
private:
public:
	T _data[width*height];

	iterator begin()
	{
		return iterator(_data);
	}

	iterator end()
	{
		return iterator(_data + width*height);
	}

	class iterator
	{
	private:
		T* ptr;
	public:

	};
};