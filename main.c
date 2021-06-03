#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void help(void);
void print_chunk(char * str, long len_str);
void print_highlight(char * str, FILE * fp, int match_case);
void print_hichunk(char * str, long len_str);


int main(int argc, char * argv[]){
    int opt = -1;
    int match_case = 0;
    size_t len_str = -1;
    FILE * fp = NULL;
    char * str = NULL;
    
    while((opt = getopt(argc, argv, "mp:")) != -1){
        switch (opt){
        case 'p':
            len_str = strlen(optarg);
            str = (char *)calloc(1, len_str+1);
            strcpy(str, optarg);
            break;
        case 'm':
            match_case = 1;
            break;
        case '?':
            help();
            exit(EXIT_FAILURE);
        }
    }   

    if(optind + 1 - argc != 0){
        help();
        free(str);
        exit(EXIT_FAILURE);
    }

    if((fp = fopen(argv[optind], "r")) == NULL){
        perror("Could not open file: ");
        free(str);
        exit(EXIT_FAILURE);
    }

    print_highlight(str, fp, match_case);
    
    free(str);
    fclose(fp);

    exit(EXIT_SUCCESS);
}

void help(void){
    printf("Usage: ./hprint -p \"[STRING]\" FILE\n");
    printf("Optional arguments: -m\t Match Case\n");
}


void print_highlight(char * str, FILE * fp, int match_case){
    long idx;
    ssize_t read;
    size_t len_line = 0;
    size_t len_str = strlen(str);
    char * precious = NULL;
    char * line = NULL;
    char * line_part = NULL;

    /* Read line */
    while((read = getline(&precious, &len_line, fp)) != -1){
        line = precious;
        /* check if line is eligible */
        if(len_line >= len_str){
            while(1){
                /* 
                 * Match case if specified 
                 * And get the first occurance of the needle in the haystack
                 */

                if(match_case){
                    if((line_part = strstr(line, str)) == NULL){
                        break;
                    }
                }else{
                    if((line_part = strcasestr(line, str)) == NULL){
                        break;
                    }
                }
                /* Find the difference between the needle and flush until needle */ 
                idx = (long)line_part - (long)line;
                // flush line
                if(idx == 0){
                    print_hichunk(line, len_str);
                }else{
                    print_chunk(line, idx);
                    /* advance line the flushed amount */
                    line += idx;
                    print_hichunk(line, len_str);
                }
                /* advance line the highlighted amount */ 
                line += len_str;
            }
        }
        /* print full line or remainder if no occurance */ 
        printf("%s", line);
    }

    if(precious){
        free(precious);
    }
}

void print_hichunk(char * str, long len_str){
    for(int i=0;i<len_str;i++){
        printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, *(char *)((long)str+i));
        // fflush(stdout);
    }
    
}

void print_chunk(char * str, long len_str){
    for(int i=0;i<len_str;i++){
        printf("%c", *(char *)((long)str+i));;
        // fflush(stdout);
    }
}