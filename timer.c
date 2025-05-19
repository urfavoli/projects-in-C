#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>  
#include <stdbool.h>
#include <windows.h>
#include <conio.h> // For kbhit() on Windows

void clearScreen() {
    system("cls");
}

void displayClock(time_t rawtime, int alarm_hour, int alarm_minute, int alarm_set) {
    struct tm *time_info = localtime(&rawtime);
    
    clearScreen();
    printf("\n  +---------------------+\n");
    printf("  |   DIGITAL ALARM CLOCK  |\n");
    printf("  +---------------------+\n\n");
    
    printf("  Current Time: %02d:%02d:%02d\n", 
           time_info->tm_hour, 
           time_info->tm_min, 
           time_info->tm_sec);
    
    if (alarm_set) {
        printf("  Alarm Set: %02d:%02d\n", alarm_hour, alarm_minute);
    } else {
        printf("  Alarm: Not Set\n");
    }
    
    printf("\n  Press 's' to set alarm\n");
    printf("  Press 'q' to quit\n");
}

void playAlarmSound() {
    // Play a beep sequence
     system("start alarm.wav");
}
void checkAlarm(int current_hour, int current_minute, 
                int alarm_hour, int alarm_minute, int alarm_set) {
    if (alarm_set && current_hour == alarm_hour && current_minute == alarm_minute) {
        printf("\a");
        printf("\n  ALARM! ALARM! ALARM!\n");
         playAlarmSound();
        Sleep(2000);
    }
}

void setAlarm(int *alarm_hour, int *alarm_minute, int *alarm_set) {
    char input[10];
    int valid = 0;
    
    while (!valid) {
        clearScreen();
        printf("\n  Set Alarm (HH:MM format, 24-hour): ");
        scanf("%9s", input);
        
        if (strlen(input) == 5 && 
            isdigit(input[0]) && isdigit(input[1]) && 
            input[2] == ':' && 
            isdigit(input[3]) && isdigit(input[4])) {
            
            *alarm_hour = (input[0] - '0') * 10 + (input[1] - '0');
            *alarm_minute = (input[3] - '0') * 10 + (input[4] - '0');
            
            if (*alarm_hour >= 0 && *alarm_hour < 24 && 
                *alarm_minute >= 0 && *alarm_minute < 60) {
                valid = 1;
                *alarm_set = 1;
            }
        }
        
        if (!valid) {
            printf("  Invalid time format! Please use HH:MM (24-hour format)\n");
            Sleep(2000);
        }
    }
}

int main() {
    time_t raw_time;
    struct tm *time_info;
    int alarm_hour = 0, alarm_minute = 0, alarm_set = 0;
    char command;
    
    printf("\n  Starting Digital Alarm Clock...\n");
    Sleep(2000);
    
    while (1) {
        time(&raw_time);
        time_info = localtime(&raw_time);
        
        displayClock(raw_time, alarm_hour, alarm_minute, alarm_set);
        checkAlarm(time_info->tm_hour, time_info->tm_min, 
                  alarm_hour, alarm_minute, alarm_set);
        
        if (_kbhit()) {
            command = _getch();
            
            if (command == 's' || command == 'S') {
                setAlarm(&alarm_hour, &alarm_minute, &alarm_set);
            } else if (command == 'q' || command == 'Q') {
                break;
            }
        }
        
        Sleep(1000);
    }
    
    clearScreen();
    printf("\n  Digital Alarm Clock stopped.\n\n");
    
    return 0;
}