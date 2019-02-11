#include <stdio.h>

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

