//Saikiran Annareddy
//where to sit program 2
//02-17-24


#include <stdio.h>
#include <string.h>

#define MAX_PEOPLE 10

typedef struct {
    char name[20];
    int has_popcorn;
} Person;

//decalring the global variables
Person people[MAX_PEOPLE];
int seating_restrictions[MAX_PEOPLE][MAX_PEOPLE];
int n, p;
int valid_order = -1; // indicating no valid order has been found yet

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// function to check if the seating order follows all seating restrictions
int check_restrictions(int order[]) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (seating_restrictions[order[j]][order[j + 1]]) {
                return 0; 
            }
        }
    }
    //checking if everyone has access to popcorn
    for (int i = 0; i < n; i++) {
        if (!people[order[i]].has_popcorn) {
            //checking if the first, last, and middle seats have access to pocorn
            if (i == 0 && !people[order[i + 1]].has_popcorn) {
                return 0; 
            } else if (i == n - 1 && !people[order[i - 1]].has_popcorn) {
                return 0; 
            } else if (!people[order[i - 1]].has_popcorn && !people[order[i + 1]].has_popcorn) {
                return 0; 
            }
        }
    }
    return 1;
}

//recursive function to generate and check the permutations of the seating order
void permute(int* order, int start_index) {
    if (valid_order == 0) return; //if a valid order has already been found it will stop 

    if (start_index == n) {
        if (check_restrictions(order)) {
            for (int i = 0; i < n; i++) {
                printf("%s\n", people[order[i]].name); // printing the valid order
            }
            valid_order = 0; // indicating a valid order has been found
            return;
        }
    } else {
        for (int i = start_index; i < n; i++) {
            swap(&order[start_index], &order[i]);
            permute(order, start_index + 1);
            swap(&order[start_index], &order[i]); 
        }
    }
}

int main(int argc, char *argv[]) {
    //opening the input file
    FILE *fp = fopen(argv[1], "r");
    
    //reading the number of people and seating restrictions from the input file
    fscanf(fp, "%d %d", &n, &p);
    
    int order[MAX_PEOPLE];//array to store the current seating order

   //reading each person's name and whether they have popcorn 
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%s %d", people[i].name, &people[i].has_popcorn);
        order[i] = i; 
    }

    //initializing the seating to have no restrictions
    for (int i = 0; i < MAX_PEOPLE; i++) {
        for (int j = 0; j < MAX_PEOPLE; j++) {
            seating_restrictions[i][j] = 0;
        }
    }

    //reading the seating restrictions from the input file and updating the restrictions
    for (int i = 0; i < p; i++) {
        char person1[20], person2[20];
        fscanf(fp, "%s %s", person1, person2);
        for (int j = 0; j < n; j++) {
            if (strcmp(people[j].name, person1) == 0) {
                for (int k = 0; k < n; k++) {
                    if (strcmp(people[k].name, person2) == 0) {
                        seating_restrictions[j][k] = 1;
                        seating_restrictions[k][j] = 1;
                    }
                }
            }
        }
    }

    fclose(fp); 

    //generating permutations and checking for valid seating orders
    permute(order, 0);
    if (valid_order != 0) {
        printf("No valid seating arrangement found.\n");
    }

    return 0;
}
