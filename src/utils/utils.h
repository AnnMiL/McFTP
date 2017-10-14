#ifndef _UTILS_H 
#define _UTILS_H 


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <time.h>
#include <limits.h>
#include <unistd.h>
// void formatPrintTime(struct timespec);
// using namespace std;



std::string getexepath();

std::string formatString(const std::string& base);
// std::istringstream stringToiss(const std::string& base);


// This function converts a string to a number vector. The  string should be 
// in format: {number1, number2, ..., numbern} or {number1 number2 ... numbern}
template<typename T> 
std::vector<T> stringToVector(std::string const& pointLine)
{
	std::istringstream iss (formatString(pointLine));

	return std::vector<T>{ 
		std::istream_iterator<T>(iss),
		std::istream_iterator<T>()
	};
}

template<typename T> 
void appStringToVector(std::string const& pointLine, std::vector<T>& data)
{
	std::istringstream iss (formatString(pointLine));

	data.insert(data.end(), std::istream_iterator<T>(iss), 
		std::istream_iterator<T>());
}

void dumpLinesSeperator();


template<typename T> 
void dumpVector(std::vector<T> a){
	for (int i = 0; i < int(a.size()); ++i){
		std::cout << a[i];
		if (i < int(a.size())-1){
			std::cout << "\t";
		}
	}
}


template<typename T> 
void dumpMatrix(std::vector<std::vector<T>> a){
	std::cout << "[";
	for (int i = 0; i < int(a.size()); ++i){
		dumpVector(a[i]);
		if (i < int(a.size())-1){
			std::cout << std::endl ;
		}
	}
	std::cout << "]" << std::endl;
	dumpLinesSeperator();
}

template<typename T> 
void dumpMatrix(const std::vector<T>& a){
	std::cout << "[";
	dumpVector(a);
	std::cout << "]" << std::endl ;
	dumpLinesSeperator();
}

template<typename T> 
void displayvector(const std::vector<T>& a, const std::string& name){
	std::cout << name << ": \n";
	dumpMatrix(a);
}

template<typename T> 
void displayvector(const std::vector<std::vector<T>>& a, const std::string& name){
	std::cout << name << ": \n";
	dumpMatrix(a);
}

template<typename T>
std::string vectorTostring(const std::vector<T>& data){
	std::stringstream out;
	for(int i = 0; i < (int)data.size(); i++) {
		out << (double)data[i];
		if ( i != (int)data.size()-1 ){
			out << ", " ;
		}
		
			
	}
	return out.str();
}

template<typename T>
std::vector<std::string> matrixTostring(const std::vector<std::vector<T>>& data){
	std::vector<std::string> ret;

	for (int i = 0; i < (int)data.size(); ++i){
		ret.push_back(vectorTostring(data[i]));
	}

	return ret;
}

template<typename T>
T* vectorMatrixTo2DArray(const std::vector<std::vector<T>>& data){
	int m = data.size();
	int n = 0;
	if (m > 0){
		n = data[0].size();
	}
	for (int i = 1; i < m; ++i)
	{
		if (data[i].size() != n){
			std::cout << "vectorMatrixTo2DArray: data is not a matrix! " << std::endl;
			return NULL;
		}
	}

	T* ret = new T[m*n];

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			ret[i + j*m] = data[i][j];
		}
	}

	return ret;

}


template<typename T>
std::vector<std::vector<T>>  vector2DArrayToVectorMatrix(T  data[], int m, int n){
	std::vector<std::vector<T>> ret;
	ret.reserve(m);

	for (int i = 0; i < m; ++i)
	{
		std::vector<T> temp ;
		temp.reserve(n);
		for (int j = 0; j < n; ++j)
		{
			temp.push_back(data[i + j*m]);
		}
		ret.push_back(temp);
	}

	return ret;

}




void matrixAAndBToWAndV(
	int N,
	double A[],
	double B[],
	double period,
	double **W,
	double **V,
	int nLoops);


#endif