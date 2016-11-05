#include<errno.h>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<unistd.h>



class UnixOperatingSystem
{
public:
  void pwd();
  void cd(std::string path);
};

void UnixOperatingSystem::pwd()
{
    char path[100];
    getcwd(path, 100);
    std::cout<<path<<std::endl;
}

void UnixOperatingSystem::cd(std::string path)
{
  char* char_path = new char[path.length()+1];
  strcpy(char_path, path.c_str());
  if(chdir(char_path)==-1) {
    printf("%s\n", strerror(errno));
  };
}


// 
// int main()
// {
//   //UnixOperatingSystem *os = new UnixOperatingSystem();
//   return 0;
// }
