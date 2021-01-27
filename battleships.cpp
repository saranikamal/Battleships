
/*
************************************************
 ***** Created by Sara Nikamalfard
************************************************
 */

#include<iostream>
#include<iomanip>
#include<stdio.h>
using namespace std;

#define BOARD_WIDTH  8
#define BOARD_HEIGHT 8



int mainMenuDisplay()
{		
                                           
	char userInput;
	cout<<"\x1B[2J\x1B[H"<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"Welcome to Battleships!\n"<<"-----------------------------"<<endl;
	cout<<"********* Main Menu *********\n"<<endl;
	cout<<setw(5)<<"1. Start Game"<<endl;
	cout<<setw(5)<<"2. Quit"<<"\n"<<endl;
	cout<<"Enter menu selection(1-2): ";
	
	while(userInput != '1' && userInput != '2')
	{
		
		cin>>userInput;
		if(userInput == '1' || userInput=='2')
		break;
		else
	   	cout<<"Invalid entry...Please try again: ";
	   
	}
	return userInput;
}

void addShipsMenu()
{
	cout<<"-----------------------------------------------\n"<<"        Add  Ship\n";
	cout<<"------------------------------------------------\n";
	cout<<"	No  Name        Square\n"<<"-----------------------------------------------"<<endl;
	
	for(int i=1 ; i<=5 ;)
	{cout<<"	"<<"1";
	  switch(i)
	  {
	  case 1:
	    cout<<"  Carrier"<<"        5"<<endl;
	    break;
	   case 2:
	    cout<<"  Battleship"<<"     4"<<endl;
	    break;
	   case 3:
	    cout<<"  Cruiser"<<"        3"<<endl;
	    break;
	   case 4:
	    cout<<"  Submarine"<<"      3"<<endl; 
	    break;
	   case 5:
	    cout<<"  Destroyer"<<"      2"<<endl; 
	    break;
	  }
	  
	  i++;
	}
	
	cout<<"------------------------------------------------\n";

}

void pressEnterToContinue(){
cout<<"Press enter to continue!";
cin.clear(); 
cin.ignore(50,'\n'); 
cin.get(); 
}

class Board
{
	public:
	
void getCoordinates(char &xCoordinate, char &yCoordinate){

	cout<<"**Enter the X coordinate (A-H): ";
	      cin>>xCoordinate;
	      
	      while((xCoordinate > 72 || xCoordinate < 65))   // only capital letter is accepted
	      {
	      	cout<<"Invalid entry...Please try again:";
	      	cin>>xCoordinate;				          
	      }
	      
	      cout<<"**Enter the Y coordinate: ";
	      cin>>yCoordinate;
	      while(yCoordinate > 56 || yCoordinate < 49)                   
	      {
	      	cout<<"Invalid entry...please try again: ";
	      	cin>>yCoordinate;
	      }
	      
}

void getDirection(char &direction)
{
	cout<<"**Enter the direction (N/E/S/W):";
	cin>>direction;
	while(!(direction == 78 || direction== 83 || direction==69 || direction== 87))  // only capital letter is accepted
	{
		cout<<"Invalid entry...Please try again: ";
		cin>>direction;
	}
}



/* cheking if a ship with it's size and coordinates is not out of board*/
bool checkNotOutOfBoard(char &xCoordinate , char &yCoordinate , char &direction , int size)
{
	bool result = true;
	
	if(direction == 'N')
	{
		if(((yCoordinate-49)-size) < 0)
		result = false;
	}
	
	else if(direction == 'S')
	{
		if(((yCoordinate-49)+size) > 7)
		result = false;
	}	
		
	else if(direction =='E')
	{
		if(((xCoordinate-65)+size) > 7)
		result = false;
	}
	
	else if(direction == 'W')
	{
		if(((xCoordinate-65) - size) < 0)
		result = false;
	}
	
	return result;	
}

/* if another ship exist at this given coordinates -- checks square status*/
bool shipExists(char **board, int size, char &xCoordinate, char &yCoordinate , char &direction)
{
	bool result = true;
	if(direction == 'S')
	{
	  for(int i=0;i<size;i++)
	  {
	    if(board[(yCoordinate-49)+i][xCoordinate-65] == 'S')
	    result = false;
	  }
	}
	
	else if(direction == 'N')
	{
	 for(int i=0;i<size;i++)
	  {
	    if(board[(yCoordinate-49)-i][xCoordinate-65] == 'S')
	    result = false;
	  }
	}
	
	else if(direction == 'E')
	{
	 for(int i=0;i<size;i++)
	  {
	    if(board[yCoordinate-49][(xCoordinate-65)+i] == 'S')
	    result = false;
	  }
	}
	
	else if(direction == 'W')
	{
	 for(int i=0;i<size;i++)
	  {
	    if(board[yCoordinate-49][(xCoordinate-65)-i] == 'S')
	    result = false;
	  }
	}

	else if(direction != 'S' || direction != 'N' || direction != 'W' || direction != 'E')
	{result = false;}
	return result;
}


void addShips(char **board , int size)                   /* Adding ships to the board*/
{
	char xCoordinate , yCoordinate, direction;
	ADDSHIP:
	getCoordinates(xCoordinate , yCoordinate);
	getDirection(direction);
	cout<<"\n";
	
	switch(direction)
	{
	  case 'S':
	  if((checkNotOutOfBoard(xCoordinate,yCoordinate,direction,size)== 1) 
	     && (shipExists(board, size, xCoordinate,yCoordinate ,direction)==1))
	 { 
	   for( int i=0; i<8; i++)
	     {
	  	for(int j=0; j<8; j++)
	  	{
	  	   for(int k=0 ; k<size;k++)
	  	   board[(yCoordinate-49) + k][xCoordinate-65] = 'S';	  	
	  	}
	     }
	 } 
	 else 
	 {cout<<"Ship cannot be placed here , please try again:"<<endl; goto ADDSHIP;}
	  break;
	  
	  case 'N':
	  if((checkNotOutOfBoard(xCoordinate,yCoordinate,direction,size)== 1)
	     && (shipExists(board, size, xCoordinate,yCoordinate ,direction)==1))
	  {
	   for( int i=0; i<8; i++)
	    {
	  	for(int j=0; j<8; j++)
	  	{	
	  	    for(int k=0 ; k<size;k++)
	  	    board[(yCoordinate-49) - k][xCoordinate-65] = 'S';    	
	  	}
	    }
	 } 
	 else 
	 {cout<<"Ship cannot be placed here, please try again:"<<endl; goto ADDSHIP;}
	  break;
	  
	  case 'W':
	  if((checkNotOutOfBoard(xCoordinate,yCoordinate,direction,size) == 1)
	      && (shipExists(board, size, xCoordinate,yCoordinate ,direction)==1))
	  {
	    for( int i=0; i<8; i++)
	    {
	  	for(int j=0; j<8; j++)
	  	{
	  	    for(int k=0 ; k<size;k++)
	  	    board[yCoordinate-49][(xCoordinate-65) - k] = 'S';		
	  	}
      	   }
	  } 
	  else 
	  {cout<<"Ship cannot be placed here, please try again:"<<endl; goto ADDSHIP;}
	  break;
	  
	  case 'E':
	  if((checkNotOutOfBoard(xCoordinate,yCoordinate,direction,size)== 1)
	     && (shipExists(board, size, xCoordinate,yCoordinate ,direction)==1))
	  {
	    for( int i=0; i<8; i++)
	     {
	  	for(int j=0; j<8; j++)
	  	{
	  	     for(int k=0 ; k<size;k++)
	  	     board[yCoordinate-49][(xCoordinate-65) + k] = 'S';	
	  	}
	  }
	 }
	  else 
	 {cout<<"Ship cannot be placed here, please try again:"<<endl; goto ADDSHIP;}
	  break;

	default:
	cout<<"Ship cannot be placed here, please try again:"<<endl; goto ADDSHIP;
	}	
}	
	
char** setGridToZero()				/*To reset the board to 0 (empty)*/
   {
    char **board = new char *[8];
    for(int i=0 ; i<8;i++)
    board[i] = new char[8];   
	for(int i=0;i<8;i++)
	{
	   for(int j=0 ; j<8; j++)
	   { board[i][j] = '0';}
	} 
	return board;
  }

  
void nowGridIs(char **grid)             /* method to show board status at each stage*/     
{
    cout<<setw(5);
    cout<<"   A--B--C--D--E--F--G--H"<<"\n-------------------------"<<endl;
    for(int i=0;i<8;i++)
    {
           cout<<i+1<<"| ";		
	   for(int j=0;j<8;j++)
	   cout<<grid[i][j]<<"  ";
	   cout<<"\n-------------------------"<<endl;
    }
}


char** setFiringBoardtoEmpty()
{
	char **firingBoard = new char *[8];
    for(int i=0 ; i<8;i++)
    firingBoard[i] = new char[8];   
	for(int i=0;i<8;i++)
	{
	   for(int j=0 ; j<8; j++)
	   { firingBoard[i][j] = ' ';}
	} 
	return firingBoard;
}

void nowFrinigBoardIs(char** firingBoard)
{
    cout<<setw(5);
    cout<<"   A--B--C--D--E--F--G--H"<<"\n-------------------------"<<endl;
    for(int i=0;i<8;i++)
    {
       cout<<i+1<<"| ";		
	   for(int j=0;j<8;j++)
	   cout<<firingBoard[i][j]<<"  ";
	   cout<<"\n-------------------------"<<endl;
    }
}

bool shipLeft(char **grid)
{
	bool result = false;
	for(int i=0 ; i<BOARD_HEIGHT;i++)
	{
		for(int j=0 ; j<BOARD_WIDTH; j++)
		{
			if(grid[i][j] == 'S')
			{result = true;}
		}
	}
	
	return result;
}

bool fireAtSquare(char **board , char** firingBoard , char &xCoordinate , char &yCoordinate)
{
  bool result;
  GETCOORDINATES:
  getCoordinates(xCoordinate , yCoordinate);
  if(board[yCoordinate-49][xCoordinate-65] == 'S')
  {cout<<"It's a Hit"<<"\n"<<endl;
   board[yCoordinate - 49][xCoordinate-65] = 'H';
   firingBoard[yCoordinate-49][xCoordinate-65] = 'H';
   result = true;
  }

  else if(board[yCoordinate-49][xCoordinate-65] == '0')
  {cout<<"It's a Miss"<<"\n"<<endl;
   board[yCoordinate - 49][xCoordinate-65] = 'M';
   firingBoard[yCoordinate-49][xCoordinate-65]='M';
   result = false;
  }

  else if(board[yCoordinate-49][xCoordinate-65] == 'H' || board[yCoordinate-49][xCoordinate-65] == 'M')
  { cout<<"\nYou have already entered these coordinates, please try again:\n"<<endl;
    goto GETCOORDINATES;
  }
  return result;
}

};

class Player
{
	private:
	string playerName;
	public:
	Board board;

void setPlayerName(string playerName)
{
  this->playerName = playerName;
}

string getPlayerName()
{
    cin>>playerName;
    return playerName; 
}

char** resetBoard()
{ return board.setGridToZero();}

void displayBoardAtThisStage(char **grid)
{board.nowGridIs(grid);}

char** resetFiringBoard()
{return board.setFiringBoardtoEmpty();}

void displayFiringBoardAtThisStage(char** firingBoard)
{board.nowFrinigBoardIs(firingBoard);}

void fire(char **grid , char** firingBoard , char &xCoordinate , char &yCoordinate)
{board.fireAtSquare(grid, firingBoard , xCoordinate , yCoordinate);} 

void placeShip(char **grid , int size)
{board.addShips(grid , size);} 

bool checkWin(char** grid , char &xCoordinate , char  &yCoordinate)
{
	bool result = true;
    
	if(board.shipLeft(grid) == 1)
	{
		result = false;	
	}
	   return result;
} 

};


int main()
{	
	int turn = 1;
	int menuSelection = mainMenuDisplay();
	char xCoordinate , yCoordinate , direction;

	Player playerOne;
	Player playerTwo;

	char** playerOneBoard = playerOne.resetBoard();
	char** playerTwoBoard = playerTwo.resetBoard();
	
	switch(menuSelection)
	{
	   case '2': 
	      cout<<"Goodbye!!!\n";
	      return 0;
	    
	   case '1':
	    mainMenuDisplay();
		cout<<"\nPlayer 1 , please enter your name: ";
		string playerOneName= playerOne.getPlayerName();
	   	playerOne.setPlayerName(playerOneName);
		cout<<"\nPlayer 2 , please enter your name: ";
		string playerTwoName = playerTwo.getPlayerName();
		playerTwo.setPlayerName(playerTwoName);

		cout<<"\n"<<playerOneName<<" please add a Carrier,size: 5\n"<<endl;
		playerOne.placeShip( playerOneBoard , 5);

		cout<<"\n"<<playerOneName<<" please add a Battleship,size: 4\n"<<endl;
		playerOne.placeShip( playerOneBoard , 4);

		cout<<"\n"<<playerOneName<<" please add a Cruiser,size: 3\n"<<endl;
		playerOne.placeShip( playerOneBoard , 3);

		cout<<"\n"<<playerOneName<<" please add a Submarine,size: 3\n"<<endl;
		playerOne.placeShip( playerOneBoard , 3);

		cout<<"\n"<<playerOneName<<" please add a Destroyer,size: 2\n"<<endl;
		playerOne.placeShip( playerOneBoard , 2);
		playerOne.displayBoardAtThisStage(playerOneBoard);
		cout<<"All ships are added!"<<endl;
		pressEnterToContinue();
		cout<<"\x1B[2J\x1B[H"<<endl;
		addShipsMenu();


		cout<<"\n"<<playerTwoName<<" please add Carrier,size: 5\n"<<endl;
		playerTwo.placeShip(playerTwoBoard , 5);
		
		cout<<"\n"<<playerTwoName<<" please add Battleship,size: 4\n"<<endl;
		playerTwo.placeShip(playerTwoBoard , 4);
		
		cout<<"\n"<<playerTwoName<<" please add Cruiser,size: 3\n"<<endl;
		playerTwo.placeShip(playerTwoBoard , 3);
		
		cout<<"\n"<<playerTwoName<<" please add Submarine,size: 3\n"<<endl;
		playerTwo.placeShip(playerTwoBoard , 3);
		
		cout<<"\n"<<playerTwoName<<" please add Destroyer,size: 2\n"<<endl;
		playerTwo.placeShip(playerTwoBoard , 2);
		playerTwo.displayBoardAtThisStage(playerTwoBoard);
		cout<<"All ships are added!"<<endl;
		pressEnterToContinue();

		char** playerOneFiringBoard =  playerOne.resetFiringBoard();
		char** playerTwoFiringBoard = playerTwo.resetFiringBoard();

		char** attackingPlayerFiringBoard = playerOneFiringBoard;
		char** defendingPlayerFiringBoard = playerTwoFiringBoard;
		

		Player* attackingPlayer = &playerOne;
		Player* defendingPlayer = &playerTwo;

		char** attackingPlayerBoard = playerOneBoard;
		char** defendingPlayerBoard = playerTwoBoard;

		string attackingPlayerName = playerOneName;
		string defendeingPlayerName = playerTwoName;


		while(attackingPlayer->checkWin(defendingPlayerBoard ,xCoordinate ,yCoordinate) != 1)
		{
			cout<<"\x1B[2J\x1B[H"<<endl;		
			cout<<"Turn: "<<turn<<endl;
			cout<<attackingPlayerName<<", enter coordinates to fire "<<endl;
			attackingPlayer->displayFiringBoardAtThisStage(defendingPlayerFiringBoard);
			attackingPlayer->fire(defendingPlayerBoard, defendingPlayerFiringBoard,xCoordinate, yCoordinate);
			if(attackingPlayer->checkWin(defendingPlayerBoard ,xCoordinate ,yCoordinate) == 1) {break;}
			else
			{
			swap(attackingPlayer , defendingPlayer);
			swap(defendingPlayerBoard , attackingPlayerBoard);
			swap(attackingPlayerName,defendeingPlayerName);
			swap(attackingPlayerFiringBoard,defendingPlayerFiringBoard);
		    turn++;
		    pressEnterToContinue();
			}
			
		}
		cout<<attackingPlayerName<<", you won!"<<endl;
		
	}
	return 0;
}
