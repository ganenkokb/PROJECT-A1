#include <iostream>
#include <string>
#include <fstream>

class Father
{
public:
    
};
class Child : public Father
{
    
};
int main()
{
    std::string line;
    std::vector<std::string> numbers;
    std::ifstream file("/Users/grpmgk/Desktop/untitled folder/Project/Project/file.txt");
    int what_the_line_counter = 0;
    int n_int;
    int a = 0; int b = 0;
    
    while(getline(file, line)){
        numbers.push_back(line);
    }
    for(std::string nums : numbers){
        for(char n : nums)
        {
            n_int=n-'0';
            if(n == n_int)
            {
                if (what_the_line_counter == 2)
                {
                    a = b = 0;
                    what_the_line_counter = 0;
                }
                if(a == 0)
                {
                    a = n_int;
                }
                else
                {
                    b = n_int;
                    //Создаем обект
                }
                what_the_line_counter += 1;
            }
        }
        std::cout << nums << std::endl;}
    file.close();
    
    return 0;
}
