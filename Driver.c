int main() {
    boot_win();
    while (true){
        for(int perc = 10; perc <= 100; perc += 10){
            print_progress(19, 4, "Progress: ", perc, 10); // row, column, message, percent, width
            wait_msec(500000);
        }
    }
    return 0;
}