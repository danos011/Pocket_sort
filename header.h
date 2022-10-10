#ifndef LAB5_HEADER_H
#define LAB5_HEADER_H

#endif //LAB5_HEADER_H
const std::string inputFileName()
int countStrings(const int x, const int y, const int mass[5][5])
std::basic_ifstream<char> openFile(const std::string& fileName, int *x, int *y)
std::basic_ofstream<char> closeFile(const std::string& fileName)
void findNumPoints(const int **array, std::ofstream& fileOut ,const int x, const int y)
void fillArray(int **array, std::ifstream& fileIn ,const int x, const int y)
void countSaddlePoints()