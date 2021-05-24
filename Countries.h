//
// Created by yuval on 12/2/18.
//

#ifndef ATLASSSS_CONTRIES_H
#define ATLASSSS_CONTRIES_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Defs.h"


typedef struct Point* Point;

typedef struct Garea* Garea;

typedef struct City* City;

typedef struct Country* Country;

//init
Point initPoint(int, int);
Garea initGarea(Point, Point );
City initCity(char *, char *, int );
City initCityBuff(char name[300], char dish[300], int residentsNum );
Country initCountry(char *, Garea );
Country addCountry(char *, int, int, int, int);
status addCity(Country, City );
status removeCityFromCountry(Country, char *);
bool ifCityExistInCountry(Country , char *);
bool checkPointInCountry(Country,Point);
void freePoint(Point);
void freeGarea(Garea);
void freeCity(City);
void freeCountry(Country);
Country deepCopyCountry(Country );
status printCountry(Country);
char* countryToName (Country);

//hash:
char* copyName(char*);
status freeName(char*);
status printName(char*);
Country copyCountry(Country);
status freeCountryH(Country) ;
status printCountryH(Country);
bool equalNames(char*,char*);

#endif //ATLASSSS_CONTRIES_H
