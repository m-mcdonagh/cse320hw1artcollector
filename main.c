#include <stdio.h>
#include <stdlib.h>
#define BOOLEAN char
#define TRUE 1
#define FALSE 0

struct art_piece{
	struct art_piece *next;

	int id;
	char* art_type;
	char* art_name;
	char* artist_name;
	int price;	
};

struct art_piece *head, *tail;

struct art_piece* createArtPiece(int id, char* art_type, char* art_name, char* artist_name, int price){
	struct art_piece *output = malloc(sizeof(struct art_piece));
	output->id = id;
	output->art_type = art_type;
	output->art_name = art_name;
	output->artist_name = artist_name;
	output->price = price;
	return output;
}

BOOLEAN empty = TRUE;

void insertNewArtPiece(struct art_piece *app){
	if (empty){
		head = app;
		tail = app;
		(*app).next = tail;
		empty = FALSE;
	}
	else{
		struct art_piece *cursor = head;
		while(((*app).id > (*(*cursor).next).id) && (cursor != tail)){
			cursor = (*cursor).next;
		}
		(*app).next = (*cursor).next;
		(*cursor).next = app;
	}
}

int main(int argc, char** argv) {
      /*
       *   * Dummy values
       *     */
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

