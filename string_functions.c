#include "string_functions.h"

bool integer_only(const char *s) {
    while (*s != '\0') {
        if ('0' > *s || '9' < *s ){ 
        	return false;
        }
        s++;
    }

    return true;
}




bool real_only(const char *s) {

	int point_counter=0;

    while (*s != '\0') {
    	if (*s == '.') {
    		point_counter++;
    	}
        else if ('0' > *s || '9' < *s ){
        	return false;
        }
        if (point_counter > 1) {
        	return false;
        }
        s++;
    }

    return true;
}
