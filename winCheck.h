// Jeremy Wilder
// Connect 4 win check function

#include <cstdlib>

#define COLMAX 7
#define ROWMAX 6

bool checkHorizontalNeighbors( char** &board, int i, int j){

		// check only to the right for 4 in a row
			// check right bound
	if( ((j+3) > COLMAX) ){
		return false;
	}
	else{
		if( (board[i][j] == board[i][j+1]) && (board[i][j] == board[i][j+2])
		&& (board[i][j] == board[i][j+3]) && (board[i][j] != 'B') ){
			return true;
		}
		return false;
	}
}

bool checkVeritcalNeighbors( char** &board, int i, int j){

		// check vertically up for 4 consecutive in a column
			// check "top" bound
	if( ((i-3) < 0) ){
		return false;
	}
	else{
		if( (board[i][j] == board[i-1][j]) && (board[i][j] == board[i-2][j])
		&& (board[i][j] == board[i-3][j]) && (board[i][j] != 'B') ){
			return true;
		}
		return false;
	}
}

bool checkRightDiagonal( char** &board, int i, int j){

		// check for a diagonal of 4 to the right
			// Check right bound and "top" bound
	if( ((j+3) > COLMAX) || ((i-3) < 0) ){
		return false;
	}
	else{
		if( (board[i][j] == board[i-1][j+1]) && (board[i][j] == board[i-2][j+2])
		&& (board[i][j] == board[i-3][j+3]) && (board[i][j] != 'B') ){
			return true;
		}
	}

	return false;
}

bool checkLeftDiagonal( char** &board, int i, int j){

		// check for a diagonal of 4 to the left
			// check left bound and "top" bound
	if( ((i-3) < 0) || ( (j-3) < 0) ){
		return false;
	}
	else{
		if( (board[i][j] == board[i-1][j-1]) && (board[i][j] == board[i-2][j-2])
		&& (board[i][j] == board[i-3][j-3]) && (board[i][j] != 'B') ){
			return true;
		}
	}

	return false;
}

// Checks the game board for a winner
bool winCheck( char** &board ){

  int i, j;
  

	for( i=ROWMAX-1; i>=0; i--){
		for( j=0; j<COLMAX; j++){
			if( checkHorizontalNeighbors( board, i, j ) ){
				return true;
			}
			if( checkVeritcalNeighbors( board, i, j) ){
				return true;
			}
			if( checkRightDiagonal( board, i, j ) ){
				return true;
			}
			if( checkRightDiagonal( board, i, j ) ){
				return true;
			}
		}
	}
return false;
}
