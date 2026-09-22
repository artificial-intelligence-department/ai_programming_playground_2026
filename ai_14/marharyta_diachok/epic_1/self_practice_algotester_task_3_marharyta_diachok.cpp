#include <iostream>
#include <string>

int main() {
int n;
std::cin >> n;

int animal = (n - 2009) % 12;
int colour = (n - 2009) % 10;
std::string colour_result;
std::string animal_result;
if (n >= 2009 && n <= 10e9) {
  if (colour == 0 || colour == 9) {colour_result = "yellow"; } 
else if (colour == 1 || colour == 2) {colour_result = "white";}
else if (colour == 3 || colour == 4) {colour_result = "black";}
else if (colour == 5 || colour == 6) {colour_result = "teal";}
else if (colour == 7 || colour == 8) {colour_result = "red";}


if (animal == 0) {animal_result = "ox";}
else if (animal == 1) {animal_result = "tiger";}
else if (animal == 2) {animal_result = "rabbit";}
else if (animal == 3) {animal_result = "dragon";}
else if (animal == 4) {animal_result = "snake";}
else if (animal == 5) {animal_result = "horse";}
else if (animal == 6) {animal_result = "sheep";}
else if (animal == 7) {animal_result = "monkey";}
else if (animal == 8) {animal_result = "rooster";}
else if (animal == 9) {animal_result = "dog";}
else if (animal == 10) {animal_result = "pig";}
else if (animal == 11) {animal_result = "rat";}
  

std::cout << colour_result << " " << animal_result;}
else {}

    return 0;
}