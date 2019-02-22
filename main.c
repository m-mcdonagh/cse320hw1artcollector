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

BOOLEAN empty = TRUE; //A value to track whether the linked list of art pieces is empty so different intialization can occur for head and tail

/*
 * Insert a Newly Created Art Piece (created with createArtPiece())
 * Points the new art piece's next to the art piece with the next higher ID, and points the art piece with the next lower ID to the new art piece
 * Params: pointer to the newly created art piece
 * Return: void
 */
void insertNewArtPiece(struct art_piece *app){
	if (empty){
		head = tail = calloc(1, sizeof(struct art_piece));
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
}

/*
 * Remove an Art Piece from the Linked List specified by its ID#
 * Points the previous entry to the next entry, skipping over the removed art piece, and frees the memory allocated to it.
 * Params: ID of the Art Piece to be removed
 * Return: void
 */
void removeArtPiece(int id){
	if (!empty){
		for (struct art_piece *cursor = head; cursor->next != tail; cursor = cursor->next){
			if (cursor->next->id == id){
				cursor->next = cursor->next->next;
				free(cursor);
				return;
			}
		}
	}
	printf("RECORD CANNOT BE DELETED NOR UPDATED\n");
	exit(5);
}

/*
 * Updates the members of an Art Piece specified by the ID# to the other fields (i.e. price)
 * Params: id: to specify which art piece to update; art_type, art_name, artist_name, price: the new data to be held in the updated art piece
 * Return: void 
 */
void updateArtPiece(int id, char* art_type, char* art_name, char* artist_name, int price){
	if (!empty){
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

BOOLEAN allFlag		= FALSE; // Flag to keep track if -v was set
BOOLEAN idFlag		= FALSE; // Flag to keep track if -i was set
BOOLEAN typeFlag 	= FALSE; // Flag to keep track if -t was set
BOOLEAN artistNameFlag  = FALSE; // Flag to keep track if -n was set

double budget; // Maximum value for the sum of the price for all Art Pieces in the Linked List Data Structure

/*
 * String to Integer Converter
 * Params: string to be converted
 * Return: the double read in from the string
 */
double stringToDouble(char* string){
	double output = 0.0;
	char* c = string;
	while(*c >= '0' && *c <= '9'){
		output *= 10;
		output += *c - '0';
		c++;
	}
	if (*c == '.'){
		int placeholder = -1;
		while (*++c != '\0')
			if (isdigit(*c))
				output += (*c - '0') * pow(10, placeholder--);
	}
	return output;
}

int main(int argc, char** argv) {

	if (argc < 2){
		printf("NO QUERY PROVIDED\n");
		exit(1);
	}
	//FILE* input = fopen(*(argv+1), "r");

	while (--argc > 0){
		char* arg = *++argv;
		if (*arg == '-'){
			switch (*++arg){
				case 'b':
					budget = stringToDouble(*++argv);
					argc--;
					printf("Budget: %f\n", budget);
					break;
				case 'v':
					allFlag = TRUE;
					break;
				case 'i':
					idFlag = TRUE;
					break;
				case 't':
					typeFlag = TRUE;
					break;
				case 'n':
					artistNameFlag = TRUE;
					break;
				default:
					printf("FAILED TO PARSE FILE");
					exit(3);
			}
		}
	}


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
	
	//fclose(input);
	return 0;
}

