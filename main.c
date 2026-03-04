#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// struct
typedef struct{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} inputBuffer; // the

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult; // result types 

// error statement for table related values.
typedef enum {PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT} PrepareResult; 

// statement for ommand type.
typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

// it is for statements.
typedef struct {
    StatementType type;
} Statement;

// initilize te buffer.
inputBuffer* new_input_buffer() {
    inputBuffer* inputBuffer = malloc(sizeof(inputBuffer));
    inputBuffer-> buffer = NULL;
    inputBuffer-> buffer_length = 0;
    inputBuffer-> input_length = 0;
}

// make the promter for cmd.
void print_prompt() {printf("db > "); }

void readBuff(inputBuffer* buff) {
    // void read the input and take the input value to read it.
    ssize_t readL = getline(&(buff->buffer), &(buff->buffer_length), stdin);
    // getline returns the character that are read.

    // if ssize_t length returned error then print an error msg and exit.
    if(readL <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // ignore the new line
    // and decrease the count of length.
    buff->input_length = readL-1; // ignore the last newL char.
    buff->buffer[readL-1] = 0;
}

// close the buff
// that are allocated by the getline
void closeBuff(inputBuffer* buff) {
    free(buff->buffer);
    free(buff);
}

MetaCommandResult do_meta_command(inputBuffer* buff) {
    if(strcmp(buff->buffer, ".exit") == 0) {
        closeBuff(buff);
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(inputBuffer* buff, Statement* statement) {
    if (strncmp(buff->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    } if(strcmp(buff->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            printf("This is where we would do an insert. \n");
            break;
        
        case (STATEMENT_SELECT):
            printf("This is where we would do a select. \n");
            break;
    }
}

// int main(int argc, char* argv[]) {
    // call the input buffer struct
    // you can make t his constructure in cpp
    
    // oepn you while loop
        // print yor header like you terminal header promter
        // then take the input untill the newL
        
        //chek if exit
            // then exit and freed the buffer with fn.
        // else
            // unrecognized print the bugg. 


// }
//
int main(int argc, char* argv[]) {
    inputBuffer* input_buffer = new_input_buffer();

    while (true) {
        print_prompt();
        readBuff(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n",input_buffer->buffer);
                continue;
        }

        execute_statement(&statement);
        printf("Executed.\n");
    }
}
