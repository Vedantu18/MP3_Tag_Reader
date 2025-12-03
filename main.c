/*Project2: MP3 Tag Reader
  Date: 18-11-2025
  Author: Vedant Shivsharan
*/

#include "header.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        show_help();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0 || argc == 1)
    {
        show_help();
    }
    else if (strcmp(argv[1], "-v") == 0 && argc == 3)
    {
        char *file_name = argv[2];
        if (!check_mp3_file(file_name))
        {
            printf("Error: Need .mp3 file\n");
            return 1;
        }
        view_song_details(file_name);
    }
    else if (strcmp(argv[1], "-e") == 0 && argc == 5)
    {
        char *tag_type = argv[2];
        char *new_value = argv[3];
        char *file_name = argv[4];
        
        if (!check_mp3_file(file_name))
        {
            printf("Error: Need .mp3 file\n");
            return 1;
        }
        edit_mp3_tag(file_name, tag_type, new_value);
    }
    else if (strcmp(argv[1], "-e") == 0 && argc == 2)
    {
        show_edit_menu();
    }
    else
    {
        show_help();
        return 1;
    }

    return 0;
}

