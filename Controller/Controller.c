#include <stdio.h>
#include <stdlib.h>

void run_program(const char *program_path) {
    printf("Running %s...\n", program_path);
    int result = system(program_path);
    if (result != 0) {
        printf("\nError: Failed to execute %s\n", program_path);
    }
}

int main() {
    int choice;
    while (1) {
        // Display menu
        printf("\n--- Program Controller Menu ---\n");
        printf("1.  Priority Queue\n");
        printf("2.  Unit Conversions\n");
        printf("3.  Rational Calculator\n");
        printf("4.  Gaussian Summation\n");
        printf("5.  Bouncy Ball\n");
        printf("6.  Database\n");
        printf("7.  Password Generator\n");
        printf("8.  To-Do List\n");
        printf("9.  SHA-256 Encryption\n");
        printf("10. System Information\n");
        printf("11. Sort Visualizer\n");
        printf("12. Pathfinding Visualizer\n");
        printf("13. Casino Game\n");
        printf("0.  Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                run_program("Programs/priorityqueue.exe");
                break;
            case 2:
                run_program("Programs/unitconversions.exe");
                break;
            case 3:
                run_program("Programs/CCalculator.exe");
                break;
            case 4:
                run_program("Programs/GaussianSummation.exe");
                break;
            case 5:
                run_program("Programs/BouncyBall.exe");
                break;
            case 6:
                run_program("Programs/database.exe");
                break;
            case 7:
                run_program("Programs/PasswordGenerator.exe");
                break;
            case 8:
                run_program("Programs/To_Do_List.exe");
                break;
            case 9:
                run_program("Programs/SHA_256.exe");
                break;
            case 10:
                run_program("Programs/SystemInfo.exe");
                break; 
            case 11:
                run_program("Programs/Sort.exe");
                break;    
            case 12:
                run_program("Programs/Path.exe");
                break;   
            case 13:
                run_program("Programs/Casino.exe");
                break;    
            case 0:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
