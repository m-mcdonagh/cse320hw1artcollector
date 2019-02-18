#include <stdio.h>
#include <stdlib.h>
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
		} 
		app->next = cursor->next;
		cursor->next = app;
	}
}

int budget; // Maximum value for the sum of the price for all Art Pieces in the Linked List Data Structure

int main(int argc, char** argv) {
	/*
	* 	* Dummy values
	*/
	int id = 1;
	char* art_type = "Painting";
	char* art_name = "Girl on the ball";
	char* artist_name = "Picasso";
	int price = 100;

	/*
    	* This formatting for the string
    	* that you are expected to follow
    	*/
	
	printf("%d %s %s %s %d\n", id, art_type, art_name, artist_name, price);

	return 0;
}

