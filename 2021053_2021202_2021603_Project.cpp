#include <iostream>
#include <vector>
#include<string>

using namespace std;

// building a structure for our nodes
struct QueueNode
{
    double value;
    int nodeNum;
    bool done = false;
};
//node storing the name and connections of particular route
struct routenode
{
    string name;
    int index=30000;
    routenode *next = nullptr;
};

class routerMap
{
    private:
       //2d graph
        double **cityArray;

        int numOfCities;
        routenode *cityHashTable;

    public:
        routerMap()

        {
            //hard core value
            int numOfCities = 6;

            this->numOfCities = numOfCities;


            //2d array creation
            cityArray = new double*[numOfCities];



            for(int cities = 0; cities < numOfCities; cities++)

            {

                cityArray[cities] = new double [numOfCities];

            }


            //hashtable to reduce searching time
            cityHashTable = new routenode[numOfCities];

            
          

        }


        //function to find hash index through ascii of string words
        int hash_index(string word)

        {

            int index=0;

            int power=1;



              for(int i=0;i<word.size();i++)

              {

                //cout<<index;

                //cout<<endl;

                 index+=(power*int(word[i]))%numOfCities;

                 power=power*71;



              }

             

              return index%numOfCities;



        }

        
          // function to create a map and giving it names
          //routes are being inserted in hashmap and their indexes are being stored to make searching optimal
         void make_router_map()

         {

            insert_in_hash("omega");

            insert_in_hash("galaxy");

            insert_in_hash("pinout");

            insert_in_hash("tplink");

            insert_in_hash("ptcl");

            insert_in_hash("transworld");



         }
         // function created to print the names from the hash table and their indexes
         void print_hash()

         {

            for(int i=0;i<numOfCities;i++)

            {

                cout<<"Name: "<<cityHashTable[i].name<<"->index : "<<cityHashTable[i].index;

                cout<<endl;

            }

         }
           //function to add a route into the hash table and to check if there is any space left for a route to be added
        void insert_in_hash(string city)

        {
              //index of city 
              int index=hash_index(city);

              int count=0;
             //this while loop is enabling linear probing to avoid clustering
              while(cityHashTable[index].index!=30000)

              {

                if(count==numOfCities+1)

                {

                    break;

                }

              

                   index=(index+1)%numOfCities;

                   count++;

              }
              //if hash map is full
              if(count==numOfCities+1)
              {
                cout<<"no storage available to add new cities";
              }
              else
              {
                cityHashTable[index].name=city;
                cityHashTable[index].index=index;
              }

        }
         //function that manually set the distance between each route from the other
         //It can be done dynamically but we are inserting hard core values so that you donot need to
         //enter all distances between routes which takes time 
        void set_distance_between_routers()
        {
            for(int i=0;i<numOfCities;i++)
            {
                 cityArray[i][i]=0;
            }

            cityArray[0][1]=cityArray[1][0]=200;
            cityArray[0][2]=cityArray[2][0]=370;
            cityArray[0][3]=cityArray[3][0]=1700;
            cityArray[0][4]=cityArray[4][0]=1100;
            cityArray[0][5]=cityArray[5][0]=15;
            cityArray[1][2]=cityArray[2][1]=550;
            cityArray[1][3]=cityArray[3][1]=2000;
            cityArray[1][4]=cityArray[4][1]=1250;
            cityArray[1][5]=cityArray[5][1]=220;
            cityArray[2][3]=cityArray[3][2]=1500;
            cityArray[2][4]=cityArray[4][2]=800;
            cityArray[2][5]=cityArray[5][2]=350;
            cityArray[3][4]=cityArray[4][3]=500;
            cityArray[3][5]=cityArray[5][3]=1650;
            cityArray[4][5]=cityArray[5][4]=1050;

        }
        // this function is the djkstra algorithm implementation which tells us the shortest route from any route depending on the start and destination
        void shortestPathAlgorithm(int src, int dest)
        {
            if(src==-1||dest==-1)
            {
                //  incorrect input
                cout<<"incorrect value of source/destination entered";
                return;
            }

            // This queue is used for Breadth First Traversal
            vector<QueueNode> nodeQueue;

            // This vector stores the shortest path as it is traversing and at the end displays
            // that shortest path
            vector<int> shortestPath;

            
            // Pushing all the nodes to the nodequeue with default values 30000(infinity) and checked false
            for(int i = 0; i < numOfCities; i++)
            {
                // setting values and pushing into queue
                QueueNode temp;
                temp.value = 30000;
                temp.nodeNum = i;
                temp.done = false;
                nodeQueue.push_back(temp);

            }

            // Setting the value of source to 0 in the queue as it is priority queue and pops the
            // smallest element which at the current moment would be the source node
            nodeQueue[src].value = 0;

            // This variable would run till the number of cities
            int h = 0;

            while(h < numOfCities)

            {
                // This variables is used to store the index of node having minimum values in queue
                // to pop it later
                int minIndex = 0;

                int min = nodeQueue[minIndex].value;

                // Finding the minimum value in queue and its index to pop it
                for(int i = 1; i < numOfCities; i++)
                {
                    if(nodeQueue[i].value < min)
                    {
                        min = nodeQueue[i].value;
                        minIndex = i;
                    }
                }


                // Updating the values of neighbours of minimum node being popped 
                for(int i = 0; i < numOfCities; i++)
                {
                    if(i != minIndex && nodeQueue[i].done == false)
                    {
                        nodeQueue[i].value = nodeQueue[minIndex].value + cityArray[minIndex][i];
                    }   
                }


                // The next shorest path is pushed in to the shortest path vector
                shortestPath.push_back(minIndex);

                // The node which is checked would not be checked again to avoid cycling through the
                // graph
                nodeQueue[minIndex].value = 40000;

                nodeQueue[minIndex].done = true;

                h++;
            }


            // Printing the shortest path
            for(int i = 0; i < shortestPath.size(); i++)
            {
                if(shortestPath[i]==dest)
                {
                    cout << cityHashTable[shortestPath[i]].name;
                    break;
                }
                cout << cityHashTable[shortestPath[i]].name  << "-->";
            }

        }
       // this function searches up a router by its name in the hash table
        int search_in_hash(string city)
        {
              int index=hash_index(city);
              int count=0;

              while(cityHashTable[index].name!=city)
              {
                if(count==numOfCities+1)
                    break;

                   index=(index+1)%numOfCities;
                   count++;
              }

              if(count==numOfCities+1)
                return -1;

              else
                return index;
        }
};


int main()
{
// routers available 

routerMap rm;

rm.make_router_map();

rm.set_distance_between_routers();
int value;
while (1)
{
    cout<<"Enter the following\nEnter 1 for checking optimal route.\nEnter 2 for exiting program\n";
    cin>>value;
    if(value==1)
    {
        cout<<endl;
        cout<<"Available Routers\nPtcl\ntransworld\ntplink\npinout\ngalaxy\nomega\n";
        cout<<"Insert name of source router(in String) :"<<endl;
        cin.ignore();
        string s1,s2;
        cin >> s1;
        cout<<"Insert name of destination router(in String) :"<<endl;
        cin.ignore();
        cin >> s2;

        while (s1 != "ptcl" && s1 != "transworld" && s1 != "tplink" && s1 != "pinout" && s1 != "galaxy" && s1 != "omega")
        {
            cout<<s1;
            cout<<"Router 1 is incorrect, Please enter again :";
            cin>>s1;

        }
        while (s2 != "ptcl" && s2 != "transworld" && s2 != "tplink" && s2!= "pinout" && s2 != "galaxy" && s2 != "omega")
        {
            cout<<"Router 1 is incorrect, Please enter again :";
            cin>>s2;
        }
        cout<<"Optimal route between "<<s1<<" and "<<s2<<" is  \n";
        rm.shortestPathAlgorithm(rm.search_in_hash(s1),rm.search_in_hash(s2));
        cout<<endl;
        cout<<endl;
    }
    else if (value==2)
    {
        break;
    }
    else{
        cout<<"Incorrect value Entered .Please enter the value again\n";
        cin>>value;
    }
    
    
}
    return 0;

}