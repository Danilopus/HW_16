#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <algorithm>
//#include <array>

//----------- INTEGER Input filtrers -------------------------------
int Get_Int_SA();				// String-analysis вариант фильтра INTEGER
int Get_Int_Positive();			// String-Analysis вариант проверки ввода INTEGER_POSITIVE		
int Get_Int_PG();				// peek&get вариант проверки ввода INTEGER	

//----------- DOUBLE Input filtrers --------------------------------
double Get_Dbl_SA();		// String-analysis вариант фильтра DOUBLE. дописать защиту от "", -5---, 6.55.55
double Get_Dbl_Positive();	// String-analysis вариант фильтра DOUBLE_POSITIVE
double Get_Dbl_PG();		// peek&get вариант проверки ввода DOUBLE	
int Get_Random_Int(int Range_min, int Range_max);

// Homework 16 -----------------------------------------------------
int Average_of_random_array()
{

	int const Size = 10;
	int Random_Array[Size] = {}, Summ = {};
	srand(time(NULL));
	for (int i = 0; i < Size; i++)
	{
		Random_Array[i] = Get_Random_Int(0, 100);
		Summ += Random_Array[i];
		std::cout << Random_Array[i] << " ";
	}
	double Average = double(Summ) / Size;
	std::cout << "\nAverage of array: " << Average;
	int Counter = 0;
	for (int i = 0; i < Size; i++)
	{

		if (Random_Array[i] < Average) Counter++;
	}
	std::cout << "\nElements under Average: " << Counter;
	return 0;
}
int Transforming_number_into_array()
{

	std::cout << "\nEnter number to transform [6-digit]: ";
	int Number_to_transform = Get_Int_Positive();
	int Destination_Array[6] = {};
	if (Number_to_transform < 1e5 && Number_to_transform >= 1e6) 
	{
		std::cout << "\nError. Exiting..."; 
		return 0;
	}
	std::cout << "\nArray: ";
	for (int i = 0; i < 6; i++)
	{
		Destination_Array[i] = (Number_to_transform % int(pow(10, 6 - i))) / pow(10, 5 - i);
	}
	for (int i = 0; i < 6; i++)
	{
		std::cout << Destination_Array[i] << ", ";
	}
	std::cout <<  "\b\b ";
	return 0;
}
int Summ_of_two_arrays()
{	
	int Array_1[5][5] = {}, Array_2[5][5] = {}, Array_3[5][5] = {};
	for (int i = 0; i < 5 ;i++)
	{
		for (int p = 0; p < 5; p++)
		{
			Array_1[i][p] = Get_Random_Int(100, 499);
			Array_2[i][p] = Get_Random_Int(100, 499);
			Array_3[i][p] = Array_1[i][p] + Array_2[i][p];
		}
		std::cout << "{ ";
		for (int p = 0; p < 5; p++)
			std::cout << Array_1[i][p] << ", ";
		std::cout << "\b\b }\t{ ";
		if (i == 2) std::cout << "\b\b\b\b\b+  { ";
		for (int p = 0; p < 5; p++)
			std::cout << Array_2[i][p] << ", ";
		std::cout << "\b\b }\t{ ";
		if (i == 2) std::cout << "\b\b\b\b\b=  { ";
		for (int p = 0; p < 5; p++)
			std::cout << Array_3[i][p] << ", ";
		std::cout << "\b\b }\n";
	}	
	return 0;
}

// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	setlocale(LC_CTYPE, "Russian");
	system("mode con cols=100 lines=40"); // ??? текст основного меню не входит в окно консоли по умолчанию. При небольшом увеличении окна (lines < 85) пропадает полоса прокрутки, что не здорово. Как ee оставить и не делать (lines > 85)?
	std::string Name_of_Work = { "Home Work 16" };
	std::string Menu_Element_1 = { "Average of random array[10]" };
	std::string Menu_Element_2 = { "Summ of two arrays[5][5]" };
	std::string Menu_Element_3 = { "Transforming number into array[6]" };
	
	do {		
		system("cls");
		std::cout << "\n\t***\t***\t" << Name_of_Work << "\t***\t***\n\n\t\n\nChoose an opion: \n";
		std::cout << "\n 1. " << Menu_Element_1;
		std::cout << "\n 2. " << Menu_Element_2;
		std::cout << "\n 3. " << Menu_Element_3;
		std::cout << "\n\n 0. Exit\n";
		int choice = 0;
		std::cout << "\nYour choice: ";
		choice = Get_Int_Positive();		
		std::cout << "\n";
		// Обработка выбора пользователя
		if		(choice == 0) { std::cout << "\nGood By"; for (int j = 0; j < 50; j++){ Sleep(50 - j); std::cout << "y"; } std::cout << "e!"; Sleep(850);  return 0; }
		else if (choice == 1) Average_of_random_array();
		else if (choice == 2) Summ_of_two_arrays();
		else if (choice == 3) Transforming_number_into_array();
	
		else { std::cout << "\nSuch choice does not exist yet\n"; Sleep(1000); }
		std::cout << "\n\n";
		system("pause");
		} while (true);
		
	//system("pause");
	return 0;
}

// Вспомагательные функции -----------------------------------------
int Get_Int_SA() {
	std::string a;
	std::cin.sync(); // заклинание средней силы против неудачного чтения getline
	std::cin.clear(); // заклинание малой силы против неудачного чтения getline
	getline(std::cin, a);
	//std::cout << "\nFunction: working with " << a << "\n"; для отладки
	if (a != "")
	{

		if ((a.find_first_not_of("-0123456789") == -1))
		{
			for (int i = 1; i < a.size(); i++) // определяем есть ли минусы кроме первого символа
			{
				if (a[i] == '-') 
				{
					std::cout << "Input Error: Minus misstanding\n";
					return Get_Int_SA();
				}
			}
			try
			{
				return stoi(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow\n";
				return Get_Int_SA();
			}


		}
		else
		{
			std::cout << "Input Error: Incorrect symbol\n";
			return Get_Int_SA();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input\n";
		return Get_Int_SA();
	}
}
int Get_Int_Positive()
{
	std::string a;
	std::cin.sync();
	std::cin.clear();
	//std::cin.ignore(1024, '\n');
	getline(std::cin, a);
	if (a != "") // оказывается getline считывает пустую строку которую stoi уже не берет
	{

		if ((a.find_first_not_of("0123456789") == -1))
		{
			try{
				return stoi(a);
			}
			catch (std::out_of_range){
				std::cout << "Incorrect input: INTEGER overflow. Decrease input\n";
			}
		}
		else
		{
			std::cout << "Incorrect symbols: positive INTEGER expected. Try again...\n";
			return Get_Int_Positive();
		}
		//return Get_Int_Positive();
	}
	else
		std::cout << "Input Error: NULL input\n";
	return Get_Int_Positive();
}
int Get_Int_PG()
{
	int a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! Repeat please...\n";
	}
	return a;
}
double Get_Dbl_SA(){
	std::string a;
	std::cin.sync();
	getline(std::cin, a);
	if (a == "") { std::cout << "\nInput Error : NULL input\n"; return Get_Dbl_SA(); }
	if ((a.find_first_not_of("-.0123456789") == -1))
	{
		for (int i = 1; i < a.size(); i++) // Проверяем отсутсвие лишних минусов
		{
			if (a[i] == '-')
			{
				std::cout << "\nInput Error: Minus misstanding\n";
				return Get_Dbl_SA();
			}

		}
		bool Dot_Flag = 0;
		for (int i = 0; i < a.size(); i++) // проверяем отсутсвие лишних точек
		{
			if (a[i] == '.')
			{
				if (Dot_Flag == 1)
				{
					std::cout << "\nInput Error: Dot misstandig\n";
					return Get_Dbl_SA();
				}
				Dot_Flag = 1;
			}

		}		 	
				try{
					return stod(a);
				}
				catch (std::out_of_range) {
					std::cout << "Data type overflow\n";
					return Get_Dbl_SA();					
				}						
	}
	else {		
		std::cout << "Incorrect symbols: REAL expected.\nUse dot instead of coma. Example 50.64\n";
		return Get_Dbl_SA();
	}
}
double Get_Dbl_Positive(){
	std::string a, dot = "."; // = "";
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "")
	{
		if ((a.find_first_not_of(".0123456789") == -1))
		{
			bool One_Dot_already = false;
			for (int i = 0; i < a.size(); i++)
			{
				//std::cout << "\na[" << i << "] ->" << a[i]<< " == " <<dot[0];
				//std::cout << "\nflag -> " << One_Dot_already;
				if (a[i] == dot[0] && One_Dot_already == true) //проверяем количество разделителей
				{
					std::cout << "dot placement error\n";
					return Get_Dbl_Positive();
				}
				if (a[i] == dot[0])	One_Dot_already = true;
			}
			try
			{
				//std::cout << "trying stod: " << a;
				//system("pause");
				return stod(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Incorrect input: Data type [DOUBLE] overflow. Decrease input\n";
				return Get_Dbl_Positive();
			}
		}
		else
		{
			//std::cout << "Incorrect symbols: positive REAL expected.\nUse coma instead of dot. Example 50,64\n"; // да точно говорю вот даже сообщение такое было, а теперь наоборот wtf*2?!
			std::cout << "Incorrect symbols: positive REAL expected.\nUse dot instead of coma. Example 50.64\n";
			return Get_Dbl_Positive();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input\n";
		return Get_Dbl_Positive();
	}
	return Get_Dbl_Positive();
}
double Get_Dbl_PG()
{
	double a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! Repeat please...\n";
	}
	return a;
}
int Get_Random_Int(int Range_min, int Range_max)
{
	if (Range_min > Range_max) 
	{ 
		std::cout << "\nError: Range_min > Range_max. New range: [Range_max..Range_min]\n";
		std::swap(Range_min, Range_max);
	}
	//srand(time(NULL));
	return (Range_min + rand() % (Range_max - Range_min + 1));
}