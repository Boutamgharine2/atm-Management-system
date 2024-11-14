#include <termios.h>
#include "header.h"
#include <stdlib.h>


const char *User ="./data/users.txt";

#define MAX_USERS 200     // Nombre maximum d'utilisateurs
#define MAX_NAME_LENGTH 50 // Longueur maximale pour un no
char Users[MAX_USERS][MAX_NAME_LENGTH]; 

int GetId();
int check(FILE *file,char name[50]);
int ValidName(char name[50]);


void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    while (fscanf(fp, "%d %s %s",&userChecker.id, userChecker.name, userChecker.password) != EOF)

    {
        printf("\n%s==>%s\n",u.name,userChecker.name);
    //printf("==>%s - %s", u.name, userChecker.name);
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}
void registereMenu(struct User U)
{    

    system("clear");
      FILE *file = fopen("./data/users.txt", "r+");  
      if (ferror(file)) {
       perror("Erreur de lectur du fichier");
       exit(0);
   }
   
     if (file == NULL) {
        printf("Erreur \n");
        exit(1);  
    }

  
    printf("\t\t\t\tBank Management System");
    printf("\n\t\t\t\t\tUser Login:");
    fgets(U.name, sizeof(U.name), stdin);
    U.name[strcspn(U.name, "\n")] = '\0';
    Checkname(U.name);

    if (check(file,U.name)==1)
    { 

        
  
    printf("\n\n\n\n\n\t\t\t\tEnter the Password to login:");
    fgets(U.password, sizeof(U.password), stdin);
    U.password[strcspn(U.password, "\n")] = '\0';
    Checkname(U.password);
   
    
    
    U.id = GetId();
    printf("%d",U.id);
    strncpy(Users[U.id],U.name, MAX_NAME_LENGTH - 1); 

    fprintf(file, "\n%d %s %s",U.id,U.name,U.password);
    fclose(file);
    } else {
        char i[3];
        int j;
        printf("this nam alredy exist!\n");
        printf("Press 1 to enter a new name or press any other key to exit!\n");
        fgets(i, sizeof(i), stdin);
        i[strcspn(i, "\n")] = '\0';


        j = atoi(i);
        
        
        if (j==1)
        {
           registereMenu(U);

        } else {
            exit(3);
        }

        

    }



}

int GetId() {
     FILE *file = fopen("./data/users.txt", "r+");  
      if (ferror(file)) {
    perror("Erreur de lectur du fichier");
    exit(0);
      }
  
    int line_count = 0; 

    char buffer[256]; 
    while (fgets(buffer, sizeof(buffer), file)) {
        line_count++;  
    }
   

    return line_count;
}

int check(FILE *file,char name[50])
 {
   

    int i = 0;
    char line[200];  // Buffer pour lire chaque ligne du fichier

    // Lire chaque ligne du fichier
    while (fgets(line, sizeof(line), file)) {
        char id[10], name[MAX_NAME_LENGTH], password[100];

        // Utiliser sscanf pour extraire l'id, le nom et le mot de passe
        int result = sscanf(line, "%s %s %s", id, name, password);

        // Si l'extraction a réussi, stocker le nom dans le tableau Users
        if (result == 3 && i < MAX_USERS) {
            // Copie du nom dans le tableau Users
            strncpy(Users[i], name, MAX_NAME_LENGTH - 1);  // On limite à MAX_NAME_LENGTH - 1 pour laisser de la place pour '\0'
            i++;
        }
    }

    fclose(file);
    if (ValidName(name) == 1 )
    {
        return 1;
    }else 
    {
        return -1;
    }
}

int ValidName(char name[50]) {
    for (int i = 0; i < 200; i++) {
        // Si on trouve une chaîne vide, cela signifie qu'on a atteint la fin des données valides
        if (Users[i][0] == '\0') {
            break;  
        }

        // Comparaison des chaînes
        if (strcmp(Users[i], name) == 0) {
            return -1;  // Le nom existe déjà dans le tableau
        }
    }

    return 1;  // Le nom n'existe pas, il est valide
}
void Checkname(char name[50]) {
    for (int i = 0; i < 50; i++) {
        if (name[i] == ' ') {
            name[i] = '\0'; 
            break; 
        }
    }
}