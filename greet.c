// clang -Wall greet.c -o greetings; mv greetings ~/bin

#include <stdio.h>
#include <time.h>

int moon_phase(int, int, int);

int main(int argc, char *argv[]) {
    time_t now;
    char time_string[64];

    char *phase[8] = {
        "waxing crescent", "at first half", "waxing gibbous",  "full",
        "waning gibbous",  "at last half",  "waning crescent", "new"};

    time(&now);
    struct tm *clock = localtime(&now);

    strftime(time_string, 64, "Today is %A, %B %d, %Y - %r", clock);

    printf("Good ");
    if (clock->tm_hour < 12) {
        printf("morning");
    } else if (clock->tm_hour < 17) {
        printf("afternoon");
    } else {
        printf("evening");
    }

    if (argc > 1)
        printf(", %s!", argv[1]);
    putchar('\n');
    printf("%s\n", time_string);

    int mp = moon_phase(clock->tm_year + 1900, clock->tm_mon, clock->tm_mday);
    printf("The moon is %s.\n", phase[mp]);

    return 0;
}

int moon_phase(int year, int month, int day) {
    int d = day;
    int g = (year - 1900) % 19;
    int e = (11 * g + 29) % 30;

    if (month == 2) {
        d += 31;
    } else if (month > 2) {
        d += 59 + (month - 3) * 30.6 + 0.5;
    }

    if (e == 25 || e == 24)
        ++e;

    // don't ask
    return ((((e + d) * 6 + 5) % 177) / 22 & 7);
}
