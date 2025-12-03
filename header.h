// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>

// int check_mp3_file(char *file_name);
// int valid_header(char *file_name);
// void view_song_details(char *file_name);
// void show_help();
// void edit_mp3_tags(char *filename);

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int check_mp3_file(char *file_name);
void view_song_details(char *file_name);
void edit_mp3_tag(char *filename, char *tag_type, char *new_value);
void show_help();
void show_edit_menu();

// Conversion functions
unsigned int big_to_little_endian(unsigned char bytes[4]);
void little_to_big_endian(unsigned int size, unsigned char result[4]);