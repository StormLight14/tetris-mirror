#include <ncurses.h>

int main() {
    // Initialize the ncurses library
    initscr();
    
    // Enable colors (if available)
    if (has_colors()) {
        start_color();
        // Define some color pairs
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_CYAN, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
    }
    
    // Get the screen size
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    // Loop through the screen and print characters with different colors
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            // Choose a random color pair for each character
            int color_pair = (x + y) % 7 + 1;
            attron(COLOR_PAIR(color_pair));

            // Print a character at the current position
            mvaddch(y, x, 'A' + ((x + y) % 26));  // Cycle through alphabet

            // Turn off color after printing the character
            attroff(COLOR_PAIR(color_pair));
        }
    }

    // Refresh the screen to display the changes
    refresh();

    // Wait for user input to exit
    getch();
    
    // End ncurses mode
    endwin();

    return 0;
}
