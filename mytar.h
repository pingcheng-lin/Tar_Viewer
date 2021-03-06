#ifndef __MYTAR_H__
#define __MYTAR_H__
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iomanip>
struct TarHeader {
    char filename[100];
    char filemode[8];
    char userid[8];
    char groupid[8];
    char filesize[12];
    char mtime[12];
    char checksum[8];
    char type;
    char lname[100];

    /* USTAR Section */
    char USTAR_id[6];
    char USTAR_ver[2];
    char username[32];
    char groupname[32];
    char devmajor[8];
    char devminor[8];
    char prefix[155];
    char pad[12];
};
void check_command(int num);
int access_file(TarHeader &head, char* name, int location);
void check_ustar(char *id);
void handle_filemode(TarHeader &head, char *fmode);
int octal_str_to_dex(char *word);
void output_detail(TarHeader &head, char *fmode);
void count_location(int &location, TarHeader &temp);

#endif