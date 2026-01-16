#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 256

// Struct to hold a line of words
typedef struct {
    char **words;   // array of strings
    int word_count; // number of words
} Line;

// Function to read all lines from a binary file
// Returns an array of Line structs, sets *line_count
Line* read_lines(const char *filename, int *line_count_out) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("Failed to open file");
        *line_count_out = 0;
        return NULL;
    }

    Line *lines = NULL;
    int lines_capacity = 0;
    int line_count = 0;

    char word_buf[MAX_WORD_LEN];
    int word_len = 0;

    Line current_line;
    current_line.words = NULL;
    current_line.word_count = 0;
    int words_capacity = 0;

    int c;
    while ((c = fgetc(f)) != EOF) 
    {
        if (c == 0x20) 
        {  
            if (word_len > 0) 
            {
                word_buf[word_len] = '\0';
                if (words_capacity == current_line.word_count) {
                    words_capacity = words_capacity ? words_capacity * 2 : 4;
                    current_line.words = realloc(current_line.words, words_capacity * sizeof(char*));
                }
                current_line.words[current_line.word_count++] = strdup(word_buf);
                word_len = 0;
            }
        } 
        else if (c == 0x3B)
        {  
            if (word_len > 0) {
                word_buf[word_len] = '\0';
                if (words_capacity == current_line.word_count) 
                {
                    words_capacity = words_capacity ? words_capacity * 2 : 4;
                    current_line.words = realloc(current_line.words, words_capacity * sizeof(char*));
                }
                current_line.words[current_line.word_count++] = strdup(word_buf);
                word_len = 0;
            }
            if (current_line.word_count > 0) {
                if (lines_capacity == line_count) 
                {
                    lines_capacity = lines_capacity ? lines_capacity * 2 : 4;
                    lines = realloc(lines, lines_capacity * sizeof(Line));
                }
                lines[line_count++] = current_line;
                current_line.words = NULL;
                current_line.word_count = 0;
                words_capacity = 0;
            }
        } 
        else 
        {
            if (word_len < MAX_WORD_LEN - 1) 
            {
                word_buf[word_len++] = (char)c;
            }
        }
    }

    if (word_len > 0) 
    {
        word_buf[word_len] = '\0';
        if (words_capacity == current_line.word_count) 
        {
            words_capacity = words_capacity ? words_capacity * 2 : 4;
            current_line.words = realloc(current_line.words, words_capacity * sizeof(char*));
        }
        current_line.words[current_line.word_count++] = strdup(word_buf);
    }
    if (current_line.word_count > 0) {
        if (lines_capacity == line_count) {
            lines_capacity = lines_capacity ? lines_capacity * 2 : 4;
            lines = realloc(lines, lines_capacity * sizeof(Line));
        }
        lines[line_count++] = current_line;
    }

    fclose(f);
    *line_count_out = line_count;
    return lines;
}

void free_lines(Line *lines, int line_count) 
{
    for (int i = 0; i < line_count; i++) {
        for (int j = 0; j < lines[i].word_count; j++) 
        {
            free(lines[i].words[j]);
        }
        free(lines[i].words);
    }
    free(lines);
}

int main() 
{
    int line_count;
    Line *lines = read_lines("code.bin", &line_count);
    if (!lines) return 1;


    for (int i = 0; i < line_count; i++) 
    {
        printf("Line %d:", i + 1);
        for (int j = 0; j < lines[i].word_count; j++) 
        {
            printf(" %s", lines[i].words[j]);
        }
        printf("\n");
    }

    free_lines(lines, line_count);
    return 0;
}
