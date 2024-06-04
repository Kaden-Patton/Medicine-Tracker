#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>
#include "Database.h"
#include "Record.h"
class Menu
{
public:

	static bool isRunning;
	static void Display();

	

private:

	static std::vector<std::string> options;
	static void RenderOptions();
	static std::string GetInput();
	static void ClearScreen();
	static void ViewRecords();
	static void InsertRecord();
	static void DeleteRecord();
};

