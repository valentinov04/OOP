#include <iostream>
#include <vector>
#include <functional>
class Set
{
public:
	virtual Set* clone() const = 0;
	virtual ~Set() = default;
	virtual bool isItAMember(int x) const = 0;
	virtual void write(std::ostream& out) const = 0;
	std::vector<int> myvctr;
};
class NaturalNumbers :public Set
{
public:
	Set* clone() const { return new NaturalNumbers(*this); }
	void write(std::ostream& out) const { out << "NaturalNumbers"; }
	bool isItAMember(int x) const
	{
		if (x >= 0)
		{
			return true;
		}
		return false;
	}
};
class EmptySet : public Set {
public:
	Set* clone() const { return new EmptySet(*this); }
	void write(std::ostream& out) const { out << "EmptySet"; }
	bool isItAMember(int x) const { return false; }
};
class Interval :public Set
{
public:
	int a;
	int b;
	Interval(int _a, int _b)
	{
		this->a = _a;
		this->b = _b;
		for (int i = a; i <= b; i++)
		{
			this->myvctr.push_back(i);
		}
	}
	~Interval()
	{
		this->myvctr.clear();
	}
	Set* clone() const { return new Interval(a, b); }
	void write(std::ostream& out) const { out << "x>= " << a << "&& x<=" << b; }
	bool isItAMember(int x) const
	{
		if (x >= a && x <= b)
		{
			return true;
		}
		return false;
	}
};
class Union :public Set
{
private:
	Set* A;
	Set* B;

public:
	Union() = default;
	Union(Set* _A, Set* _B) {
		this->A = _A->clone();
		this->B = _B->clone();
		for (int i = 0; i < A->myvctr.size(); i++)
		{
			this->myvctr.push_back(A->myvctr[i]);
		}
		for (int j = 0; j < B->myvctr.size(); j++)
		{
			this->myvctr.push_back(B->myvctr[j]);
		}
	}
	Union(const Union& other) {
		this->A = other.A->clone();
		this->B = other.B->clone(); for (int i = 0; i < A->myvctr.size(); i++)
		{
			this->myvctr.push_back(A->myvctr[i]);
		}
		for (int j = 0; j < B->myvctr.size(); j++)
		{
			this->myvctr.push_back(B->myvctr[j]);
		}
	}
	~Union() {
		delete this->A;
		delete this->B;
		this->myvctr.clear();
		std::cout << "deleted Union\n";
	}
	Set* clone() const { return new Union(*this); }
	void write(std::ostream& out) const {
		A->write(out);
		out << ',';
		B->write(out);
	}
	bool isItAMember(int x) const { return A->isItAMember(x) || B->isItAMember(x); }

};
class Intersect :public Set
{
private:
	Set* A;
	Set* B;

public:
	Intersect() = default;
	Intersect(Set* _A, Set* _B) {
		this->A = _A->clone();
		this->B = _B->clone();
		for (int i = 0; i < A->myvctr.size(); i++)
		{
			this->myvctr.push_back(A->myvctr[i]);
		}
		for (int j = 0; j < B->myvctr.size(); j++)
		{
			this->myvctr.push_back(B->myvctr[j]);
		}
	}
	Intersect(const Intersect& other) {
		this->A = other.A->clone();
		this->B = other.B->clone();
		for (int i = 0; i < A->myvctr.size(); i++)
		{
			this->myvctr.push_back(A->myvctr[i]);
		}
		for (int j = 0; j < B->myvctr.size(); j++)
		{
			this->myvctr.push_back(B->myvctr[j]);
		}
	}
	~Intersect() {
		delete this->A;
		delete this->B;
		this->myvctr.clear();
		std::cout << "deleted Intersect\n";
	}
	Set* clone() const { return new Intersect(*this); }
	void write(std::ostream& out) const {
		A->write(out);
		out << " Intersect ";
		B->write(out);
	}
	bool isItAMember(int x) const { return A->isItAMember(x) || B->isItAMember(x); }

};
class Filter :public Set
{
private:
	Set* A;
	std::string str;
public:
	std::vector<int> vctrFiltered;
	Filter() = default;
	Filter(Set* _A, std::function<std::vector<int>(std::vector<int>)> f, std::string _str) {
		this->A = _A->clone();
		vctrFiltered.clear();
		vctrFiltered = f(_A->myvctr);
		this->A->myvctr = vctrFiltered;
		str = _str;
	}
	Filter(Set* _A, Set* _B, char* typeOf_B, std::string _str) {
		this->A = _A->clone();
		if (typeOf_B == "NaturalNumbers")
		{
			vctrFiltered.clear();
			for (int i = 0; i < A->myvctr.size(); i++)
			{
				if (A->myvctr[i] >= 0)
				{
					vctrFiltered.push_back(A->myvctr[i]);
				}
			}
			A->myvctr = vctrFiltered;
		}
		else if (typeOf_B == "EmptySet")
		{
			//nothing happens
		}
		else if (typeOf_B == "Interval")
		{
			vctrFiltered.clear();
			for (int i = 0; i < A->myvctr.size(); i++)
			{
				if (A->myvctr[i] >= _B->myvctr[0] && A->myvctr[i] <= _B->myvctr[_B->myvctr.size() - 1])
				{
					vctrFiltered.push_back(A->myvctr[i]);
				}
			}
			A->myvctr = vctrFiltered;
		}
		str = _str;
	}
	~Filter() {
		delete this->A;
		A->myvctr.clear();
		std::cout << "deleted Filter\n";
	}
	Set* clone() const { return new Filter(*this); }
	void write(std::ostream& out) const {
		A->write(out);
		std::cout << " | ";
		out << str;
	}
	bool isItAMember(int x) const
	{
		for (int i = 0; i < vctrFiltered.size(); i++) {
			if (vctrFiltered[i] == x)
			{
				return true;
			}
		}
		return false;

	}
};
class Series :public Set
{
private:
	Set* A;
	std::string str;
public:
	std::vector<int> vctrFiltered;
	Series() = default;
	Series(Set* _A, std::function<std::vector<int>(std::vector<int>)> f, std::string _str) {
		this->A = _A->clone();
		vctrFiltered = f(_A->myvctr);
		this->A->myvctr = vctrFiltered;
		str = _str;
	}
	~Series() {
		delete this->A;
		this->myvctr.clear();
		std::cout << "deleted Series\n";
	}
	Set* clone() const { return new Series(*this); }
	void write(std::ostream& out) const {
		out << str << " | ";
		A->write(out);
	}
	bool isItAMember(int x) const
	{
		for (int i = 0; i < vctrFiltered.size(); i++) {
			if (vctrFiltered[i] == x)
			{
				return true;
			}
		}
		return false;

	}
};
class Family :public Set
{
public:
	std::vector<Set*> vctrForAllSets;
	Family() = default;

	~Family() {
		this->vctrForAllSets.clear();
		std::cout << "deleted Family\n";
	}
	void addSet(Set* set)
	{
		vctrForAllSets.push_back(set);
	}

	Family operator+ (Set* newSet)
	{
		this->vctrForAllSets.push_back(newSet);
		return *this;
	}

	Family operator+= (Set* newSet)
	{
		this->vctrForAllSets.push_back(newSet);
		return *this;
	}
	Set* clone() const { return new Family(*this); }
	void write(std::ostream& out) const {
		for (int i = 0; i < vctrForAllSets.size(); i++)
		{
			vctrForAllSets[i]->write(out);
			out << ',';
		}
	}
	bool isItAMember(int x) const
	{
		for (int i = 0; i < vctrForAllSets.size(); i++) {
			for (int j = 0; j < vctrForAllSets[i]->myvctr.size(); j++)
			{
				if (vctrForAllSets[i]->myvctr[j] == x)
				{
					return true;
				}
			}
		}
		return false;

	}
};

std::vector<int> myFunction(std::vector<int> _vctr) {
	std::vector<int> myvctr;
	for (int i = 0; i < _vctr.size(); i++)
	{
		myvctr.push_back(_vctr[i] * _vctr[i]);
	}
	return myvctr;
}
int main()
{
	//Interval interval(0, 10);
	//std::string str = "n*n";
	//std::vector<int> vctr;
	//vctr.push_back(10);
	//Series(interval, myFunction(vctr), str);
}
