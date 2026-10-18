#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
void listContacts(AddressBook *addressBook) 
{
	int choice;

	printf("Sort contacts by:\n");
	printf("1. Name\n");
	printf("2. Phone\n");
	printf("3. Email\n");
	printf("4. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	getchar();
	if(choice==4){
		return;
	}
	for(int i=0; i<addressBook->contactCount-1; i++){
		for(int j=i+1; j<addressBook->contactCount; j++){
			char *value1;
			char *value2;
			if(choice == 1)
			{
				value1 = addressBook->contacts[i].name;
				value2 = addressBook->contacts[j].name;
			}else if(choice == 2)
            		{
                		value1 = addressBook->contacts[i].phone;
                		value2 = addressBook->contacts[j].phone;
            		}else if(choice == 3)
	            	{
                    		value1 = addressBook->contacts[i].email;
                		value2 = addressBook->contacts[j].email;
            		}else{
				printf("Invalid Choice\n");
				return; 
			}
			if(strcmp(value1, value2) > 0)
	            	{
                    		Contact temp;
                		temp = addressBook->contacts[i];
                		addressBook->contacts[i] = addressBook->contacts[j];
                		addressBook->contacts[j] = temp;
            		}		
		}
	}
	printf("\nName\t\tPhone\t\tEmail\n");
	// Sort contacts based on the chosen criteria
    	for(int i = 0; i < addressBook->contactCount; i++)
	{
		printf("%s\t\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
}

void initialize(AddressBook *addressBook) {
    	addressBook->contactCount = 0;
    
    
    	loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
	saveContactsToFile(addressBook); // Save contacts to file
    	exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	Contact newContact;
	do
	{
		printf("Enter Name: ");
		fgets(newContact.name, 50, stdin);
		newContact.name[strcspn(newContact.name, "\n")] = '\0';

		if(!isalpha(newContact.name[0]))
		{
			printf("Invalid name\n");
		}

	}while(!isalpha(newContact.name[0]));
	
	int flag;
	int unique;
	do{
		flag=1;
		unique=1;
		printf("Enter Phone: ");
		fgets(newContact.phone,20,stdin);
		newContact.phone[strcspn(newContact.phone, "\n")] = '\0';
		
		if(newContact.phone[0] < '6' || newContact.phone[0] > '9'){
			flag=0;
			printf("Phone number must start with digit 6,7,8 or 9\n");
			continue;
		}
		int count=0;
		for(int i=0; newContact.phone[i] != '\0'; i++){
			count++;
			if(!isdigit(newContact.phone[i])){
				flag=0;
			}
		}
		if(count != 10){
			flag=0;
			printf("Phone number must be exactly 10 digits\n");
			continue;
		}
		if(!flag){
			printf("Invalid Phone\n");
			continue;
		}
		for(int i=0; i<addressBook->contactCount; i++){
			if(strcmp(newContact.phone,addressBook->contacts[i].phone) == 0){
				unique=0;
				break;
			}
		}
		if(!unique){
			printf("Phone number already exists\n");
		}
	}while(!flag || !unique);
	
	do{
		printf("Enter email: ");
		fgets(newContact.email,50,stdin);
		newContact.email[strcspn(newContact.email, "\n")] = '\0';
		flag=1;
		if(!isalpha(newContact.email[0])){
			flag=0;
		}
		if(strstr(newContact.email,"@gmail.com")==NULL){
			flag=0;
		}
		if(!flag){
			printf("Invalid email\n");
		}
		int atCount = 0;
		for(int i = 0; newContact.email[i] != '\0'; i++)
		{
			if(newContact.email[i] == '@')
			atCount++;
		}
		if(atCount != 1)
		{
			flag=0;
			printf("Email must contain exactly one @\n");
			continue;
		}
		int dotCount = 0;
		for(int i = 0; newContact.email[i] != '\0'; i++)
		{
			if(newContact.email[i] == '.')
			dotCount++;
		}
		if(dotCount == 0)
		{
			flag=0;
			printf("Email must contain a dot\n");
			continue;
		}
		int atPos = -1;
		int dotpos = -1;
		int dotbeforeat = 0;

		for(int i = 0; newContact.email[i] != '\0'; i++)
		{
			if(newContact.email[i] == '@')
				atPos = i;
			if(newContact.email[i] == '.'){
				dotpos=i;
				if(atPos==-1){
					dotbeforeat = 1;
				}
			}
		}
		if(dotbeforeat)
		{
			flag=0;
			printf("Dot must appear after @\n");
			continue;
		}
		if(dotpos == atPos + 1)
		{
			flag=0;
			printf("There must be at least one character between @ and .\n");
			continue;
		}
		int len = strlen(newContact.email);
		if(len < 4 || strcmp(newContact.email + len - 4, ".com") != 0)
		{
			flag=0;
			printf("Email must end with .com\n");
			continue;
		}
		for(int i = 0; newContact.email[i] != '\0'; i++)
		{
			if(!isalnum(newContact.email[i]) && newContact.email[i] != '@' && newContact.email[i] != '.')
			{
				flag = 0;
				printf("Invalid symbol in email\n");
				break;
			}
		}

		unique=1;
		for(int i=0; i<addressBook->contactCount; i++){
			if(strcmp(newContact.email,addressBook->contacts[i].email) == 0){
				unique=0;
				break;
			}
		}
		if(!unique){
			printf("Email already exists\n");
		}
	}while(!flag || !unique);

	addressBook->contacts[addressBook->contactCount] = newContact;
	addressBook->contactCount++;
	/* Define the logic to create a Contacts */
}

void searchContact(AddressBook *addressBook) 
{
	int choice;
	printf("Search by:\n");
	printf("1. Name\n");
	printf("2. Phone\n");
	printf("3. Email\n");
	printf("4. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	getchar();
	
	if(choice<1 || choice>4){
		printf("Invalid Choice\n");
		return;
	}
	if(choice == 4)
	{
		return;
	}

	char searchValue[50];
	printf("Enter search value: ");
	fgets(searchValue, 50, stdin);
	searchValue[strcspn(searchValue, "\n")] = '\0';

	int flag=0;
	for(int i=0; i<addressBook->contactCount; i++){
		
		char *value;
		if(choice==1){
			value=addressBook->contacts[i].name;
		}else if(choice==2){
			value=addressBook->contacts[i].phone;
		}else if(choice==3){
			value=addressBook->contacts[i].email;
		}

		if(strcmp(searchValue, value) == 0){
			printf("\nIndex: %d\n",i);
			printf("Name: %s\n",addressBook->contacts[i].name);
			printf("Phone: %s\n",addressBook->contacts[i].phone);
			printf("Email: %s\n",addressBook->contacts[i].email);
			flag=1;
			if(choice != 1){
				break;
			}
		}
	}
	if(flag==0){
		printf("Contact not found\n");
		return;
	}
	/* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	int choice;
	printf("Edit contact by:\n");
	printf("1. Name\n");
	printf("2. Phone\n");
	printf("3. Email\n");
	printf("4. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	getchar();

	if(choice == 4)
	{
		return;
	}
	char searchValue[50];
	printf("Enter search value: ");
	fgets(searchValue, 50, stdin);
	searchValue[strcspn(searchValue, "\n")] = '\0';

	int flag=0;
	int index=-1;
	int count=0;
	for(int i=0; i<addressBook->contactCount; i++){
		char *value;
		if(choice==1){
			value=addressBook->contacts[i].name;
		}else if(choice==2){
			value = addressBook->contacts[i].phone;
		}else if(choice==3){
			value = addressBook->contacts[i].email;
		}else{
			printf("Invalid Choice\n");
			return;
		}
		if(strcmp(searchValue, value) == 0){

			flag=1;
			count++;
			index=i;
			printf("\nIndex: %d\n",i);
			printf("Name: %s\n", addressBook->contacts[i].name);
			printf("Phone: %s\n", addressBook->contacts[i].phone);
			printf("Email: %s\n", addressBook->contacts[i].email);
			if(choice!=1){
				break;
			}
		}
	}
	if(flag == 0)
	{
		    printf("Contact not found\n");
		        return;
	}
	
	if(choice==1){
		if(count>1){
			printf("\nEnter index of contact to edit: ");
			scanf("%d", &index);
			getchar();
			if(index < 0 || index >= addressBook->contactCount ||strcmp(searchValue, addressBook->contacts[index].name) != 0){
				printf("Invalid Index\n");
				return;
			}
		}
	}

	int editChoice;

	printf("What do you want to edit?\n");
	printf("1. Name\n");
	printf("2. Phone\n");
	printf("3. Email\n");
	printf("4. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &editChoice);
	getchar();
	if(choice==4){
		return;
	}

	if(editChoice == 1)
	{
    		int valid=1;
    		do
    		{
        		printf("Enter new name: ");
        		fgets(addressBook->contacts[index].name, 50, stdin);
        		addressBook->contacts[index].name[strcspn(addressBook->contacts[index].name, "\n")] = '\0';
        		valid = 1;
			if(addressBook->contacts[index].name[0] == '\0' ||!isalpha(addressBook->contacts[index].name[0])){
            			valid = 0;
            			printf("Invalid name\n");
        		}

    		}while(!valid);	
	}else if(editChoice == 2)
	{	
		int valid;
		int unique;
		do{
			valid=1;
			unique=1;
			printf("Enter new phone: ");
			fgets(addressBook->contacts[index].phone, 20, stdin);
			addressBook->contacts[index].phone[strcspn(addressBook->contacts[index].phone, "\n")] = '\0';
			if(addressBook->contacts[index].phone[0] == '\0')
			{
				valid = 0;
			}
	    		for(int i = 0; addressBook->contacts[index].phone[i] != '\0'; i++)
        		{
            			if(!isdigit(addressBook->contacts[index].phone[i]))
            			{
                			valid = 0;
                			break;
            			}
        		}
			if(addressBook->contacts[index].phone[0] < '6' || addressBook->contacts[index].phone[0] > '9')
			{
				valid = 0;
				printf("Phone number must start with digit 6,7,8 or 9\n");
				continue;
			}
			int count = 0;
			for(int i = 0; addressBook->contacts[index].phone[i] != '\0'; i++)
			{
				count++;
				if(!isdigit(addressBook->contacts[index].phone[i]))
				{
					valid = 0;
				}
			}
			if(count != 10)
			{
				valid = 0;
				printf("Phone number must be exactly 10 digits\n");
				continue;
			}
			if(!valid)
	        	{
            			printf("Invalid Phone\n");
            			continue;
        		}
			unique = 1;
			for(int i = 0; i < addressBook->contactCount; i++){
				if(i != index && strcmp(addressBook->contacts[index].phone,addressBook->contacts[i].phone) == 0)
				{
					unique = 0;
					break;
				}
			}
			if(!unique)
			{
				printf("Phone number already exists\n");
			}
		}while(!valid || !unique);
	}else if(editChoice == 3)
	{
		int valid;
		int unique;
		do{
			valid=1;
			unique=1;
			printf("Enter new email: ");
			fgets(addressBook->contacts[index].email, 50, stdin);
			addressBook->contacts[index].email[strcspn(addressBook->contacts[index].email, "\n")] = '\0';
			if(addressBook->contacts[index].email[0] == '\0' || !isalpha(addressBook->contacts[index].email[0]))
			{
				valid = 0;
			}
			if(strstr(addressBook->contacts[index].email, "@gmail.com") == NULL)
			{
				valid = 0;
			}
			int atCount = 0;
			for(int i = 0; addressBook->contacts[index].email[i] != '\0'; i++)
			{
				if(addressBook->contacts[index].email[i] == '@')
				atCount++;
			}
			if(atCount != 1)
			{
				valid=0;
				printf("Email must contain exactly one @\n");
				continue;
			}
			int dotCount = 0;
			for(int i = 0; addressBook->contacts[index].email[i] != '\0'; i++)
			{
				if(addressBook->contacts[index].email[i] == '.')
					dotCount++;
			}
			if(dotCount == 0)
			{
				valid=0;
				printf("Email must contain a dot\n");
				continue;
			}
			int atPos = -1;
			int dotPos = -1;
			for(int i = 0; addressBook->contacts[index].email[i] != '\0'; i++)
			{
				if(addressBook->contacts[index].email[i] == '@')
					atPos = i;
				if(addressBook->contacts[index].email[i] == '.')
					dotPos = i;
			}
			if(dotPos < atPos){
				valid=0;
				printf("Dot must appear after @\n");
				continue;
			}
			if(dotPos == atPos + 1)
			{
				valid=0;
				printf("There must be at least one character between @ and .\n");
				continue;
			}
			int len = strlen(addressBook->contacts[index].email);
			if(len < 4 || strcmp(addressBook->contacts[index].email + len - 4, ".com") != 0)
			{
				valid=0;
				printf("Email must end with .com\n");
				continue;
			}
			for(int i = 0; addressBook->contacts[index].email[i] != '\0'; i++)
			{
				if(!isalnum(addressBook->contacts[index].email[i]) && addressBook->contacts[index].email[i] != '@' &&addressBook->contacts[index].email[i] != '.'){
					valid = 0;
					printf("Invalid symbol in email\n");
					break;
				}
			}
			if(!valid)
			{
				printf("Invalid email\n");
				continue;
			}
			unique = 1;
			for(int i = 0; i < addressBook->contactCount; i++){
				if(i != index && strcmp(addressBook->contacts[index].email, addressBook->contacts[i].email) == 0){
					unique = 0;
					break;
				}	       
			}
			if(!unique)
			{
				printf("Email already exists\n");
			}
		}while(!valid || !unique);
	}else
	{
		printf("Invalid Choice\n");
		return;
	}
	/* Define the logic for Editcontact */
}

void deleteContact(AddressBook *addressBook)
{
	int choice;
	printf("Delete contact by:\n");
    	printf("1. Name\n");
    	printf("2. Phone\n");
    	printf("3. Email\n");
	printf("4. Exit\n");
    	printf("Enter your choice: ");
    	scanf("%d", &choice);
    	getchar();

	if(choice==4){
		return;
	}
    	char searchValue[50];

    	printf("Enter search value: ");
    	fgets(searchValue, 50, stdin);
    	searchValue[strcspn(searchValue, "\n")] = '\0';    
	/* Define the logic for deletecontact */
   	int flag=0;
	int index=-1;
	int count=0;
	for(int i=0; i<addressBook->contactCount; i++){
		char *value;

		if(choice == 1)
			value = addressBook->contacts[i].name;
		else if(choice == 2)
			value = addressBook->contacts[i].phone;
		else if(choice == 3)
			value = addressBook->contacts[i].email;
		else
		{
			printf("Invalid Choice\n");
			return;
		}
		if(strcmp(searchValue, value) == 0)
		{
			flag = 1;
			index = i;
			count++;
			printf("\nIndex: %d\n", i);
			printf("Name: %s\n", addressBook->contacts[i].name);
			printf("Phone: %s\n", addressBook->contacts[i].phone);
			printf("Email: %s\n", addressBook->contacts[i].email);
			if(choice != 1)
			{
				break;
			}
		}					        
	}
	if(flag == 0)
	{
		printf("Contact not found\n");
		return;
	}
	if(choice == 1 && count > 1)
	{
		do
		{
			printf("\nEnter index of contact to delete: ");
			scanf("%d", &index);
			getchar();
			if(index < 0 || index >= addressBook->contactCount || strcmp(searchValue, addressBook->contacts[index].name) != 0){
				printf("Invalid Index\n");
			}
		}while(index < 0 || index >= addressBook->contactCount || strcmp(searchValue, addressBook->contacts[index].name) != 0);
	}
	char confirm;

	printf("Are you sure you want to delete? (y/n): ");
	scanf(" %c", &confirm);

	if(confirm != 'y' && confirm != 'Y')
	{
		printf("Delete cancelled\n");
		return;
	}
	for(int i=index; i< addressBook->contactCount-1; i++){
		addressBook->contacts[i] = addressBook->contacts[i+1];
	}
	addressBook->contactCount--;
}
