#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define BOOLEAN char
#define TRUE 1
#define FALSE 0

/*
 * The Structure for the Basic Art Piece
 * Members: its ID, Type, Name, Artist Name, Price, and a pointer to the Art Piece with the next highest ID#
 * 	art_pieces and tail are used to manipulate the linked list data struture of all Art Pieces
 */
struct art_piece{
	struct art_piece *next;

	int id;
	char* art_type;
	char* art_name;
	char* artist_name;
	int price;	
} *art_pieces, *tail;

FILE* out; //File that will be printed to if specified

/* 
 * Copy String: similar to strcpy, but capitalizes every letter
 * Params: String to be copied, and max size of the copied string;
 * Return: Pointer to string allocated in the heap
 */
char* copyArtType(char* string, int size){
	char* output = malloc(size*sizeof(char));
	char* temp = output;
	for (int i=0; i<=size; i++){
		*temp = toupper(*string);
		temp++;
		if (*string == '\0'){
			return output;
		}
		string++;
	}
	if(out)
		fprintf(out, "FAILED TO PARSE FILE\n");
	else
		printf("FAILED TO PARSE FILE\n");
	exit(3);
}

/* 
 * Copy String: similar to strcpy, but capitalizes every letter
 * Params: String to be copied, and max size of the copied string;
 * Return: Pointer to string allocated in the heap
 */
char* copyName(char* string, int size){
	char* output = malloc(size*sizeof(char));
	char* temp = output;
	*temp = toupper(*string);
	temp++;
	if (*string == '\0')
		return output;
	string++;
	for (int i=0; i<size; i++){
		*temp = tolower(*string);
		temp++;
		if (*string == '\0')
			return output;
		string++;
	}
	if (out)
		fprintf(out, "FAILED TO PARSE FILE\n");
	else
		printf("FAILED TO PARSE FILE\n");
	exit(3);
}

/*
 * Concatenate [Two Strings]: similar to strcat, but we can't use that :(
 * Params: Strings to be concateted
 * Return: Pointer to new string of the concatination, with a space between
 */
char* concat(char* s1, char* s2){
	char* temp1 = s1;
	char* temp2 = s2;
	int counter;
	while(*temp1++ != '\0')
		counter++;
	while(*temp2++ != '\0')
		counter++;
	counter+= 2;
	char* output = malloc(counter * sizeof(char));
	char* temp = output;
	while(*s1 != '\0')
		*temp++ = *s1++;
	while(*s2 != '\0')
		*temp++ = *s2++;
	*temp = '\0';
	return output;
}

/*
 * Are [These Strings] Equal:  similar to strcmp, but we can't use that :(
 * Params: Strings to be compared
 * Return: 1 if contain the same chars and of the same size, 0 otherwise
 */
int areEqual(char* s1, char* s2){
	if (toupper(*s1) != toupper(*s2)) return 0;
	while(*s1 != '\0')
		if (toupper(*++s1) != toupper(*++s2))
			return 0;
	return 1;
}

int numArtPieces = 0;	// Value to track the number of Art Pieces in the data base
int budget;		// Value to keep track of money left from original budget and all purchases/sales
int collectionWorth;	// Value to keep track of sum of the prices from all art pieces

BOOLEAN allFlag		= FALSE; // Flag to keep track if -v was set
BOOLEAN idFlag		= FALSE; // Flag to keep track if -i was set
BOOLEAN typeFlag 	= FALSE; // Flag to keep track if -t was set
BOOLEAN artistNameFlag  = FALSE; // Flag to keep track if -n was set

int idArg;
char* typeArg;
char* nameArg;

/* 
 * Print Art Piece: prints the data of an art piece to either stdin or a file if it was specified (by global variable out)
 * Params: Pointer to the art piece to be printed
 * Return: void
 */
void printArtPiece(struct art_piece* app){
	if (out)
		fprintf(out, "%d %s %s %s %d\n", app->id, app->art_type, app->art_name, app->artist_name, app->price);
	else
		printf("%d %s %s %s %d\n", app->id, app->art_type, app->art_name, app->artist_name, app->price);
}

/* 
 * Print All Art Pieces: prints all the art pieces specified by the argument flags (-v for all, etc.)
 * Params: void (gets the data structure through the global art_pieces);
 * Return: void
 */
void printAllArtPieces(){
	if (allFlag){
		for (struct art_piece *cursor = art_pieces->next; cursor != tail; cursor = cursor->next){
			printArtPiece(cursor);
		}
	}
	else{
		struct art_piece** artPieces = malloc(numArtPieces*sizeof(struct art_piece*));
		struct art_piece** temp = artPieces;
		int counter = 0;
		struct art_piece* artPiece;
		for (struct art_piece *cursor = art_pieces->next; cursor != tail; cursor = cursor->next){
			
			if (idFlag){
				if (cursor->id == idArg)
					artPiece = cursor;
				else{
					artPiece = NULL;
					continue;
				}
			}

			if (typeFlag){
				if (areEqual(cursor->art_type, typeArg))
					artPiece = cursor;
				else{
					artPiece = NULL;
					continue;
				}
			}

			if (artistNameFlag){
				if (areEqual(cursor->artist_name, nameArg))
					artPiece = cursor;
				else{
					artPiece = NULL;
					continue;
				}
			}
			if (artPiece){
				*artPieces = artPiece;
				artPieces++;
				counter++;
				artPiece = NULL;
			}
		}
		if (artPiece){
			*artPieces = artPiece;
			counter++;
		}
		artPieces = temp;
		if (!counter){
			if(out)
				fprintf(out, "RECORD NOT FOUND\n");
			else
				printf("RECORD NOT FOUND\n");
			exit(6);
		}
		while (--counter >= 0)
			printArtPiece(*artPieces++);
		free(temp);
	}
	if (out)
		fprintf(out, "%d\n%d\n", budget, collectionWorth);
	else
		
		printf("%d\n%d\n", budget, collectionWorth);
}

/*
 * Method to Create an Art Piece in the context of a linked list
 * Params: an ID, Type, Name, Artist Name, and Price that describe a real-world art piece
 * Return: a pointer to an Art Piece Structure with all values initialized except next, since there's a separate function for that: insertNewArtPiece()
 */
struct art_piece* createArtPiece(int id, char* art_type, char* art_name, char* artist_name, int price){
	struct art_piece *output = malloc(sizeof(struct art_piece));
	output->id = id;
	output->art_type = copyArtType(art_type, 11);
	output->art_name = copyName(art_name, 51);
	output->artist_name = copyName(artist_name, 21);
	output->price = price;
	return output;
}

BOOLEAN empty = TRUE; //A value to track whether the linked list of art pieces is empty so different intialization can occur for art_pieces and tail

/*
 * Insert a Newly Created Art Piece (created with createArtPiece())
 * Points the new art piece's next to the art piece with the next higher ID, and points the art piece with the next lower ID to the new art piece
 * Params: pointer to the newly created art piece
 * Return: void
 */
void insertNewArtPiece(struct art_piece *app){
	if (empty){
		art_pieces = calloc(1, sizeof(struct art_piece));
		tail = calloc(1, sizeof(struct art_piece));
		art_pieces->next = app;
		app->next = tail;
		empty = FALSE;
	}
	else{
		struct art_piece *cursor = art_pieces->next;
		while((app->id > cursor->next->id) && (cursor->next != tail)){
			cursor = cursor->next;
		}
		if (cursor->id == app->id){
			if (out)
				fprintf(out, "ID NOT UNIQUE\n");
			else
				printf("ID NOT UNIQUE\n");
			exit(4);
		}
		app->next = cursor->next;
		cursor->next = app;
	}
	numArtPieces++;
}

/*
 * Updates the members of an Art Piece specified by the ID# to the other fields (i.e. price)
 * Params: id: to specify which art piece to update; art_type, art_name, artist_name, price: the new data to be held in the updated art piece
 * Return: void 
 */
void updateArtPiece(int id, char* art_type, char* art_name, char* artist_name, int price){
	if (numArtPieces){
		for (struct art_piece *cursor = art_pieces->next; cursor != tail; cursor = cursor->next){
			if (cursor->id == id){
				collectionWorth -= cursor->price;
				collectionWorth += price;
				cursor->art_type = copyArtType(art_type, 11);
				cursor->art_name = copyName(art_name, 51);
				cursor->artist_name = copyName(artist_name, 21);
				cursor->price = price;
				return;
			}
		}
	}
	if (out)
		fprintf(out, "RECORD CANNOT BE DELETED NOR UPDATED\n");
	else
		printf("RECORD CANNOT BE DELETED NOR UPDATED\n");
	exit(5);
}

/*
 * Remove an Art Piece from the Linked List specified by its ID#
 * Points the previous entry to the next entry, skipping over the removed art piece, and frees the memory allocated to it.
 * Params: ID of the Art Piece to be removed
 * Return: void
 */
void removeArtPiece(int id){
	if (numArtPieces){
		for (struct art_piece *cursor = art_pieces; cursor->next != tail; cursor = cursor->next){
			if (cursor->next->id == id){
				struct art_piece* temp = cursor->next;
				cursor->next = cursor->next->next;
				free(temp->art_type);
				free(temp->art_name);
				free(temp->artist_name);
				collectionWorth -= temp->price;
				free(temp);
				numArtPieces--;
				return;
			}
		}
	}
	if (out)
		fprintf(out, "RECORD CANNOT BE DELETED NOR UPDATED\n");
	else
		printf("RECORD CANNOT BE DELETED NOR UPDATED\n");
	exit(5);
}

/*
 * String to Integer Converter
 * Params: string to be converted
 * Return: the int read in from the string
 */
int stringToInt(char* string){
	int output = 0;
	char* c = string;
	while (isspace(*c))
		c++;
	while(*c >= '0' && *c <= '9'){
		output *= 10;
		output += *c - '0';
		c++;
	}
	return output;
}

/*
 * String Splitter: splits command arguments string into 5 strings for each argument.
 * If an argument is surrounded by quotes, all that is within the quotes is one argument.
 * Otherwise, the arguments should be sepaerted by whitespace.
 * Params: the string to be split
 * Return: Pointer to 5 pointers to 5 strings
 */
char** stringSplitter(char* string){
	if (*string == '\0'){
		if (out)
			fprintf(out, "FAILED TO PARSE FILE");
		else
			printf("FAILED TO PARSE FILE\n");
		exit(3);
	}
	char** artPiece = malloc(5*sizeof(char*));
	char** output = artPiece;
	int inputCheck = 0;
	*artPiece = string;
	artPiece++; inputCheck++;
	while (*++string != '\0'){
		if (*string == ' '){
			*string = '\0';
			while (isspace(*++string));
			if (*string == '\"'){
				*artPiece = ++string;
				artPiece++; inputCheck++;
				while (*string != '\"'){
					if (*string == '\0'){
						if (out)
							fprintf(out, "FAILED TO PARSE FILE");
						else
							printf("FAILED TO PARSE FILE\n");
						exit(3);
					}
					string++;
				}
				*string = '\0';
				while(isspace(*++string));
			}
			*artPiece = string;
			artPiece++; inputCheck++;
		}
		if (inputCheck > 5){
			if (out)
				fprintf(out, "FAILED TO PARSE FILE");
			else
				printf("FAILED TO PARSE FILE\n");
			exit(3);
		}
	}
	if (inputCheck != 5){
		if (out)
			fprintf(out, "FAILED TO PARSE FILE");
		else
			printf("FAILED TO PARSE FILE\n");
		exit(3);
	}
	return output;
}


/*
 * Buy: creates a new art piece, inserts it into the database from the arguments of BUY, and updates the budget
 * Params: argument string (art_id art_type art_name artist_name price)
 * Return: void
 */
void buy(char* argumentString){
	char** artPiece = stringSplitter(argumentString);
	int id = 		stringToInt(*artPiece);
	char* art_type =	*++artPiece;
	char* art_name =	*++artPiece;
	char* artist_name =	*++artPiece;
	int price =		stringToInt(*++artPiece);
	struct art_piece* app = createArtPiece(id, art_type, art_name, artist_name, price);
	insertNewArtPiece(app);
	budget -= price;
	collectionWorth += price;
	if (budget < 0){
		if (out)
			fprintf(out, "NOT ENOUGH MONIES\n");
		else
			printf("NOT ENOUGH MONIES\n");
		exit(7);
	}
}

/*
 * Update: updates an existing art piece from the arguments of UPDATE
 * Params: argument string (art_id art_type art_name artist_name price)
 * Return: void
 */
void update(char* argumentString){
	char** artPiece = stringSplitter(argumentString);
	int id = 		stringToInt(*artPiece);
	char* art_type =	*++artPiece;
	char* art_name =	*++artPiece;
	char* artist_name =	*++artPiece;
	int price =		stringToInt(*++artPiece);
	updateArtPiece(id, art_type, art_name, artist_name, price);
}

/*
 * Sell: removes the art piece specified by its id from the database via the arguments of SELL, and updates the budget
 * Params: argument string (art_id price)
 * Return: void
 */
void sell(char* argumentString){
	while (isspace(*argumentString))
		argumentString++;
	char* idString = argumentString;
	while (!isspace(*++argumentString)){
		if (*argumentString == '\0'){
			if (out)
				fprintf(out, "FAILED TO PARSE FILE");
			else
				printf("FAILED TO PARSE FILE\n");
			exit(3);
		}
	}
	*argumentString = '\0';
	while (isspace(*++argumentString));
	char* priceString = argumentString;
	int id = 	stringToInt(idString);
	removeArtPiece(id);
	int price =	stringToInt(priceString);
	budget += price;
}


int main(int argc, char** argv) {
	collectionWorth = 0;
	if (argc < 2){
		printf("NO QUERY PROVIDED\n");
		exit(1);
	}
	FILE* input = fopen(*(++argv), "r");
	argc--;
	if (!input){
		printf("FAILED TO PARSE FILE\n");
		exit(3);
	}
	budget = -1;
	while (--argc > 0){
		char* arg = *++argv;
		if (*arg == '-'){
			switch (*++arg){
				case 'b':
					if (*++arg != '\0'){
						if (out)
						       fprintf(out, "OTHER ERROR\n");
						else
							printf("OTHER ERROR\n");
						exit(8);
					}
					budget = stringToInt(*++argv);
					argc--;
					break;
				case 'v':
					if (*++arg != '\0'){
						if (out)
						       fprintf(out, "OTHER ERROR\n");
						else
							printf("OTHER ERROR\n");
						exit(8);
					}
					allFlag = TRUE;
					break;
				case 'i':
					if (*++arg != '\0'){
						if (out)
						       fprintf(out, "OTHER ERROR\n");
						else
							printf("OTHER ERROR\n");
						exit(8);
					}
					idFlag = TRUE;
					idArg = stringToInt(*++argv);
					argc--;
					break;
				case 't':
					if (*++arg != '\0'){
						if (out)
						       fprintf(out, "OTHER ERROR\n");
						else
							printf("OTHER ERROR\n");
						exit(8);
					}
					typeFlag = TRUE;
					typeArg = *++argv;
					argc--;
					break;
				case 'n':
					if (*++arg != '\0'){
						if (out)
						       fprintf(out, "OTHER ERROR\n");
						else
							printf("OTHER ERROR\n");
						exit(8);
					}
					artistNameFlag = TRUE;
					nameArg = *++argv;
					argc--;
					break;
				case 'o':
					if (*++arg != '\0'){
						if (out)
						       fprintf(out, "OTHER ERROR\n");
						else
							printf("OTHER ERROR\n");
						exit(8);
					}
					argv++;
					argc--;
					out = fopen(*argv, "r");
					if (out){
						char answer;
						while(answer != 'y'){
							printf("FILE EXISTS. Overwrite File? (y/n)\n");
							scanf("%c", &answer);
							switch(tolower(answer)){
								case 'y':
									break;
								case 'n':
									printf("FILE EXISTS\n");
									exit(2);
									break;
							}
						}
						fclose(out);
					}
					out = fopen(*argv, "w");
					if (!out){
						printf("FAILED TO PARSE FILE\n");
						exit(3);
					}
					break;
				default:
					if (out)
						fprintf(out, "OTHER ERROR\n");
					else
						printf("OTHER ERROR\n");
					exit(8);
					break;
			}
		}
		else{
			printf("OTHER ERROR\n");
			exit(8);
		}
	}
	if (budget < -1){
		if (out)
			fprintf(out, "OTHER ERROR\n");
		else
			printf("OTHER ERROR\n");
		exit(8);
	}
	if (allFlag && (idFlag || typeFlag || artistNameFlag)){
		if (out)
			fprintf(out, "OTHER ERROR\n");
		else
			printf("OTHER ERROR\n");
		exit(8);
	}
	if (!allFlag && !idFlag && !typeFlag && !artistNameFlag){
		if (out)
			fprintf(out, "NO QUERY PROVIDED\n");
		else
			printf("NO QUERY PROVIDED\n");
		exit(1);
	}
	char* commandLine = malloc(256*sizeof(char));
	while(fgets(commandLine, 256, input) != NULL){
		switch(*commandLine){
			case 'B':
				if (*++commandLine != 'U' || *++commandLine != 'Y'){
					printf("FAILED TO PARSE FILE\n");
					exit(3);
				}
				while (isspace(*++commandLine));
				buy(commandLine);
				break;
			case 'U':
				if (*++commandLine != 'P' || *++commandLine != 'D' || *++commandLine != 'A' || *++commandLine != 'T' || *++commandLine != 'E'){
					printf("FAILED TO PARSE FILE\n");
					exit(3);
				}
				while (isspace(*++commandLine));
				update(commandLine);
				break;
			case 'S':
				if (*++commandLine != 'E' || *++commandLine != 'L' || *++commandLine != 'L'){
					printf("FAILED TO PARSE FILE\n");
					exit(3);
				}
				while (isspace(*++commandLine));
				sell(commandLine);
				break;
			default:
				printf("FAILED TO PARSE FILE\n");
				exit(3);
		}
	}
	printAllArtPieces();
	fclose(input);
	if (out){
		fclose(out);
	}
	return 0;
}

