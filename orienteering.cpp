#include <cstdlib>
#include <iostream>
#include <cstring>
#include <queue>
#include <stack>

using namespace std;

#define MAX_NODE  20
#define MAX_CHECK_POINT  18
#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define INFINITY 99999

int distance_subset[MAX_NODE][ (1 << 19) + 10 ];

void Stack_()
{
	stack<int> S;
	S.
}

class Orienteering {
     //--------------------
    char input_mat[MAX_HEIGHT][MAX_WIDTH];
    int  reverse_mat_index[MAX_HEIGHT][MAX_WIDTH];
    int all_point_index[MAX_NODE][2];

    int width,height;
    int check_point_count;
    int total_node;
    int goal_index;

    int nodes_reachable_from_source;
    bool source_exploring;

    //--------- bfs() ------------------
    int distance_mat[MAX_NODE][MAX_NODE];
    int bfs_distance[MAX_HEIGHT][MAX_WIDTH];
    //--------- bfs() ------------------
    //-----------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------
    int input();
    int generate_distance_matrix();
    int bfs(int start_i, int start_j);
    bool explorer(int start_i, int start_j,int point_i,int point_j,int next_i,int next_j);
    int output();
    int tsp(int current_node, int subset);
    int check();
    //-------------------------------------------------------
    public:
        Orienteering();
        int main();


};

int Orienteering::check(){
    /*
    cout<<"all point index \n";
    for(int i=0 ; i < total_node ; i++ ){
        for(int j = 0 ; j < 2  ; j++ ){
            cout<<all_point_index[i][j];//<<endl;
        }
        cout<<endl;
    }
    */
    /*
    cout<<"Distance mat \n";
    for(int i=0 ; i < total_node ; i++ ){
        for(int j = 0 ; j < total_node  ; j++ ){
            cout<<distance_mat[i][j];//<<endl;
        }
        cout<<endl;
    }
    //*/
    /*
    for(int i=0 ; i < height ; i++ ){
        for(int j = 0 ; j < width  ; j++ ){
            cout<<input_mat[i][j];//<<endl;
        }
        cout<<endl;
    }
    */
}


Orienteering::Orienteering(){
    width = height = 0;

    // 0 is for start point and last count for goal
    //check_point_count = 1;
}

/**
* after calling input() -> check_point_count holds total # of check point which are stored from 1 to check_point_count
index in all_point_index[][].
start_point is stored at [0][]
goal at                  [19][] i.e. at end always.
*/

int Orienteering::input(){

    // input is given in order : W H
    cin>>width;

    cin>>height;

    if( ( width < 1 || width > MAX_WIDTH ) || ( height < 1 || height > MAX_HEIGHT ) )
        return -1;

    // 0 is for start point and last count for goal
    check_point_count = 0;
    int start,goal, goal_i, goal_j;
    start=goal = 0;
    char ch;
    for(int i=0 ; i < height ; i++ ){
        for( int j=0 ; j<width ; j++){
            cin>>ch;

            if( ch == '@' ){

                if( check_point_count > MAX_CHECK_POINT )
                    return -1;

                ++check_point_count;
                all_point_index[ check_point_count][0] = i;
                all_point_index[ check_point_count][1] = j;

                // if get time implement with a Map<> to save space
                reverse_mat_index[i][j] = check_point_count;

                //check_point_count++;

            }else if( ch == 'S' ){
                if(start != 0 )
                    return -1;
                start++;

                all_point_index[0][0] = i;
                all_point_index[0][1] = j;

                reverse_mat_index[i][j] = 0 ;

            }else if( ch == 'G' ){
                if( goal != 0 )
                    return -1;
                goal++;
                goal_i = i;
                goal_j = j;
                /*
                //-----------  if u want to keep goal not in index 19 rather after all @ this is to be kept in comment
                all_point_index[19][0] = i;
                all_point_index[19][1] = j;

                reverse_mat_index[i][j] = 19 ;
                */

            }else if( ch != '.' && ch != '#' ){
                return -1 ;
            }
            input_mat[i][j] = ch ;

        }
    }

    if( start== 0 || goal == 0 )
        return -1;
    // store goal at end of @ in array
    all_point_index[ check_point_count + 1 ][0] = goal_i ;
    all_point_index[ check_point_count + 1 ][1] = goal_j ;

    reverse_mat_index[goal_i][goal_j] = check_point_count + 1;

    goal_index = check_point_count + 1 ;
    total_node = check_point_count + 2 ;
    //check();
    return 1;

}


bool Orienteering::explorer(int start_i, int start_j,int point_i,int point_j,int next_i,int next_j){
    /*
    */
    bool enqueue = false;
    char check = input_mat[next_i][next_j];
    if( check != '#' ){
        if( bfs_distance[next_i][next_j] == -1 ){//0 ){

            enqueue = true ; // first time visit so enqueue this node

            bfs_distance[next_i][next_j] = bfs_distance[point_i][point_j] + 1;

            if( check == '@' || check == 'S' || check == 'G' ){
                int i = reverse_mat_index[start_i][start_j];
                int j = reverse_mat_index[next_i][next_j] ;
                distance_mat[i][j] = bfs_distance[next_i][next_j];

                if(source_exploring == true){
                    nodes_reachable_from_source++;
                }
            }

        }
    }
    return enqueue;
}

int Orienteering::bfs(int start_i, int start_j ){
    /*
    //--------- bfs() ------------------
    int distance_mat[MAX_NODE][MAX_NODE];
    int bfs_distance[MAX_HEIGHT][MAX_WIDTH];
    //--------- bfs() ------------------
    */
    int point_i,point_j,next_i,next_j;
    queue<int> node_queue;

    node_queue.push(start_i);
    node_queue.push(start_j);


    memset(bfs_distance , -1 , sizeof(bfs_distance) );
    bfs_distance[start_i][start_j] = 0 ;

    while( !node_queue.empty() ){
        point_i = next_i = node_queue.front();
        node_queue.pop();
        point_j = next_j = node_queue.front();
        node_queue.pop();

        // right
        if( point_j + 1 < width ){
            next_j++;//
            if ( explorer( start_i, start_j, point_i, point_j, next_i, next_j) ){
                node_queue.push(next_i);
                node_queue.push(next_j);
            }
             next_j-- ;
        }

        //down
        if( point_i + 1 < height ){
            next_i++;// = point_i + 1 ;
            if ( explorer(start_i, start_j, point_i, point_j, next_i, next_j) ){
                node_queue.push(next_i);
                node_queue.push(next_j);
            }
            next_i--;
        }

        //left
        if( point_j - 1 >= 0 ){
            next_j--;// = point_j - 1 ;
            if ( explorer( start_i, start_j, point_i, point_j, next_i, next_j) ){
                node_queue.push(next_i);
                node_queue.push(next_j);
            }
            next_j++;
        }

        //up
        if( point_i - 1 >= 0 ){
            next_i--;
            if ( explorer( start_i, start_j, point_i, point_j, next_i, next_j) ){
                node_queue.push(next_i);
                node_queue.push(next_j);
            }
            next_i++;
        }

    }


}

int Orienteering::generate_distance_matrix(){

    //cout<<"generate_distance_matrix() \n";
    source_exploring = true;
    nodes_reachable_from_source = 0;
    for(int i=0 ; i < total_node ; i++ ){

        bfs(all_point_index[i][0] , all_point_index[i][1] );
        if(source_exploring){
            source_exploring=false;
            if( nodes_reachable_from_source != (total_node-1) ){
                    cout<<-1<<endl;
                return -1;
            }
        }
    }
    return 1;
}

int Orienteering::tsp(int current_node, int subset){
    // if all

    if( subset == ( ( 1<< (total_node - 1 )  ) -1  )  ){
        return distance_mat[ current_node ][ goal_index ]; //
    }
    // if already
    if( distance_subset[current_node][subset] != -1 ){
        return distance_subset[current_node][subset] ;
    }

    int minimum_distance = INFINITY ;
    int distance_i_subset;

    // except goal node
    for(int i = 1 ; i <= check_point_count ; i++ ){
        // i is not in the subset
        if( ( subset & ( 1 << i ) ) == 0  ) {

            distance_i_subset = distance_mat[current_node][i] + tsp(i , ( subset | (1 << i) ) );

            if( distance_i_subset < minimum_distance )
                minimum_distance = distance_i_subset;

        }
    }
    distance_subset[current_node][subset] = minimum_distance ;
    return minimum_distance ;
}

int Orienteering::output(){
    memset( distance_subset , -1 , sizeof(distance_subset));

    //cout<<"after Memset 1 << 19 \n total node ="<<total_node<<" check_point_count = "<<check_point_count<<" goal_index="<<goal_index<<endl;

    int min_distance = tsp(0,1);
    cout<<min_distance<<endl;
    char ch;
    //cin>>ch;
    //cin>>ch;
    return 1;
}

int Orienteering::main(){

    if( input() == -1 ){
        //error
        return -1;
    }
    if( generate_distance_matrix() == -1 ){
        //error not all nodes not reachable
        return -1;
    }
     output();
        // error
}


int main(int argc, char** argv) {

    Orienteering o;
    o.main();
    return 0;
}
