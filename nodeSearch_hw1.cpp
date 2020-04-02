#include<iostream>
#include<string>
#include <cstdlib>
using namespace std;

void adjacency_lists( int n, int m, int **list, int ** weight, int **edgeInfo, int *degrees);
void inputGraphInfo(int m, int **edgeInfo, int *degrees);
void findNextNode(int n, int s, int i, int node, int *degrees, int **list, int **weight, int *nodeAccept, int *leastDist, int &cnt, int dist, int currentDist, int pre);
void sortNodeAcpt(int n, int *nodeAccept);
void printNode(int n, int * nodeAccept);


bool ifAccepted(int n, int node, int *nodeAcceept);

int main()
{	string pn, pm, px, ps;

	getline(cin, pn, ',');
	int n = atoi(pn.c_str());

	getline(cin, pm);
	int m = atoi(pm.c_str());

    // to create a 3 * m matrix
	int **edgeInfo = new int*[m];     
	for(int i = 0; i < m; i++)
	    edgeInfo[i] = new int[3];
	
	int **list;          
	list = new int *[n];
	
	int **weight;                  //紀錄權重(distance) 
    weight = new int *[n];
    
    int *degrees = new int[n];    // 紀錄每一個點有多少邊 
    for(int i = 0; i < n; i++)
        degrees[i] = 0;
    
    int *nodeAccept;              //紀錄範圍內的node 
    nodeAccept = new int[n];
    for(int i = 0; i < n; i++)
		nodeAccept[i] = -1;
	
	int *leastDist;
	leastDist = new int[n];
	for(int i = 0; i < n; i++)
		leastDist[i] = 1000000;
   
//-----------------------------------------------------------------
					
	inputGraphInfo( m, edgeInfo, degrees);
	
    getline(cin, px, ',');
    int x = atoi(px.c_str());
    x--;                                  //全部點的編號都減一(測資1~5 = 這裡0~4) 
    nodeAccept[0] = x;
	getline(cin, ps); 
    int s = atoi(ps.c_str());
	
    adjacency_lists(n, m, list, weight, edgeInfo, degrees);
    
    int node = x, currentDist = 0;
    int cnt = 1;
    for(int i = 0; i < degrees[node]; i++)
    {   node = x; currentDist = 0;
        int pre = node, dist = currentDist;
   //  	cout << "default : node = " << node << " : branch = " << i << "ready to find next" << "\n";  
    	findNextNode(n, s, i, node, degrees, list, weight, nodeAccept, leastDist, cnt, dist, currentDist, pre);
	}
/*
	cout << "this is nodeAccept" << "\n";
	for(int i = 0; i < n; i++)
	  cout << nodeAccept[i] << " " ;
	cout << "\n";
*/
// 清掉第一個數(x自己)		
//-----------------------------------	
	for(int i = 0; i < n -1; i++)
	{
		if(nodeAccept[i+1] != -1)
			nodeAccept[i] = nodeAccept[i+1];
		else
		    nodeAccept[i] = -1;
	}
	if(nodeAccept[n -1] != -1)
		nodeAccept[n-1] = -1;
/*
	cout << "this is nodeAccept cleared first" << "\n";
	for(int i = 0; i < n; i++)
	  cout << nodeAccept[i] << " " ;
	cout << "\n";
*/
	sortNodeAcpt(n, nodeAccept);
/*
	cout << "this is sorted nodeAccept" << "\n";
	for(int i = 0; i < n; i++)
	  cout << nodeAccept[i] << " " ;
	cout << "\n";
*/
	printNode(n, nodeAccept);


    
/*	
//default check

    cout << "this is weight" << "\n";
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < degrees[i]; j++)
		    cout << weight[i][j] << " ";
		cout << "\n";
	}
	cout << "THIS IS LIST " << "\n";
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < degrees[i]; j++)
		    cout << list[i][j] << " ";
		cout << "\n";
	}
	cout << "this is edgeInfo" << "\n";
	for(int i = 0; i < m; i++)
	{ 
	    for(int j = 0; j < 3; j++)  
	        cout << edgeInfo[i][j] << " ";
	    cout << "\n";
	}	
	cout << "this is degrees" << "\n"; 
	for(int i = 0; i < n; i++)
	  cout << degrees[i] << " ";
	cout << "\n";
	cout << "this is nodeAccept" << "\n";
	for(int i = 0; i < n; i++)
	  cout << nodeAccept[i] << " " ;
	cout << "\n"; 
	
*/ 
	

//release memory
//-------------------------------------------------
	delete [] edgeInfo;
	delete [] list;
	delete [] degrees;
	delete [] weight;
	delete [] nodeAccept;
	delete [] leastDist;
}
  

void inputGraphInfo(int m, int **edgeInfo, int *degrees)   //要傳pointer進去, call by pointer 
{
	for(int i = 0; i < m; i++)// input data and calculate the degrees
	{   
    	string pu, pv, pdist;   // 一條邊的端點、另一個端點
    	getline(cin, pu, ',');
    	int u = atoi(pu.c_str());
    	u--;                                              //編號減一 
    	edgeInfo[i][0] = u;
    	degrees[u]++;
    	  	
	    getline(cin, pv, ',');
	    int v = atoi(pv.c_str());
	    v--;                                              // 編號減一 
	    edgeInfo[i][1] = v;
	    degrees[v]++;
	    
	    getline(cin, pdist);
	    int dist = atoi(pdist.c_str());
	    edgeInfo[i][2] = dist;     
    }
	
} 

void adjacency_lists( int n, int m, int **list, int ** weight, int **edgeInfo, int *degrees)
{  
	//紀錄list 目前intput進幾個值  
	int *size;
	size = new int[n];    
	for(int i = 0; i < n; i++)
	    size[i] = 0;  
	
	for(int i = 0; i < n; i++)
		list[i] = new int[degrees[i]];
	for(int i = 0; i < n; i++)
		weight[i] = new int[degrees[i]];
	  
	//create adjacency
	for(int i = 0; i < m; i++)
	{ 
	    int v, u, dist;
	    
		   v = edgeInfo[i][0];
		   u = edgeInfo[i][1];
		dist = edgeInfo[i][2];
	
		list[v][size[v]] = u;
		list[u][size[u]] = v;
		weight[v][size[v]] = dist;
		weight[u][size[u]] = dist;	
		size[v]++;
		size[u]++;
	}  
}

void findNextNode(int n, int s, int i, int node, int *degrees, int **list, int **weight, int *nodeAccept, int *leastDist, int &cnt, int dist, int currentDist, int pre)
{   
 //   cout << "cnt = "  << cnt - 1 << "\n"; 
//    cout << "dist = " << dist << "\n";

    int a = dist + weight[node][i];
    if(	a <= s)
	{   
	    if(list[node][i] != pre)
		{   
			pre = node;
			node = list[node][i];
			if(!ifAccepted(n, node, nodeAccept))                         // 如果此範圍內節點還沒有被紀錄過，加進nodeAccept 
			{	
	//			cout << node << "add into nodeAccept" << "\n";
	//			cout << " pre = " << pre << ", i = " << i << "weight[pre][i] = " << weight[pre][i] << "\n";
		   		nodeAccept[cnt] = node;
		   		cnt++;
			}
			dist += weight[pre][i];
			currentDist = dist;
			if(currentDist < leastDist[node])
			{
				leastDist[node] = currentDist;
	 			for(int i = 0; i < degrees[node]; i++)
	   			{	
	   		    	dist = currentDist;
	//   			cout << "default : node = " << node << " : branch = " << i << " ready to find next" << "\n";
	    			findNextNode(n, s,  i, node, degrees, list, weight, nodeAccept, leastDist, cnt, dist, currentDist, pre);
   				} 			
			} 
		}
	}	
}

bool ifAccepted(int n, int node, int *nodeAccept)
{
	for(int i = 0; i < n; i++)
	{
		if(nodeAccept[i] == -1)
			return false;
		else
			if(node == nodeAccept[i])
				return true;		  
	}
	return false;
}

void sortNodeAcpt(int n, int *nodeAccept)
{   
    for (int i = 1; i < n; i++) 
	{   if(nodeAccept[i] != -1)
		{
        	int key = nodeAccept[i];
        	int j = i - 1;
        	while (key < nodeAccept[j] && j >= 0)
			{
            	nodeAccept[j+1] = nodeAccept[j];
            	j--;
        	}
        	nodeAccept[j+1] = key;
    	}
    	else
    		break;
	}	
}

void printNode(int n, int *nodeAccept)
{
	for(int i = 0; i < n; i++)
	{   
		if(nodeAccept[0] == -1)
		{
			cout << "None";
			break;
		}
		if(nodeAccept[i] != -1)
		{
			cout << nodeAccept[i] + 1;
			if(nodeAccept[i + 1] != -1)
				cout << ",";
		} 
	}	
}


