#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
	FILE *fp;
	fp=fopen("contacts.txt","w");
	
	for(int i=0; i<addressBook->contactCount; i++){
		fprintf(fp,"%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	fclose(fp);	
}

void loadContactsFromFile(AddressBook *addressBook) {
	FILE *fp = fopen("contacts.txt", "r");
	while(fscanf(fp, "%s %s %s",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email) == 3){
		addressBook->contactCount++;
	}
	fclose(fp);
}
