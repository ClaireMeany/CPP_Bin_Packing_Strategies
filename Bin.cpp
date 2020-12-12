#include "Bin.h"

//constructor, Bins are set to have capacity 100
Bin::Bin(){
  this->capacity=100;
  total=0;

}
//add a number to a bin
void Bin::add(int num){
  this->list.push_back(num);
  this->total=this->total+num;
}
//check if there is space in bin for a number to be added
bool Bin::isSpace(int num){
  if(num+this->total<=this->capacity){
    return true;
  }
  else{
    return false;
  }
}
//returns how much space would remain if a number is added to a bin
int Bin::spaceAfterAdd(int num){
  if(num+this->total<=this->capacity){
    return this->capacity-(num+this->total);
  }
  else{
    return -1;
  }
}

//gets total occupied space of a bin
int Bin::getTotal(){
  return this->total;
}

//prints the list inside each bin
void Bin::printList(ofstream &rawData){
  //cout << "Printing Bin: ";
  for (int i=0;i<this->list.size();i++){
    rawData << this->list.at(i)<< " ";
  }
  rawData <<endl;
}
