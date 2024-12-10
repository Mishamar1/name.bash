#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decoding(const char* str, char* cod, const char* symbols, char* morse[], 
                int (*bulkhead)(const char* x, char* morse[])) // начало рассшифровки
{    
    int indx[550] = {0}, mas = 0;

    for(int i = 0; str[i] != '\0';){
        char x[7] = "";
        int j = 0;
        while (str[i] != ' ' && str[i] != '\0' && j <= 6) {
            x[j++] = str[i++];
        }
        x[j] = '\0';
        indx[mas] = bulkhead(x, morse);
        mas++;
        i++;
    }

    for(int i = 0; i < mas; i++) {
        if(indx[i] == -1){
            cod[i] = '+';  // если символ не получилось расшифровать
        }
        else
            cod[i] = toupper(symbols[indx[i]]);
    }
    cod[mas] = '\0';
}                                   

int bulkhead(const char* x, char* morse[]) {
    for(int i = 0; i < 40; i++) {
        if(strcmp(morse[i], x) == 0)
            return i;
    }
    return -1;                           // конец расшифровки
}

void encoding(const char* str, char* cod, const char* symbols, const char* morse[], 
            int (*yasy)(char bukva, const char* symbols)) //  начало кодировки 
{
    for(int i = 0; str[i] != '\0'; i++) {
        char bukva = toupper((unsigned char)str[i]);  // Преобразуем к верхнему регистру
        int indx = yasy(bukva, symbols);
        if(indx != -1) {
            strcat(cod, morse[indx]);
            strcat(cod, " ");
        }
    }
    cod[strlen(cod) - 1] = '\0';
}

int yasy(char bukv, const char* symbols) {
    for(int i = 0; i < 40; i++) {
        if(symbols[i] == bukv)
            return i;
    }
    return -1;
}                       // конец кодировки

int main(void) {

    puts("Specify the desired action with a number.\n Encrypt text: \"1\"\n Decrypt text: \"2\"");

    int x;
    scanf("%d", &x);

    getchar(); // Чтение оставшегося символа новой строки

    if(x == 1)
        puts("Enter the text you want to encrypt: ");
    else if(x == 2){
        puts("*Decryption of the text will be a caption*");
        puts("Enter the text you want to decrypt: ");
    }
    else {
        puts("Error. An invalid character has been entered");
        return 1;
    }

    char str[2000] = {0};
    fgets(str, sizeof(str)-1, stdin);
    char* ptr_n = strrchr(str, '\n');
    if(ptr_n != NULL)
        *ptr_n = '\0';

    char cod[1500] = {0};
char symbols[] = "AJS2BKT3CLU4DMV5ENW6FOX7GPY8HQZ9IR10 ?!,";

char *morse[] = {".-", ".---",	"...", "..---", "-...", "-.-", "-", 
                 "...--", "-.-.", ".-..", "..-", "....-", "-..", "--", 
                 "...-", ".....", ".", "-.", ".--", "-....", "..-.", 
                 "---", "-..-", "--...", "--.", ".--.", "-.--", 
                 "---..", "....", "--.-", "--..", "----.", "..", ".-.", 
                 ".----", "-----", "-...-", "..--..", "--..--", ".-.-.-"};

    switch(x) {
        case 1:
            encoding(str, cod, symbols, morse, yasy);
            break;
        case 2:
            decoding(str, cod, symbols, morse, bulkhead);
            break;
        default:
            break;
    }

    puts(cod);

    return 0;
}
