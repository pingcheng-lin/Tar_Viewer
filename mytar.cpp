#include"mytar.h"
using namespace std;
void check_command(int num){
    if(num < 2){
        cout << "Need an argument for target.\n";
        exit(0);
    }
    if(num > 2){
        cout << "Too many arguments for target.\n";
        exit(0);
    }
}

int access_file(TarHeader &head, char* name, int location){
    if(!(name[strlen(name)-4] == '.' && name[strlen(name)-3] == 't' && name[strlen(name)-2] == 'a' && name[strlen(name)-1] == 'r')){
        cout << "mytar: " << name << "c: Cannot open: No such file or directory\n";
        cout << "mytar: " << "Error is not recoverable: exiting now\n";
        exit(0);
    }
    ifstream file(name);
    if(!file.is_open()){
        cout << "file open error";
        exit(0);
    }

    file.seekg(location+156,ios::beg);
    file.get(head.type);
    if(head.type == '\0')
        return 0;
    if(location == 0){
        file.seekg(location+257,ios::beg);
        file.read(head.USTAR_id,sizeof(head.USTAR_id));
        check_ustar(head.USTAR_id);
    }

    file.seekg(location+100,ios::beg);
    file.read(head.filemode,sizeof(head.filemode));
    char fmode[11] = {'-'};
    handle_filemode(head, fmode);

    file.seekg(location+265,ios::beg);
    file.read(head.username,sizeof(head.username));

    file.seekg(location+297,ios::beg);
    file.read(head.groupname,sizeof(head.groupname));

    file.seekg(location+124,ios::beg);
    file.read(head.filesize,sizeof(head.filesize));

    file.seekg(location+136,ios::beg);
    file.read(head.mtime,sizeof(head.mtime));

    file.seekg(location,ios::beg);
    file.read(head.filename,sizeof(head.filename));

    output_detail(head, fmode);
    return 1;
}

void check_ustar(char *id){
    if(strcmp(id,"ustar\0"))
        cout << "It is ustar format.\n";
    else{
        cout << "It isn't ustar format.\n";
        exit(0);
    }
}

void handle_filemode(TarHeader &head, char *fmode){
    int num[3];
    num[0] = head.filemode[4]-'0';
    num[1] = head.filemode[5]-'0';
    num[2] = head.filemode[6]-'0';
    if(head.type == '5')
        fmode[0] = 'd';
    int j = 0;
    for(int i = 1; i < 8; i+=3, j++){
        if((num[j]-4) == 0 || (num[j]-4) == 1 || (num[j]-4) == 2 || (num[j]-4) == 3)
            fmode[i] = 'r';
        else
            fmode[i] = '-';
        if((num[j]-2) == 0 || (num[j]-2) == 1 || (num[j]-2) == 4 || (num[j]-2) == 5)
            fmode[i+1] = 'w';
        else
            fmode[i+1] = '-';
        if((num[j]-1) == 0 || (num[j]-1) == 2 || (num[j]-1) == 4 || (num[j]-1) == 6)
            fmode[i+2] = 'x';
        else
            fmode[i+2] = '-';
    }
}

int octal_str_to_dex(char *word){
    int total = 0;
    for(int i = 0; i < strlen(word); i++)
        total += (word[i] - '0') * pow(8,(strlen(word)-i-1));
    return total;
}

void output_detail(TarHeader &head, char *fmode){
    time_t rawtime = octal_str_to_dex(head.mtime);
    struct tm *ptm = localtime(&rawtime);
    cout << fmode << " "
         << head.username << "/" << head.groupname
         << setw(12) << octal_str_to_dex(head.filesize)
         << " " << setw(4) << 1900+ptm->tm_year << "-" << setw(2) << 1+ptm->tm_mon << "-" << setw(2) << ptm->tm_mday << " " << setw(2) << ptm->tm_hour << ":" << setw(2) << ptm->tm_min
         << " " << head.filename << endl;
}

void count_location(int &location, TarHeader &temp){
    location += octal_str_to_dex(temp.filesize) + 512;
    if(location%512)
        location = (location/512+1)*512;
}