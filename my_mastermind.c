#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 

/** PROBLÈMES
* Gestion de flags.
* Si l'input est trop grand, affiche wrong input plusieurs fois.
* (On a ôté le if else prc si tu mettais un wrong input il affichait pas les wp et les ms).
* Regarde le charactere End Of Text dans la table ASCII.
*/

// taille ?
int my_strlen(char *s){
    int i = 0;
    int count = 0;
    while (s[i] != '\0') {
        count += 1;
        i += 1;
    }
    return count;
}

// compare ?
int my_strcmp(char* param_1, char* param_2){
    while(*param_1 && (*param_1 == *param_2)){
        param_1 += 1;
        param_2 += 1;
    }
    return (*param_1 - *param_2);
}

//doublons ?
int duplicates(char *doublons){
    int indexduplication = 0;
    while (indexduplication < my_strlen(doublons)) {
        int next = indexduplication + 1;
        while (next < my_strlen(doublons)) {
            if (doublons[indexduplication] == doublons[next])
                return 1;
            next += 1;
        }
        indexduplication += 1;
    }
    return 0;
}

// nombre de pièces
int pieces(char* position, char* code, int numbre){
    int greatplace = 0;
    int wrongplace = 0;
    int index = 0;
    int posIndex = 0;

    while (index < 4){
        if (position[index] == code[index])
            greatplace += 1;
        index += 1;
    }

    while (posIndex < 4){
        int codeIndex = 0;
        while (codeIndex < 4){
            if (posIndex != codeIndex && position[posIndex] == code[codeIndex])
                wrongplace += 1;
            codeIndex += 1;
        }
        posIndex += 1;
    }

    if (numbre == 1)
        return greatplace;
    return wrongplace;
}

//je dois verifier si unput = bon format ou pas 
int greatstructure(char* input){
    int index=0;
    if (my_strlen(input) != 4){
        return 0;
    }
    // Vérifier que chaque char entre [0, 8]
    while (index < 4){
        if (input[index] < '0' || input[index] > '8'){
            return 0;
        }
        index += 1;
    }
    // Vérifier doublons
    if (duplicates(input)){
        return 0;
    }
    return 1;
}

int read_word(char* buffer, int max_size) {
    int i = 0;
    char c;
    
    while (i < max_size - 1) {
        ssize_t bytes_read = read(0, &c, 1);
        if (bytes_read <= 0) {
            // Ctrl+D (EOF)
            buffer[i] = '\0';
            return 0; // EOF détecté
        }
        
        if (c == '\n' || c == ' ' || c == '\t') {
            break;
        }
        
        buffer[i] = c;
        i++;
    }
    buffer[i] = '\0';
    return 1; // Lecture normale
}

// jeu Mastermind simplifié
int my_mastermind(int argc, char **argv){
    int indexround = 0;
    char inputnumber[100];
    char randomnumber[5];
    int i = 0;
    int arg = 1;
    int code_provided = 0;

    srand(time(NULL));
    
    // Gestion des paramètres
    while (arg < argc) {
        if (my_strcmp(argv[arg], "-c") == 0 && arg + 1 < argc) {
            // Vérifier que le code après -c est valide
            if (my_strlen(argv[arg + 1]) == 4 && greatstructure(argv[arg + 1])) {
                i = 0;
                while (i < 4) {
                    randomnumber[i] = argv[arg + 1][i];
                    i += 1;
                }
                randomnumber[4] = '\0';
                code_provided = 1;
                printf("Code personnalisé: %s\n", randomnumber);
                arg += 2; // Skip -c et le code
            } else {
                printf("Code invalide après -c, génération aléatoire...\n");
                arg += 1;
            }
        }
        // Flag -t ignoré mais présent pour compatibilité
        else if (my_strcmp(argv[arg], "-t") == 0) {
            arg += 1;
        }
        else {
            arg += 1;
        }
    }
    
    // Si pas de code fourni, générer aléatoirement
    if (!code_provided) {
        i = 0;
        while (i < 4){
            randomnumber[i] = '0' + (rand() % 9);
            i += 1;
        }
        randomnumber[4] = '\0';
    }

    while (indexround < 10){
        printf("---\nRound %d\n", indexround);
        write(0, ">", 1);

        // Lecture de l'input mot par mot
        if (read_word(inputnumber, sizeof(inputnumber)) == 0) {
            // Ctrl+D détecté
            printf("\nEnd of File détecté. Fin normale du programme.\n");
            return 0;
        }

        // Nettoyer l'input pour ne garder que les 4 premiers caractères
        if (my_strlen(inputnumber) > 4) {
            inputnumber[4] = '\0';
        }

        // Si l'input est vide après Ctrl+D
        if (my_strlen(inputnumber) == 0) {
            printf("Entrée vide. Fin normale du programme.\n");
            return 0;
        }

        while (greatstructure(inputnumber) == 0){
            printf("Wrong input!\n");
            write(0, ">", 1);
            
            if (read_word(inputnumber, sizeof(inputnumber)) == 0) {
                // Ctrl+D détecté
                printf("\nEnd of File détecté. Fin normale du programme.\n");
                return 0;
            }
            
            if (my_strlen(inputnumber) > 4) {
                inputnumber[4] = '\0';
            }
            
            if (my_strlen(inputnumber) == 0) {
                printf("Entrée vide. Fin normale du programme.\n");
                return 0;
            }
        }
        
        if (my_strcmp(inputnumber, randomnumber) == 0){
            printf("Congratz! You did it!\n");
            return 0;
        }
        printf("Well placed pieces: %d\n", pieces(inputnumber, randomnumber, 1));
        printf("Misplaced pieces: %d\n", pieces(inputnumber, randomnumber, 0));

        indexround += 1;
    }
    printf("Game over!\n");
    return 0;
}

int main(int argc, char **argv){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    my_mastermind(argc, argv);
    return 0;
}
/* Crée un jeu mastermind (le jeu des couleurs ou tu dois deviner la combine la)
sauf que la c'est des numeros !
prend ce que le client te donne et compare avec ce que tu va generer
aléatoirement 10 essaie

PROMPT>./my_mastermind -c "0123"
Will you find the secret code?
Please enter a valid guess
---
Round 0
>1456
Well placed pieces: 0
Misplaced pieces: 1
---
Round 1
>tata
Wrong input!
>4132
Well placed pieces: 1
Misplaced pieces: 2
---
Round 2
>0123
Congratz! You did it!
 dois finir tirée C (code specifique). + ctrl D*/
