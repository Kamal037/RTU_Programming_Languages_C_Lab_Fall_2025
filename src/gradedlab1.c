#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dirent.h>
#endif


const char *SRC = NULL;
size_t POS = 0;
size_t LEN = 0;
int error_flag = 0;
size_t error_pos = 0;


double parse_expr();
double parse_term();
double parse_factor();
void next_nonspace();


void next_nonspace() {
    while (POS < LEN && isspace((unsigned char)SRC[POS])) POS++;
}


char peek() {
    if (POS >= LEN) return '\0';
    return SRC[POS];
}


double parse_number() {
    size_t start = POS;
    int has_dot = 0;

    
    while (POS < LEN && (isdigit(SRC[POS]) || SRC[POS] == '.')) {
        if (SRC[POS] == '.') {
            if (has_dot) break;
            has_dot = 1;
        }
        POS++;
    }

    
    char buf[64];
    size_t len = POS - start;
    if (len >= sizeof(buf)) len = sizeof(buf) - 1;
    strncpy(buf, SRC + start, len);
    buf[len] = '\0';

    char *endptr;
    double val = strtod(buf, &endptr);

   
    if (endptr == buf) {
        error_flag = 1;
        error_pos = start + 1;
        return 0;
    }

    return val;
}



double parse_expr() {
    double val = parse_term();
    while (!error_flag) {
        next_nonspace();
        char c = peek();
        if (c == '+' || c == '-') {
            POS++;  
            double rhs = parse_term();
            if (error_flag) return 0;
            if (c == '+') val += rhs;
            else val -= rhs;
        } else break;
    }
    return val;
}


double parse_term() {
    double val = parse_factor();
    while (!error_flag) {
        next_nonspace();
        char c = peek();
        if (c == '*') {
            POS++;  
            double rhs = parse_factor();
            if (error_flag) return 0;
            val *= rhs;
        } else break;
    }
    return val;
}


double parse_factor() {
    next_nonspace();
    char c = peek();

   
    if (c == '(') {
        POS++;  
        double val = parse_expr();
        next_nonspace();
        if (peek() != ')') {  
            error_flag = 1;
            error_pos = POS + 1;
            return 0;
        }
        POS++; 
        return val;
    }

 
    if (isdigit(c) || c == '.') {
        return parse_number();
    }

    
    error_flag = 1;
    error_pos = POS + 1;
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: calc input.txt\n");
        return 1;
    }

   
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Cannot open file: %s\n", argv[1]);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    LEN = ftell(f);
    rewind(f);

   
    char *buf = (char*)malloc(LEN + 1);
    fread(buf, 1, LEN, f);
    buf[LEN] = '\0';
    fclose(f);

    SRC = buf;
    POS = 0;
    error_flag = 0;
    error_pos = 0;


    double result = parse_expr();
    next_nonspace();

    if (!error_flag && POS < LEN) {
        error_flag = 1;
        error_pos = POS + 1;
    }

    
    char outname[256];
    snprintf(outname, sizeof(outname), "%s_result.txt", argv[1]);

    FILE *out = fopen(outname, "w");
    if (!out) {
        printf("Cannot create output file!\n");
        free(buf);
        return 1;
    }

    if (error_flag) {
        fprintf(out, "ERROR:%zu\n", error_pos);
        printf("ERROR:%zu\n", error_pos);
    } else {
        fprintf(out, "%.15g\n", result);
        printf("%.15g\n", result);
    }

    fclose(out);
    free(buf);
    return 0;
}