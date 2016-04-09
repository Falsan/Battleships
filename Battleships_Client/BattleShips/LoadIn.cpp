#include "LoadIn.h"
#include <fstream>
#include <iostream>



std::vector<Cell*> LoadIn::loadFile(std::string _fileName)
{
	std::vector<Cell*> saveVector;
	_fileName.append(".txt");
	int HOLD;
	std::ifstream outFile(_fileName);

	if (outFile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				//Pull out the value stored in the save file and place it in to the save vector
				outFile >> HOLD;
				saveVector[(i*10) + j]->setType(HOLD);
			}
		}
		outFile.close();
	}
	else
	{
		std::cout << "Error could not find save file" << std::endl;
	}
	return saveVector;
}

bool LoadIn::saveFile(std::vector<Cell*> _saveVector,std::string _saveName)
{
	std::ofstream saveFile(_saveName);
	
	if (saveFile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				saveFile << _saveVector[(i*10)+j];
			}
			saveFile << "\n";
		}

		saveFile.close();
	}
	else
	{
		std::cout <<  "Error could not save file" << std::endl;
		return false;
	}
	return true;
}
