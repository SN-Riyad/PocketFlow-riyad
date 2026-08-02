#include <stdio.h>
#include <string.h>

#define FILENAME "users.dat"

struct User {
    char username[50];
    char password[50];
};

// ---------------- SIGN UP ----------------
void signUp() {
    struct User newUser;
    FILE *fp;

    printf("\n--- SIGN UP ---\n");
    printf("Enter username: ");
    scanf("%49s", newUser.username);
    printf("Enter password: ");
    scanf("%49s", newUser.password);

    // check if username already exists
    fp = fopen(FILENAME, "rb");
    if (fp != NULL) {
        struct User temp;
        while (fread(&temp, sizeof(struct User), 1, fp) == 1) {
            if (strcmp(temp.username, newUser.username) == 0) {
                printf("Username already exists! Try a different one.\n");
                fclose(fp);
                return;
            }
        }
        fclose(fp);
    }

    // save new user (append mode)
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&newUser, sizeof(struct User), 1, fp);
    fclose(fp);

    printf("Sign up successful! You can now sign in.\n");
}

// ---------------- SIGN IN ----------------
void signIn() {
    char username[50], password[50];
    struct User temp;
    FILE *fp;
    int found = 0;
    int attempts = 3;

    printf("\n--- SIGN IN ---\n");
    printf("Enter username: ");
    scanf("%49s", username);

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No users registered yet. Please sign up first.\n");
        return;
    }

    // find the username first
    while (fread(&temp, sizeof(struct User), 1, fp) == 1) {
        if (strcmp(temp.username, username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Username not found. Please sign up first.\n");
        return;
    }

    // password check loop -- wrong password can't proceed
    while (attempts > 0) {
        printf("Enter password: ");
        scanf("%49s", password);

        if (strcmp(temp.password, password) == 0) {
            printf("Login successful! Welcome, %s.\n", username);
            return;
        } else {
            attempts--;
            if (attempts > 0)
                printf("Wrong password! %d attempt(s) left.\n", attempts);
            else
                printf("Wrong password! No attempts left. Login failed.\n");
        }
    }
}

// ---------------- MAIN MENU ----------------
int main() {
    int choice;

    while (1) {
        printf("\n===== bKash Style App =====\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                signIn();
                break;
            case 3:
                printf("Exiting... Thank you!\n");
                return 0;
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}