#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

#ifndef Bin_H
#define Bin_H


class Bin{

private:
  int total;
  int capacity;
  vector<int> list;
public:
  Bin();
  void add(int num);
  bool isSpace(int num);
  int spaceAfterAdd(int num);

  int getTotal();
  void printList(ofstream &rawData);


};
#endif
