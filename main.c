#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define BOOLEAN char
#define TRUE 1
#define FALSE 0

/*
 * The Structure for the Basic Art Piece
 * Members: its ID, Type, Name, Artist Name, Price, and a pointer to the Art Piece with the next highest ID#
 * 	head and tail are used to manipulate the linked list data struture of all Art Pieces
 */
struct art_piece{
	struct art_piece *next;

	int id;
	char* art_type;
	char* art_name;
	char* artist_name;
	int price;	
} *head, *tail;

/*
 * Method to Create an Art Piece in the context of a linked list
 * Params: an ID, Type, Name, Artist Name, and Price that describe a real-world art piece
 * Return: a pointer to an Art Piece Structure with all values initialized except next, since there's a separate function for that: insertNewArtPiece()
 */
struct art_piece* createArtPiece(int id, char* art_type, char* art_name, char* artist_name, int price){
	struct art_piece *output = malloc(sizeof(struct art_piece));
	output->id = id;
	output->art_type = art_type;
	output->art_name = art_name;
	output->artist_name = artist_name;
	output->price = price;
	return output;
}

int areEqual(char* s1, char* s2){
	if (*s1 != *s2) return 0;
	while(*s1 != '\0')
		if (*++s1 != *++s2)
			return 0;
	return 1;
}

int numArtPieces = 0; //A value to track the number of Art Pieces in the data base

BOOLEAN allFlag		= FALSE; // Flag to keep track if -v was set
BOOLEAN idFlag		= FALSE; // Flag to keep track if -i was set
BOOLEAN typeFlag 	= FALSE; // Flag to keep track if -t was set
BOOLEAN artistNameFlag  = FALSE; // Flag to keep track if -n was set

int idArg;
char* typeArg;
char* nameArg;
FILE* out;

void printArtPiece(struct art_piece* app){
	if (out)
		fprintf(out, "%d %s %s %s %d\n", app->id, app->art_type, app->art_name, app->artist_name, app->price);
	else
		printf("%d %s %s %s %d\n", app->id, app->art_type, app->art_name, app->artist_name, app->price);
}

void printAllArtPieces(){
	if (allFlag){
		for (struct art_piece *cursor = head->next; cursor != tail; cursor = cursor->next){
			printArtPiece(cursor);
		}
	}
	else{
		struct art_piece** artPieces = malloc(numArtPieces*sizeof(struct art_piece*));
		struct art_piece** temp = artPieces;
		int counter;
		struct art_piece* artPiece;
		for (struct art_piece *cursor = head->next; cursor != tail; cursor = cursor->next){
			
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
			}
		}
		artPieces = temp;
		while (--counter > 0)
			printArtPiece(*artPieces++);
	}
}

BOOLEAN empty = TRUE; //A value to track whether the linked list of art pieces is empty so different intialization can occur for head and tail

/*
 * Insert a Newly Created Art Piece (created with createArtPiece())
 * Points the new art piece's next to the art piece with the next higher ID, and points the art piece with the next lower ID to the new art piece
 * Params: pointer to the newly created art piece
 * Return: void
 */
void insertNewArtPiece(struct art_piece *app){
	if (empty){
		head = calloc(1, sizeof(struct art_piece));
		tail = calloc(1, sizeof(struct art_piece));
		head->next = app;
		app->next = tail;
		empty = FALSE;
	}
	else{
		struct art_piece *cursor = head->next;
		while((app->id > cursor->next->id) && (cursor->next != tail)){
			cursor = cursor->next;
		}
		if (cursor->id == app->id){
			printf("ID NOT UNIQUE\n");
			exit(4);
		}
		app->next = cursor->next;
		cursor->next = app;
	}
	numArtPieces++;
	//printf("INSERTED: ");
	//printArtPiece(app);
}

/*
 * Updates the members of an Art Piece specified by the ID# to the other fields (i.e. price)
 * Params: id: to specify which art piece to update; art_type, art_name, artist_name, price: the new data to be held in the updated art piece
 * Return: void 
 */
void updateArtPiece(int id, char* art_type, char* art_name, char* artist_name, int price){
	if (numArtPieces){
		for (struct art_piece *cursor = head->next; cursor != tail; cursor = cursor->next){
			if (cursor->id == id){
				cursor->art_type = art_type;
				cursor->art_name = art_name;
				cursor->artist_name = artist_name;
				cursor->price = price;
				return;
			}
		}
	}
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
		for (struct art_piece *cursor = head; cursor->next != tail; cursor = cursor->next){
			if (cursor->next->id == id){
				cursor->next = cursor->next->next;
				free(cursor);
				numArtPieces--;
				return;
			}
		}
	}
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
			printf("FAILED TO PARSE FILE\n");
			exit(3);
		}
	}
	if (inputCheck != 5){
		printf("FAILED TO PARSE FILE\n");
		exit(3);
	}
	return output;
}

int originalBudget; 	// Maximum value for the sum of the price for all Art Pieces in the Linked List Data Structure
int budget;		// Value to keep track of money left from original budget and all purchases/sales

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
	int price =		stringToInt(*artPiece);
	updateArtPiece(id, art_type, art_name, artist_name, price);
}

/*
 * Sell: removes the art piece specified by its id from the database via the arguments of SELL, and updates the budget
 * Params: argument string (art_id price)
 * Return: void
 */
void sell(char* argumentString){
	char* idString = argumentString;
	while (isspace(*argumentString))
		argumentString++;
	while (isspace(*++argumentString)){
		if (*argumentString == '\0'){
			printf("FAILED TO PARSE FILE\n");
			exit(3);
		}
	}
	*argumentString = '\0';
	char* priceString = ++argumentString;
	int id = 	stringToInt(idString);
	removeArtPiece(id);
	int price =	stringToInt(priceString);
	budget += price;
}


int main(int argc, char** argv) {
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

	while (--argc > 0){
		char* arg = *++argv;
		if (*arg == '-'){
			switch (*++arg){
				case 'b':
					originalBudget = stringToInt(*++argv);
					budget = originalBudget;
					argc--;
					break;
				case 'v':
					allFlag = TRUE;
					break;
				case 'i':
					idFlag = TRUE;
					idArg = stringToInt(*++argv);
					argc--;
					break;
				case 't':
					typeFlag = TRUE;
					typeArg = *++argv;
					argc--;
					break;
				case 'n':
					artistNameFlag = TRUE;
					nameArg = *++argv;
					argc--;
					break;
				case 'o':
					out = fopen(*++argv, "r");
					argc--;
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
					}
					out = fopen(*argv, "w");
					break;
				default:
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
	if (allFlag && (idFlag || typeFlag || artistNameFlag)){
		printf("OTHER ERROR\n");
		exit(8);
	}
	
	char* commandLine = malloc(256*sizeof(char));
	while(fgets(commandLine, 256, input) != NULL){
		printf("%s\n", commandLine);
		switch(*commandLine){
			case 'B':
				if (*++commandLine != 'U' || *++commandLine != 'Y'){
					printf("FAILED TO PARSE FILE\n");
					exit(3);
				}
				commandLine++;
				printf("%s\n\n", commandLine);
				buy(++commandLine);
				break;
			case 'U':
				if (*++commandLine != 'P' || *++commandLine != 'D' || *++commandLine != 'A' || *++commandLine != 'T' || *++commandLine != 'E'){
					printf("FAILED TO PARSE FILE\n");
					exit(3);
				}
				commandLine++;
				printf("%s\n\n", commandLine);
				update(++commandLine);
				break;
			case 'S':
				if (*++commandLine != 'E' || *++commandLine != 'L' || *++commandLine != 'L'){
					printf("FAILED TO PARSE FILE\n");
					exit(3);
				}
				commandLine++;
				printf("%s\n\n", commandLine);
				sell(++commandLine);
				break;
			default:
				printf("FAILED TO PARSE FILE\n");
				exit(3);
		}
	}
	printAllArtPieces();
	/*
	* 	* Dummy values
	*
	int id = 1;
	char* art_type = "Painting";
	char* art_name = "Girl on the ball";
	char* artist_name = "Picasso";
	int price = 100;*/

	/*
    	* This formatting for the string
    	* that you are expected to follow
    	* "%d %s %s %s %d\n", id, art_type, art_name, artist_name, price
	*/
	
	fclose(input);
	if (out){
		fclose(out);
	}
	return 0;
}

