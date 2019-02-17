#include <stdio.h>

typedef struct ArtPiece {
	ArtPiece *prev;
	ArtPiece *next;

	int id;
	char* art_type;
	char* art_name;
	char* artist_name;
	int price;	
} *head, *tail;

ArtPiece *createArtPiece(int id, char* art_type, char* art_name, char* artist_name, int price){
	ArtPiece output;
	output.id = id;
	output.art_type = art_type;
	output.art_name = art_name;
	output.artist_name = artist_name;
	output.price = price;
	return *output;
}

bool empty = true;

void insertNewArtPiece(ArtPiece *app){
	if (empty){
		head = app;
		tail = app;
		(&app).prev = head;
		(&app).next = tail;
		empty = false;
	}
	else{
		ArtPiece *cursor = head;
		while(((&app).id > (&(&cursor).next).id) && (cursor != tail)){
			cursor = (&cursor).next;
		}
		(&app).prev = cursor;
		(&app).next = (&cursor).next;
		(&cursor).next = app;
		(&(&app).next).prev = app;
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

