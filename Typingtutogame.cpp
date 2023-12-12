#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

#define SCREEN_WIDTH 110
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

class TypingTutor 
{
    private:
    HANDLE console;
    COORD CursorPosition;
    char keys[10];
    int keyPos[10][10];
    int score;
    string playerName;
    char i;
    string highScorePlayer;
    int highScore;
    
    public:
    TypingTutor() 
	{
        console = GetStdHandle(STD_OUTPUT_HANDLE);
        CursorPosition = {0, 0};
        score = 0;
        highScore = 0;
        playerName = "";
        
    }
    void gameOver() 
	{
       
        system("cls");
	cout<<endl;
	cout<<"\t";
	cout<<"\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
    }
    
    

    void setCursorPosition(int x, int y) 
	{
        CursorPosition.X = x;
        CursorPosition.Y = y;
        SetConsoleCursorPosition(console, CursorPosition);
    }

    void setCursor(bool visible, DWORD size) 
	{
        if (size == 0)
            size = 20;

        CONSOLE_CURSOR_INFO lpCursor;
        lpCursor.bVisible = visible;
        lpCursor.dwSize = size;
        SetConsoleCursorInfo(console, &lpCursor);
    }
    void drawBorder()
	{
	  
	for(int i=0; i<SCREEN_WIDTH; i++)
	{ 
		setCursorPosition(i,SCREEN_HEIGHT); cout<<"=";
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++)
	{
		setCursorPosition(0,i); cout<<"=";
		setCursorPosition(SCREEN_WIDTH,i); cout<<"=";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++)
	{
		setCursorPosition(WIN_WIDTH,i); cout<<"=";
	}
	
    }

    void genAlphabet(int ind)
	{
	keys[ind] = 65+rand()%26;
	keyPos[ind][0] = 3+rand()%(WIN_WIDTH-3);
	keyPos[ind][1] = 1;
    }
   
    void drawAlphabet(int ind)
	{
	if( keyPos[ind][0] != 0){
		setCursorPosition(keyPos[ind][0], keyPos[ind][1]);   cout<<keys[ind];  
	}
	 
    }
    
    void eraseAlphabet(int ind){
    	
	if( keyPos[ind][0] != 0 ){
		setCursorPosition(keyPos[ind][0], keyPos[ind][1]);   cout<<" ";  
	}
	
    }
    
    void resetAlphabet(int ind){
	eraseAlphabet(ind);
	genAlphabet(ind);
    }
    void setPlayerName(const string& name) {
        playerName = name;
    }
	
   void updateScore() {
        setCursorPosition(WIN_WIDTH + 7, 5);
        cout << "Player: " << playerName<< " | Score: " << score << endl; 
    }
      void displayInstructions() 
	{
       
    system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n On Left side you will see falling characters ";
	cout<<"\n You have to keep them away from touching floor";
	cout<<"\n Press respective key from keyboard to keep playing";
	cout<<"\n\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
	
    }
     void displayHighScore() {
        system("cls");
        cout << "High Score" << endl;
        cout << "-----------------" << endl<<endl;
        cout << "Player: " << highScorePlayer << " | High Score: " << highScore << endl << endl;
        cout << "You: " << playerName << " | Your Score: " << score << endl;
        cout << "\nPress any key to go back to menu.";
        getch();
    }
   void updateHighScore() {
    ifstream scoreFile("highscore.txt");
    if (scoreFile.is_open()) {
        scoreFile >> highScore;
        scoreFile >> highScorePlayer;
        scoreFile.close();
    } else {
        cout << "Unable to open the file for reading high score." << endl;
    }

    if (score > highScore) {
        highScore = score;
        highScorePlayer =playerName;

        ofstream newScoreFile("highscore.txt");
        if (newScoreFile.is_open()) {
            newScoreFile << highScore << endl;
            newScoreFile << highScorePlayer << endl;
            newScoreFile.close();
        } else {
            cout << "Unable to open the file for updating high score." << endl;
        }
    }
}


    void playGame() {
    	            
    	            
        cout << endl;
        cout << "Enter your name: ";
        cin >> playerName; 
    
                   
       score = 0;
	for(int i=0; i<10; i++){
		keyPos[i][0] = keyPos[i][1] = 1;	
	}
	
	 
	system("cls"); 
	drawBorder(); 
	updateScore();
	
	for(int i=0; i<10; i++)
		genAlphabet(i); 
	
	setCursorPosition(WIN_WIDTH + 5, 2);cout<<"Typing Tutor";
	setCursorPosition(WIN_WIDTH + 6, 4);cout<<"-------------------------------";
	setCursorPosition(WIN_WIDTH + 6, 6);cout<<"-------------------------------";
	
	setCursorPosition(18, 5);cout<<"Press any key to start";
	getch();
	setCursorPosition(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			for(int i=0; i<10; i++){
				if( ch == keys[i] || ch-32 == keys[i] ){
					resetAlphabet(i);
					score++;
					updateScore();
				}
			}
			if(ch==27){
				break;
			}
		} 
		
		for(int i=0; i<10; i++)
			drawAlphabet(i);  
			
		Sleep(300); 
		
		for(int i=0; i<10; i++){
			eraseAlphabet(i);  
			keyPos[i][1] += 1;
			if( keyPos[i][1] > SCREEN_HEIGHT ){
				gameOver();
				updateHighScore();
				
				 ofstream scores("scores.txt", ios::app);
                if (scores.is_open()) {
                    scores << "Player: " << playerName<< " | Score: " << score << endl;
                    scores.close();
                } else {
                    cout << "Unable to open the file for saving scores." << endl;
                }
				return;
				
	  
    }		
        
			}
		}
		
	};
	
};
int main() {
    TypingTutor game;
    fstream scores;
   
    do {
        system("cls");
        game.setCursor(0, 0);

        cout << " -------------------------- " << endl;
        cout << " |     TYPING  TUTOR      | " << endl;
        cout << " --------------------------" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Instructions" << endl;
        cout << "3. Your score and High Score" << endl;        
        cout << "4. Quit" << endl;
        cout << "Select option: ";

        char option = getche();

        switch (option) {
            case '1':        	
                game.playGame();
                break;
            case '2':
                game.displayInstructions();
                break;
                case '3':
                game.displayHighScore();
                break;
            case '4':
                exit(0);
                break;
            default:
                cout << "\nInvalid option! Please try again.\n";
                break;
        }
    } while (1);

    return 0;

}
