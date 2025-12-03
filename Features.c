
#include "header.h"
void view_song_details(char *file_name)
{
    FILE *file = fopen(file_name, "rb");
    if (!file)
    {
        printf("Error: Cannot open file\n");
        return;
    }

    fseek(file, 10, SEEK_SET);
    printf("MP3 Song Details:\n===============================================\n");

    char *tag_ids[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
    char *tag_names[] = {"Title", "Artist", "Album", "Year", "Genre", "Comments"};

    while (1)
    {
        char tag_id[5] = {0};
        unsigned char size_bytes[4];

        if (fread(tag_id, 4, 1, file) != 1)
            break;
        if (fread(size_bytes, 4, 1, file) != 1)
            break;

        fseek(file, 2, SEEK_CUR);
        if (tag_id[0] == 0)
            break;

        // Use conversion function
        unsigned int data_size = big_to_little_endian(size_bytes);

        char *tag_data = malloc(data_size);
        if (!tag_data)
            break;

        fread(tag_data, 1, data_size, file);

        for (int i = 0; i < 6; i++)
        {
            if (strncmp(tag_id, tag_ids[i], 4) == 0)
            {
                printf("%-8s: ", tag_names[i]);
                for (int j = 1; j < data_size && tag_data[j] != '\0'; j++)
                {
                    printf("%c", tag_data[j]);
                }
                printf("\n");
                break;
            }
        }

        free(tag_data);
    }

    printf("===============================================\n");
    fclose(file);
}

void edit_mp3_tag(char *filename, char *tag_type, char *new_value)
{
    FILE *src = fopen(filename, "rb");
    FILE *tmp = fopen("temp.mp3", "wb");
    if (!src || !tmp)
    {
        printf("Error: Cannot open files\n");
        return;
    }

    char header[10];
    fread(header, 1, 10, src);
    fwrite(header, 1, 10, tmp);

    // Map command line options to tag IDs
    char *tag_to_edit = NULL;

    if (strcmp(tag_type, "-t") == 0)
        tag_to_edit = "TIT2";
    else if (strcmp(tag_type, "-a") == 0)
        tag_to_edit = "TPE1";
    else if (strcmp(tag_type, "-A") == 0)
        tag_to_edit = "TALB";
    else if (strcmp(tag_type, "-y") == 0)
        tag_to_edit = "TYER";
    else if (strcmp(tag_type, "-g") == 0)
        tag_to_edit = "TCON";
    else if (strcmp(tag_type, "-c") == 0)
        tag_to_edit = "COMM";
    else
    {
        printf("Invalid tag type\n");
        show_edit_menu();
        fclose(src);
        fclose(tmp);
        remove("temp.mp3");
        return;
    }

    char *tag_names[] = {"Title", "Artist", "Album", "Year", "Genre", "Composer"};
    char *current_tag_name = "Unknown";

    if (strcmp(tag_type, "-t") == 0)
        current_tag_name = "Title";
    else if (strcmp(tag_type, "-a") == 0)
        current_tag_name = "Artist";
    else if (strcmp(tag_type, "-A") == 0)
        current_tag_name = "Album";
    else if (strcmp(tag_type, "-y") == 0)
        current_tag_name = "Year";
    else if (strcmp(tag_type, "-g") == 0)
        current_tag_name = "Genre";
    else if (strcmp(tag_type, "-c") == 0)
        current_tag_name = "Comments";

    int edited = 0;

    while (1)
    {
        char tag[5] = {0};
        if (fread(tag, 4, 1, src) != 1)
            break;

        unsigned char size_b[4];
        if (fread(size_b, 4, 1, src) != 1)
            break;

        unsigned char flags[2];
        fread(flags, 1, 2, src);

        if (tag[0] == 0)
            break;

        // Use conversion function
        unsigned int size = big_to_little_endian(size_b);

        if (strncmp(tag, tag_to_edit, 4) == 0 && !edited)
        {
            // Write edited tag
            fwrite(tag, 4, 1, tmp);

            int new_size = strlen(new_value) + 2;

            // Use conversion function for big endian
            unsigned char new_size_b[4];
            little_to_big_endian(new_size, new_size_b);

            fwrite(new_size_b, 4, 1, tmp);
            fwrite(flags, 1, 2, tmp);

            unsigned char encoding = 0;
            fwrite(&encoding, 1, 1, tmp);
            fwrite(new_value, 1, strlen(new_value), tmp);
            fwrite("\0", 1, 1, tmp);

            fseek(src, size, SEEK_CUR);
            edited = 1;
            printf("%s updated to: %s\n", current_tag_name, new_value);
        }
        else
        {
            // Copy original tag
            fwrite(tag, 4, 1, tmp);
            fwrite(size_b, 4, 1, tmp);
            fwrite(flags, 1, 2, tmp);

            char *data = malloc(size);
            if (!data)
                break;

            fread(data, 1, size, src);
            fwrite(data, 1, size, tmp);
            free(data);
        }
    }

    // Copy remaining data
    int ch;
    while ((ch = fgetc(src)) != EOF)
        fputc(ch, tmp);

    fclose(src);
    fclose(tmp);

    remove(filename);
    rename("temp.mp3", filename);
    printf("File updated successfully!\n");
}
