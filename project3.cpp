#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

template <typename T> class vectorClass
{
    T* array;
    int cap;
    int cur;

public:
    vectorClass()
    {
        array = new T[1];
        cap = 1;
        cur = 0;
    }


    void push(T data)
    {

        if (cur == cap) {
            T* temp = new T[2 * cap];
            for (int i = 0; i < cap; i++) {
                temp[i] = array[i];
            }
            delete[] array;
            cap*= 2;
            array = temp;
        }
        array[cur] = data;
        cur++;
    }

    T get(int index)
    {
        if (index < cur)
            return array[index];
    }

    int size() {
        return cur;
    }

    void pop() {
        cur--;
    }

    void push(int data, int index)
    {
        if (index == cap)
            push(data);
        else
            array[index] = data;
    }
};

struct Edge{
   int edge1;
   int edge2;
   int weight;
};



using namespace std;
vectorClass<int>  breakingUpString(vectorClass<string> numbers);
bool containsValue(vectorClass<string> oddVertices, string s);
vectorClass<Edge> returnEdges(vectorClass<string> numbers, vectorClass<Edge> edges);
void addEdge(vectorClass<int> adj_list[], int u, int v);
void displayAdjList(vectorClass<int> adj_list[], int v);
int returnNumEdges(vectorClass<string> numbers);
vector<vector<int>> floydMarshall(vector<vector<int>> graph);
bool contains( vectorClass<int> oddVertices, int num);



int main() {
    string s;
    string line;
    vectorClass<string> numbers;
    ifstream myfile ("konigsberg.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
           numbers.push(line);
        }
        myfile.close();
    }

    vectorClass<int> oddVertices;
    int num = 0;
    num = returnNumEdges(numbers);
    vectorClass<int> adj[returnNumEdges(numbers)];

    vector<vector<int>> graph(num -1, vector<int> (num-1 , 0));

    vectorClass<Edge> edges;
    oddVertices = breakingUpString(numbers);
    edges = returnEdges(numbers, edges);

    for(int i=0; i< edges.size(); i++){
        int point1;
        int point2;

        point1 = edges.get(i).edge1;
        point2 = edges.get(i).edge2;

        graph[point1 - 1][point2 -1] = 1;
        graph[point2 - 1][point1 -1] = 1;
    }


    vector<vector<int>> allDistances;
    vector<int> distances1;


    floydMarshall(graph);



    for(int i=0; i< graph.size(); i++){
        vector<int> distances;
        for(int j=0; j< graph[i].size(); j++){
            if(contains(oddVertices, (i+1)) == true && contains(oddVertices, (j+1)) == true) {
             distances.push_back(graph[i][j]);
             distances1.push_back(graph[i][j]);
            }
        }

        allDistances.push_back(distances);

    }


    cout  << endl;
    cout << endl;

    cout << "Results of Floyd-Warhshall on O:" << endl;
    cout << "     | ";
    for(int i=0; i< oddVertices.size(); i++){
        cout <<"   " << oddVertices.get(i);
    }
    cout << endl;
    cout << "--- -+- ";





    for(int i=0; i< oddVertices.size(); i++){
        cout << "--- ";
    }




    cout << endl;

    int count = 0;
    int control = 0;
    for(int i=0; i< oddVertices.size(); i++){
        cout << "  " << oddVertices.get(i) << "  |";

        for(int a = count; a< count + 2; a++){

            cout << "    " << distances1[a] << "   ";
            cout << distances1[a+1];

            if(control == 0){
                break;
            }



        }

        cout << endl;
        count +=2;


    }








    cout << endl;
    return 0;
}

bool contains( vectorClass<int> oddVertices, int num){

   for(int i=0; i < oddVertices.size(); i++){
       if(oddVertices.get(i) == num){
           return true;
       }
   }

   return false;
}
vector<vector<int>> floydMarshall(vector<vector<int>> graph){

   int i, j, k;

    for(k=0; k < graph.size(); k++) {

        for (i = 0; i < graph.size(); i++) {
            for (j = 0; j < graph.size(); j++)
            {
                if ((graph[i][k] * graph[k][j] != 0) && (i != j))
                {
                    if ((graph[i][k] + graph[k][j] < graph[i][j]) || (graph[i][j] == 0))
                    {
                       graph[i][j] = graph[i][k] + graph[k][j];
                    }
                }
            }
        }
        }


    vector<vector<int>> allDistance;


    for (i = 0; i < graph.size(); i++)
    {
        vectorClass<int> distance;
        for (j = 0; j < graph.size(); j++)
        {
           graph[i][j] = graph[i][j];
        }
    }



    return graph;

}


int returnNumEdges(vectorClass<string> numbers) {
    vectorClass<string> words;
    for (int i = 0; i < numbers.size(); i++) {
        string word = "";
        for (auto x: numbers.get(i)) {
            if (x == ' ') {
                words.push(word);
                word = "";

            } else {
                word = word + x;
            }
        }

        words.push(word);
    }


    return stoi(words.get(1));
}
void addEdge(vectorClass<int> adj_list[], int u, int v){
    adj_list[u].push(v);
    adj_list[v].push(u);
}
vectorClass<int>  breakingUpString(vectorClass<string> numbers){

    vectorClass<string> words;
    int count = 0;
    for(int i=0; i< numbers.size(); i++){
        string word = "";
        for(auto x: numbers.get(i)){
            if( x== ' '){
                words.push(word);
                if(count == 0 || count == 1){
                    words.pop();
                }
                word = "";
                count ++;
            } else{
                 word = word + x;
            }
        }

        words.push(word);

        if(count == 0 || count == 1){
            words.pop();
        }

        count ++;
    }


    vectorClass<string> oddVerticesString;
    vectorClass<int> oddVerticesInteger;
    for(int i =0; i< words.size(); i++){
        string checker = words.get(i);
        int count = 0;
        for(int j=0; j< words.size(); j++){

            if(words.get(i).compare(words.get(j)) == 0){
                count++;
            }
        }

        if(count % 2 != 0 && containsValue(oddVerticesString, words.get(i)) == false){
            oddVerticesString.push(words.get(i));
        }
    }

    for(int i=0; i< oddVerticesString.size(); i++){
        oddVerticesInteger.push(stoi(oddVerticesString.get(i)));
    }


    cout << "The odd-degree vertices in G: O = { ";
    for(int i=0; i< oddVerticesInteger.size(); i++){
        cout << oddVerticesInteger.get(i) << " ";
    }

    cout << "}";


   return oddVerticesInteger;

}

vectorClass<Edge> returnEdges(vectorClass<string> numbers, vectorClass<Edge> edges){
    vectorClass<string> words;
    int count = 0;
    for(int i=0; i< numbers.size(); i++){
        string word = "";
        for(auto x: numbers.get(i)){
            if( x== ' '){
                words.push(word);
                if(count == 0 || count == 1){
                    words.pop();
                }
                word = "";
                count ++;
            } else{
                word = word + x;
            }
        }

        words.push(word);

        if(count == 0 || count == 1){
            words.pop();
        }

        count ++;
    }




    vectorClass<vectorClass<string>> numberStrings;

    for(int i=0; i < words.size(); i+=2){
        Edge edge;
        edge.edge1 = stoi(words.get(i));
        edge.edge2 = stoi(words.get(i + 1));
        edges.push(edge);

    }


    return edges;



}


bool containsValue(vectorClass<string> oddVertices, string s){
    for(int i=0; i< oddVertices.size(); i++){
        if(oddVertices.get(i).compare(s) == 0){
            return true;
        }
    }
    return false;
}




