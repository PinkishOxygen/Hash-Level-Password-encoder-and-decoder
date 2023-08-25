#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool containsInvalidCharacter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        return false;
    }
    return true;
}

void transformPassword(char *password) {
    int length = strlen(password);

    // Step 1: Convert uppercase to lowercase
    for (int i = 0; i < length; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            password[i] = password[i] + ('a' - 'A');
        }
    }

    // Step 2: Convert every other letter to their number equal
for (int i = 1; i < length; i += 2) {
    if ((password[i] >= 'a' && password[i] <= 'z') || (password[i] >= 'A' && password[i] <= 'Z')) {
        if (password[i] >= 'a' && password[i] <= 'z') {
            password[i] = 'a' + (password[i] - 'a' + 1) % 26;
        } else if (password[i] >= 'A' && password[i] <= 'Z') {
            password[i] = 'A' + (password[i] - 'A' + 1) % 26;
        }
    }
}

    // Step 3: Convert every other letter to uppercase
    for (int i = 0; i < length; i += 2) {
        if (password[i] >= 'a' && password[i] <= 'z') {
            password[i] = password[i] - ('a' - 'A');
        }
    }

    // Step 4: Replace 'a' or 'A' with '@'
    for (int i = 0; i < length; i++) {
        if (password[i] == 'a' || password[i] == 'A') {
            password[i] = '@';
        }
    }

    // Step 5: Replace 's' or 'S' with '$'
    for (int i = 0; i < length; i++) {
        if (password[i] == 's' || password[i] == 'S') {
            password[i] = '$';
        }
    }
}

int main() 
{
        int i;
        int loadingBarWidth = 40;
        int choice;
        char input_password_1[100];
        
        printf("Select One:\n---------\n1) Encode\n2) Decode\n\nInput: ");
        scanf("%d", &choice);
    
        if (choice == 1) {
            printf("\nMake a password to encode: ");
            scanf("%s", input_password_1);
    
            // Validate password for invalid characters
            bool hasInvalidCharacter = false;
            int passwordLength = strlen(input_password_1);
            for (i = 0; i < passwordLength; i++) {
                if (containsInvalidCharacter(input_password_1[i])) {
                    hasInvalidCharacter = true;
                    break;
                }
            }
    
            if (hasInvalidCharacter) {
                printf("\nInvalid Character:\n%s\n", input_password_1);
                for (int j = 0; j < passwordLength; j++) {
                    if (containsInvalidCharacter(input_password_1[j])) {
                        printf("^");
                    } else {
                        printf(" ");
                    }
                }
                printf("\n");
                return 1; // Exit with an error code
            }
    
            printf("\nEncoding...\n");
            for (i = 0; i <= loadingBarWidth; i++) {
                usleep(100000);  // Sleep for 100 milliseconds (adjust as needed)
    
                printf("[");
                for (int j = 0; j < loadingBarWidth; j++) {
                    if (j <= i) {
                        printf("=");
                    } else {
                        printf(" ");
                    }
                }
                printf("] %d%%\r", (i * 100) / loadingBarWidth);
                fflush(stdout);
            }
    
            // Transform the password
            transformPassword(input_password_1);
    
            printf("\nEncoding complete!\n");
            printf("\n\nNew Password: \n\n%s", input_password_1);
    
        } else if (choice == 2)
    {
            printf("Put in password to decode: ");
            scanf("%s", input_password_1);
        
            // Decoding logic (reverse of encoding steps)
        int passwordLength = strlen(input_password_1);
        
        // Step 5: Replace '$' with 's' or 'S'
            for (int i = 0; i < passwordLength; i++) {
                if (input_password_1[i] == '$') {
                    input_password_1[i] = 's';
                }
            }
        
            // Step 4: Replace '@' with 'a' or 'A'
            for (int i = 0; i < passwordLength; i++) {
                if (input_password_1[i] == '@') {
                    input_password_1[i] = 'a';
                }
            }
        
         // Step 3: Convert every other letter to lowercase
            for (int i = 0; i < passwordLength; i += 2) {
                if (input_password_1[i] >= 'A' && input_password_1[i] <= 'Z') {
                    input_password_1[i] = input_password_1[i] + ('a' - 'A');
                }
            }
        
        
        // Step 2: Convert every other letter back to their original letter
            for (int i = 1; i < passwordLength; i += 2) {
                if ((input_password_1[i] >= 'a' && input_password_1[i] <= 'z') || (input_password_1[i] >= 'A' && input_password_1[i] <= 'Z')) {
                    if (input_password_1[i] >= 'a' && input_password_1[i] <= 'z') {
                        input_password_1[i] = 'a' + (input_password_1[i] - 'a' + 25) % 26;
                    } else if (input_password_1[i] >= 'A' && input_password_1[i] <= 'Z') {
                        input_password_1[i] = 'A' + (input_password_1[i] - 'A' + 25) % 26;
                    }
                }
            }
        
         // Step 1: Convert lowercase to uppercase
            for (int i = 0; i < passwordLength; i++) {
                if (input_password_1[i] >= 'a' && input_password_1[i] <= 'z') {
                    input_password_1[i] = input_password_1[i] - ('a' - 'A');
                    }
                }
            
        printf("\nDecoding complete!\n");
        printf("\n\nOriginal Password: \n\n%s", input_password_1);
    } 
    
    return 0;
}
