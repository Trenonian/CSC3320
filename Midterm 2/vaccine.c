#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 * Name: Michael Anderson
 * Student Email: manderson113@student.gsu.edu
 */

enum sexes {
	male,
	female,
	other
};

const char *sex_names[3] = {
	"Male",
	"Female",
	"Does not wish to identify"
};

enum dose_number {
	one = 1,
	two = 2
};

enum vaccine_type {
	Pfizer,
	Moderna,
	Johnson
};

const char *vaccine_names[3] = {
	"Pfizer",
	"Moderna",
	"Johnson & Johnson"
};

// accurate count of vaccine options
const unsigned int vaccine_count = sizeof(vaccine_names)/sizeof(vaccine_names[0]);

typedef enum selection_options {
	none = 0, // no selection made
	get = 1,  // retrieving a record
	put = 2,  // creating a record
	quit = 3  // exit the program
} selection;

// contains all the information stored for the form
typedef struct form {
	char firstName[50], lastName[50], zipcode[13], code[9];
	struct tm dateOfBirth, previousDose;
	enum sexes sex;
	enum dose_number dose;
	enum vaccine_type vaccine;
} Form;

// this struct stores all the forms and meta information for them
typedef struct registry {
	Form *forms;         // pointer to all the forms
	size_t max;          // the current maximum count
	size_t count;        // number of forms stored
	double growthFactor; // how much to expand the memory by when it fills up
} Registry;

// creates the form, and ensures there is enough
// memory allocated for all the forms
Form* create_form(Registry*);

// prompts the user for the information to fill
// out the form and returns it
Form* register_form(Form*);

// prints a form with formatting
void print_form(Form*);

// generates the code for the given form and stores it
// in the form
Form* generate_code(Form*);

// searches the registry for a form with a given code
Form* retrieve(char*, Registry*);

// initializes the registry, which is the struct that holds
void setup(Registry*);

// prompts the user for if they want to
// make a new record, search for a record, or quit
selection getSelection();

// prompts the user for a code to search the registry
void find_form(Registry *vr);

// cleans up before quitting
void end(Registry *vr);

// fills the time struct with 0's
void zero_time(struct tm*);

void main(int argc, char* argv[])
{
	Registry vr;
	setup(&vr);
	while (1) // continuous loop
	{
		selection choice = getSelection();
		if (choice == put) { // create new entry
			// creates and fills the form
			Form *newForm = create_form(&vr);
			// adds the form to the registry
			register_form(newForm);
		} else if (choice == get) { // find entry
			find_form(&vr);
		} else {
			end(&vr); // cleans up
			return; // ends the program
		}
	}
}	

// initial setup for the registry to hold the forms
void setup(Registry *vr)
{
	const size_t INITIAL_COUNT = 5;
	const double GROWTH_FACTOR = 1.5; // will increase by 1.5x times when full

	vr->max = INITIAL_COUNT;
	vr->growthFactor = GROWTH_FACTOR;
	vr->forms = (Form*)malloc(vr->max * sizeof(struct form));
	vr->count = 0;
}

// prompts the user for what action they'd like to preform
selection getSelection()
{
	selection choice = none;
	while (choice == none)
	{
		printf("(N)ew, (R)etrieve, (Q)uit\n");
		char input[20];
		scanf("%s",input);
		char c = input[0];
		if ((c == 'n') || (c == 'N')) {
			choice = put;
		} else if ((c == 'r') || (c == 'R')) {
			choice = get;
		} else if ((c == 'q') || (c == 'Q')) {
			choice = quit;
		}
	}
	printf("\n");
	return choice;
}

// prompts the user for the code, prints the matching form
void find_form(Registry *vr)
{
	printf("Enter your vaccine code: \n");
	char input[20];
	scanf("%s",input);
	Form *f = retrieve(input, vr);
	printf("\n");
	if (f == NULL) {
		// not found
		printf("Record not found.\n\n");
	} else {
		print_form(f);	
	}
}

// final cleanup
void end(Registry *vr)
{
	// frees the allocated space for the forms
	free(vr->forms);
}


Form* create_form(Registry* vr)
{
	if (vr->count >= vr->max)
	{
		// need to expand allocated space
		vr->max *= vr->growthFactor;
		vr->forms = (Form*)realloc(vr->forms, vr->max * sizeof(struct form));
	}
	// get the index for the next form location
	Form *newForm = &(vr->forms[vr->count]);
	vr->count++;
	return newForm;
}

Form* register_form(Form* f)
{
	// zero out all the members of the time structs
	zero_time(&f->dateOfBirth);
	zero_time(&f->previousDose);

	printf("First name: ");
	scanf("%s", f->firstName);
	
	printf("Last name: ");
	scanf("%s", f->lastName);
	
	printf("Date of birth (mm/dd/yyyy): ");
	scanf("%d/%d/%d", &(f->dateOfBirth.tm_mon), &(f->dateOfBirth.tm_mday), &(f->dateOfBirth.tm_year));
	// months are from 0-11
	f->dateOfBirth.tm_mon--;
	// years are from 1900
	f->dateOfBirth.tm_year -= 1900;
	
	printf("(M)ale, (F)emale, (X) Do not wish to identify: ");
	char sex[20];
	scanf("%s", sex);
	char c = sex[0];
	if ((c == 'M') || (c == 'm')) {
		f->sex = male;
	} else if ((c == 'F') || (c == 'f')) {
		f->sex = female;
	} else {
		f->sex = other;
	}
	
	printf("Dose number: ");
	unsigned int dose;
	scanf("%d", &dose);
	if (dose == 2) {
		f->dose = two;
	} else {
		f->dose = one;
	}
	
	// only if the user had a previous dose
	if (f->dose > 1) {
		printf("Date of last dose (mm/dd/yyyy): ");
		scanf("%d/%d/%d", &(f->previousDose.tm_mon), &(f->previousDose.tm_mday), &(f->previousDose.tm_year));
		// months are from 0-11
		f->previousDose.tm_mon--;
		// years are from 1900
		f->previousDose.tm_year -= 1900;
	}
	
	// print available vaccines
	unsigned int i;
	for (i=0; i<vaccine_count; i++) {
		printf("%d: %s\n", i, vaccine_names[i]);
	}
	printf("Type of vaccine: ");
	unsigned int vaccine_choice = -1; // becomes largest number for unsigned ints
	while (vaccine_choice >= vaccine_count) // vaccine_choice cannot be negative
	{
		scanf("%d", &vaccine_choice);
	}
	f->vaccine = vaccine_choice;
	
	printf("Zip Code: ");
	scanf("%s", f->zipcode);
	
	printf("\n");
	generate_code(f);
	return f;
}

// returns the form with the matching code, NULL otherwise
Form* retrieve(char* code, Registry *vr)
{
	int i;
	for (i=0; i < vr->count; i++) {
		Form *f = &(vr->forms[i]);
		char *formCode = f->code;
		if (strncmp(code, formCode, 8) == 0) {
			return f;
		}
	}
	return NULL;
}

// prints all information stored in the form
void print_form(Form *f) {
	printf("Name: %s %s\n", f->firstName, f->lastName);
	
	printf("Date of birth: %d/%d/%d\n",
		f->dateOfBirth.tm_mon+1, f->dateOfBirth.tm_mday, f->dateOfBirth.tm_year + 1900
	);
	
	printf("Sex: %s\n", sex_names[f->sex]);
	
	printf("Dose number: %d\n", f->dose);
	
	if (f->dose > 1) {
		// ony print if there was a previous dose
		printf("Date of last dose: %d/%d/%d\n",
			f->previousDose.tm_mon+1, f->previousDose.tm_mday, f->previousDose.tm_year + 1900
		);
	}

	printf("Type of vaccine: %s\n", vaccine_names[f->vaccine]);
	
	printf("Zip Code: %s\n", f->zipcode);
	
	printf("\n");
}

Form* generate_code(Form* f)
{
	f->code[0] = f->firstName[0]; // first letter of first name
	
	f->code[1] = f->lastName[0]; // first letter of last name

	// time from 1900 to birth day in seconds
	time_t birthTime = mktime( &f->dateOfBirth );
	time_t currentTime;
	time(&currentTime); // time from 1900 to now in seconds
	//  finds the user's current age                  s    min  hr   yr         fix rounding issue
	int years = ((difftime(currentTime, birthTime) / (60 * 60 * 24 * 365.25)) + 1e-9);
	// age as two digits
	if (years <= 0) { // zeroes if less or equal to zero
		f->code[2] = '0';
		f->code[3] = '0';
	} else if (years >= 99) { // caps at 99
		f->code[2] = '9';
		f->code[3] = '9';
	} else { // 0 < age < 99
		char age[3];
		sprintf(age, "%d", years); // age = (string)years
		if (years < 10) {
			f->code[2] = '0';
			f->code[3] = age[0];
		} else {
			f->code[2] = age[0];
			f->code[3] = age[1];
		}
	}
	
	f->code[4] = vaccine_names[f->vaccine][0]; // first letter of vaccine
	
	int zipSize = strlen(f->zipcode);
	int i;
	int index = 5; // starts at the 5th index of the code, 6-8th characters
	for (i=zipSize-3; i<zipSize; i++)
	{
		// gets last three characters of zip code
		if (i<0) {
			// only relevant if zip code is less than three characters
			// this shouldn't happen, but ensures the program won't break
			continue;
		}
		f->code[index] = f->zipcode[i];
		index++;
	}
	
	f->code[index] = '\0'; // null character, end string

	printf("Your unique code: %s\n\n", f->code);
	return f;
}	

// zeroes out the time struct, had issues with it otherwise
void zero_time(struct tm *time)
{
	time->tm_sec= 0;
	time->tm_min = 0;
	time->tm_hour = 0;
	time->tm_mday = 0;
	time->tm_mon = 0;
	time->tm_year = 0;
	time->tm_wday = 0;
	time->tm_yday = 0;
	time->tm_isdst = 0;
}
