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
  // Print board state
	std::cout << std::endl << "Current Board State\n";
	std::cout << "1 2 3 4 5 6 7\n";
	for( i = 0; i<ROWMAX; i++){
		for( j = 0; j<COLMAX; j++){
		
			std::cout << board[i][j] << " ";
		}
	std::cout << std::endl;
  }
	//int i, j;
  std::cerr << "WIN1" << std::endl;

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
      std::cerr << "WIN2" << std::endl;
			if( checkRightDiagonal( board, i, j ) ){
				return true;
			}
      std::cerr << "WIN2.1" << std::endl;
		}
	}
std::cerr << "WIN3" << std::endl;
return false;
}
