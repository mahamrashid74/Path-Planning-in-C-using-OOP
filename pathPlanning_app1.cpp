#include<iostream>
#include <string>
#include<time.h>
#include<Windows.h>
#include<glut.h>
using namespace std;

const int size = 10;//defines the boundaries of working space
int obstacles[7][2];
int arr[size][size];//working space

struct node //each node represents a point
{
	int data1;//x coordinate of the point
	int data2;//y coordinate of the point
	node*left;
	node*right;
	node*up;
	node*down;//links one point to the next point
};

struct finalpath
{
	int data1;
	int data2;
	finalpath*next;
};

struct obstacle
{
	int data1;
	int data2;
	obstacle*next;
};

obstacle*finalobstacle = new obstacle;
obstacle* ohead=new obstacle;
finalpath* path=new finalpath;

class Path1
{
private:
	int x;
	int y;
	int togo;
	int distance;
	int check;
	node*newhead;
	node*head;

public:
	int finalx;
	int finaly;

Path1()
{
	head = new node; 
}
	/*Path1(node*, int, int, int, int, int, int, int,node*,obstacle*,finalpath*);*/

node* makehead(node*c)
{
	c=head;
	return c;
}
bool repeat(node*itemp, int x, int y)
{
	node*temp=itemp;
	while(temp!=NULL)
	{
		if(temp->data1==x && temp->data2==y)
			return true;
		else 
		{
			if(temp->left != NULL)
			{
				temp=temp->left;
			}
			else if(temp->right != NULL)
			{
				temp=temp->right;
			}
			else if(temp->up != NULL)
			{
				temp=temp->up;
			}
			else if(temp->down != NULL)
			{
				temp=temp->down;
			}
			else 
			{
				break;
			}
		}
	}
	return false;
}

node* newpath(int xco, int yco, node*prevhead)//gets rid of the older path and creates a new path
{
	int shortestdist = xco + yco;//evaluates shortest distance
	
	int x= 0;
	int y = 0;

	//creating the path from the beginning
	newhead->left = NULL;
	newhead->right= NULL;
	newhead->up=NULL;
	newhead->down=NULL;
	newhead->data1=x;
	newhead->data2=y;
	node*curr = new node;
	curr = newhead;//head points to the node similar to that head points 

	//infinite loop
	for(int s=0;s<30;s++)
	{
		int num = rand() % 2;//random number is generated i.e. either 0 or 1
		if (num == 0 && x < xco)//
		{
			x++;
		
		if(ifobstacle(x,y)==false)
		{curr = insertpath(curr, x, y,num);}
		else
			x--;
		}
		else if (num == 1 && y < yco)
		{
			y++;
		if(ifobstacle(x,y)==false)
		{curr = insertpath(curr, x, y,num);}
		else
			y--;
		}
		else if (x == xco && y == yco)
		{
			break;
		}
	}
	if(x == xco && y == yco)
	{

		return newhead;}
	else
		return prevhead;
}

node* insertpath(node*temp, int & xcord, int & ycord, int togo)//inputs are pointer to the node or point, x and y coordinates  of the point
{ 
	if(repeat(head,xcord,ycord)==false)
	{
		if ((xcord >= 0 && ycord >= 0) && (xcord < size && ycord < size))
		{
			if(togo==0)
			{
				node*newnode= new node;
				newnode->data1 = xcord;//newnode stores x coordinate of the point to be linked
				newnode->data2 = ycord;//newnode stores y coordinate of the point to be linked
				temp->down=newnode;
				temp=temp->down;
				temp->down=NULL;
				temp->left=NULL;
				temp->up=NULL;
				temp->right=NULL;
			}
			if(togo==1)
			{
				node*newnode= new node;
				newnode->data1 = xcord;//newnode stores x coordinate of the point to be linked
				newnode->data2 = ycord;//newnode stores y coordinate of the point to be linked
				temp->right=newnode;
				temp=temp->right;
				temp->down=NULL;
				temp->left=NULL;
				temp->up=NULL;
				temp->right=NULL;
			}
			if(togo==2)
			{
				node*newnode= new node;
				newnode->data1 = xcord;//newnode stores x coordinate of the point to be linked
				newnode->data2 = ycord;//newnode stores y coordinate of the point to be linked
				temp->up=newnode;
				temp=temp->up;
				temp->down=NULL;
				temp->left=NULL;
				temp->up=NULL;
				temp->right=NULL;
			}
			if(togo==3)
			{
				node*newnode= new node;
				newnode->data1 = xcord;//newnode stores x coordinate of the point to be linked
				newnode->data2 = ycord;//newnode stores y coordinate of the point to be linked
				temp->left=newnode;
				temp=temp->left;
				temp->down=NULL;
				temp->left=NULL;
				temp->up=NULL;
				temp->right=NULL;
			}
		}
		else
		{
			if(togo==3)
			{ycord++;}
			if(togo==1)
			{ycord--;}
		    if(togo==0)
			{xcord--;}
			if(togo==2)
			{xcord++;}
		}
		return temp;
	}
	else
	{
		if(togo==3)
		{ycord++;}
		if(togo==1)
		{ycord--;}
		if(togo==0)
		{xcord--;}
		if(togo==2)
		{xcord++;}
		return temp;
	}
}

bool ifobstacle(int x, int y)
{
	obstacle*temp=ohead;
	while (temp != NULL)
	{
		if (temp->data1 == x && temp->data2 == y)
			return true;
		else
			temp = temp->next;

	}
	return false;

}
int checkinc()
{
	check++;//increments check every time a node is created or a new point is linked to the former point
	return check;
}

bool dist(int distance, int check) 
{
	//checks if there is any possible distance less than check (already covered distance)
	if (distance < check)
		return true;
	else 
		return false;
}
void display()
{
	node*newtemp=new node;
	newtemp=head;
	finalpath*currpath=new finalpath;
	currpath = path;
	while(newtemp!=NULL)
	{   
		currpath->data1 = newtemp->data1;
		currpath->data2 = newtemp->data2;
		cout<<newtemp->data1<<" "<<newtemp->data2<<endl;
		if(newtemp->left != NULL)
		{
			newtemp=newtemp->left;
		}
		else if(newtemp->right != NULL)
		{
			newtemp=newtemp->right;
		}
		else if(newtemp->up != NULL)
		{
			newtemp=newtemp->up;
		}
		else if(newtemp->down != NULL)
		{
			newtemp=newtemp->down;
		}
		else
		{
			break;	
		}
		currpath->next=new finalpath;
		currpath=currpath->next;
	}
	currpath->next=NULL;
}
void displayobstacle()
{
	obstacle*newtemp=new obstacle;
	newtemp=ohead;
	while(newtemp!=NULL)
	{
		cout<<newtemp->data1<<" "<<newtemp->data2<<endl;
		newtemp=newtemp->next;
	}
}
void callnewpath(int xcord, int ycord)
{
	head = newpath(xcord, ycord, head);
}


~Path1()
{
	cout << "Path destroyed" << endl;
}
};

void Draw() 
{
	//Path1 pathfunc2;
	obstacle*ob = ohead;
	glClear(GL_COLOR_BUFFER_BIT);

	for (float boundry = 5; boundry <= 95; boundry = boundry + 1)
	{
		boundry = boundry / 100;
		glColor3f(0, 0, 1);
		glBegin(GL_POINTS);
		glVertex3f(boundry, 0.05, 0);
		boundry = boundry * 100;
		glEnd();
		glFlush();
	}
	for (float boundry = 5; boundry <= 95; boundry = boundry + 1)
	{
		boundry = boundry / 100;
		glColor3f(0, 0, 1);
		glBegin(GL_POINTS);
		glVertex3f(0.05, boundry, 0);
		boundry = boundry * 100;
		glEnd();
		glFlush();
	}
	for (float boundry = 5; boundry <= 95; boundry = boundry + 1)
	{
		boundry = boundry / 100;
		glColor3f(0, 0, 1);
		glBegin(GL_POINTS);
		glVertex3f(boundry, 0.95, 0);
		boundry = boundry * 100;
		glEnd();
		glFlush();
	}
	for (float boundry = 5; boundry <= 95; boundry = boundry + 1)
	{
		boundry = boundry / 100;
		glColor3f(0, 0, 1);
		glBegin(GL_POINTS);
		glVertex3f(0.95, boundry, 0);
		boundry = boundry * 100;
		glEnd();
		glFlush();
	}
	glColor3f(1, 1, 1);
	while (finalobstacle != NULL)
	{
		float x, y;
		x = finalobstacle->data1;
		y = finalobstacle->data2;
		x = x / 10;
		y = y / 10;
		glBegin(GL_LINES);

		glVertex3f(x + 0.1 + 0.05, y + 0.1 + 0.05, 0);
		glVertex3f(x + 0.1 + 0.05, y + 0.1 - 0.05, 0);
		glVertex3f(x + 0.1 - 0.05, y + 0.1 + 0.05, 0);
		glVertex3f(x + 0.1 - 0.05, y + 0.1 - 0.05, 0);
		glVertex3f(x + 0.1 + 0.05, y + 0.1 - 0.05, 0);
		glVertex3f(x + 0.1 - 0.05, y + 0.1 - 0.05, 0);
		glVertex3f(x + 0.1 + 0.05, y + 0.1 + 0.05, 0);
		glVertex3f(x + 0.1 - 0.05, y + 0.1 + 0.05, 0);
		glEnd();
		glFlush();
		x = x * 10;
		y = y * 10;
		/*cout<<x<<" "<<y<<endl;*/
		finalobstacle = finalobstacle->next;
	}
	glColor3f(1, 0, 0);
	while (path->next != NULL)
	{
		Sleep(500);
		float a, b, c, d;
		a = path->data1;
		b = path->data2;
		c = path->next->data1;
		d = path->next->data2;
		a = a / 10;
		b = b / 10;
		c = c / 10;
		d = d / 10;
		glBegin(GL_LINES);
		glVertex3f(a + 0.1, b + 0.1, 0.0);
		glVertex3f(c + 0.1, d + 0.1, 0.0);
		a = a * 10;
		b = b * 10;
		c = c * 10;
		d = d * 10;

		glEnd();
		glFlush();
		/*cout<<c<<" "<<d<<endl;*/
		path = path->next;
	}
}

void Initialize() 
{
	glClearColor(0, 0, 0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void create_obstacle(int finx,int finy)
{
	obstacle*c = ohead;
	for (int i=0;i<5;i++)
	{
		int xrandom=2*(rand()%4);
		int yrandom=2*(rand()%3+1);
		if (xrandom!=finx && yrandom!=finy)
		{
			if((xrandom==0 && yrandom==0)||(xrandom==0 && yrandom==1) || (xrandom==1 && yrandom== 0))
			{
				i--;
			}
			else
			{
				c->data1=xrandom;
				c->data2=yrandom;
				if(i<4)
				{
					c->next=new obstacle;
					c=c->next;
				}
			}
		}
		else
		{
			i--;
		}
	}
	c->next=NULL;
}

int main(int iArgc, char** cppArgv)
{	
	Path1 path1;
	srand(time(NULL));//sets time to 0

	int xc, yc, finalx, finaly;
	xc=0,yc=0,finalx=7,finaly=5;
	int num;
	//sets values of the initial point/node
	
	node*curr;
	curr=path1.makehead(curr);
	
	create_obstacle(finalx,finaly);
	cout<<"obstacles:"<<endl;
	path1.displayobstacle();
	cout<<endl;

	while(1)
	{
		num = rand() % 4;//random number between 0 and 4 is generated
		//cout << "number generated" << togo << endl;
		if (num== 0)
		{
			xc++;
		}
		else if (num == 1)
		{
			yc++;
		}
		else if (num == 2)
		{
			xc--;
		}
		else if (num == 3)
		{
			yc--;
		}
		
		if(path1.ifobstacle(xc,yc)==false)
		{curr = path1.insertpath(curr,xc,yc,num);//creates the path by inserting node and storing values in it
		int checkdist=path1.checkinc();//increments check every time a node is added to the tree
		int mindistance = xc + yc;//calculates shortest distance
		
		//check if distance covered is or is not the shortest
		if (path1.dist(mindistance,checkdist) == true)
		{
			path1.callnewpath(xc, yc);//if distance covered is greater than shortest distance, new path is created
		}
		}
		else
		{
		if (num == 0)
		{xc--;}
		else if (num == 1)
		{yc--;}
		else if (num == 2)
		{xc++;}
		else if (num == 3)
		{yc++;}
		}
		if(xc==path1.finalx&&yc==path1.finaly)
		break;
	}
	path1.display();
	
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("XoaX.net");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	
	system("pause");
	return 0;
}

