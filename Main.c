#include <stdio.h>
#include "Defs.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "Countries.h"
#include "KeyValuePair.h"


void clean(Point po,City city,Country co){
	//free pointers:
	po=NULL;
	city=NULL;
	co=NULL;

	printf("all the memory cleaned and program safely closed");
}

//transformKeyIntoNumber
int transformKeyIntoNumber(char* ch){
	int i = 0;
	int iCh = 0;
	for(i=0;i<strlen(ch);i++){
		iCh=iCh+(int)ch[i];
	}
	return iCh;
}//transformKeyIntoNumber

int main(int argc,char* argv[]) {

	int ch = 0;
	int numOfCountry = 0;
	int i;
	int x;
	int y;
	char countryNameB[300] = {'\0'};
	int residentsNum;
	Point po = NULL;
	City city = NULL;
	Country co = NULL;
	City ci = NULL;
	char getLine[300];
	const char comma[2] = "," ;
	char bufferName [300]  = {'\0'};
	char bufferDish [300]  = {'\0'};
	int x1;
	int x2;
	int y1;
	int y2;


	hashTable atlasHash = createHashTable(
			(Element)copyName
			,(Element)freeName
			,(Element)printName
			, (Element)copyCountry
			,(Element)freeCountryH
			,(Element)printCountryH,
			(Element)equalNames
			,(Element)transformKeyIntoNumber
			, (atoi(argv[1])));


	if(atlasHash == NULL){
		printf("no memory available");
		ch=8;
		destroyHashTable(atlasHash);
		clean(po,city,co);
	}
	else
	{
		FILE *file;
		file=fopen(argv[3], "r");
		if(file==NULL){
			printf("error opening file");
			return -1;	}

		while(fgets(getLine,300,file) != NULL){ //read one line until the end of file

			if(getLine[0] != '\t'){

				strcpy(countryNameB,strtok(getLine,comma));//change ',' to pointer

				x1=atoi (strtok (NULL,comma));//casting from char to int until the comma
				y1=atoi (strtok (NULL,comma));
				x2=atoi (strtok (NULL,comma));
				y2=atoi (strtok (NULL,"\n"));

				co = addCountry(countryNameB,x1,y1,x2,y2);
				addToHashTable(atlasHash,countryNameB,co);
				freeCountry(co);
				co = NULL;

				if((Country )lookupInHashTable(atlasHash,countryNameB) == NULL){
					printf("no memory available");
					ch=8;
					destroyHashTable(atlasHash);
					clean(po,city,co);
					break;
				}
				numOfCountry++;
			}

			else{//city
				for(i=1;i<strlen(getLine); i++){ //make the string start at zero (remove TAB)
					getLine[i-1]=getLine[i];
				}
				//name
				strcpy(bufferName,strtok(getLine,comma));//copy the line until the comma

				//dish
				strcpy(bufferDish, strtok(NULL,comma));

				residentsNum = atoi(strtok (NULL ,"\n"));

				ci = initCityBuff(bufferName,bufferDish, residentsNum);
				if(ci==NULL){
					printf("no memory available");
					ch=8;
					destroyHashTable(atlasHash);
					clean(po,city,co);
					break;
				}

				co = (Country )lookupInHashTable(atlasHash,countryNameB);
				if(addCity(co, ci) == null){
					printf("no memory available");
					ch=8;
					destroyHashTable(atlasHash);
					clean(po,city,co);
				}
				freeCity(ci);//free all the city not the pointer

			}
		}
		fclose(file);
	}


	//end read text
	while( ch != 8 )
	{
		printf("please choose one of the following numbers:\n");
		printf("1 : print countries\n");
		printf("2 : add country\n");
		printf("3 : add city to country\n");
		printf("4 : delete city from country\n");
		printf("5 : print country by name\n");
		printf("6 : delete country\n");
		printf("7 : is country in area\n");
		printf("8 : exit\n");

		scanf("%d", &ch);

		switch (ch)
		{

		case 1://print countries

			displayHashElements(atlasHash);

			break;

		case 2:// add  country

			printf("please enter a country name\n");
			scanf("%s",countryNameB);

			co = (Country )lookupInHashTable(atlasHash,countryNameB);

			if(co != NULL)//if we find the country in the table
			{
				printf("country with this name already exist\n");
				break;
			}

			printf("please enter tow x and y cordinations:x1,y1,x2,y2\n");
			scanf("%d,%d,%d,%d", &x1, &y1, &x2, &y2);

			co = addCountry(countryNameB,x1,y1,x2,y2);
			addToHashTable(atlasHash,countryNameB,co);
			freeCountry(co);
			co = NULL;

			numOfCountry++;

			break;

		case 3://add city to country

			printf("please enter a country name\n");
			scanf("%s",countryNameB);
			co = (Country )lookupInHashTable(atlasHash,countryNameB);
			if( co != NULL)
			{//		check if country exist
				//city:
				printf("please enter a city name\n");
				scanf("%s",bufferName);


				if (ifCityExistInCountry(co, bufferName) == false)
				{//	city already in the country?

					printf("please enter the city favorite food\n");
					scanf("%s",bufferDish);
					printf("please enter number of residents in city\n"); //

					scanf("%d", &residentsNum);

					city = initCity(bufferName, bufferDish, residentsNum);//enter residentsNum to the country
					if(city==NULL)
					{
						printf("no memory available");
						ch=8;
						destroyHashTable(atlasHash);
						clean(po,city,co);
						break;
					}
					if(addCity(co, city) == null)//enter a city to the country
					{

						printf("no memory available");
						ch=8;
						destroyHashTable(atlasHash);
						clean(po,city,co);
						break;
					}
					freeCity(city);

				}//if city already in the country?
				else
				{
					printf("this city already exist in this country\n");//error message
				}
			}//if country exist?

			else
			{
				printf("country name not exist .\n");//error message

				break;
			}

			break;

		case 4://delete city from country
			printf("please enter a country name\n");
			scanf("%s",countryNameB);

			co = (Country )lookupInHashTable(atlasHash,countryNameB);
			if(co == NULL)
			{//		check if country exist
				printf("country name not exist\n");
				break;
			}
			else
			{
				//city:
				printf("please enter a city name\n");
				scanf("%s",bufferName);

				if (ifCityExistInCountry(co, bufferName) ==true)
				{//if city already in the country?
					removeCityFromCountry(co,bufferName);//remuveCityFromCountry
				}
				else
				{
					printf("the city not exist in this country\n");    //error message country exist city no
				}
			}


			break;

		case 5:  /* print country by name */
			printf("please enter a country name\n");
			scanf("%s",countryNameB);

			co = (Country )lookupInHashTable(atlasHash,countryNameB);
			if(co == NULL)
			{
				printf("country name not exist\n");//error message
			}
			else
			{
				if (printCountry(co) != success)
				{
					printf("country name not exist\n");
				}
			}
			break;

		case 6://delete country
			printf("please enter a country name\n");
			scanf("%s",countryNameB);

			if(removeFromHashTable(atlasHash,countryNameB) == success){
				printf("country deleted\n");
				numOfCountry--;
			}

			else
				printf("can't delete the country\n");

			break;

		case 7://is country in area
			printf("please enter a country name\n");
			//get the country name
			scanf("%s",countryNameB);

			co = (Country)lookupInHashTable(atlasHash,countryNameB);

			if(co==NULL)
			{
				printf("country name not exist\n");
				break;
			}
			else
			{
				//get the point:
				printf("please enter x and y cordinations:x,y\n");
				scanf("%d,%d", &x, &y);
				po = initPoint(x, y);
				if(po==NULL)
				{
					printf("no memory available");
					ch=8;
					destroyHashTable(atlasHash);
					freePoint(po);
					clean(po,city,co);
					break;
				}

				//search the point in the country:
				if (checkPointInCountry(co, po) == true)
				{
					printf("the coordinate in the country\n");

				}
				else
				{
					printf("the coordinate not in the country\n");
				}

			}
			freePoint(po);
			break;

		case 8:  /*  exit and clean memory */

			destroyHashTable(atlasHash);
			clean(po,city,co);

			break;

		default:
		{
			printf("‫‪please‬‬ ‫‪choose‬‬ ‫‪a‬‬ ‫‪valid‬‬ ‫‪number‬‬ \n");
		}

		}//Switch

	}//while
}//main
