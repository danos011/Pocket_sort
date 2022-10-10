#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

const std::string ERROR_FILE_NOT_OPEN = "Error: incorrect file name ";
const std::string ERROR_NOT_POSITIVE_INTEGER_NUMBER = "Error: it must be a positive integer number! ";
const std::string ERROR_WRONG_CONTENT_OF_FILE = "Error: it must be an integer number in file! ";
const std::string OUT_FILE_NAME = "result.txt";

const std::string inputFileName() {
    std::string fileName;
    std::cout << "Enter a name of input file: " << std::endl;
    std::cin >> fileName;
    return fileName;
}

std::basic_ifstream<char> openFile(const std::string& fileName, int *x, int *y) {
    std::ifstream fileIn(fileName, std::ifstream::in);
    std::string size;
    int flag = 0;

    if (!fileIn.is_open()) {
        throw ERROR_FILE_NOT_OPEN + fileName;
    }

    getline(fileIn,size);
    for (size_t i = 1; i < 100; i++) {
        if (size == std::to_string(i)) {
            flag = 1;
            break;
        }
    }

    if (!flag) {
        throw ERROR_NOT_POSITIVE_INTEGER_NUMBER + fileName;
    }
    flag = 0;
    *x = std::stoi(size);

    getline(fileIn,size);
    for (size_t i = 1; i < 100; i++) {
        if (size == std::to_string(i)) {
            flag = 1;
            break;
        }
    }

    if (!flag) {
        throw ERROR_NOT_POSITIVE_INTEGER_NUMBER + fileName;
    }
    *y = std::stoi(size);
    return fileIn;
}

std::basic_ofstream<char> closeFile(const std::string& fileName) {
    std::ofstream fileOut(fileName, std::ifstream::out);

    if (!fileOut.is_open()) {
        throw ERROR_FILE_NOT_OPEN + fileName;
    }
    return fileOut;
}

void countStrings(const int x, const int y, const int mass[5][5]) {
    int flag = 1;
    int counter = 0;

    for(size_t i = 0; i < x ; i++)
    {
        for(int j = 0; j < y ; j++)
        {
            if(mass[i][j] == 0) {
                flag = 0;
                break;
            }

            if(!flag){
                counter++;
                flag = 1;
            }
        }
    }
    std::basic_ofstream<char> fileOut = closeFile(OUT_FILE_NAME);
    fileOut << counter;
    fileOut.close();
}

void findNumPoints(const int **array, std::ofstream& fileOut ,const int x, const int y) {
    int flag1 = 0;
    int flag2 = 0;
    int counter = 0;
    for(size_t i = 0;i < x;i++)
    {
        for(size_t j = 0; j < y; j++)
        {
            for(size_t o = 0; o < y; o++)
            {
                if(array[i][j] > array[i][o] && j != o){
                    flag1 = 1;
                    break;
                }
            }

            if(flag1) {
                flag1 = 0;
                continue;
            }

            for(size_t n = 0; n < x; n++)
            {
                if(array[i][j] < array[n][j] && i != n){
                    flag2 = 1;
                    break;
                }
            }

            if(!flag1 && !flag2){
                counter++;
            }
            else{
                flag1 = flag2 = 0;
            }
        }
    }

    fileOut << counter;
}

void fillArray(int **array, std::ifstream& fileIn ,const int x, const int y) {

    for(size_t i = 0; i < x; i++)
    {
        for(size_t j = 0; j < y; j++)
        {
            if(!fileIn){
                throw ERROR_WRONG_CONTENT_OF_FILE;
            }
            fileIn >> array[i][j];
        }
    }
}

void countSaddlePoints()
{
    int x;
    int y;

    std::basic_ifstream<char> fileIn = openFile(inputFileName(),&x,&y);
    std::basic_ofstream<char> fileOut = closeFile(OUT_FILE_NAME);
    int ** dynamicMatrix = new int*[x];

    for(size_t i = 0; i < x; ++i)
        dynamicMatrix[i] = new int[y];

    fillArray(dynamicMatrix,fileIn,x,y);
    findNumPoints((const int **)dynamicMatrix,fileOut,x,y);

    delete[] dynamicMatrix;
    fileOut.close();
    fileIn.close();
}

int main()
{
    const int staticMatrix[5][5] = {0, 2 , 3 , 4 , 5,
                              1, 3, 6, 0 , 1,
                              2, 0, 4, 4, 4,
                              2, 3, 1, 2, 9,
                              7, 8, 4, 5, 3};
    int choice = 0;
    int flag = 0;

    try {

        std::cout << "Enter a number of task: " << std::endl;
        std::cin >> choice;

        if(!std::cin){
            throw ERROR_NOT_POSITIVE_INTEGER_NUMBER;
        }

        switch (choice) {
            case 1:
                countStrings(5, 5, staticMatrix);
                break;
            case 2:
                countSaddlePoints();
                break;
        }
    }
    catch (std::string error)
    {
        std::cerr << std::endl << error << std::endl;
        flag = -1;
    }
    return flag;
}
