#include "header.h"
// It is for the file checking.
int check_mp3_file(char *file_name)
{
    if (strstr(file_name, ".mp3") != NULL)
        return 1;

    return 0;
}

// Convert size from big endian to little endian
unsigned int big_to_little_endian(unsigned char bytes[4])
{
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

// Convert size from little endian to big endian
void little_to_big_endian(unsigned int size, unsigned char result[4])
{
    result[0] = (size >> 24) & 0xFF;
    result[1] = (size >> 16) & 0xFF;
    result[2] = (size >> 8) & 0xFF;
    result[3] = size & 0xFF;
}

//help menue function 
void show_help()
{
    printf("View Song Details: ./program -v file.mp3\n");
    printf("Edit Song Details: ./program -e -t title_name file.mp3\n");
}
void show_edit_menu()
{
    printf("MP3 Tag Editor\n");
    printf("Use: ./program -e [option] value filename.mp3\n");
    printf("Options:\n");
    printf("  -t value Edit Title\n");
    printf("  -a value Edit Artist\n");
    printf("  -A value Edit Album\n");
    printf("  -y value Edit Year\n");
    printf("  -g value Edit Genre\n");
    printf("  -c value Edit Comments\n");
}
