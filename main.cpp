#include"mytar.h"
using namespace std;
int main(int argc, char **argv){
    check_command(argc);
    TarHeader temp;
    int location = 0;
    while(1){
        if(!access_file(temp, argv[1], location))
            break;
        count_location(location, temp);
    }
    return 0;
}