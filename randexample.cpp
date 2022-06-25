// Online C++ compiler to run C++ program online
#include <iostream>
#include <cmath>
int main() {
    int min_angle = 100;
    int max_angle = 120; 
    int interval_angle = 40;
    int range_angle = max_angle - min_angle;
    for(int i=0; i<10; i++){
        int tvangle = (rand());
        printf("%d\n", tvangle); 
    }
    printf("----------------------------------------------------\n");
    
    for(int i=0; i<10; i++){
        int tvangle = min_angle + (rand());
        printf("%d\n", tvangle); 
    }
    printf("----------------------------------------------------\n");
    
    for(int i=0; i<10; i++){
        int tvangle = min_angle + (rand() % range_angle);
        printf("%d\n", tvangle); 
    }
    printf("----------------------------------------------------\n");
    
    for(int i=0; i<10; i++){
        int tvangle = min_angle + (rand() % range_angle) / interval_angle * interval_angle;
        printf("%d\n", tvangle); 
    }
    printf("----------------------------------------------------\n");
    
    return 0;
}