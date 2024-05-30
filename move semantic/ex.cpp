#include <iostream>
class Vector
{
private:
	int* data;
	int size;
	int capacity;
public:
	Vector(int c) : capacity(c), size(0)
	{
		data = new int[capacity];
		std::cout << "base\n";
	}
	Vector(const Vector& v) :size(v.size), capacity(v.capacity) {
		std::cout << "Copy\n";
		data = new int[capacity];
		for (int i = 0; i < size; i++)
		{
			data[i] = v.data[i];
		}
	}
	Vector(Vector&& v) :size(v.size), capacity(v.capacity), data(v.data) {
		std::cout << "Move\n";
		v.size = 0;
		v.capacity = 0;
		v.data = nullptr;
	}
	bool push(int x)
	{
		if (capacity > size)
		{
			data[size] = x;
			size++;
			return true;
		}
		return false;
	}
	void print_size() const {
		std::cout << size << std::endl;
	}
	Vector& operator=(const Vector& v)
	{
		if (this != &v)
		{
			delete[] data;
			size = v.size;
			capacity = v.capacity;
			data = new int[capacity];
			for (int i = 0; i < size; i++)
			{
				data[i] = v.data[i];
			}
		}
		std::cout << "Copy\n";
		return *this;
	}

	Vector& operator=(Vector&& v) noexcept
	{
		if (this != &v)
		{
			delete[] data;
			size = v.size;
			capacity = v.capacity;
			data = v.data;
			v.size = 0;
			v.capacity = 0;
			v.data = nullptr;
			delete[] v.data;
		}
		std::cout << "Move\n";
		return *this;
	}

};

Vector create_vector(int n) {
	std::cout << "create\n";
	Vector v(n);
	v.push(3);
	return v;
}

int main()
{
	Vector v(10);
	Vector u(5);
	u = v;
	u = create_vector(5);
}