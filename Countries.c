//
// Created by Yuval and Adi on 11/19/18.
//

#include "Countries.h"

struct Point {
	int x;
	int y;
};

struct Garea {
	Point p1UpLeft;
	Point p2DownRight;
};

struct City {
	char *name;
	char *dish;
	int residentsNum;
};

struct Country {
	char *name;
	City *cities;//array of pointers to city
	int citiesNum;
	Garea gArea;
};
////function:


//Init structs:
Point initPoint(int x, int y) {
	Point newPoint = (Point) malloc(sizeof(struct Point));
	if (newPoint == NULL)
		return NULL;
	newPoint->x = x;
	newPoint->y = y;
	return newPoint;
}

Garea initGarea(Point left, Point right) {

	Garea newArea = (Garea) malloc(sizeof(struct Garea));
	if (newArea == NULL) {
		return NULL;
	}
	newArea->p1UpLeft = left;
	newArea->p2DownRight = right;

	return newArea;
}

City initCity(char *name, char *dish, int residentsNum) {
	City newCity = (City) malloc(sizeof(struct City));
	if (newCity == NULL)
		return NULL;
	//name
	newCity->name = (char *) malloc(strlen(name) + 1);
	if (newCity->name == NULL)
		return NULL;
	strcpy(newCity->name, name);

	//dish
	newCity->dish = (char *) malloc(strlen(dish) + 1);
	if (newCity->dish == NULL)
		return NULL;
	strcpy(newCity->dish, dish);

	//residentsNum
	newCity->residentsNum = residentsNum;

	return newCity;
}

City initCityBuff(char name[300], char dish[300], int residentsNum) {
	City newCity = (City) malloc(sizeof(struct City));
	if (newCity == NULL)
		return NULL;
	//name
	newCity->name = (char *) malloc(strlen(name) + 1);
	if (newCity->name == NULL)
		return NULL;
	strcpy(newCity->name, name);

	//dish
	newCity->dish = (char *) malloc(strlen(dish) + 1);
	if (newCity->dish == NULL)
		return NULL;
	strcpy(newCity->dish, dish);

	//residentsNum
	newCity->residentsNum = residentsNum;

	return newCity;
}


Country initCountry(char *name1, Garea gArea) {

	Country newCountry = (Country) malloc(sizeof(struct Country));
	if (newCountry == NULL)
		return NULL;
	newCountry->cities = NULL;
	newCountry->citiesNum = 0;
	newCountry->gArea = gArea;
	newCountry->name = "";
	char *newName = (char *) malloc(strlen(name1) + 1);
	if (newName == NULL)
		return NULL;
	strcpy(newName, name1);
	newCountry->name = newName;
	return newCountry;
}

bool checkPointInCountry(Country country, Point point) {
	if (point->x >= country->gArea->p1UpLeft->x && point->x <= country->gArea->p2DownRight->x) {
		if (point->y >= country->gArea->p2DownRight->y && point->y <= country->gArea->p1UpLeft->y) {
			return true;
		} else
			return false;
	} else
		return false;
}//checkPointInCountry


//This function get country name and two coordinations and add this country to Country stuck.
Country addCountry(char *name, int x1, int y1, int x2, int y2) {
	Point point1 = initPoint(x1, y1);
	Point point2 = initPoint(x2, y2);
	if (point1 == NULL || point2 == NULL)
		return NULL;
	Garea area = initGarea(point1, point2);
	if (area == NULL)
		return NULL;
	Country newCountry;
	newCountry = initCountry(name, area);
	if (newCountry == NULL)
		return NULL;
	return newCountry;
}//addCountry

//add city:
status addCity(Country country, City newCity) {
	if ((newCity == NULL) || (country == NULL)) {
		return failure;
	}

	country->citiesNum= country->citiesNum+1;
	//realloc for cities array in country
	country->cities = (City *) realloc(country->cities, ((country->citiesNum)) * sizeof(City));
	if (country->cities == NULL) {//if the allocation faild--> return null status
		return null;
	}

	//malloc for the last city in array
	country->cities[country->citiesNum - 1] = (City) malloc(sizeof(struct City));
	if (country->cities[country->citiesNum - 1] == NULL) {
		return null;
	}

	//dish
	country->cities[country->citiesNum - 1]->dish = (char *) malloc(strlen(newCity->dish) + 1);

	if (country->cities[country->citiesNum - 1]->dish == NULL) {
		return null;
	} else {
		strcpy(country->cities[country->citiesNum - 1]->dish, newCity->dish);
	}

	//name
	country->cities[country->citiesNum - 1]->name = (char *) malloc(strlen(newCity->name) + 1);

	if (country->cities[country->citiesNum - 1]->name == NULL) {
	} else {
		strcpy(country->cities[country->citiesNum - 1]->name, newCity->name);
	}

	//number
	country->cities[country->citiesNum - 1]->residentsNum = newCity->residentsNum;

	return success;

}//addCity

//Remove city from country:
status removeCityFromCountry(Country country, char *cityName) {

	int i, numCityToRemove;
	for (i = 0; i < country->citiesNum; i++) {
		if (strcmp(country->cities[i]->name, cityName) == 0) {
			numCityToRemove = i;
			break;
		}
	}
	freeCity(country->cities[numCityToRemove]);

	country->cities[numCityToRemove] = (country->cities[country->citiesNum - 1]);

	country->cities = (City *) realloc(country->cities, ((country->citiesNum - 1)) * sizeof(City));
	if (country == NULL) {
		return failure;
	} else {
		country->citiesNum--;
		return success;
	}
}
//removeCityFromCountry

bool ifCityExistInCountry(Country country, char *cityName) {
	if (country == NULL) {
		return false;
	}

	int i;
	for (i = 0; i < country->citiesNum; i++) {
		if (strcmp(country->cities[i]->name, cityName) == 0)
			return true;
	}
	return false;
}//ifCityExistInCountry


//This function get country and return a deep copy country
Country deepCopyCountry(Country originCountry) {
	if (originCountry == NULL)
		return NULL;

	Country newCountry = addCountry(originCountry->name, originCountry->gArea->p1UpLeft->x,originCountry->gArea->p1UpLeft->y,
			originCountry->gArea->p2DownRight->x,originCountry->gArea->p2DownRight->y);

	if (newCountry == NULL)
		return NULL;

	status stat;
	int i, numberOfCity = 0;
	if (originCountry->cities != NULL)//copy cities to country
			{
		numberOfCity = originCountry->citiesNum;
		for (i = 0; i < numberOfCity; i++) {
			stat = addCity(newCountry, originCountry->cities[i]);
			if (stat == failure) {
				return NULL;
			}
		}
			}
	return newCountry;
}//deepCopyCountry


//////free functions:

////free point
void freePoint(Point point) {
	if (point != NULL) {
		free(point);
		point = NULL;
	}
}//free point

//free Garea
void freeGarea(Garea area) {
	if (area != NULL) {
		freePoint(area->p1UpLeft);
		freePoint(area->p2DownRight);

		area->p2DownRight = NULL;
		area->p1UpLeft = NULL;

		free(area);
		area = NULL;
	}
}//free Garea

////free city
void freeCity(City city) {
	if (city != NULL) {
		free(city->dish);
		free(city->name);

		city->dish = NULL;
		city->name = NULL;
		free(city);
		city = NULL;
	}
}//free city

////free country
void freeCountry(Country country) {
	if (country != NULL) {
		freeGarea(country->gArea);
		free(country->name);
		country->gArea = NULL;
		country->name = NULL;
		int i;
		for (i = 0; i < country->citiesNum; i++) {
			freeCity(country->cities[i]);//free every city in the cities array
			country->cities[i] = NULL;
		}
		free(country->cities);
		free(country);

	}

}//free country

//print:
//This function get country, print the details of country and return a status if success.
status printCountry(Country country) {
	//check if the name exist - for status: ifCountryExist(byName)
	if (country->gArea == NULL) {
		return failure;
	} else {

		printf("Country‬‬ %s ‫‪coordinates:‬‬ <%d,%d>,<%d,%d>\n",
				country->name,
				country->gArea->p1UpLeft->x,
				country->gArea->p1UpLeft->y,
				country->gArea->p2DownRight->x,
				country->gArea->p2DownRight->y);
		int i;
		for (i = 0; i < country->citiesNum; i++) {
			printf("‫‪\t‬‬%s ‫‪includes‬‬ ‫‪%d‬‬ ‫‪residents‬‬ ‫‪and‬‬ ‫‪their‬‬ ‫‪favorite‬‬ ‫‪food‬‬ ‫‪is‬‬ %s.\n",
					country->cities[i]->name,
					country->cities[i]->residentsNum,
					country->cities[i]->dish);
			//print all the cities in this country
		}
		return success;// print city from main by loop.
	}

}//printCountryByName

////Hash:
//copyKey
char * copyName(char * ch) {
	char *newName = malloc(strlen(ch) + 1);
	if (newName == NULL) {
		return NULL;
	}
	strcpy(newName,ch);
	return newName;
}//copyKey

//freeKey
status freeName(char * ch) {
	if(ch == NULL)
		return failure;
	free( ch);
	ch = NULL;
	return success;
}//freeKey

//printKey
status printName(char* ch) {
	if(ch == NULL)
		return failure;
	printf("%s",ch);
	return success;
}//printKey

//copyValue
Country copyCountry(Country c) {
	if(c == NULL)
		return NULL;

	return deepCopyCountry(c);
}

//freeValue
status freeCountryH(Country country) {
	if(country ==NULL)
		return failure;
	freeCountry(country);
	return success;
}//freeValue

//printValue
status printCountryH(Country country) {
	if(country ==NULL)
		return failure;
	status stat;
	stat = printCountry(country);
	return stat;
}//printValue

//equalKey
bool equalNames(char* a,char* b)
{
	if((a==NULL)||(b==NULL))
		return false;

	if(strcmp(a,b) == 0)
		return true;
	return false;
}//equalKey

