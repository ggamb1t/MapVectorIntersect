#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>


struct VectorMapPair
{
public:
	std::vector<int> vec;
	std::map<std::string, int> map;
};



VectorMapPair Intersection(const std::vector<int> &vec_in, const std::map<std::string, int> &map_in)
{ 
	VectorMapPair vec_map_pair;
	std::vector<int> vec_out;
	std::map<std::string, int> map_out;
	bool intersection_found; // If an intersection was found at this iteration
	for (auto& it_vec : vec_in)
	{
		intersection_found = false;
		for (auto& it_map : map_in)
		{
			if (it_vec == it_map.second)
			{
				if (!intersection_found)
				{
					vec_out.push_back(it_vec);
					intersection_found = true;
				}
				map_out.emplace(it_map.first, it_map.second);
			}
		}
	}
	vec_map_pair.vec = vec_out;
	vec_map_pair.map = map_out;
	return vec_map_pair;
}

std::vector<int> ReadVectorData(std::ifstream &in )
{ // Vector Initialization
	std::vector<int> vec;
	int vec_size = 0;
	in >> vec_size;
	int temp_int;
	for (int i = 0; i < vec_size; i++)
	{
		in >> temp_int;
		vec.push_back(temp_int);
	}
	return vec;
}

std::map<std::string, int> ReadMapData(std::ifstream& in) 
{ // Map initialization
	std::map<std::string, int> map;
	int map_size = 0;
	int temp_int;
	std::string temp_str;
	in >> map_size;
	for (int i = 0; i < map_size; i++)
	{
		in >> temp_str;
		in >> temp_int;
		map.emplace(temp_str, temp_int);
	}
	return map;
}

void ShowElements(const std::vector<int> &vec)
{
	std::cout << " \n\n Vector values:\n ";
	for (auto it_vec = vec.begin(); it_vec != vec.end(); it_vec++) 
		std::cout << *it_vec << ' ';
}
void ShowElements(const std::map<std::string, int>& map)
{
	std::cout << " \n\n Map values:\n ";
	for (auto it_map = map.begin(); it_map != map.end(); it_map++)
		std::cout << it_map->first << ' ' << it_map->second << "\n ";
}

bool OpenFile(const std::string path, std::ifstream &in)
{
	in.open(path);
	if (in.is_open())
	{
		return true;
	}
	else
	{
		std::cerr<<"\n File is not found.\n";
		return false;
	}
}

/*
default file to read "text.txt"
*/

int main (int argc, char* argv[])
{
	std::cout << " Usage:\n TrueConfTest.cpp <input_file> \n Parameters:\n -<input_file> \n -file to read(default \"text.txt\")";
	std::ifstream fin; 
	std::string path = (argc > 1)? argv[1]: "text.txt";

	if (OpenFile(path, fin))
	{
		VectorMapPair vm_pair;

		vm_pair.vec = ReadVectorData(fin);
		vm_pair.map = ReadMapData(fin);

		ShowElements(vm_pair.vec);
		ShowElements(vm_pair.map);

		vm_pair = Intersection(vm_pair.vec, vm_pair.map);

		ShowElements(vm_pair.vec);
		ShowElements(vm_pair.map);

		return 0;
	}
	else
	{
		return 1;
	}
}