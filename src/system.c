#include "header.h"


const char *RECORDS = "./data/records.txt";
const char *User ="./data/users.txt";
char Users[200];
#define MAX_USERS 200     // Nombre maximum d'utilisateur
#define MAX_NAME_LENGTH 50 // Longueur maximale pour un nom

int GetId(FILE *file);
int check(FILE *file,char name[50]);


int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}
void registere(struct User U)
{    

    system("clear");
      FILE *file = fopen("./data/users.txt", "r+");  // Ouvrir le fichier en mode écriture et lire  ("w")
   
     if (file == NULL) {
        printf("Erreur \n");
        exit(0);  // Sortir en cas d'erreur
    }

  
    printf("\t\t\t\tBank Management System");
    printf("\n\t\t\t\t\tUser Login:");
    scanf("%s", U.name);
    if (check(file,U.name)==1)
    { 
  
    printf("\n\n\n\n\n\t\t\t\tEnter the Password to login:");
    scanf("%s", U.password);
    
    U.id = GetId(file);
    Users[U.id]=U.name;
    printf(User);
    fprintf(file, "\n%d %s %s",U.id,U.name,U.password);
    fclose(file);
    } else {
        printf("this name alredy exist!");

    }



}

int GetId(FILE *f) {
     if (ferror(f)) {
    perror("Erreur de lecture du fichier");
    return -11;
}
    int line_count = 0; 

    char buffer[256]; 
    while (fgets(buffer, sizeof(buffer), f)) {
        line_count++;  
    }
   

    return line_count;
}
 // char Users[MAX_USERS][MAX_NAME_LENGTH];

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
        if (Users[i] == '\0') {
            break;  
        }

        // Comparaison des chaînes
        if (strcmp(Users[i], name) == 0) {
            return -1;  // Le nom existe déjà dans le tableau
        }
    }

    return 1;  // Le nom n'existe pas, il est valide
}

