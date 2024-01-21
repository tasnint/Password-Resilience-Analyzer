#include <stdio.h>
#include <string.h>
#include <ctype.h>

int hasLowerCase(char password[]) {
    int i;
    int score1 = 0;
    for (i = 0; password[i] != '\0'; i++) {
        if (islower(password[i])) {
            score1 = 1;  
            break;      
        }
    }
    return score1;
}

int hasUpperCase(char password[]) {
    int i;
    int score2 = 0;
    for (i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            score2 = 1;  
            break;      
        }
    }
    return score2;
}

int hasSpecialChar(char password[]) {
    int score3 = 0;
    const char specialChars[] = "!@#$%^&*()";
    int i;
    int j;
    for (i = 0; password[i] != '\0'; i++) {
        for (j = 0; specialChars[j] != '\0'; j++) {
            if (password[i] == specialChars[j]) {
                score3 = 1;  
                break;      
            }
        }
    }
    return score3;
}

int hasDigit(char password[]) {
    int i;
    int score4 = 0;
    for (i=0; password[i] != '\0'; i++){
        if (isdigit(password[i])){
            score4 = 1;
            break;
        }
    }
    return score4;
}

int main() {
    int choice;
    char lastTestedPassword[100] = "";
    int lastTestedPasswordStrength = -1;

    while (1) {
        printf("Password Resilience Analyzer\n");
        printf("1. Test a new password\n");
        printf("2. View strength of the last tested password\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Your input is not valid, you must enter either '1', '2' or '3'\n\n");
            while (getchar() != '\n');  
            continue;
        }

        int extra;
        if ((extra = getchar()) != '\n' && extra != EOF) {
            printf("Your input is not valid, you must enter either '1', '2' or '3'\n\n");
            while (getchar() != '\n');  
            continue;
        }

        if (choice == 1 || choice == 2 || choice == 3) {
            if (choice == 1) {
                char password[100];
                int passwordlength;

                do {
                    printf("Enter a password: ");
                    if (scanf("%99[^\n]", password) != 1) {
                        return 1;
                    }
                    while (getchar() != '\n');  

                    passwordlength = strlen(password);

                    if (passwordlength < 8) {
                        printf("Error: Password should be at least 8 characters long.\n\n");
                        break;
                    }
                } while (passwordlength < 8);

                if (passwordlength < 8) {
                    continue; 
                }

                int score1 = hasLowerCase(password);
                int score2 = hasUpperCase(password);
                int score3 = hasSpecialChar(password);
                int score4 = hasDigit(password);

                int finalscore = 0;

                finalscore += score1;
                finalscore += score2;
                finalscore += score3;
                finalscore += score4;

                if (passwordlength >= 12) {
                    finalscore++;
                }

                if (finalscore >= 0 && finalscore <= 2) {
                    printf("Password Strength: Weak\n\n");
                } else if (finalscore >= 3 && finalscore <= 4) {
                    printf("Password Strength: Moderate\n\n");
                } else if (finalscore == 5) {
                    printf("Password Strength: Strong\n\n");
                }

                strcpy(lastTestedPassword, password);
                lastTestedPasswordStrength = finalscore;
            } else if (choice == 2) {
                if (lastTestedPasswordStrength == -1) {
                    printf("No password has been tested yet.\n\n");
                } else {
                    printf("Last tested password strength: ");
                    if (lastTestedPasswordStrength >= 0 && lastTestedPasswordStrength <= 2) {
                        printf("Weak\n\n");
                    } else if (lastTestedPasswordStrength >= 3 && lastTestedPasswordStrength <= 4) {
                        printf("Moderate\n\n");
                    } else if (lastTestedPasswordStrength == 5) {
                        printf("Strong\n\n");
                    }
                }
            } else if (choice == 3) {
                printf("Exiting...\n");
                break;
            }
        } else {
            printf("Your input is not valid, you must enter either '1', '2' or '3'\n\n");
            while (getchar() != '\n');  
        }
    } // End of while loop

    return 0;
}
