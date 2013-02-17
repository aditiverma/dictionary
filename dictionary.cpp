//dictionary data structure
==========

#include <time.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include<math.h>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

ofstream outputfile; //this is the handle of the output files.
ifstream inputfile; //this is the handle for the input files.

//following class is the node which is used by AVL trees
class node
{
  public:
	int key,value;
	int hbal;
	int height;
	node *left;
	node *right;
	node *parent;

	node (int a, int b, node *p)
	{
		key = a;
		value = b;
		parent = p;
		left=right=NULL;
		height = 1;
		hbal = 0;
	}
	node()
	{
	}
};

//this class is the node of the binary trees.
class btreenode //this is the node class
{
    public:
    int *key,*value,pairs;
    btreenode **children;
    btreenode (int m)
    {
        int i=0;
        key = new int[m-1];
        value = new int[m-1];
        children = new btreenode*[m];
        children[0]=NULL;
        pairs = 0;
        while(i<m)
        {
            children[i]=NULL;
            i++;
        }
    }
    btreenode()
    {
    }
};
//this class is used by the btrees to save the key and value pair to be inserted in the parent node and it also saves the pointer to the new
//node after splitting the node.
class returncontainer //this is the container class which enables toreturn both the pair and a pointer to a node from same return.
{
    public:
    int key;
    int value;
    btreenode *p;
};
//this is the main btree class which implements the inserting searching functionality of btree
//it also implements the inOrder and the postOrder sequence of the traversal.
class btree
{
    private:
    btreenode *root,*test;
    btreenode *childnode,*newnode,*newnode2;
    deque<btreenode*> mydeque;
    int m;
    public:
    btree(int m1)
    {
        root=0;
        m = m1;
    }
    void insert(int k1, int v1) //this is the actual insert API
    {
        int k=k1,v=v1,i=0,j,middle,pkey,pvalue;
        btreenode *p=NULL;
        returncontainer *returnc;
        if(!root)
        {
            root = new btreenode(m);
            root->key[0]=k;
            root->value[0]=v;
            root->pairs = 1;
            return;
        }
        i=0;
        while((k>root->key[i])&&(i<root->pairs))
        {
            i++;
        }
        childnode = root->children[i];
        if(childnode)
        {
            returnc = insert2(k,v,childnode);
            if(returnc->p==NULL)
            {
                return;
            }
            else
            {
                k = returnc->key;
                v = returnc->value;
                p = returnc ->p;
            }
        }
        if(root->pairs<(m-1))
        {
            i=0;
           while((k>root->key[i])&&(i<root->pairs))
            {
                i++;
            }
            j=root->pairs-1;
            while(j>=i)
            {
                root->key[j+1]=root->key[j];
                root->value[j+1]=root->value[j];
                root->children[j+2]=root->children[j+1];
                j--;
            }
            root->key[i]=k;
            root->value[i]=v;
            root->children[i+1]=p;
            root->pairs=root->pairs+1;
        }
        else
        {
            middle = ceil((double)m/2)-2;
            if(k>root->key[middle])
            {
                if(k<root->key[middle+1])
                {
                    //code for pinsert = k
                    pkey = k;
                    pvalue = v;
                    newnode = new btreenode(m);
                    i=middle+1;
                    j=0;
                    newnode->children[0]=p;
                    while(i<(m-1))
                    {
                        newnode->key[j]=root->key[i];
                        newnode->value[j]=root->value[i];
                        newnode->children[j+1]=root->children[i+1];
                        i++;
                        j++;
                    }
                    newnode->pairs = m-middle-2;
                    root->pairs = middle + 1;
                    newnode2 = new btreenode(m);
                    newnode2->key[0]=pkey;
                    newnode2->value[0]=pvalue;
                    newnode2->pairs = 1;
                    newnode2->children[0]=root;
                    newnode2->children[1]=newnode;
                    root=newnode2;
                }
                else
                {
                    //code for inserting key into new node
                    pkey = root->key[middle+1];
                    pvalue = root->key[middle+1];
                    newnode = new btreenode(m);
                    i=middle+2;
                    j=0;
                    newnode->children[0]=root->children[middle+2];
                    while((i<(m-1)&&k>root->key[i]))
                    {
                        newnode->key[j]=root->key[i];
                        newnode->value[j]=root->value[i];
                        newnode->children[j+1]=root->children[i+1];
                        i++;
                        j++;
                    }
                    newnode->key[j]=k;
                    newnode->value[j]=v;
                    newnode->children[j+1]=p;
                    j++;
                    while((i<(m-1)))
                    {
                        newnode->key[j]=root->key[i];
                        newnode->value[j]=root->value[i];
                        newnode->children[j+1]=root->children[i+1];
                        i++;
                        j++;
                    }
                    newnode->pairs = m-middle-2;
                    root->pairs = middle + 1;
                    newnode2 = new btreenode(m);
                    newnode2->key[0]=pkey;
                    newnode2->value[0]=pvalue;
                    newnode2->pairs = 1;
                    newnode2->children[0]=root;
                    newnode2->children[1]=newnode;
                    root=newnode2;
                }
            }
            else
            {
                //code for inserting key in old node
                    pkey = root->key[middle];
                    pvalue = root->value[middle];
                    newnode = new btreenode(m);
                    i=middle+1;
                    j=0;
                    newnode->children[0]=root->children[middle+1];
                    while(i<(m-1))
                    {
                        newnode->key[j]=root->key[i];
                        newnode->value[j]=root->value[i];
                        newnode->children[j+1]=root->children[i+1];
                        i++;
                        j++;
                    }
                    newnode->pairs = m-middle-2;
                    root->pairs = middle+1;
                    i=0;
                    while((k>root->key[i])&&(i<(root->pairs-1)))
                    {
                        i++;
                    }
                    j=root->pairs-1;
                    while(j>=i)
                    {
                        root->key[j+1]=root->key[j];
                        root->value[j+1]=root->value[j];
                        root->children[j+2]=root->children[j+1];
                        j--;
                    }
                    root->key[i]=k;
                    root->value[i]=v;
                    root->children[i+1]=p;
                    newnode2 = new btreenode(m);
                    newnode2->key[0]=pkey;
                    newnode2->value[0]=pvalue;
                    newnode2->pairs = 1;
                    newnode2->children[0]=root;
                    newnode2->children[1]=newnode;
                    root=newnode2;
            }
        }
    }
    int search(int k)
    {
        int i=0;
        btreenode *p=root;
        while(p)
        {
            i=0;
            while((k>p->key[i])&&(i<p->pairs))
            {
                i++;
            }
            if(p->key[i]==k)
           {
               return p->value[i];
           }

            p=p->children[i];
            i=0;
        }
        return 0;
    }
    returncontainer* insert2(int k,int v, btreenode *start)
    {
        int i=0,j,middle,pkey,pvalue;
        btreenode *childnode,*newnode,*p=NULL;
        returncontainer *returnc;
        returnc = new returncontainer();
        returnc->key=0;
        returnc->value=0;
        returnc->p=NULL;
        while((k>start->key[i])&&(i<start->pairs))
        {
            i++;
        }
        childnode = start->children[i];
        if(childnode)
        {
            returnc = insert2(k,v,childnode);
            if(returnc->p==NULL)
            {
                return returnc;
            }
            else
            {
                k = returnc->key;
                v = returnc->value;
                p = returnc->p;
            }
        }
         if(start->pairs<(m-1))
        {
            i=0;
           while((k>start->key[i])&&(i<start->pairs))
            {
                i++;
            }
            j=start->pairs-1;
            while(j>=i)
            {
                start->key[j+1]=start->key[j];
                start->value[j+1]=start->value[j];
                start->children[j+2]=start->children[j+1];
                j--;
            }
            start->key[i]=k;
            start->value[i]=v;
            start->children[i+1]=p;
            start->pairs++;
            returnc->p = NULL;
            return returnc;
        }
        else
        {
            middle = ceil((double)m/2)-2;
            if(k>start->key[middle])
            {
                if(k<start->key[middle+1])
                {
                    //code for pinsert = k
                    pkey = k;
                    pvalue = v;
                    newnode = new btreenode(m);
                    i=middle+1;
                    j=0;
                    newnode->children[0]=p;
                    while(i<(m-1))
                    {
                        newnode->key[j]=start->key[i];
                        newnode->value[j]=start->value[i];
                        newnode->children[j+1]=start->children[i+1];
                        j++;
                        i++;
                    }
                    newnode->pairs = m-middle-2;
                    start->pairs = middle + 1;
                    returnc->key = pkey;
                    returnc->value = pvalue;
                    returnc->p = newnode;
                    return returnc;
                }
                else
                {
                    //code for inserting key into new node
                    pkey = start->key[middle+1];
                    pvalue = start->key[middle+1];
                    newnode = new btreenode(m);
                    i=middle+2;
                    j=0;
                    newnode->children[0]=start->children[middle+2];
                    while((i<(m-1)&&k>start->key[i]))
                    {
                        newnode->key[j]=start->key[i];
                        newnode->value[j]=start->value[i];
                        newnode->children[j+1]=start->children[i+1];
                        i++;
                        j++;
                    }
                    newnode->key[j]=k;
                    newnode->value[j]=v;
                    newnode->children[j+1]=p;
                    j++;
                    while((i<(m-1)))
                    {
                        newnode->key[j]=start->key[i];
                        newnode->value[j]=start->value[i];
                        newnode->children[j+1]=start->children[i+1];
                        i++;
                        j++;
                    }
                    newnode->pairs = m-middle-2;
                    start->pairs = middle + 1;
                    returnc->key = pkey;
                    returnc->value = pvalue;
                    returnc->p = newnode;
                    return returnc;
                }
            }
            else
            {
                //code for inserting key in old node
                pkey = start->key[middle];
                pvalue = start->value[middle];
                newnode = new btreenode(m);
                i=middle+1;
                j=0;
                newnode->children[0]=start->children[middle+1];
                while(i<(m-1))
                {
                    newnode->key[j]=start->key[i];
                    newnode->value[j]=start->value[i];
                    newnode->children[j+1]=start->children[i+1];
                    i++;
                    j++;
                }
                newnode->pairs = m-middle-2;
                start->pairs = middle+1;
                i=0;
                while((k>start->key[i])&&(i<(start->pairs-1)))
                {
                    i++;
                }
                j=start->pairs-1;
                while(j>=i)
                {
                    start->key[j+1]=start->key[j];
                    start->value[j+1]=start->value[j];
                    start->children[j+2]=start->children[j+1];
                    j--;
                }
                start->key[i]=k;
                start->value[i]=v;
                start->children[i+1]=p;
                returnc->key = pkey;
                returnc->value = pvalue;
                returnc->p = newnode;
                return returnc;
            }
        }
    }
    void display( btreenode *p)
    {
       int i=0;
       if(p!=NULL)
       {
           if(p->children[i]!=NULL)
                    mydeque.push_back(p->children[i]);
            while(i<p->pairs)
            {
                outputfile<<p->key[i]<<" ";
                //cout<<p->value[i]<<" ";
                i++;
                if(p->children[i]!=NULL)
                    mydeque.push_back(p->children[i]);
            }
            //cout<<endl;
       }
    }
    void levelOrder()
    {
        mydeque.push_back(root);
        while (!mydeque.empty())
        {
            display(mydeque.front());
            mydeque.pop_front();
        }
    }
    void inOrder()
    {
        inOrderDisplay(root);
    }
    void inOrderDisplay(btreenode *p)
    {
        if(p!=NULL)
        {
            int i=0;
            inOrderDisplay(p->children[i]);
            while(i<p->pairs)
            {
                outputfile<<p->key[i]<<" ";
                i++;
                inOrderDisplay(p->children[i]);
            }
            //cout<<endl;
        }
    }
};
//this is the class whhich implement the btreeHash tree. It in turn uses btree class for its implementation.
class btreeHash
{
    private:
    btree **btrees;
    int s;
    int index;
    public:
    btreeHash(int m,int sInput)
    {
        s = sInput;
        btrees = new btree *[s];
        int i;
        for(i=0;i<s;i++)
        {
            btrees[i] = new btree(m);
        }
    }
    btreeHash()
    {}
    void insert(int key,int value)
    {
        index = (key%s);
        btrees[index]->insert(key,value);
    }
    int search(int key)
    {
        index = (key%s);
        return btrees[index]->search(key);
    }
    void levelOrder()
    {
        int i;
        for(i=0;i<s;i++)
        {
            btrees[i]->levelOrder();
            outputfile<<endl;
        }
    }
};
//this is the main AVL class which implements the AVL trees
class AVL
{
	private:
	node *root,*tempNode;
	node *currentNode;
	node *parentNode;
	int hbalance,hl,hr;
	node* rotateLL(node *A)
	{
		//std::cout<<"LL rotation called at node "<<(*A).key<<std::endl;
		node *B,*Br;
		B = (*A).left;
		printNode(B);
		Br = (*B).right;
		//std::cout<<"initialized B and Br"<<std::endl;
		//std::cout<<"B is "<<(*B).key<<std::endl;
		if(Br!=NULL)
		{
			//std::cout<<"should not enter here"<<std::endl;
			(*Br).parent = A;
		}
		//std::cout<<"updating A left with Br"<<std::endl;
		(*A).left = Br;
		//std::cout<<"updating B right with A"<<std::endl;
		(*B).right = A;
		(*A).parent = B;
		//std::cout<<"initialized LL rotation done, height update remaining"<<std::endl;
		updateHeight(A);
		updateHeight(B);
		return B;
	}
	node* rotateLR(node *A)
	{

		node *B,*C,*Cl,*Cr;
		B = (*A).left;
		C = (*B).right;
		Cl = (*C).left;
		Cr = (*C).right;

		if(Cl!=NULL)
		{
			(*Cl).parent = B;
		}
		(*B).right = Cl;

		if(Cr!=NULL)
		{
			(*Cr).parent = A;
		}
		(*A).left = Cr;

		(*B).parent = C;
		(*C).left = B;

		(*A).parent = C;
		(*C).right = A;

		updateHeight(A);
		updateHeight(B);
		updateHeight(C);
		return C;
	}
	node* rotateRL(node *A)
	{
		node *B,*C,*Cl,*Cr;
		B = (*A).right;
		C = (*B).left;
		Cl = (*C).left;
		Cr = (*C).right;

		if(Cl!=NULL)
		{
			(*Cl).parent = A;
		}
		(*A).right = Cl;

		if(Cr!=NULL)
		{
			(*Cr).parent = B;
		}
		(*B).left = Cr;

		(*B).parent = C;
		(*C).right = B;

		(*A).parent = C;
		(*C).left = A;

		updateHeight(A);
		updateHeight(B);
		updateHeight(C);
		return C;
	}
	node* rotateRR(node *A)
	{
		//int hl,hr;
		//std::cout<<"RR rotation called at node "<<(*A).key<<std::endl;
		node *B,*Bl;
		B = (*A).right;
		Bl = (*B).left;

		if(Bl!=NULL)
		{
			(*Bl).parent = A;
		}
		(*A).right = Bl;

		(*B).left = A;
		(*A).parent = B;

		updateHeight(A);
		updateHeight(B);
		return B;
	}

	void updateHeight(node *N)
	{
		int hl,hr;
		if((*N).left==NULL)
			hl = 0;
		else
			hl = (*(*N).left).height;
		if((*N).right==NULL)
			hr = 0;
		else
			hr = (*(*N).right).height;
		(*N).height = 1 + max(hl,hr);
	}

	void printNode(node *A)
	{
		//std::cout<<"Printing the node "<<std::endl;
		if(A==NULL)
		{
			//std::cout<<"The node is NULL"<<std::endl;
		}
		else
		{
			//std::cout<<"The current node is "<<(*A).key<<std::endl;
			if((*A).parent==NULL)
			{
				//std::cout<<"This node is the root!"<<std::endl;
			}
			else
			{
				//std::cout<<"The parent is "<<(*(*A).parent).key<<std::endl;
			}
			if((*A).left==NULL)
			{
				//std::cout<<"The left is NULL!"<<std::endl;
			}
			else
			{
				//std::cout<<"The left is "<<(*(*A).left).key<<std::endl;
			}
			if((*A).right==NULL)
			{
				//std::cout<<"The right is NULL!"<<std::endl;
			}
			else
			{
				//std::cout<<"The right is "<<(*(*A).right).key<<std::endl;
			}
		}
	}

	public:
	void insert(int key,int value)
	{
		//if(root!=NULL)
		//std::cout<<std::endl<<std::endl<<std::endl<<"Starting insertion of "<<key<<" Root is "<<(*root).key<<std::endl;
		bool flag = false;

		if(root==NULL)
		{
			root = new node(key,value,NULL);
			flag = true;
			//std::cout<<"inserted "<<key<<" at root"<<std::endl;
			return;
		}

		currentNode = root;
		while(flag==false)
		{
			//std::cout<<"(*currentNode).key "<<(*currentNode).key<<std::endl;
				if((*currentNode).key>key)
				{
					if((*currentNode).left==NULL)
					{
						(*currentNode).left = new node(key,value,currentNode);
						currentNode = (*currentNode).left;
						flag = true;
						//std::cout<<"inserted "<<(*(*(*currentNode).parent).left).key<<" on left of "<<(*(*currentNode).parent).key<<std::endl;
					}
					else
					{
						currentNode = (*currentNode).left;
					}
				}
				else
				{
					if((*currentNode).right==NULL)
					{
						(*currentNode).right = new node(key,value,currentNode);
						currentNode = (*currentNode).right;
						flag = true;
						//std::cout<<"inserted "<<(*(*(*currentNode).parent).right).key<<" on right of "<<(*(*currentNode).parent).key<<std::endl;
					}
					else
					{
						currentNode = (*currentNode).right;
					}
				}
		}
		//std::cout<<(*currentNode).key<<std::endl;
		parentNode = (*currentNode).parent;

		currentNode = parentNode;

		while(currentNode!=NULL)
		{
			//std::cout<<"Entering the height balancing and rotation loop from node "<<(*currentNode).key<<std::endl;
			printNode(currentNode);
			updateHeight(currentNode);
			if((*currentNode).left==NULL)
				hl=0;
			else
				hl = (*(*currentNode).left).height;

			//std::cout<<"hl is "<<hl<<std::endl;

			if((*currentNode).right==NULL)
				hr=0;
			else
				hr = (*(*currentNode).right).height;

			//std::cout<<"hr is "<<hr<<std::endl;

			hbalance = (hl-hr);

			//std::cout<<"hbal of current node is "<<hbalance<<std::endl;

			if(hbalance==2)
			{
				if((*(*currentNode).left).hbal==1)
				{
					//std::cout<<"LL"<<std::endl;
					tempNode = rotateLL(currentNode);
					//std::cout<<"LL done"<<std::endl;
					//link((*currentNode).parent,tempNode);
				}
				else
				{
					//std::cout<<"LR"<<std::endl;
					tempNode = rotateLR(currentNode);
					//link((*currentNode).parent,tempNode);
				}
				if(currentNode==root)
				{
					root = tempNode;
					(*tempNode).parent = NULL;
					printNode(tempNode);
				}
				else
				{
					if(currentNode==(*parentNode).left)
					{
						(*parentNode).left = tempNode;
						(*tempNode).parent = parentNode;
					}
					else
					{
						(*parentNode).right = tempNode;
						(*tempNode).parent = parentNode;
					}
					printNode(tempNode);
				}
				return;
			}
			else if(hbalance==-2)
			{
				if((*(*currentNode).right).hbal==1)
				{
					//std::cout<<"RL"<<std::endl;
					tempNode = rotateRL(currentNode);
				}
				else
				{
					//std::cout<<"RR"<<std::endl;
					tempNode = rotateRR(currentNode);
				}
				if(currentNode==root)
				{
					root = tempNode;
					(*tempNode).parent = NULL;
					printNode(tempNode);
				}
				else
				{
					if(currentNode==(*parentNode).left)
					{
						(*parentNode).left = tempNode;
						(*tempNode).parent = parentNode;
					}
					else
					{
						(*parentNode).right = tempNode;
						(*tempNode).parent = parentNode;
					}
					printNode(tempNode);
				}
				return;
			}
			else if(hbalance==0)
			{
				return;
			}
			else
			{
				(*currentNode).hbal = hbalance;
				currentNode = (*currentNode).parent;
				if(currentNode!=NULL)
				parentNode = (*currentNode).parent;
			}
		}
	}


	int search(int key)
	{
		currentNode = root;
		while(currentNode!=NULL)
		{
			if((*currentNode).key==key)
			{
				return (*currentNode).value;
			}
			else if((*currentNode).key>key)
			{
				currentNode = (*currentNode).left;
			}
			else
			{
				currentNode = (*currentNode).right;
			}
		}
		return 0;
	}


	AVL()
	{
		root = NULL;
	}
	void inOrderDisplay(node *p)
	{
	    if(p)
	    {
	        if(p->left)
                inOrderDisplay(p->left);
            outputfile<<p->value<<" ";
            if(p->right)
                inOrderDisplay(p->right);
	    }
	}
	void inOrder()
	{
	    inOrderDisplay(root);
	}
	void postOrderDisplay(node *p)
	{
	    if(p)
	    {
	        if(p->left)
                postOrderDisplay(p->left);
            if(p->right)
                postOrderDisplay(p->right);
            outputfile<<p->value<<" ";
	    }
	}
	void postOrder()
	{
	    postOrderDisplay(root);
	}
};
//this is the main AVL class which implements the AVL hash trees
class AVLHash
{
    private:
    AVL **AVLtrees;
    int s;
    int index;
    public:
    AVLHash(int sInput)
    {
        s = sInput;
        AVLtrees = new AVL *[s];
        int i;
        for(i=0;i<s;i++)
        {
            AVLtrees[i] = new AVL();
        }
    }
    AVLHash()
    {}
    void insert(int key,int value)
    {
        index = (key%s);
        AVLtrees[index]->insert(key,value);
    }
    int search(int key)
    {
        index = (key%s);
        return AVLtrees[index]->search(key);
    }
    void inOrder()
    {
        int i;
        for(i=0;i<s;i++)
        {
            AVLtrees[i]->inOrder();
            outputfile<<endl;
        }
    }
};
//this is the main AVL class which implements the red-black hash trees.
class RedBlackHash
{
    private:
    map<int,int> **RedBlackHashtrees;
    int s;
    int index;
    public:
    RedBlackHash(int sInput)
    {
        s = sInput;
        RedBlackHashtrees = new map<int,int> *[s];
        int i;
        for(i=0;i<s;i++)
        {
            RedBlackHashtrees[i] = new map<int,int>;
        }
    }
    RedBlackHash()
    {}
    void insert(int key,int value)
    {
        index = (key%s);
        RedBlackHashtrees[index]->insert(pair<int,int>(key,value));
    }
    int search(int key)
    {
        index = (key%s);
        return RedBlackHashtrees[index]->find(key)->second;
    }
};

int main(int argc,char *argv[])
{
    int mode,args=0;
    args++; //this is incremented in case the first argument doesnt start from 0.

    //here we select the execution mode of the program.
    if(argc == 0)
    {
        cout<<"No Arguments!\n";
        return 0;
    }
    if(strcmp(argv[args], "-r") == 0) //this is random mode.
    {
        mode = 1;
    }
    else if (strcmp(argv[args], "-u") == 0) //this is the file input mode.
    {
        mode = 2;
    }
    else
    {
        cout<<argv[args]<<endl;
        cout<<"Wrong arguments\n";
        return 0;
    }

    int m,i,n,s,j;
    //cout<<"m is: ";
    //cin>>m;
    //s = 3;
    n=1000000;

    //initialication of the trees

    btree *btreeObject;
    btreeHash *btreeHashObject;
    AVL *AVLtreeObject;
    AVLHash *AVLHashObject;
    RedBlackHash * RedBlackHashTree;
    map<int,int> redBlackTree;
    map<int,int>::iterator mit;
    AVLtreeObject = new AVL();
    int *input;
    int *values;

    if(mode==1) //this is the random execution mode.
    {

        n=1000000;
        args++;
        s = atoi (argv[args]);
        cout<<s<<endl;
        args++;
        m= atoi (argv[args]);
        cout<<m<<endl;
        if(m<3)
        {
            cout<<"m should be bigger than 2";
            return 0;
        }

        btreeObject = new btree(m);
        btreeHashObject = new btreeHash(m,s);
        AVLHashObject = new AVLHash(s);
        RedBlackHashTree = new RedBlackHash(s);

        //int input[n];
        input = new int[n];

    clock_t Start, Time;
    double sumbtree=0.0,sumbtreehash=0.0,sumAVLhash=0.0,sumAVL=0.0,sumRedBlack=0.0,sumRedBlackHash=0.0;
    double totalbtree=0.0,totalbtreehash=0.0,totalAVLhash=0.0,totalAVL=0.0,totalRedBlack=0.0,totalRedBlackHash=0.0;
    double totalbtrees=0.0,totalbtreehashs=0.0,totalAVLhashs=0.0,totalAVLs=0.0,totalRedBlacks=0.0,totalRedBlackHashs=0.0;

    //forming a random sequence of unique numbers...
    srand ( unsigned ( time (NULL) ) );
    vector<int> myvector;
    vector<int>::iterator it;
    // set some values:
    for (i=1; i<=n; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9
    // using built-in random generator:

    for(j=0;j<10;j++)
    {
    random_shuffle ( myvector.begin(), myvector.end());
    // cout<<"Following is the sequence of input: "<<endl;
    //random sequence generated
    //now saving the random sequence in an array called input[i]
    i=0;
    for (it=myvector.begin(); it!=myvector.end(); ++it)
    {
        input[i]=*it;
        i++;
    }
    //done with saving the random sequence of input
    sumbtree=0.0;sumbtreehash=0.0;sumAVL=0.0;sumAVLhash=0.0;sumRedBlack=0.0;sumRedBlackHash=0.0;

    //following is the insertion and the calculation of avg insertion time.
    cout<<endl<<endl<<"Iteration Number: "<<(j+1);
    for(i=0;i<n;i++)
    {
        Start = clock();
        btreeObject->insert(input[i],(2*input[i]));
        Time = clock() - Start;
        sumbtree = sumbtree + Time;
    }
    //cout<<"btreeObject"<<endl;

    for(i=0;i<n;i++)
    {
        Start = clock();
        btreeHashObject->insert(input[i],(2*input[i]));
        Time = clock() - Start;
        sumbtreehash = sumbtreehash + Time;
    }

    //cout<<"btreeHashObject"<<endl;

    for(i=0;i<n;i++)
    {
        Start = clock();
        AVLtreeObject->insert(input[i],(2*input[i]));
        Time = clock() - Start;
        sumAVL = sumAVL + Time;
    }

    //cout<<"AVLtreeObject"<<endl;

    for(i=0;i<n;i++)
    {

        Start = clock();
        AVLHashObject->insert(input[i],(2*input[i]));
        Time = clock() - Start;
        sumAVLhash = sumAVLhash + Time;
    }

    //cout<<"AVLHashObject"<<endl;

    for(i=0;i<n;i++)
    {

        Start = clock();
        redBlackTree.insert ( pair<int,int>(input[i],2*input[i]) );
        Time = clock() - Start;
        sumRedBlack = sumRedBlack + Time;
    }

    //cout<<"redBlackTree"<<endl;

    for(i=0;i<n;i++)
    {

        Start = clock();
        RedBlackHashTree->insert(input[i],(2*input[i]));
        Time = clock() - Start;
        sumRedBlackHash = sumRedBlackHash + Time;
    }

    //cout<<"RedBlackHashTree"<<endl;

    cout<<endl<<endl<<((sumbtree)/(double)n)<<" milliseconds Avg insert in btree.";
    cout<<endl<<((sumAVL)/(double)n)<<" milliseconds Avg insert in AVLtree.";
    cout<<endl<<((sumRedBlack)/(double)n)<<" milliseconds Avg insert in RedBlackTree.";
    cout<<endl<<((sumbtreehash)/(double)n)<<" milliseconds Avg insert in btreeHash.";
    cout<<endl<<((sumAVLhash)/(double)n)<<" milliseconds Avg insert in AVLtreeHash.";
    cout<<endl<<((sumRedBlackHash)/(double)n)<<" milliseconds Avg insert in RedBlacktreeHash.";

    totalbtree+=sumbtree;totalbtreehash+=sumbtreehash;totalAVL+=sumAVL;totalAVLhash+=sumAVLhash;totalRedBlack+=sumRedBlack;totalRedBlackHash+=sumRedBlackHash;

   //cout<<endl<<endl<<"inOrder"<<endl;
    //test->inOrder();
   // cout<<endl<<endl<<"levelOrder"<<endl;
   // test->levelOrder();
    sumbtree=0.0;sumbtreehash=0.0;sumAVL=0.0;sumAVLhash=0.0;sumRedBlack=0.0;sumRedBlackHash=0.0;
     for(i=0;i<n;i++)
     {
        Start = clock();
        btreeObject->search(input[i]);
        Time = clock() - Start;
        sumbtree = sumbtree + Time;
    }

    for(i=0;i<n;i++)
    {

        Start = clock();
        btreeHashObject->search(input[i]);
        Time = clock() - Start;
        sumbtreehash = sumbtreehash + Time;
    }

    for(i=0;i<n;i++)
    {

        Start = clock();
        AVLtreeObject->search(input[i]);
        Time = clock() - Start;
        sumAVL = sumAVL + Time;
    }

    for(i=0;i<n;i++)
    {

        Start = clock();
        AVLHashObject->search(input[i]);
        Time = clock() - Start;
        sumAVLhash = sumAVLhash + Time;
    }

    for(i=0;i<n;i++)
    {

        Start = clock();
        redBlackTree.find(input[i]);
        Time = clock() - Start;
        sumRedBlack = sumRedBlack + Time;
    }

    for(i=0;i<n;i++)
    {

        Start = clock();
        RedBlackHashTree->search(input[i]);
        Time = clock() - Start;
        sumRedBlackHash = sumRedBlackHash + Time;
     }

    cout<<endl<<endl<<((sumbtree)/(double)n)<<" milliseconds Avg search in btree.";
    cout<<endl<<((sumAVL)/(double)n)<<" milliseconds Avg search in AVLtree.";
    cout<<endl<<((sumRedBlack)/(double)n)<<" milliseconds Avg search in RedBlack.";
    cout<<endl<<((sumbtreehash)/(double)n)<<" milliseconds Avg search in btreeHash.";
    cout<<endl<<((sumAVLhash)/(double)n)<<" milliseconds Avg search in AVLtreeHash.";
    cout<<endl<<((sumRedBlackHash)/(double)n)<<" milliseconds Avg search in RedBlacktreeHash.";

    totalbtrees+=sumbtree;totalbtreehashs+=sumbtreehash;totalAVLs+=sumAVL;totalAVLhashs+=sumAVLhash;totalRedBlacks+=sumRedBlack;totalRedBlackHashs+=sumRedBlackHash;

    }

    cout<<endl<<"------------------------------------------------------"<<endl;

    cout<<endl<<endl<<((totalbtree)/(double)(n*10))<<" milliseconds Avg insert in btree after all iterations.";
    cout<<endl<<((totalAVL)/(double)(n*10))<<" milliseconds Avg insert in AVLtree after all iterations.";
    cout<<endl<<((totalRedBlack)/(double)(n*10))<<" milliseconds Avg insert in RedBlackTree after all iterations.";
    cout<<endl<<((totalbtreehash)/(double)(n*10))<<" milliseconds Avg insert in btreeHash after all iterations.";
    cout<<endl<<((totalAVLhash)/(double)(n*10))<<" milliseconds Avg insert in AVLtreeHash after all iterations.";
    cout<<endl<<((totalRedBlackHash)/(double)(n*10))<<" milliseconds Avg insert in RedBlacktreeHash after all iterations.";

    cout<<endl<<endl<<((totalbtrees)/(double)(n*10))<<" milliseconds Avg search in btree after all iterations.";
    cout<<endl<<((totalAVLs)/(double)(n*10))<<" milliseconds Avg search in AVLtree after all iterations.";
    cout<<endl<<((totalRedBlacks)/(double)(n*10))<<" milliseconds Avg search in RedBlackTree after all iterations.";
    cout<<endl<<((totalbtreehashs)/(double)(n*10))<<" milliseconds Avg search in btreeHash after all iterations.";
    cout<<endl<<((totalAVLhashs)/(double)(n*10))<<" milliseconds Avg search in AVLtreeHash after all iterations.";
    cout<<endl<<((totalRedBlackHashs)/(double)(n*10))<<" milliseconds Avg search in RedBlacktreeHash after all iterations.\n";
    }

    else if(mode==2)
    {
        btreeObject = new btree(3);
        btreeHashObject = new btreeHash(3,3);
        AVLHashObject = new AVLHash(3);
        int p,q;
        string line;
        args++;

        //trying to take the input from the file
        inputfile.open(argv[args]);
        if (inputfile.is_open())
        {
            getline (inputfile,line);
            sscanf(line.c_str(), "%d", &n);
            cout<<n<<" inputs."<<endl;
            input = new int[n];
            values = new int[n];
            i=0;
        while (i<n )
        {
            getline (inputfile,line);
            sscanf(line.c_str(), "%d %d", &input[i],&values[i]);
            //cout << input[i]<<" "<<q << endl;
            i++;
        }
        inputfile.close();
    }

    else cout << "Unable to open file";

    //inputs taken from the file,

//inserting the input into the different trees.

    for(i=0;i<n;i++)
    {
        btreeObject->insert(input[i],values[i]);
    }

    for(i=0;i<n;i++)
    {
        btreeHashObject->insert(input[i],values[i]);
    }

    for(i=0;i<n;i++)
    {
        AVLtreeObject->insert(input[i],values[i]);
    }

    for(i=0;i<n;i++)
    {
        AVLHashObject->insert(input[i],values[i]);
    }

//saving the output in the files.

    outputfile.open ("AVL_inorder.out");
    AVLtreeObject->inOrder();
    outputfile.close();

    outputfile.open ("AVL_postorder.out");
    AVLtreeObject->postOrder();
    outputfile.close();

    outputfile.open ("AVLHash_inorder.out");
    AVLHashObject->inOrder();
    outputfile.close();

    outputfile.open ("BTree_sorted.out");
    btreeObject->inOrder();
    outputfile.close();

    outputfile.open ("BTree_level.out");
    btreeObject->levelOrder();
    outputfile.close();

    outputfile.open ("BTreeHash_level.out");
    btreeHashObject->levelOrder();
    outputfile.close();



    }

    return 0;
}
