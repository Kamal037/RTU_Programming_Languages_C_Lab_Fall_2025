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

//Global variables
const char *SRC = NULL; // Pointer to the input expression string
size_t POS = 0;// Current reading position
size_t LEN = 0;// Length of the input string
int error_flag = 0;// Error flag (1 if an error occurs)
size_t error_pos = 0;// Position of the error in the input string

//Function declarations
double parse_expr();
double parse_term();
double parse_factor();
void next_nonspace();

//Helper functions

// Skip any whitespace characters
void next_nonspace() {
    while (POS < LEN && isspace((unsigned char)SRC[POS])) POS++;
}

// Return the current character without moving POS
char peek() {
    if (POS >= LEN) return '\0';
    return SRC[POS];
}

// Parse a number (integer or floating-point)
double parse_number() {
    size_t start = POS;
    int has_dot = 0;  // Flag for decimal point

    //Read digits and optionally one dot
    while (POS < LEN && (isdigit(SRC[POS]) || SRC[POS] == '.')) {
        if (SRC[POS] == '.') {
            if (has_dot) break; //Second dot ends number (error handled later)
            has_dot = 1;
        }
        POS++;
    }

    //Copy the number substring into a buffer
    char buf[64];
    size_t len = POS - start;
    if (len >= sizeof(buf)) len = sizeof(buf) - 1;
    strncpy(buf, SRC + start, len);
    buf[len] = '\0';

    //Convert string to double
    char *endptr;
    double val = strtod(buf, &endptr);

    // If nothing was read, set error
    if (endptr == buf) {
        error_flag = 1;
        error_pos = start + 1;
        return 0;
    }

    return val;
}

//Expression parser
// expr = term { ('+' | '-') term }
double parse_expr() {
    double val = parse_term();
    while (!error_flag) {
        next_nonspace();
        char c = peek();
        if (c == '+' || c == '-') {
            POS++;  // Consume operator
            double rhs = parse_term();
            if (error_flag) return 0;
            if (c == '+') val += rhs;
            else val -= rhs;
        } else break;
    }
    return val;
}

//term = factor { '*' factor }
double parse_term() {
    double val = parse_factor();
    while (!error_flag) {
        next_nonspace();
        char c = peek();
        if (c == '*') {
            POS++;  // Consume operator
            double rhs = parse_factor();
            if (error_flag) return 0;
            val *= rhs;
        } else break;
    }
    return val;
}

//factor = number | '(' expr ')'
double parse_factor() {
    next_nonspace();
    char c = peek();

    // Handle parentheses
    if (c == '(') {
        POS++;  // Consume '('
        double val = parse_expr();
        next_nonspace();
        if (peek() != ')') {  // Expect closing ')'
            error_flag = 1;
            error_pos = POS + 1;
            return 0;
        }
        POS++;  // Consume ')'
        return val;
    }

    // Handle numbers
    if (isdigit(c) || c == '.') {
        return parse_number();
    }

    // If none of the above, it's an error
    error_flag = 1;
    error_pos = POS + 1;
    return 0;
}

//Main function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: calc input.txt\n");
        return 1;
    }

    //Open input file
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Cannot open file: %s\n", argv[1]);
        return 1;
    }

    //Get file length
    fseek(f, 0, SEEK_END);
    LEN = ftell(f);
    rewind(f);

    //Read file content into buffer
    char *buf = (char*)malloc(LEN + 1);
    fread(buf, 1, LEN, f);
    buf[LEN] = '\0';
    fclose(f);

    //Initialize parser
    SRC = buf;
    POS = 0;
    error_flag = 0;
    error_pos = 0;

    //Parse expression
    double result = parse_expr();
    next_nonspace();

    //If extra characters remain after parsing, it is an error
    if (!error_flag && POS < LEN) {
        error_flag = 1;
        error_pos = POS + 1;
    }

    //Prepare output file name
    char outname[256];
    snprintf(outname, sizeof(outname), "%s_result.txt", argv[1]);

    FILE *out = fopen(outname, "w");
    if (!out) {
        printf("Cannot create output file!\n");
        free(buf);
        return 1;
    }

    //Write result or error to output
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