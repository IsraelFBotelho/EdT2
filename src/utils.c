#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int chooseColor(double s){
    if(s < 25){
        return 0;
    }else if( s < 50){
        return 1;
    }else if( s < 100){
        return 2;
    }else if( s < 250){
        return 3;
    }else if( s < 600){
        return 4;
    }else if( s < 1000){
        return 5;
    }else if( s < 8000){
        return 6;
    }else{
        return 7;
    }
}