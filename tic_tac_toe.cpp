#include<bits/stdc++.h>
using namespace std;
char AI='X';
char HUMAN='O';
char EMPTY= ' ';
enum game_state 
{
    HUMAN_TURN,
    AI_TURN,
    GAME_OVER_WIN_HUMAN,
    GAME_OVER_WIN_AI,
    GAME_OVER_DRAW
};
void print_board(vector<vector<char>>& board)
{
    cout<<endl;
    int i=0,j=0;
    for(i=0;i<3;i++)
     {
        for(j=0;j<3;j++)
         {
            cout<<board[i][j];
            if(j<2) cout<<" | ";
         }
        cout<<endl;
        if(i<2) cout<<"---------"<<endl; 
    }
    cout<<endl;
}
char check_winner(vector<vector<char>>& board)
{
	int i=0,j=0;
    for(i=0;i<3;i++)
     if(board[i][0]==board[i][1] and board[i][1]==board[i][2] and board[i][0]!=EMPTY)
      return board[i][0];
    for(j=0;j<3;j++)
     if(board[0][j]==board[1][j] and board[1][j]==board[2][j] and board[0][j]!=EMPTY)
      return board[0][j];
    if(board[0][0]==board[1][1] and board[1][1]==board[2][2] and board[0][0]!=EMPTY)
     return board[0][0];
    if(board[0][2]==board[1][1] and board[1][1]==board[2][0] and board[0][2]!=EMPTY)
     return board[0][2];
    return EMPTY;      
}
bool board_full(vector<vector<char>>& board)
{
	int i=0,j=0;
    for(i=0;i<3;i++)
     for(j=0;j<3;j++)
      if(board[i][j]==EMPTY) return false;
    return true;  
}
int evaluate(vector<vector<char>>& board)
{
    char winner=check_winner(board);
    if(winner==AI) return 10;
    else if(winner==HUMAN) return -10;
    return 0;
}
int minimax(vector<vector<char>>& board,int depth,bool whos_turn)
{
	int i=0,j=0;
    int score=evaluate(board);
    if(score==10) return score-depth;
    if(score==-10) return score+depth;
    if(board_full(board)) return 0;
    if(whos_turn)
     {
        int best=std::numeric_limits<int>::min();
        for(i=0;i<3;i++)
         for(j=0;j<3;j++)
          if(board[i][j]==EMPTY)
           {
            board[i][j]=AI;
            best=max(best,minimax(board,depth+1,false));
            board[i][j]=EMPTY;
           }
        return best;   
     }
    else
     {
        int best=std::numeric_limits<int>::max();
        for(i=0;i<3;i++)
         for(j=0;j<3;j++)
          if(board[i][j]==EMPTY)
           {
            board[i][j]=HUMAN;
            best=min(best,minimax(board,depth+1,true));
            board[i][j]=EMPTY;
           }
        return best;   
     }  
}
pair<int,int> find_best(vector<vector<char>>& board)
{
	int i=0,j=0;
    int best_val=std::numeric_limits<int>::min();
    pair<int,int> best_move={-1,-1};
    for(i=0;i<3;i++)
     for(j=0;j<3;j++)
      if(board[i][j]==EMPTY)
       {
        board[i][j]=AI;
        int move_val=minimax(board,0,false);
        board[i][j]=EMPTY;
        if(move_val>best_val)
         {
            best_move={i,j};
            best_val=move_val;
         }
       }
    return best_move;   
}
int main()
{
    vector<vector<char>> board(3,vector<char>(3,EMPTY));
    game_state current_state;
    cout<<"Tic-Tac-Toe AI(minimax algorithm)"<<endl;
    cout<<"Human = 'O' AI = 'X'"<<endl;
    char choice;
    cout<<"Go first?(y/n):";
    cin>>choice;
    if(choice=='n' or choice=='N') current_state=AI_TURN;
    else current_state=HUMAN_TURN;
    while(true)
     {
        print_board(board);
        switch(current_state)
         {
            case HUMAN_TURN:
             {
                int row,col;
                cout<<"Your turn please enter row and col(0-2): ";
                cin>>row>>col;
                if(row>=0 and row<3 and col>=0 and col<3 and board[row][col]==EMPTY)
                 {
                    board[row][col]=HUMAN;
                    char winner=check_winner(board);
                    if(winner==HUMAN) current_state=GAME_OVER_WIN_HUMAN;
                    else if(board_full(board)) current_state=GAME_OVER_DRAW;
                    else current_state=AI_TURN;
                 }
                else cout<<"Wrond input"<<endl;
                break;
             }
            case AI_TURN:
             {
                cout<<"AI thinking..."<<endl;
                pair<int,int> ai_move=find_best(board);
                board[ai_move.first][ai_move.second]=AI;
                char winner=check_winner(board);
                if(winner==AI) current_state=GAME_OVER_WIN_AI;
                else if(board_full(board)) current_state= GAME_OVER_DRAW;
                else current_state=HUMAN_TURN;
                break;
             }
            case GAME_OVER_WIN_HUMAN:
             {
                cout<<"You WIN Congrats!"<<endl;
                goto end_game;
             }
            case GAME_OVER_WIN_AI:
             {
                cout<<"AI WIN please try again."<<endl;
                goto end_game;
             }
            case GAME_OVER_DRAW:
             {
                cout<<"GAME DRAW try again."<<endl;
                goto end_game;
             }  
         } 
     }
    end_game:
        print_board(board); 
        return 0;
}