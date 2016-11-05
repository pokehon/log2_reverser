//Author:	Hung-Xin Chen, Yi-Hao Chen
//License:	GPL-2 | GPL-3 [expanded from: GPL (≥ 2)]

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
// g++ -O3 -o calc calc.cpp --std=c++11
class CSVSolver
{
public:
	CSVSolver(std::string fileName)
	{
		std::cout << "Read file from " << fileName << std::endl;
		if (!open(fileName))
			std::cout << "Open file failed [" << fileName << "]\n";
	}
	bool open(std::string fileName)
	{
		if (file.is_open())
			file.close();
		file.open(fileName);
		return file.is_open();
	}
	std::vector<std::vector<double>> readTable()
	{
		std::vector<double> res;
		dataTable.clear();
		while (1)
		{
			res = readRow();
			if (res.empty())
				break;
			dataTable.push_back(res);
		}
		return dataTable;
	}
	bool writeTable(std::string output_filename)
	{
		std::ofstream file(output_filename);
		std::cout << "Output file to " << output_filename << std::endl;
		if (!file.is_open())
			return false;
		file << std::fixed << std::setprecision(6);
		for (size_t i = 0; i < dataTable.size(); i++)
		{
			for (size_t j = 0; j < dataTable[i].size(); j++)
			{
				file << pow(2.0,dataTable[i][j]);
				if (j != dataTable[i].size() - 1)
					file << ',';
			}
			file << std::endl;
		}
		file.close();
		std::cout << "Finished.\n";
		return true;
	}
private:
	inline std::vector<double> readRow()
	{
		double c;
		std::stringstream ss;
		std::string str;
		std::vector<double> vec;
		if (file.is_open())
		{
			std::getline(file, str);
			ss << str;
			while (std::getline(ss, str, ','))
			{
				std::stringstream cvt(str);
				cvt >> c;
				vec.push_back(c);
			}
		}
		return vec;
	}
	std::vector<std::vector<double>> dataTable;
	std::ifstream file;
};
int main(void)
{
	CSVSolver reader("auxin_microarray_data.csv");
	reader.readTable();
	reader.writeTable("result.csv");
	return 0;
}
