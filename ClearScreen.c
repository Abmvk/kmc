/* voorstel van ChatGPT ter vervanging van system("clear"). Deze aanpak zou meer platform-onafhankelijk moeten zijn. Nog te testen.

Als het werkt, opnemen in stdavk.h en stdavk.c als cls()

*/


#include <stdio.h>

void clearScreen() {
    printf("\033[2J"); // Print ANSI escape sequence to clear screen
    printf("\033[%d;%dH", 0, 0); // Move cursor to top-left corner of screen
}

int main() {
    clearScreen(); // Call the function to clear the screen
    printf("Hello, world!\n"); // Output text
    return 0;
}
